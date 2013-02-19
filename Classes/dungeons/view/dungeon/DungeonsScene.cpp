#include "DungeonsScene.h"
#include "DungeonsProxy.h"
#include "StaticDungeon.h"
#include "FightProxy.h"
#include "NetController.h"
#include "NotifyDefine.h"

DungeonsScene::DungeonsScene()
	: mTaskDesc(NULL)
	, mTaskBoss(NULL)
	, mTaskNormal(NULL)
	, mMainMenu(NULL)
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
	CC_SAFE_RELEASE(mMainMenu);
}

bool DungeonsScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTaskDesc", TaskDesc*, mTaskDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTaskBoss", TaskBoss*, mTaskBoss);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTaskNormal", TaskNormal*, mTaskNormal);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainMenu", MainMenu*, mMainMenu);
	return false;
}

void DungeonsScene::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("DungeonsScene::%s()", __FUNCTION__);
	mTaskBoss->setTaskDesc(mTaskDesc);
	mMainMenu->setZOrder(100);

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
	mTaskNormal->removeFromParent();
	mTaskBoss->removeFromParent();
	if (DungeonsProxy::shared()->getCurTaskStatic()->bossID == -1)
	{
		mTaskDesc->refresh();
		mTaskNormal->refresh();
		addChild(mTaskNormal);
	}
	else
	{
		mTaskDesc->refresh();
		mTaskBoss->refresh();
		addChild(mTaskBoss);
	}
}

void DungeonsScene::_onNotification( CCObject* object )
{
	CCLOG("DungeonsScene::%s()", __FUNCTION__);

	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());
	
	if (name == kNCDungeonExplore)
	{
		int win = FightProxy::shared()->mBattleInfo.win;
		if (win == 1)		//战斗胜利
		{
			mTaskBoss->reset();
			FRAMEWORK->popup("FightSucceedDialog");
		}
		else if(win == 2 )	//战斗失败
		{
			FRAMEWORK->popup("FightFailedDialog");
		}
		else
		{
			ExploreEvent& info = FightProxy::shared()->mEventInfo;
			if(info.type == EVENT_TYPE_NONE)
				_playAwardAnim();
			else if(info.type == EVENT_TYPE_LOST_LIFE)
				FRAMEWORK->popup("LostLifeEventDialog");
			else if(info.type == EVENT_TYPE_GET_COIN)
				FRAMEWORK->popup("GetMoneyEventDialog");
			else if(info.type == EVENT_TYPE_GET_ENERGY)
				FRAMEWORK->popup("GetEnergyEventDialog");
			else if(info.type == EVENT_TYPE_GET_EQUIP)
			{
				FRAMEWORK->popup("GetEquipEventDialog");
			}
			refresh();
			mTaskDesc->shakeScene();
		}
		
		//玩家升级
		if(DungeonsProxy::shared()->getCurFloor() == -1)
		{
			FRAMEWORK->changeState("DungeonsListScene");
		}
		else
		{
			PostNotification(kVCLevelUp, NULL);
			//需要刷新生命值，因为升级后生命值会补满
			if (DungeonsProxy::shared()->getCurTaskStatic()->bossID == -1)	//不是boss关
				mTaskNormal->refresh();
		}
	}
	else if(name == kNCBuyLife)
	{
		mTaskNormal->refresh();
		if (DungeonsProxy::shared()->getCurTaskStatic()->bossID != -1)	//需刷新生命值
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
	ExploreEvent& award = FightProxy::shared()->mEventInfo;
	if (award.exp > 0 || award.coin > 0)
	{
		FloatText::shared()->playAnim(fls("get_award", award.exp, award.coin));
	}
}
