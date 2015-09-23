#ifndef __Cleaning__ShopDialogEntry__
#define __Cleaning__ShopDialogEntry__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"


class ShopDialogEntry : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(ShopDialogEntry);
	static ShopDialogEntry* createFromCCB();

	ShopDialogEntry();
	virtual ~ShopDialogEntry();

	virtual void onEnter();
	virtual void onExit();

    cocos2d::ValueMap getItemInfo()
    {
        return _itemInfo;
    }
    
    void setItemInfo(cocos2d::ValueMap itemInfo);

private:


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Label *_labelName;
	cocos2d::Label *_labelType;
	cocos2d::Sprite *_containerPrice;
	cocos2d::Label *_labelPrice;
    cocos2d::Sprite *_spriteItem;
    
    cocos2d::ValueMap _itemInfo;

};

CREATE_CLASS_LOADER(ShopDialogEntry, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__ShopDialogEntry__) */
