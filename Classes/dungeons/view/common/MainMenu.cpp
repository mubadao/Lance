#include "MainMenu.h"
#include "DungeonsProxy.h"
#include "MainTools.h"

MainMenu::MainMenu()
: mBtnHome(NULL)
, mBtnEquip(NULL)
, mBtnDungeon(NULL)
, mBtnShop(NULL)
, mBtnMore(NULL)
{
	CCLOG("MainMenu::%s()", __FUNCTION__);
}

MainMenu::~MainMenu()
{
	CCLOG("MainMenu::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mBtnHome);
	CC_SAFE_RELEASE(mBtnEquip);
	CC_SAFE_RELEASE(mBtnDungeon);
	CC_SAFE_RELEASE(mBtnShop);
	CC_SAFE_RELEASE(mBtnMore);
}	

SEL_MenuHandler MainMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MainMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnHome", MainMenu::onBtnHome);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnEquip", MainMenu::onBtnEquip);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnDungeon", MainMenu::onBtnDungeon);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnShop", MainMenu::onBtnShop);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnMore", MainMenu::onBtnMore);
	return NULL;
}

bool MainMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnHome", CCControlButton*, mBtnHome);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnEquip", CCControlButton*, mBtnEquip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnDungeon", CCControlButton*, mBtnDungeon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnShop", CCControlButton*, mBtnShop);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnMore", CCControlButton*, mBtnMore);
	
	return false;
}

void MainMenu::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("MainMenu::%s()", __FUNCTION__);
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	setTouchPriority(touch_priority_1);

	mBtnHome->setDefaultTouchPriority(touch_priority_2);
	mBtnEquip->setDefaultTouchPriority(touch_priority_2);
	mBtnDungeon->setDefaultTouchPriority(touch_priority_2);
	mBtnShop->setDefaultTouchPriority(touch_priority_2);
	mBtnMore->setDefaultTouchPriority(touch_priority_2);
}

void MainMenu::onBtnHome(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	FRAMEWORK->changeState("HomeScene");
}

void MainMenu::onBtnEquip(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	FRAMEWORK->changeState("PacketScene");
}

void MainMenu::onBtnDungeon(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	int dungeonID = DungeonsProxy::shared()->getMaxDungeonsID();
	int floorID = DungeonsProxy::shared()->getMaxFloorID();
	int taskID = DungeonsProxy::shared()->getMaxTaskID();
	int progress = DungeonsProxy::shared()->getMaxProgress();

	if(dungeonID == 1 && floorID == 1 && taskID == 1 && progress == 0)
	{
		FRAMEWORK->changeState("DungeonsListScene");
	}
	else
	{
		FRAMEWORK->changeState("DungeonsScene");
	}
}

void MainMenu::onBtnShop(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	FRAMEWORK->changeState("ShopScene");
}

void MainMenu::onBtnMore(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	FRAMEWORK->popup("MainTools");
}

bool MainMenu::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return isTouchInside(pTouch, this);
}

