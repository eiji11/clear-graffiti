#include "AlertBox.h"

#include "managers_caches/EventCustomMapped.h"


USE_NS

AlertBox *AlertBox::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("AlertBox", AlertBoxLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<AlertBox*>(ccbReader->readNodeGraphFromFile("AlertBox.ccbi"));
}

AlertBox::AlertBox() : cocos2d::Layer()
//, _containerMain(NULL)
//, _labelMessage(NULL)
, _buttonOkay(NULL)
{

}

AlertBox::~AlertBox()
{
//	CC_SAFE_RELEASE(_containerMain);
//	CC_SAFE_RELEASE(_labelMessage);
	CC_SAFE_RELEASE(_buttonOkay);
}

void AlertBox::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UILockManager::getInstance()->changeLockLevel(VAR_LOCK_CONTEXT, 1);
}

void AlertBox::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(NULL);
    
    UILockManager::getInstance()->changeLockLevel(VAR_LOCK_CONTEXT, -1);
    
    
    EventCustomMapped *mappedEvent = new EventCustomMapped(EVENT_ALERT_BOX_CLOSED);
    ValueMap info;
    info["tag"] = this->getTag();
    mappedEvent->setInfo(info);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(mappedEvent);
}

void AlertBox::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
	}
}

void AlertBox::onPressOkay(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
        animationManager->runAnimationsForSequenceNamed("Exit");
	}
}

//void AlertBox::setMessageText(std::string text)
//{
//    _labelMessage->setString(text);
//}

//void AlertBox::setButtonText(std::string text)
//{
//    _buttonOkay->setTitleForState(text, Control::State::NORMAL);
//    _buttonOkay->setTitleForState(text, Control::State::SELECTED);
//    _buttonOkay->setTitleForState(text, Control::State::HIGH_LIGHTED);
//    _buttonOkay->setTitleForState(text, Control::State::DISABLED);
//}


#pragma mark - CCBMemberVariableAssigner functions

bool AlertBox::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
//	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerMain", cocos2d::LayerColor*, _containerMain);
//	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelMessage", cocos2d::Label*, _labelMessage);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOkay", cocos2d::extension::ControlButton*, _buttonOkay);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler AlertBox::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOkay", AlertBox::onPressOkay);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void AlertBox::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
}


#pragma mark - CCBAnimationManagerDelegate functions

void AlertBox::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	else if (strcmp(name, "Enter") == 0)
	{
		
	}
	else if (strcmp(name, "Exit") == 0)
	{
        this->removeFromParent();
	}
	
}


