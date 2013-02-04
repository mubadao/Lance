//  FMLayerWebView.h  

//  WebViewDemo  

//  

//  Created by Yanghui Liu on 12-6-5.  

//  Copyright (c) 2012年 FMinutes company. All rights reserved.  

//  



#ifndef WebViewDemo_FMLayerWebView_h  

#define WebViewDemo_FMLayerWebView_h  


#include "Global.h"  

class FMLayerWebView : public CCLayer{  
    
public:  
    
    FMLayerWebView();  
    
    ~FMLayerWebView();  
    
    virtual bool init();  
    
    CREATE_FUNC(FMLayerWebView);  
    
    void webViewDidFinishLoad();  
    
    void onBackbuttonClick();  
    
    void setUrl(const char* url);
    
    void setWebSize(float width, float height);
    
    void setWebPosition(float x, float y);
    
    void show(CCNode* layer, const char* url);
    
    void hide();
    
    static FMLayerWebView* shared();
    
    
private:  
    int mWebViewLoadCounter;  
    
};  



#endif  