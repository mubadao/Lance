#ifndef _PreLoaderScene_h__
#define _PreLoaderScene_h__

#include "Global.h"

class PreLoaderScene
	: public CCLayer
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PreLoaderScene, create);

	PreLoaderScene(void);
	virtual ~PreLoaderScene(void);

	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	void _onNotification(CCObject* object);
	void _delayComplete();
	void _loadComplete();

	int mFileCount;
	int mInitResult;
};

#endif