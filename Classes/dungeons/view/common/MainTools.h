#ifndef _MainTools_H_
#define _MainTools_H_

#include "Global.h"

class MainTools
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainTools, create);

	MainTools();
	~MainTools();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCControlButton* mBtnBg;
	CCControlButton* mTaskBtn;
	CCControlButton* mDungeonListBtn;
	CCControlButton* mEquipBtn;
	CCControlButton* mAttributeBtn;
	CCControlButton* mOpenboxBtn;
	CCControlButton* mShopBtn;
	CCControlButton* mChallengeBtn;

	void onBtnBg(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onTaskBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onDungeonListBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onEquipBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onAttributeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onOpenboxBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onShopBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onChallengeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif