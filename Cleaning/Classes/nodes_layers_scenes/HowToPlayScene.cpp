#include "HowToPlayScene.h"

#include "PlayMenu.h"

#include "LevelSelectDialog.h"


USE_NS

HowToPlayScene *HowToPlayScene::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("HowToPlayScene", HowToPlaySceneLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<HowToPlayScene*>(ccbReader->readNodeGraphFromFile("HowToPlayScene.ccbi"));
}

HowToPlayScene::HowToPlayScene() : cocos2d::Layer()
, _content(NULL)
, _buttonLeft(NULL)
, _buttonRight(NULL)
, _buttonBack(NULL)

, m_currentPage(0)
, m_maxPages(6)
{
	_textureNamePlaceholder = "scenes/howto_%d.png";
}

HowToPlayScene::~HowToPlayScene()
{
	CC_SAFE_RELEASE(_content);
	CC_SAFE_RELEASE(_buttonLeft);
	CC_SAFE_RELEASE(_buttonRight);
	CC_SAFE_RELEASE(_buttonBack);
}

void HowToPlayScene::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    m_currentPage = 0;
    
    this->fixArrows();
}

void HowToPlayScene::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}

void HowToPlayScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void HowToPlayScene::fixArrows()
{
    if (m_currentPage == 0)
    {
        _buttonLeft->setEnabled(false);
    }
    else if (m_currentPage < m_maxPages - 1)
    {
        _buttonLeft->setEnabled(true);
        _buttonRight->setEnabled(true);
    }
    else
    {
        _buttonRight->setEnabled(false);
    }
    
    std::string texture = StringUtils::format(_textureNamePlaceholder.c_str(), m_currentPage + 1);
    
    _content->setTexture(texture);
}

void HowToPlayScene::setTextureNamePlaceHolder(std::string placeholder)
{
	_textureNamePlaceholder = placeholder;
}

void HowToPlayScene::setMaxPage(int pages)
{
	m_maxPages = pages;
}

void HowToPlayScene::onPressLeft(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
        m_currentPage = clampf(m_currentPage - 1, 0, m_maxPages - 1);
        fixArrows();
	}
}

void HowToPlayScene::onPressRight(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        m_currentPage = clampf(m_currentPage + 1, 0, m_maxPages - 1);
        fixArrows();
	}
}

void HowToPlayScene::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
		Director::getInstance()->popScene();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool HowToPlayScene::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_content", cocos2d::Sprite*, _content);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLeft", cocos2d::extension::ControlButton*, _buttonLeft);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRight", cocos2d::extension::ControlButton*, _buttonRight);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler HowToPlayScene::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressLeft", HowToPlayScene::onPressLeft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressRight", HowToPlayScene::onPressRight);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", HowToPlayScene::onPressBack);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void HowToPlayScene::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void HowToPlayScene::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


