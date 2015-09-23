#include "ConfirmExitDialog.h"


USE_NS

ConfirmExitDialog *ConfirmExitDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("ConfirmExitDialog", ConfirmExitDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<ConfirmExitDialog*>(ccbReader->readNodeGraphFromFile("ConfirmExitDialog.ccbi"));
}

ConfirmExitDialog::ConfirmExitDialog() : cocos2d::Layer()
, _buttonOk(NULL)
, _buttonCancel(NULL)
{

}

ConfirmExitDialog::~ConfirmExitDialog()
{
	CC_SAFE_RELEASE(_buttonOk);
	CC_SAFE_RELEASE(_buttonCancel);
}

void ConfirmExitDialog::onEnter()
{
	cocos2d::Layer::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);

    UI_LOCK_MANAGER_INCREASE();
}

void ConfirmExitDialog::onExit()
{
	cocos2d::Layer::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    UI_LOCK_MANAGER_DECREASE();
}

void ConfirmExitDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressConfirm(_buttonCancel, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void ConfirmExitDialog::onPressConfirm(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		if (sender == _buttonOk)
		{
			Director::getInstance()->end();
		}
		else
		{
			this->removeFromParent();
		}
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool ConfirmExitDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonCancel", cocos2d::extension::ControlButton*, _buttonCancel);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler ConfirmExitDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressConfirm", ConfirmExitDialog::onPressConfirm);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void ConfirmExitDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void ConfirmExitDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


