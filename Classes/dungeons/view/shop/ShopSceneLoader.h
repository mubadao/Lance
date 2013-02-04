#ifndef _ShopSceneLoader_H_
#define _ShopSceneLoader_H_

#include "Global.h"
#include "ShopScene.h"

class ShopSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ShopSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ShopScene);
};

#endif
