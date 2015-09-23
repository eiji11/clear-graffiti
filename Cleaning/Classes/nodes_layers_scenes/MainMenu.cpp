#include "MainMenu.h"

#include "GameScene.h"
#include "PlayMenu.h"
#include "SettingsDialog.h"
#include "AboutMenu.h"
#include "LeaderBoardDialog.h"
#include "ConfirmExitDialog.h"
#include "AboutEquipments.h"
#include "ShopDialog.h"

#include "game/Player.h"

#include "managers_caches/ObserverManager.h"

USE_NS
using namespace CocosDenshion;


MainMenu *MainMenu::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("MainMenu", MainMenuLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<MainMenu*>(ccbReader->readNodeGraphFromFile("MainMenu.ccbi"));
}

MainMenu::MainMenu() : cocos2d::Layer()
, _containerMain(NULL)
, _labelHelloThere(NULL)
, _labelName(NULL)
, _buttonStart(NULL)
, _buttonSettings(NULL)
, _buttonShop(NULL)
, _buttonAbout(NULL)
, _buttonRank(NULL)
{

}

MainMenu::~MainMenu()
{
	CC_SAFE_RELEASE(_containerMain);
    CC_SAFE_RELEASE(_labelHelloThere);
    CC_SAFE_RELEASE(_labelName);
    CC_SAFE_RELEASE(_buttonStart);
    CC_SAFE_RELEASE(_buttonSettings);
    CC_SAFE_RELEASE(_buttonShop);
    CC_SAFE_RELEASE(_buttonAbout);
    CC_SAFE_RELEASE(_buttonRank);
}

void MainMenu::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    OBSERVE(this, EVENT_LOCK_LEVEL_CHANGED, [&](EventCustom *e){
        _labelName->setString(Player::getInstance()->getName());
    });

    if (IS_MUSIC_ENABLED)
    {
    	SimpleAudioEngine::getInstance()->playBackgroundMusic("playing.mp3", true);
    }
}

void MainMenu::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    UNOBSERVE(this);
}

void MainMenu::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		ConfirmExitDialog *l = ConfirmExitDialog::createFromCCB();
		this->addChild(l, 1000);
	}
}

void MainMenu::onPressStart(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        PlayMenu *layer = PlayMenu::createFromCCB();
        auto scene = Scene::create();
        scene->addChild(layer);
        Director::getInstance()->replaceScene(scene);
	}
}

void MainMenu::onPressSettings(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        SettingsDialog *d = SettingsDialog::createFromCCB();
        this->addChild(d, 10000);
    }
}

void MainMenu::onPressShop(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
    	ShopDialog *d = ShopDialog::createFromCCB();
    	Director::getInstance()->getRunningScene()->addChild(d, 1000);
    }
}

void MainMenu::onPressAbout(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        AboutMenu *l = AboutMenu::createFromCCB();
        Scene *scene = Scene::create();
        scene->addChild(l);
        Director::getInstance()->replaceScene(scene);
    }
}

void MainMenu::onPressRank(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        LeaderBoardDialog *l = LeaderBoardDialog::createFromCCB();
        this->addChild(l, 1000);
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool MainMenu::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerMain", cocos2d::Node*, _containerMain);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelHelloThere", cocos2d::Label*, _labelHelloThere);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelName", cocos2d::Label*, _labelName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonStart", cocos2d::extension::ControlButton*, _buttonStart);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSettings", cocos2d::extension::ControlButton*, _buttonSettings);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonShop", cocos2d::extension::ControlButton*, _buttonShop);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonAbout", cocos2d::extension::ControlButton*, _buttonAbout);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRank", cocos2d::extension::ControlButton*, _buttonRank);
    
    return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler MainMenu::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressStart", MainMenu::onPressStart);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSettings", MainMenu::onPressSettings);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressShop", MainMenu::onPressShop);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressAbout", MainMenu::onPressAbout);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressRank", MainMenu::onPressRank);
    
    return NULL;
}


#pragma mark - NodeLoaderListener functions

void MainMenu::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    _labelName->setString(Player::getInstance()->getName());
}


#pragma mark - CCBAnimationManagerDelegate functions

void MainMenu::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}
