#ifndef _TaskDescLoader_H_
#define _TaskDescLoader_H_

#include "Global.h"
#include "TaskDesc.h"

class TaskDescLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskDescLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TaskDesc);
};

#endif
