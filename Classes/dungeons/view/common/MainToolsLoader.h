#ifndef _MainToolsLoader_H_
#define _MainToolsLoader_H_

#include "Global.h"
#include "MainTools.h"

class MainToolsLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainToolsLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainTools);
};

#endif
