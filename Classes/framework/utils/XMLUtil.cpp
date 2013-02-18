#include "XMLUtil.h"
#include "StringUtil.h"

int attrToInt(xmlNodePtr node, const char* key)
{
	xmlChar* prop = xmlGetProp(node,(const xmlChar*)key);
	if (!prop)
		assert(false);
	int rtn = StringUtil::parseCharToInt((const char*)prop);
	xmlFree(prop);
	return rtn;
}

float attrToFloat(xmlNodePtr node, const char* key)
{
	xmlChar* prop = xmlGetProp(node,(const xmlChar*)key);
	if (!prop)
		assert(false);
	float rtn = StringUtil::parseCharToFloat((const char*)prop);
	xmlFree(prop);
	return rtn;
}

string attrToChar(xmlNodePtr node, const char* key)
{
	xmlChar* prop = xmlGetProp(node,(const xmlChar*)key);
	if (!prop)
		assert(false);
	string rtn = (const char*)prop;
	xmlFree(prop);
	return rtn;
}
