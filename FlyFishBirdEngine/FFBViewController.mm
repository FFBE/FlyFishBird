//
//  FFBViewController.m
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/30.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#import "FFBViewController.h"
#import "GameController.hpp"
#import "DrawObject.hpp"
#import "Texture2D.hpp"
#import <OpenGLES/ES2/glext.h>

using namespace ffb;

@interface FFBViewController()
{
    GameController * controller;
}

@property (strong, nonatomic) EAGLContext * context;
@property (strong, nonatomic) GLKBaseEffect * effect;

@property (nonatomic, assign)NSTimeInterval lastTime;
@property (nonatomic, assign)NSTimeInterval newTime;

- (void)setupGL;
- (void)tearDownGL;

@end


@implementation FFBViewController

- (instancetype)init
{
    self = [super init];
    if (self) {
        _newTime = 0;
        _lastTime = [[NSDate date]timeIntervalSince1970];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    NSLog(@"%@", NSStringFromCGSize(self.view.frame.size));

    controller = GameController::GetSingletonPtr();
    controller->SetGLVersion(3.0);
    self.context = [[EAGLContext alloc]initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!self.context) {
        NSLog(@"failed to create ES3 context");
        controller->SetGLVersion(2.0);
        self.context = [[EAGLContext alloc]initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if (!self.context) {
            NSLog(@"failed to create ES2 context");
            return;
        }
    }
    
    GLKView * view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void)dealloc
{
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    if ([self isViewLoaded] && [[self view] window]) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        
        self.context = nil;
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    CGFloat scale = [UIScreen mainScreen].scale;
    
    controller->SetScreenScale(scale);
    controller->SetScreenSize(self.view.frame.size.width, self.view.frame.size.height);
    
    Scene * scene = FFBMalloc(Scene);
    scene->Create();
    controller->SetRootScene(scene);
    
    DrawObject * drawObject = FFBMalloc(DrawObject);
    drawObject->Create();
    drawObject->DrawCircleAndFill(0, 0, 200);
    drawObject->SetColor(1, 1, 1, 1);
    scene->GetRootObject()->AddObject(drawObject);
    drawObject->release();
    drawObject->SetPosition(0, 0);
    
//    Texture2D *texture1 = FFBMalloc(Texture2D);
//    texture1->CreateImageTexture("login.png");
//    Object * object1 = FFBMalloc(Object);
//    object1->Object::Create(texture1);
//    scene->GetRootObject()->AddObject(object1);
//    object1->SetPosition(100, 100);
//    texture1->release();
//    object1->release();
//    
//    Texture2D *texture2 = FFBMalloc(Texture2D);
//    texture2->CreateImageTexture("sale.png");
//    Object * object2 = FFBMalloc(Object);
//    object2->Object::Create(texture2);
//    scene->GetRootObject()->AddObject(object2);
//    object2->SetPosition(100, 100);
//    texture2->release();
//    object2->release();
    
    Texture2D *texture = FFBMalloc(Texture2D);
    texture->CreateStringTexture("Helvetica", "我的", 20);
    Object * object = FFBMalloc(Object);
    object->Object::Create(texture);
    object->SetPosition(0, 0);
    scene->GetRootObject()->AddObject(object);
    texture->release();
    object->release();
    
    
    scene->release();
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

- (void)update
{
    _newTime = [[NSDate date]timeIntervalSince1970];
    controller->update(_newTime-_lastTime);
    _lastTime = [[NSDate date]timeIntervalSince1970];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    controller->render();
}

@end
