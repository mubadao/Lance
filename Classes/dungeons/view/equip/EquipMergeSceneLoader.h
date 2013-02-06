#ifndef _EquipMergeSceneLoader_H_
#define _EquipMergeSceneLoader_H_

#include "Global.h"
#include "EquipMergeScene.h"

class EquipMergeSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipMergeSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipMergeScene);
};

#endif