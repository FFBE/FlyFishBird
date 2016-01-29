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
#import "GameScene.hpp"

using namespace ffb;

@interface FFBViewController()
{
    GameController * controller;
}

@property (strong, nonatomic) EAGLContext * context;


- (void)setupGL;
- (void)tearDownGL;

@end


@implementation FFBViewController

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
//Point ctrlPts[] = {{-40, -40}, {-10, 200}, {10, -200}, {40, 40}};

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    CGFloat scale = [UIScreen mainScreen].scale;

    controller->GetDevice()->SetScreenScale(scale);
    controller->GetDevice()->SetScreenSize(self.view.frame.size.width, self.view.frame.size.height);

    GameScene * scene = FFBMalloc(GameScene);
    scene->Create();
    controller->SetRootScene(scene);
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

- (void)update
{
    controller->update(self.timeSinceLastUpdate);
}

@end
