//
//  MultiPlatform.cpp
//  lance
//
//  Created by bo on 12-10-28.
//  Copyright 2012年 Elex. All rights reserved.
//

#include <iostream>
#include "MultiPlatform.h"
#include "IOSPlatform.h"
#include "AndroidPlatform.h"

MultiPlatform* MultiPlatform::msMultiPlatform = NULL;

MultiPlatform* MultiPlatform::shared()
{
    if(msMultiPlatform == NULL)
        msMultiPlatform = new MultiPlatform();
    return msMultiPlatform;
}

void MultiPlatform::setPlatformType(const char* type)
{
    mPlatformType = type;
    string playType = type;
    if (playType == "ios")
        mPlatform = new IosPlatform();
    else if(playType == "android")
        mPlatform = new AndroidPlatform();
}

const char* MultiPlatform::getPlatformType()
{
    return mPlatformType;
}

void MultiPlatform::setLanguage(const char* language)
{
    mLanguage = language;
}

const char* MultiPlatform::getLanguage()
{
    return mLanguage;
}

PlatformInterface* MultiPlatform::getPlatform()
{
    return mPlatform;
}