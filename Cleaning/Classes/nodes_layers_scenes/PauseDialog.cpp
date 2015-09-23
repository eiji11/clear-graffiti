#include "PauseDialog.h"
#include "MainMenu.h"

#include "game/Player.h"


USE_NS

PauseDialog *PauseDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PauseDialog", PauseDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PauseDialog*>(ccbReader->readNodeGraphFromFile("PauseDialog.ccbi"));
}

PauseDialog::PauseDialog() : cocos2d::Layer()
, _labelTime(NULL)
, _containerName(NULL)
, _containerMusic(NULL)
, _buttonMusic(NULL)
, _checkBoxMusic(NULL)
, _containerSounds(NULL)
, _buttonSounds(NULL)
, _checkBoxSound(NULL)
, _buttonOk(NULL)
{

}

PauseDialog::~PauseDialog()
{
    CC_SAFE_RELEASE(_labelTime);
    CC_SAFE_RELEASE(_containerName);
	CC_SAFE_RELEASE(_containerMusic);
	CC_SAFE_RELEASE(_buttonMusic);
	CC_SAFE_RELEASE(_checkBoxMusic);
	CC_SAFE_RELEASE(_containerSounds);
	CC_SAFE_RELEASE(_buttonSounds);
	CC_SAFE_RELEASE(_checkBoxSound);
	CC_SAFE_RELEASE(_buttonOk);
}

void PauseDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void PauseDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();

}

void PauseDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressOk(_buttonOk, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void PauseDialog::setGame(Game *game)
{
    _game = game;
    _game->retain();
    
    _labelTime->setString(StringUtils::format("%d", _game->getTime()));
}

void PauseDialog::onPressMusic(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        UserDefault *ud = UserDefault::getInstance();
        bool value = ud->getBoolForKey("music_enabled", true);
        ud->setBoolForKey("music_enabled", !value);
        
        if (value)
        {
            _checkBoxMusic->removeAllChildren();
        }
        else
        {
            Label *l = Label::create();
            l->setString("/");
            l->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            l->setGlobalZOrder(this->getGlobalZOrder());
            
            _checkBoxMusic->addChild(l);
        }
        
        ud->flush();
	}
}

void PauseDialog::onPressSound(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        UserDefault *ud = UserDefault::getInstance();
        bool value = ud->getBoolForKey("sound_enabled", true);
        ud->setBoolForKey("sound_enabled", !value);
        
        if (value)
        {
            _checkBoxSound->removeAllChildren();
        }
        else
        {
            Label *l = Label::create();
            l->setString("/");
            l->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            l->setGlobalZOrder(this->getGlobalZOrder());
            
            _checkBoxSound->addChild(l);
        }
        
        ud->flush();
	}
}

void PauseDialog::onPressHome(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        MainMenu *layer = MainMenu::createFromCCB();
        auto scene = Scene::create();
        scene->addChild(layer);
        Director::getInstance()->replaceScene(scene);
	}
}

void PauseDialog::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool PauseDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTime", cocos2d::Label*, _labelTime);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerName", cocos2d::LayerColor*, _containerName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerMusic", cocos2d::Node*, _containerMusic);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonMusic", cocos2d::extension::ControlButton*, _buttonMusic);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_checkBoxMusic", cocos2d::Sprite*, _checkBoxMusic);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerSounds", cocos2d::Node*, _containerSounds);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSounds", cocos2d::extension::ControlButton*, _buttonSounds);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_checkBoxSound", cocos2d::Sprite*, _checkBoxSound);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PauseDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressMusic", PauseDialog::onPressMusic);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSound", PauseDialog::onPressSound);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", PauseDialog::onPressOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHome", PauseDialog::onPressHome);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PauseDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    UserDefault *ud = UserDefault::getInstance();
    
    if (ud->getBoolForKey("music_enabled", true))
    {
        Label *l = Label::create();
        l->setString("X");
        l->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        
        _checkBoxMusic->addChild(l);
    }
    if (ud->getBoolForKey("sound_enabled", true))
    {
        Label *l = Label::create();
        l->setString("X");
        l->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        
        _checkBoxSound->addChild(l);
    }
}


#pragma mark - CCBAnimationManagerDelegate functions

void PauseDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


