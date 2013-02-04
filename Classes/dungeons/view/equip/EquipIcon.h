#ifndef _EquipIcon_H_
#define _EquipIcon_H_

#include "Global.h"
#include "ItemProxy.h"

class EquipIcon
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipIcon, create);

	static EquipIcon* create(CCObject* pOwer);

	EquipIcon();
	~EquipIcon();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
	void setInfo(int itemID);
	void _onNotification( CCObject* object );
	
private:
	CCSprite* mBg;
	CCSprite* mIcon;

	int mItemID;
	EquipQuality mQuality;
};

#endif