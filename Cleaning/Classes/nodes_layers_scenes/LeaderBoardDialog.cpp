#include "LeaderBoardDialog.h"

#include "LeaderBoardDialogEntry.h"

#include "external/json/rapidjson.h"
#include "external/json/document.h"

#include "plugin/protocols/include/FacebookAgent.h"

#include "game/Player.h"

#include <algorithm>


USE_NS
using namespace plugin;

LeaderBoardDialog *LeaderBoardDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("LeaderBoardDialog", LeaderBoardDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<LeaderBoardDialog*>(ccbReader->readNodeGraphFromFile("LeaderBoardDialog.ccbi"));
}

LeaderBoardDialog::LeaderBoardDialog() : cocos2d::Layer()
, _containerTableView(NULL)
, _buttonBack(NULL)
{

}

LeaderBoardDialog::~LeaderBoardDialog()
{
	CC_SAFE_RELEASE(_containerTableView);
	CC_SAFE_RELEASE(_buttonBack);
}

void LeaderBoardDialog::onEnter()
{
	cocos2d::Layer::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	this->setKeyboardEnabled(true);

	if (FacebookAgent::getInstance()->isLoggedIn())
	{
		CCLOG("LOGGED IN ALREADY");
		this->loadItems();
	}
	else
	{
		CCLOG("NOT YET LOGGED IN");
		std::string permissions = "publish_actions,user_friends";
		FacebookAgent::getInstance()->login(permissions, [&](int ret, std::string &jsonStr){
			CCLOG("RET: %d, %s", ret, jsonStr.c_str());
			if (ret == 0)
			{
				this->loadItems();
			}
		});
	}

    UI_LOCK_MANAGER_INCREASE();
}

void LeaderBoardDialog::onExit()
{
	cocos2d::Layer::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    UI_LOCK_MANAGER_DECREASE();
}

void LeaderBoardDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !IS_LOCKED)
	{
		this->runAction(CallFunc::create([&](){
			this->onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
		}));
	}
}

void LeaderBoardDialog::loadItems()
{
	FacebookAgent::FBInfo params;
	params["score"] = StringUtils::format("%d", Player::getInstance()->getTotalPoints());

	std::string path = "me/scores";
	FacebookAgent::getInstance()->api(path, FacebookAgent::HttpMethod::Post, params, [&](int result, std::string &jsonString){
		if (result == 0)
		{
			FacebookAgent::FBInfo params2;

			std::string path2 = "577545502348552/scores";

			FacebookAgent::getInstance()->api(path2, FacebookAgent::HttpMethod::Get, params2, [&](int result, std::string &jsonString){
				if (result == 0)
				{
					rapidjson::Document json;
					json.Parse<0>(jsonString.c_str());
					if (!json.HasParseError())
					{
						rapidjson::Value &data = json["data"];

						_items.clear();

						for (rapidjson::SizeType i = 0; i < data.Size(); i++)
						{
							const rapidjson::Value& entry = data[i];
							const rapidjson::Value& scoreValue = entry["score"];

							int score = scoreValue.GetInt();
							const rapidjson::Value& userInfo = entry["user"];
							const rapidjson::Value& nameValue = userInfo["name"];
							std::string name = nameValue.GetString();

							ValueMap map;
							map["score"] = score;
							map["name"] = name;

							_items.push_back(Value(map));

						}

						std::reverse(_items.begin(), _items.end());

						ValueMap leaderBoardMap;
						leaderBoardMap["data"] = _items;

						std::string leaderBoardFilePath = FileUtils::getInstance()->getWritablePath() + "leaderboard_map";
						FileUtils::getInstance()->writeToFile(leaderBoardMap, leaderBoardFilePath);
					}
					else
					{
						this->loadSavedItems();
					}
				}
				else
				{
					this->loadSavedItems();
				}
				this->runAction(CallFunc::create([&](){
					_tableView->reloadData();
				}));
			});
		}
		else
		{
			loadSavedItems();
		}
	});
}

void LeaderBoardDialog::loadSavedItems()
{
	_items.clear();

	std::string leaderBoardFilePath = FileUtils::getInstance()->getWritablePath() + "leaderboard_map";
	if (FileUtils::getInstance()->isFileExist(leaderBoardFilePath))
	{
		ValueMap leaderBoardMap = FileUtils::getInstance()->getValueMapFromFile(leaderBoardFilePath);
		_items = leaderBoardMap["data"].asValueVector();
	}
	else
	{
		ValueMap map;
		map["score"] = Player::getInstance()->getTotalPoints();
		map["name"] = Player::getInstance()->getName();

		_items.push_back(Value(map));
	}

	this->runAction(CallFunc::create([&](){
		_tableView->reloadData();
	}));
}

void LeaderBoardDialog::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		this->removeFromParent();
	}
}


#pragma mark - TableView Methods

Size LeaderBoardDialog::cellSizeForTable(cocos2d::extension::TableView *table)
{
    static cocos2d::Size CELL_SIZE = Size(242, 58);
    
    return CELL_SIZE;
}

TableViewCell *LeaderBoardDialog::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = TableViewCell::create();
    ValueMap map = _items[idx].asValueMap();
    CCLOG("loaded map");
    LeaderBoardDialogEntry *entry = LeaderBoardDialogEntry::createFromCCB();
    entry->setInfo((int)((_items.size() - idx)), map);
    CCLOG("entry setup");

    cell->addChild(entry);
    
    return cell;
}

ssize_t LeaderBoardDialog::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return _items.size();
}

#pragma mark - CCBMemberVariableAssigner functions

bool LeaderBoardDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerTableView", cocos2d::Node*, _containerTableView);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler LeaderBoardDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", LeaderBoardDialog::onPressBack);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void LeaderBoardDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    
    _tableView = TableView::create(this, _containerTableView->getContentSize());
    
    _containerTableView->addChild(_tableView);
}


#pragma mark - CCBAnimationManagerDelegate functions

void LeaderBoardDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


