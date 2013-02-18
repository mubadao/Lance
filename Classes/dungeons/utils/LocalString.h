#ifndef _LocalString_H_
#define _LocalString_H_

#include "Global.h"

class LocalString : public Singleton<LocalString>
{
	map<string, string> mStringMap;
	
public:	
	void parse();
	const char* getLocalizationString(const char* id);
};

#define gls(id) LocalString::shared()->getLocalizationString(id)
#define fls(id,...) fcs(gls(id), ## __VA_ARGS__)
	
#endif
