#ifndef _EquipItem_H_
#define _EquipItem_H_

#include "Global.h"
#include "EquipIcon.h"

class EquipItem
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipItem, create);

	static EquipItem* create(CCObject* pOwer);

	EquipItem();
	~EquipItem();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
	void setInfo(EquipInfo* data);

private:
	CCLabelTTF* mName;
	CCLabelTTF* mLevel;
	CCLabelTTF* mProperty;
	EquipIcon* mEquipIcon;
	CCControlButton* mAttributeBtn;
	
	EquipInfo* mInfo;

	void onBgClick(CCObject* pSender);
	void onAttributeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void _onNotification(CCObject* pSender);
};

#endif