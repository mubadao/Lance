#ifndef DungeonsProxy_h__
#define DungeonsProxy_h__

#include "Global.h"
#include "ViewVO.h"
#include "NCDefines.h"
#include "StaticDungeons.h"

/**
 * @brief 任务属性信息定义。
 */
struct TaskInfo
{
    int dungeonID;
    int floor;
    int task;
    int progress;
    TaskInfo():dungeonID(1),floor(1),task(1),progress(1){}
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
	int getCurDungeonsID();
	int getCurFloorID();
	int getCurTaskID();
	int getCurProgress();
	int getMaxDungeonsID();
	int getMaxFloorID();
	int getMaxTaskID();
	int getMaxProgress();

    const char* getCurDesc();
    const char* getDesc(int index);

	void setCurFloor(int dungeonsID, int floorID);

	DungeonsStatic* getCurDungeonsStatic();
	FloorStatic* getCurFloorStatic();
	TaskStatic* getCurTaskStatic();
    
    BattleResult battleResult;
};
#define DUNPROXY DungeonsProxy::shared()

#endif // DungeonsProxy_h__