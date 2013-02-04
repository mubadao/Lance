#ifndef _DungeonsItemVO_h_
#define _DungeonsItemVO_h_

typedef struct
{
	int layerID;
	int iconID;
	int exploreCount;
	int maxCount;
	bool openBoss;
	const char* name;
} DungeonsItemVO;

#endif
