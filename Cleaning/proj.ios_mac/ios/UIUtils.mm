//
//  UIUtils.m
//  Mappin
//
//  Created by bibi-apple on 31/1/14.
//  Copyright (c) 2014 Spotcat Studio. All rights reserved.
//

#import "UIUtils.h"

USING_NS_CC;

@interface UIUtils ()
{
}

@end

@implementation UIUtils

+(UIUtils *)sharedInstance
{
    static UIUtils* instance;
    
    if (instance == NULL) {
        instance = [UIUtils new];
    }
    
    return instance;
}

-(NSDateFormatter *)datePreFormatter
{
    if(!datePreFormatter){
        datePreFormatter = [NSDateFormatter new];
        datePreFormatter.dateFormat = @"yyyy-MM-dd HH:mm:ss";
        
    }
    return datePreFormatter;
}

-(NSDateFormatter *)datePostFormatter
{
    if(!datePostFormatter){
        datePostFormatter = [NSDateFormatter new];
        datePostFormatter.dateFormat = @"dd MMM yyyy";
    }
    return datePostFormatter;
}

- (UIImage*)maskImage:(UIImage *) image withMask:(UIImage *) mask
{
    CGImageRef imageReference = image.CGImage;
    CGImageRef maskReference = mask.CGImage;
    
    CGImageRef imageMask = CGImageMaskCreate(CGImageGetWidth(maskReference),
                                             CGImageGetHeight(maskReference),
                                             CGImageGetBitsPerComponent(maskReference),
                                             CGImageGetBitsPerPixel(maskReference),
                                             CGImageGetBytesPerRow(maskReference),
                                             CGImageGetDataProvider(maskReference),
                                             NULL, // Decode is null
                                             YES // Should interpolate
                                             );
    
    CGImageRef maskedReference = CGImageCreateWithMask(imageReference, imageMask);
    
    UIImage *maskedImage = [UIImage imageWithCGImage:maskedReference];
    
    CGImageRelease(maskedReference);
    CGImageRelease(imageMask);
    
    return maskedImage;
}

- (UIImage *)scaleImage:(UIImage *)image toSize:(CGSize)newSize
{
    UIGraphicsBeginImageContext(newSize);
    
    [image drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

- (Sprite*)uiImageToSprite:(UIImage *)image
{
    Image *imf = new Image();
    NSData *imgData = UIImagePNGRepresentation(image);
    NSUInteger len = [imgData length];
    Byte *byteData = (Byte*)malloc(len);
    memcpy(byteData, [imgData bytes], len);
    imf->initWithImageData(byteData,imgData.length);
    imf->autorelease();
    Texture2D* pTexture = new Texture2D();
    pTexture->initWithImage(imf);
    pTexture->autorelease();
    Sprite *sprite = Sprite::createWithTexture(pTexture);
    CCLOG("size :%f :%f ", sprite->getContentSize().width , sprite->getContentSize().height);
    
    return sprite;
}

-(UIImage *)spriteToUIImage:(Sprite*)sprite
{
    cocos2d::Size spriteSize = sprite->getContentSize();
    Sprite *nSprite = sprite;
    nSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    nSprite->setPosition(Vec2::ZERO);
    
    nSprite->setFlippedY(true);
    
    RenderTexture* rt = RenderTexture::create(spriteSize.width, spriteSize.height);
    rt->retain();
    
    rt->begin();
    nSprite->visit();
    rt->end();
    
    cocos2d::Image* ccImage = rt->newImage();
    
    NSUInteger bytesPerPixel = 4;
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                              ccImage->getData(),
                                                              ccImage->getDataLen() * bytesPerPixel,
                                                              NULL);
    
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    NSUInteger scanWidth = ccImage->getWidth() * bytesPerPixel;
    CGImageRef imageRef = CGImageCreate(ccImage->getWidth(),
                                        ccImage->getHeight(),
                                        8,
                                        bytesPerPixel * 8,
                                        scanWidth,
                                        colorSpaceRef,
                                        bitmapInfo,
                                        provider,
                                        NULL,
                                        NO,
                                        renderingIntent);
    
    UIImage *image = [UIImage imageWithCGImage:imageRef];
    CGColorSpaceRelease(colorSpaceRef);
    CGImageRelease(imageRef);
    
    UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
    
    return image;
}
                           
                           

@end
