//
//  FMUIWebViewBridge.cpp
//  lance
//
//  Created by bo on 12-10-27.
//  Copyright 2012年 Elex. All rights reserved.
//

#include <iostream>
#import "FMUIWebViewBridge.h"  

#import "EAGLView.h"  

@implementation FMUIWebViewBridge  

- (id)init{  
    
    self = [super init];  
    
    if (self) {  
        mX = 0;
        mY = 0;
        mWebWidth = 320;
        mWebHeight = 534;
        // init code here.  
        
        mView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, mWebWidth ,mWebHeight)];  

        int wBottomMargin = mWebHeight*0.10;  
        
        int wWebViewHeight = mWebHeight - wBottomMargin;  
        
        mWebView = [[UIWebView alloc] initWithFrame:CGRectMake(mX, mY, mWebWidth, wWebViewHeight)]; 
        
        mWebView.delegate = self;  
        
        //Create a button  
        
        mBackButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [mBackButton setFrame:CGRectMake(220, 10, 80, 44)];
        [mBackButton setTitle:@"关闭" forState:UIControlStateNormal];  
//        [mBackButton setImage:[UIImage imageNamed:@"sprite/btn_06.png"] forState:UIControlStateNormal];
//        [mBackButton setImage:[UIImage imageNamed:@"sprite/btn_06_d.png"] forState:UIControlStateHighlighted];
        [mBackButton addTarget:self action:@selector(backClicked:) forControlEvents:UIControlEventTouchUpInside];
        
        [mView addSubview:mWebView]; 
        
        [mView addSubview:mBackButton]; 
        
        [[EAGLView sharedEGLView] addSubview:mView]; 
    }  
    
    return self;  
    
}  

- (void)dealloc{  
    
    [mBackButton release];  
    
    [mWebView release];  
    
    [mView release];  
    
    [super dealloc];  
    
}  



-(void) setLayerWebView : (FMLayerWebView*) iLayerWebView URLString:(const char*) urlString{  
    
    mLayerWebView = iLayerWebView;
    
    NSString *urlBase = [NSString stringWithCString:urlString encoding:NSUTF8StringEncoding];  
    
    [mWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlBase ]]];  
    
    [mWebView setUserInteractionEnabled:NO]; //don't let the user scroll while things are  
    
}  



- (void)webViewDidStartLoad:(UIWebView *)thisWebView {  
    
}  



- (void)webViewDidFinishLoad:(UIWebView *)thisWebView{  
    
    [mWebView setUserInteractionEnabled:YES];  
    
    mLayerWebView->webViewDidFinishLoad();  
    
}  



- (void)webView:(UIWebView *)thisWebView didFailLoadWithError:(NSError *)error {  
    
    if ([error code] != -999 && error != NULL) { //error -999 happens when the user clicks on something before it's done loading.  
        
        
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Network Error" message:@"Unable to load the page. Please keep network connection."  
                              
                                                       delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil];  
        
        [alert show];  
        
        [alert release];  
        
        
        
    }  
    
}  



-(void) backClicked:(id)sender {  
    
    mWebView.delegate = nil; //keep the webview from firing off any extra messages  
    
    //remove items from the Superview...just to make sure they're gone  
    
    [mToolbar removeFromSuperview];  
    
    [mWebView removeFromSuperview];  
    
    [mView removeFromSuperview];  
    
    mLayerWebView->onBackbuttonClick();  
    
}  

-(void) setWebSize:(float)width webHeight:(float)height{
    mWebWidth = width;
    mWebHeight = height;
    [self refreshPosition];
}

-(void) setWebPosition:(float)x webY:(float)y
{
    mX = x;
    mY = y;
    [self refreshPosition];
}

-(void) refreshPosition{
    [mView initWithFrame:CGRectMake(0, 0, mWebWidth ,mWebHeight)];  
    int wBottomMargin = mWebHeight*0.10;  
    int wWebViewHeight = mWebHeight - wBottomMargin;  
    [mWebView initWithFrame:CGRectMake(mX, mY, mWebWidth, wWebViewHeight)];  
    [mToolbar setFrame:CGRectMake(0, wWebViewHeight, mWebWidth, wBottomMargin)]; 
}

@end  