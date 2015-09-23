#include "PreGame.h"

#include "GameScene.h"
#include "AlertBox.h"
#include "ShopDialog.h"
#include "managers_caches/ObserverManager.h"
#include "managers_caches/EventCustomMapped.h"
#include "utils/GeneralUtils.h"

#include "game/Player.h"


USE_NS

PreGame *PreGame::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PreGame", PreGameLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PreGame*>(ccbReader->readNodeGraphFromFile("PreGame.ccbi"));
}

PreGame::PreGame() : cocos2d::Layer()
, _sprayContainer1(NULL)
, _buttonSpray1(NULL)
, _sprayImage1(NULL)
, _sprayContainer2(NULL)
, _buttonSpray2(NULL)
, _sprayImage2(NULL)
, _sprayContainer3(NULL)
, _buttonSpray3(NULL)
, _sprayImage3(NULL)
, _brushContainer1(NULL)
, _buttonBrush1(NULL)
, _brushImage1(NULL)
, _brushContainer2(NULL)
, _buttonBrush2(NULL)
, _brushImage2(NULL)
, _brushContainer3(NULL)
, _buttonBrush3(NULL)
, _brushImage3(NULL)
, _containerMoney(NULL)
, _labelMoney(NULL)
, _buttonPlay(NULL)
, _buttonClose(NULL)
{

}

PreGame::~PreGame()
{
	CC_SAFE_RELEASE(_sprayContainer1);
	CC_SAFE_RELEASE(_buttonSpray1);
	CC_SAFE_RELEASE(_sprayImage1);
	CC_SAFE_RELEASE(_sprayContainer2);
	CC_SAFE_RELEASE(_buttonSpray2);
	CC_SAFE_RELEASE(_sprayImage2);
	CC_SAFE_RELEASE(_sprayContainer3);
	CC_SAFE_RELEASE(_buttonSpray3);
	CC_SAFE_RELEASE(_sprayImage3);
	CC_SAFE_RELEASE(_brushContainer1);
	CC_SAFE_RELEASE(_buttonBrush1);
	CC_SAFE_RELEASE(_brushImage1);
	CC_SAFE_RELEASE(_brushContainer2);
	CC_SAFE_RELEASE(_buttonBrush2);
	CC_SAFE_RELEASE(_brushImage2);
	CC_SAFE_RELEASE(_brushContainer3);
	CC_SAFE_RELEASE(_buttonBrush3);
	CC_SAFE_RELEASE(_brushImage3);
	CC_SAFE_RELEASE(_containerMoney);
	CC_SAFE_RELEASE(_labelMoney);
	CC_SAFE_RELEASE(_buttonPlay);
}

void PreGame::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    OBSERVE(this, EVENT_ITEM_SELECTED, ([&](EventCustom *event){
        EventCustomMapped *e = dynamic_cast<EventCustomMapped*>(event);
        
        ValueMap info = e->getInfo();
        int type = info.at("type").asInt();
        int index = info.at("index").asInt();
        float price = info.at("price").asFloat();
        
        if (price <= Player::getInstance()->getMoney())
        {
            CCLOG("TYPE: %d, INDEX: %d", type, index);
            UserDefault *ud = UserDefault::getInstance();
            if (type == 1)
            {
                ValueMap item;
                int id = info.at("id").asInt();
                item["type"] = id;
                item["charge"] = 100.f;
                
                _game->setSpray(index, item);

                Sprite *sprites[] = {_sprayImage1, _sprayImage2, _sprayImage3};
                ControlButton *buttons[] = {_buttonSpray1, _buttonSpray2, _buttonSpray3};
                auto sprite = sprites[index];
                auto button = buttons[index];
                button->setVisible(false);
                sprite->setSpriteFrame(StringUtils::format("equipments/spray-%d.png", id));
                sprite->setVisible(true);
                std::string key = StringUtils::format("bought-spray-%d", id);
                std::string indexed = StringUtils::format("spray-index-%d", index);
                ud->setBoolForKey(key.c_str(), true);
                ud->setIntegerForKey(indexed.c_str(), id);
            }
            else if (type == 2)
            {
                ValueMap item;
                int id = info.at("id").asInt();
                item["type"] = id;
                item["charge"] = 100.f;
                
                _game->setBrush(index, item);

                Sprite *sprites[] = {_brushImage1, _brushImage2, _brushImage3};
                ControlButton *buttons[] = {_buttonBrush1, _buttonBrush2, _buttonBrush3};
                auto sprite = sprites[index];
                auto button = buttons[index];
                button->setVisible(false);
                sprite->setSpriteFrame(StringUtils::format("equipments/brush-%d.png", id));
                sprite->setVisible(true);
                std::string key = StringUtils::format("bought-brush-%d", id);
                std::string indexed = StringUtils::format("brush-index-%d", index);
                ud->setBoolForKey(key.c_str(), true);
                ud->setIntegerForKey(indexed.c_str(), id);
            }
            ud->flush();
            
            Player::getInstance()->addMoney(-price);
            Player::getInstance()->save();
            
            _labelMoney->setString(StringUtils::format("%d", Player::getInstance()->getMoney()));
            
        }
        else
        {
        	AlertBox *a = AlertBox::createFromCCB();
        	Director::getInstance()->getRunningScene()->addChild(a, 10000);
        }
    }));
    
    UI_LOCK_MANAGER_INCREASE();
}

void PreGame::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UNOBSERVE(this);
    
    UI_LOCK_MANAGER_DECREASE();
}

void PreGame::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressClose(_buttonClose, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void PreGame::setGame(Game *game)
{
    _game = game;
    _game->retain();

	auto ud = UserDefault::getInstance();
	{
	Sprite *sprays[] = {_sprayImage1, _sprayImage2, _sprayImage3};
	Sprite *brushes[] = {_brushImage1, _brushImage2, _brushImage3};
	ControlButton *sButtons[] = {_buttonSpray1, _buttonSpray2, _buttonSpray3};
	ControlButton *bButtons[] = {_buttonBrush1, _buttonBrush2, _buttonBrush3};

	for (int x = 1; x < 3; x++)
	{
        std::string sIndex = StringUtils::format("spray-index-%d", x);
        int sItem = ud->getIntegerForKey(sIndex.c_str(), -1);
        if (sItem != -1)
        {
            ValueMap item;
            item["type"] = sItem;
            item["charge"] = 100.f;

        	_game->setSpray(x, item);
        }

        std::string bIndex = StringUtils::format("brush-index-%d", x);
        int bItem = ud->getIntegerForKey(bIndex.c_str(), -1);
        if (bItem != -1)
        {
            ValueMap item;
            item["type"] = bItem;
            item["charge"] = 100.f;

        	_game->setBrush(x, item);
        }
	}
	}
    
    _labelMoney->setString(StringUtils::format("%d", _game->getMoney()));
    
    Sprite *sprayImages[] = {_sprayImage1, _sprayImage2, _sprayImage3};
    ValueVector sprays = _game->getSprays();
    
    for (int x = 0; x < sprays.size(); x++) {
        ValueMap itemMap = sprays[x].asValueMap();
        sprayImages[x]->setVisible(itemMap.at("type").asInt() != 0);
        if (itemMap.at("type").asInt() != 0) {
            sprayImages[x]->setSpriteFrame(StringUtils::format("equipments/spray-%d.png", itemMap.at("type").asInt()));
        }
    }
    
    Sprite *brushImages[] = {_brushImage1, _brushImage2, _brushImage3};
    ValueVector brushes = _game->getBrushes();
    
    for (int x = 0; x < brushes.size(); x++) {
        ValueMap itemMap = brushes[x].asValueMap();
        brushImages[x]->setVisible(itemMap.at("type").asInt() != 0);
        if (itemMap.at("type").asInt() != 0) {
            brushImages[x]->setSpriteFrame(StringUtils::format("equipments/brush-%d.png", itemMap.at("type").asInt()));
        }
    }
}

void PreGame::onPressSpray(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
        int index = -1;
        if (sender == _buttonSpray1) {
            return;
        }
        else if (sender == _buttonSpray2) {
            index = 1;
        }
        else if (sender == _buttonSpray3) {
            index = 2;
        }
        
        ShopDialog *d = ShopDialog::createFromCCB();
        d->setGame(_game);
        d->setIndex(index);
        d->setType(1);
        
        Director::getInstance()->getRunningScene()->addChild(d, 1002);
	}
}

void PreGame::onPressBrush(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        int index = -1;
        if (sender == _buttonBrush1) {
            return;
        }
        else if (sender == _buttonBrush2) {
            index = 1;
        }
        else if (sender == _buttonBrush3) {
            index = 2;
        }
        
        
        ShopDialog *d = ShopDialog::createFromCCB();
        d->setGame(_game);
        d->setIndex(index);
        d->setType(2);
        
        Director::getInstance()->getRunningScene()->addChild(d, 1002);
	}
}

void PreGame::onPressPlay(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        GameScene *layer = GameScene::createFromCCB();
        layer->loadGame(_game);
        auto scene = Scene::create();
        scene->addChild(layer);
        Director::getInstance()->replaceScene(scene);
	}
}

void PreGame::onPressClose(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        this->removeFromParent();
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool PreGame::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprayContainer1", cocos2d::Sprite*, _sprayContainer1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSpray1", cocos2d::extension::ControlButton*, _buttonSpray1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprayImage1", cocos2d::Sprite*, _sprayImage1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprayContainer2", cocos2d::Sprite*, _sprayContainer2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSpray2", cocos2d::extension::ControlButton*, _buttonSpray2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprayImage2", cocos2d::Sprite*, _sprayImage2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprayContainer3", cocos2d::Sprite*, _sprayContainer3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSpray3", cocos2d::extension::ControlButton*, _buttonSpray3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprayImage3", cocos2d::Sprite*, _sprayImage3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_brushContainer1", cocos2d::Sprite*, _brushContainer1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBrush1", cocos2d::extension::ControlButton*, _buttonBrush1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_brushImage1", cocos2d::Sprite*, _brushImage1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_brushContainer2", cocos2d::Sprite*, _brushContainer2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBrush2", cocos2d::extension::ControlButton*, _buttonBrush2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_brushImage2", cocos2d::Sprite*, _brushImage2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_brushContainer3", cocos2d::Sprite*, _brushContainer3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBrush3", cocos2d::extension::ControlButton*, _buttonBrush3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_brushImage3", cocos2d::Sprite*, _brushImage3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerMoney", cocos2d::Sprite*, _containerMoney);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelMoney", cocos2d::Label*, _labelMoney);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPlay", cocos2d::extension::ControlButton*, _buttonPlay);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonClose", cocos2d::extension::ControlButton*, _buttonClose);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PreGame::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSpray", PreGame::onPressSpray);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBrush", PreGame::onPressBrush);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPlay", PreGame::onPressPlay);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressClose", PreGame::onPressClose);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PreGame::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	auto ud = UserDefault::getInstance();
	Sprite *sprays[] = {_sprayImage1, _sprayImage2, _sprayImage3};
	Sprite *brushes[] = {_brushImage1, _brushImage2, _brushImage3};
	ControlButton *sButtons[] = {_buttonSpray1, _buttonSpray2, _buttonSpray3};
	ControlButton *bButtons[] = {_buttonBrush1, _buttonBrush2, _buttonBrush3};

	for (int x = 1; x < 3; x++)
	{
        std::string sIndex = StringUtils::format("spray-index-%d", x);
        int sItem = ud->getIntegerForKey(sIndex.c_str(), -1);
        if (sItem != -1)
        {
            sprays[x]->setSpriteFrame(StringUtils::format("equipments/spray-%d.png", sItem));
            sButtons[x]->setVisible(false);
        }

        std::string bIndex = StringUtils::format("brush-index-%d", x);
        int bItem = ud->getIntegerForKey(bIndex.c_str(), -1);
        if (bItem != -1)
        {
        	brushes[x]->setSpriteFrame(StringUtils::format("equipments/brush-%d.png", bItem));
        	bButtons[x]->setVisible(false);
        }
	}
}


#pragma mark - CCBAnimationManagerDelegate functions

void PreGame::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


