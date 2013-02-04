#include "BuyMoneyDialog.h"
#include "StaticShop.h"
#include "BuyMoneyItem.h"
#include "NetController.h"

BuyMoneyDialog::BuyMoneyDialog()
	: mTitle(NULL)
	, mBtnClose(NULL)
	, mScrollView(NULL)
{
	CCLOG("BuyMoneyDialog::%s()", __FUNCTION__);
}

BuyMoneyDialog::~BuyMoneyDialog()
{
	CCLOG("BuyMoneyDialog::%s()", __FUNCTION__);
	RemoveObserver(this);

	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mBtnClose);
	CC_SAFE_RELEASE(mScrollView);
}

bool BuyMoneyDialog::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("150"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnClose", CCControlButton*, mBtnClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView*, mScrollView);
	return false;
}

SEL_MenuHandler BuyMoneyDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler BuyMoneyDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", BuyMoneyDialog::onCloseBtnClick);
	return NULL;
}

void BuyMoneyDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("BuyMoneyDialog::%s()", __FUNCTION__);
	CCArray* nameList = CCArray::create(ccs(kNCBuyMoney),NULL);
	RegisterObservers(this, nameList, callfuncO_selector(BuyMoneyDialog::_onNotification));

	mTitle->setString(gls("175"));

	BuyMoneyStaticList list = StaticShop::shared()->getBuyMoneyStaticList();
	CCPoint contentPos = ccp(0, list.size() * 124);
	mScrollView->setContentSize(CCSizeMake(640, contentPos.y));
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - contentPos.y));
	for(int i = 0; i < list.size(); i++)
	{
		BuyMoneyItem* item = BuyMoneyItem::create(NULL);
		item->setData(i);
		item->setPosition(ccp(0, contentPos.y - (i + 1) * 124));
		mScrollView->getContainer()->addChild(item);
	}
}

void BuyMoneyDialog::_onNotification( CCObject* object )
{
	CCLOG("BuyMoneyDialog::%s()", __FUNCTION__);
	
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());

	if (name == kNCBuyMoney)
	{
		FloatText::shared()->playAnim(gls("164"));
		close();
	}
}

void BuyMoneyDialog::onCloseBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	close();
}
