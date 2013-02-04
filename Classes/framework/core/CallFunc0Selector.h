#ifndef _ScheduleSelector_h_
#define _ScheduleSelector_h_

#include "CommonHeader.h"

class CallFunc0Selector
{
private:
	CallFunc0Selector() {}
	
public:
	CCObject* mTarget;
	SEL_SCHEDULE mSelector;

	CallFunc0Selector(CCObject* target, SEL_SCHEDULE selector)
	: mTarget(target)
	, mSelector(selector)
	{
	}

	void activate(float object)
	{
		if(mTarget && mSelector)
			(mTarget->*mSelector)(object);
	}
};

#endif