#ifndef __Cleaning__GameScene__
#define __Cleaning__GameScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"

#include "game/Game.h"
#include "custom_nodes/VandalNode.h"

#include "nodes_layers_scenes/AlertBox.h"


class GameScene : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	static bool SHOW_HOW_TO_PLAY;

	CREATE_FUNC(GameScene);
	static GameScene* createFromCCB();

	GameScene();
	virtual ~GameScene();

	virtual void onEnter();
	virtual void onExit();

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void updateTimer(float delta);

    
    void loadGame(Game *game);
    void addVandal(VandalNode *vandal);
    void removeVandal(VandalNode *vandal);
    void clearVandals();
    
private:
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
	CREATE_HANDLER(onPressPause);
	CREATE_HANDLER(onPressSpray);
	CREATE_HANDLER(onPressBrush);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);
    
    void highlight();
    void unhighlight();
    
    void hideVandals();
    void showVandals();


private:
    cocos2d::Sprite *_background;
    cocos2d::Node *_containerScene;
    cocos2d::Node *_containerTutorial;
    cocos2d::Sprite *_spriteLeft;
    cocos2d::Sprite *_spriteRight;
    cocos2d::Sprite *_spriteRubber;
    cocos2d::Sprite *_hudUpper;
    cocos2d::Sprite *_titleMoney;
    cocos2d::Sprite *_titleTime;
    cocos2d::Sprite *_titleScore;
    cocos2d::Sprite *_containerMoney;
    cocos2d::Label *_labelMoney;
    cocos2d::Sprite *_containerTime;
    cocos2d::Label *_labelTime;
    cocos2d::Sprite *_containerScore;
    cocos2d::Label *_labelScore;
    cocos2d::Sprite *_hudLower;
    cocos2d::extension::ControlButton *_buttonSpray;
    cocos2d::extension::ControlButton *_buttonPause;
    cocos2d::extension::ControlButton *_buttonBrush;
    
    Game *_game;
    cocos2d::Vector<VandalNode*> _vandals;
    
    bool _hasTutorial;
    int _tutorialState;

    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);
    
    cocos2d::Vec2 _currentTouchLocation;
    
    TouchType _touchType;
    cocos2d::ValueVector _sprayTypes;
    cocos2d::ValueVector _brushTypes;
    
    int _sprayTypeIndex;
    int _brushTypeIndex;
    
    bool _isPaused;
    bool _isGameOver;
    
    bool _isHighlighting = false;
    int _highlightTimer = 5.0f;



};

CREATE_CLASS_LOADER(GameScene, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__GameScene__) */
