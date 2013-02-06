#include "MainTools.h"
#include "ShopScene.h"
#include "PacketScene.h"

MainTools::MainTools()
	: mBtnBg(NULL)
	, mTaskBtn(NULL)
	, mDungeonListBtn(NULL)
	, mEquipBtn(NULL)
	, mAttributeBtn(NULL)
	, mOpenboxBtn(NULL)
	, mShopBtn(NULL)
	, mChallengeBtn(NULL)
{
	CCLOG("MainTools::%s()", __FUNCTION__);
}

MainTools::~MainTools()
{
	CCLOG("MainTools::%s()", __FUNCTION__);

	CC_SAFE_RELEASE(mBtnBg);
	CC_SAFE_RELEASE(mTaskBtn);
	CC_SAFE_RELEASE(mDungeonListBtn);
	CC_SAFE_RELEASE(mEquipBtn);
	CC_SAFE_RELEASE(mAttributeBtn);
	CC_SAFE_RELEASE(mShopBtn);
	CC_SAFE_RELEASE(mOpenboxBtn);
	CC_SAFE_RELEASE(mChallengeBtn);
}

bool MainTools::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnBg", CCControlButton*, mBtnBg);
	CCB_CONTROLBUTTON_GLUE(this, "mShopBtn", mShopBtn, gls("66"));
	CCB_CONTROLBUTTON_GLUE(this, "mTaskBtn", mTaskBtn, gls("172"));
	CCB_CONTROLBUTTON_GLUE(this, "mEquipBtn", mEquipBtn, gls("173"));
	CCB_CONTROLBUTTON_GLUE(this, "mAttributeBtn", mAttributeBtn, gls("91"));
	CCB_CONTROLBUTTON_GLUE(this, "mDungeonListBtn", mDungeonListBtn, gls("141"));
	CCB_CONTROLBUTTON_GLUE(this, "mOpenboxBtn", mOpenboxBtn, gls("174"));
	CCB_CONTROLBUTTON_GLUE(this, "mChallengeBtn", mChallengeBtn, gls("87"));
	return false;
}

SEL_MenuHandler MainTools::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler MainTools::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnBg", MainTools::onBtnBg);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTaskBtnClick", MainTools::onTaskBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEquipBtnClick", MainTools::onEquipBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAttributeBtnClick", MainTools::onAttributeBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onShopBtnClick", MainTools::onShopBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDungeonListBtnClick", MainTools::onDungeonListBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOpenboxBtnClick", MainTools::onOpenboxBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChallengeBtnClick", MainTools::onChallengeBtnClick);
	return NULL;
}

void MainTools::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("MainTools::%s()", __FUNCTION__);

	addChild(Mask::create(50));
	
	mBtnBg->setDefaultTouchPriority(touch_priority_4);
	mTaskBtn->setDefaultTouchPriority(touch_priority_5);
	mDungeonListBtn->setDefaultTouchPriority(touch_priority_5);
	mEquipBtn->setDefaultTouchPriority(touch_priority_5);
	mAttributeBtn->setDefaultTouchPriority(touch_priority_5);
	mOpenboxBtn->setDefaultTouchPriority(touch_priority_5);
	mShopBtn->setDefaultTouchPriority(touch_priority_5);
	mChallengeBtn->setDefaultTouchPriority(touch_priority_5);
}

void MainTools::onTaskBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	FRAMEWORK->changeState("DungeonsScene");
	close();
}

void MainTools::onEquipBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	PacketScene::msCurTab = PACK_TAB_EQUIP;
	FRAMEWORK->changeState("PacketScene");
	close();
}

void MainTools::onAttributeBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	FRAMEWORK->changeState("PlayerDetailScene");
	close();
}

void MainTools::onShopBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	FRAMEWORK->changeState("ShopScene");
	close();
}

void MainTools::onDungeonListBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	FRAMEWORK->changeState("DungeonsListScene");
	close();
}

void MainTools::onOpenboxBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	ShopScene::msCurTab = SHOP_TAB_LOTTERY;
	FRAMEWORK->changeState("ShopScene");
	close();
}

void MainTools::onChallengeBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	FRAMEWORK->changeState("ChallengeScene");
	close();
}

void MainTools::onBtnBg(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	close();
}
