#ifndef _Waitting_H_
#define _Waitting_H_

#include "Global.h"

class Waitting : public CCNode, public Singleton<Waitting>
{
public:
	Waitting();
	~Waitting();
	
	bool init();
	void show();
	void hide();
	void onHide();
	
private:
	bool isShow;
	Mask* mMask;
	
	CCSprite* mLoading1;
	CCSprite* mLoading2;
};

#endif
