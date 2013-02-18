#include "DownloadModule.h"
#include "UserProxy.h"
//#include "AlertDialog.h"

DownloadModule::DownloadModule()
: mTarget(NULL)
, mSelector(NULL)
{
}

DownloadModule::~DownloadModule()
{
}

void DownloadModule::activate()
{
}

void DownloadModule::_onNotification( CCObject* object )
{
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = notification->getName();
	CCObject* params = notification->getObject();

	if (name == FileDownload::notificationName)
	{
		CCString* filename = (CCString*)params;
		if (!_isValid(filename->getCString()))
		{
//			AlertDialog::initContent(fcs("%s is no valid file!",filename->getCString()), ALERT_STYLE_OK);
//			FRAMEWORK->popup("AlertDialog");
		}
		++mVersionIter;
		loadFile();
	}
}

void DownloadModule::download( CCObject* target, SEL_CallFunc selector )
{
	CCArray* nameList = CCArray::create(ccs(FileDownload::notificationName),NULL);
	RegisterObservers(this, nameList, callfuncO_selector(DownloadModule::_onNotification));
	
    mTarget = target;
	mSelector = selector;
    
	mVersionIter = UserProxy::shared()->mXMLVersionMap.begin();
	loadFile();
}

void DownloadModule::loadFile()
{
	if(mVersionIter == UserProxy::shared()->mXMLVersionMap.end())
	{
		RemoveObserver(this);
        if(mTarget && mSelector)
            (mTarget->*mSelector)();
	}
	else
	{
		if(!_isValid(mVersionIter->first.c_str()))
		{
			string fileName = mVersionIter->first;
			string fileUrl = UserProxy::shared()->mConfigUrl + fileName;
            fileUrl = "http://www.happybluefin.com/Test/backend/config/" + fileName;
            CCLOG("start download fileUrl:%s;fileName:%s", fileUrl.c_str(),fileName.c_str());
            FILEDOWNLOAD->downloadFile(fileUrl, fileName);
		}
        else 
        {
            ++mVersionIter;
            loadFile();
        }
	}
}

bool DownloadModule::_isValid(const char* fliename)
{
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += fliename;

    if(!isFileExistsInWritablePath(fliename))
        return false;
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
    
	xmlDocPtr doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == doc)
        return false;

	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
        return false;

	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
            xmlChar* item = xmlGetProp(curNode, BAD_CAST "name");
			if (!xmlStrcmp(item, BAD_CAST "version"))
			{
				string version = attrToChar(curNode, "version");
				XMLVersionMap& versionMap = UserProxy::shared()->mXMLVersionMap;

                xmlFreeDoc(doc);
                bool valid = (version == versionMap[fliename]);
				return valid;
			}
		}
		curNode = curNode->next;
	}
    
    xmlFreeDoc(doc);
	return false;
}
