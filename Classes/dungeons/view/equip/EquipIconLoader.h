#ifndef _EquipIconLoader_H_
#define _EquipIconLoader_H_

#include "Global.h"
#include "EquipIcon.h"

class EquipIconLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipIconLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipIcon);
};

#endif
