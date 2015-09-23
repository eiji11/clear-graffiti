#ifndef __Cleaning__PauseDialog__
#define __Cleaning__PauseDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "ui/CocosGUI.h"

#include "Defines.h"

#include "game/Game.h"
#include "managers_caches/UILockManager.h"


class PauseDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PauseDialog);
	static PauseDialog* createFromCCB();

	PauseDialog();
	virtual ~PauseDialog();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void setGame(Game *game);


private:
	CREATE_HANDLER(onPressMusic);
	CREATE_HANDLER(onPressSound);
	CREATE_HANDLER(onPressOk);
	CREATE_HANDLER(onPressHome);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
    cocos2d::Label *_labelTime;
    cocos2d::LayerColor *_containerName;
	cocos2d::Node *_containerMusic;
	cocos2d::extension::ControlButton *_buttonMusic;
	cocos2d::Sprite *_checkBoxMusic;
	cocos2d::Node *_containerSounds;
	cocos2d::extension::ControlButton *_buttonSounds;
	cocos2d::Sprite *_checkBoxSound;
	cocos2d::extension::ControlButton *_buttonOk;
    
    Game *_game;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
};

CREATE_CLASS_LOADER(PauseDialog, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__PauseDialog__) */
