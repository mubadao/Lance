#ifndef _MainMenu_H_
#define _MainMenu_H_

#include "Global.h"

enum MainMenuTab
{
	MAIN_MENU_TAB_NONE=0,
	MAIN_MENU_TAB_HOME,
	MAIN_MENU_TAB_EQUIP,
	MAIN_MENU_TAB_DUNGEON,
	MAIN_MENU_TAB_SHOP,
	MAIN_MENU_TAB_MENU,
};

class MainMenu
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainMenu, create);

	MainMenu();
	~MainMenu();
	
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCControlButton* mBtnHome;
	CCControlButton* mBtnEquip;
	CCControlButton* mBtnDungeon;
	CCControlButton* mBtnShop;
	CCControlButton* mBtnMore;
	
	void onBtnHome(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onBtnEquip(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onBtnDungeon(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onBtnShop(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onBtnMore(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif