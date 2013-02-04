//
//  AMFCaller.h
//  Lance网络命令远程调用
//
//  Created by Zhaoyi on 12.07.25.
//  Copyright (c) 2012年 tunnies. All rights reserved.

#ifndef _AMF_CALLER_H_
#define _AMF_CALLER_H_

#import "AMFRemotingCall.h"

@interface AMFCaller : NSObject <AMFRemotingCallDelegate>
{
	AMFRemotingCall *mRemoteCaller;
}

+ (AMFCaller*)shared;

- (void)setURL:(NSString*)url;

- (void)setURL:(NSString*)url service:(NSString*)service method:(NSString*)method;

- (void)sendPackage:(NSArray*)package;

@end

#endif // __REMOTE_CALLER_H
