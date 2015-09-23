#include "AboutEquipments.h"

#include "HowToPlayScene.h"
#include "MainMenu.h"


USE_NS

AboutEquipments *AboutEquipments::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("AboutEquipments", AboutEquipmentsLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<AboutEquipments*>(ccbReader->readNodeGraphFromFile("AboutEquipments.ccbi"));
}

AboutEquipments::AboutEquipments() : cocos2d::Layer()
, _buttonSprayers(NULL)
, _buttonBrushes(NULL)
, _buttonBack(NULL)
{

}

AboutEquipments::~AboutEquipments()
{
	CC_SAFE_RELEASE(_buttonSprayers);
	CC_SAFE_RELEASE(_buttonBrushes);
}

void AboutEquipments::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void AboutEquipments::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    UI_LOCK_MANAGER_DECREASE();
}

void AboutEquipments::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void AboutEquipments::onPressSprayers(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		HowToPlayScene *p = HowToPlayScene::createFromCCB();
		p->setMaxPage(4);
		p->setTextureNamePlaceHolder("scenes/sprayer_%d.png");
		Scene *s = Scene::create();
		s->addChild(p);
		Director::getInstance()->pushScene(s);
	}
}

void AboutEquipments::onPressBrushes(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
		HowToPlayScene *p = HowToPlayScene::createFromCCB();
		p->setMaxPage(4);
		p->setTextureNamePlaceHolder("scenes/brush_%d.png");
		Scene *s = Scene::create();
		s->addChild(p);
		Director::getInstance()->pushScene(s);
    }
}

void AboutEquipments::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        Director::getInstance()->popScene();
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool AboutEquipments::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonAbout", cocos2d::extension::ControlButton*, _buttonSprayers);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonCredits", cocos2d::extension::ControlButton*, _buttonBrushes);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler AboutEquipments::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSprayers", AboutEquipments::onPressSprayers);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBrushes", AboutEquipments::onPressBrushes);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", AboutEquipments::onPressBack);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void AboutEquipments::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void AboutEquipments::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


