//
//  FMUIWebViewBridge.h
//  lance
//
//  Created by bo on 12-10-27.
//  Copyright 2012年 Elex. All rights reserved.
//

#ifndef _FMUIWebViewBridge_h_
#define _FMUIWebViewBridge_h_

#import <Foundation/Foundation.h>  

#import <CoreLocation/CoreLocation.h>  

#import <UIKit/UIKit.h>  



#import "FMLayerWebView.h"  



@interface FMUIWebViewBridge : NSObject<UIWebViewDelegate,UIAlertViewDelegate>{  
    
    FMLayerWebView * mLayerWebView;  
    
    UIView    *mView;  
    
    UIWebView *mWebView;  
    
    UIToolbar *mToolbar;  
    
    UIButton *mBackButton; 
    
    float mWebWidth;
    
    float mWebHeight;
    
    float mX;
    
    float mY;
    
}  



-(void) setLayerWebView : (FMLayerWebView*) iLayerWebView URLString:(const char*) urlString;  

-(void) backClicked:(id)sender; 

-(void) setWebSize:(float)width webHeight:(float)height;

-(void) setWebPosition:(float)x webY:(float)y;

-(void) refreshPosition;



@end 

#endif
