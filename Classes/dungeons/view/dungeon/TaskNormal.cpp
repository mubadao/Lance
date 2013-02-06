#include "TaskNormal.h"
#include "StaticDungeons.h"
#include "DungeonsProxy.h"
#include "UserProxy.h"
#include "NetController.h"

TaskNormal::TaskNormal()
	: mLifeTitle(NULL)
	, mProgressTitle(NULL)
	, mExp(NULL)
	, mCoin(NULL)
	, mEnergy(NULL)
	, mDoItBtn(NULL)
{
	CCLOG("TaskNormal::%s()", __FUNCTION__);
}

TaskNormal::~TaskNormal()
{
	CCLOG("TaskNormal::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mLifeTitle);
	CC_SAFE_RELEASE(mProgressTitle);
	CC_SAFE_RELEASE(mExp);
	CC_SAFE_RELEASE(mCoin);
	CC_SAFE_RELEASE(mEnergy);
	CC_SAFE_RELEASE(mDoItBtn);
}

bool TaskNormal::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLifeTitle", CCLabelTTF*, mLifeTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProgressTitle", CCLabelTTF*, mProgressTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExp", CCLabelTTF*, mExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoin", CCLabelTTF*, mCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnergy", CCLabelTTF*, mEnergy);
	CCB_CONTROLBUTTON_GLUE(this, "mDoItBtn", mDoItBtn, gls("180"));
	return false;
}

SEL_MenuHandler TaskNormal::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler TaskNormal::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDoItBtnClick", TaskNormal::onDoItBtnClick);
	return NULL;
}

void TaskNormal::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("TaskNormal::%s()", __FUNCTION__);
	mLifeProgress = ProgressText::create("progress_03.png", DEFAULT_FONT, 28);
	mLifeProgress->setMode(PROGRESS_TEXT_FORMAT_CURMAX);
	mLifeProgress->setRange(0, 100);
	mLifeProgress->setPosition(318, 234);
	mLifeProgress->getText()->setPosition(ccp(210, 25));
	mLifeProgress->getText()->setColor(ccGREEN);
	mLifeProgress->getText()->setAnchorPoint(ccp(1, 0.5));
	mLifeProgress->getText()->setHorizontalAlignment(kCCTextAlignmentRight);
	addChild(mLifeProgress);

	mProgress = ProgressText::create("progress_01.png", DEFAULT_FONT, 28);
	mProgress->setMode(PROGRESS_TEXT_FORMAT_CURMAX);
	mProgress->setRange(0, 100);
	mProgress->setPosition(318, 170);
	mProgress->getText()->setPosition(ccp(210, 25));
	mProgress->getText()->setColor(ccGREEN);
	mProgress->getText()->setAnchorPoint(ccp(1, 0.5));
	mProgress->getText()->setHorizontalAlignment(kCCTextAlignmentRight);
	addChild(mProgress);
}

void TaskNormal::refresh()
{
	TaskStatic* taskInfo = DungeonsProxy::shared()->getCurTaskStatic();

	mExp->setString(fcs("%d-%d", taskInfo->expMin, taskInfo->expMax));
	mCoin->setString(fcs("%d-%d", taskInfo->coinMin, taskInfo->coinMax));
	mEnergy->setString(fcs("-%d", taskInfo->energy));

	mProgress->setRange(0, 100);
	mProgress->setPecent(DungeonsProxy::shared()->getCurProgress());
	mLifeProgress->setRange(0, UserProxy::shared()->userVO.life);
	mLifeProgress->setPecent(UserProxy::shared()->userVO.lifeCur);
}

void TaskNormal::onDoItBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	int life = UserProxy::shared()->userVO.lifeCur;
	if(life <= 0)
	{
		NetError netError;
		netError.cmdName = kNCBuyLife;
		netError.errorCode = kNCErrorLife;
		Post_Net_Notification(kNCNetError, (CCObject*)(&netError));
	}
	else
	{
		NetController::shared()->dungeonExplore(
			DungeonsProxy::shared()->getCurDungeonsID(),
			DungeonsProxy::shared()->getCurFloorID(),
			DungeonsProxy::shared()->getCurTaskID());
		FightProxy::shared()->dungeons = DungeonsProxy::shared()->getCurDungeonsID();
		FightProxy::shared()->floor = DungeonsProxy::shared()->getCurFloorID();
		FightProxy::shared()->task = DungeonsProxy::shared()->getCurTaskID();
	}
}
