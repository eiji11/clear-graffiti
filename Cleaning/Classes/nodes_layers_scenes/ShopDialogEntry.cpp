#include "ShopDialogEntry.h"

#include "utils/GeneralUtils.h"


USE_NS

ShopDialogEntry *ShopDialogEntry::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("ShopDialogEntry", ShopDialogEntryLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<ShopDialogEntry*>(ccbReader->readNodeGraphFromFile("ShopDialogEntry.ccbi"));
}

ShopDialogEntry::ShopDialogEntry() : cocos2d::Layer()
, _labelName(NULL)
, _labelType(NULL)
, _containerPrice(NULL)
, _labelPrice(NULL)
, _spriteItem(NULL)
{

}

ShopDialogEntry::~ShopDialogEntry()
{
	CC_SAFE_RELEASE(_labelName);
	CC_SAFE_RELEASE(_labelType);
    CC_SAFE_RELEASE(_containerPrice);
    CC_SAFE_RELEASE(_labelPrice);
    CC_SAFE_RELEASE(_spriteItem);
}

void ShopDialogEntry::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);
}

void ShopDialogEntry::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}

void ShopDialogEntry::setItemInfo(cocos2d::ValueMap itemInfo)
{
    _itemInfo = itemInfo;
    
    int intType = _itemInfo.at("type").asInt();
    std::string type = intType == 1 ? "Sprayer" : "Brush";
    
    _labelName->setString(_itemInfo.at("name").asString());
    _labelType->setString(type);
    _labelPrice->setString(StringUtils::format("%d", _itemInfo.at("price").asInt()));
    
    std::string itemPrefix = intType == 1 ? "equipments/spray-%d.png" : "equipments/brush-%d.png";
    _spriteItem->setSpriteFrame(StringUtils::format(itemPrefix.c_str(), itemInfo.at("id").asInt()));
}


#pragma mark - CCBMemberVariableAssigner functions

bool ShopDialogEntry::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelName", cocos2d::Label*, _labelName);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelType", cocos2d::Label*, _labelType);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerPrice", cocos2d::Sprite*, _containerPrice);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPrice", cocos2d::Label*, _labelPrice);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_spriteItem", cocos2d::Sprite*, _spriteItem);
    

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler ShopDialogEntry::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void ShopDialogEntry::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void ShopDialogEntry::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


