//
//  AssortedUtils.h
//  WaterQuiz
//
//  Created by bibi-apple on 15/1/15.
//
//

#ifndef __WaterQuiz__AssortedUtils__
#define __WaterQuiz__AssortedUtils__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#include "Defines.h"

class AssortedUtils
{
public:
    static void fixFontSize(cocos2d::Label* label);
    
    static std::string makeSpace(int spaces);
    static std::string readValue(cocos2d::Value value, int spaces);
};

#endif /* defined(__WaterQuiz__AssortedUtils__) */
