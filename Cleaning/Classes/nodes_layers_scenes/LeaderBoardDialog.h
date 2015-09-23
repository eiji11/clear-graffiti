#ifndef __Cleaning__LeaderBoardDialog__
#define __Cleaning__LeaderBoardDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"
#include "managers_caches/UILockManager.h"


class LeaderBoardDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
, public cocos2d::extension::TableViewDataSource
{
public:
	CREATE_FUNC(LeaderBoardDialog);
	static LeaderBoardDialog* createFromCCB();

	LeaderBoardDialog();
	virtual ~LeaderBoardDialog();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
    
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    void loadItems();
    void loadSavedItems();
    
private:
	CREATE_HANDLER(onPressBack);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Node *_containerTableView;
	cocos2d::extension::ControlButton *_buttonBack;
    
    cocos2d::extension::TableView *_tableView;
    
    cocos2d::ValueVector _items;

    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(LeaderBoardDialog, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__LeaderBoardDialog__) */
