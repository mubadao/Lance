#ifndef _ChallengeResultDialogLoader_H_
#define _ChallengeResultDialogLoader_H_

#include "Global.h"
#include "ChallengeResultDialog.h"

class ChallengeResultDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChallengeResultDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChallengeResultDialog);
};

#endif
