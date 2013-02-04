#ifndef _BuyMoneyItemLoader_H_
#define _BuyMoneyItemLoader_H_

#include "Global.h"
#include "BuyMoneyItem.h"

class BuyMoneyItemLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BuyMoneyItemLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BuyMoneyItem);
};

#endif
