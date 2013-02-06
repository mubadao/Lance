#ifndef _ChallengeSceneLoader_H_
#define _ChallengeSceneLoader_H_

#include "Global.h"
#include "ChallengeScene.h"

class ChallengeSceneLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChallengeSceneLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChallengeScene);
};

#endif