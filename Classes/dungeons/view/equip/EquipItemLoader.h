#ifndef _EquipItemLoader_H_
#define _EquipItemLoader_H_

#include "Global.h"
#include "EquipItem.h"

class EquipItemLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipItemLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipItem);
};

#endif
