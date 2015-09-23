//
//  ImageIOIOS.mm
//  BaldBalancing
//
//  Created by bibi-apple on 20/6/14.
//
//

#import <UIKit/UIKit.h>
#import "ImageIOIOS.h"
#import "UIUtils.h"

USING_NS_CC;

ImageIOProtocol* ImageIOProtocol::getInstance()
{
    return ImageIOIOS::getInstance();
}

ImageIOIOS* ImageIOIOS::getInstance()
{
    static ImageIOIOS* instance;
    if (instance == NULL)
    {
        instance = new ImageIOIOS();
    }
    return instance;
}

Sprite* ImageIOIOS::saveSprite(cocos2d::Sprite *sprite)
{
    cocos2d::Size spriteSize = sprite->getContentSize();
    Sprite *nSprite = Sprite::createWithTexture(sprite->getTexture());
    nSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    nSprite->setPosition(Vec2::ZERO);
    
//    nSprite->setFlippedY(true);
    
    RenderTexture* rt = RenderTexture::create(spriteSize.width, spriteSize.height);
    rt->retain();
    
    rt->beginWithClear(0, 0, 0, 0);
    nSprite->visit();
    rt->end();
    
    bool success = rt->saveToFile(IMAGE_FILENAME, Image::Format::PNG, false);

    
    if (success)
    {
        return rt->getSprite();
    }
    else
    {
        return NULL;
    }
}

Sprite* ImageIOIOS::loadSprite()
{
    
    std::string fullpath = FileUtils::getInstance()->getWritablePath() + IMAGE_FILENAME;
    
    bool hasImage = FileUtils::getInstance()->isFileExist(fullpath);
    if (hasImage)
    {
        Image* image = new Image();
        image->initWithImageFile(fullpath);
        Texture2D *texture = new Texture2D();
        texture->initWithImage(image);
        Sprite *sprite = Sprite::createWithTexture(texture);
        return sprite;
    }
    else
    {
        return NULL;
    }
}

bool ImageIOIOS::deleteSprite()
{
    std::string fullpath = FileUtils::getInstance()->getWritablePath() + IMAGE_FILENAME;
    
    bool hasImage = FileUtils::getInstance()->isFileExist(fullpath);
    
    if (hasImage)
    {
        id fileManager = [NSFileManager defaultManager];
        NSString *filePath = [NSString stringWithCString:fullpath.c_str() encoding:NSUTF8StringEncoding];
        NSError *error = nil;
        
        BOOL success = [fileManager removeItemAtPath:filePath error:&error];
        
        if (error != nil || !success)
        {
            NSLog(@"ERROR: %@", error);
        }
        return success;
    }
    else
    {
        return false;
    }
    
}