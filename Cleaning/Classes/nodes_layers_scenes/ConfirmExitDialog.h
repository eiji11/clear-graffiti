#ifndef __Cleaning__ConfirmExitDialog__
#define __Cleaning__ConfirmExitDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class ConfirmExitDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(ConfirmExitDialog);
	static ConfirmExitDialog* createFromCCB();

	ConfirmExitDialog();
	virtual ~ConfirmExitDialog();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


private:
	CREATE_HANDLER(onPressConfirm);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::extension::ControlButton *_buttonOk;
	cocos2d::extension::ControlButton *_buttonCancel;

    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);
};

CREATE_CLASS_LOADER(ConfirmExitDialog, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__ConfirmExitDialog__) */
