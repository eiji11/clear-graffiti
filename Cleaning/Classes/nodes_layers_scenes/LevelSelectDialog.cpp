#include "LevelSelectDialog.h"

#include "game/Player.h"
#include "game/Game.h"

#include "nodes_layers_scenes/PreGame.h"
#include "ComicsScene.h"


USE_NS

LevelSelectDialog *LevelSelectDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("LevelSelectDialog", LevelSelectDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<LevelSelectDialog*>(ccbReader->readNodeGraphFromFile("LevelSelectDialog.ccbi"));
}

LevelSelectDialog::LevelSelectDialog() : cocos2d::Layer()
, _containerLevel1(NULL)
, _buttonLevel1(NULL)
, _containerLevel2(NULL)
, _buttonLevel2(NULL)
, _containerLevel3(NULL)
, _buttonLevel3(NULL)
, _containerLevel4(NULL)
, _buttonLevel4(NULL)
, _containerLevel5(NULL)
, _buttonLevel5(NULL)
, _containerLevel6(NULL)
, _buttonLevel6(NULL)
, _containerLevel7(NULL)
, _buttonLevel7(NULL)
, _containerLevel8(NULL)
, _buttonLevel8(NULL)
, _containerLevel9(NULL)
, _buttonLevel9(NULL)
, _buttonClose(NULL)
{

}

LevelSelectDialog::~LevelSelectDialog()
{
	CC_SAFE_RELEASE(_containerLevel1);
	CC_SAFE_RELEASE(_buttonLevel1);
	CC_SAFE_RELEASE(_containerLevel2);
	CC_SAFE_RELEASE(_buttonLevel2);
	CC_SAFE_RELEASE(_containerLevel3);
	CC_SAFE_RELEASE(_buttonLevel3);
	CC_SAFE_RELEASE(_containerLevel4);
	CC_SAFE_RELEASE(_buttonLevel4);
	CC_SAFE_RELEASE(_containerLevel5);
	CC_SAFE_RELEASE(_buttonLevel5);
	CC_SAFE_RELEASE(_containerLevel6);
	CC_SAFE_RELEASE(_buttonLevel6);
	CC_SAFE_RELEASE(_containerLevel7);
	CC_SAFE_RELEASE(_buttonLevel7);
	CC_SAFE_RELEASE(_containerLevel8);
	CC_SAFE_RELEASE(_buttonLevel8);
	CC_SAFE_RELEASE(_containerLevel9);
	CC_SAFE_RELEASE(_buttonLevel9);
	CC_SAFE_RELEASE(_buttonClose);
}

void LevelSelectDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void LevelSelectDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    UI_LOCK_MANAGER_DECREASE();
}

void LevelSelectDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressClose(_buttonClose, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

int LevelSelectDialog::getChapter()
{
    return _chapter;
}

void LevelSelectDialog::setChapter(int chapter)
{
    _chapter = chapter;
    
    int playerChapter = Player::getInstance()->getChapter();
    int playerLevel = Player::getInstance()->getLevel();
    
    Node *containers[] = {
        _containerLevel1,
        _containerLevel2,
        _containerLevel3,
        _containerLevel4,
        _containerLevel5,
        _containerLevel6,
        _containerLevel7,
        _containerLevel8,
        _containerLevel9,
    };
    ControlButton *buttons[] = {
        _buttonLevel1,
        _buttonLevel2,
        _buttonLevel3,
        _buttonLevel4,
        _buttonLevel5,
        _buttonLevel6,
        _buttonLevel7,
        _buttonLevel8,
        _buttonLevel9,
    };
    
    for (int x = 0; x < 9; x++) {
        Node *container = containers[x];
        ControlButton *button = buttons[x];
        
        auto star1 = container->getChildByName("1");
        auto star2 = container->getChildByName("2");
        auto star3 = container->getChildByName("3");
        
        if (_chapter < playerChapter) {
            button->setEnabled(true);
            
            int starInfo = Player::getInstance()->getStarForLevel(_chapter, x + 1);
            
            star3->setVisible(starInfo >= 3);
            star2->setVisible(starInfo >= 2);
            star1->setVisible(starInfo >= 1);
        }
        else if (_chapter == playerChapter)
        {
            button->setEnabled(x < playerLevel);
            if (x >= playerLevel)
            {
                star1->setVisible(false);
                star2->setVisible(false);
                star3->setVisible(false);
            }
            else
            {
                int starInfo = Player::getInstance()->getStarForLevel(_chapter, x + 1);
                
                star3->setVisible(starInfo >= 3);
                star2->setVisible(starInfo >= 2);
                star1->setVisible(starInfo >= 1);
            }
        }
        else
        {
            button->setEnabled(false);

            star1->setVisible(false);
            star2->setVisible(false);
            star3->setVisible(false);
        }
        
    }
    
}

void LevelSelectDialog::onPressLevel(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        int level = 0;
        if (sender == _buttonLevel1) {
            level = 1;
        }
        else if (sender == _buttonLevel2) {
            level = 2;
        }
        else if (sender == _buttonLevel3) {
            level = 3;
        }
        else if (sender == _buttonLevel4) {
            level = 4;
        }
        else if (sender == _buttonLevel5) {
            level = 5;
        }
        else if (sender == _buttonLevel6) {
            level = 6;
        }
        else if (sender == _buttonLevel7) {
            level = 7;
        }
        else if (sender == _buttonLevel8) {
            level = 8;
        }
        else if (sender == _buttonLevel9) {
            level = 9;
        }
        
        Game *game = Game::create(_chapter, level);

        PreGame *l = PreGame::createFromCCB();
        l->setGame(game);
        
        Director::getInstance()->getRunningScene()->addChild(l, 1000);


        if (level == 1)
        {

        	UserDefault *ud = UserDefault::getInstance();
			std::string chapter = StringUtils::format("comic-%d", _chapter);
			bool shown = ud->getBoolForKey(chapter.c_str(), false);
			if (!shown)
			{
				this->runAction(CallFunc::create([&, game, ud, chapter](){
					ComicsScene *s = ComicsScene::createFromCCB();
					s->setGame(game);

					Scene *scene = Scene::create();
					scene->addChild(s);

					ud->setBoolForKey(chapter.c_str(), true);
					ud->flush();

					Director::getInstance()->pushScene(scene);
				}));
			}

        }
	}
}

void LevelSelectDialog::onPressClose(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
        this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool LevelSelectDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel1", cocos2d::Node*, _containerLevel1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel1", cocos2d::extension::ControlButton*, _buttonLevel1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel2", cocos2d::Node*, _containerLevel2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel2", cocos2d::extension::ControlButton*, _buttonLevel2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel3", cocos2d::Node*, _containerLevel3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel3", cocos2d::extension::ControlButton*, _buttonLevel3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel4", cocos2d::Node*, _containerLevel4);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel4", cocos2d::extension::ControlButton*, _buttonLevel4);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel5", cocos2d::Node*, _containerLevel5);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel5", cocos2d::extension::ControlButton*, _buttonLevel5);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel6", cocos2d::Node*, _containerLevel6);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel6", cocos2d::extension::ControlButton*, _buttonLevel6);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel7", cocos2d::Node*, _containerLevel7);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel7", cocos2d::extension::ControlButton*, _buttonLevel7);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel8", cocos2d::Node*, _containerLevel8);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel8", cocos2d::extension::ControlButton*, _buttonLevel8);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerLevel9", cocos2d::Node*, _containerLevel9);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLevel9", cocos2d::extension::ControlButton*, _buttonLevel9);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonClose", cocos2d::extension::ControlButton*, _buttonClose);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler LevelSelectDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressLevel", LevelSelectDialog::onPressLevel);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressClose", LevelSelectDialog::onPressClose);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void LevelSelectDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void LevelSelectDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


