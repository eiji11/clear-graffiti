#ifndef __Cleaning__PreGame__
#define __Cleaning__PreGame__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "game/Game.h"
#include "managers_caches/UILockManager.h"


class PreGame : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PreGame);
	static PreGame* createFromCCB();

	PreGame();
	virtual ~PreGame();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    Game *getGame()
    {
        return _game;
    }
    
    void setGame(Game *game);


private:
	CREATE_HANDLER(onPressSpray);
    CREATE_HANDLER(onPressBrush);
    CREATE_HANDLER(onPressPlay);
    CREATE_HANDLER(onPressClose);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Sprite *_sprayContainer1;
	cocos2d::extension::ControlButton *_buttonSpray1;
	cocos2d::Sprite *_sprayImage1;
	cocos2d::Sprite *_sprayContainer2;
	cocos2d::extension::ControlButton *_buttonSpray2;
	cocos2d::Sprite *_sprayImage2;
	cocos2d::Sprite *_sprayContainer3;
	cocos2d::extension::ControlButton *_buttonSpray3;
	cocos2d::Sprite *_sprayImage3;
	cocos2d::Sprite *_brushContainer1;
	cocos2d::extension::ControlButton *_buttonBrush1;
	cocos2d::Sprite *_brushImage1;
	cocos2d::Sprite *_brushContainer2;
	cocos2d::extension::ControlButton *_buttonBrush2;
	cocos2d::Sprite *_brushImage2;
	cocos2d::Sprite *_brushContainer3;
	cocos2d::extension::ControlButton *_buttonBrush3;
	cocos2d::Sprite *_brushImage3;
	cocos2d::Sprite *_containerMoney;
    cocos2d::Label *_labelMoney;
    cocos2d::extension::ControlButton *_buttonPlay;
    cocos2d::extension::ControlButton *_buttonClose;
    
    Game *_game;

    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(3);
};

CREATE_CLASS_LOADER(PreGame, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__PreGame__) */
