#include "DungeonsProxy.h"
#include "CCFileUtils.h"
#include "Global.h"

DungeonsProxy::DungeonsProxy()
{
//	testData();
    curTaskInfo.dungeonID = 1;
    curTaskInfo.floor = 1;
    curTaskInfo.task = 1;
    curTaskInfo.progress = 0;
    maxTaskInfo.dungeonID = 1;
    maxTaskInfo.floor = 1;
    maxTaskInfo.task = 1;
    maxTaskInfo.progress = 0;
}

DungeonsProxy::~DungeonsProxy()
{
	
}

void DungeonsProxy::testData()
{
	curTaskInfo.dungeonID = 1;
	curTaskInfo.floor = 1;
	curTaskInfo.task = 1;
	curTaskInfo.progress = 0;
}

DungeonsStatic* DungeonsProxy::getCurDungeonsStatic()
{
	return StaticDungeons::shared()->getDungeonsInfo(getCurDungeonsID());
}

FloorStatic* DungeonsProxy::getCurFloorStatic()
{
	return StaticDungeons::shared()->getFloorInfo(
		getCurDungeonsID(),
		getCurFloorID());
}

TaskStatic* DungeonsProxy::getCurTaskStatic()
{
	return StaticDungeons::shared()->getTaskInfo(
		getCurDungeonsID(),
		getCurFloorID(),
		getCurTaskID());
}

int DungeonsProxy::getCurDungeonsID()
{
	return curTaskInfo.dungeonID;
}

int DungeonsProxy::getCurFloorID()
{
	return curTaskInfo.floor;
}

int DungeonsProxy::getCurTaskID()
{
	return curTaskInfo.task;
}

int DungeonsProxy::getMaxProgress()
{
	return maxTaskInfo.progress;
}

int DungeonsProxy::getMaxDungeonsID()
{
	return maxTaskInfo.dungeonID;
}

int DungeonsProxy::getMaxFloorID()
{
	return maxTaskInfo.floor;
}

int DungeonsProxy::getMaxTaskID()
{
	return maxTaskInfo.task;
}

int DungeonsProxy::getCurProgress()
{
	return curTaskInfo.progress;
}

const char* DungeonsProxy::getCurDesc()
{
    // dungeon, floor, progress
    return gls(fcs("dd_01_%02d_%d_%d", curTaskInfo.floor, ((curTaskInfo.task - 1) % 6) + 1, MAX(0,curTaskInfo.progress-1) / 20 + 1));
}

const char* DungeonsProxy::getDesc(int index)
{
    // dungeon, floor, progress
    return gls(fcs("dd_01_%02d_%d_%d", curTaskInfo.floor, ((curTaskInfo.task - 1) % 6) + 1, index));
}

void DungeonsProxy::setCurFloor(int dungeonsID, int floorID)
{
	curTaskInfo.dungeonID = dungeonsID;
	curTaskInfo.floor = floorID;
	curTaskInfo.task = (floorID-1) * 6 + 1;
}
