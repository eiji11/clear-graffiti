/*
 * ImageIOAndroid.cpp
 *
 *  Created on: 13 Jul, 2014
 *      Author: mac-user1
 */

#include "ImageIOAndroid.h"
#include <stdio.h>

USING_NS_CC;

ImageIOProtocol* ImageIOProtocol::getInstance()
{
	return ImageIOAndroid::getInstance();
}

ImageIOAndroid::~ImageIOAndroid()
{
}

ImageIOAndroid* ImageIOAndroid::getInstance()
{
	static ImageIOAndroid* instance;

	if (instance == nullptr)
	{
		instance = new ImageIOAndroid();
	}

	return instance;
}

Sprite* ImageIOAndroid::saveSprite(cocos2d::Sprite* sprite)
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

Sprite* ImageIOAndroid::loadSprite()
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

bool ImageIOAndroid::deleteSprite()
{
    std::string fullpath = FileUtils::getInstance()->getWritablePath() + IMAGE_FILENAME;

    bool hasImage = FileUtils::getInstance()->isFileExist(fullpath);

    if (hasImage)
    {
    	bool success = remove(fullpath.c_str());
        return success;
    }
    else
    {
        return false;
    }
}
