#include "EventProxy.h"

EventProxy::EventProxy()
{
	testData();
}

EventProxy::~EventProxy()
{
	EventList::iterator iter = mEventList.begin();
	while(iter != mEventList.end())
	{
		delete *iter;
		iter++;
	}
	mEventList.clear();
}

void EventProxy::testData()
{
	int type[4] = {EVENT_TYPE_CHALLENGE,EVENT_TYPE_AMULET,EVENT_TYPE_FRAGMENT,EVENT_TYPE_SYSTEM};
	for(int i = 0; i < 10; i++)
	{
		EventInfo* eventInfo = new EventInfo();
		eventInfo->type = type[i % 4];
		eventInfo->coin = 30;
		eventInfo->id = i;
		eventInfo->itemID = 26002;
		eventInfo->name = "gege";
		eventInfo->pid = 10;
		eventInfo->succeed = i % 5 == 0;
		mEventList.push_back(eventInfo);
	}
}

void EventProxy::getAllEvent( EventList& eventList )
{
	eventList.clear();
	EventList::iterator iter = mEventList.begin();
	while(iter != mEventList.end())
	{
		eventList.push_back(*iter);
		iter++;
	}
}

void EventProxy::getFightEvent( EventList& eventList )
{
	eventList.clear();
	EventList::iterator iter = mEventList.begin();
	while(iter != mEventList.end())
	{
		if((*iter)->type == 0 || (*iter)->type == 1 || (*iter)->type == 2)
			eventList.push_back(*iter);
		iter++;
	}
}

void EventProxy::getFriendEvent( EventList& eventList )
{

}

void EventProxy::getSystemEvent( EventList& eventList )
{
	eventList.clear();
	EventList::iterator iter = mEventList.begin();
	while(iter != mEventList.end())
	{
		if((*iter)->type == 3)
			eventList.push_back(*iter);
		iter++;
	}
}

