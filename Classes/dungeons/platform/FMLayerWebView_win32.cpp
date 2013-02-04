//  FMLayerWebView.mm  

//  WebViewDemo  

//  

//  Created by Yanghui Liu on 12-6-5.  

//  Copyright (c) 2012Äê FMinutes company. All rights reserved.  

//  



#include "FMLayerWebView.h"  

static FMLayerWebView* g_FMLayerWebView = NULL;

FMLayerWebView::FMLayerWebView(){  

}  



FMLayerWebView::~FMLayerWebView(){  


}  

FMLayerWebView* FMLayerWebView::shared(){  
	if(g_FMLayerWebView == NULL)
		g_FMLayerWebView = FMLayerWebView::create();
	return g_FMLayerWebView;
}  



void FMLayerWebView::webViewDidFinishLoad(){  

}  



void FMLayerWebView::onBackbuttonClick(){  

	this->removeFromParentAndCleanup(true);  

}  



bool FMLayerWebView::init(){  

	if ( !CCLayer::init() ){  

		return false;  

	}  
	return true;  

}  

void FMLayerWebView::setUrl(const char* url)
{
	
}

void FMLayerWebView::setWebSize(float width, float height)
{
	
}

void FMLayerWebView::setWebPosition(float x, float y)
{
	
}


