#ifndef _PacketSceneLoader_H_
#define _PacketSceneLoader_H_

#include "Global.h"
#include "PacketScene.h"

class PacketSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PacketSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PacketScene);
};

#endif
