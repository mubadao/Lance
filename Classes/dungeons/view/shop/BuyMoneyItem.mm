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
}

BuyMoneyItem::~BuyMoneyItem()
{
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
//    mBuyBtn->setDefaultTouchPriority(￼)
}

void BuyMoneyItem::setData(int index)
{
	mIndex = index;
	BuyMoneyStaticList list = StaticShop::shared()->getBuyMoneyStaticList();
	mMoney->setString(fls("186", list[index]->money));
	
	NSString* cost = [[ShopIAPHelper sharedHelper] getItemCost:[NSString stringWithFormat:@"%s", list[index]->identifier]];

	if (cost != nil)
		mDollor->setString(fcs("%s", [cost cStringUsingEncoding:NSUTF8StringEncoding]));
	else
		mDollor->setString(fls("187", list[index]->dollar));
}

void BuyMoneyItem::onBuyBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent )
{
	BuyMoneyStaticList list = StaticShop::shared()->getBuyMoneyStaticList();
	[[ShopIAPHelper sharedHelper] purchaseItem:list[mIndex]->id-1];
}

BuyMoneyItem* BuyMoneyItem::create(CCObject* pOwer)
{
	return (BuyMoneyItem*)ReadItem("BuyMoneyItem", BuyMoneyItemLoader::loader());
}
