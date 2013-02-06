#include "EquipItem.h"
#include "EquipIconLoader.h"
#include "EquipItemLoader.h"

EquipItem::EquipItem()
	: mName(NULL)
	, mLevel(NULL)
	, mProperty(NULL)
	, mAttributeBtn(NULL)
	, mEquipIcon(NULL)
	, mInfo(NULL)
{
	CCLOG("EquipItem::%s()", __FUNCTION__);
}

EquipItem::~EquipItem()
{
	CCLOG("EquipItem::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mName);
	CC_SAFE_RELEASE(mLevel);
	CC_SAFE_RELEASE(mProperty);
	CC_SAFE_RELEASE(mAttributeBtn);
	CC_SAFE_RELEASE(mEquipIcon);
}

bool EquipItem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF*, mName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel", CCLabelTTF*, mLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProperty", CCLabelTTF*, mProperty);
	CCB_CONTROLBUTTON_GLUE(this, "mAttributeBtn", mAttributeBtn, gls("91"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipIcon", EquipIcon*, mEquipIcon);
	return false;
}

SEL_MenuHandler EquipItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler EquipItem::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAttributeBtnClick", EquipItem::onAttributeBtnClick);
	return NULL;
}

void EquipItem::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("EquipItem::%s()", __FUNCTION__);
}

void EquipItem::setInfo(EquipInfo* data)
{
	mInfo = data;
	EquipStatic* itemInfo = StaticItem::shared()->getEquipInfo(data->id);

	mName->setColor(data->getNameColor());
	mName->setString(itemInfo->name);
	mLevel->setString(fcs("%s LV.%d", ItemProxy::shared()->getTypeTitle(data->id), data->level));
	mProperty->setString(fcs("%s: %s", data->getPropertyTitle(), data->getAttachPropertyStr()));
	
	mEquipIcon->setInfo(data->id);
}

void EquipItem::onAttributeBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	gsEquipInfo = mInfo;
	FRAMEWORK->popup("EquipDetailDialog");
}

EquipItem* EquipItem::create(CCObject* pOwer)
{
	CCNodeLoaderLibrary* pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	
	pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
	pLoaderLibrary->registerCCNodeLoader("EquipItem", EquipItemLoader::loader());
	
	CCBReader* ccbReader = new CCBReader(pLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("EquipItem.ccbi", NULL);
	ccbReader->release();
	return (EquipItem*)node;
}

