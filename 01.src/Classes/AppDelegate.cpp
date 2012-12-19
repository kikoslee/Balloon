#include "AppDelegate.h"

#include "HBCommon.h"
#include "SceneLogoLoader.h"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setProjection(kCCDirectorProjection2D);
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    CCFileUtils::sharedFileUtils()->setResourceDirectory("imageshd");
    pDirector->setContentScaleFactor(1);
    if (screenSize.width > 640)
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(768, 1024, kResolutionShowAll);
    else
    {
        if (screenSize.height > 960)
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionShowAll);
        else
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionShowAll);
    }
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
	pDirector->runWithScene(HBSceneLoader("SceneLogo", SceneLogoLoader::loader()));

//    HBScore::initScore();
//
//    // Sound
//    SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
//
//	GlobalData::load();
//    
//    CCSize s = CCDirector::sharedDirector()->getWinSize();
//    gScreenWidth = 320; // s.width;
//    gScreenHeight = 480; //s.height;
//    gScreenWidthHalf = 160; //s.width / 2;
//    gScreenHeightHalf = 240; //s.height / 2;
//
//    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
//    cache->addSpriteFramesWithFile("sheet.plist");
//
//    // create a scene. it's an autorelease object
//    CCScene *pScene =  LayerLogo::scene();
//
//    // run
//    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
