#include "TaskDesc.h"
#include "DungeonsProxy.h"
#include "TaskDescLoader.h"
#include "StaticRole.h"

TaskDesc::TaskDesc()
	: mName(NULL)
	, mDesc(NULL)
	, mSelect(NULL)
	, mNodeBg(NULL)
	, mBtnList(NULL)
{
	CCLOG("TaskDesc::%s()", __FUNCTION__);
}

TaskDesc::~TaskDesc()
{
	CCLOG("TaskDesc::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mName);
	CC_SAFE_RELEASE(mDesc);
	CC_SAFE_RELEASE(mSelect);
	CC_SAFE_RELEASE(mNodeBg);
	CC_SAFE_RELEASE(mBtnList);
}

bool TaskDesc::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDesc", CCLabelTTF *, mDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF *, mName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelect", CCSprite *, mSelect);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeBg", CCNode*, mNodeBg);
	CCB_CONTROLBUTTON_GLUE(this, "mBtnList", mBtnList, gls("QuestList"));
	return false;
}

SEL_MenuHandler TaskDesc::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler TaskDesc::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnList", TaskDesc::onBtnList);
	return NULL;
}

void TaskDesc::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("TaskDesc::%s()", __FUNCTION__);
	mSelect->runAction(CCRepeatForever::create(CCRotateBy::create(5, 360)));
	mSelect->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
		CCFadeTo::create(0.8, 160), CCFadeTo::create(0.8, 255), NULL)));
}

void TaskDesc::refresh()
{
	TaskStatic* taskInfo = DungeonsProxy::shared()->getCurTaskStatic();
	FloorStatic* floorStatic = DungeonsProxy::shared()->getCurFloorStatic();
	mName->setString(floorStatic->name);
	mDesc->setString(DUNPROXY->getCurDesc());
	int index = taskInfo->taskID - 1;
	mSelect->setPosition(ccp((index % 6) * 100 + 70, mSelect->getPositionY()));
	
	mNodeBg->removeAllChildren();
	if (taskInfo->bossID == -1)
	{
		mNodeBg->addChild(CCSprite::create(fcs("scene/scene%d.jpg", DungeonsProxy::shared()->getCurFloorID())));
	}
	else
	{
		BossInfo* bossInfo = StaticRole::shared()->getBossInfo(taskInfo->bossID);
		mNodeBg->addChild(CCSprite::create(fcs("boss/%s", bossInfo->icon)));
	}	
}

void TaskDesc::onBtnList(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	FRAMEWORK->changeState("DungeonsListScene");
}

void TaskDesc::shakeScene()
{
	CCSequence* sequence1 = (CCSequence*)CCSequence::create(
		CCRotateBy::create(0.05, -5),
		CCRotateBy::create(0.05, 5),
		CCRotateBy::create(0.05, 5),
		CCRotateBy::create(0.05, -5),
		NULL);

	CCSequence* sequence2 = (CCSequence*)CCSequence::create(
		CCRepeat::create(sequence1, 5),
		CCRotateTo::create(0.05, 0),
		NULL);

	mNodeBg->runAction(sequence2);
}

void TaskDesc::setDesc(const char* desc)
{
	mDesc->setString(desc);
}
