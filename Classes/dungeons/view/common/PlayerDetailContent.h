#ifndef _PlayerDetailContent_H_
#define _PlayerDetailContent_H_

#include "Global.h"

class PlayerDetailContent
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PlayerDetailContent, create);

	PlayerDetailContent();
	~PlayerDetailContent();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	bool init();
	void refresh();
	void refreshEnergy();

private:
	int mCurLifeValue;
	int mAddLifeValue;
	int mCurEnergyValue;
	int mAddEnergyValue;
	int mCurProficiency;
	int mMaxProficiency;
	
	CCLabelTTF* mBaseTitle;
	CCLabelTTF* mName;                  // 昵称
	CCLabelTTF* mLevel;                 // 等级
	CCLabelTTF* mExp;                   // 经验
	CCLabelTTF* mCoin;                  // 铜币
	CCLabelTTF* mMoney;                 // 钻石
	CCLabelTTF* mEnergy;                // 能量
	CCLabelTTF* mNextEnergyTime;        // 能量下一点回复
	CCLabelTTF* mAllEnergyTime;         // 能量完全回复
	CCLabelTTF* mExpGainRatio;          // 经验获得加成
	CCLabelTTF* mCoinGainRatio;         // 铜币获得加成
	CCLabelTTF* mFightTitle;
	CCLabelTTF* mPutonCount;            // 装备数量
	CCLabelTTF* mAttack;                // 攻击力
	CCLabelTTF* mDefense;               // 防御力
	CCLabelTTF* mLife;                  // 生命值
	CCLabelTTF* mTeShuTitle;
	CCLabelTTF* mAtkMaxReappear;        // 最大攻击打出概率
	CCLabelTTF* mDefMaxReappear;        // 最大防御打出概率
	CCLabelTTF* mEquipageDropRatio;     // 装备掉落几率
	CCLabelTTF* mEnergyRecoverRatio;    // 能量恢复加成
	
	void _onNotification(CCObject* object);
	
	void updateEnergyTime( float object );
	void updateAllEnergyTime( float object );
};

#endif