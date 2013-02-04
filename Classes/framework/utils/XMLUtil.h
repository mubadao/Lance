#ifndef XMLUtil_h__
#define XMLUtil_h__

#include "libxml/parser.h"
#include "libxml/tree.h"

class XMLUtil
{
public:
	static int attributeToInt(xmlNodePtr node, const char* key);
	static float attributeToFloat(xmlNodePtr node, const char* key);
	static const char* attributeToChar(xmlNodePtr node, const char* key);
};

#define attriToInt(node, key) XMLUtil::attributeToInt(node, key)
#define attriToFloat(node, key) XMLUtil::attributeToFloat(node, key)
#define attriToChar(node, key) XMLUtil::attributeToChar(node, key)

#endif // XMLUtil_h__
