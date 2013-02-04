#include "ShopScene.h"
#include "BuyMoneyItem.h"
#include "NCDefines.h"
#include "ShopProxy.h"
#include "StaticShop.h"
#include "AlertDialog.h"
#include "AwardEquipDialog.h"

ShopTab ShopScene::msCurTab = SHOP_TAB_LOTTERY;

ShopScene::ShopScene(void)
	: mTableView(NULL)
	, mScrollView(NULL)
{
}

ShopScene::~ShopScene(void)
{
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
		BoxStaticList itemList;
		BoxStaticList& boxStaticList = StaticShop::shared()->mBoxStaticList;
		
		itemList.push_back(boxStaticList[0]);
		itemList.push_back(boxStaticList[1]);
		if(ShopProxy::shared()->mRemainderOpenBoxTime == 0)
			itemList.push_back(boxStaticList[3]);
		else
			itemList.push_back(boxStaticList[2]);
		
		CCLayer* content = CCLayer::create();
		CCSize size = CCSizeMake(640, 1230);
		mScrollView->setContainer(content);
		mScrollView->setContentSize(size);
		mScrollView->setContentOffset(mLastScrollPos);
		
		CCSprite* sprite = CCSprite::create("bg_43.jpg");
		sprite->setPosition(ccp(size.width/2, size.height/2));
		content->addChild(sprite);

		vector<CCPoint> points;
		points.push_back(ccp(0, 830));
		points.push_back(ccp(0, 430));
		points.push_back(ccp(0, 30));
		for(int i = 0; i < itemList.size(); i++)
		{
			ShopItem* item = ShopItem::create(NULL);
			item->setData(itemList[i]);
			item->setPosition(points[i]);
			content->addChild(item);
		}
	}
	else if(msCurTab == SHOP_TAB_SHOP || msCurTab == SHOP_TAB_ITEM)
	{
		BuyMoneyStaticList list = StaticShop::shared()->getBuyMoneyStaticList();
		CCPoint contentPos = ccp(0, list.size() * 124);
		CCLayer* content = CCLayer::create();
		content->setContentSize(CCSizeMake(640, contentPos.y));
		mScrollView->setContainer(content);
		mScrollView->setContentOffset(mLastScrollPos);

		for(int i = 0; i < list.size(); i++)
		{
			BuyMoneyItem* item = BuyMoneyItem::create(NULL);
			item->setData(i);
			item->setPosition(ccp(0, contentPos.y - (i + 1) * 124));
			content->addChild(item);
		}
	}
}

void ShopScene::_onNotification( CCObject* object )
{
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());
	
	if (name == kNCOpenBox)
	{
		SellResult& sellResult = ShopProxy::shared()->mSellResult;
		if (sellResult.result == 1 && sellResult.mEquipInfo != NULL)
		{
			gsEquipInfo = sellResult.mEquipInfo;
			FRAMEWORK->popup("AwardEquipDialog");
		}
		else if(sellResult.result == 2)
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

