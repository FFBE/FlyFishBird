//
//  FFBViewController.m
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/30.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#import "FFBViewController.h"

#import <OpenGLES/ES2/glext.h>

#import "GameController.hpp"
#import "DrawObject.hpp"
#import "AutoReleasePool.hpp"

using namespace ffb;

@interface FFBViewController()
{
    GameController * controller;
    PoolManager * poolManager;
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

    poolManager = PoolManager::GetSingletonPtr();
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
//Point ctrlPts[] = {{-40, -40}, {-10, 200}, {10, -200}, {40, 40}};

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    CGFloat scale = [UIScreen mainScreen].scale;
    
    controller->GetDevice()->SetScreenScale(scale);
    controller->GetDevice()->SetScreenSize(self.view.frame.size.width, self.view.frame.size.height);
    
    Scene * scene = FFBMalloc(Scene);
    scene->Create();
    controller->SetRootScene(scene);
    
    DrawObject * draw = FFBMalloc(DrawObject);
    draw->Create();
    draw->DrawLine(0, 0, 100, 100);
    draw->SetColor(1, 1, 1, 1);
    scene->GetRootObject()->AddObject(draw);
    draw->release();
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

    poolManager->GetMainPool()->Clear();
}

@end
