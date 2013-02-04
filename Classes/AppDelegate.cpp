#include "CCEGLView.h"
#include "AppDelegate.h"

#include "Global.h"
#include "SceneManager.h"
#include "CommonNotify.h"

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
    
    CCLog("AppDelegate::applicationDidFinishLaunching() frameWidth:%f, frameHeight:%f", screenSize.width, screenSize.height);
    
    CCFileUtils::sharedFileUtils()->setResourceDirectory("images");
    pDirector->setContentScaleFactor(1);
//    if (screenSize.width > 640)
//        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(768, 1024, kResolutionExactFit);
//    else
//    {
//        if (screenSize.height > 960)
//            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionExactFit);
//        else
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionShowAll);
//    }

	// turn on display FPS
	//pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
    
	FRAMEWORK->init();

	CommonNotify::shared()->registerNotify();
    
	FRAMEWORK->setStateManager(new SceneManager);
	FRAMEWORK->changeState("PreLoaderScene");

//k    MultiPlatform* multiPlatform = MultiPlatform::shared();
//    multiPlatform->setPlatformType("ios");
    
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();
}


