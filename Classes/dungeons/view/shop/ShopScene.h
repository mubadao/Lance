#ifndef _ShopScene_H_
#define _ShopScene_H_

#include "Global.h"
#include "ShopItem.h"

enum ShopTab
{
	SHOP_TAB_LOTTERY=0,
	SHOP_TAB_SHOP,
	SHOP_TAB_ITEM
};

class ShopScene
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ShopScene, create);

	ShopScene();
	~ShopScene();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void refresh();

	static ShopTab msCurTab;
	
private:
	CCScrollView* mScrollView;
	TableTextView* mTableView;
	
	CCPoint mLastScrollPos;
	
	void changeTab(ShopTab tab);
	void clearList();
	void _onNotification(CCObject* object);

	void onTabClick(CCObject* pSender);
};

#endif