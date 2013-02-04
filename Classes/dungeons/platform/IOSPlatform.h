#ifndef _IosPlatform_h_
#define _IosPlatform_h_

#include "Global.h"
#include "PlatformInterface.h"

class IosPlatform : public PlatformInterface
{
public:
	virtual void navigateToURL(CCNode* layer, const char* url);
};

#endif // _IosPlatform_h_
