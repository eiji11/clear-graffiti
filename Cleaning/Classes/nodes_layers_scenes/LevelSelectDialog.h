#ifndef __Cleaning__LevelSelectDialog__
#define __Cleaning__LevelSelectDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"
#include "managers_caches/UILockManager.h"


class LevelSelectDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(LevelSelectDialog);
	static LevelSelectDialog* createFromCCB();

	LevelSelectDialog();
	virtual ~LevelSelectDialog();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    int getChapter();
    void setChapter(int chapter);


private:
	CREATE_HANDLER(onPressLevel);
	CREATE_HANDLER(onPressClose);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Node *_containerLevel1;
	cocos2d::extension::ControlButton *_buttonLevel1;
	cocos2d::Node *_containerLevel2;
	cocos2d::extension::ControlButton *_buttonLevel2;
	cocos2d::Node *_containerLevel3;
	cocos2d::extension::ControlButton *_buttonLevel3;
	cocos2d::Node *_containerLevel4;
	cocos2d::extension::ControlButton *_buttonLevel4;
	cocos2d::Node *_containerLevel5;
	cocos2d::extension::ControlButton *_buttonLevel5;
	cocos2d::Node *_containerLevel6;
	cocos2d::extension::ControlButton *_buttonLevel6;
	cocos2d::Node *_containerLevel7;
	cocos2d::extension::ControlButton *_buttonLevel7;
	cocos2d::Node *_containerLevel8;
	cocos2d::extension::ControlButton *_buttonLevel8;
	cocos2d::Node *_containerLevel9;
	cocos2d::extension::ControlButton *_buttonLevel9;
	cocos2d::extension::ControlButton *_buttonClose;
    
    int _chapter;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(LevelSelectDialog, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__LevelSelectDialog__) */
