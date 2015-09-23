//
//  PhotoCaptureIOS.h
//  BaldBalancing
//
//  Created by bibi-apple on 13/6/14.
//
//

#ifndef __BaldBalancing__PhotoCaptureIOS__
#define __BaldBalancing__PhotoCaptureIOS__

#import "protocols/PhotoCaptureProtocol.h"
#import "cocos2d.h"

class PhotoCaptureIOS : public PhotoCaptureProtocol
{
public:
    static PhotoCaptureIOS* getInstance();
    
    virtual void callSelector(PhotoCaptureCallbackHandler *callback);
    virtual void callGallery(PhotoCaptureCallbackHandler *callback);
    virtual void callCamera(PhotoCaptureCallbackHandler *callback);
    virtual void processImage(cocos2d::Sprite *sprite);
    virtual void deleteImage();
    virtual void cancelSelector();
    
};

#endif /* defined(__BaldBalancing__PhotoCaptureIOS__) */
