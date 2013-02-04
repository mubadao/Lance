#ifndef _StateManager_H_
#define _StateManager_H_

#include "CommonHeader.h"
#include "Dialog.h"

class StateManager
{
public:
    StateManager() {}
    virtual ~StateManager() {}
    
	virtual CCLayer* getState(const string& name) = 0;
	virtual Dialog* getDialog(const string& name) = 0;
};

#endif