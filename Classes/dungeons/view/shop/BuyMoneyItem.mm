#include "BuyMoneyItem.h"
#include "BuyMoneyItemLoader.h"
#include "StaticShop.h"
//#include "net/NetController.h"

#import "ShopIAPHelper.h"

BuyMoneyItem::BuyMoneyItem()
	: mBuyBtn(NULL)
	, mMoney(NULL)
	, mDollor(NULL)
{
	CCLOG("BuyMoneyItem::%s()", __FUNCTION__);
}

BuyMoneyItem::~BuyMoneyItem()
{
	CCLOG("BuyMoneyItem::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mMoney);
	CC_SAFE_RELEASE(mDollor);
	CC_SAFE_RELEASE(mBuyBtn);
}

bool BuyMoneyItem::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMoney", CCLabelTTF*, mMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDollor", CCLabelTTF*, mDollor);
	CCB_CONTROLBUTTON_GLUE(this, "mBuyBtn", mBuyBtn, gls("133"));
	return false;
}

SEL_MenuHandler BuyMoneyItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler BuyMoneyItem::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBuyBtnClick", BuyMoneyItem::onBuyBtnClick);
	return NULL;
}

void BuyMoneyItem::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("BuyMoneyItem::%s()", __FUNCTION__);
//    mBuyBtn->setDefaultTouchPriority(￼)
}

void BuyMoneyItem::setData(int index)
{
	mIndex = index;
	mMoney->setString(fls("186", StaticShop::shared()->mBuyMoney[index].money));
	
	NSString* cost = [[ShopIAPHelper sharedHelper] getItemCost:[NSString stringWithFormat:@"%s", StaticShop::shared()->mBuyMoney[index].identifier.c_str()]];

	if (cost != nil)
		mDollor->setString(fcs("%s", [cost cStringUsingEncoding:NSUTF8StringEncoding]));
	else
		mDollor->setString(fls("187", StaticShop::shared()->mBuyMoney[index].dollar.c_str()));
}

void BuyMoneyItem::onBuyBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent )
{
	[[ShopIAPHelper sharedHelper] purchaseItem:StaticShop::shared()->mBuyMoney[mIndex].id-1];
}

BuyMoneyItem* BuyMoneyItem::create(CCObject* pOwer)
{
	return (BuyMoneyItem*)ReadItem("BuyMoneyItem", BuyMoneyItemLoader::loader());
}
