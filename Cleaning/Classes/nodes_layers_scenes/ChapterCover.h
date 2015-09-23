#ifndef __Cleaning__ChapterCover__
#define __Cleaning__ChapterCover__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class ChapterCover : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(ChapterCover);
	static ChapterCover* createFromCCB();

	ChapterCover();
	virtual ~ChapterCover();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void fixArrows();
    

private:
	CREATE_HANDLER(onPressChapter);
	CREATE_HANDLER(onPressLeft);
	CREATE_HANDLER(onPressRight);
	CREATE_HANDLER(onPressBack);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Sprite *_spriteChapter;
	cocos2d::extension::ControlButton *_buttonChapter;
	cocos2d::extension::ControlButton *_buttonLeft;
	cocos2d::extension::ControlButton *_buttonRight;
	cocos2d::Sprite *_titleChapter;
	cocos2d::extension::ControlButton *_buttonBack;
    
    int m_currentPage;
    int m_maxPages;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);

};

CREATE_CLASS_LOADER(ChapterCover, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__ChapterCover__) */
