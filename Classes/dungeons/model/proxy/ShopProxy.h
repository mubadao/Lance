#ifndef _ShopProxy_H_
#define _ShopProxy_H_

#include "Global.h"
#include "EquipProxy.h"

struct OpenBoxResult : public CCObject
{
	int result;
	EquipInfo* equipInfo;
};

class ShopProxy : public Singleton<ShopProxy>
{
public:
	ShopProxy();
	~ShopProxy();

    int mRemainderOpenBoxTime;
};

#endif
