#ifndef _EquipDetailContent_H_
#define _EquipDetailContent_H_

#include "Global.h"
#include "EquipIcon.h"

class EquipDetailContent
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipDetailContent, create);

	static EquipDetailContent* create(CCObject* pOwer);

	EquipDetailContent();
	~EquipDetailContent();
	
	void refresh();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mName;
	CCLabelTTF* mLevel;
	CCLabelTTF* mType;
	CCLabelTTF* mProperty;
	CCLabelTTF* mCurProperty;
	CCLabelTTF* mAffixTitle[6];
	CCLabelTTF* mAffixValue[6];
	EquipIcon* mEquipIcon;
};

#endif