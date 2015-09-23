//
//  VandalNode.h
//  Cleaning
//
//  Created by bibi-apple on 2/4/15.
//
//

#ifndef __Cleaning__VandalNode__
#define __Cleaning__VandalNode__

#include "cocos2d.h"

#include "Defines.h"

#include "game/Vandal.h"
#include "game/VandalCell.h"

#include <functional>

class VandalNode : public cocos2d::Node
{
public:
    static VandalNode* create(Vandal *vandal);
    VandalNode();
    
    bool init(Vandal *vandal);
    
    virtual void onEnter();
    virtual void onExit();
    
    Vandal *getVandal()
    {
        return _vandal;
    }
    
    bool isCleared();
    
    bool isTouched(cocos2d::Vec2 location);
    bool intersects(cocos2d::Rect cursor);
    
    bool spray(int sprayType, cocos2d::Touch *pTouch, float cursorRadius);
    void brush(int brushType, cocos2d::Touch *pTouch, float cursorRadius);
    
    void highlight();
    void unhighlight();
    
    
protected:
    bool setupSprite(std::string frameName);
    void initCells();
    
    
private:
    
    Vandal *_vandal;
    cocos2d::Sprite *_sprite;
    cocos2d::DrawNode *_stencil;
    cocos2d::ClippingNode *_clipper;
    cocos2d::LayerColor *_highlighter;
    
    std::vector<cocos2d::Vector<VandalCell*>> _cells;
    
};

#endif /* defined(__Cleaning__VandalNode__) */
