#ifndef __Cleaning__HowToPlayScene__
#define __Cleaning__HowToPlayScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class HowToPlayScene : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(HowToPlayScene);
	static HowToPlayScene* createFromCCB();

	HowToPlayScene();
	virtual ~HowToPlayScene();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void fixArrows();
    
    void setTextureNamePlaceHolder(std::string placeholder);
    void setMaxPage(int pages);
    

private:
	CREATE_HANDLER(onPressLeft);
	CREATE_HANDLER(onPressRight);
	CREATE_HANDLER(onPressBack);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Sprite *_content;
	cocos2d::extension::ControlButton *_buttonLeft;
	cocos2d::extension::ControlButton *_buttonRight;
	cocos2d::extension::ControlButton *_buttonBack;

	std::string _textureNamePlaceholder;
    
    int m_currentPage;
    int m_maxPages;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);

};

CREATE_CLASS_LOADER(HowToPlayScene, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__HowToPlayScene__) */
