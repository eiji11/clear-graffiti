//
//  Player.cpp
//  Cleaning
//
//  Created by bibi-apple on 26/3/15.
//
//

#include "Player.h"

USING_NS_CC;

#define CHAPTER_COUNT 5
#define SAVE_FILE "clear_grafitti_player.plist"

Player *Player::getInstance()
{
    static Player* instance;
    if (instance == nullptr)
    {
        instance = new Player;
        instance->load();
    }
    return instance;
}

Player::Player()
{
}

bool Player::load()
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + SAVE_FILE;
    CCLOG("filePath: %s", filePath.c_str());
    ValueMap playerMap = FileUtils::getInstance()->getValueMapFromFile(filePath);
    
    if (!playerMap.empty())
    {
        _name = playerMap["name"].asString();
        _chapter = playerMap["chapter"].asInt();
        _level = playerMap["level"].asInt();
        _money = playerMap["money"].asInt();
        _totalPoints = playerMap["total_points"].asInt();
        
        _starsInfo = playerMap["stars_info"].asValueVector();
        
        for (ssize_t x = _starsInfo.size(); x < CHAPTER_COUNT; x++)
        {
            _starsInfo.push_back(Value(ValueVector()));
        }
    }
    else
    {
        CCLOG("CAN'T LOAD PLAYER INFO");
    
        _name = "PlayerName";
        _chapter = 1;
        _level = 1;
        _money = 500;
        _totalPoints = 0;
        
        for (ssize_t x = 0; x < CHAPTER_COUNT; x++)
        {
            _starsInfo.push_back(Value(ValueVector()));
        }
    }
    return false;
}

bool Player::save()
{
    ValueMap playerMap;
    
    playerMap["name"] = _name;
    playerMap["chapter"] = _chapter;
    playerMap["level"] = _level;
    playerMap["money"] = _money;
    playerMap["total_points"] = _totalPoints;
    
    playerMap["stars_info"] = _starsInfo;
    
    std::string filePath = FileUtils::getInstance()->getWritablePath() + SAVE_FILE;
    CCLOG("filePath: %s", filePath.c_str());
    return FileUtils::getInstance()->writeToFile(playerMap, filePath);
}

std::string Player::getName()
{
    return _name;
}

void Player::setName(std::string name)
{
    _name = name;
}

int Player::getChapter()
{
    return _chapter;
}

void Player::setChapter(int chapter)
{
    _chapter = chapter;
}

int Player::getLevel()
{
    return _level;
}

void Player::setLevel(int level)
{
    _level = level;
}

int Player::getMoney()
{
    return _money;
}

void Player::setMoney(int money)
{
    _money = money;
}

void Player::addMoney(int value)
{
    setMoney(_money + value);
}

int Player::getTotalPoints()
{
    return _totalPoints;
}

void Player::setTotalPoints(int totalPoints)
{
    _totalPoints = totalPoints;
}

void Player::addTotalPoints(int value)
{
    setTotalPoints(_totalPoints + value);
}

int Player::getStarForLevel(int chapter, int level)
{
    if (chapter <=_starsInfo.size())
    {
        ValueVector chapterLevels = _starsInfo[chapter - 1].asValueVector();
        if (level <= chapterLevels.size()) {
            return chapterLevels[level - 1].asInt();
        }
    }
    return -1;
}

void Player::setStarForLevel(int stars, int chapter, int level)
{
    if (chapter <= CHAPTER_COUNT) {
        for (ssize_t x = _starsInfo.size(); x < CHAPTER_COUNT; x++)
        {
            _starsInfo.push_back(Value(ValueVector()));
        }
        ValueVector chapterLevels = _starsInfo[chapter - 1].asValueVector();
        for (ssize_t x = chapterLevels.size(); x < 9; x++) {
            chapterLevels.push_back(Value(-1));
        }
        if (level <= chapterLevels.size()) {
            int currentStar = chapterLevels[level - 1].asInt();
            if (currentStar < stars) {
                chapterLevels[level - 1] = stars;
            }
        }
        _starsInfo[chapter - 1] = chapterLevels;
    }
}