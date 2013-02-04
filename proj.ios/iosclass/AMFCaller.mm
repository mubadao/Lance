//
//  AMFCaller.mm
//  Lance网络命令远程调用
//
//  Created by Zhaoyi on 12.07.25.
//  Copyright (c) 2012年 tunnies. All rights reserved.
//

#import "AMFCaller.h"

#include "NetController.h"

@implementation AMFCaller

#pragma mark - Initialization & Deallocation

static AMFCaller* _sharedAMFCaller = nil;

+ (AMFCaller*)shared
{
	if(_sharedAMFCaller == nil)
	{
		_sharedAMFCaller = [[AMFCaller alloc] init];
	}
	return _sharedAMFCaller;
}

- (id)init
{
    if (self = [super init])
    {
        mRemoteCaller = [[AMFRemotingCall alloc] init];
        //设置远程调用服务
        mRemoteCaller.service = @"BaseService";
        //设置远程调用方法
        mRemoteCaller.method = @"dispatch";
        //设置远程调用回调
        mRemoteCaller.delegate = self;
    }
    
    return self;
}

- (void)dealloc
{
    [mRemoteCaller release];
    [super dealloc];
}

- (void)setURL:(NSString*)url
{
    //设置远程调用URL
    mRemoteCaller.URL = [NSURL URLWithString: url];
}

- (void)setURL:(NSString*)url service:(NSString*)service method:(NSString*)method
{
    //设置远程调用URL
    mRemoteCaller.URL = [NSURL URLWithString: url];
    //设置远程调用服务
    mRemoteCaller.service = service;
    //设置远程调用方法
    mRemoteCaller.method = method;
}

#pragma mark - Public methods

- (void)_test
{
    [mRemoteCaller start];
}

- (void)sendPackage:(NSArray*)package
{
    NSLog(@"AMF Send Data:\n%@", package);

    mRemoteCaller.arguments = package;
    [self performSelector:@selector(_test) withObject:nil afterDelay:0.05];
}

#pragma mark - AMFRemotingCall Delegate methods

- (void)remotingCallDidFinishLoading:(AMFRemotingCall *)remotingCall 
                      receivedObject:(NSObject *)object
{
    NSLog(@"AMF Received Data:\n%@", object);

    NetController::shared()->parseData(object);
}

- (void)remotingCall:(AMFRemotingCall *)remotingCall didFailWithError:(NSError *)error
{
    NSLog(@"AMF Received Failed:\n%@", error.description);

    NetController::shared()->receiveError();
}

@end
