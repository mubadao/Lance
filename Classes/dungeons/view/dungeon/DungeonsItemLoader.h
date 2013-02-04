#ifndef _DungeonsItemLoaderLoader_H_
#define _DungeonsItemLoaderLoader_H_

#include "Global.h"
#include "DungeonsItem.h"

class DungeonsItemLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DungeonsItemLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(DungeonsItem);
};

#endif
