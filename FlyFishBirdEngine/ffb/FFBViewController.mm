//
//  FFBViewController.m
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/30.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#import "FFBViewController.h"
#import <objc/runtime.h>
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
    view.multipleTouchEnabled = YES;
    
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
    
    float scale = self.view.frame.size.height/320.0;

    controller->GetDevice()->SetScreenScale(scale * [UIScreen mainScreen].scale);
    controller->GetDevice()->SetScreenSize(self.view.frame.size.width/scale, 320);

    GameScene * scene = FFBMalloc(GameScene);
    scene->Create();
    controller->SetRootScene(scene);
    scene->release();
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

- (void)update
{
    controller->update(self.timeSinceLastUpdate);
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch * touch = [event allTouches].anyObject;
    ffb::Point point = [self converViewPointToGamePoint:[touch locationInView:self.view]];
    Object * touchObject = controller->GetCurrentScene()->GetRootObject()->TouchCheck(point);
    controller->GetCurrentScene()->SetTouchObject(touchObject);
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch * touch = [event allTouches].anyObject;
    ffb::Point point = [self converViewPointToGamePoint:[touch locationInView:self.view]];
    Object * touchObject = controller->GetCurrentScene()->GetTouchObject();
    if(touchObject != nullptr)
    {
        touchObject->TouchMoved(point);
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch * touch = [event allTouches].anyObject;
    ffb::Point point = [self converViewPointToGamePoint:[touch locationInView:self.view]];
    Object * touchObject = controller->GetCurrentScene()->GetTouchObject();
    if(touchObject != nullptr)
    {
        touchObject->TouchEnd(point);
    }
}

- (ffb::Point)converViewPointToGamePoint:(CGPoint)viewPoint
{
    ffb::Size screenSize = controller->GetDevice()->GetScreenSize();
    return PointMake(viewPoint.x, screenSize.height-viewPoint.y);
}

@end
