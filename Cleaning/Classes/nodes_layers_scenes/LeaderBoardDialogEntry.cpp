#include "LeaderBoardDialogEntry.h"


USE_NS

LeaderBoardDialogEntry *LeaderBoardDialogEntry::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	CCLOG("nll");

	ccNodeLoaderLibrary->registerNodeLoader("LeaderBoardDialogEntry", LeaderBoardDialogEntryLoader::loader());

	CCLOG("registered loader");

	LeaderBoardDialogEntry *b = nullptr;

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	Node *n = ccbReader->readNodeGraphFromFile("LeaderBoardDialogEntry.ccbi");

	if (n != nullptr)
	{
		CCLOG("LOADING LAYER");
		b = dynamic_cast<LeaderBoardDialogEntry*>(n);
		CCLOG("LAYER LOADED");
	}
	else
	{
		CCLOG("LAYER NOT LOADED");
	}


	return b;
}

LeaderBoardDialogEntry::LeaderBoardDialogEntry() : cocos2d::Layer()
, _labelRank(NULL)
, _labelScore(NULL)
, _labelName(NULL)
{

}

LeaderBoardDialogEntry::~LeaderBoardDialogEntry()
{
	CC_SAFE_RELEASE(_labelRank);
	CC_SAFE_RELEASE(_labelScore);
	CC_SAFE_RELEASE(_labelName);
}

void LeaderBoardDialogEntry::onEnter()
{
	cocos2d::Layer::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);

}

void LeaderBoardDialogEntry::onExit()
{
	cocos2d::Layer::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}

void LeaderBoardDialogEntry::setInfo(int rank, cocos2d::ValueMap info)
{
	CCLOG("setting info");
    _labelRank->setString(StringUtils::format("%d", rank));
    _labelScore->setString(info.at("score").asString());
    _labelName->setString(info.at("name").asString());

	CCLOG("info set");
}


#pragma mark - CCBMemberVariableAssigner functions

bool LeaderBoardDialogEntry::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelRank", cocos2d::Label*, _labelRank);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelScore", cocos2d::Label*, _labelScore);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelName", cocos2d::Label*, _labelName);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler LeaderBoardDialogEntry::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void LeaderBoardDialogEntry::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void LeaderBoardDialogEntry::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


