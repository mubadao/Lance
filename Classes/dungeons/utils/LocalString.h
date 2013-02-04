#ifndef _LocalString_h_
#define _LocalString_h_

#include "Global.h"

class LocalString : public Singleton<LocalString>
{
private:
	xmlDocPtr xmlDoc;
	xmlNodePtr rootNode;
	xmlNodePtr childNode;
public:
	LocalString();
	~LocalString();
	void parse();
	const char* getLocalizationString(const char* id);
};

#define gls(id) LocalString::shared()->getLocalizationString(id)
#define fls(id,...) fcs(gls(id), ## __VA_ARGS__)
	
#endif // LocalString_h__
