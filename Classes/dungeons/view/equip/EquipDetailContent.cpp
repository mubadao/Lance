#include "EquipDetailContent.h"
#include "EquipDetailContentLoader.h"
#include "EquipIconLoader.h"

EquipDetailContent::EquipDetailContent()
	: mName(NULL)
	, mLevel(NULL)
	, mType(NULL)
	, mProperty(NULL)
	, mCurProperty(NULL)
	, mEquipIcon(NULL)
{
	CCLOG("EquipDetailContent::%s()", __FUNCTION__);
	for (int i = 0; i < 6; i++)
	{
		mAffixTitle[i] = NULL;
		mAffixValue[i] = NULL;
	}
}

EquipDetailContent::~EquipDetailContent(void)
{
	CCLOG("EquipDetailContent::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mName);
	CC_SAFE_RELEASE(mLevel);
	CC_SAFE_RELEASE(mType);
	CC_SAFE_RELEASE(mProperty);
	CC_SAFE_RELEASE(mCurProperty);
	for (int i = 0; i < 6; i++)
	{
		CC_SAFE_RELEASE(mAffixTitle[i]);
		CC_SAFE_RELEASE(mAffixValue[i]);
	}
}

bool EquipDetailContent::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF*, mName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel", CCLabelTTF*, mLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mType", CCLabelTTF*, mType);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProperty", CCLabelTTF*, mProperty);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCurProperty", CCLabelTTF*, mCurProperty);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixTitle1", CCLabelTTF*, mAffixTitle[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixValue1", CCLabelTTF*, mAffixValue[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixTitle2", CCLabelTTF*, mAffixTitle[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixValue2", CCLabelTTF*, mAffixValue[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixTitle3", CCLabelTTF*, mAffixTitle[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixValue3", CCLabelTTF*, mAffixValue[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixTitle4", CCLabelTTF*, mAffixTitle[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixValue4", CCLabelTTF*, mAffixValue[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixTitle5", CCLabelTTF*, mAffixTitle[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixValue5", CCLabelTTF*, mAffixValue[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixTitle6", CCLabelTTF*, mAffixTitle[5]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAffixValue6", CCLabelTTF*, mAffixValue[5]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipIcon", EquipIcon*, mEquipIcon);
	return false;
}

void EquipDetailContent::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("EquipDetailContent::%s()", __FUNCTION__);
	EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(gsEquipInfo->id);
	
	mName->setColor(gsEquipInfo->getNameColor());
	mName->setString(equipStatic->name);
	mLevel->setString(fcs("lv %d", gsEquipInfo->level));
	mType->setString(ItemProxy::shared()->getTypeTitle(gsEquipInfo->id));
	
	mProperty->setString(fcs("%s:%s", gsEquipInfo->getPropertyTitle(), gsEquipInfo->getBasePropertyStr()));
	
	for (int i = 0; i < 6; i++)
	{
		mAffixTitle[i]->setVisible(false);
		mAffixValue[i]->setVisible(false);
	}
	
	AffixList& affixList = gsEquipInfo->affixs;
	for (int i = 0; i < affixList.size(); i++)
	{
		if(i >= 6)
			break;
		
		Affix* affix = affixList[i];
		mAffixTitle[i]->setString(affix->getTitle());
		if(affix->isPer())
			mAffixValue[i]->setString(fcs("+%d%%", affix->value));
		else
			mAffixValue[i]->setString(fcs("+%d", affix->value));
		mAffixTitle[i]->setVisible(true);
		mAffixValue[i]->setVisible(true);
	}
	
	mEquipIcon->setInfo(gsEquipInfo->id);
	
	EquipInfo* putEquipInfo = ItemProxy::shared()->getPutOnEquip(gsEquipInfo->getKind());
	if(NULL == putEquipInfo)
	{
		mCurProperty->setVisible(false);
	}
	else
	{
		mCurProperty->setVisible(true);
		mCurProperty->setString(fcs("%s:%s", gls("200"), putEquipInfo->getBasePropertyStr()));
	}
}

EquipDetailContent* EquipDetailContent::create( CCObject* pOwer )
{
	CCNodeLoaderLibrary* pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	
	pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
	pLoaderLibrary->registerCCNodeLoader("EquipDetailContent", EquipDetailContentLoader::loader());
	
	CCBReader* ccbReader = new CCBReader(pLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("EquipDetailContent.ccbi", NULL);
	ccbReader->release();
	return (EquipDetailContent*)node;
}
