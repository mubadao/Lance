#ifndef _BuyMoneyItem_H_
#define _BuyMoneyItem_H_

#include "Global.h"

class BuyMoneyItem
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BuyMoneyItem, create);

	static BuyMoneyItem* create(CCObject* pOwer);

	BuyMoneyItem();
	~BuyMoneyItem();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	virtual void setData(int index);

private:
	CCLabelTTF* mMoney;
	CCLabelTTF* mDollor;
	CCControlButton* mBuyBtn;
	
	int mIndex;

	void onBuyBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif