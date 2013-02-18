#include "SceneManager.h"

// Common
#include "EquipIconLoader.h"
#include "EquipDetailContentLoader.h"
#include "EquipDetailLoader.h"
#include "MainMenuLoader.h"
#include "MainToolsLoader.h"
#include "MoneyIconLoader.h"
#include "PlayerDetailContentLoader.h"
#include "TaskDescLoader.h"
#include "TaskNormalLoader.h"
#include "TaskBossLoader.h"
#include "UserInfoLoader.h"

// Scene
#include "DungeonsSceneLoader.h"
#include "DungeonsListSceneLoader.h"
#include "HomeSceneContentLoader.h"
#include "HomeSceneLoader.h"
#include "PreLoaderSceneLoader.h"
#include "PacketSceneLoader.h"
#include "PlayerDetailSceneLoader.h"
#include "ShopSceneLoader.h"
#include "ChallengeSceneLoader.h"

// Dialog
#include "MainTools.h"
#include "EquipDetailDialogLoader.h"
#include "LevelUpDialogLoader.h"
#include "AwardEquipDialogLoader.h"
#include "AlertDialogLoader.h"
#include "BuyMoneyDialogLoader.h"
#include "FightSucceedDialogLoader.h"
#include "FightFailedDialogLoader.h"
#include "LostLifeEventDialogLoader.h"
#include "GetEnergyEventDialogLoader.h"
#include "GetEnergyEventDialogLoader.h"
#include "GetEnergyEventDialogLoader.h"
#include "GetEquipEventDialogLoader.h"
#include "GetMoneyEventDialogLoader.h"
#include "AlertTitleDialogLoader.h"
#include "MeltOkDialogLoader.h"
#include "MeltResultDialogLoader.h"
#include "ChallengePreviewDialogLoader.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

CCLayer* SceneManager::getState(const string& name)
{
	CCNodeLoaderLibrary* pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

	if (name == "PreLoaderScene")
	{
		pLoaderLibrary->registerCCNodeLoader("PreLoaderScene", PreLoaderSceneLoader::loader());
	}
	else if (name == "HomeScene")
	{
		pLoaderLibrary->registerCCNodeLoader("UserInfo", UserInfoLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MainMenu", MainMenuLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MainTools", MainToolsLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("HomeSceneContent", HomeSceneContentLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("HomeScene", HomeSceneLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetail", EquipDetailLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetailContent", EquipDetailContentLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MoneyIcon", MoneyIconLoader::loader());
	}
	else if(name == "DungeonsScene")
	{
		pLoaderLibrary->registerCCNodeLoader("UserInfo", UserInfoLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MainMenu", MainMenuLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("TaskDesc", TaskDescLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("TaskNormal", TaskNormalLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("TaskBoss", TaskBossLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("DungeonsScene", DungeonsSceneLoader::loader());
	}
	else if(name == "DungeonsListScene")
	{
		pLoaderLibrary->registerCCNodeLoader("UserInfo", UserInfoLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MainMenu", MainMenuLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("DungeonsListScene", DungeonsListSceneLoader::loader());
	}
	else if(name == "PacketScene")
	{
		pLoaderLibrary->registerCCNodeLoader("UserInfo", UserInfoLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MainMenu", MainMenuLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("PacketScene", PacketSceneLoader::loader());
	}
	else if(name == "PlayerDetailScene")
	{
		pLoaderLibrary->registerCCNodeLoader("UserInfo", UserInfoLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MainMenu", MainMenuLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("PlayerDetailContent", PlayerDetailContentLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("PlayerDetailScene", PlayerDetailSceneLoader::loader());
	}
	else if(name == "ShopScene")
	{
		pLoaderLibrary->registerCCNodeLoader("UserInfo", UserInfoLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MainMenu", MainMenuLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("ShopScene", ShopSceneLoader::loader());
	}
	else if(name == "ChallengeScene")
	{
		pLoaderLibrary->registerCCNodeLoader("UserInfo", UserInfoLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MainMenu", MainMenuLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("ChallengeScene", ChallengeSceneLoader::loader());
	}
	
	CCBReader* ccbReader = new CCBReader(pLoaderLibrary);
	string n = name;
	n.append(".ccbi");
	CCLayer* state = (CCLayer*)ccbReader->readNodeGraphFromFile(n.c_str(), NULL);

	ccbReader->release();
	
	return state;
}

Dialog* SceneManager::getDialog(const string& name)
{
	CCNodeLoaderLibrary* pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	
	if (name == "EquipDetailDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetailContent", EquipDetailContentLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetail", EquipDetailLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MoneyIcon", MoneyIconLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetailDialog", EquipDetailDialogLoader::loader());
	}
	else if (name == "LevelUpDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("LevelUpDialog", LevelUpDialogLoader::loader());
	}
	else if (name == "AwardEquipDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetailContent", EquipDetailContentLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetail", EquipDetailLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("AwardEquipDialog", AwardEquipDialogLoader::loader());
	}
	else if (name == "AlertDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("AlertDialog", AlertDialogLoader::loader());
	}
	else if (name == "AlertTitleDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("AlertTitleDialog", AlertTitleDialogLoader::loader());
	}
	else if (name == "BuyMoneyDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("BuyMoneyDialog", BuyMoneyDialogLoader::loader());
	}
	else if (name == "FightSucceedDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetailContent", EquipDetailContentLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetail", EquipDetailLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("FightSucceedDialog", FightSucceedDialogLoader::loader());
	}
	else if (name == "FightFailedDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("FightFailedDialog", FightFailedDialogLoader::loader());
	}
	else if (name == "LostLifeEventDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("LostLifeEventDialog", LostLifeEventDialogLoader::loader());
	}
	else if (name == "GetEnergyEventDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("GetEnergyEventDialog", GetEnergyEventDialogLoader::loader());
	}
	else if (name == "GetEquipEventDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetailContent", EquipDetailContentLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("EquipDetail", EquipDetailLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("MoneyIcon", MoneyIconLoader::loader());
		pLoaderLibrary->registerCCNodeLoader("GetEquipEventDialog", GetEquipEventDialogLoader::loader());
	}
	else if (name == "GetMoneyEventDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("GetMoneyEventDialog", GetMoneyEventDialogLoader::loader());
	}
    else if (name == "MeltOkDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("MeltOkDialog", MeltOkDialogLoader::loader());
	}
    else if (name == "MeltResultDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("MeltResultDialog", MeltResultDialogLoader::loader());
	}
	else if (name == "MainTools")
	{
		pLoaderLibrary->registerCCNodeLoader("MainTools", MainToolsLoader::loader());
	}
	else if (name == "ChallengePreviewDialog")
	{
		pLoaderLibrary->registerCCNodeLoader("ChallengePreviewDialog", ChallengePreviewDialogLoader::loader());
	}
	
	CCBReader* ccbReader = new CCBReader(pLoaderLibrary);
	string n = name;
	n.append(".ccbi");
	Dialog* dlg = (Dialog*)ccbReader->readNodeGraphFromFile(n.c_str(), NULL);
	
	ccbReader->release();
	
	return dlg;
}