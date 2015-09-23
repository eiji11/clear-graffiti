#ifndef __Cleaning__PostGame__
#define __Cleaning__PostGame__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"

#include "game/Game.h"


class PostGame : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PostGame);
	static PostGame* createFromCCB();

	PostGame();
	virtual ~PostGame();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void setGame(Game *game);
    Game *getGame(){
        return _game;
    }
    
    void setFailed(bool failed);
    bool isFailed()
    {
        return _failed;
    }


private:
	CREATE_HANDLER(onPressHome);
	CREATE_HANDLER(onPressPlay);
	CREATE_HANDLER(onPressReplay);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Sprite *_star1;
	cocos2d::Sprite *_star2;
	cocos2d::Sprite *_star3;
    cocos2d::Sprite *_title;
    cocos2d::Node *_containerRemarks;
	cocos2d::Label *_labelTime;
	cocos2d::Label *_labelScore;
	cocos2d::Label *_labelMoney;
	cocos2d::Sprite *_titleLevelUp;
	cocos2d::extension::ControlButton *_buttonHome;
	cocos2d::extension::ControlButton *_buttonPlay;
	cocos2d::extension::ControlButton *_buttonReplay;

    Game *_game;
    bool _failed;
    
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);
};

CREATE_CLASS_LOADER(PostGame, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__PostGame__) */
