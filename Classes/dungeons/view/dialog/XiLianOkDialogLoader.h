#ifndef _XiLianOkDialogLoader_H_
#define _XiLianOkDialogLoader_H_

#include "Global.h"
#include "XiLianOkDialog.h"

class XiLianOkDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(XiLianOkDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(XiLianOkDialog);
};

#endif
