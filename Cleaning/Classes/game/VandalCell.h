//
//  VandalCell.h
//  Cleaning
//
//  Created by bibi-apple on 3/4/15.
//
//

#ifndef __Cleaning__VandalCell__
#define __Cleaning__VandalCell__

#include "cocos2d.h"

#include "Vandal.h"


class VandalCell : public cocos2d::Ref
{
public:
    static VandalCell* create(cocos2d::Vec2 center, Vandal *vandal);
    bool init(cocos2d::Vec2 center, Vandal *vandal);
    
    void setVandal(Vandal * vandal);
    
    cocos2d::Vec2 getCenter()
    {
        return _center;
    }
    
    bool isCleared()
    {
        return _isCleared;
    }
    
    void setCleared(bool cleared)
    {
        _isCleared = cleared;
    }
    
    bool isCharged()
    {
        return _isCharged;
    }
    
    void setCharged(bool charged)
    {
        _isCharged = charged;
    }
    
    void spray(int sprayType);
    void brush(int brushType);
    
    void setBubble(cocos2d::Sprite *bubble);
    void releaseBubble();
    
private:
    Vandal *_vandal;
    cocos2d::Vec2 _center;
    
    bool _isCleared;
    bool _isCharged;
    
    cocos2d::Sprite *_bubble;
    
    cocos2d::Vector<cocos2d::Sprite*> _bubbles;
};

#endif /* defined(__Cleaning__VandalCell__) */
