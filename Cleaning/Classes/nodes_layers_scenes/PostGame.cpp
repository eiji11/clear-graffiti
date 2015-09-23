#include "PostGame.h"

#include "PreGame.h"
#include "MainMenu.h"
#include "ChapterCover.h"

#include "game/Player.h"

#include "utils/GeneralUtils.h"


USE_NS

PostGame *PostGame::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PostGame", PostGameLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PostGame*>(ccbReader->readNodeGraphFromFile("PostGame.ccbi"));
}

PostGame::PostGame() : cocos2d::Layer()
, _star1(NULL)
, _star2(NULL)
, _star3(NULL)
, _title(NULL)
, _containerRemarks(NULL)
, _labelTime(NULL)
, _labelScore(NULL)
, _labelMoney(NULL)
, _titleLevelUp(NULL)
, _buttonHome(NULL)
, _buttonPlay(NULL)
, _buttonReplay(NULL)

, _failed(false)
{

}

PostGame::~PostGame()
{
	CC_SAFE_RELEASE(_star1);
	CC_SAFE_RELEASE(_star2);
	CC_SAFE_RELEASE(_star3);
	CC_SAFE_RELEASE(_title);
    CC_SAFE_RELEASE(_containerRemarks);
	CC_SAFE_RELEASE(_labelTime);
	CC_SAFE_RELEASE(_labelScore);
	CC_SAFE_RELEASE(_labelMoney);
	CC_SAFE_RELEASE(_titleLevelUp);
	CC_SAFE_RELEASE(_buttonHome);
	CC_SAFE_RELEASE(_buttonPlay);
	CC_SAFE_RELEASE(_buttonReplay);
}

void PostGame::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();

    if (IS_SOUND_ENABLED)
    {
		if (_failed)
		{
			PLAY_SOUND("failedsound.mp3");
		}
		else
		{
			PLAY_SOUND("success.mp3");
		}
	}
}

void PostGame::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();
}

void PostGame::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressHome(_buttonHome, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void PostGame::setGame(Game *game)
{
    _game = game;
    _game->retain();
    
    int startTime = _game->getStartTime();
    int timeLeft = _game->getTime();
    
    int stars = 3;
    
    for (int x = 0; x < 3; x++) {
        if (startTime - timeLeft < _game->getTimeLimit(x)) {
            break;
        }
        stars--;
    }
    
    Sprite *starsSprite[] = {_star1, _star2, _star3};
    
    for (int x = 0; x < 3; x++)
    {
        starsSprite[x]->setVisible(x < stars);
    }
    
    Player *player = Player::getInstance();
    
    int gChapter =_game->getChapter();
    int gLevel = _game->getLevel();
    int pChapter = player->getChapter();
    int pLevel = player->getLevel();
    
    int starsInfo = player->getStarForLevel(gChapter, gLevel);
    
    if (stars > starsInfo) {
        player->setStarForLevel(stars, gChapter, gLevel);
    }
    
    if (stars > 0 && pChapter == gChapter && pLevel == gLevel) {
        pLevel++;
        if (pLevel > 9) {
            pChapter++;
            pLevel = 1;
        }
        
        player->setLevel(pLevel);
        player->setChapter(pChapter);
    }
    
    bool saved = player->save();
    CCLOG("SAVED: %i", saved);
    
    _labelTime->setString(StringUtils::format("%d", startTime - timeLeft));
    _labelScore->setString(StringUtils::format("%d", _game->getScoreGained()));
    _labelMoney->setString(StringUtils::format("%d", _game->getMoneyGained()));
}

void PostGame::setFailed(bool failed)
{
    if (_failed == failed)
    {
        return;
    }
    
    _failed = failed;
    
	_title->setVisible(!_failed);
    _containerRemarks->setVisible(!_failed);
    _buttonPlay->setVisible(!_failed);
    
    if (!_failed)
    {
        _title->setSpriteFrame("pre-post-game/success.png");
    }
    else
    {
        _titleLevelUp->setSpriteFrame("pre-post-game/youfail.png");
        _titleLevelUp->setVisible(true);
        
        _star1->setVisible(false);
        _star2->setVisible(false);
        _star3->setVisible(false);
    }
}

void PostGame::onPressHome(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        MainMenu *layer = MainMenu::createFromCCB();
        auto scene = Scene::create();
        scene->addChild(layer);
        Director::getInstance()->replaceScene(scene);
	}
}

void PostGame::onPressPlay(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
	    int gChapter =_game->getChapter();
	    int gLevel = _game->getLevel();

	    gLevel++;
		if (gLevel > 9) {
			gChapter++;
			gLevel = 1;
		}

        PreGame *layer = PreGame::createFromCCB();
        layer->setGame(Game::create(gChapter, gLevel));
        
        Director::getInstance()->getRunningScene()->addChild(layer, 1001);
	}
}

void PostGame::onPressReplay(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
	    int gChapter =_game->getChapter();
	    int gLevel = _game->getLevel();

        PreGame *layer = PreGame::createFromCCB();
        layer->setGame(Game::create(gChapter, gLevel));
        
        Director::getInstance()->getRunningScene()->addChild(layer, 1001);
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool PostGame::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star1", cocos2d::Sprite*, _star1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star2", cocos2d::Sprite*, _star2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star3", cocos2d::Sprite*, _star3);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_title", cocos2d::Sprite*, _title);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerRemarks", cocos2d::Node*, _containerRemarks);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTime", cocos2d::Label*, _labelTime);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelScore", cocos2d::Label*, _labelScore);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelMoney", cocos2d::Label*, _labelMoney);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_titleLevelUp", cocos2d::Sprite*, _titleLevelUp);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonHome", cocos2d::extension::ControlButton*, _buttonHome);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPlay", cocos2d::extension::ControlButton*, _buttonPlay);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonReplay", cocos2d::extension::ControlButton*, _buttonReplay);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PostGame::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHome", PostGame::onPressHome);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPlay", PostGame::onPressPlay);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressReplay", PostGame::onPressReplay);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PostGame::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void PostGame::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


