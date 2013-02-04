#include "PacketScene.h"
#include "NetController.h"
#include "AlertDialog.h"

PackTab PacketScene::msCurTab = PACK_TAB_EQUIP;
EquipFilterType PacketScene::msSortKind = EQUIP_FILTER_BY_ALL;

PacketScene::PacketScene()
	: mScrollView(NULL)
	, mBagCount(NULL)
{
}

PacketScene::~PacketScene()
{
	RemoveObserver(this);

	CC_SAFE_RELEASE(mScrollView);
	CC_SAFE_RELEASE(mBagCount);
}

bool PacketScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView*, mScrollView);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBagCount", CCLabelTTF*, mBagCount);
	return false;
}

void PacketScene::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	ComboBox* combobox = ComboBox::create("commobox_upskin.png","commobox_downskin.png","commobox_item_upskin.png","commobox_item_downskin.png");
	combobox->addItem(gls("helm"), EQUIP_FILTER_BY_HELM);
	combobox->addItem(gls("necklace"), EQUIP_FILTER_BY_NECKLACE);
	combobox->addItem(gls("weapon"), EQUIP_FILTER_BY_WEAPON);
	combobox->addItem(gls("cloth"), EQUIP_FILTER_BY_CLOTH);
	combobox->addItem(gls("ring"), EQUIP_FILTER_BY_RING);
	combobox->addItem(gls("shoes"), EQUIP_FILTER_BY_SHOES);
	combobox->addItem(gls("177"), EQUIP_FILTER_BY_ALL);
	combobox->addItem(gls("178"), EQUIP_FILTER_BY_PUTON);
	combobox->addItem(gls("179"), EQUIP_FILTER_BY_TAKEOFF);
	combobox->setTarget(this, callfuncO_selector(PacketScene::onEquipTypeSortSelect));
	combobox->selectItem(msSortKind);
	combobox->setPosition(-160, 343);
	addChild(combobox);
	
	CCArray* nameList = CCArray::create(ccs(kNCLoadEquipage), ccs(kNCUnloadEquipage), ccs(kNCSellEquipage), ccs(kNCFusionEquipage), NULL);
	RegisterObservers(this, nameList, callfuncO_selector(PacketScene::_onNotification));

	mLastScrollPos = CCPointZero;	
	_refresh();
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - mScrollView->getContainer()->getContentSize().height));
	
	int magMax = ItemProxy::shared()->getBagMax();
	int bagCount = ItemProxy::shared()->getEquipCount();

	if(magMax - bagCount <= 2)
	{
		AlertDialog::initContent(gls("192"));
		FRAMEWORK->popup("AlertDialog");
	}
}

void PacketScene::_onNotification(CCObject* object)
{
	NotificationObserver* observer = (NotificationObserver*)object;
	string name(observer->getName());
	
	if (name == kNCLoadEquipage || name == kNCUnloadEquipage || name == kNCSellEquipage || name == kNCFusionEquipage)
	{
		_refresh();

		if(name == kNCLoadEquipage)
			FloatText::shared()->playAnim(gls("195"));
		else if(name == kNCUnloadEquipage)
			FloatText::shared()->playAnim(gls("196"));
	}
}

void PacketScene::_refresh()
{
	mBagCount->setString(fcs("%d/%d", ItemProxy::shared()->getEquipCount(), ItemProxy::shared()->mBagMax));
	
	mLastScrollPos = mScrollView->getContentOffset();
	mScrollView->setContainer(NULL);
	
	EquipList equipList = _getEquipList(msSortKind);
	CCPoint contentPos = ccp(0, equipList.size() * 158);
	CCLayer* content = CCLayer::create();
	mScrollView->setContainer(NULL);
	mScrollView->setContainer(content);
	mScrollView->setContentSize(CCSizeMake(640, contentPos.y));
	mScrollView->setContentOffset(mLastScrollPos);
	for(int i = 0; i < equipList.size(); i++)
	{
		EquipItem* item = EquipItem::create(NULL);
		item->setInfo(equipList[i]);
		item->setPosition(ccp(0, contentPos.y - (i + 1) * 158));
		content->addChild(item);
	}
}

void PacketScene::onEquipTypeSortSelect(CCObject* object)
{
	ToggleItem* item = (ToggleItem*)object;
	msSortKind = (EquipFilterType)item->getTag();
	_refresh();
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - mScrollView->getContainer()->getContentSize().height));
}

EquipList PacketScene::_getEquipList(EquipFilterType type)
{
	EquipList& equipList1 = ItemProxy::shared()->getEquipList();
	EquipList rtn;
	
	if(type >= EQUIP_FILTER_BY_HELM && type <= EQUIP_FILTER_BY_SHOES)
	{
		for (int i = 0; i < equipList1.size(); i++)
		{
			ItemKind kind = ItemProxy::shared()->getItemKind(equipList1[i]->id);
			if(type == (EquipFilterType)kind)
				rtn.push_back(equipList1[i]);
		}
	}
	else if(type == EQUIP_FILTER_BY_ALL)
	{
		rtn = equipList1;
	}
	else if(type == EQUIP_FILTER_BY_PUTON)
	{
		for (int i = 0; i < equipList1.size(); i++)
		{
			if(equipList1[i]->isPutOn())
				rtn.push_back(equipList1[i]);
		}
	}
	else if(type == EQUIP_FILTER_BY_TAKEOFF)
	{
		for (int i = 0; i < equipList1.size(); i++)
		{
			if(!equipList1[i]->isPutOn())
				rtn.push_back(equipList1[i]);
		}
	}
	
	return rtn;
}
