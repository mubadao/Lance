#include "PreLoaderScene.h"
#include "NetController.h"
#include "StaticDungeons.h"
#include "StaticItem.h"
#include "StaticCompose.h"
#include "StaticShop.h"
#include "StaticRole.h"
#include "UserProxy.h"
#include "MultiPlatform.h"
#include "DownloadModule.h"

PreLoaderScene::PreLoaderScene()
: mFileCount(0)
{
}

PreLoaderScene::~PreLoaderScene()
{
	RemoveObserver(this);
}

void PreLoaderScene::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCArray* nameList = CCArray::create(ccs(kNCRegist), ccs(kNCGameInit), ccs(kNCGetSelfInfo), NULL);
	RegisterObservers(this, nameList, callfuncO_selector(PreLoaderScene::_onNotification));

#if NETCONTROLLER_USE_JSON
	NCCTRL->init("http://www.happybluefin.com/Test/backend/www/json/gateway.php");
#else
	NCCTRL->init("http://www.happybluefin.com/Test/backend/www/amf/gateway.php");
#endif
//    NetController::shared()->init("http://111.194.0.181/Lance/www/amf/gateway.php");
	NCCTRL->gameInit();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	loadComplete();
#endif
}

void PreLoaderScene::_onNotification(CCObject* object)
{
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = notification->getName();
	CCObject* params = notification->getObject();
	
	if (name == kNCGameInit)
	{
		mInitResult = (int)params;
		DownloadModule::shared()->download(this, callfunc_selector(PreLoaderScene::_loadComplete));
	}
	else if (name == kNCRegist || name == kNCGetSelfInfo)
	{
		CCLOG("PreLoaderScene::_onNotification()");
		getParent()->runAction(CCSequence::create(CCDelayTime::create(0.2), CCCallFunc::create(this, callfunc_selector(PreLoaderScene::_delayComplete)), NULL));
	}
}

void PreLoaderScene::_loadComplete()
{
	LocalString::shared()->parse();
	StaticDungeons::shared()->parse();
	StaticItem::shared()->parse();
	StaticCompose::shared()->parse();
	StaticShop::shared()->parse();
	StaticRole::shared()->parse();
	
	if(mInitResult == 1)
		NCCTRL->getSelfInfo();
	else if(mInitResult == 2)
		NCCTRL->regist("lance1", 1);
}

void PreLoaderScene::_delayComplete()
{
	FRAMEWORK->changeState("HomeScene");
	if(UserProxy::shared()->mHtmlUrl != "")
	{
		MultiPlatform* multiPlatform = MultiPlatform::shared();
		multiPlatform->getPlatform()->navigateToURL(FRAMEWORK->topLayer, UserProxy::shared()->mHtmlUrl.c_str());
	}
}
