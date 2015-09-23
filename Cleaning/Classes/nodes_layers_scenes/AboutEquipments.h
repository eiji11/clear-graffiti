#ifndef __Cleaning__AboutEquipments__
#define __Cleaning__AboutEquipments__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class AboutEquipments : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(AboutEquipments);
	static AboutEquipments* createFromCCB();

	AboutEquipments();
	virtual ~AboutEquipments();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    CREATE_HANDLER(onPressSprayers);
    CREATE_HANDLER(onPressBrushes);
    CREATE_HANDLER(onPressBack);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
    cocos2d::extension::ControlButton *_buttonSprayers;
    cocos2d::extension::ControlButton *_buttonBrushes;
    cocos2d::extension::ControlButton *_buttonBack;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);

};

CREATE_CLASS_LOADER(AboutEquipments, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__AboutEquipments__) */
