//
//  main.h
//  Android jni
//
//  Created by Zhaoyi on 12-9-19.
//  Copyright (c) 2012年 HappyBluefin. All rights reserved.
//

#ifndef _Main_H_
#define _Main_H_

#include <jni.h>

extern "C"
{

void showLeaderBoard(const char* boardName);
void reportScore(const char* boardName, int score);

void gotoUrl(const char* url);
void gotoReview();

int umengGetParamValue(const char* name);
void umengCustomEvent(const char* name, const char* value);
    
void purchaseItem(const char* itemName);

}
#endif // _Main_H_
