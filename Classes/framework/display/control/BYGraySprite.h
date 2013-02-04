// BYGraySprite.h  
// Demo  
//  
// Created by Yanghui Liu on 12-11-2.  
// Copyright (c) 2012Äê BoyoJoy. All rights reserved.  
//  


#ifndef Demo_BYGraySprite_h  
#define Demo_BYGraySprite_h  


#include "cocoa/CCGeometry.h"  
#include "cocos2d.h"  
USING_NS_CC;  


class BYGraySprite : public CCSprite{  


public:  
	BYGraySprite();  
	virtual ~BYGraySprite();  
	static BYGraySprite* create(const char* pszFileName);  
	bool initWithTexture(CCTexture2D* pTexture, const CCRect& tRect);  
	virtual void draw();  


};  


#endif  
