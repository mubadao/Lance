#ifndef _PlatformInterface_h_
#define _PlatformInterface_h_

#include "Global.h"

class PlatformInterface
{
public:
	virtual void navigateToURL(CCNode* layer, const char* url) = 0;
};

#endif // _PlatformInterface_h_
