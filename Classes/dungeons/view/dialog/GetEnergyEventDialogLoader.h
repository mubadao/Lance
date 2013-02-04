#ifndef _GetEnergyEventDialogLoader_H_
#define _GetEnergyEventDialogLoader_H_

#include "Global.h"
#include "GetEnergyEventDialog.h"

class GetEnergyEventDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GetEnergyEventDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GetEnergyEventDialog);
};

#endif
