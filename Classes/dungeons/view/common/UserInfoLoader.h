#ifndef _UserInfoLoader_H_
#define _UserInfoLoader_H_

#include "Global.h"
#include "UserInfo.h"

class UserInfoLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(UserInfoLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(UserInfo);
};

#endif
