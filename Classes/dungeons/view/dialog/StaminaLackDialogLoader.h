#ifndef _StaminaLackDialogLoader_H_
#define _StaminaLackDialogLoader_H_

#include "Global.h"
#include "StaminaLackDialog.h"

class StaminaLackDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StaminaLackDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StaminaLackDialog);
};

#endif
