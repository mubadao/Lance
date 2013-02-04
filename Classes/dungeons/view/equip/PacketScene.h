#ifndef _PacketScene_H_
#define _PacketScene_H_

#include "Global.h"
#include "EquipItem.h"

enum PackTab
{
	PACK_TAB_EQUIP = 0,
	PACK_TAB_PACKET,
	PACK_TAB_SELL
};

enum EquipFilterType
{
	EQUIP_FILTER_BY_HELM=0,
	EQUIP_FILTER_BY_NECKLACE,
	EQUIP_FILTER_BY_WEAPON,
	EQUIP_FILTER_BY_CLOTH,
	EQUIP_FILTER_BY_RING,
	EQUIP_FILTER_BY_SHOES,
	EQUIP_FILTER_BY_ALL,
	EQUIP_FILTER_BY_PUTON,
	EQUIP_FILTER_BY_TAKEOFF
};

class PacketScene
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PacketScene, create);

	PacketScene();
	virtual ~PacketScene();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	static PackTab msCurTab;
	static EquipFilterType msSortKind;

private:
	CCScrollView* mScrollView;
	CCLabelTTF* mBagCount;

	CCPoint mLastScrollPos;
	
	void _refresh();
	void _onNotification(CCObject* object);
	EquipList _getEquipList(EquipFilterType type);

	void onEquipTypeSortSelect(CCObject* object);
};

#endif