#ifndef _ChallengeItem_H_
#define _ChallengeItem_H_

#include "Global.h"
#include "ChallengeProxy.h"

class ChallengeItem
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChallengeItem, create);

	static ChallengeItem* create(CCObject* pOwer);

	ChallengeItem();
	~ChallengeItem();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

	void refresh();

protected:
	CCLabelTTF* mName;
	CCLabelTTF* mLevel;
	CCLabelTTF* mAttack;
	CCLabelTTF* mDefense;
	CCControlButton* mChallengeBtn;
	
	void onChallengeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif