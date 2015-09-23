#ifndef __Cleaning__InGameItemSelectorDialog__
#define __Cleaning__InGameItemSelectorDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"
#include "managers_caches/UILockManager.h"


class InGameItemSelectorDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(InGameItemSelectorDialog);
	static InGameItemSelectorDialog* createFromCCB();

	InGameItemSelectorDialog();
	virtual ~InGameItemSelectorDialog();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void setType(int type, cocos2d::ValueVector items);
    void highlightItem();


private:
	CREATE_HANDLER(onPressItemSelect);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Node *_holder1;
	cocos2d::extension::ControlButton *_buttonSelect1;
	cocos2d::Sprite *_hand;
	cocos2d::Sprite *_item1;
	cocos2d::Node *_holder2;
	cocos2d::extension::ControlButton *_buttonSelect2;
	cocos2d::Sprite *_item2;
	cocos2d::Node *_holder3;
	cocos2d::extension::ControlButton *_buttonSelect3;
	cocos2d::Sprite *_item3;
    
    cocos2d::ValueVector _items;
    int _type;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(InGameItemSelectorDialog, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__InGameItemSelectorDialog__) */
