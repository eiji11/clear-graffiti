#ifndef __Cleaning__AboutMenu__
#define __Cleaning__AboutMenu__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class AboutMenu : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(AboutMenu);
	static AboutMenu* createFromCCB();

	AboutMenu();
	virtual ~AboutMenu();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    CREATE_HANDLER(onPressAbout);
    CREATE_HANDLER(onPressCredits);
    CREATE_HANDLER(onPressBack);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
    cocos2d::extension::ControlButton *_buttonAbout;
    cocos2d::extension::ControlButton *_buttonCredits;
    cocos2d::extension::ControlButton *_buttonBack;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);

};

CREATE_CLASS_LOADER(AboutMenu, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__AboutMenu__) */
