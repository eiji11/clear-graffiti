#include "PlayMenu.h"

#include "ChapterCover.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "HowToPlayScene.h"
#include "AboutEquipments.h"

#include "game/Game.h"


USE_NS

PlayMenu *PlayMenu::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PlayMenu", PlayMenuLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PlayMenu*>(ccbReader->readNodeGraphFromFile("PlayMenu.ccbi"));
}

PlayMenu::PlayMenu() : cocos2d::Layer()
, _buttonStoryMode(NULL)
, _buttonTimeAttack(NULL)
, _buttonHowToPlay(NULL)
, _buttonEquipments(NULL)
, _buttonBack(NULL)
{

}

PlayMenu::~PlayMenu()
{
	CC_SAFE_RELEASE(_buttonStoryMode);
	CC_SAFE_RELEASE(_buttonTimeAttack);
	CC_SAFE_RELEASE(_buttonHowToPlay);
	CC_SAFE_RELEASE(_buttonEquipments);
    CC_SAFE_RELEASE(_buttonBack);
}

void PlayMenu::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void PlayMenu::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    UI_LOCK_MANAGER_DECREASE();
}

void PlayMenu::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void PlayMenu::onPressStoryMode(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        ChapterCover *l = ChapterCover::createFromCCB();
        Scene *scene = Scene::create();
        scene->addChild(l);
        Director::getInstance()->replaceScene(scene);
	}
}

void PlayMenu::onPressTimeAttack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        ValueVector chapters = FileUtils::getInstance()->getValueVectorFromFile("games.plist");
        int c = CCRANDOM_0_1() * chapters.size();
        ValueVector levels = chapters.at(c).asValueVector();
        int l = CCRANDOM_0_1() * levels.size();
        
        Game *g = Game::create(c + 1, l + 1);
        g->setTimeAttack(true);
        GameScene *layer = GameScene::createFromCCB();
        layer->loadGame(g);
        
        Scene *s = Scene::create();
        s->addChild(layer);
        
        Director::getInstance()->replaceScene(s);
	}
}

void PlayMenu::onPressHowToPlay(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
    	HowToPlayScene *h = HowToPlayScene::createFromCCB();
    	Scene *s = Scene::create();
    	s->addChild(h);
    	Director::getInstance()->pushScene(s);
    }
}

void PlayMenu::onPressEquipments(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
    	AboutEquipments *h = AboutEquipments::createFromCCB();
    	Scene *s = Scene::create();
    	s->addChild(h);
    	Director::getInstance()->pushScene(s);
    }
}

void PlayMenu::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
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

bool PlayMenu::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonStoryMode", cocos2d::extension::ControlButton*, _buttonStoryMode);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonTimeAttack", cocos2d::extension::ControlButton*, _buttonTimeAttack);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonHowToPlay", cocos2d::extension::ControlButton*, _buttonHowToPlay);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonEquipments", cocos2d::extension::ControlButton*, _buttonEquipments);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);
    
	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PlayMenu::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressStoryMode", PlayMenu::onPressStoryMode);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressTimeAttack", PlayMenu::onPressTimeAttack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHowToPlay", PlayMenu::onPressHowToPlay);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressEquipments", PlayMenu::onPressEquipments);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", PlayMenu::onPressBack);
    

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PlayMenu::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void PlayMenu::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


