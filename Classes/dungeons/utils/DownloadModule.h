#ifndef _DownloadModule_h__
#define _DownloadModule_h__

#include "Global.h"

class DownloadModule : public CCObject, public Singleton<DownloadModule>
{
public:
	DownloadModule();
	~DownloadModule();

	void download(CCObject* target, SEL_CallFunc selector);
	void loadFile();

    void activate();

private:
	bool _isValid(const char* fliename);
	void _onNotification(CCObject* object);

	XMLVersionMap::iterator mVersionIter;
    CCObject* mTarget;
    SEL_CallFunc mSelector;
};

#endif