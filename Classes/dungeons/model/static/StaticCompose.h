#ifndef _StaticCompose_h__
#define _StaticCompose_h__
#include "Global.h"

struct ComposeItemStatic
{
	int mItemID;
	int mItemCount;
};

typedef std::vector<ComposeItemStatic*> ComposeItemList;
struct ComposeInfoStatic
{
	int mItemID;
	ComposeItemList mComposeItemList;
};
typedef std::map<int, ComposeInfoStatic*> ComposeInfoStaticMap;
class StaticCompose : public Singleton<StaticCompose>
{
private:
	ComposeInfoStaticMap mComposeInfoMap;
protected:
public:
	StaticCompose();
	~StaticCompose();

	ComposeInfoStatic* getComposeInfo(int itemID);
	ComposeInfoStaticMap& getComposeMap();
	void parse();
};
#endif // _StaticCompose_h__