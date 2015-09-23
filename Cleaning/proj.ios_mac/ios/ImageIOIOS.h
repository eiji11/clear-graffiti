//
//  ImageIOIOS.h
//  BaldBalancing
//
//  Created by bibi-apple on 20/6/14.
//
//

#ifndef BaldBalancing_ImageIOIOS_h
#define BaldBalancing_ImageIOIOS_h

#import "protocols/ImageIOProtocol.h"
#import "cocos2d.h"

class ImageIOIOS : public ImageIOProtocol
{
public:
    static ImageIOIOS* getInstance();
    
    virtual cocos2d::Sprite* saveSprite(cocos2d::Sprite* sprite);
    
    virtual cocos2d::Sprite* loadSprite();
    
    virtual bool deleteSprite();
};

#endif
