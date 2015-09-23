//
//  VandalCell.cpp
//  Cleaning
//
//  Created by bibi-apple on 3/4/15.
//
//

#include "VandalCell.h"

#include "Defines.h"


USING_NS_CC;


VandalCell* VandalCell::create(cocos2d::Vec2 center, Vandal *vandal)
{
    VandalCell *retVal = new VandalCell();
    if (retVal->init(center, vandal))
    {
        retVal->autorelease();
        return retVal;
    }
    
    delete retVal;
    retVal = nullptr;
    return nullptr;
}

bool VandalCell::init(cocos2d::Vec2 center, Vandal *vandal)
{
    setVandal(vandal);
    _center = center;
    
    return true;
}

void VandalCell::setVandal(Vandal *vandal)
{
    _vandal = vandal;
    _vandal->retain();
    
    _isCleared = false;
    _isCharged = false;
}

void VandalCell::spray(int sprayType)
{
    
    if (!_isCharged)
    {
        _isCharged = true;
    }
}

void VandalCell::brush(int brushType)
{
    if (_isCharged && !_isCleared)
    {
        _isCleared = true;
        
        releaseBubble();
    }
}

void VandalCell::setBubble(cocos2d::Sprite *bubble)
{
    _bubble = bubble;
    _bubble->retain();
}

void VandalCell::releaseBubble()
{
    if (_bubble !=  nullptr)
    {
        _bubble->removeFromParent();
        
        _bubble = nullptr;
    }
}

