#ifndef _EquipDetailDialogLoader_H_
#define _EquipDetailDialogLoader_H_

#include "Global.h"
#include "EquipDetailDialog.h"

class EquipDetailDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipDetailDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipDetailDialog);
};

#endif
