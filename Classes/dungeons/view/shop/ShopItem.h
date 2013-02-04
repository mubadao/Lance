#ifndef _ShopItem_h__
#define _ShopItem_h__

#include "Global.h"
#include "MoneyIcon.h"
#include "StaticShop.h"

class ShopItem
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ShopItem, create);

	static ShopItem* create(CCObject* pOwer);

	ShopItem();
	~ShopItem();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void setData(BoxStatic* data);

private:
	CCSprite* mBg;
	CCSprite* mRect;
	CCLabelTTF* mFree;
	CCControlButton* mUseBtn;
	MoneyIcon* mMoneyIcon;
	
	BoxStatic* mData;
	
	void onUseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	
};

#endif