#ifndef _UserInfo_H_
#define _UserInfo_H_

#include "Global.h"

class UserInfo
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(UserInfo, create);

	UserInfo();
	~UserInfo();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void refresh();
	void refreshEnergy();

private:
	CCLabelTTF* mLevel;
	CCLabelTTF* mName;
	CCLabelTTF* mEnergy;
	CCLabelTTF* mPower;
	CCLabelTTF* mCoin;
	CCLabelTTF* mMoney;
	ProgressText* mProgress;

	CCLabelTTF* mNextEnergyTitle;
	CCLabelTTF* mEnergyTime;
	
	CCControlButton* mBtnBg;
	CCControlButton* mBtnAddMoney;
	CCControlButton* mBtnAddCoin;
	CCControlButton* mBtnAddEnergy;
	
	void _onNotification(CCObject* object);
	
public:
	void setLevel(unsigned int level);
	void setUserName(char* name);
	void setEnergy(unsigned int cur, unsigned int max);
	void setGold(unsigned int gold);
	void setExp(unsigned int exp);

	void onBtnBg(CCObject * pSender);
	void onBtnAddEnergy(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onBtnAddMoney(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onBtnAddCoin(CCObject * pSender, CCControlEvent pCCControlEvent);

	void updateEnergyTime(float object);
	void buyCoin(CCObject* object);
	void buyEnergy();
};

#endif