#include "TaskBoss.h"
#include "StaticDungeon.h"
#include "StaticRole.h"
#include "StaticItem.h"
#include "DungeonsProxy.h"
#include "UserProxy.h"
#include "FightProxy.h"
#include "NetController.h"

TaskBoss::TaskBoss()
	: mBossName(NULL)
	, mBossAttack(NULL)
	, mBossDefense(NULL)
	, mBossLife(NULL)
	, mEnergy(NULL)
	, mExp(NULL)
	, mCoin(NULL)
	, mItemName(NULL)
	, mItemLevel(NULL)
	, mLifeTitle(NULL)
	, mEquipIcon(NULL)
	, mDoItBtn(NULL)
	, mLifeProgress(NULL)
	, mCurStep(1)
{
	CCLOG("TaskBoss::%s()", __FUNCTION__);
}

TaskBoss::~TaskBoss()
{
	CCLOG("TaskBoss::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mBossName);
	CC_SAFE_RELEASE(mBossAttack);
	CC_SAFE_RELEASE(mBossDefense);
	CC_SAFE_RELEASE(mBossLife);
	CC_SAFE_RELEASE(mEnergy);
	CC_SAFE_RELEASE(mExp);
	CC_SAFE_RELEASE(mCoin);
	CC_SAFE_RELEASE(mItemName);
	CC_SAFE_RELEASE(mItemLevel);
	CC_SAFE_RELEASE(mLifeTitle);
	CC_SAFE_RELEASE(mEquipIcon);
	CC_SAFE_RELEASE(mDoItBtn);
}

SEL_MenuHandler TaskBoss::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler TaskBoss::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDoItBtnClick", TaskBoss::onDoItBtnClick);
	return NULL;
}

bool TaskBoss::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBossName", CCLabelTTF*, mBossName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBossAttack", CCLabelTTF*, mBossAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBossDefense", CCLabelTTF*, mBossDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBossLife", CCLabelTTF*, mBossLife);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnergy", CCLabelTTF*, mEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExp", CCLabelTTF*, mExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoin", CCLabelTTF*, mCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemName", CCLabelTTF*, mItemName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemLevel", CCLabelTTF*, mItemLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLifeTitle", CCLabelTTF*, mLifeTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipIcon", EquipIcon*, mEquipIcon);
	CCB_CONTROLBUTTON_GLUE(this, "mDoItBtn", mDoItBtn, gls("180"));
	return false;
}

void TaskBoss::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("TaskBoss::%s()", __FUNCTION__);
//    CCB_CONTROLBUTTON_GLUE(this, "mFightBtn", mFightBtn, gls("140"));

	mLifeProgress = ProgressText::create("progress_03.png", DEFAULT_FONT, 28);
	mLifeProgress->setMode(PROGRESS_TEXT_FORMAT_CURMAX);
	mLifeProgress->setRange(0, 100);
//	mLifeProgress->getText()->setAnchorPoint(ccp(0, 0.5));
	mLifeProgress->setPosition(376, 238);
	mLifeProgress->getText()->setColor(ccGREEN);
//	mLifeProgress->getText()->setPosition(ccp(-40,0));
	addChild(mLifeProgress);
}

void TaskBoss::refresh()
{
	xmlTaskInfo* taskInfo = DungeonsProxy::shared()->getCurTaskStatic();
	xmlEquipInfo* itemStatic = StaticItem::shared()->getEquipInfo(taskInfo->drop);
	xmlBossInfo* bossInfo = StaticRole::shared()->getBossInfo(taskInfo->bossID);
	
	mBossName->setString(gls(fcs("%boss04d", bossInfo->id)));
	mBossAttack->setString(fcs("%s: %d-%d", gls("Attack"), bossInfo->atk_min, bossInfo->atk_max));
	mBossDefense->setString(fcs("%s: %d-%d", gls("Defense"), bossInfo->def_min, bossInfo->def_max));
	mBossLife->setString(fcs("%s: %d", gls("Life"), bossInfo->life));
	
	mItemName->setColor(EquipInfo::getNameColor(itemStatic->quality));
	mItemName->setString(gls(fcs("item%05d", taskInfo->drop)));
	mItemLevel->setString(fcs("LV.%d", itemStatic->level));
	mItemLevel->setPositionX(mItemName->getPositionX() + mItemName->getContentSize().width + 10);

	mEquipIcon->setInfo(taskInfo->drop);
	
	mLifeProgress->setRange(0, UserProxy::shared()->userVO.life);
	mLifeProgress->setPecent(UserProxy::shared()->userVO.lifeCur);

	mExp->setString(fcs("%d-%d", taskInfo->expMin, taskInfo->expMax));
	mCoin->setString(fcs("%d-%d", taskInfo->coinMin, taskInfo->coinMax));
	mEnergy->setString(fcs("-%d", taskInfo->energy));
	
	mTaskDesc->setDesc(DungeonsProxy::shared()->getDesc(mCurStep));

	if(mCurStep >= 5)
	{
		mDoItBtn->setTitleForState(ccs(gls("180")), CCControlStateNormal);
		mDoItBtn->setTitleForState(ccs(gls("180")), CCControlStateHighlighted);
	}
	else
	{
		mDoItBtn->setTitleForState(ccs(gls("140")), CCControlStateNormal);
		mDoItBtn->setTitleForState(ccs(gls("140")), CCControlStateHighlighted);
	}
}

void TaskBoss::refreshLife()
{
	mLifeProgress->setRange(0, UserProxy::shared()->userVO.life);
	mLifeProgress->setPecent(UserProxy::shared()->userVO.lifeCur);
}

void TaskBoss::onDoItBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	++mCurStep;
	if(mCurStep > 5)
	{
		FightProxy::shared()->mBossID = DungeonsProxy::shared()->getCurTaskStatic()->bossID;
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
			NetController::shared()->dungeonExplore(DungeonsProxy::shared()->getCurDungeon(),
				DungeonsProxy::shared()->getCurFloor(), DungeonsProxy::shared()->getCurTask());
			FightProxy::shared()->mDungeons = DungeonsProxy::shared()->getCurDungeon();
			FightProxy::shared()->mFloor = DungeonsProxy::shared()->getCurFloor();
			FightProxy::shared()->mTask = DungeonsProxy::shared()->getCurTask();
		}
	}
	else
	{
		mTaskDesc->setDesc(DungeonsProxy::shared()->getDesc(mCurStep));
		if (mCurStep == 5)
		{
			mDoItBtn->setTitleForState(ccs(gls("180")), CCControlStateNormal);
			mDoItBtn->setTitleForState(ccs(gls("180")), CCControlStateHighlighted);
		}
	}
}

void TaskBoss::reset()
{
	mCurStep = 1;
}
