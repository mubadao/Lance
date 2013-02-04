#ifndef _FightSucceedDialogLoader_H_
#define _FightSucceedDialogLoader_H_

#include "Global.h"
#include "FightSucceedDialog.h"

class FightSucceedDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FightSucceedDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(FightSucceedDialog);
};

#endif
