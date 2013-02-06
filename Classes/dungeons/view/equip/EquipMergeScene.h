#ifndef _EquipMergeScene_H_
#define _EquipMergeScene_H_

#include "Global.h"
#include "EquipIcon.h"
#include "MoneyIcon.h"

class EquipMergeScene
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EquipMergeScene, create);

	EquipMergeScene();
	~EquipMergeScene();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
	static EquipInfo* msEquipInfo;

private:
	CCLabelTTF* mName;
	CCLabelTTF* mType;
	CCLabelTTF* mIntensifyCount;
	CCLabelTTF* mPropertyTitle;
	CCLabelTTF* mProperty;
	CCLabelTTF* mPreviewTitle;
	CCLabelTTF* mAddPropertyTitle;
	CCLabelTTF* mAddProperty;
	CCLabelTTF* mPerfectTitle;
	CCLabelTTF* mPerfect;
	CCLabelTTF* mZhuRongTitle;
	CCLabelTTF* mZhuRongCount;
	CCLabelTTF* mZhuRongCostTitle;
	CCLabelTTF* mZhuRongDesc;
	CCLabelTTF* mFusionTitle;
	CCLabelTTF* mFusion;
	CCLabelTTF* mNeedFusionTitle;
	CCLabelTTF* mNeedFusion;
	CCLabelTTF* mNeedCoinTitle;
	CCLabelTTF* mNeedCoin;

	CCControlButton* mSubZhuRongBtn;
	CCControlButton* mAddZhuRongBtn;
	CCControlButton* mResetBtn;
	CCControlButton* mAddIntensifyBtn;
	CCControlButton* mFusionBtn;
	CCControlButton* mReturnBtn;

	MoneyIcon* mZhuRongCostIcon;
	EquipIcon* mEquipIcon;

	CCProgressTimer* mStarProgress;
	
	int curSelect;
	bool isChangeEquip;
	int mZhuRongJiCount;
	int mQiangHuaCount;
	
	void _onNotification(CCObject* object);
		
	void onSubZhuRongBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onAddZhuRongBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onResetBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onAddIntensifyBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onIntensifyBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onReturnBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	
	void _refresh();
	void _refreshZhuRongCount();
	void _refreshPerfect();
	void _refreshAddProperty();
	void _refreshFusion();
	void _refreshStarLevel();
	void _buyFusion();
};

#endif