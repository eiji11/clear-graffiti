/*
 * PhotoCaptureAndroid.cpp
 *
 *  Created on: 14 Jul, 2014
 *      Author: mac-user1
 */

#include "PhotoCaptureAndroid.h"
#include "cocos2d.h"
#include "ImageIOAndroid.h"
#include "utils/GeneralUtils.h"

USING_NS_CC;

jclass PhotoCaptureAndroid::jPhotoCaptureAndroidId = nullptr;
jmethodID PhotoCaptureAndroid::jPhotoCaptureAndroidCallDialog = nullptr;
jmethodID PhotoCaptureAndroid::jPhotoCaptureAndroidCallGallery = nullptr;
jmethodID PhotoCaptureAndroid::jPhotoCaptureAndroidCallCamera = nullptr;

PhotoCaptureProtocol* PhotoCaptureProtocol::getInstance()
{
	return PhotoCaptureAndroid::getInstance();
}

PhotoCaptureAndroid::~PhotoCaptureAndroid() {
}

PhotoCaptureAndroid* PhotoCaptureAndroid::getInstance()
{
	static PhotoCaptureAndroid *instance;
	if (instance == nullptr)
	{
		JNIEnv *env = JniHelper::getEnv();

		jPhotoCaptureAndroidId = (jclass)env->NewGlobalRef((jobject)(env->FindClass("com/spotcatstudio/photo_capture/PhotoCaptureAndroid")));
		jPhotoCaptureAndroidCallDialog = env->GetStaticMethodID(jPhotoCaptureAndroidId, "callDialog", "(Z)V");
		jPhotoCaptureAndroidCallGallery = env->GetStaticMethodID(jPhotoCaptureAndroidId, "callGallery", "()V");
		jPhotoCaptureAndroidCallCamera = env->GetStaticMethodID(jPhotoCaptureAndroidId, "callCamera", "()V");

		instance = new PhotoCaptureAndroid();
	}

	return instance;
}

void PhotoCaptureAndroid::callSelector(PhotoCaptureCallbackHandler *callback)
{
	JNIEnv *env = JniHelper::getEnv();

	env->CallStaticVoidMethod(jPhotoCaptureAndroidId, jPhotoCaptureAndroidCallDialog, _deletingEnabled);

    _callback = callback;
}

void PhotoCaptureAndroid::callGallery(PhotoCaptureCallbackHandler *callback)
{
	JNIEnv *env = JniHelper::getEnv();

	env->CallStaticVoidMethod(jPhotoCaptureAndroidId, jPhotoCaptureAndroidCallGallery);

    _callback = callback;
}

void PhotoCaptureAndroid::callCamera(PhotoCaptureCallbackHandler *callback)
{
	JNIEnv *env = JniHelper::getEnv();

	env->CallStaticVoidMethod(jPhotoCaptureAndroidId, jPhotoCaptureAndroidCallCamera);

    _callback = callback;
}

void PhotoCaptureAndroid::processImage(cocos2d::Sprite *sprite)
{
    _callback->onAcceptCallback(sprite);
}

void PhotoCaptureAndroid::deleteImage()
{
    bool success = ImageIOProtocol::getInstance()->deleteSprite();
    _callback->onDeleteCallback(success);
}

void PhotoCaptureAndroid::cancelSelector()
{
    _callback->onCancelCallback();
}

extern "C"{
	JNIEXPORT void JNICALL Java_com_spotcatstudio_photo_1capture_PhotoCaptureAndroid_onRemovePhoto (JNIEnv *env, jclass jclass)
	{
		PhotoCaptureProtocol::getInstance()->deleteImage();
	}

	JNIEXPORT void JNICALL Java_com_spotcatstudio_photo_1capture_PhotoCaptureAndroid_onCancel (JNIEnv *env, jclass jclass)
	{
		PhotoCaptureProtocol::getInstance()->cancelSelector();
	}

	JNIEXPORT void JNICALL Java_com_spotcatstudio_photo_1capture_PhotoCaptureAndroid_processImageFilePath (JNIEnv *env, jclass jclass, jstring selectedImagePath)
	{
		jboolean isCopy = true;
		static const char* a = JniHelper::getEnv()->GetStringUTFChars(selectedImagePath, &isCopy);
		CCLOG("IMAGE PATH: %s", a);
		Director::getInstance()->getScheduler()->schedule([&](float delta){
			CCLOG("IMAGE PATH 2: %s", a);
			Image *image = new Image();
			image->initWithImageFile(a);

			Sprite *sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(image, GeneralUtils::getInstance()->generateRandomString(10)));

			PhotoCaptureProtocol::getInstance()->processImage(sprite);
		}, Director::getInstance()->getRunningScene(), 0.0f, 1, 0.0f, false, GeneralUtils::getInstance()->generateRandomString(5));
	}

	JNIEXPORT void JNICALL Java_com_spotcatstudio_photo_1capture_PhotoCaptureAndroid_processImageData (JNIEnv *env, jclass jclass, jbyteArray imageData, jint imageSize)
	{
		jboolean isCopy = true;
		static signed char* a = JniHelper::getEnv()->GetByteArrayElements(imageData, &isCopy);
		static int l = imageSize;
		Director::getInstance()->getScheduler()->schedule([&](float delta){
			CCLOG("IMAGE PATH 2: %s", a);
			Image *image = new Image();
			image->initWithImageData((unsigned char*)a, l);

			Sprite *sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(image, GeneralUtils::getInstance()->generateRandomString(10)));

			PhotoCaptureProtocol::getInstance()->processImage(sprite);
		}, Director::getInstance()->getRunningScene(), 0.0f, 1, 0.0f, false, GeneralUtils::getInstance()->generateRandomString(5));
	}
}
