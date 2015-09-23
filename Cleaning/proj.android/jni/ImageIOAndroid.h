/*
 * ImageIOAndroid.h
 *
 *  Created on: 13 Jul, 2014
 *      Author: mac-user1
 */

#ifndef IMAGEIOANDROID_H_
#define IMAGEIOANDROID_H_

#include "protocols/ImageIOProtocol.h"
#include "cocos2d.h"

class ImageIOAndroid : public ImageIOProtocol {
public:
	virtual ~ImageIOAndroid();

    static ImageIOAndroid* getInstance();

    virtual cocos2d::Sprite* saveSprite(cocos2d::Sprite* sprite);

    virtual cocos2d::Sprite* loadSprite();

    virtual bool deleteSprite();

};

#endif /* IMAGEIOANDROID_H_ */
