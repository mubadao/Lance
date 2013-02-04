#ifndef _AlertTitleDialogLoader_H_
#define _AlertTitleDialogLoader_H_

#include "Global.h"
#include "AlertTitleDialog.h"

class AlertTitleDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AlertTitleDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AlertTitleDialog);
};

#endif
