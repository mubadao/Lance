#ifndef _EquipDetailContentLoader_H_
#define _EquipDetailContentLoader_H_

#include "Global.h"
#include "EquipDetailContent.h"

class EquipDetailContentLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipDetailContentLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipDetailContent);
};

#endif