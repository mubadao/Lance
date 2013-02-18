#ifndef _StaticDungeon_H_
#define _StaticDungeon_H_

#include "Global.h"

struct xmlTaskInfo
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
typedef map<int, xmlTaskInfo> xmlTaskMap;

struct xmlFloorInfo
{
	int floorID;
	vector<int> taskList;
};
typedef map<int, xmlFloorInfo> xmlFloorMap;

struct xmlDungeonInfo
{
	int dungeonsID;
	xmlFloorMap floorList;
	
	xmlFloorInfo* getFloor(int floorID)
	{
		if (floorList.find(floorID) == floorList.end())
			assert(false);
		return &floorList[floorID];
	}
};
typedef map<int, xmlDungeonInfo> xmlDungeonMap;

class StaticDungeon : public Singleton<StaticDungeon>
{
public:
	xmlTaskMap taskMap;
	xmlDungeonMap dungeonMap;

	void parse();
	
	xmlDungeonInfo* getDungeonInfo(int dungeonID);
	xmlFloorInfo* getFloorInfo(int dungeonsID, int floorID);
	xmlTaskInfo* getTaskInfo(int dungeonsID, int floorID, int taskID);
};

#endif