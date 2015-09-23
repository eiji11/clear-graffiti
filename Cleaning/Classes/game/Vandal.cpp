//
//  Vandal.cpp
//  Cleaning
//
//  Created by bibi-apple on 28/2/15.
//
//

#include "Vandal.h"

#include "Defines.h"

USING_NS_CC;

Vandal *Vandal::create(cocos2d::ValueMap map)
{
    Vandal *retVal = new Vandal();
    if (retVal->init(map)) {
        retVal->autorelease();
        return retVal;
    }
    delete retVal;
    retVal = nullptr;
    return nullptr;
}

Vandal::Vandal() : Ref()
{
    
}

Vandal::~Vandal()
{
    

}

bool Vandal::init(cocos2d::ValueMap map)
{
    _frameName = map.at("frame").asString();
    _position = Vec2(map.at("x").asInt(), (1136 - map.at("y").asInt())) / 2;
    
    return true;
}

