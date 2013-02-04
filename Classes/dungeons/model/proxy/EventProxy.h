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
	int type;	//0:��ս�¼�, 1:���Ụ����¼�, 2:������Ƭ�¼�, 3:ϵͳ�¼�
	int coin;	//ʧȥ����Ϸ��
	int itemID; //ʧȥ�ĵ���id������������Ƭid
	bool succeed;	//�Ƿ�ɹ�
	int pid;	//���pid
	std::string name;	//����ǳ�
	int id;		//�����������ս�б��е�id
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