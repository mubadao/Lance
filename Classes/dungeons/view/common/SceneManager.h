#ifndef _SceneManager_H_
#define _SceneManager_H_

#include "Global.h"

class SceneManager : public StateManager
{
public:
	SceneManager();
	virtual ~SceneManager();
	
	CCLayer* getState(const string& name);
	Dialog* getDialog(const string& name);
};

#endif
