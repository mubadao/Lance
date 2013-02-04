#ifndef _TaskBossLoader_H_
#define _TaskBossLoader_H_

#include "Global.h"
#include "TaskBoss.h"

class TaskBossLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskBossLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TaskBoss);
};

#endif
