#include "DungeonsProxy.h"
#include "CCFileUtils.h"
#include "Global.h"

DungeonsProxy::DungeonsProxy()
{
//	testData();
}

DungeonsProxy::~DungeonsProxy()
{
}

void DungeonsProxy::testData()
{
	curTaskInfo.dungeon = 1;
	curTaskInfo.floor = 1;
	curTaskInfo.task = 1;
	curTaskInfo.progress = 0;
}

xmlDungeonInfo* DungeonsProxy::getCurDungeonsStatic()
{
	return StaticDungeon::shared()->getDungeonInfo(curTaskInfo.dungeon);
}

xmlFloorInfo* DungeonsProxy::getCurFloorStatic()
{
	return StaticDungeon::shared()->getFloorInfo(curTaskInfo.dungeon, curTaskInfo.floor);
}

xmlTaskInfo* DungeonsProxy::getCurTaskStatic()
{
	return StaticDungeon::shared()->getTaskInfo(
		curTaskInfo.dungeon,
		curTaskInfo.floor,
		curTaskInfo.task);
}

int DungeonsProxy::getCurDungeon()
{
	return curTaskInfo.dungeon;
}

int DungeonsProxy::getCurFloor()
{
	return curTaskInfo.floor;
}

int DungeonsProxy::getCurTask()
{
	return curTaskInfo.task;
}

int DungeonsProxy::getMaxProgress()
{
	return maxTaskInfo.progress;
}

int DungeonsProxy::getMaxDungeon()
{
	return maxTaskInfo.dungeon;
}

int DungeonsProxy::getMaxFloor()
{
	return maxTaskInfo.floor;
}

int DungeonsProxy::getMaxTask()
{
	return maxTaskInfo.task;
}

int DungeonsProxy::getCurProgress()
{
	return curTaskInfo.progress;
}

const char* DungeonsProxy::getCurName()
{
	return gls(fcs("dn_%02d_%02d", curTaskInfo.dungeon, curTaskInfo.floor));
}

const char* DungeonsProxy::getName(int dungeon, int floor)
{
	return gls(fcs("dn_%02d_%02d", dungeon, floor));
}

const char* DungeonsProxy::getCurDesc()
{
    return gls(fcs("dd_01_%02d_%d_%d", curTaskInfo.floor, ((curTaskInfo.task - 1) % 6) + 1, MAX(0, curTaskInfo.progress - 1) / 20 + 1));
}

const char* DungeonsProxy::getDesc(int index)
{
    return gls(fcs("dd_01_%02d_%d_%d", curTaskInfo.floor, ((curTaskInfo.task - 1) % 6) + 1, index));
}

void DungeonsProxy::setCurFloor(int dungeon, int floor)
{
	curTaskInfo.dungeon = dungeon;
	curTaskInfo.floor = floor;
	curTaskInfo.task = (floor - 1) * 6 + 1;
}
