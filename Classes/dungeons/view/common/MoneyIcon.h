#ifndef _MoneyIcon_H_
#define _MoneyIcon_H_

#include "Global.h"
#include "model/static/StaticItem.h"

class MoneyIcon
	: public CCNode
	, public CCBMemberVariableAssigner
{
public:
	MoneyIcon();
	~MoneyIcon();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MoneyIcon, create);
	
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);

	void setType(MoneyType type);
	void setCount(int value);
	
private:
	CCSprite* mIcon;
	CCLabelTTF* mCount;
};

#endif // _MoneyIcon_h_
