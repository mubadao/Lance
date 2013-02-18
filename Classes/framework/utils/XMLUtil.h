#ifndef _XMLUtil_H_
#define _XMLUtil_H_

#include "CommonHeader.h"
#include "libxml/parser.h"
#include "libxml/tree.h"

int attrToInt(xmlNodePtr node, const char* key);
float attrToFloat(xmlNodePtr node, const char* key);
string attrToChar(xmlNodePtr node, const char* key);

#endif
