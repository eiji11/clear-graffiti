//
//  Vandal.h
//  Cleaning
//
//  Created by bibi-apple on 28/2/15.
//
//

#ifndef __Cleaning__Vandal__
#define __Cleaning__Vandal__

#include "cocos2d.h"
typedef std::unordered_map<int, int> DamageTypes;

class Vandal : public cocos2d::Ref
{
public:
    static Vandal* create(cocos2d::ValueMap map);
    
    Vandal();
    virtual ~Vandal();
    
    bool init(cocos2d::ValueMap map);
    
    std::string getFrameName()
    {
        return _frameName;
    }
    
    void setFrameName(std::string frameName)
    {
        _frameName = frameName;
    }
    
    cocos2d::Vec2 getPosition()
    {
        return _position;
    }
    
    void setPosition(cocos2d::Vec2 position)
    {
        _position = position;
    }
    
private:
    std::string _frameName;
    cocos2d::Vec2 _position;
    
};

#endif /* defined(__Cleaning__Vandal__) */
