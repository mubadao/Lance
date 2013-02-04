#ifndef _ShopItemLoader_H_
#define _ShopItemLoader_H_

#include "Global.h"
#include "ShopItem.h"

class ShopItemLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ShopItemLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ShopItem);
};

#endif