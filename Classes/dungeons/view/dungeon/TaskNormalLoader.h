#ifndef _TaskNormalLoader_H_
#define _TaskNormalLoader_H_

#include "Global.h"
#include "TaskNormal.h"

class TaskNormalLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskNormalLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TaskNormal);
};

#endif
