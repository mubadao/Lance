#ifndef _MeltOkDialogLoader_H_
#define _MeltOkDialogLoader_H_

#include "Global.h"
#include "MeltOkDialog.h"

class MeltOkDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MeltOkDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MeltOkDialog);
};

#endif
