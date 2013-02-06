#ifndef _CommonNotify_H_
#define _CommonNotify_H_

#include "Global.h"
#include "NotifyDefine.h"

class CommonNotify : public CCObject, public Singleton<CommonNotify>
{
private:
	vector<CallFunc0Selector> mPowerSelector;
	vector<CallFunc0Selector> mEnergySelector;
	vector<CallFunc0Selector> mAllPowerSelector;
	vector<CallFunc0Selector> mAllEnergySelector;

public:
	CommonNotify();
	~CommonNotify();

	void registerNotify();

	void registerPowerTimeCall(CCObject* target, SEL_SCHEDULE selector);
	void registerAllPowerTimeCall(CCObject* target, SEL_SCHEDULE selector);
	void registerEnergyTimeCall(CCObject* target, SEL_SCHEDULE selector);
	void registerAllEnergyTimeCall(CCObject* target, SEL_SCHEDULE selector);

	void unregisterPowerTimeCall( CCObject* target, SEL_SCHEDULE selector );
	void unregisterAllPowerTimeCall( CCObject* target, SEL_SCHEDULE selector );
	void unregisterEnergyTimeCall( CCObject* target, SEL_SCHEDULE selector );
	void unregisterAllEnergyTimeCall( CCObject* target, SEL_SCHEDULE selector );

	void powerTimeUpdate(float lastTime);
	void energyTimeUpdate(float lastTime);
	void allPowerTimeUpdate(float lastTime);
	void allEnergyTimeUpdate(float lastTime);

	void update(float object);
	
private:
	void _onNotification( CCObject* object );

    void _sellItem();
    void _buyEnergy();
    void _buyLife();
    void _buyFusion();
    void _forceUpgrade();
};

#endif
