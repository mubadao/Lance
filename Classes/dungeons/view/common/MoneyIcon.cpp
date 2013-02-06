#include "MoneyIcon.h"

MoneyIcon::MoneyIcon()
: mIcon(NULL)
	, mCount(NULL)
{
	CCLOG("MoneyIcon::%s()", __FUNCTION__);
}

MoneyIcon::~MoneyIcon()
{
	CCLOG("MoneyIcon::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mIcon);
	CC_SAFE_RELEASE(mCount);
}

bool MoneyIcon::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIcon", CCSprite*, mIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCount", CCLabelTTF*, mCount);
	return false;
}

void MoneyIcon::setType(MoneyType type)
{
	if (type == MONEY_TYPE_GOLD)
	{
		mIcon->initWithFile("money_gold.png");
	}
	else if(type == MONEY_TYPE_MONEY)
	{
		mIcon->initWithFile("money_money.png");
	}
}

void MoneyIcon::setCount(int value)
{
	mCount->setString(fcs("%d", value));
}

