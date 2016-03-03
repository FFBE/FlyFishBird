//
//  TextInput.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/3/1.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "TextInput.hpp"
#import <UIKit/UITextView.h>
#import <UIKit/UIApplication.h>
#import "AppDelegate.h"

namespace ffb {
    
    
    void TextInput::CreateTextInputInRect(Point point, Size size, int tag)
    {
        AppDelegate * m_delegate = [UIApplication sharedApplication].delegate;
        UITextView * textView = [[UITextView alloc]initWithFrame:CGRectMake(point.x, point.y, size.width, size.height)];
        textView.font = [UIFont systemFontOfSize:17];
        textView.backgroundColor = [UIColor grayColor];
        [m_delegate.window.rootViewController.view addSubview:textView];
        textView.tag = tag;
    }
    
    void TextInput::DestoryTexInputByTag(int tag)
    {
        AppDelegate * m_delegate = [UIApplication sharedApplication].delegate;
        [[m_delegate.window.rootViewController.view viewWithTag:tag] removeFromSuperview];
    }
    
    std::string TextInput::GetTextByTag(int tag)
    {
        AppDelegate * m_delegate = [UIApplication sharedApplication].delegate;
        UITextView * textView = [m_delegate.window.rootViewController.view viewWithTag:tag];
        return textView.text.UTF8String;
    }
    
    void TextInput::SetTextInputHiddenByTag(int tag, bool hidden)
    {
        AppDelegate * m_delegate = [UIApplication sharedApplication].delegate;
        UITextView * textView = [m_delegate.window.rootViewController.view viewWithTag:tag];
        textView.hidden = hidden?YES:NO;
        if (hidden) {
            [textView resignFirstResponder];
        }
        else
        {
            if ([textView canBecomeFirstResponder]) {
                [textView becomeFirstResponder];
            }
        }
    }
    
    void TextInput::SetTextByTag(int tag, std::string text)
    {
        AppDelegate * m_delegate = [UIApplication sharedApplication].delegate;
        UITextView * textView = [m_delegate.window.rootViewController.view viewWithTag:tag];
        textView.text = [NSString stringWithFormat:@"%s", text.c_str()];
    }
}




