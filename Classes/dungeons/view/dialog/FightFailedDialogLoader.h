#ifndef _FightFailedDialogLoader_H_
#define _FightFailedDialogLoader_H_

#include "Global.h"
#include "FightFailedDialog.h"

class FightFailedDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FightFailedDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(FightFailedDialog);
};

#endif
