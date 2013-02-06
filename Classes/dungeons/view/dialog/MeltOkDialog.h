#ifndef _MeltOkDialog_H_
#define _MeltOkDialog_H_

#include "Global.h"
//#include "model/proxy/ItemProxy.h"

class MeltOkDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MeltOkDialog, create);

	MeltOkDialog();
	~MeltOkDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

	static EquipInfo* msEquipInfo;

private:
	CCLabelTTF* mTitle;
	CCLabelTTF* mDesc;
	CCLabelTTF* mGetEnergy;

	CCControlButton* mOkBtn;
	CCControlButton* mCancelBtn;

	void onOkBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onCancelBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);

	void _onNotification(CCObject* object);
	int _getMeltCost();
};

#endif