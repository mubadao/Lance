#ifndef _HomeSceneContentLoader_H_
#define _HomeSceneContentLoader_H_

#include "Global.h"
#include "HomeSceneContent.h"

class HomeSceneContentLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HomeSceneContentLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HomeSceneContent);
};

#endif