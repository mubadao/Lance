#ifndef _CommonHeader_H_
#define _CommonHeader_H_

#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

#include "cocos2d.h"
USING_NS_CC;

#include "cocos-ext.h"
USING_NS_CC_EXT;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#define Audio SimpleAudioEngine::sharedEngine()

#include "Singleton.h"

enum TouchPriority
{
    touch_priority_0 = 0,
    touch_priority_1 = -10,
    touch_priority_2 = -20,
    touch_priority_3 = -30,     // mask priority
    touch_priority_4 = -40,
    touch_priority_5 = -50,
};

bool isTouchInside(CCTouch* pTouch, CCNode* node);

#endif