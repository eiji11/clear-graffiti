#include "InGameItemSelectorDialog.h"

#include "managers_caches/EventCustomMapped.h"


USE_NS

InGameItemSelectorDialog *InGameItemSelectorDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("InGameItemSelectorDialog", InGameItemSelectorDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<InGameItemSelectorDialog*>(ccbReader->readNodeGraphFromFile("InGameItemSelectorDialog.ccbi"));
}

InGameItemSelectorDialog::InGameItemSelectorDialog() : cocos2d::Layer()
, _holder1(NULL)
, _hand(NULL)
, _buttonSelect1(NULL)
, _item1(NULL)
, _holder2(NULL)
, _buttonSelect2(NULL)
, _item2(NULL)
, _holder3(NULL)
, _buttonSelect3(NULL)
, _item3(NULL)
{

}

InGameItemSelectorDialog::~InGameItemSelectorDialog()
{
	CC_SAFE_RELEASE(_holder1);
	CC_SAFE_RELEASE(_buttonSelect1);
	CC_SAFE_RELEASE(_hand);
	CC_SAFE_RELEASE(_item1);
	CC_SAFE_RELEASE(_holder2);
	CC_SAFE_RELEASE(_buttonSelect2);
	CC_SAFE_RELEASE(_item2);
	CC_SAFE_RELEASE(_holder3);
	CC_SAFE_RELEASE(_buttonSelect3);
	CC_SAFE_RELEASE(_item3);
}

void InGameItemSelectorDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER->changeLockLevel(_uiContext, 1);
    
}

void InGameItemSelectorDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER->changeLockLevel(_uiContext, -1);

}

void InGameItemSelectorDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressItemSelect(nullptr, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void InGameItemSelectorDialog::setType(int type, cocos2d::ValueVector items)
{
    _type = type;

    _items = items;
    
    Sprite *sItems[] = {_item1, _item2, _item3};
    if (_type == TOUCH_SPRAY)
    {
        for (int x = 0; x < _items.size(); x++)
        {
            ValueMap itemMap = _items[x].asValueMap();
            sItems[x]->setVisible(itemMap.at("type").asInt() != 0);
            if (itemMap.at("type").asInt() != 0) {
                sItems[x]->setSpriteFrame(StringUtils::format("equipments/spray-%d.png", itemMap.at("type").asInt()));
            }
        }
    }
    else if (_type == TOUCH_BRUSH)
    {
        for (int x = 0; x < _items.size(); x++)
        {
            ValueMap itemMap = _items[x].asValueMap();
            sItems[x]->setVisible(itemMap.at("type").asInt() != 0);
            if (itemMap.at("type").asInt() != 0) {
                sItems[x]->setSpriteFrame(StringUtils::format("equipments/brush-%d.png", itemMap.at("type").asInt()));
            }
        }
    }
}

void InGameItemSelectorDialog::highlightItem()
{
	_hand->setVisible(true);
}

void InGameItemSelectorDialog::onPressItemSelect(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        int index = 0;
        if (sender == _buttonSelect1) {
            index = 0;
        }
        else if (sender == _buttonSelect2) {
            index = 1;
        }
        else if (sender == _buttonSelect3) {
            index = 2;
        }
        else
        {
        	return;
        }
        
        ValueMap info;
        
        info["type"] = _type;
        info["index"] = index;
        
        EventCustomMapped *e = new EventCustomMapped(EVENT_ITEM_SELECTED);
        e->setInfo(info);
        
        Director::getInstance()->getEventDispatcher()->dispatchEvent(e);
        
        this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool InGameItemSelectorDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_holder1", cocos2d::Node*, _holder1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSelect1", cocos2d::extension::ControlButton*, _buttonSelect1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_hand", cocos2d::Sprite*, _hand);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_item1", cocos2d::Sprite*, _item1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_holder2", cocos2d::Node*, _holder2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSelect2", cocos2d::extension::ControlButton*, _buttonSelect2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_item2", cocos2d::Sprite*, _item2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_holder3", cocos2d::Node*, _holder3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSelect3", cocos2d::extension::ControlButton*, _buttonSelect3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_item3", cocos2d::Sprite*, _item3);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler InGameItemSelectorDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressItemSelect", InGameItemSelectorDialog::onPressItemSelect);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void InGameItemSelectorDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void InGameItemSelectorDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


