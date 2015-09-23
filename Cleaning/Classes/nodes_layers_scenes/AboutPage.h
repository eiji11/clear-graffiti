#ifndef __Cleaning__AboutPage__
#define __Cleaning__AboutPage__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"


class AboutPage : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(AboutPage);
	static AboutPage* createFromCCB();

	AboutPage();
	virtual ~AboutPage();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void setMessageSprite(std::string textureName);


private:
	CREATE_HANDLER(onPressLeft);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Sprite *_message;
	cocos2d::extension::ControlButton *_buttonLeft;

	cocos2d::extension::ScrollView *_scrollView;

};

CREATE_CLASS_LOADER(AboutPage, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__AboutPage__) */
