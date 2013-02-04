#include "EquipLevelUpDialog.h"
#include "utils/LocalString.h"
#include "EquipIcon.h"

EquipLevelUpDialog::EquipLevelUpDialog(void)
	:mLastLevel(NULL),mCurLevel(NULL),mLastAttack(NULL),mCurAttack(NULL),
	mLastDefense(NULL),mCurDefense(NULL),mLastLife(NULL),mCurLife(NULL)
	,mAttackTitle(NULL),mDefenseTitle(NULL),mLifeTitle(NULL)
{
}

EquipLevelUpDialog::~EquipLevelUpDialog(void)
{
	CC_SAFE_RELEASE(mLastLevel);
	CC_SAFE_RELEASE(mCurLevel);
	CC_SAFE_RELEASE(mLastAttack);
	CC_SAFE_RELEASE(mCurAttack);
	CC_SAFE_RELEASE(mLastDefense);
	CC_SAFE_RELEASE(mCurDefense);
	CC_SAFE_RELEASE(mLastLife);
	CC_SAFE_RELEASE(mCurLife);
	CC_SAFE_RELEASE(mAttackTitle);
	CC_SAFE_RELEASE(mDefenseTitle);
	CC_SAFE_RELEASE(mLifeTitle);
}

bool EquipLevelUpDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLastLevel", CCLabelTTF *, mLastLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCurLevel", CCLabelTTF *, mCurLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLastAttack", CCLabelTTF *, mLastAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCurAttack", CCLabelTTF *, mCurAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLastDefense", CCLabelTTF *, mLastDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCurDefense", CCLabelTTF *, mCurDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLastLife", CCLabelTTF *, mLastLife);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCurLife", CCLabelTTF *, mCurLife);
	CCB_CCLABELTTF_GLUE(this, "mAttackTitle", mAttackTitle, gls("attack"));
	CCB_CCLABELTTF_GLUE(this, "mDefenseTitle", mDefenseTitle, gls("defense"));
	CCB_CCLABELTTF_GLUE(this, "mLifeTitle", mLifeTitle, gls("93"));
	return false;
}

bool EquipLevelUpDialog::init()
{
	return true;
}

SEL_MenuHandler EquipLevelUpDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDoItClick", EquipLevelUpDialog::onDoItClick);
	return NULL;
}

SEL_CCControlHandler EquipLevelUpDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

void EquipLevelUpDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{

}

void EquipLevelUpDialog::onEnter()
{
	Dialog::onEnter();
}

void EquipLevelUpDialog::onExit()
{
	Dialog::onExit();
}

void EquipLevelUpDialog::refresh()
{
	EquipInfo* lastMergeInfo = ItemProxy::shared()->lastQiangHuaEquip;
	EquipInfo* curMergeInfo = ItemProxy::shared()->curQiangHuaEquip;
	mLastLevel->setString(fls("92",lastMergeInfo->level));
	mCurLevel->setString(fls("92",curMergeInfo->level));
	mLastAttack->setString(itos(lastMergeInfo->atkMax));
	mCurAttack->setString(itos(curMergeInfo->atkMax));
	mLastDefense->setString(itos(lastMergeInfo->defMin));
	mCurDefense->setString(itos(curMergeInfo->defMin));
	mLastLife->setString(itos(lastMergeInfo->life));
	mCurLife->setString(itos(curMergeInfo->life));
    EquipIcon* itemIcon = EquipIcon::create(this);
    itemIcon->setInfo(curMergeInfo->id);
    itemIcon->setScale(0.4);
    itemIcon->setPosition(ccp(13, 239));
    addChild(itemIcon);
}

void EquipLevelUpDialog::_onNotification( CCObject* pSender )
{

}

void EquipLevelUpDialog::onDoItClick(CCObject* pSender)
{
    
}

void EquipLevelUpDialog::onMergeBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{

}

void EquipLevelUpDialog::touchScreen()
{
	close();
}
