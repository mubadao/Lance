#ifndef _EquipLevelUpDialogLoader_h__
#define _EquipLevelUpDialogLoader_h__

#include "Global.h"
#include "EquipLevelUpDialog.h"

class EquipLevelUpDialogLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipLevelUpDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipLevelUpDialog);
};

#endif //_EquipLevelUpDialogLoader_h__
