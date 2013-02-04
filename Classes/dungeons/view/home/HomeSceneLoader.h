#ifndef _HomeSceneLoader_H_
#define _HomeSceneLoader_H_

#include "Global.h"
#include "HomeScene.h"

class HomeSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HomeSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HomeScene);
};

#endif