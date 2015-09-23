#include "AboutMenu.h"

#include "AboutPage.h"
#include "MainMenu.h"


USE_NS

AboutMenu *AboutMenu::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("AboutMenu", AboutMenuLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<AboutMenu*>(ccbReader->readNodeGraphFromFile("AboutMenu.ccbi"));
}

AboutMenu::AboutMenu() : cocos2d::Layer()
, _buttonAbout(NULL)
, _buttonCredits(NULL)
, _buttonBack(NULL)
{

}

AboutMenu::~AboutMenu()
{
	CC_SAFE_RELEASE(_buttonAbout);
	CC_SAFE_RELEASE(_buttonCredits);
}

void AboutMenu::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void AboutMenu::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    UI_LOCK_MANAGER_DECREASE();
}

void AboutMenu::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void AboutMenu::onPressAbout(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		AboutPage *p = AboutPage::createFromCCB();
		Scene *s = Scene::create();
		s->addChild(p);
		Director::getInstance()->pushScene(s);
	}
}

void AboutMenu::onPressCredits(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
		AboutPage *p = AboutPage::createFromCCB();
		p->setMessageSprite("scenes/credits.png");
		Scene *s = Scene::create();
		s->addChild(p);
		Director::getInstance()->pushScene(s);
    }
}

void AboutMenu::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        MainMenu *l = MainMenu::createFromCCB();
        Scene *s = Scene::create();
        s->addChild(l);
        
        Director::getInstance()->replaceScene(s);
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool AboutMenu::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonAbout", cocos2d::extension::ControlButton*, _buttonAbout);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonCredits", cocos2d::extension::ControlButton*, _buttonCredits);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler AboutMenu::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressAbout", AboutMenu::onPressAbout);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressCredits", AboutMenu::onPressCredits);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", AboutMenu::onPressBack);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void AboutMenu::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void AboutMenu::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


