//
//  ImageIOProtocol.h
//  BaldBalancing
//
//  Created by bibi-apple on 20/6/14.
//
//

#ifndef BaldBalancing_ImageIOProtocol_h
#define BaldBalancing_ImageIOProtocol_h

#define IMAGE_FILENAME "waterquiz_profile_pic.png"

#include "cocos2d.h"

class ImageIOProtocol
{
public:
	virtual ~ImageIOProtocol(){}
    static ImageIOProtocol* getInstance();
    
    virtual cocos2d::Sprite *saveSprite(cocos2d::Sprite* sprite) = 0;
    
    virtual cocos2d::Sprite* loadSprite() = 0;
    
    virtual bool deleteSprite() = 0;
};

#endif
