#ifndef _DungeonsSceneLoader_H_
#define _DungeonsSceneLoader_H_

#include "Global.h"
#include "DungeonsScene.h"

class DungeonsSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DungeonsSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(DungeonsScene);
};

#endif
