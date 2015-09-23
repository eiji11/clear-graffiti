//
//  Game.h
//  Cleaning
//
//  Created by bibi-apple on 2/3/15.
//
//

#ifndef __Cleaning__Game__
#define __Cleaning__Game__

#include "cocos2d.h"

#include "Vandal.h"


class Game : public cocos2d::Ref
{
public:
    static Game* create(int chapter, int level);
    
    Game();
    ~Game();
    
    bool init(int chapter, int level);
    
    int getChapter();
    int getLevel();
    
    std::string getBackgroundFile();
    
    cocos2d::Vector<Vandal*> getVandals();
    void addVandal(Vandal *vandal);
    
    int getScore();
    void setScore(int score);
    void addScore(int value);
    int getScoreGained();
    
    int getTime();
    void setTime(int time);
    void addTime(int value = -1);
    
    int getTimeLimit(int index);
    
    int getStartTime();
    void setStartTime(int startTime);
    
    int getMoney();
    void setMoney(int money);
    void addMoney(int value);
    int getMoneyGained();
    
    cocos2d::ValueVector getSprays()
    {
        return _sprays;
    }
    
    cocos2d::ValueVector getBrushes()
    {
        return _brushes;
    }
    
    void setSpray(int index, cocos2d::ValueMap sprayMap)
    {
        _sprays[index] = cocos2d::Value(sprayMap);
    }
    
    void setBrush(int index, cocos2d::ValueMap brushMap)
    {
        _brushes[index] = cocos2d::Value(brushMap);
    }
    
    bool isTimeAttack()
    {
        return _isTimeAttack;
    }
    
    void setTimeAttack(bool t)
    {
        _isTimeAttack = t;
    }
    
    void setTimeAttacksFinished(int times)
    {
        _timeAttacksFinished = times;
    }
    
    int getTimeAttacksFinished()
    {
        return _timeAttacksFinished;
    }

private:
    cocos2d::ValueMap _rawInfo;
    int _chapter;
    int _level;
    std::string _backgroundFile;
    
    int _moneyGained;
    int _scoreGained;

    cocos2d::Vector<Vandal*> _vandals;
    int _time;
    std::vector<int> _times;
    int _startTime;
    
    cocos2d::ValueVector _sprays;
    cocos2d::ValueVector _brushes;
    
    bool _isTimeAttack;
    int _timeAttacksFinished;
    
};

#endif /* defined(__Cleaning__Game__) */
