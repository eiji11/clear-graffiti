#ifndef __Cleaning__MainMenu__
#define __Cleaning__MainMenu__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class MainMenu : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(MainMenu);
	static MainMenu* createFromCCB();

	MainMenu();
	virtual ~MainMenu();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


private:
    CREATE_HANDLER(onPressStart);
    CREATE_HANDLER(onPressSettings);
    CREATE_HANDLER(onPressShop);
    CREATE_HANDLER(onPressAbout);
    CREATE_HANDLER(onPressRank);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Node *_containerMain;
    cocos2d::Label *_labelHelloThere;
    cocos2d::Label *_labelName;
    cocos2d::extension::ControlButton *_buttonStart;
    cocos2d::extension::ControlButton *_buttonSettings;
    cocos2d::extension::ControlButton *_buttonShop;
    cocos2d::extension::ControlButton *_buttonAbout;
    cocos2d::extension::ControlButton *_buttonRank;

    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);
};

CREATE_CLASS_LOADER(MainMenu, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__MainMenu__) */
