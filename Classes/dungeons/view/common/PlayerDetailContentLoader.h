#ifndef _PlayerDetailContentLoader_H_
#define _PlayerDetailContentLoader_H_

#include "Global.h"
#include "PlayerDetailContent.h"

class PlayerDetailContentLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PlayerDetailContentLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PlayerDetailContent);
};

#endif
