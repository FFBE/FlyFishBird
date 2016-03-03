//
//  GameLevelAnalysis.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/3/1.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "GameLevelAnalysis.hpp"
#include "ReadFile.h"
#include "Macro.h"
#include "DiskCache.hpp"



void CopyItem(GameItem formItem, GameItem &toItem)
{
    toItem.fileName = formItem.fileName;
    toItem.height = formItem.height;
    toItem.width = formItem.width;
    toItem.x = formItem.x;
    toItem.y = formItem.y;
}

void AnalysisGameByLevel(GameItems &gameitems, int level)
{
    std::string fileContent;
    char levelStr[3];
    sprintf(levelStr, "%d", level);
    std::string levelString = "level_";
    levelString += levelStr;
#if FFBDEBUG
    
    fileContent = ffb::DiskCache::GetSingletonPtr()->GetStringForKey(levelString);
    
#else
    fileContent = ReadFile("gamelevel.txt");
    
    int i = (int)fileContent.find(levelString);
    fileContent = fileContent.substr(i);
    
    level++;
    sprintf(levelStr, "%d", level);
    levelString = "level_";
    levelString += levelStr;
    
    i = (int)fileContent.find(levelString);
    fileContent = fileContent.substr(0, i);
#endif
    
    while (fileContent != "") {
        
        int j = (int)fileContent.find("{")+1;
        std::string itemStr = fileContent.substr(j);
        
        j = (int)fileContent.find("}");
        itemStr = itemStr.substr(0, j);
        
        GameItem item = AnalysisString(itemStr);
        
        gameitems.push_back(item);
        
        fileContent = fileContent.substr(j);
    }
    
}


GameItem AnalysisString(std::string itemString )
{
    GameItem item = {"", 0, 0, 0, 0};
    std::string itemStr = itemString + "\n";
    while (itemStr != "") {
        int attributeIndex = (int)itemStr.find("\n");
        if (attributeIndex == 0) {
            continue;
        }
        
        std::string attributeStr = itemStr.substr(0, attributeIndex);
        itemStr = itemStr.substr(attributeIndex+1);
        
        int typeIndex = (int)attributeStr.find(":")+1;
        std::string typeStr = attributeStr.substr(0, typeIndex);
        if (typeStr.length() == attributeStr.length()) {
            continue;
        }
        std::string valueStr = attributeStr.substr(typeIndex);
        
        if (typeStr == "fileName:") {
            char file[30];
            sscanf(valueStr.c_str(), "%s", file);
            item.fileName = file;
        }
        else if (typeStr == "width:")
        {
            sscanf(valueStr.c_str(), "%f", &item.width);
        }
        else if (typeStr == "height:")
        {
            sscanf(valueStr.c_str(), "%f", &item.height);
        }
        else if (typeStr == "x:")
        {
            sscanf(valueStr.c_str(), "%f", &item.x);
        }
        else if (typeStr == "y:")
        {
            sscanf(valueStr.c_str(), "%f", &item.y);
        }
    }
    return item;
}
