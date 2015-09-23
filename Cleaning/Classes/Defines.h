//
//  Defines.h
//  WaterQuiz
//
//  Created by bibi-apple on 26/12/14.
//
//

#ifndef WaterQuiz_Defines_h
#define WaterQuiz_Defines_h

#include "managers_caches/CBClassBuilderMacros.h"

#define DC(klazz, obj) \
dynamic_cast<klazz>(obj)

#define HAS_KEY(map, key) \
map.find(key) != map.end()

typedef enum TOUCH_TYPE
{
    TOUCH_SPRAY,
    TOUCH_BRUSH,
    TOUCH_NONE
} TouchType;


typedef std::vector<cocos2d::ValueMap> ValueMapList;

#define EVENT_ALERT_BOX_CLOSED "alert_box_closed"

#define EVENT_BEGIN_BRUSHING "begin_brushing"
#define EVENT_END_BRUSHING "end_brushing"

#define EVENT_ITEM_SELECTED "item_selected"
#define EVENT_VANDAL_FORCED_REMOVED "vandal_forced_removed"


#define FB_APP_ID "577545502348552"

#define IS_MUSIC_ENABLED UserDefault::getInstance()->getBoolForKey("music_enabled", true)
#define IS_SOUND_ENABLED UserDefault::getInstance()->getBoolForKey("sound_enabled", true)
#define PLAY_SOUND(sound_file) \
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(sound_file, false, 1.f, 0.f, 1.f)

#define BRUSH_RADIUS 7.5f

#endif
