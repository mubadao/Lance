#ifndef _DungeonsItem_H_
#define _DungeonsItem_H_

#include "Global.h"

class DungeonsItem
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	DungeonsItem();
	~DungeonsItem();

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DungeonsItem, create);

	static DungeonsItem* create(CCObject* pOwer);

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void setInfo(int dungeonId, int floorId);

private:
	CCLabelTTF* mName;
	CCSprite* mLock;
	CCControlButton* mGoBtn;
	CCNode* mNodeBg;
	
	int mDungeonID;
	int mFloorID;

	void onGoBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void _gotoExplore();
};

#endif