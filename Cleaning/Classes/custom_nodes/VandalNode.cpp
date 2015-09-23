//
//  VandalNode.cpp
//  Cleaning
//
//  Created by bibi-apple on 2/4/15.
//
//

#include "VandalNode.h"

#include "managers_caches/ObserverManager.h"

USING_NS_CC;

VandalNode *VandalNode::create(Vandal *vandal)
{
    VandalNode *retVal = new VandalNode();
    if (retVal->init(vandal))
    {
        retVal->autorelease();
        return retVal;
    }
    
    delete retVal;
    retVal = nullptr;
    return nullptr;
}

VandalNode::VandalNode() : Node()
, _vandal(nullptr)
, _sprite(nullptr)
, _clipper(nullptr)
{
}

bool VandalNode::init(Vandal *vandal)
{
    if (Node::init())
    {
        do
        {
            _vandal = vandal;
            this->setPosition(_vandal->getPosition());
            CC_BREAK_IF(!setupSprite(_vandal->getFrameName()));
            initCells();
            
            return true;
        } while(false);
    }
    return false;
}

void VandalNode::onEnter()
{
    Node::onEnter();
    
    OBSERVE(this, EVENT_BEGIN_BRUSHING, [&](EventCustom *event){
    });
    
    OBSERVE(this, EVENT_END_BRUSHING, [&](EventCustom *event){
    });
}

void VandalNode::onExit()
{
    Node::onExit();
    
    UNOBSERVE(this);
}

bool VandalNode::setupSprite(std::string frameName)
{
    
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
    if (frame != nullptr)
    {
        _sprite = Sprite::createWithSpriteFrame(frame);
        _sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        Size spriteSize = _sprite->getContentSize();
        Vec2 center = Vec2(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
        
        _sprite->setPosition(center);
        
        this->setContentSize(spriteSize);
        this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        
        _stencil = DrawNode::create();
        _stencil->setPosition(center);
        _stencil->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _stencil->setContentSize(_sprite->getContentSize());
        
        _stencil->retain();
        
        _clipper = ClippingNode::create(_stencil);
        _clipper->setContentSize(spriteSize);
        _clipper->setPosition(center);
        _clipper->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _clipper->setAlphaThreshold(1.f);
        _clipper->setInverted(true);
        
        _clipper->addChild(_sprite);
        
        this->addChild(_clipper, 2);
        
        return true;
    }
    return false;
}

void VandalNode::initCells()
{
    Size spriteSize = _sprite->getContentSize();
    Vec2 nCenter = Vec2(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
    RenderTexture *rt = RenderTexture::create(spriteSize.width, spriteSize.height, Texture2D::PixelFormat::RGBA8888);
    
    Sprite *spriter = Sprite::createWithSpriteFrame(_sprite->getSpriteFrame());
//    spriter->setScale(Director::getInstance()->getContentScaleFactor());
    spriter->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    
    rt->beginWithClear(1.f, 1.f, 1.f, 0.f);
    
    spriter->visit();
    
    
    rt->end();
    
    
    std::string filename = StringUtils::format("%03d-%03d.png", (int)nCenter.x, (int)nCenter.y);
    rt->saveToFile(filename);
    
    
    this->runAction(CallFunc::create([&, spriteSize, filename](){
        CCLOG("SETTING UP: %s", _vandal->getFrameName().c_str());
        Image *rawImage = new Image();
        rawImage->initWithImageFile(FileUtils::getInstance()->getWritablePath() + filename);
        
        ssize_t dataLength = rawImage->getDataLen();
        
        unsigned char *data = new unsigned char[dataLength * 4];
        data = rawImage->getData();
        
        int rows = roundf(spriteSize.height / (BRUSH_RADIUS * 2));
        int columns = roundf(spriteSize.width / (BRUSH_RADIUS * 2));
        
        int cellHeight = spriteSize.height / rows;
        int cellWidth = spriteSize.width / columns;
        
        
        int totalRed = 0;
        int totalGreen = 0;
        int totalBlue = 0;
        
        float divider = 0.f;
        
        for (int row = 0; row < rows; row++) {
            Vector<VandalCell*>cellsInRow;
            for (int column = 0; column < columns; column++)
            {
                Vec2 center;
                center.x = cellWidth * (column + 0.5f);
                center.y = cellHeight * (row + 0.5f);
                
                
                bool hasAlpha = false;
                
                int yStart = center.y - (cellHeight * 0.2f);
                int yEnd = center.y + (cellHeight * 0.2f);
                int xStart = center.x - (cellWidth * 0.2f);
                int xEnd = center.x + (cellWidth * 0.2f);
                
                
                for (int y = yStart; y <= yEnd; y++)
                {
                    for (int x = xStart; x <= xEnd; x++)
                    {
                        int ny = spriteSize.height - y;
                        int index = ((x + (ny * (int)spriteSize.width * Director::getInstance()->getContentScaleFactor())) * 4) * Director::getInstance()->getContentScaleFactor();
                        unsigned char *pixel = data + index;
                        
                        unsigned char red = *(pixel);
                        unsigned char green = *(pixel + 1);
                        unsigned char blue = *(pixel + 2);
                        unsigned char alpha = *(pixel + 3);
                        
                        
                        if (alpha > 0)
                        {
                            totalRed += red;
                            totalGreen += green;
                            totalBlue += blue;
                            
                            divider++;
                        }
                        
                        if (!hasAlpha)
                        {
                            hasAlpha = alpha != 0;
                        }
                    }
                }
                
                VandalCell *cell = VandalCell::create(center, _vandal);
                cellsInRow.pushBack(cell);
                
                CCLOG("CENTER: %d, %d : %i", row, column, hasAlpha);
                
                cell->setCleared(!hasAlpha);
            }
            _cells.push_back(cellsInRow);
        }
        
        Color4B hColor((int)(totalRed / divider),
                        (int)(totalGreen / divider),
                        (int)(totalBlue / divider),
                        255);
        
        _highlighter = LayerColor::create(hColor);
        _highlighter->setContentSize(spriteSize);
        _highlighter->setOpacity(0);
        this->addChild(_highlighter, -1);
        
        if (this->isCleared())
        {
            EventCustom *event = new EventCustom(EVENT_VANDAL_FORCED_REMOVED);
            event->setUserData(this);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
        }
        
    }));
}

bool VandalNode::isCleared()
{
    for (int row = 0; row < _cells.size(); row++)
    {
        Vector<VandalCell *> cellsInRow = _cells.at(row);
        for (int column = 0; column < cellsInRow.size(); column++) {
            VandalCell *cell = cellsInRow.at(column);
            if (!cell->isCleared()) {
                return false;
            }
        }
    }
    return true;
}

bool VandalNode::isTouched(cocos2d::Vec2 location)
{
    bool retVal = false;
    try
    {
        Rect box = this->getBoundingBox();
        
        retVal = box.containsPoint(location);
    }
    catch (const std::exception &e)
    {
        
    }
    
    return retVal;
}

bool VandalNode::intersects(cocos2d::Rect cursor)
{
    bool retVal = false;
    try
    {
        Rect box = this->getBoundingBox();
        
        retVal = box.intersectsRect(cursor);
    }
    catch (const std::exception &e)
    {
        
    }
    
    return retVal;
}

bool VandalNode::spray(int sprayType,  cocos2d::Touch *pTouch, float cursorRadius)
{
    Vec2 start = this->convertToNodeSpace(pTouch->getLocation());
    Vec2 end = this->convertToNodeSpace(pTouch->getPreviousLocation());
    
    float distance = start.distance(end);
    
    float diffX = end.x - start.x;
    float diffY = end.y - start.y;
    
    bool sprayed = false;
    
    for (float i = 0; i <= distance; i += (BRUSH_RADIUS))
    {
        float delta = i / distance;
        Vec2 position(start.x + (diffX * delta), start.y + (diffY * delta));
        
        for (int row = 0; row < _cells.size(); row++)
        {
            Vector<VandalCell *> cellsInRow = _cells.at(row);
            for (int column = 0; column < cellsInRow.size(); column++) {
                VandalCell *cell = cellsInRow.at(column);
                
                Vec2 center = cell->getCenter();
                
                if (position.distance(center) <= (BRUSH_RADIUS + cursorRadius))
                {
                    if (!cell->isCharged() && !cell->isCleared())
                    {
                        sprayed = true;
                        cell->spray(sprayType);
                    
                        std::string bubble;
                        Size contentSize = this->getContentSize();
                        
                        std::string bubbles[] = {"bubbles/0.png", "bubbles/1.png", "bubbles/2.png"};
                        
                        bubble = bubbles[((int)(CCRANDOM_0_1() * 3))];
                        
                        Sprite *bubbleSprite = Sprite::createWithSpriteFrameName(bubble);
                        bubbleSprite->setPosition(center);
                        bubbleSprite->setGlobalZOrder(1);
                        
                        this->addChild(bubbleSprite, 1);
                        cell->setBubble(bubbleSprite);
                    }
                    else if (cell->isCharged() && cell->isCleared())
                    {
                        return false;
                    }
                }
            }
        }
    }
    
    return sprayed;
}

void VandalNode::brush(int brushType, cocos2d::Touch *pTouch, float cursorRadius)
{
    Vec2 start = this->convertToNodeSpace(pTouch->getLocation());
    Vec2 end = this->convertToNodeSpace(pTouch->getPreviousLocation());
    
    float distance = start.distance(end);
    
    float diffX = end.x - start.x;
    float diffY = end.y - start.y;
    
    
    for (float i = 0; i <= distance; i += (BRUSH_RADIUS))
    {
        float delta = i / distance;
        Vec2 position(start.x + (diffX * delta), start.y + (diffY * delta));
        
        for (int row = 0; row < _cells.size(); row++)
        {
            Vector<VandalCell *> cellsInRow = _cells.at(row);
            for (int column = 0; column < cellsInRow.size(); column++) {
                VandalCell *cell = cellsInRow.at(column);
                
                Vec2 center = cell->getCenter();
                
                if (position.distance(center) <= (BRUSH_RADIUS + cursorRadius))
                {
                    if (cell->isCharged())
                    {
                        _stencil->drawDot(position, cursorRadius, Color4F(1.f, 1.f, 1.f, 1.f));
                        cell->brush(brushType);
                    }
                }
            }
        }
    }
}

void VandalNode::highlight()
{
    _highlighter->stopAllActions();
    _highlighter->runAction(Sequence::create(ScaleTo::create(1.f, 1.25f), DelayTime::create(1.f), ScaleTo::create(1.f, 1.f), NULL));
    _highlighter->runAction(Sequence::create(FadeTo::create(1.f, 96), DelayTime::create(1.f), FadeTo::create(1.f, 0), CallFuncN::create([&](Node *n){
        n->setOpacity(0);
    }), NULL));
}

void VandalNode::unhighlight()
{
    _highlighter->stopAllActions();
    _highlighter->runAction(Sequence::create(ScaleTo::create(1.f, 1.f), NULL));
    _highlighter->runAction(Sequence::create(FadeTo::create(1.f, 0), CallFuncN::create([&](Node *n){
        n->setOpacity(0);
    }), NULL));
}
