#include "ComicsScene.h"


USE_NS

ComicsScene *ComicsScene::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("ComicsScene", ComicsSceneLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<ComicsScene*>(ccbReader->readNodeGraphFromFile("ComicsScene.ccbi"));
}

ComicsScene::ComicsScene() : cocos2d::Layer()
, _spriteComics(NULL)
, _buttonPlay(NULL)
{

}

ComicsScene::~ComicsScene()
{
	CC_SAFE_RELEASE(_spriteComics);
	CC_SAFE_RELEASE(_buttonPlay);
}

void ComicsScene::onEnter()
{
	cocos2d::Layer::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);

    if (IS_SOUND_ENABLED)
    {
    	PLAY_SOUND("pageflip.mp3");
    }
}

void ComicsScene::onExit()
{
	cocos2d::Layer::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}

void ComicsScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
	}
}

void ComicsScene::setGame(Game *game)
{
	_game = game;
	_game->retain();

	std::string t = StringUtils::format("comics/chapter%d-1.png", _game->getChapter());
	Texture2D *tx = TextureCache::getInstance()->addImage(t);
	if (tx == nullptr)
	{
		std::string img = StringUtils::format("comics/komik%d_big.png", _game->getChapter());
		tx = TextureCache::getInstance()->addImage(img);

		_triviaMode = false;
	}
	else
	{
		_triviaMode = true;
	}

	_spriteComics->setTexture(tx);
}

void ComicsScene::onPressPlay(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
	    if (IS_SOUND_ENABLED)
	    {
	    	PLAY_SOUND("pageflip.mp3");
	    }

		if (_triviaMode)
		{
			std::string img = StringUtils::format("comics/komik%d_big.png", _game->getChapter());
			Texture2D *tx = TextureCache::getInstance()->addImage(img);
			_spriteComics->setTexture(tx);

			_triviaMode = false;
		}
		else
		{
			Director::getInstance()->popScene();
		}
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool ComicsScene::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_spriteComics", cocos2d::Sprite*, _spriteComics);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPlay", cocos2d::extension::ControlButton*, _buttonPlay);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler ComicsScene::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPlay", ComicsScene::onPressPlay);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void ComicsScene::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void ComicsScene::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


