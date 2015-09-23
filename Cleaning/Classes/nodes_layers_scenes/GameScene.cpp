#include "GameScene.h"

#include "managers_caches/ObserverManager.h"
#include "managers_caches/EventCustomMapped.h"

#include "nodes_layers_scenes/InGameItemSelectorDialog.h"
#include "nodes_layers_scenes/PostGame.h"
#include "PauseDialog.h"

#include "utils/GeneralUtils.h"


USE_NS

bool GameScene::SHOW_HOW_TO_PLAY = true;

GameScene *GameScene::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("GameScene", GameSceneLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<GameScene*>(ccbReader->readNodeGraphFromFile("GameScene.ccbi"));
}

GameScene::GameScene() : cocos2d::Layer()
, _background(NULL)
, _containerScene(NULL)
, _containerTutorial(NULL)
, _spriteLeft(NULL)
, _spriteRight(NULL)
, _spriteRubber(NULL)
, _hudUpper(NULL)
, _titleMoney(NULL)
, _titleTime(NULL)
, _titleScore(NULL)
, _containerMoney(NULL)
, _labelMoney(NULL)
, _containerTime(NULL)
, _labelTime(NULL)
, _containerScore(NULL)
, _labelScore(NULL)
, _hudLower(NULL)
, _buttonSpray(NULL)
, _buttonPause(NULL)
, _buttonBrush(NULL)

, _isPaused(false)
, _isGameOver(false)
, _sprayTypeIndex(-1)
, _brushTypeIndex(-1)
, _tutorialState(0)
{

}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_containerScene);
    CC_SAFE_RELEASE(_containerTutorial);
    CC_SAFE_RELEASE(_spriteLeft);
    CC_SAFE_RELEASE(_spriteRight);
    CC_SAFE_RELEASE(_spriteRubber);
    CC_SAFE_RELEASE(_hudUpper);
    CC_SAFE_RELEASE(_titleMoney);
    CC_SAFE_RELEASE(_titleTime);
    CC_SAFE_RELEASE(_titleScore);
    CC_SAFE_RELEASE(_containerMoney);
    CC_SAFE_RELEASE(_labelMoney);
    CC_SAFE_RELEASE(_containerTime);
    CC_SAFE_RELEASE(_labelTime);
    CC_SAFE_RELEASE(_containerScore);
    CC_SAFE_RELEASE(_labelScore);
    CC_SAFE_RELEASE(_hudLower);
    CC_SAFE_RELEASE(_buttonSpray);
    CC_SAFE_RELEASE(_buttonPause);
    CC_SAFE_RELEASE(_buttonBrush);
}

void GameScene::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    GeneralUtils::getInstance()->setGlobalZOrder(_hudLower, 3);
    
    _touchType = TOUCH_NONE;
    
    EventListenerTouchOneByOne *toucher = EventListenerTouchOneByOne::create();
    toucher->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    toucher->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    toucher->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    toucher->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(toucher, _containerScene);
    
    
    this->schedule(schedule_selector(GameScene::updateTimer), 1.f);
    
    OBSERVE(this, EVENT_LOCK_LEVEL_CHANGED, [&](EventCustom *e){

        if (IS_LOCKED && _isPaused) {
            this->hideVandals();
        }
        else if (!IS_LOCKED && _isPaused)
        {
            _isPaused = false;
            this->showVandals();
        }
    	this->_buttonPause->setVisible(!_isPaused);
    });
    
    OBSERVE(this, EVENT_VANDAL_FORCED_REMOVED, [&](EventCustom *event){
        VandalNode *vandalNode = (VandalNode*)event->getUserData();
        if (vandalNode != nullptr)
        {
            this->removeVandal(vandalNode);
        }
    });
    
    OBSERVE(this, EVENT_ALERT_BOX_CLOSED, [&](EventCustom *event){
        EventCustomMapped* e = DC(EventCustomMapped*, event);
        ValueMap info = e->getInfo();
        
        int tag = info.at("tag").asInt();
        
        if (tag == 1) {
            
        }
    });
    
    OBSERVE(this, EVENT_ITEM_SELECTED, [&](EventCustom *event){
        EventCustomMapped* e = DC(EventCustomMapped*, event);
        ValueMap info = e->getInfo();
        
        int type = info.at("type").asInt();
        int index = info.at("index").asInt();
        
        _touchType = static_cast<TouchType>(type);
        
        SpriteFrameCache *sfc = SpriteFrameCache::getInstance();
        
        if (type == TOUCH_SPRAY)
        {
        	if (_hasTutorial && _tutorialState == 2)
        	{
        		_tutorialState = 3;
        		_spriteRubber->setVisible(true);
        		_spriteRubber->runAction(RepeatForever::create(Sequence::create(
        				MoveBy::create(0.5f, Vec2(25.f, 25.f)),
        				MoveBy::create(1.f, Vec2(-50.f, -50.f)),
        				MoveBy::create(0.5f, Vec2(25.f, 25.f)),
        				NULL
        				)));
        	}

            _sprayTypeIndex = index;
            ValueMap sprayType = _sprayTypes[_sprayTypeIndex].asValueMap();
            std::string sprayFrame = StringUtils::format("equipments/spray-%d.png", sprayType.at("type").asInt());
            
            SpriteFrame *frame = sfc->getSpriteFrameByName(sprayFrame);
            
            _buttonSpray->setBackgroundSpriteFrameForState(frame, Control::State::NORMAL);
            _buttonSpray->setBackgroundSpriteFrameForState(frame, Control::State::SELECTED);
            _buttonSpray->setBackgroundSpriteFrameForState(frame, Control::State::DISABLED);
            _buttonSpray->setBackgroundSpriteFrameForState(frame, Control::State::HIGH_LIGHTED);
            
            _buttonSpray->setPreferredSize(frame->getRect().size);

			GeneralUtils::getInstance()->setGlobalZOrder(_buttonSpray, _hudLower->getGlobalZOrder());
        }
        else if (type == TOUCH_BRUSH)
        {

        	if (_hasTutorial && _tutorialState == 6)
        	{
        		_tutorialState = 7;
        		_spriteRubber->setVisible(true);
        		_spriteRubber->runAction(RepeatForever::create(Sequence::create(
        				MoveBy::create(0.5f, Vec2(25.f, 25.f)),
        				MoveBy::create(1.f, Vec2(-50.f, -50.f)),
        				MoveBy::create(0.5f, Vec2(25.f, 25.f)),
        				NULL
        				)));
        	}

            _brushTypeIndex = index;
            ValueMap brushType = _brushTypes[_brushTypeIndex].asValueMap();
            std::string brushFrame = StringUtils::format("equipments/brush-%d.png", brushType.at("type").asInt());
            
            SpriteFrame *frame = sfc->getSpriteFrameByName(brushFrame);
            
            _buttonBrush->setBackgroundSpriteFrameForState(frame, Control::State::NORMAL);
            _buttonBrush->setBackgroundSpriteFrameForState(frame, Control::State::SELECTED);
            _buttonBrush->setBackgroundSpriteFrameForState(frame, Control::State::DISABLED);
            _buttonBrush->setBackgroundSpriteFrameForState(frame, Control::State::HIGH_LIGHTED);
            
            _buttonBrush->setPreferredSize(frame->getRect().size);

			GeneralUtils::getInstance()->setGlobalZOrder(_buttonBrush, _hudLower->getGlobalZOrder());
        }
    });
    
    if (_hasTutorial)
    {
		_tutorialState = 1;
    	_spriteLeft->setVisible(true);
    	_spriteLeft->runAction(RepeatForever::create(Sequence::create(
    			ScaleTo::create(0.5f, 1.1f),
    			ScaleTo::create(0.5f, 1.f),
		NULL)));
    }

}

void GameScene::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    _eventDispatcher->removeEventListenersForTarget(_containerScene);
    
    UNOBSERVE(this);
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressPause(_buttonPause, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void GameScene::updateTimer(float delta)
{
    if (_isPaused || _isGameOver)
    {
        return;
    }
    
    if (_game->getTime() <= 0)
    {
        _isGameOver = true;
        
        if (IS_SOUND_ENABLED){
        	PLAY_SOUND("times-up.mp3");
        }

        Sprite *timesup = Sprite::createWithSpriteFrameName("scenes_ui/timesup.png");
        Size sSize = this->getContentSize();
        timesup->setPosition(Vec2(sSize.width * 0.5f, sSize.height * 0.6f));
        timesup->runAction(Sequence::create(
        		MoveBy::create(2.f, Vec2(0, -sSize.height * 0.15f)),
        CallFuncN::create([&](Node *n){
            PostGame *d = PostGame::createFromCCB();
            d->setGame(_game);
            d->setFailed(true);

            this->addChild(d, 1000);
            n->removeFromParent();
        }),
        NULL));

        this->addChild(timesup, 100);

        this->clearVandals();

        _spriteLeft->setVisible(false);
        _spriteRight->setVisible(false);
        _spriteRubber->setVisible(false);

        this->unschedule(schedule_selector(GameScene::updateTimer));
    }
    
    if (!_isHighlighting) {
        if (_highlightTimer == 0)
        {
            highlight();
        }
    }
    else
    {
        if (_highlightTimer <= -3)
        {
            _isHighlighting = false;
            _highlightTimer = 5.f;
        }
    }
    _highlightTimer--;
    
    
    if (_game->getTime() > 0)
    {
        _game->addTime(-1);
        _labelTime->setString(StringUtils::format("%d", _game->getTime()));
    }
}

void GameScene::loadGame(Game *game)
{
    _game = game;
    _game->retain();
    
    _hasTutorial = _game->getChapter() == 1 && _game->getLevel() == 1 && !_game->isTimeAttack() && SHOW_HOW_TO_PLAY;
    if (_hasTutorial)
    {
    	SHOW_HOW_TO_PLAY = false;
    }
    else
    {
    	_tutorialState = -1;
    }

    _background->setTexture(_game->getBackgroundFile());
    
    _sprayTypes = _game->getSprays();
    _brushTypes = _game->getBrushes();
    
    SpriteFrameCache *sfc = SpriteFrameCache::getInstance();
    
    std::string sprayFrame = StringUtils::format("equipments/spray-%d.png", _sprayTypes.front().asValueMap().at("type").asInt());
    
    SpriteFrame *frame = sfc->getSpriteFrameByName(sprayFrame);
    
    _buttonSpray->setBackgroundSpriteFrameForState(frame, Control::State::NORMAL);
    _buttonSpray->setBackgroundSpriteFrameForState(frame, Control::State::SELECTED);
    _buttonSpray->setBackgroundSpriteFrameForState(frame, Control::State::DISABLED);
    _buttonSpray->setBackgroundSpriteFrameForState(frame, Control::State::HIGH_LIGHTED);
    
    _buttonSpray->setPreferredSize(frame->getRect().size);
    
    sprayFrame = StringUtils::format("equipments/brush-%d.png", _sprayTypes.front().asValueMap().at("type").asInt());
    frame = sfc->getSpriteFrameByName(sprayFrame);
    
    _buttonBrush->setBackgroundSpriteFrameForState(frame, Control::State::NORMAL);
    _buttonBrush->setBackgroundSpriteFrameForState(frame, Control::State::SELECTED);
    _buttonBrush->setBackgroundSpriteFrameForState(frame, Control::State::DISABLED);
    _buttonBrush->setBackgroundSpriteFrameForState(frame, Control::State::HIGH_LIGHTED);
    
    _buttonBrush->setPreferredSize(frame->getRect().size);
    
    
    Vector<Vandal*> vandals = game->getVandals();
    
    Size sceneSize = _containerScene->getContentSize();
    float yStart = _hudLower->getContentSize().height;
    float yLimit = sceneSize.height - _hudUpper->getContentSize().height;


    for (Vandal *vandal : vandals)
    {
		VandalNode *vandalNode = VandalNode::create(vandal);
		if (vandalNode != nullptr)
		{
			Size vandalContentSize = vandalNode->getContentSize();
			Vec2 vandalPosition = vandalNode->getPosition();
			Vec2 original = vandalPosition;

			if (vandalPosition.x - vandalContentSize.width * 0.5f < 0)
			{
				vandalPosition.x = vandalContentSize.width * 0.5f;
			}
			else if (vandalPosition.x + vandalContentSize.width * 0.5f > sceneSize.width)
			{
				vandalPosition.x = sceneSize.width - vandalContentSize.width * .5f;
			}

			if (vandalPosition.y - vandalContentSize.height * 0.5f < yStart)
			{
				vandalPosition.y = yStart + vandalContentSize.height * 0.5f;
			}
			else if (vandalPosition.y + vandalContentSize.height * 0.5f > yLimit)
			{
				vandalPosition.y = yLimit - vandalContentSize.height * 0.5f;
			}

			vandalNode->setPosition(vandalPosition);

			this->addVandal(vandalNode);
		}
    }
    
    _labelTime->setString(StringUtils::format("%d", _game->getTime()));
    
    _labelScore->setString(StringUtils::format("%d", _game->getScore()));
    _labelMoney->setString(StringUtils::format("%d", _game->getMoney()));
    
}

void GameScene::addVandal(VandalNode *vandal)
{
    _containerScene->addChild(vandal);
    _vandals.pushBack(vandal);
}

void GameScene::removeVandal(VandalNode *vandal)
{
    _vandals.eraseObject(vandal);
    
    vandal->removeFromParent();
}

void GameScene::clearVandals()
{
    for (auto n : _vandals)
    {
        n->removeFromParent();
    }
    
    _vandals.clear();
}

void GameScene::onPressPause(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        _isPaused = true;
        
        PauseDialog *l = PauseDialog::createFromCCB();
        l->setGame(_game);
        
        this->addChild(l, 1002);
        GeneralUtils::getInstance()->setGlobalZOrder(l, this->getGlobalZOrder());
	}
}

void GameScene::onPressSpray(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !(_isPaused || _isGameOver) && !IS_LOCKED)
	{

        if (!_game->isTimeAttack())
        {
            InGameItemSelectorDialog *dialog = InGameItemSelectorDialog::createFromCCB();

    		if (_hasTutorial && _tutorialState == 1)
    		{
    			_tutorialState = 2;
    			_spriteLeft->stopAllActions();
    			_spriteLeft->setVisible(false);

    			dialog->highlightItem();
    		}
            
            dialog->setType(TOUCH_SPRAY, _sprayTypes);
            GeneralUtils::getInstance()->setGlobalZOrder(dialog, 4);
            
            this->addChild(dialog, 100);
        }
        else
        {
            _touchType = TOUCH_SPRAY;
            _sprayTypeIndex = 0;
        }
	}
}

void GameScene::onPressBrush(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !(_isPaused || _isGameOver) && !IS_LOCKED)
    {
        if (!_game->isTimeAttack())
        {
            InGameItemSelectorDialog *dialog = InGameItemSelectorDialog::createFromCCB();

    		if (_hasTutorial && _tutorialState == 5)
    		{
    			_tutorialState = 6;
    			_spriteRight->stopAllActions();
    			_spriteRight->setVisible(false);

    			dialog->highlightItem();
    		}

            dialog->setType(TOUCH_BRUSH, _brushTypes);
            GeneralUtils::getInstance()->setGlobalZOrder(dialog, 4);
            
            this->addChild(dialog, 100);
        }
        else
        {
            _touchType = TOUCH_BRUSH;
            _brushTypeIndex = 0;
        }
	}
}

void GameScene::highlight()
{
    _isHighlighting = true;
    for (VandalNode *vandalNode : _vandals)
    {
        vandalNode->highlight();
    }
}

void GameScene::unhighlight()
{
    if (_isHighlighting)
    {
        _isHighlighting = false;
        for (VandalNode *vandalNode : _vandals)
        {
            vandalNode->unhighlight();
        }
    }
    
    _highlightTimer = 5.f;
}

void GameScene::hideVandals()
{
    for (VandalNode *vandalNode : _vandals)
    {
        vandalNode->setVisible(false);
    }
}

void GameScene::showVandals()
{
    for (VandalNode *vandalNode : _vandals)
    {
        vandalNode->setVisible(true);
    }
}


#pragma mark - Touch methods

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    _currentTouchLocation = touch->getLocation();
    
    if (!(_isPaused || _isGameOver) && !IS_LOCKED)
    {
    	if (_hasTutorial && (_tutorialState == 3 || _tutorialState == 7))
    	{
    		if (_tutorialState == 3)
    		{
    			_tutorialState = 4;
    		}
    		else
    		{
    			_tutorialState = 8;
    		}
    		_spriteRubber->stopAllActions();
    		_spriteRubber->setVisible(false);
    	}
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BEGIN_BRUSHING);
        
        return true;
    }

    return false;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if ((_isPaused || _isGameOver) && !IS_LOCKED)
    {
        event->stopPropagation();
        return;
    }
    
    Vec2 location = touch->getLocation();
    float distance = sqrtf(powf(location.x - _currentTouchLocation.x, 2) +  powf(location.y - _currentTouchLocation.y, 2));
    int cursorRadius = BRUSH_RADIUS;
    
    if (_touchType == TOUCH_SPRAY)
    {
        cursorRadius = BRUSH_RADIUS * (_sprayTypeIndex + 1);
    }
    else if (_touchType == TOUCH_BRUSH)
    {
        cursorRadius = BRUSH_RADIUS * (_brushTypeIndex + 1);
    }
    
    
    if (distance >= BRUSH_RADIUS * 0.5f) {
        bool noVandalSprayed = _touchType == TOUCH_SPRAY;
        for (VandalNode *vandal : _vandals)
        {
            if (vandal->isCleared()) {
                continue;
            }
            
            Rect cursorRect;
            cursorRect.size = Size(cursorRadius, cursorRadius);
            cursorRect.origin = Vec2(location.x - cursorRadius, location.y - cursorRadius);
            
            if (vandal->intersects(cursorRect))
            {
                if (_touchType == TOUCH_SPRAY)
                {
                    if (_sprayTypeIndex != -1)
                    {
                        if (vandal->spray(_sprayTypes[_sprayTypeIndex].asValueMap().at("type").asInt(), touch, cursorRadius))
                        {
                            noVandalSprayed = false;
                            this->unhighlight();
                        }
                    }
                }
                else if (_touchType == TOUCH_BRUSH)
                {
                    if (_brushTypeIndex != -1) {
                        vandal->brush(_brushTypes[_brushTypeIndex].asValueMap().at("type").asInt(), touch, cursorRadius);
                        this->unhighlight();
                        if (vandal->isCleared())
                        {
                            Size vSize = vandal->getContentSize();
                            
                            int score = Vec2::ZERO.distance(Vec2(vSize.width, vSize.height));
                            
                            _game->addScore(score);
                            _game->addMoney(score * 0.125f);
                            
                            _labelScore->setString(StringUtils::format("%d", _game->getScore()));
                            _labelMoney->setString(StringUtils::format("%d", _game->getMoney()));
                            
                            this->removeVandal(vandal);
                            
                            if (_vandals.empty())
                            {
                                _isGameOver = true;
                                
                                if (!_game->isTimeAttack())
                                {
                                    PostGame *d = PostGame::createFromCCB();
                                    d->setGame(_game);
                                    d->setFailed(false);
                                    
                                    this->clearVandals();

                                    this->addChild(d, 100);
                                }
                                else
                                {
                                    ValueVector chapters = FileUtils::getInstance()->getValueVectorFromFile("games.plist");
                                    int c = CCRANDOM_0_1() * chapters.size();
                                    ValueVector levels = chapters.at(c).asValueVector();
                                    int l = CCRANDOM_0_1() * levels.size();
                                    
                                    Game *g = Game::create(c + 1, l + 1);
                                    g->setStartTime(_game->getTime() + 30);
                                    g->setTime(_game->getTime() + 30);
                                    g->setTimeAttack(true);
                                    g->setTimeAttacksFinished(_game->getTimeAttacksFinished() + 1);
                                    GameScene *layer = GameScene::createFromCCB();
                                    layer->loadGame(g);
                                    
                                    
                                    Scene *s = Scene::create();
                                    s->addChild(layer);
                                    
                                    Director::getInstance()->replaceScene(s);
                                }
                            
                            }
                        }
                    }
                }
            }
        }
        
        if (noVandalSprayed)
        {
            std::string bubbles[] = {"bubbles/0.png", "bubbles/1.png", "bubbles/2.png"};
            
            std::string bubble = bubbles[(int)(CCRANDOM_0_1() * 3)];
            
            Sprite *bubbleSprite = Sprite::createWithSpriteFrameName(bubble);
            bubbleSprite->setPosition(location);
            bubbleSprite->setGlobalZOrder(2);
            
            _containerScene->addChild(bubbleSprite, 1);
            
            bubbleSprite->runAction(Sequence::create(FadeTo::create(2.0f, 100), CallFuncN::create([&](Node *node){
                node->removeFromParent();
            }), NULL));
        }
        
        _currentTouchLocation = location;
    }
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{

	if (_hasTutorial && (_tutorialState == 4 || _tutorialState == 8))
	{
		if (_tutorialState == 4)
		{
			_tutorialState = 5;
			_spriteRight->setVisible(true);
	    	_spriteRight->runAction(RepeatForever::create(Sequence::create(
	    			ScaleTo::create(0.5f, 1.1f),
	    			ScaleTo::create(0.5f, 1.f),
			NULL)));
		}
		else
		{
			_tutorialState = 9;
		}

	}

    _currentTouchLocation = Vec2::ZERO;
}

void GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    _currentTouchLocation = Vec2::ZERO;
}


#pragma mark - CCBMemberVariableAssigner functions

bool GameScene::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_background", cocos2d::Sprite*, _background);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerScene", cocos2d::Node*, _containerScene);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerTutorial", cocos2d::Node*, _containerTutorial);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_spriteLeft", cocos2d::Sprite*, _spriteLeft);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_spriteRight", cocos2d::Sprite*, _spriteRight);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_spriteRubber", cocos2d::Sprite*, _spriteRubber);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_hudUpper", cocos2d::Sprite*, _hudUpper);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_titleMoney", cocos2d::Sprite*, _titleMoney);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_titleTime", cocos2d::Sprite*, _titleTime);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_titleScore", cocos2d::Sprite*, _titleScore);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerMoney", cocos2d::Sprite*, _containerMoney);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelMoney", cocos2d::Label*, _labelMoney);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerTime", cocos2d::Sprite*, _containerTime);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTime", cocos2d::Label*, _labelTime);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerScore", cocos2d::Sprite*, _containerScore);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelScore", cocos2d::Label*, _labelScore);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_hudLower", cocos2d::Sprite*, _hudLower);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSpray", cocos2d::extension::ControlButton*, _buttonSpray);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPause", cocos2d::extension::ControlButton*, _buttonPause);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBrush", cocos2d::extension::ControlButton*, _buttonBrush);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler GameScene::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPause", GameScene::onPressPause);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSpray", GameScene::onPressSpray);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBrush", GameScene::onPressBrush);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void GameScene::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	_spriteLeft->setGlobalZOrder(5);
	_spriteRight->setGlobalZOrder(5);
	_spriteRubber->setGlobalZOrder(5);
}


#pragma mark - CCBAnimationManagerDelegate functions

void GameScene::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


