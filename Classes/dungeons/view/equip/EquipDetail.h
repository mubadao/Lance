#ifndef _EquipDetail_h__
#define _EquipDetail_h__

#include "Global.h"
#include "EquipIcon.h"
#include "EquipDetailContent.h"

class EquipDetail
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipDetail, create);
	static EquipDetail* create(CCObject* pOwer);

	EquipDetail();
	~EquipDetail();
	
	void refresh();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCScrollView* mScrollView;
};

#endif