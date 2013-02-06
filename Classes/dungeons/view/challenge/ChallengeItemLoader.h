#ifndef _ChallengeItemLoader_H_
#define _ChallengeItemLoader_H_

#include "ChallengeItem.h"

class ChallengeItemLoader : public CCNodeLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChallengeItemLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChallengeItem);
};

#endif
