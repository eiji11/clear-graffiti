#include "AboutPage.h"


USE_NS

AboutPage *AboutPage::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("AboutPage", AboutPageLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<AboutPage*>(ccbReader->readNodeGraphFromFile("AboutPage.ccbi"));
}

AboutPage::AboutPage() : cocos2d::Layer()
, _message(NULL)
, _buttonLeft(NULL)
{

}

AboutPage::~AboutPage()
{
	CC_SAFE_RELEASE(_message);
	CC_SAFE_RELEASE(_buttonLeft);
}

void AboutPage::onEnter()
{
	cocos2d::Layer::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
}

void AboutPage::onExit()
{
	cocos2d::Layer::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}

void AboutPage::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressLeft(_buttonLeft, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void AboutPage::setMessageSprite(std::string textureName)
{
	_message->setTexture(textureName);
}

void AboutPage::onPressLeft(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		Director::getInstance()->popScene();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool AboutPage::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_message", cocos2d::Sprite*, _message);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLeft", cocos2d::extension::ControlButton*, _buttonLeft);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler AboutPage::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressLeft", AboutPage::onPressLeft);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void AboutPage::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	this->runAction(CallFunc::create([&](){
		_message->retain();
		_message->removeFromParent();

		_scrollView = ScrollView::create(this->getContentSize(), _message);
		this->addChild(_scrollView);
		_buttonLeft->setLocalZOrder(10);
	}));
}


#pragma mark - CCBAnimationManagerDelegate functions

void AboutPage::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


