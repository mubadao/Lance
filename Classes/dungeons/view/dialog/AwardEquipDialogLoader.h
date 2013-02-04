#ifndef _AwardEquipDialogLoaderLoader_H_
#define _AwardEquipDialogLoaderLoader_H_

#include "Global.h"
#include "AwardEquipDialog.h"

class AwardEquipDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AwardEquipDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AwardEquipDialog);
};

#endif
