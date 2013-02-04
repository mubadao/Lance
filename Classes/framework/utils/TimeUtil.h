#ifndef _TimeUtil_H_
#define _TimeUtil_H_

struct HHMMSS
{
	int hour;
	int minute;
	int second;

	HHMMSS():hour(0),minute(0),second(0){}
    HHMMSS(long mill)
    {
        hour = mill / (1000 * 60 * 60);
        minute = mill / (1000 * 60) % 60;
        second = mill / 1000 % 60;
    }
};

struct MMSS
{
	int minute;
	int second;
    
	MMSS():minute(0),second(0){}
    MMSS(long mill)
    {
        minute = mill / 1000 / 60;
        second = mill / 1000 % 60;
    }
};

#endif