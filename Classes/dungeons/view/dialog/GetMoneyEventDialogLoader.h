#ifndef _GetMoneyEventDialogLoader_H_
#define _GetMoneyEventDialogLoader_H_

#include "Global.h"
#include "GetMoneyEventDialog.h"

class GetMoneyEventDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GetMoneyEventDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GetMoneyEventDialog);
};

#endif
