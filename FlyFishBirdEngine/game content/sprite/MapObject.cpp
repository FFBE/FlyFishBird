//
//  DesignRootObject.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/29.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "MapObject.hpp"

#define TextViewTag                 1


using namespace ffb;

void MapObject::Clear()
{
#if FFBDEBUG
    m_textInput = FFBMalloc(TextInput);
#endif
    Object::Clear();
    m_choseObject = nullptr;
    m_subObjectCanRespond = false;
    m_choseGameItem = m_gameItems.end();

}

void MapObject::Destory()
{
#if FFBDEBUG
    m_textInput->DestoryTexInputByTag(TextViewTag);
    FFBSaveFree(m_textInput);
#endif
    Object::Destory();
}

bool MapObject::Create()
{
    return Object::Create();
}

#if FFBDEBUG
bool MapObject::Create(int level, bool design)
#else
bool MapObject::Create(int level)
#endif
{
    if (!Object::Create()) {
        return false;
    }
    
#if FFBDEBUG
    if (design) {
        Size screenSize = Device::GetSingletonPtr()->GetScreenSize();
        m_textInput->CreateTextInputInRect(PointMake(screenSize.width/2-100, 30), SizeMake(200, 80), 1);
        m_textInput->SetTextByTag(TextViewTag, "fileName:\nwidth:\nheight:\nx:\ny:");
        m_textInput->SetTextInputHiddenByTag(TextViewTag, true);
    }
#endif
    
    m_level = level;
    AnalysisGameByLevel(m_gameItems, level);
    
    size_t number = m_gameItems.size();
    
    GameItem item;
    for (size_t i = 0; i<number; i++) {
        item = m_gameItems[i];
        RepeatSprite * sprite = FFBMalloc(RepeatSprite);
        sprite->Create(item.fileName);
        sprite->SetRepeatSize(item.width, item.height);
        sprite->SetPosition(item.x, item.y);
        AddObject(sprite);
    }
    
    return true;
}

int MapObject::GetLevel()
{
    return m_level;
}

#if FFBDEBUG
#include "SelectSprite.hpp"

std::string MapObject::GetDesignString()
{
    char level[3]; IntToString(level, m_level);
    std::string designString = "level_"; designString = designString + level + "\n";
    for (GameItem item : m_gameItems)
    {
        std::string itemString = "{\n";
        char width[10]; IntToString(width, item.width);
        char height[10]; IntToString(height, item.height);
        char x[10]; IntToString(x, item.x);
        char y[10]; IntToString(y, item.y);
        itemString += "fileName:" + item.fileName + "\nwidth:" + width + "\nheight:" + height + "\nx:" + x + "\ny:" + y + "\n}\n";
        designString += itemString;
    }
    return designString;
}

void MapObject::Sure(ffb::TouchObject * object)
{
    std::string inputString = m_textInput->GetTextByTag(TextViewTag);
    GameItem item = AnalysisString(inputString);
    
    SelectSprite * sprite = static_cast<SelectSprite *>(m_choseObject);
    sprite->Create(item.fileName);
    sprite->SetRepeatSize(item.width, item.height);
    sprite->SetPosition(item.x, item.y);
    Cancel(nullptr);
    
    *m_choseGameItem = item;
    
}

void MapObject::Cancel(ffb::TouchObject * object)
{
    m_choseObject->SetScale(1);
    m_textInput->SetTextInputHiddenByTag(TextViewTag, true);
    m_choseObject = nullptr;
    SetTouchEnable(true);
}

void MapObject::SpriteBeenTouch(ffb::TouchObject *object)
{
    if (m_choseObject != nullptr) {
        m_choseObject->SetScale(1.0);
    }
    m_choseObject = object;
    m_choseObject->SetScale(1.3);
    m_textInput->SetTextInputHiddenByTag(TextViewTag, false);
    SetTouchEnable(false);
    
    SelectSprite * sprite = static_cast<SelectSprite *>(object);
    char width[10]; IntToString(width, sprite->GetSprite()->GetSize().width);
    char height[10]; IntToString(height, sprite->GetSprite()->GetSize().height);
    char x[10]; IntToString(x, sprite->GetPosition().x);
    char y[10]; IntToString(y, sprite->GetPosition().y);
    std::string text =  "fileName:" + sprite->GetSprite()->GetFileName() + "\nwidth:" + width + "\nheight:" + height + "\nx:" + x + "\ny:" + y;
    m_textInput->SetTextByTag(TextViewTag, text);
    
    GameItems::iterator itera = m_gameItems.begin();
    for (; itera != m_gameItems.end(); itera ++) {
        GameItem item = *itera;
        if (item.fileName == sprite->GetSprite()->GetFileName() &&
            item.width == sprite->GetRepeatSize().width &&
            item.height == sprite->GetRepeatSize().height &&
            item.x == sprite->GetPosition().x &&
            item.y == sprite->GetPosition().y) {
            m_choseGameItem = itera;
        }
    }
}

void MapObject::AddTouchObject()
{
    if (m_choseObject != nullptr) {
        return;
    }
    
    SelectSprite * sprite = FFBMalloc(SelectSprite);
    sprite->Create("game_triangle");
    sprite->SetPosition(100, 100);
    sprite->SetRepeatSize(32, 28);
    AddObject(sprite);
    sprite->SetTouchFunction(function1st(MapObject::SpriteBeenTouch, this));
    sprite->release();
    GameItem item = {"game_triangle", 28, 32, 100, 100};
    m_gameItems.push_back(item);
    
    SpriteBeenTouch(sprite);
}

void MapObject::RemoveTouchObject()
{
    if(m_choseObject == nullptr) return;
    RemoveObject(m_choseObject);
    Cancel(nullptr);
}

void MapObject::TouchObjectCannotTouch()
{
    m_subObjectCanRespond = false;
}

bool MapObject::TouchShouldBegin(ffb::Touch *touch)
{
    m_subObjectCanRespond = true;
    TimeSchedule::GetSingletonPtr()->AddSchedule(function0st(MapObject::TouchObjectCannotTouch, this), 0.3);
    m_lastTouchPoint = touch->ConverTouchPointToObject(this);
    
    return true;
}

void MapObject::TouchMoved(ffb::Touch *touch)
{
    m_subObjectCanRespond = false;
    Point point = touch->ConverTouchPointToObject(this);
    
    float x = m_position.x + point.x - m_lastTouchPoint.x;
    if (x > 0) {
        return;
    }
    m_position = PointMake(x , m_position.y);
    
    m_lastTouchPoint = point;
}

void MapObject::TouchEnd(ffb::Touch *touch)
{
    if (m_subObjectCanRespond) {
        
        ObjectList::iterator itera = m_objectList.begin();
        Object * object;
        for (; itera != m_objectList.end(); ++itera) {
            object = *itera;
            if (object->TouchShouldBegin(touch)) {
                TouchObject * touchObject = static_cast<TouchObject *>(object);
                touchObject -> TouchEnd(touch);
            }
        }
        
    }
    
    m_subObjectCanRespond = false;
}

#endif




















