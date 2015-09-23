#include "ShopDialog.h"

#include "ShopDialogEntry.h"

#include "managers_caches/EventCustomMapped.h"
#include "game/Player.h"

#include "utils/GeneralUtils.h"


USE_NS


ShopDialog *ShopDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("ShopDialog", ShopDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<ShopDialog*>(ccbReader->readNodeGraphFromFile("ShopDialog.ccbi"));
}

ShopDialog::ShopDialog() : cocos2d::Layer()
, _labelMoney(NULL)
, _containerTableView(NULL)
, _buttonBack(NULL)
, _game(NULL)
, _type(0)
, _index(-1)
{

}

ShopDialog::~ShopDialog()
{
	CC_SAFE_RELEASE(_labelMoney);
	CC_SAFE_RELEASE(_containerTableView);
	CC_SAFE_RELEASE(_buttonBack);
}

void ShopDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    this->loadItems();
    
    UI_LOCK_MANAGER_INCREASE();
}

void ShopDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();
}

void ShopDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void ShopDialog::setGame(Game *game)
{
    _game = game;
    _game->retain();
    
    _labelMoney->setString(StringUtils::format("%d", _game->getMoney()));
}

void ShopDialog::setType(int type)
{
    _type = type;
}

void ShopDialog::setIndex(int index)
{
    _index = index;
}

void ShopDialog::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        this->removeFromParent();
	}
}

void ShopDialog::loadItems()
{
    ValueMap equipments = FileUtils::getInstance()->getValueMapFromFile("equipments-info.plist");
    
    if (_type == 1)
    {
        ValueVector sprays = equipments.at("sprays").asValueVector();
        ValueVector currentSprays = _game->getSprays();
        
        std::vector<int> sprayIds;
        for (int x = 0; x < currentSprays.size(); x++) {
            sprayIds.push_back(currentSprays[x].asValueMap().at("type").asInt());
        }
        
        
        for (int x = sprays.size() - 1; x >= 0; x--) {
            ValueMap spray = sprays.at(x).asValueMap();
            int id = x + 1;
            spray["id"] = id;
            spray["type"] = 1;
            
            bool found = false;
            for (auto sprayId : sprayIds) {
                if (id == sprayId)
                {
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                _items.push_back(Value(spray));
            }
        }
    }
    else if (_type == 2)
    {
        ValueVector brushes = equipments.at("brushes").asValueVector();
        ValueVector currentBrushes = _game->getBrushes();
        
        std::vector<int> brushIds;
        for (int x = 0; x < currentBrushes.size(); x++) {
            brushIds.push_back(currentBrushes[x].asValueMap().at("type").asInt());
        }
        
        for (int x = brushes.size() - 1; x >= 0; x--) {
            ValueMap brush = brushes.at(x).asValueMap();
            int id = x + 1;
            brush["id"] = id;
            brush["type"] = 2;
            
            bool found = false;
            for (auto brushId : brushIds) {
                if (id == brushId)
                {
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                _items.push_back(Value(brush));
            }
        }
    }
    else
    {
        ValueVector sprays = equipments.at("sprays").asValueVector();
        ValueVector brushes = equipments.at("brushes").asValueVector();

        for (int x = sprays.size() - 1; x >= 0; x--) {
            ValueMap spray = sprays.at(x).asValueMap();
            int id = x + 1;
            spray["id"] = id;
            spray["type"] = 1;

			_items.push_back(Value(spray));
        }

        for (int x = brushes.size() - 1; x >= 0; x--) {
            ValueMap brush = brushes.at(x).asValueMap();
            int id = x + 1;
            brush["id"] = id;
            brush["type"] = 2;

			_items.push_back(Value(brush));
        }
    }
    
    _tableView->reloadData();
    
}


#pragma mark - TableView Methods

void ShopDialog::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
	if (_game == nullptr)
	{
		return;
	}

    auto item = _items[cell->getIdx()].asValueMap();
    
    if (!item.empty())
    {
        ValueMap itemInfo = item;
        itemInfo["index"] = _index;
        
        EventCustomMapped *event = new EventCustomMapped(EVENT_ITEM_SELECTED);
        event->setInfo(itemInfo);
        
        Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
        
        this->runAction(CallFunc::create([&](){
            this->removeFromParent();
        }));
    }
}

Size ShopDialog::cellSizeForTable(cocos2d::extension::TableView *table)
{
    static cocos2d::Size CELL_SIZE(242, 92);
    
    return CELL_SIZE;
}

TableViewCell *ShopDialog::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = TableViewCell::create();
    
    ShopDialogEntry *entry = ShopDialogEntry::createFromCCB();
    entry->setItemInfo(_items[idx].asValueMap());
    
    cell->addChild(entry);
    
    return cell;
}

ssize_t ShopDialog::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return _items.size();
}


#pragma mark - CCBMemberVariableAssigner functions

bool ShopDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelMoney", cocos2d::Label*, _labelMoney);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerTableView", cocos2d::Node*, _containerTableView);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler ShopDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", ShopDialog::onPressBack);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void ShopDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    _tableView = TableView::create(this, _containerTableView->getContentSize());
    _tableView->setDelegate(this);
    
    _containerTableView->addChild(_tableView);

    _labelMoney->setString(StringUtils::format("%d", Player::getInstance()->getMoney()));
}


#pragma mark - CCBAnimationManagerDelegate functions

void ShopDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


