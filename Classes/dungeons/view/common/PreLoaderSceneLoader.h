#ifndef _PreLoaderSceneLoader_h__
#define _PreLoaderSceneLoader_h__

#include "Global.h"
#include "PreLoaderScene.h"

class PreLoaderSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PreLoaderSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PreLoaderScene);
};

#endif //_PreLoaderScene_h__
