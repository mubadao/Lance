#ifndef _LostLifeEventDialogLoader_H_
#define _LostLifeEventDialogLoader_H_

#include "Global.h"
#include "LostLifeEventDialog.h"

class LostLifeEventDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LostLifeEventDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LostLifeEventDialog);
};

#endif
