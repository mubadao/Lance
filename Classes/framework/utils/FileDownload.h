//
//  FileDownload.h
//  lance
//
//  Created by Limin on 12-11-18.
//  Copyright (c) 2012年 HappyBluefin. All rights reserved.
//

#ifndef _FileDownload_H_
#define _FileDownload_H_

#include "CommonHeader.h"

class FileDownload : public Singleton<FileDownload>, public CCObject
{
    void _requestCompleted(CCNode* sender, void *data);
    void _imageCompleted(CCNode* sender, void *data);

public:
    static const char* notificationName;
    
    FileDownload();
    ~FileDownload();
    
    void downloadFile(const string& url, const string& filename);

    void loadNetImage(CCLayer* layer, char* filename, char* url);
};

#define FILEDOWNLOAD FileDownload::shared()

CCSprite* getSpriteFromWriteablePath(const char* name);
char* getFileDataFromWriteablePath(const char* name);
bool isFileExistsInWritablePath(const char* name);
bool isFileExistsInResourcePath(const char* name);


#endif