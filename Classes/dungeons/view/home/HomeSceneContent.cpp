#include "HomeSceneContent.h"
#include "UserProxy.h"
#include "MainMenu.h"
#include "StaticItem.h"
#include "ItemProxy.h"
#include "EquipIcon.h"
#include "NetController.h"

HomeSceneContent::HomeSceneContent()
	: mAttack(NULL)
	, mDefense(NULL)
	, mLife(NULL)
	, mAttackTitle(NULL)
	, mDefenseTitle(NULL)
	, mLifeTitle(NULL)
	, mAttributeBtn(NULL)
{
	CCLOG("HomeSceneContent::%s()", __FUNCTION__);
	for (int i = 0; i < 6; i++)
		mNodeEquip[i] = NULL;
}

HomeSceneContent::~HomeSceneContent()
{
	CCLOG("HomeSceneContent::%s()", __FUNCTION__);
	RemoveObserver(this);

	CC_SAFE_RELEASE(mAttack);
	CC_SAFE_RELEASE(mDefense);
	CC_SAFE_RELEASE(mLife);

	CC_SAFE_RELEASE(mAttackTitle);
	CC_SAFE_RELEASE(mDefenseTitle);
	CC_SAFE_RELEASE(mLifeTitle);
	CC_SAFE_RELEASE(mAttributeBtn);
	for (int i = 0; i < 6; i++)
		CC_SAFE_RELEASE(mNodeEquip[i]);
}

bool HomeSceneContent::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAttack", CCLabelTTF *, mAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDefense", CCLabelTTF *, mDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLife", CCLabelTTF *, mLife);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeWeapon", CCNode *, mNodeEquip[ITEM_KIND_WEAPON]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeHelm", CCNode *, mNodeEquip[ITEM_KIND_HELM]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeNecklace", CCNode *, mNodeEquip[ITEM_KIND_NECKLACE]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeCloth", CCNode *, mNodeEquip[ITEM_KIND_CLOTH]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeShoes", CCNode *, mNodeEquip[ITEM_KIND_SHOES]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeRing", CCNode *, mNodeEquip[ITEM_KIND_RING]);
	CCB_CCLABELTTF_GLUE(this, "mAttackTitle", mAttackTitle, gls("attack"));
	CCB_CCLABELTTF_GLUE(this, "mDefenseTitle", mDefenseTitle, gls("defense"));
	CCB_CCLABELTTF_GLUE(this, "mLifeTitle", mLifeTitle, gls("93"));
	CCB_CONTROLBUTTON_GLUE(this, "mAttributeBtn", mAttributeBtn, gls("144"));
	return false;
}

SEL_MenuHandler HomeSceneContent::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler HomeSceneContent::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAttributeBtnClick", HomeSceneContent::onAttributeBtnClick);
	return NULL;
}

void HomeSceneContent::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("HomeSceneContent::%s()", __FUNCTION__);
	CCArray* nameList = CCArray::create(ccs(kNCRegist), ccs(kNCGetSelfInfo), NULL);
	RegisterObservers(this, nameList, callfuncO_selector(HomeSceneContent::_onNotification));

	_refresh();
}

void HomeSceneContent::_refresh()
{
	// 基础数值
	UserVO& userVO = UserProxy::shared()->userVO;
	mAttack->setString(fcs("%d-%d", userVO.atkMin, userVO.atkMax));
	mDefense->setString(fcs("%d-%d", userVO.defMin, userVO.defMax));
	mLife->setString(fcs("%d", userVO.life));
	
	// 装备
	EquipList& equipList = ItemProxy::shared()->getEquipList();
	EquipList::iterator iter = equipList.begin();
	while(iter != equipList.end())
	{
		if((*iter)->state == 1)
		{
			ItemKind part = ItemProxy::shared()->getItemKind((*iter)->id);
			EquipIcon* itemIcon = EquipIcon::create(this);
			itemIcon->setInfo((*iter)->id);
			itemIcon->setScale(0.339);
			mNodeEquip[part]->addChild(itemIcon);
		}
		iter++;
	}
}

void HomeSceneContent::_onNotification(CCObject* object)
{
	CCLOG("HomeSceneContent::%s()", __FUNCTION__);
	
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = notification->getName();
	
	if (name == kNCRegist || name == kNCGetSelfInfo)
	{
		_refresh();
	}
}

void HomeSceneContent::onAttributeBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	FRAMEWORK->changeState("PlayerDetailScene");
}
