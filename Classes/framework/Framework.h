#ifndef _Framework_H_
#define _Framework_H_

#include "CommonHeader.h"
#include "StateManager.h"
#include "Mask.h"

struct DialogInfo
{
	string name;
	void* data;
	DialogInfo(string n) : name(n), data(NULL) {}
	DialogInfo(string n, void* d) : name(n), data(d) {}
};

class Framework : public Singleton<Framework>
{
    CC_SYNTHESIZE_READONLY(Mask*, mDialogMask, DialogMask);
    CC_SYNTHESIZE_READONLY(CCLayer*, mLayerDialog, LayerDialog);
    CC_SYNTHESIZE(StateManager*, mStateManager, StateManager);
    
public:
	CCScene* mainScene;
	CCLayer* bgLayer;
	CCLayer* globalLayer;
	CCLayer* topLayer;
	CCNode* maskLayer;

public:
	Framework();
    ~Framework();
    
	void init();

    // 切换主场景
    void changeState(const string& name);
	
	// 切换到上一场景
	void changeToLastState();

    // 弹出对话框
	void popup(const string& name, void* data = NULL);
    // 弹出下一个对话框
	void popupNext();
    
private:
    CCLayer* mLayerState;               // 场景层
	CCLayer* mCurState;                 // 当前层
    
	string mLastStateName;
	string mCurStateName;

	queue<DialogInfo> mDialogList;
};

#define FRAMEWORK Framework::shared()

#endif