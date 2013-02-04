#ifndef _GetEquipEventDialogLoader_H_
#define _GetEquipEventDialogLoader_H_

#include "Global.h"
#include "GetEquipEventDialog.h"

class GetEquipEventDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GetEquipEventDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GetEquipEventDialog);
};

#endif
