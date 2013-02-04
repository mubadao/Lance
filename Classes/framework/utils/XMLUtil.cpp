#include "XMLUtil.h"
#include "StringUtil.h"

int XMLUtil::attributeToInt( xmlNodePtr node, const char* key )
{
	return charToInt((const char*)xmlGetProp(node,(const xmlChar*)key));
}

float XMLUtil::attributeToFloat( xmlNodePtr node, const char* key )
{
	return charToFloat((const char*)xmlGetProp(node,(const xmlChar*)key));
}

const char* XMLUtil::attributeToChar( xmlNodePtr node, const char* key )
{
	return (const char*)xmlGetProp(node,(const xmlChar*)key);
}
