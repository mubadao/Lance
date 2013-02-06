#include "DungeonsScene.h"
#include "DungeonsProxy.h"
#include "StaticDungeons.h"
#include "FightProxy.h"
#include "NotifyDefine.h"

DungeonsScene::DungeonsScene()
	: mTaskDesc(NULL)
	, mTaskBoss(NULL)
	, mTaskNormal(NULL)
{	
	CCLOG("DungeonsScene::%s()", __FUNCTION__);
}


DungeonsScene::~DungeonsScene()
{
	CCLOG("DungeonsScene::%s()", __FUNCTION__);
	RemoveObserver(this);

	CC_SAFE_RELEASE(mTaskDesc);
	CC_SAFE_RELEASE(mTaskBoss);
	CC_SAFE_RELEASE(mTaskNormal);
}

bool DungeonsScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTaskDesc", TaskDesc*, mTaskDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTaskBoss", TaskBoss*, mTaskBoss);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTaskNormal", TaskNormal*, mTaskNormal);
	return false;
}

void DungeonsScene::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("DungeonsScene::%s()", __FUNCTION__);
	mTaskBoss->setTaskDesc(mTaskDesc);

	CCArray* nameList = CCArray::create(
		ccs(kNCDungeonExplore),
		ccs(kNCBuyLife),
		ccs(kNCDungeonStart),
		NULL);
	RegisterObservers(this, nameList, callfuncO_selector(DungeonsScene::_onNotification));

	refresh();
}

void DungeonsScene::refresh()
{
	TaskStatic* taskInfo = DungeonsProxy::shared()->getCurTaskStatic();

	if (taskInfo->bossID == -1)
	{
		mTaskDesc->refresh();
		mTaskNormal->refresh();
		mTaskNormal->setVisible(true);
		mTaskBoss->setVisible(false);
	}
	else
	{
		mTaskDesc->refresh();
		mTaskBoss->refresh();
		mTaskNormal->setVisible(false);
		mTaskBoss->setVisible(true);
	}
}


void DungeonsScene::_onNotification( CCObject* object )
{
	CCLOG("DungeonsScene::%s()", __FUNCTION__);

	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());
	
	if (name == kNCDungeonExplore)
	{
		int win = FightProxy::shared()->battleInfo.win;
		if (win == 1)		//战斗胜利
		{
			mTaskBoss->reset();
			gsEquipInfo = FightProxy::shared()->awardInfo.equipList[0];
			FRAMEWORK->popup("FightSucceedDialog");
		}
		else if(win == 2 )	//战斗失败
		{
			FRAMEWORK->popup("FightFailedDialog");
		}
		else
		{
			Award& award = FightProxy::shared()->awardInfo;
			if(award.eventType == EVENT_TYPE_NONE)
				_playAwardAnim();
			else if(award.eventType == EVENT_TYPE_LOST_LIFE)
				FRAMEWORK->popup("LostLifeEventDialog");
			else if(award.eventType == EVENT_TYPE_GET_COIN)
				FRAMEWORK->popup("GetMoneyEventDialog");
			else if(award.eventType == EVENT_TYPE_GET_ENERGY)
				FRAMEWORK->popup("GetEnergyEventDialog");
			else if(award.eventType == EVENT_TYPE_GET_EQUIP)
			{
				gsEquipInfo = award.equipList[0];
				FRAMEWORK->popup("GetEquipEventDialog");
			}
			refresh();
			mTaskDesc->shakeScene();
		}
		
		//玩家升级
		if(DungeonsProxy::shared()->getCurFloorID() == -1)
		{
			FRAMEWORK->changeState("DungeonsListScene");
		}
		else
		{
			PostNotification(kVCLevelUp, NULL);
			//需要刷新生命值，因为升级后生命值会补满
			TaskStatic* taskInfo = DungeonsProxy::shared()->getCurTaskStatic();
			if (taskInfo->bossID == -1)	//不是boss关
				mTaskNormal->refresh();
		}
	}
	else if(name == kNCBuyLife)
	{
		mTaskNormal->refresh();
		TaskStatic* taskInfo = DungeonsProxy::shared()->getCurTaskStatic();
		if (taskInfo->bossID != -1)	//需刷新生命值
		{
			mTaskBoss->refreshLife();
		}
	}
	else if(name == kNCDungeonStart)
	{
		refresh();
		mTaskBoss->reset();
	}
}

void DungeonsScene::_playAwardAnim()
{
	Award& award = FightProxy::shared()->awardInfo;
	if (award.exp > 0 || award.coin > 0)
	{
		FloatText::shared()->playAnim(fls("get_award", award.exp, award.coin));
	}
}
