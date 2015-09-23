//
//  GeneralUtils.h
//  BaldBalancing
//
//  Created by bibi-apple on 25/6/14.
//
//

#ifndef __BaldBalancing__GeneralUtils__
#define __BaldBalancing__GeneralUtils__

#include "cocos2d.h"

#define FB_PERMISSIONS {"user_friends"}


typedef enum E_CONTROLLER_TYPE
{
    E_CONTROLLER_TILT,
    E_CONTROLLER_TOUCH,
    E_CONTROLLER_UNKNOWN
}ControllerType;

class GeneralUtils
{
protected:
    
public:
    static GeneralUtils* getInstance();
    
    std::string formatTime(float time);
    ControllerType getControllerType();
    void setControllerType(ControllerType controllerType);
    std::string generateRandomString(const int len);
    
    void setGlobalZOrder(cocos2d::Node *node, int zOrder);
};

#endif /* defined(__BaldBalancing__GeneralUtils__) */
