//
//  GeneralUtils.cpp
//  BaldBalancing
//
//  Created by bibi-apple on 25/6/14.
//
//

#include "GeneralUtils.h"

USING_NS_CC;

using namespace std;

GeneralUtils* GeneralUtils::getInstance()
{
    static GeneralUtils* instance;
    if (instance == NULL)
    {
        instance = new GeneralUtils();
    }
    
    return instance;
}

std::string GeneralUtils::formatTime(float time)
{
    int minutes = time / 60;
    
    float secondsRemainder = fmodf(time, 60.0f);
    int seconds = secondsRemainder;
    int milliSeconds = fmodf(secondsRemainder, 1.0f) * 100;
    
    return StringUtils::format("%02d:%02d:%02d", minutes, seconds, milliSeconds);
}

ControllerType GeneralUtils::getControllerType()
{
    int controllerTypeInt = UserDefault::getInstance()->getIntegerForKey("control_type", 1);
    
    ControllerType controllerType = E_CONTROLLER_UNKNOWN;
    
    if (controllerTypeInt == 1)
    {
        controllerType = E_CONTROLLER_TOUCH;
    }
    else if (controllerTypeInt == 2)
    {
        controllerType = E_CONTROLLER_TILT;
    }
    
    return controllerType;
}

void GeneralUtils::setControllerType(ControllerType controllerType)
{
    int controllerTypeInt = 0;
    
    if (controllerType == E_CONTROLLER_TOUCH)
    {
        controllerTypeInt = 1;
    }
    else if (controllerType == E_CONTROLLER_TILT)
    {
        controllerTypeInt = 2;
    }
    else
    {
        return;
    }
    
    UserDefault *ud = UserDefault::getInstance();
    
    ud->setIntegerForKey("control_type", controllerTypeInt);
    ud->flush();
}

string GeneralUtils::generateRandomString(const int len) {
	string s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return s;
}

void GeneralUtils::setGlobalZOrder(Node *node, int zOrder)
{
    node->setGlobalZOrder(zOrder);
    
    Vector<Node*>children = node->getChildren();
    for (Node *child : children) {
        setGlobalZOrder(child, zOrder);
    }
}