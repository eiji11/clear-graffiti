//
//  Player.h
//  Cleaning
//
//  Created by bibi-apple on 26/3/15.
//
//

#ifndef __Cleaning__Player__
#define __Cleaning__Player__

#include "cocos2d.h"

class Player
{
public:
    static Player *getInstance();
    
    Player();
    
    bool load();
    bool save();
    
    std::string getName();
    void setName(std::string name);
    
    int getChapter();
    void setChapter(int chapter);
    
    int getLevel();
    void setLevel(int level);
    
    int getMoney();
    void setMoney(int money);
    void addMoney(int value);
    
    int getTotalPoints();
    void setTotalPoints(int points);
    void addTotalPoints(int value);
    
    int getStarForLevel(int chapter, int level);
    void setStarForLevel(int stars, int chapter, int level);
    
private:
    std::string _name;
    
    int _chapter;
    int _level;
    int _money;
    int _totalPoints;
    
    
    cocos2d::ValueVector _starsInfo;
    
};

#endif /* defined(__Cleaning__Player__) */
