#include "CommonHelper.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import "UIDevice+IdentifierAddition.h"

const char* getDeviceID()
{
	NSString* deviceName = [[UIDevice currentDevice] uniqueDeviceIdentifier];
//    NSString* deviceName = [[UIDevice currentDevice] uniqueIdentifier];    
    return [deviceName cStringUsingEncoding:NSASCIIStringEncoding];
}

void gJumpToStore()
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://itunes.apple.com/app/id581978359?mt=8&ls=1"]];
}



#endif