#ifndef __WaterQuiz__AlertBox__
#define __WaterQuiz__AlertBox__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class AlertBox : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(AlertBox);
	static AlertBox* createFromCCB();

	AlertBox();
	virtual ~AlertBox();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void setUILockContext(std::string context)
    {
        VAR_LOCK_CONTEXT = context;
    }
    
    std::string getUILockContext()
    {
        return VAR_LOCK_CONTEXT;
    }
    
//    void setMessageText(std::string text);
//
//    void setButtonText(std::string text);

private:
	CREATE_HANDLER(onPressOkay);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
//	cocos2d::LayerColor *_containerMain;
//	cocos2d::Label *_labelMessage;
	cocos2d::extension::ControlButton *_buttonOkay;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);

};

CREATE_CLASS_LOADER(AlertBox, spritebuilder::LayerLoader);


#endif /* defined(__WaterQuiz__AlertBox__) */
