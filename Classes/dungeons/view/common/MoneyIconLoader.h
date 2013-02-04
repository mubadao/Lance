#ifndef _MoneyIconLoader_H_
#define _MoneyIconLoader_H_

#include "Global.h"
#include "MoneyIcon.h"

class MoneyIconLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MoneyIconLoader, loader);
	
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MoneyIcon);
};

#endif
