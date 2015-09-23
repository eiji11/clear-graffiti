/*
 * PhotoCaptureAndroid.h
 *
 *  Created on: 14 Jul, 2014
 *      Author: mac-user1
 */

#ifndef PHOTOCAPTUREANDROID_H_
#define PHOTOCAPTUREANDROID_H_

#include "protocols/PhotoCaptureProtocol.h"
#include "platform/android/jni/JniHelper.h"

class PhotoCaptureAndroid : public PhotoCaptureProtocol
{
public:
	static jclass jPhotoCaptureAndroidId;
	static jmethodID jPhotoCaptureAndroidCallDialog;
	static jmethodID jPhotoCaptureAndroidCallGallery;
	static jmethodID jPhotoCaptureAndroidCallCamera;

	virtual ~PhotoCaptureAndroid();

	static PhotoCaptureAndroid* getInstance();

    virtual void callSelector(PhotoCaptureCallbackHandler *callback);
    virtual void callGallery(PhotoCaptureCallbackHandler *callback);
    virtual void callCamera(PhotoCaptureCallbackHandler *callback);
    virtual void processImage(cocos2d::Sprite *sprite);
    virtual void deleteImage();
    virtual void cancelSelector();
};

#endif /* PHOTOCAPTUREANDROID_H_ */
