#include "AppDelegate.h"
#include "nodes_layers_scenes/GameScene.h"
#include "nodes_layers_scenes/MainMenu.h"


USING_NS_CC;
USING_NS_CC_EXT;

using namespace spritebuilder;

#define PHYSIC_FACTOR 32

const char* CCSetupPixelFormat = "CCSetupPixelFormat";
const char* CCSetupScreenMode = "CCSetupScreenMode";
const char* CCSetupScreenOrientation = "CCSetupScreenOrientation";
const char* CCSetupAnimationInterval = "CCSetupAnimationInterval";
const char* CCSetupFixedUpdateInterval = "CCSetupFixedUpdateInterval";
const char* CCSetupShowDebugStats = "CCSetupShowDebugStats";
const char* CCSetupTabletScale2X = "CCSetupTabletScale2X";

const char* CCSetupDepthFormat = "CCSetupDepthFormat";
const char* CCSetupPreserveBackbuffer = "CCSetupPreserveBackbuffer";
const char* CCSetupMultiSampling = "CCSetupMultiSampling";
const char* CCSetupNumberOfSamples = "CCSetupNumberOfSamples";

const char* CCScreenOrientationLandscape = "CCScreenOrientationLandscape";
const char* CCScreenOrientationPortrait = "CCScreenOrientationPortrait";

const char* CCScreenModeFlexible = "CCScreenModeFlexible";
const char* CCScreenModeFixed = "CCScreenModeFixed";

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        glview->setFrameSize(320, 568);
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    Size size = director->getWinSize();
    
    float scaleFactor = size.height / 568.0f;
    glview->setDesignResolutionSize(size.width / scaleFactor, 568.0f, ResolutionPolicy::SHOW_ALL);
    
    director->setContentScaleFactor(scaleFactor / (size.height / 1136.0f));
    
    CCBReader::setupSpriteBuilder("resources-phonehd", PHYSIC_FACTOR);
    FileUtils::getInstance()->addSearchPath("defaults");
    
    CocosDenshion::SimpleAudioEngine *audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadEffect("success.mp3");
    audio->preloadEffect("failedsound.mp3");
    audio->preloadEffect("pageflip.mp3");
    audio->preloadEffect("times-up.mp3");

    audio->preloadBackgroundMusic("playing.mp3");


    MainMenu *layer = MainMenu::createFromCCB();
    auto scene = Scene::create();
    scene->addChild(layer);
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
