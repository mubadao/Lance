#ifndef _LevelUpDialogLoaderLoader_H_
#define _LevelUpDialogLoaderLoader_H_

#include "Global.h"
#include "LevelUpDialog.h"

class LevelUpDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LevelUpDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LevelUpDialog);
};

#endif
