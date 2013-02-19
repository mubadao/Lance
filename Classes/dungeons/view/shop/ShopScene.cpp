#include "ShopScene.h"
#include "BuyMoneyItem.h"
#include "NCDefines.h"
#include "ShopProxy.h"
#include "StaticShop.h"
#include "AlertDialog.h"

ShopTab ShopScene::msCurTab = SHOP_TAB_LOTTERY;

ShopScene::ShopScene(void)
	: mTableView(NULL)
	, mScrollView(NULL)
{
	CCLOG("ShopScene::%s()", __FUNCTION__);
}

ShopScene::~ShopScene(void)
{
	CCLOG("ShopScene::%s()", __FUNCTION__);
	RemoveObserver(this);
	msCurTab = SHOP_TAB_LOTTERY;

	CC_SAFE_RELEASE(mScrollView);
}

bool ShopScene::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView *, mScrollView);
	return false;
}

void ShopScene::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("ShopScene::%s()", __FUNCTION__);
	mTableView = TableTextView::create(DEFAULT_FONT, TAB_FONT_SIZE, TAB_FONT_COLOR
		,"btn_33.png", "btn_33_d.png", SHOP_TAB_LOTTERY, gls("184")
		, "btn_32.png", "btn_32_d.png", SHOP_TAB_SHOP, gls("66")
//		,"sprite/btn_27.png","sprite/btn_27_d.png",SHOP_TAB_ITEM,gls("67")
		, NULL);
	mTableView->setTarget(this, callfuncO_selector(ShopScene::onTabClick));
	mTableView->alignItemsHorizontallyWithPadding(0);
	mTableView->setPosition(320, 808);
	addChild(mTableView);

	mLastScrollPos = CCPointZero;
	CCArray* nameList = CCArray::create(ccs(kNCOpenBox),NULL);
	RegisterObservers(this, nameList, callfuncO_selector(ShopScene::_onNotification));
	changeTab(msCurTab);
}

void ShopScene::refresh()
{
	clearList();
	if (msCurTab == SHOP_TAB_LOTTERY)
	{
		CCLayer* content = CCLayer::create();
		CCSize size = CCSizeMake(640, 1230);
		mScrollView->setContainer(content);
		mScrollView->setContentSize(size);
		mScrollView->setContentOffset(mLastScrollPos);
		
		CCSprite* sprite = CCSprite::create("bg_43.jpg");
		sprite->setPosition(ccp(size.width/2, size.height/2));
		content->addChild(sprite);

		xmlBoxList& itemList = StaticShop::shared()->mBox;
		CCPoint points[3] = { ccp(0, 830), ccp(0, 430), ccp(0, 30) };
		for(int i = 0; i < 3; i++)
		{
			ShopItem* item = ShopItem::create(NULL);
			if(i == 2 && ShopProxy::shared()->mRemainderOpenBoxTime == 0)
				item->setData(&itemList[i + 1]);
			else
				item->setData(&itemList[i]);
			item->setPosition(points[i]);
			content->addChild(item);
		}
	}
	else if(msCurTab == SHOP_TAB_SHOP || msCurTab == SHOP_TAB_ITEM)
	{
		xmlBuyMoneyList list = StaticShop::shared()->mBuyMoney;
		CCPoint contentPos = ccp(0, list.size() * 128);
		CCLayer* content = CCLayer::create();
		content->setContentSize(CCSizeMake(640, contentPos.y));
		mScrollView->setContainer(content);
		mScrollView->setContentOffset(mLastScrollPos);

		for(int i = 0; i < list.size(); i++)
		{
			BuyMoneyItem* item = BuyMoneyItem::create(NULL);
			item->setData(i);
			item->setPosition(ccp(9, contentPos.y - (i + 1) * 128));
			content->addChild(item);
		}
	}
}

void ShopScene::_onNotification(CCObject* object)
{
	CCLOG("ShopScene::%s()", __FUNCTION__);
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());
	
	if (name == kNCOpenBox)
	{
		OpenBoxResult* obr = (OpenBoxResult*)notification->getObject();
		if (obr->result == 1)
		{
			FRAMEWORK->popup("AwardEquipDialog", obr->equipInfo);
		}
		else if(obr->result == 2)
		{
			AlertDialog::initContent(gls("120"));
			FRAMEWORK->popup("AlertDialog");
		}
		refresh();
	}
}

void ShopScene::onTabClick(CCObject* pSender)
{
	CCMenuItem* menuItem = (CCMenuItem*)pSender;
	msCurTab = (ShopTab)(menuItem->getTag());
	changeTab(msCurTab);
}

void ShopScene::changeTab( ShopTab tab )
{
	msCurTab = tab;
	mTableView->selectItem(msCurTab);
	refresh();
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - mScrollView->getContainer()->getContentSize().height));
}

void ShopScene::clearList()
{
	mLastScrollPos = mScrollView->getContentOffset();
	mScrollView->setContainer(NULL);
}

