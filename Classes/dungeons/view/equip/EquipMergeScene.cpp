#include "EquipMergeScene.h"
#include "CommonNotify.h"
#include "NetController.h"
#include "XiLianOkDialog.h"
#include "AlertTitleDialog.h"
#include "StaticShop.h"

EquipMergeScene::EquipMergeScene()
	: mName(NULL)
	, mType(NULL)
	, mIntensifyCount(NULL)
	, mPropertyTitle(NULL)
	, mProperty(NULL)
	, mPreviewTitle(NULL)
	, mAddPropertyTitle(NULL)
	, mAddProperty(NULL)
	, mPerfectTitle(NULL)
	, mPerfect(NULL)
	, mZhuRongTitle(NULL)
	, mZhuRongCount(NULL)
	, mZhuRongCostTitle(NULL)
	, mZhuRongDesc(NULL)
	, mFusionTitle(NULL)
	, mFusion(NULL)
	, mNeedFusionTitle(NULL)
	, mNeedFusion(NULL)
	, mNeedCoinTitle(NULL)
	, mNeedCoin(NULL)
	, mSubZhuRongBtn(NULL)
	, mAddZhuRongBtn(NULL)
	, mResetBtn(NULL)
	, mAddIntensifyBtn(NULL)
	, mFusionBtn(NULL)
	, mReturnBtn(NULL)
	, mZhuRongCostIcon(NULL)
	, mEquipIcon(NULL)
{
	CCLOG("EquipMergeScene::%s()", __FUNCTION__);
    mZhuRongJiCount = 0;
    mQiangHuaCount = 0;
}

EquipMergeScene::~EquipMergeScene()
{
	CCLOG("EquipMergeScene::%s()", __FUNCTION__);
	RemoveObserver(this);
	
	CC_SAFE_RELEASE(mName);
	CC_SAFE_RELEASE(mType);
	CC_SAFE_RELEASE(mIntensifyCount);
	CC_SAFE_RELEASE(mPropertyTitle);
	CC_SAFE_RELEASE(mProperty);
	CC_SAFE_RELEASE(mPreviewTitle);
	CC_SAFE_RELEASE(mAddPropertyTitle);
	CC_SAFE_RELEASE(mAddProperty);
	CC_SAFE_RELEASE(mPerfectTitle);
	CC_SAFE_RELEASE(mPerfect);
	CC_SAFE_RELEASE(mZhuRongTitle);
	CC_SAFE_RELEASE(mZhuRongCount);
	CC_SAFE_RELEASE(mZhuRongCostTitle);
	CC_SAFE_RELEASE(mZhuRongDesc);
	CC_SAFE_RELEASE(mFusionTitle);
	CC_SAFE_RELEASE(mFusion);
	CC_SAFE_RELEASE(mNeedFusionTitle);
	CC_SAFE_RELEASE(mNeedFusion);
	CC_SAFE_RELEASE(mNeedCoinTitle);
	CC_SAFE_RELEASE(mNeedCoin);
	CC_SAFE_RELEASE(mSubZhuRongBtn);
	CC_SAFE_RELEASE(mAddZhuRongBtn);
	CC_SAFE_RELEASE(mResetBtn);
	CC_SAFE_RELEASE(mAddIntensifyBtn);
	CC_SAFE_RELEASE(mFusionBtn);
	CC_SAFE_RELEASE(mReturnBtn);
	CC_SAFE_RELEASE(mZhuRongCostIcon);
	CC_SAFE_RELEASE(mEquipIcon);
}

bool EquipMergeScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF*, mName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mType", CCLabelTTF*, mType);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIntensifyCount", CCLabelTTF*, mIntensifyCount);
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPropertyTitle", CCLabelTTF*, mPropertyTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProperty", CCLabelTTF*, mProperty);
    
    CCB_CCLABELTTF_GLUE(this, "mPreviewTitle", mPreviewTitle, gls("94"));
    
    CCB_CCLABELTTF_GLUE(this, "mAddPropertyTitle", mAddPropertyTitle, gls("96"));
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAddProperty", CCLabelTTF*, mAddProperty);
    
    CCB_CCLABELTTF_GLUE(this, "mPerfectTitle", mPerfectTitle, gls("95"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPerfect", CCLabelTTF*, mPerfect);
    
    CCB_CCLABELTTF_GLUE(this, "mZhuRongTitle", mZhuRongTitle, gls("100"));
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mZhuRongCount", CCLabelTTF*, mZhuRongCount);
    
    CCB_CCLABELTTF_GLUE(this, "mZhuRongCostTitle", mZhuRongCostTitle, gls("208"));
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mZhuRongCostIcon", MoneyIcon*, mZhuRongCostIcon);
    CCB_CCLABELTTF_GLUE(this, "mZhuRongDesc", mZhuRongDesc, gls("101"));
    
    CCB_CCLABELTTF_GLUE(this, "mFusionTitle", mFusionTitle, gls("98"));
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFusion", CCLabelTTF*, mFusion);
    
    CCB_CCLABELTTF_GLUE(this, "mNeedFusionTitle", mNeedFusionTitle, gls("97"));
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNeedFusion", CCLabelTTF*, mNeedFusion);
    
    CCB_CCLABELTTF_GLUE(this, "mNeedCoinTitle", mNeedCoinTitle, gls("99"));
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNeedCoin", CCLabelTTF*, mNeedCoin);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSubZhuRongBtn", CCControlButton*, mSubZhuRongBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAddZhuRongBtn", CCControlButton*, mAddZhuRongBtn);
	CCB_CONTROLBUTTON_GLUE(this, "mResetBtn", mResetBtn, gls("209"));
	CCB_CONTROLBUTTON_GLUE(this, "mAddIntensifyBtn", mAddIntensifyBtn, gls("103"));
	CCB_CONTROLBUTTON_GLUE(this, "mFusionBtn", mFusionBtn, gls("104"));
	CCB_CONTROLBUTTON_GLUE(this, "mReturnBtn", mReturnBtn, gls("80"));
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipIcon", EquipIcon*, mEquipIcon);

	return false;
}

SEL_MenuHandler EquipMergeScene::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler EquipMergeScene::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSubZhuRongBtnClick", EquipMergeScene::onSubZhuRongBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAddZhuRongBtnClick", EquipMergeScene::onAddZhuRongBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onResetBtnClick", EquipMergeScene::onResetBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onIntensifyBtnClick", EquipMergeScene::onIntensifyBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturnBtnClick", EquipMergeScene::onReturnBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAddIntensifyBtnClick", EquipMergeScene::onAddIntensifyBtnClick);
	return NULL;
}

void EquipMergeScene::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("EquipMergeScene::%s()", __FUNCTION__);

    mZhuRongCostIcon->setType(MONEY_TYPE_MONEY);

    CCSprite* pSprite = CCSprite::create("img_14.png");
    mStarProgress = CCProgressTimer::create(pSprite);
    mStarProgress->setPosition(326, 804);
    mStarProgress->setType(kCCProgressTimerTypeBar);
	mStarProgress->setMidpoint(ccp(0,0));
	mStarProgress->setBarChangeRate(ccp(1,0));
	mStarProgress->setPercentage(70);
	addChild(mStarProgress);

	CCArray* nameList = CCArray::create(
		ccs(kVCSelectItem),
		ccs(kNCIntensifyEquipage),
		ccs(kNCResetEquipage),
		ccs(kVCBuyZhuRongJi),
		ccs(kNCBuyFusion),
		NULL);
	RegisterObservers(this, nameList, callfuncO_selector(EquipMergeScene::_onNotification));
	
	_refresh();
}

void EquipMergeScene::_onNotification( CCObject* object )
{
	CCLOG("EquipMergeScene::%s()", __FUNCTION__);

	NotificationObserver* notification = (NotificationObserver*)object;
	string name = std::string(notification->getName());
	if (name == kVCSelectItem)
	{
//		if (isChangeEquip)
//		{
//			int select = ItemProxy::getSingletonPtr()->mSelectList[0];
//			ItemProxy::getSingletonPtr()->setLastQiangHuaEquip(ItemProxy::getSingletonPtr()->getEquip(select)) ;
//			refresh();
//		} 
//		else
//		{
//			FRAMEWORK->popup("MeltOkDialog");
//		}
	}
	else if(name == kNCIntensifyEquipage)
	{
		FRAMEWORK->popup("MeltResultDialog");
        mZhuRongJiCount = 0;
        _refresh();
	}
    else if(name == kNCResetEquipage)
	{
		_refresh();
        FloatText::shared()->playAnim(gls("212"));
	}
	else if(name == kNCBuyFusion)
	{
        _refreshFusion();
        FloatText::shared()->playAnim(gls("164"));
	}
}

void EquipMergeScene::_refresh()
{
	EquipInfo* equipInfo = ItemProxy::shared()->curQiangHuaEquip;
    EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(equipInfo->id);

    mEquipIcon->setInfo(equipInfo->id);
    mName->setString(equipStatic->name);
    mIntensifyCount->setString(fcs("+%d", equipInfo->intensifyNum));
    mType->setString(ItemProxy::shared()->getTypeTitle(equipInfo->id));
    mPropertyTitle->setString(equipInfo->getPropertyTitle());
    int addProterty = int(equipInfo->getMaxBaseProperty() * (equipInfo->intensifyValue / 100));
    mProperty->setString(fcs("%s(+%d)", equipInfo->getAttachPropertyStr(), addProterty));
    mNeedCoin->setString(fcs("%d", equipStatic->intensify_price));
    mNeedFusion->setString(fcs("%d", equipStatic->intensify_energy));
    
	_refreshPerfect();
    _refreshAddProperty();
    _refreshZhuRongCount();
    _refreshFusion();
    _refreshStarLevel();
}

void EquipMergeScene::onSubZhuRongBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	if (mZhuRongJiCount > 0)
	{
		mZhuRongJiCount--;
		_refreshZhuRongCount();
		_refreshPerfect();
		_refreshAddProperty();
		_refreshStarLevel();
	}
}

void EquipMergeScene::onAddZhuRongBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    int zhuRongCount = mZhuRongJiCount + 1;
    if(zhuRongCount > 4)
		return;
    
    BuyZhuRongStatic* itemStatic = StaticShop::shared()->getBuyZhuRongStatic(zhuRongCount);
    UserVO& userVO = UserProxy::shared()->userVO;
	if(itemStatic->money > userVO.money)
    {
        Post_Net_Notification(kVCBuyMoney, NULL);
    }
    else 
    {
        mZhuRongJiCount = zhuRongCount;
        _refreshZhuRongCount();
        _refreshPerfect();
        _refreshAddProperty();
        _refreshStarLevel();
    }
}

void EquipMergeScene::onIntensifyBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    NetController::shared()->intensifyEquipage(
        ItemProxy::shared()->curQiangHuaEquip->index,
        mZhuRongJiCount);
}

void EquipMergeScene::onResetBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    XiLianOkDialog::msEquipInfo = ItemProxy::shared()->curQiangHuaEquip;
	FRAMEWORK->popup("XiLianOkDialog");
}

void EquipMergeScene::onReturnBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
    FRAMEWORK->changeToLastState();
}

void EquipMergeScene::onAddIntensifyBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    BuyCountStatic& buyFusionStatic = StaticShop::shared()->mBuyFusionStatic;
	AlertTitleDialog::initContent(
		gls("210"),
		fls("211", buyFusionStatic.costType.getCostCount(), buyFusionStatic.count),
		false,
		this,
		callfunc_selector(EquipMergeScene::_buyFusion),
		NULL,
		NULL,
		gls("133"));
    FRAMEWORK->popup("AlertTitleDialog");
}

void EquipMergeScene::_refreshZhuRongCount()
{
    mZhuRongCount->setString(fcs("%d", mZhuRongJiCount));
    if(mZhuRongJiCount == 0)
    {
        mZhuRongCostIcon->setCount(0);
    }
    else 
    {
        BuyZhuRongStatic* itemStatic = StaticShop::shared()->getBuyZhuRongStatic(mZhuRongJiCount);
        mZhuRongCostIcon->setCount(itemStatic->money);
    }
}

void EquipMergeScene::_refreshPerfect()
{
    mPerfect->setString(fcs("%d%%--%d%%", 10 + mZhuRongJiCount * 20, 100));
}

void EquipMergeScene::_refreshAddProperty()
{
    EquipInfo* equipInfo = ItemProxy::shared()->curQiangHuaEquip;
    float minRate = (10 + mZhuRongJiCount * 20) / 100;
    float maxRate = 100 / 100;
    int addMinProterty = equipInfo->getMaxBaseProperty() * 0.1 * minRate;
    int addMaxProterty = equipInfo->getMaxBaseProperty() * 0.1 * maxRate;
    mAddProperty->setString(fcs("%d--%d", addMinProterty, addMaxProterty));
}

void EquipMergeScene::_refreshFusion()
{
    UserVO& userVO = UserProxy::shared()->userVO;
    mFusion->setString(fcs("%d", userVO.fusion));
}

void EquipMergeScene::_refreshStarLevel()
{
    int minRate = 10 + mZhuRongJiCount * 20;
    mStarProgress->setPercentage(minRate);
}

void EquipMergeScene::_buyFusion()
{
    BuyCountStatic& buyFusionStatic = StaticShop::shared()->mBuyFusionStatic;
    UserVO& userVO = UserProxy::shared()->userVO;
	if(buyFusionStatic.costType.getCostCount() > userVO.money)
    {
        Post_Net_Notification(kVCBuyMoney, NULL);
    }
    else 
    {
        NetController::shared()->buyFusion(buyFusionStatic.costType.getMoneyType());
    }
    
}
