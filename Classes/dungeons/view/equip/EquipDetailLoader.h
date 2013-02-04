#ifndef _EquipDetailLoader_H_
#define _EquipDetailLoader_H_

#include "Global.h"
#include "EquipDetail.h"

class EquipDetailLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipDetailLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipDetail);
};

#endif