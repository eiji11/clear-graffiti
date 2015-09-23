#ifndef __Cleaning__LeaderBoardDialogEntry__
#define __Cleaning__LeaderBoardDialogEntry__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"


class LeaderBoardDialogEntry : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(LeaderBoardDialogEntry);
	static LeaderBoardDialogEntry* createFromCCB();

	LeaderBoardDialogEntry();
	virtual ~LeaderBoardDialogEntry();

	virtual void onEnter();
	virtual void onExit();
    
    void setInfo(int rank, cocos2d::ValueMap info);


private:


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Label *_labelRank;
	cocos2d::Label *_labelScore;
	cocos2d::Label *_labelName;
};

CREATE_CLASS_LOADER(LeaderBoardDialogEntry, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__LeaderBoardDialogEntry__) */
