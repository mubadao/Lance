#ifndef _PlayerDetailSceneLoader_H_
#define _PlayerDetailSceneLoader_H_

#include "Global.h"
#include "PlayerDetailScene.h"

class PlayerDetailSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PlayerDetailSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PlayerDetailScene);
};

#endif
