//
//  UIUtils.h
//  Mappin
//
//  Created by bibi-apple on 31/1/14.
//  Copyright (c) 2014 Spotcat Studio. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "cocos2d.h"

@interface UIView (UIUtils)
- (id)findFirstResponder;
@end


@interface UIUtils : NSObject{
    NSDateFormatter *datePreFormatter;
    NSDateFormatter *datePostFormatter;
}

+ (UIUtils*)sharedInstance;

- (NSDateFormatter*)datePreFormatter;
- (NSDateFormatter*)datePostFormatter;

- (UIImage*)maskImage:(UIImage *) image withMask:(UIImage *) mask;
- (UIImage *)scaleImage:(UIImage *)image toSize:(CGSize)newSize;

- (cocos2d::Sprite*)uiImageToSprite:(UIImage*)image;
- (UIImage*)spriteToUIImage:(cocos2d::Sprite*)sprite;

@end
