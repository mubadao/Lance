#include "ChallengeItem.h"
#include "UserProxy.h"
#include "ChallengeItemLoader.h"

ChallengeItem::ChallengeItem()
	: mName(NULL)
	, mLevel(NULL)
	, mAttack(NULL)
	, mDefense(NULL)
	, mChallengeBtn(NULL)
	, mData(NULL)
{
	CCLOG("ChallengeItem::%s()", __FUNCTION__);
}

ChallengeItem::~ChallengeItem()
{
	CCLOG("ChallengeItem::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mName);
	CC_SAFE_RELEASE(mLevel);
	CC_SAFE_RELEASE(mAttack);
	CC_SAFE_RELEASE(mDefense);
	CC_SAFE_RELEASE(mChallengeBtn);
}

SEL_MenuHandler ChallengeItem::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler ChallengeItem::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChallengeBtnClick", ChallengeItem::onChallengeBtnClick);
	return NULL;
}

bool ChallengeItem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF *, this->mName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel", CCLabelTTF *, this->mLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAttack", CCLabelTTF *, this->mAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDefense", CCLabelTTF *, this->mDefense);
	CCB_CONTROLBUTTON_GLUE(this, "mChallengeBtn", mChallengeBtn, gls("87"));
	return false;
}

void ChallengeItem::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("ChallengeItem::%s()", __FUNCTION__);
	mDefense->setString(fcs("%s: ???", gls("Defense")));
}

void ChallengeItem::setData(ChallengeEnemyInfo* data)
{
	mData = data;

	mName->setString(data->name.c_str());
	mLevel->setString(fcs("LV.%d", data->level));
	mAttack->setString(fcs("%s: %d-%d", gls("Attack"), data->atkMin, data->atkMax));
}

void ChallengeItem::onChallengeBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
    if(UserProxy::shared()->userVO.powerCur <= 0)
    {
		FRAMEWORK->popup("StaminaLackDialog");
    }
    else 
    {
        ChanllengeProxy::shared()->mCurChallengeEnemyInfo = mData;
        FRAMEWORK->popup("ChallengePreviewDialog");
    }
}

ChallengeItem* ChallengeItem::create(CCObject* pOwer)
{
	return (ChallengeItem*)ReadItem("ChallengeItem", ChallengeItemLoader::loader());
}

