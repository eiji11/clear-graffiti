//
//  PhotoCaptureProtocol.h
//  BaldBalancing
//
//  Created by bibi-apple on 13/6/14.
//
//

#ifndef BaldBalancing_PhotoCaptureProtocol_h
#define BaldBalancing_PhotoCaptureProtocol_h

#include <functional>

namespace cocos2d {
    class Sprite;
}

class PhotoCaptureCallbackHandler
{
public:
    std::function<void(cocos2d::Sprite *)> onAcceptCallback;
    std::function<void(bool success)> onDeleteCallback;
    std::function<void()> onCancelCallback;
};

class PhotoCaptureProtocol
{
protected:
    PhotoCaptureCallbackHandler *_callback;
    bool _deletingEnabled;
    
public:
    virtual ~PhotoCaptureProtocol(){}

    static PhotoCaptureProtocol* getInstance();
    
    inline void setDeletingEnable(bool enable)
    {
        _deletingEnabled = enable;
    };
    
    inline bool isDeletingEnabled()
    {
        return _deletingEnabled;
    }
    
    virtual void callSelector(PhotoCaptureCallbackHandler *callback) = 0;
    virtual void callGallery(PhotoCaptureCallbackHandler *callback) = 0;
    virtual void callCamera(PhotoCaptureCallbackHandler *callback) = 0;
    virtual void processImage(cocos2d::Sprite *sprite) = 0;
    virtual void deleteImage() = 0;
    virtual void cancelSelector() = 0;
};

#endif
