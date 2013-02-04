#ifndef _ShopProxy_h__
#define _ShopProxy_h__
#include "Global.h"
#include "ItemProxy.h"

struct SellResult
{
    int result;
	int mCoin;
	int mMoney;
	EquipInfo* mEquipInfo;
	void clear()
	{
		mCoin = 0;
		mMoney = 0;
		mEquipInfo = NULL;
	}
};

class ShopProxy : public Singleton<ShopProxy>
{
private:
	void testData();
protected:
public:
	ShopProxy();
	~ShopProxy();
	bool mHasLottery;
    int mRemainderOpenBoxTime;
	int mRefreshMysteryShopCost;
	SellResult mSellResult;
	EquipInfo* mBuyEquipInfo;
};
#endif // _ShopProxy_h__