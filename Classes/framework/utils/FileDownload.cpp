//
//  FileDownload.cpp
//  lance
//
//  Created by elex on 12-11-18.
//  Copyright (c) 2012年 Elex. All rights reserved.
//

#include "FileDownload.h"
#include "NotificationCenter.h"

const char* FileDownload::notificationName = "FileDownloadNotification";

FileDownload::FileDownload()
{
}

FileDownload::~FileDownload()
{
}

void FileDownload::downloadFile(const string& url, const string& filename )
{
	CCHttpRequest* request = new CCHttpRequest;

	request->setUrl(url.c_str());
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this, callfuncND_selector(FileDownload::_requestCompleted));
	request->setTag(filename.c_str());

	CCHttpClient::getInstance()->send(request);

	request->release();
}

void FileDownload::loadNetImage(CCLayer* layer, char* url, char* filename)
{
    int id = NotificationCenter::shared()->addImgObserver(filename, layer);

	CCHttpRequest* request = new CCHttpRequest;
    
	request->setUrl(url);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this, callfuncND_selector(FileDownload::_imageCompleted));
	request->setTag(CCString::createWithFormat("%05d;%s", id, filename)->getCString());
    
	CCHttpClient::getInstance()->send(request);
    
	request->release();
}

void FileDownload::_imageCompleted(CCNode* sender, void* data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    
    if (!response)
    {
        CCLog("FileDownload: [Error] receive null data");
        return;
    }
    
    int statusCode = response->getResponseCode();
    CCLOG("FileDownload: Status Code: [%d]", statusCode);
    
    const char* tag = response->getHttpRequest()->getTag();
    int id;
    char filename[100];
    sscanf(tag, "%05d;%s", &id, filename);
    
    if (0 != strlen(tag))
        CCLOG("FileDownload: [%s] completed", filename);
    
    if (!response->isSucceed())
    {
        CCLOG("FileDownload: response failed");
        CCLOG("FileDownload: error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    vector<char> *buffer = response->getResponseData();
	
    string writePath = CCFileUtils::sharedFileUtils()->getWriteablePath();
    writePath += filename;
    
    FILE *fp = fopen(writePath.c_str(), "wb");
    fwrite(buffer->data(), 1, buffer->size(), fp);
    fclose(fp);
    
    // send Notification
    NotificationCenter::shared()->postNotification(CCString::createWithFormat("ImageDownload%d", id)->getCString());
}

void FileDownload::_requestCompleted(CCNode* sender, void* data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    
    if (!response)
    {
        CCLog("FileDownload: [Error] receive null data");
        return;
    }
    
    // You can get original request type from: response->request->reqType
    int statusCode = response->getResponseCode();
    CCLOG("FileDownload: Status Code: [%d]", statusCode);

    const char* tag = response->getHttpRequest()->getTag();
    if (0 != strlen(tag))
        CCLOG("FileDownload: [%s] completed", tag);
    
    if (!response->isSucceed())
    {
        CCLOG("FileDownload: response failed");
        CCLOG("FileDownload: error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    vector<char> *buffer = response->getResponseData();
	
    string writePath = CCFileUtils::sharedFileUtils()->getWriteablePath();
    writePath += tag;

    FILE *fp = fopen(writePath.c_str(), "wb");
    fwrite(buffer->data(), 1, buffer->size(), fp);
    fclose(fp);

    // send Notification
    NotificationCenter::shared()->postNotification(notificationName, CCString::create(tag));
}

CCSprite* getSpriteFromWriteablePath(const char* name)
{
    CCLOG("getSpriteFromWriteablePath:%s", name);
    
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += name;

	FILE* fp = fopen(path.c_str(),"rb");
	if (!fp)
		return NULL;

	fseek(fp,0,SEEK_END);
	int len = ftell(fp);
	fseek(fp,0,SEEK_SET);
	unsigned char* buf = (unsigned char*)malloc(len);
	fread(buf,len,1,fp);
	fclose(fp);
    
    CCImage* img = new CCImage;
    img->initWithImageData(buf,len);

    free(buf);

    do
    {
        if (!img)
        {
            img->release();
            break;
        }
        
        cocos2d::CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addUIImage(img, path.c_str());
        img->release();

        if (!texture)
            break;

        CCSprite* sprite = CCSprite::createWithTexture(texture);
        if (!sprite)
            break;

        return sprite;
    } while(0);

    //TODO:没加到图时给个默认
    return CCSprite::create("50black.png");//加载资源并非图片时返回的默认图
}

//判断文件是否存在于可写文件夹
bool isFileExistsInWritablePath(const char* name)
{
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += name;

	FILE* fp = fopen(path.c_str(),"rb");
	if (!fp)
		return false;
	fclose(fp);

	return true;
}

//判断文件是否存在于资源文件夹
bool isFileExistsInResourcePath(const char* name)
{
    unsigned long size;
    CCFileUtils* utils = CCFileUtils::sharedFileUtils();
    
    bool notif=utils->isPopupNotify();
    utils->setPopupNotify(false);
    unsigned char * pBytes = utils->getFileData(utils->fullPathForFilename(name).c_str(), "rb", &size);
    utils->setPopupNotify(notif);

    if (pBytes) {
        delete[] pBytes;
        return true;
    }
    
    return false;
}
