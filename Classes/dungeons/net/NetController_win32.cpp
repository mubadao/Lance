//
//  NetController.m
//  Dungeons
//
//  Created by Limin on 12-7-27.
//  Copyright (c) 2012年 LIHO. All rights reserved.
//

#include "NetController.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "NCDefines.h"

NetController::NetController()
{
}

NetController::~NetController()
{
}

bool NetController::init(const char* url)
{
	return true;
}

bool NetController::_sendCommand(const string& cmd, void* params)
{
	return true;
}

void NetController::parseData(void* data)
{
}

void NetController::receiveError()
{
    
}

void NetController::_parseRegist(void* params)
{
	//CCObject* postData;
	//Post_Net_Notification(kNCRegist, postData);
}

bool NetController::regist(const std::string& name, const int avata)
{    
	return true;
}

bool NetController::dungeonExplore(int dungeon, int floor, int task)
{
	return true;
}

bool NetController::intensifyEquipage(int index, int number)
{
	return true;
}

bool NetController::loadEquipage(int index)
{
	return true;
}

bool NetController::unloadEquipage(int index)
{
	return true;
}

bool NetController::sellEquipage(std::vector<int>& indexArray)
{
	return true;
}

bool NetController::fusionEquipage(std::vector<int>& indexArray)
{
	return true;
}

bool NetController::resetEquipage(int index)
{
	return true;
}

bool NetController::findChallengePlayerByName(const std::string& name)
{
	return true;
}

bool NetController::getChallengeList()
{
	return true;
}

bool NetController::getChallengeEnemyList()
{
	return true;
}

bool NetController::challengePlayer(int gid)
{
	return true;
}

bool NetController::gameInit()
{
	return true;
}

bool NetController::getSelfInfo()
{
	return true;
}

bool NetController::getAmuletEnemyList()
{
	return true;
}

bool NetController::getFragmentEnemyList(int itemID)
{
	return true;
}

bool NetController::snatchPlayer(const int pid, int itemID)
{
	return true;
}

bool NetController::composeEquipage( int itemID )
{
	return true;
}

bool NetController::getComposeEquipageList()
{
	return true;
}

bool NetController::buyItem( int itemID, int count )
{
	return true;
}

bool NetController::useItem( int itemID )
{
	return true;
}

bool NetController::getPrize()
{
	return true;
}

bool NetController::refreshMysteryShop()
{
	return true;
}

bool NetController::getAllEvent()
{
	return true;
}

bool NetController::getFightEvent()
{
	return true;
}

bool NetController::getSystemEvent()
{
	return true;
}

bool NetController::openBox(int type, const int id)
{
	return true;
}

bool NetController::buyEnergy(int type)
{
	return true;
}

bool NetController::buyPower(int type)
{
	return true;
}

bool NetController::dungeonStart(int dungeon, int floor)
{
	return true;
}

bool NetController::buyMoney( int id )
{
	return true;
}

bool NetController::buyCoin( int id )
{
	return true;
}

void NetController::_parseLevelInfo( void* params )
{

}










#endif
