//
//  ImageCaptureConfig.h
//  WaterQuiz
//
//  Created by bibi-apple on 13/2/15.
//
//

#ifndef WaterQuiz_ImageCaptureIncludes_h
#define WaterQuiz_ImageCaptureIncludes_h

#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "ImageIOIOS.h"
#include "PhotoCaptureIOS.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "ImageIOAndroid.h"
#include "PhotoCaptureAndroid.h"
#endif

#endif
