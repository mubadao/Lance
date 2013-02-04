//
//  MultiPlatform.h
//  lance
//
//  Created by bo on 12-10-28.
//  Copyright 2012年 Elex. All rights reserved.
//

#ifndef _MultiPlatform_h_
#define _MultiPlatform_h_

#include "Global.h"
#include "PlatformInterface.h"
class MultiPlatform
{
public:
    static MultiPlatform* shared();
public:
    
    void setPlatformType(const char* type);
    const char* getPlatformType();
    void setLanguage(const char* language);
    const char* getLanguage();
    PlatformInterface* getPlatform();
protected:
    static MultiPlatform* msMultiPlatform;
    const char* mPlatformType;
    const char* mLanguage;
    PlatformInterface* mPlatform;
};

#endif
