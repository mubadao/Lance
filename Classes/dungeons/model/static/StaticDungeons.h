#ifndef _StaticDungeons_H_
#define _StaticDungeons_H_

#include "StaticData.h"
#include "Global.h"
#include "ViewVO.h"

struct TaskStatic
{
	int taskID;
	int bossID;
	int energy;
	int coinMax;
	int coinMin;
	int expMax;
	int expMin;
	int drop;
	float progress;
};

struct FloorStatic
{
	int floorID;
	const char* name;
	const char* desc;
	const char* scene;
	std::map<int, TaskStatic*> taskList;
	TaskStatic* getTask(int taskID)
	{
		assert(taskList.count(taskID) != 0);
		return taskList[taskID];
	}
};

struct DungeonsStatic : public Singleton<DungeonsStatic>
{
	int dungeonsID;
	std::map<int, FloorStatic*> floorList;
	FloorStatic* getFloor(int floorID)
	{
		assert(floorList.count(floorID) != 0);
		return floorList[floorID];
	}
};

typedef std::map<int, TaskStatic*> TaskStaticMap;
typedef std::map<int, FloorStatic*> FloorStaticMap;
typedef std::map<int, DungeonsStatic*> DungeonsStaticMap;

class StaticDungeons  : public StaticData, public Singleton<StaticDungeons>
{
public:
	TaskStaticMap taskInfoMap;
	DungeonsStaticMap dungeonsInfoMap;

	void parse();
	DungeonsStatic* getDungeonsInfo(int dungeonsID);
	FloorStatic* getFloorInfo(int dungeonsID, int floorID);
	TaskStatic* getTaskInfo(int dungeonsID, int floorID, int taskID);
	
};

#endif // StaticDungeons_h__