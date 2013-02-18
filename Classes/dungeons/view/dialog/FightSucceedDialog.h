#ifndef _FightSucceedDialog_H_
#define _FightSucceedDialog_H_

#include "Global.h"
#include "EquipDetail.h"

class FightSucceedDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FightSucceedDialog, create);

	FightSucceedDialog();
	~FightSucceedDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName){return NULL;}
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
	virtual void refresh();

private:
	CCLabelTTF* mGold;
	CCLabelTTF* mExp;

	CCLabelTTF* mTitle;
	CCLabelTTF* mTalk;

	EquipDetail* mEquipDetail;
	CCControlButton* mReturnBtn;
	
	void onReturnBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void _onNotification( CCObject* object );
};
#endif
