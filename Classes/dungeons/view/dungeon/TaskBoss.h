#ifndef _TaskBoss_H_
#define _TaskBoss_H_

#include "Global.h"
#include "EquipIcon.h"
#include "TaskDesc.h"

class TaskBoss
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskBoss, create);

	TaskBoss();
	virtual ~TaskBoss();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void refresh();
	void reset();
    void refreshLife();

	CC_SYNTHESIZE(TaskDesc*, mTaskDesc, TaskDesc)

private:
	CCLabelTTF* mBossName;
	CCLabelTTF* mBossAttack;
	CCLabelTTF* mBossDefense;
	CCLabelTTF* mBossLife;
	
	CCLabelTTF* mEnergy;
	CCLabelTTF* mExp;
	CCLabelTTF* mCoin;

	CCLabelTTF* mItemName;
	CCLabelTTF* mItemLevel;

    CCLabelTTF* mLifeTitle;
	EquipIcon* mEquipIcon;

	CCControlButton* mDoItBtn;
	ProgressText* mLifeProgress;

	int mCurStep;

	void onDoItBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif