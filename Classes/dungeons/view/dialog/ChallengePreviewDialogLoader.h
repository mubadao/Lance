#ifndef _ChallengePreviewDialogLoader_H_
#define _ChallengePreviewDialogLoader_H_

#include "Global.h"
#include "ChallengePreviewDialog.h"

class ChallengePreviewDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChallengePreviewDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChallengePreviewDialog);
};

#endif
