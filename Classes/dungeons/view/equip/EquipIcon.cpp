#include "EquipIcon.h"
#include "EquipIconLoader.h"

EquipIcon::EquipIcon()
	: mBg(NULL)
	, mIcon(NULL)
{
	CCLOG("EquipIcon::%s()", __FUNCTION__);
}

EquipIcon::~EquipIcon()
{
	CCLOG("EquipIcon::%s()", __FUNCTION__);
	RemoveObserver(this);

	CC_SAFE_RELEASE(mBg);
	CC_SAFE_RELEASE(mIcon);
}

bool EquipIcon::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBg", CCSprite*, mBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIcon", CCSprite*, mIcon);
	return false;
}

void EquipIcon::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("EquipIcon::%s()", __FUNCTION__);
	RegisterObserver(this, callfuncO_selector(EquipIcon::_onNotification), FileDownload::notificationName, NULL);
}

void EquipIcon::_onNotification(CCObject* object)
{
	CCLOG("EquipIcon::%s()", __FUNCTION__);
	
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = notification->getName();
	CCObject* params = notification->getObject();
	if (name == FileDownload::notificationName)
	{
		CCString* filename1 = (CCString*)params;
		EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(mItemID);
		CCString* filename2 = CCString::create(equipStatic->icon);
		if(filename1->isEqual(filename2))
		{
			mIcon->initWithFile(filename1->getCString());
		}
		filename2->release();
	}
}

void EquipIcon::setInfo(int itemID)
{
	// 装备图
	mItemID = itemID;
	EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(itemID);

	string filename = "item/";
	filename += equipStatic->icon;
	mIcon->initWithFile(filename.c_str());
	
	//    std::string fileName = equipStatic->icon;
	//    std::string fileUrl = UserProxy::shared()->mServerUrl + fileName;
	//    CCLOG("download item icon fileUrl:%s;fileName:%s", fileUrl.c_str(),fileName.c_str());
	//    FileDownload::shared()->downloadFile(fileUrl.c_str(),fileName.c_str());

	// 背景图
	mQuality = (EquipQuality)equipStatic->quality;
	switch(mQuality)
	{
		case EQUIP_QUALITY_WHITE:
			mBg->initWithFile("equip_bg_white.png");
			break;
		case EQUIP_QUALITY_BLUE:
			mBg->initWithFile("equip_bg_blue.png");
			break;
		case EQUIP_QUALITY_YELLOW:
			mBg->initWithFile("equip_bg_yellow.png");
			break;
		case EQUIP_QUALITY_GOLD:
			mBg->initWithFile("equip_bg_gold.png");
			break;
		case EQUIP_QUALITY_PURPLE:
			mBg->initWithFile("equip_bg_purple.png");
			break;
		case EQUIP_QUALITY_ORANGE:
			mBg->initWithFile("equip_bg_orange.png");
			break;
	}
}

EquipIcon* EquipIcon::create( CCObject* pOwer )
{
	return (EquipIcon*)ReadItem("EquipIcon", EquipIconLoader::loader());
}
