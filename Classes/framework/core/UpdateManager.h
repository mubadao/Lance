#ifndef _UpdateManager_H_
#define _UpdateManager_H_

#include "CommonHeader.h"
#include "CallFunc0Selector.h"
#include "Singleton.h"

class UpdateManager : public CCNode, public Singleton<UpdateManager>
{
public:
	UpdateManager();
	~UpdateManager();

	void regist(CCObject* target, SEL_SCHEDULE selector);
	void unregist(CCObject* target, SEL_SCHEDULE selector);

private:
	vector<CallFunc0Selector> mUpdates;
	void update(float object);
};

#endif