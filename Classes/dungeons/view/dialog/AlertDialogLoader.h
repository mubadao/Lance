#ifndef _AlertDialogLoader_H_
#define _AlertDialogLoader_H_

#include "Global.h"
#include "AlertDialog.h"

class AlertDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AlertDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AlertDialog);
};

#endif
