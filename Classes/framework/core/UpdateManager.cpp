#include "UpdateManager.h"
#include "Framework.h"

UpdateManager::UpdateManager()
{
	FRAMEWORK->topLayer->addChild(this);
	schedule(schedule_selector(UpdateManager::update));
}

UpdateManager::~UpdateManager()
{
}

void UpdateManager::regist(CCObject* target, SEL_SCHEDULE selector)
{
	if(target && selector)
		mUpdates.push_back(CallFunc0Selector(target, selector));
}

void UpdateManager::unregist(CCObject* target, SEL_SCHEDULE selector)
{
	vector<CallFunc0Selector>::iterator iter = mUpdates.begin();
	while(iter != mUpdates.end())
	{
		if(target == iter->mTarget && selector == iter->mSelector)
			iter = mUpdates.erase(iter);
		else
			++iter;
	}
}

void UpdateManager::update(float object)
{
	for (int i  = 0; i < mUpdates.size(); i++)
	{
		mUpdates[i].activate(object * 1000);
	}
}

