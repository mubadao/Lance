#ifndef _EventProxy_h__
#define _EventProxy_h__
#include "Global.h"

enum EventType
{
	EVENT_TYPE_CHALLENGE=0,
	EVENT_TYPE_AMULET,
	EVENT_TYPE_FRAGMENT,
	EVENT_TYPE_SYSTEM
};
struct EventInfo
{
	int type;	//0:挑战事件, 1:抢夺护身符事件, 2:抢夺碎片事件, 3:系统事件
	int coin;	//失去的游戏币
	int itemID; //失去的道具id，护符或者碎片id
	bool succeed;	//是否成功
	int pid;	//玩家pid
	std::string name;	//玩家昵称
	int id;		//在抢夺或者挑战列表中的id
};

typedef std::vector<EventInfo*> EventList;
class EventProxy : public Singleton<EventProxy>
{
private:
	void testData();
	EventList mEventList;
protected:
public:
	EventProxy();
	~EventProxy();

	void getAllEvent(EventList& eventList);
	void getFightEvent(EventList& eventList);
	void getFriendEvent(EventList& eventList);
	void getSystemEvent(EventList& eventList);
};
#endif // _EventProxy_h__