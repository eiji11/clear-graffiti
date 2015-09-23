#ifndef __Cleaning__ComicsScene__
#define __Cleaning__ComicsScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "game/Game.h"


class ComicsScene : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(ComicsScene);
	static ComicsScene* createFromCCB();

	ComicsScene();
	virtual ~ComicsScene();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void setGame(Game *game);

private:
	CREATE_HANDLER(onPressPlay);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Sprite *_spriteComics;
	cocos2d::extension::ControlButton *_buttonPlay;


	Game *_game;
	bool _triviaMode;

};

CREATE_CLASS_LOADER(ComicsScene, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__ComicsScene__) */
