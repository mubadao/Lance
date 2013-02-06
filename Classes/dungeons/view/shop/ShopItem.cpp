#include "ShopItem.h"
#include "ShopItemLoader.h"
#include "MoneyIconLoader.h"
#include "ItemProxy.h"
#include "NetController.h"
#include "AlertDialog.h"

ShopItem::ShopItem(void)
	: mMoneyIcon(NULL)
	, mFree(NULL)
	, mUseBtn(NULL)
	, mBg(NULL)
	, mRect(NULL)
{
	CCLOG("ShopItem::%s()", __FUNCTION__);
}

ShopItem::~ShopItem(void)
{
	CCLOG("ShopItem::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mFree);
	CC_SAFE_RELEASE(mUseBtn);
	CC_SAFE_RELEASE(mBg);
	CC_SAFE_RELEASE(mRect);
	CC_SAFE_RELEASE(mMoneyIcon);
}

bool ShopItem::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBg", CCSprite*, mBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRect", CCSprite*, mRect);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMoneyIconNode", MoneyIcon*, mMoneyIcon);
	CCB_CONTROLBUTTON_GLUE(this, "mUseBtn", mUseBtn, gls("136"));
	CCB_CCLABELTTF_GLUE(this, "mFree", mFree, gls("189"));
	return false;
}

SEL_MenuHandler ShopItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler ShopItem::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onUseBtnClick", ShopItem::onUseBtnClick);
	return NULL;
}

void ShopItem::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("ShopItem::%s()", __FUNCTION__);
}

void ShopItem::setData(BoxStatic* data)
{
	mData = data;
	MoneyType moneyType = data->costType.getMoneyType();

	if (moneyType == MONEY_TYPE_FREE)
	{
		mFree->setVisible(true);
		mMoneyIcon->setVisible(false);
	}
	else
	{
		mFree->setVisible(false);
		mMoneyIcon->setVisible(true);
		mMoneyIcon->setType(moneyType);
		mMoneyIcon->setCount(data->costType.getCostCount());
	}
	
	if(data->id == 27001)
	{
		mRect->initWithFile("bg_39.png");
		mBg->initWithFile("bg_40.jpg");
	}
	else if(data->id == 27002)
	{
		mRect->initWithFile("bg_41.png");
		CCPoint point = mRect->getPosition();
		mRect->setPosition(ccp(point.x, point.y-5));
		mBg->initWithFile("bg_48.jpg");
	}
	else if(data->id == 27003 || data->id == 27004)
	{
		mRect->initWithFile("bg_42.png");
		CCPoint point = mRect->getPosition();
		mRect->setPosition(ccp(point.x, point.y-11));
		mBg->initWithFile("bg_49.jpg");
	}
}

void ShopItem::onUseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	if(ItemProxy::shared()->isBagFull())
	{
		AlertDialog::initContent(gls("191"));
		FRAMEWORK->popup("AlertDialog");
	}
	else {
		NetController::shared()->openBox(mData->costType.getMoneyType(),mData->id);
	}
}

ShopItem* ShopItem::create(CCObject* pOwer)
{
	CCNodeLoaderLibrary* pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

	pLoaderLibrary->registerCCNodeLoader("MoneyIcon", MoneyIconLoader::loader());
	pLoaderLibrary->registerCCNodeLoader("ShopItem", ShopItemLoader::loader());
	
	CCBReader* ccbReader = new CCBReader(pLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("ShopItem.ccbi", NULL);
	ccbReader->release();
	return (ShopItem*)node;
}
