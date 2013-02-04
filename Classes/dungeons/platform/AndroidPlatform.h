#ifndef _AndroidPlatform_h_
#define _AndroidPlatform_h_

#include "Global.h"
#include "PlatformInterface.h"

class AndroidPlatform : public PlatformInterface
{
public:
	virtual void navigateToURL(CCNode* layer, const char* url);
};

#endif // _AndroidPlatform_h_
