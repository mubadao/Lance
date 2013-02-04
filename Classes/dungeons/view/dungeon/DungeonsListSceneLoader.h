#ifndef _DungeonsListSceneLoader_H_
#define _DungeonsListSceneLoader_H_

#include "Global.h"
#include "DungeonsListScene.h"

class DungeonsListSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DungeonsListSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(DungeonsListScene);
};

#endif
