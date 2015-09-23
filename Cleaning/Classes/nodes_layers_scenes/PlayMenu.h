#ifndef __Cleaning__PlayMenu__
#define __Cleaning__PlayMenu__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class PlayMenu : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PlayMenu);
	static PlayMenu* createFromCCB();

	PlayMenu();
	virtual ~PlayMenu();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


private:
	CREATE_HANDLER(onPressStoryMode);
    CREATE_HANDLER(onPressTimeAttack);
    CREATE_HANDLER(onPressHowToPlay);
    CREATE_HANDLER(onPressEquipments);
    CREATE_HANDLER(onPressBack);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::extension::ControlButton *_buttonStoryMode;
    cocos2d::extension::ControlButton *_buttonTimeAttack;
    cocos2d::extension::ControlButton *_buttonHowToPlay;
    cocos2d::extension::ControlButton *_buttonEquipments;
    cocos2d::extension::ControlButton *_buttonBack;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);

};

CREATE_CLASS_LOADER(PlayMenu, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__PlayMenu__) */
