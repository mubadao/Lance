#ifndef _AwardEquipDialog_H_
#define _AwardEquipDialog_H_

#include "Global.h"
#include "EquipDetail.h"

class AwardEquipDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AwardEquipDialog, create);

	AwardEquipDialog();
	~AwardEquipDialog();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mTitle;
	EquipDetail* mEquipDetail;
	CCControlButton* mCloseBtn;
	
	void onCloseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif