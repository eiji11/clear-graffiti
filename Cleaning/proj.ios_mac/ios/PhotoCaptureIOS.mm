//
//  PhotoCaptureIOS.cpp
//  BaldBalancing
//
//  Created by bibi-apple on 13/6/14.
//
//

#import "PhotoCaptureIOS.h"
#import <UIKit/UIKit.h>
#import <AssetsLibrary/AssetsLibrary.h>
#import "AppController.h"
#import "UIUtils.h"
#import "protocols/ImageIOProtocol.h"


USING_NS_CC;

@interface Delegator : NSObject<UIAlertViewDelegate, UINavigationControllerDelegate, UIImagePickerControllerDelegate>
+ (Delegator*) getInstance;

@property (copy) NSString *photoName;

@end

@implementation Delegator

+ (Delegator *)getInstance
{
    static Delegator *instance;
    if (instance == nil)
    {
        instance = [Delegator new];
    }
    
    return instance;
}

#pragma mark - UIAlertView methods

- (void) alertView:(UIAlertView *)alert clickedButtonAtIndex:(NSInteger)buttonIndex
{
    UIImagePickerController *uip = [UIImagePickerController new];
    if(buttonIndex == 0) {
        uip.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    }
    else if (buttonIndex == 1){
        uip.sourceType = UIImagePickerControllerSourceTypeCamera;
    }
    else if (buttonIndex == 2 && PhotoCaptureIOS::getInstance()->isDeletingEnabled())
    {
        PhotoCaptureIOS::getInstance()->deleteImage();
        return;
    }
    else{
        PhotoCaptureIOS::getInstance()->cancelSelector();
        return;
    }
    
    @try {
        uip.allowsEditing = NO;
        
        uip.delegate = [Delegator getInstance];
        
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:uip animated:YES completion:nil];
    }
    @catch (NSException * e) {
    }
    @finally {
        
    }
}


#pragma mark UIImagePickerControllerDelegate

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    
    UIUtils* uiUtil = [UIUtils sharedInstance];
    
    UIImage *pickedImage = [info objectForKey:UIImagePickerControllerOriginalImage];
    
    NSLog(@"PICKED IMAGE SIZE: %f, %f", pickedImage.size.width, pickedImage.size.height);
    
    UIImage *i = pickedImage;
    UIImage *resizedImage;
    
    float maxSize = 1536;
    
    if(i.size.width > i.size.height && i.size.width > maxSize){
        resizedImage = [uiUtil scaleImage:i toSize:CGSizeMake(maxSize, (maxSize / i.size.width) * i.size.height)];
    }
    else if(i.size.height > i.size.width && i.size.height > maxSize){
        resizedImage = [uiUtil scaleImage:i toSize:CGSizeMake((maxSize / i.size.height) * i.size.width, maxSize)];
    }
    else
    {
        resizedImage = i;
    }
    
    NSURL *refURL = [info valueForKey:UIImagePickerControllerReferenceURL];
    
    ALAssetsLibraryAssetForURLResultBlock resultblock = ^(ALAsset *imageAsset)
    {
        ALAssetRepresentation *imageRep = [imageAsset defaultRepresentation];
        _photoName =  imageRep.filename;
    };
    
    ALAssetsLibrary* assetslibrary = [[ALAssetsLibrary alloc] init];
    [assetslibrary assetForURL:refURL resultBlock:resultblock failureBlock:nil];
    
//    UIImage *imageForSprite = [self getEdgesOfImage:resizedImage];
    
    Sprite* sprite = [uiUtil uiImageToSprite:(resizedImage)];
    
    PhotoCaptureProtocol::getInstance()->processImage(sprite);
    
    
    [[UIApplication sharedApplication].keyWindow.rootViewController dismissViewControllerAnimated:YES completion:nil];
}

-(void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    
    PhotoCaptureProtocol::getInstance()->cancelSelector();

    [[UIApplication sharedApplication].keyWindow.rootViewController dismissViewControllerAnimated:YES completion:nil];
}

@end

PhotoCaptureProtocol* PhotoCaptureProtocol::getInstance()
{
    return PhotoCaptureIOS::getInstance();
}

PhotoCaptureIOS* PhotoCaptureIOS::getInstance()
{
    static PhotoCaptureIOS* instance;
    if (instance == NULL)
    {
        instance = new PhotoCaptureIOS();
    }
    
    return instance;
}

void PhotoCaptureIOS::callSelector(PhotoCaptureCallbackHandler *callback)
{
    UIAlertView* dialog = [[UIAlertView alloc] init];
    [dialog setDelegate:[Delegator getInstance]];
    [dialog setTitle:@"Select Photo"];
    [dialog setMessage:@"Where would you like to get the photo?"];
    [dialog addButtonWithTitle:@"Photo Album"];
    [dialog addButtonWithTitle:@"Camera"];
    if (_deletingEnabled)
    {
        [dialog addButtonWithTitle:@"Remove Photo"];
    }
    [dialog addButtonWithTitle:@"Cancel"];
    [dialog show];
    
    _callback = callback;
}

void PhotoCaptureIOS::callGallery(PhotoCaptureCallbackHandler *callback)
{
    UIImagePickerController *uip = [UIImagePickerController new];
    uip.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    
    @try {
        uip.allowsEditing = NO;
        
        uip.delegate = [Delegator getInstance];
        
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:uip animated:YES completion:nil];
    }
    @catch (NSException * e) {
    }
    @finally {
        
    }
    
    _callback = callback;
}

void PhotoCaptureIOS::callCamera(PhotoCaptureCallbackHandler *callback)
{
    UIImagePickerController *uip = [UIImagePickerController new];
    uip.sourceType = UIImagePickerControllerSourceTypeCamera;
    
    @try {
        uip.allowsEditing = NO;
        
        uip.delegate = [Delegator getInstance];
        
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:uip animated:YES completion:nil];
    }
    @catch (NSException * e) {
    }
    @finally {
        
    }
    
    _callback = callback;
}

void PhotoCaptureIOS::deleteImage()
{
    bool success = ImageIOProtocol::getInstance()->deleteSprite();
    if (_callback != nullptr && _callback->onDeleteCallback != nullptr)
    {
        _callback->onDeleteCallback(success);
    }
}

void PhotoCaptureIOS::processImage(cocos2d::Sprite *sprite)
{
    if (_callback != nullptr && _callback->onAcceptCallback != nullptr)
    {
        _callback->onAcceptCallback(sprite);
    }
}

void PhotoCaptureIOS::cancelSelector()
{
    if (_callback != nullptr && _callback->onCancelCallback != nullptr)
    {
        _callback->onCancelCallback();
    }
}