#include "ChapterCover.h"

#include "PlayMenu.h"

#include "LevelSelectDialog.h"


USE_NS

ChapterCover *ChapterCover::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("ChapterCover", ChapterCoverLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<ChapterCover*>(ccbReader->readNodeGraphFromFile("ChapterCover.ccbi"));
}

ChapterCover::ChapterCover() : cocos2d::Layer()
, _spriteChapter(NULL)
, _buttonChapter(NULL)
, _buttonLeft(NULL)
, _buttonRight(NULL)
, _titleChapter(NULL)
, _buttonBack(NULL)

, m_currentPage(0)
, m_maxPages(5)
{

}

ChapterCover::~ChapterCover()
{
	CC_SAFE_RELEASE(_spriteChapter);
	CC_SAFE_RELEASE(_buttonChapter);
	CC_SAFE_RELEASE(_buttonLeft);
	CC_SAFE_RELEASE(_buttonRight);
	CC_SAFE_RELEASE(_titleChapter);
	CC_SAFE_RELEASE(_buttonBack);
}

void ChapterCover::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);
    
    m_currentPage = 0;
    m_maxPages = 5;
    
    this->fixArrows();
}

void ChapterCover::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}

void ChapterCover::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void ChapterCover::fixArrows()
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
    
    std::string cover = StringUtils::format("story_mode_bg/chapter_%d.png", m_currentPage + 1);
    std::string title = StringUtils::format("story_mode_bg/chapter_%d_title.png", m_currentPage + 1);
    
    _spriteChapter->setTexture(cover);
    _titleChapter->setTexture(title);
}

void ChapterCover::onPressChapter(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
        if (m_currentPage + 1 < 5) {
            LevelSelectDialog *d = LevelSelectDialog::createFromCCB();
            d->setChapter(m_currentPage + 1);
            
            Director::getInstance()->getRunningScene()->addChild(d, 1000);
        }
	}
}

void ChapterCover::onPressLeft(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
        m_currentPage = clampf(m_currentPage - 1, 0, m_maxPages - 1);
        fixArrows();
	}
}

void ChapterCover::onPressRight(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        m_currentPage = clampf(m_currentPage + 1, 0, m_maxPages - 1);
        fixArrows();
	}
}

void ChapterCover::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
        PlayMenu *l = PlayMenu::createFromCCB();
        Scene *scene = Scene::create();
        scene->addChild(l);
        Director::getInstance()->replaceScene(scene);
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool ChapterCover::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_spriteChapter", cocos2d::Sprite*, _spriteChapter);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonChapter", cocos2d::extension::ControlButton*, _buttonChapter);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLeft", cocos2d::extension::ControlButton*, _buttonLeft);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRight", cocos2d::extension::ControlButton*, _buttonRight);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_titleChapter", cocos2d::Sprite*, _titleChapter);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler ChapterCover::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressChapter", ChapterCover::onPressChapter);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressLeft", ChapterCover::onPressLeft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressRight", ChapterCover::onPressRight);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", ChapterCover::onPressBack);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void ChapterCover::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void ChapterCover::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


