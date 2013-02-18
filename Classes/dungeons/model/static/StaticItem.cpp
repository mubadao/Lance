#include "StaticItem.h"

void StaticItem::parse()
{
    if(!isFileExistsInWritablePath("Equipage.xml"))
        assert(false);
		
    string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "Equipage.xml";
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	xmlDocPtr doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == doc)
		assert(false);

	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		assert(false);

	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (0 == xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			string name = attrToChar(curNode,"name");
			if (name == "properties")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Properties"))
					{
						xmlEquipInfo info;
						info.baseId = attrToInt(elem, "id");
						info.icon = attrToChar(elem, "icon");
						info.type = (EquipType)attrToInt(elem, "type");
						info.quality = attrToInt(elem, "quality");
						info.fusion = attrToInt(elem, "fusion");
						info.intensify_price = attrToInt(elem, "intensify_price");
						info.intensify_energy = attrToInt(elem, "intensify_energy");
						info.intensify_fusion = attrToInt(elem, "intensify_fusion");
						info.rule = attrToInt(elem, "rule");
						info.level = attrToInt(elem, "level");
						info.sell = attrToInt(elem, "sell");

						mEquipInfoMap[info.baseId] = info;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}

	xmlFreeDoc(doc);
}

xmlEquipInfo* StaticItem::getEquipInfo(int id)
{
	if (mEquipInfoMap.find(id) == mEquipInfoMap.end())
		assert(false);
	return &mEquipInfoMap[id];
}
