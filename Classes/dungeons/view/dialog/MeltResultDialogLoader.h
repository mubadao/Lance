#ifndef _MeltResultDialogLoader_H_
#define _MeltResultDialogLoader_H_

#include "Global.h"
#include "MeltResultDialog.h"

class MeltResultDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MeltResultDialogLoader, loader);
    
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MeltResultDialog);
};

#endif
