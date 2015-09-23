#ifndef __Cleaning__ShopDialog__
#define __Cleaning__ShopDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "game/Game.h"
#include "managers_caches/UILockManager.h"


class ShopDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
, public cocos2d::extension::TableViewDataSource
, public cocos2d::extension::TableViewDelegate
{
public:
	CREATE_FUNC(ShopDialog);
	static ShopDialog* createFromCCB();

	ShopDialog();
	virtual ~ShopDialog();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void setGame(Game *game);
    void setType(int type);
    void setIndex(int index);

    
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    
    virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);

    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);

    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
private:
	CREATE_HANDLER(onPressBack);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);

    void loadItems();

private:
	cocos2d::Label *_labelMoney;
	cocos2d::Node *_containerTableView;
	cocos2d::extension::ControlButton *_buttonBack;
    
    cocos2d::extension::TableView *_tableView;
    
    Game *_game;
    int _type;
    int _index;
    cocos2d::ValueVector _items;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(4);

};

CREATE_CLASS_LOADER(ShopDialog, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__ShopDialog__) */
