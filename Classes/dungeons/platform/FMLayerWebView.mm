//  FMLayerWebView.mm  

//  WebViewDemo  

//  

//  Created by Yanghui Liu on 12-6-5.  

//  Copyright (c) 2012年 FMinutes company. All rights reserved.  

//  



#include "FMLayerWebView.h"  

#include "FMUIWebViewBridge.h"  



static FMUIWebViewBridge *g_FMUIWebViewBridge=nil;  

static FMLayerWebView* g_FMLayerWebView = nil;

FMLayerWebView::FMLayerWebView(){  
    
}  



FMLayerWebView::~FMLayerWebView(){  
    
    [g_FMUIWebViewBridge release]; 
    [g_FMLayerWebView release]; 
    
}  

FMLayerWebView* FMLayerWebView::shared(){  
    if(g_FMLayerWebView == nil)
        g_FMLayerWebView = FMLayerWebView::create();
    return g_FMLayerWebView;
}  



void FMLayerWebView::webViewDidFinishLoad(){  
    
}  



void FMLayerWebView::onBackbuttonClick(){  
    
    hide();
    
}  



bool FMLayerWebView::init(){  
    
    if ( !CCLayer::init() ){  
        
        return false;  
        
    }  
    
    g_FMUIWebViewBridge = [[FMUIWebViewBridge alloc] init];  
     
    
    return true;  
    
}  

void FMLayerWebView::setUrl(const char* url)
{
    [g_FMUIWebViewBridge setLayerWebView : this URLString:url]; 
}

void FMLayerWebView::setWebSize(float width, float height)
{
    [g_FMUIWebViewBridge setWebSize : width webHeight:height];
}

void FMLayerWebView::setWebPosition(float x, float y)
{
    [g_FMUIWebViewBridge setWebPosition : x webY:y];
}

void FMLayerWebView::show(CCNode* layer, const char* url)
{
    setUrl(url);
    removeFromParentAndCleanup(false);
    retain();

    FRAMEWORK->getDialogMask()->removeFromParentAndCleanup(true);
    layer->addChild(FRAMEWORK->getDialogMask());
    layer->addChild(this); 
}

void FMLayerWebView::hide()
{
    FRAMEWORK->getDialogMask()->removeFromParentAndCleanup(true);
    removeFromParentAndCleanup(true);
}


