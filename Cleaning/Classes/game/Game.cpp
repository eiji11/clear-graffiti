//
//  Game.cpp
//  Cleaning
//
//  Created by bibi-apple on 2/3/15.
//
//

#include "Game.h"

#include "Defines.h"

#include "Player.h"

USING_NS_CC;

Game *Game::create(int chapter, int level)
{
    Game *retVal = new Game();
    if (retVal->init(chapter, level))
    {
        retVal->autorelease();
        return retVal;
    }
    delete retVal;
    retVal = nullptr;
    return nullptr;
}

Game::Game() : Ref()
, _time(30)
, _startTime(30)
, _timeAttacksFinished(0)
, _scoreGained(0)
, _moneyGained(0)
, _isTimeAttack(false)
{
    
}

Game::~Game()
{
    
}

bool Game::init(int chapter, int level)
{
    try {
        ValueVector chapterList = FileUtils::getInstance()->getValueVectorFromFile("games.plist");
        
        ValueVector levelList = chapterList.at(chapter - 1).asValueVector();
        
        ValueMap vm = levelList.at(level - 1).asValueMap();
        _rawInfo = vm;
        
        if (!_rawInfo.empty()) {
            _chapter = _rawInfo.at("chapter").asInt();
            _level = _rawInfo.at("level").asInt();
            
            _backgroundFile = _rawInfo.at("background").asString();
            
            ValueVector times = _rawInfo.at("time_limit").asValueVector();
            for (Value timeValue : times)
            {
                _times.push_back(timeValue.asInt());
            }
            
            _startTime = _time = _times.back();
            
            ValueVector vandalsVector = _rawInfo.at("vandals").asValueVector();
            for (Value vandalValue : vandalsVector)
            {
                ValueMap vandalMap = vandalValue.asValueMap();
                
                Vandal *vandal = Vandal::create(vandalMap);
                if (vandal != nullptr) {
                    _vandals.pushBack(vandal);
                }
            }
            
            ValueMap spray1;
            spray1["type"] = 1;
            spray1["charge"] = 100.f;
            _sprays.push_back(Value(spray1));
            
            ValueMap spray2;
            spray2["type"] = 0;
            spray2["charge"] = 0.f;
            _sprays.push_back(Value(spray2));
            
            ValueMap spray3;
            spray3["type"] = 0;
            spray3["charge"] = 0.f;
            _sprays.push_back(Value(spray3));
            
            
            ValueMap brush1;
            brush1["type"] = 1;
            brush1["charge"] = 100.f;
            _brushes.push_back(Value(brush1));
            
            ValueMap brush2;
            brush2["type"] = 0;
            brush2["charge"] = 0.f;
            _brushes.push_back(Value(brush2));
            
            ValueMap brush3;
            brush3["type"] = 0;
            brush3["charge"] = 0.f;
            _brushes.push_back(Value(brush3));
            
        }
    } catch (...) {
        _rawInfo.clear();
    }
    
    return !_rawInfo.empty();
}

int Game::getChapter()
{
    return _rawInfo.at("chapter").asInt();
}

int Game::getLevel()
{
    return _rawInfo.at("level").asInt();
}

std::string Game::getBackgroundFile()
{
    return _rawInfo.at("background").asString();
}

Vector<Vandal *> Game::getVandals()
{
    return _vandals;
}

void Game::addVandal(Vandal *vandal)
{
    if (!_vandals.contains(vandal))
    {
        _vandals.pushBack(vandal);
    }
}

int Game::getScore()
{
    return Player::getInstance()->getTotalPoints();
}

void Game::setScore(int score)
{
    Player::getInstance()->setTotalPoints(score);
}

void Game::addScore(int value)
{
	_scoreGained += value;
    setScore(getScore() + value);
}

int Game::getScoreGained()
{
	return _scoreGained;
}

int Game::getTime()
{
    return _time;
}

void Game::setTime(int time)
{
    _time = time;
}

void Game::addTime(int value)
{
    setTime(_time + value);
}

int Game::getTimeLimit(int index)
{
    return _times[index];
}

int Game::getStartTime()
{
    return _startTime;
}

void Game::setStartTime(int startTime)
{
    _startTime = startTime;
}

int Game::getMoney()
{
    return Player::getInstance()->getMoney();
}

void Game::setMoney(int money)
{
    Player::getInstance()->setMoney(money);
}

void Game::addMoney(int value)
{
	_moneyGained += value;
    setMoney(getMoney() + value);
}

int Game::getMoneyGained()
{
	return _moneyGained;
}
