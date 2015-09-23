#include "SettingsDialog.h"

#include "game/Player.h"


USE_NS

using namespace ui;

SettingsDialog *SettingsDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("SettingsDialog", SettingsDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<SettingsDialog*>(ccbReader->readNodeGraphFromFile("SettingsDialog.ccbi"));
}

SettingsDialog::SettingsDialog() : cocos2d::Layer()
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

SettingsDialog::~SettingsDialog()
{
    CC_SAFE_RELEASE(_containerName);
	CC_SAFE_RELEASE(_containerMusic);
	CC_SAFE_RELEASE(_buttonMusic);
	CC_SAFE_RELEASE(_checkBoxMusic);
	CC_SAFE_RELEASE(_containerSounds);
	CC_SAFE_RELEASE(_buttonSounds);
	CC_SAFE_RELEASE(_checkBoxSound);
	CC_SAFE_RELEASE(_buttonOk);
}

void SettingsDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void SettingsDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();

}

void SettingsDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressOk(_buttonOk, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void SettingsDialog::onPressMusic(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        UserDefault *ud = UserDefault::getInstance();
        bool value = ud->getBoolForKey("music_enabled", true);
        ud->setBoolForKey("music_enabled", !value);
        
        if (value)
        {
            _checkBoxMusic->removeAllChildren();
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
        }
        else
        {
            Label *l = Label::create();
            l->setString("X");
            l->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            
            _checkBoxMusic->addChild(l);

            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("playing.mp3", true);
        }
        
        ud->flush();
	}
}

void SettingsDialog::onPressSound(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
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
            l->setString("X");
            l->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            
            _checkBoxSound->addChild(l);
        }
        
        ud->flush();
	}
}

void SettingsDialog::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        std::string name = _inputName->getStringValue();
        Player::getInstance()->setName(name);
        Player::getInstance()->save();
        this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool SettingsDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
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

Control::Handler SettingsDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressMusic", SettingsDialog::onPressMusic);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSound", SettingsDialog::onPressSound);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", SettingsDialog::onPressOk);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void SettingsDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    _inputName = TextField::create();
	_inputName->setMaxLengthEnabled(true);
	_inputName->setMaxLength(15);
    _inputName->setContentSize(_containerName->getContentSize());
    _inputName->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _inputName->setPlaceHolder("Name");
    _inputName->setColor(Color3B::BLACK);
    
    _containerName->addChild(_inputName);
    
    _inputName->setText(Player::getInstance()->getName());
    
    
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

void SettingsDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


