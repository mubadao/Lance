#include "Framework.h"
//#include "display/dialog/Dialog.h"
//#include "utils/CoordinateUtil.h"

Framework::Framework()
: mStateManager(NULL)
, mLayerState(NULL)
, mLayerDialog(NULL)
, mCurState(NULL)
, mDialogMask(NULL)
{
	bgLayer = CCLayer::create();
	mLayerState = CCLayer::create();
	globalLayer = CCLayer::create();
	mLayerDialog = CCLayer::create();
	maskLayer = CCNode::create();
	topLayer = CCLayer::create();
    
	mainScene = CCScene::create();
	mainScene->addChild(bgLayer);
	mainScene->addChild(mLayerState);
	mainScene->addChild(globalLayer);
	mainScene->addChild(mLayerDialog);
	mainScene->addChild(topLayer);
    
    mDialogMask = Mask::create(100);
    mDialogMask->retain();
}

Framework::~Framework()
{
    CC_SAFE_RELEASE(mDialogMask);
    if (mStateManager)
        delete mStateManager;
}

void Framework::init()
{
//k	CCSprite* pSprite = CCSprite::create("sprite/mask.png");
//	pSprite->setPosition(cult(pSprite, 0, -160));
//	maskLayer->addChild(pSprite);
//
//	CCScale9Sprite *backgroundButton = CCScale9Sprite::create("sprite/bg_26.png");
//	backgroundButton->setAnchorPoint(ccp(0, 0));
//	backgroundButton->setContentSize(CCDirector::sharedDirector()->getWinSize());
//	bgLayer->addChild(backgroundButton);

	CCDirector::sharedDirector()->runWithScene(mainScene);
}

void Framework::changeState(const string& name)
{
//	CCPoolManager::sharedPoolManager()->purgePoolManager();
	assert(mStateManager);
    assert(!name.empty());
    
    if (name == mCurStateName)
        return;
    
	mLastStateName = mCurStateName;
	mCurStateName = name;
    
	CCLayer* state = mStateManager->getState(name);
    assert(state);
    
	if (mCurState)
		mLayerState->removeChild(mCurState, true);
    
	mCurState = state;
	mLayerState->addChild(mCurState);
}

void Framework::popup(const string& name, void* data)
{
	DialogInfo info(name, data);
	mDialogList.push(info);
	popupNext();
}

void Framework::popupNext()
{
	if(!mDialogList.empty())
	{
		DialogInfo& di = mDialogList.front();
		Dialog* dlg = mStateManager->getDialog(di.name);
		dlg->setUserData(di.data);
		dlg->popup();
		mDialogList.pop();
	}
}

void Framework::changeToLastState()
{
	if (!mLastStateName.empty())
	{
		changeState(mLastStateName);
	}
}