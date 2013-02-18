#ifndef _DungeonsProxy_H_
#define _DungeonsProxy_H_

#include "Global.h"
#include "StaticDungeon.h"

// 任务信息
struct TaskInfo
{
    int dungeon;
    int floor;
    int task;
    int progress;
	
    TaskInfo() : dungeon(1),floor(1),task(1),progress(1) {}
};

class DungeonsProxy : public Singleton<DungeonsProxy>
{
private:
	void testData();
	
public:
	DungeonsProxy();
	~DungeonsProxy();
    
    TaskInfo curTaskInfo;
    TaskInfo maxTaskInfo;
    
public:
	int getCurDungeon();
	int getCurFloor();
	int getCurTask();
	int getCurProgress();
	int getMaxDungeon();
	int getMaxFloor();
	int getMaxTask();
	int getMaxProgress();

	const char* getCurName();
	const char* getName(int dungeon, int floor);
    const char* getCurDesc();
    const char* getDesc(int index);

	void setCurFloor(int dungeons, int floor);

	xmlDungeonInfo* getCurDungeonsStatic();
	xmlFloorInfo* getCurFloorStatic();
	xmlTaskInfo* getCurTaskStatic();
};

#endif