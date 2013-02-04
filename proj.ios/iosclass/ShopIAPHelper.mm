//
//  ShopIAPHelper.m
//  Lance
//
//  Created by Limin on 12-12-03.
//  Copyright 2011年 HappyBluefin. All rights reserved.
//

#import "ShopIAPHelper.h"
#import "GTMBase64.h"
#import "NSString+MD5Addition.h"
#include "NetController.h"
#import "AppController.h"
#import "RootViewController.h"
#import "Waitting.h"

NSString* gIapName[LANCE_IAP_COUNT] =
{
    @"com.happybluefin.lance.coin1",
    @"com.happybluefin.lance.coin2",
	@"com.happybluefin.lance.coin3",
	@"com.happybluefin.lance.coin4",
	@"com.happybluefin.lance.coin5",
	@"com.happybluefin.lance.coin6",
};

@implementation ShopIAPHelper

@synthesize purchaseInfoList = _purchaseInfoList;

static ShopIAPHelper * _sharedHelper;

+ (ShopIAPHelper *) sharedHelper
{
	if (_sharedHelper == nil) {
		_sharedHelper = [[ShopIAPHelper alloc] init];
	}
	return _sharedHelper;    
}

- (id)init
{
	NSSet* productIdentifiers = [NSSet setWithObjects:gIapName count:LANCE_IAP_COUNT];
	if ((self = [super initWithProductIdentifiers:productIdentifiers]))
	{
		_purchaseInfoList = [[NSMutableArray alloc] init];
		NSMutableArray* array = [[NSUserDefaults standardUserDefaults] objectForKey:@"purchaseList"];
		if(array != nil)
			self.purchaseInfoList = array;
	}
	return self;    
}

-(void)dealloc 
{
	[_purchaseInfoList release];
	[super dealloc];
}

-(NSString*)getItemCost:(NSString*)identifier
{
	for(SKProduct* product in self.products)
	{
        if ([product.productIdentifier isEqualToString:identifier])
        {
            NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
            [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
            [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
            [numberFormatter setLocale:product.priceLocale];
            NSString *formattedString = [numberFormatter stringFromNumber:product.price];
            [numberFormatter release];
            return formattedString;
        }
	}
	return nil;
}

-(NSArray*)getItemCost
{
	NSMutableArray* array = [NSMutableArray arrayWithObjects:nil];
	for(SKProduct* product in self.products)
	{
		NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
		[numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
		[numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
		[numberFormatter setLocale:product.priceLocale];
		NSString *formattedString = [numberFormatter stringFromNumber:product.price];
        [numberFormatter release];
		[array addObject:formattedString];
	}
	return [NSArray arrayWithArray:array];
}

-(void)checkLostPurchase
{
	// 检测丢单
	for(NSDictionary* info in _purchaseInfoList)
	{

		NSString* productIdentifier = [info objectForKey:@"identifier"];
        char identifier[200];
        [productIdentifier getCString:identifier maxLength:200 encoding:NSASCIIStringEncoding];

		NSString* dataStr = [info objectForKey:@"data"];
        char data[2000];
        [dataStr getCString:data maxLength:2000 encoding:NSASCIIStringEncoding];

		NSString* dataMD5 = [info objectForKey:@"md5"];
        char md5[200];
        [dataMD5 getCString:md5 maxLength:200 encoding:NSASCIIStringEncoding];

        NetController::shared()->buyMoney(identifier, data);
	}
}

// 购买成功
- (void)provideContent:(NSString*)productIdentifier myData:(NSData*)productData
{
	NSString* dataStr = [GTMBase64 stringByEncodingData:productData];

	NSLog(@"PurchaseInfo:%@", productData);
	// 生成订单号
	NSString *dataMD5 = [dataStr stringFromMD5];
	NSDictionary* info = [NSDictionary dictionaryWithObjectsAndKeys:productIdentifier, @"identifier", dataMD5, @"md5", dataStr, @"data", nil];
	[_purchaseInfoList addObject:info];
	[[NSUserDefaults standardUserDefaults] setObject:_purchaseInfoList forKey:@"purchaseList"];
	[[NSUserDefaults standardUserDefaults] synchronize];

	[self hideHUD];

	// 发送给服务器请求验证
    char identifier[200];
    [productIdentifier getCString:identifier maxLength:200 encoding:NSASCIIStringEncoding];
    char data[5000];
    [dataStr getCString:data maxLength:5000 encoding:NSASCIIStringEncoding];
    char md5[200];
    [dataMD5 getCString:md5 maxLength:200 encoding:NSASCIIStringEncoding];

//    CCLog("%s", data);
    NetController::shared()->buyMoney(identifier, data);
}

// 购买失败
-(void)purchaseFailed:(NSError*)error
{
	[self hideHUD];
//	if (error.code != SKErrorPaymentCancelled) {
//		UIAlertView *alert = [[[UIAlertView alloc] initWithTitle:@"Error!" message:error.localizedDescription delegate:nil cancelButtonTitle:nil otherButtonTitles:@"OK", nil] autorelease];
//		[alert show];
//	}
}

-(void) purchaseItem:(int)index
{
	[self buyProductIdentifier:gIapName[index]];
	[self showHUD];
}

-(void)removePurchaseByUUID:(NSString*)uuid
{
	NSLog(@"removePurchaseByUUID:%@", uuid);
	for(NSDictionary* info in _purchaseInfoList)
	{
		NSString* uuida = [info objectForKey:@"uuid"];
		NSLog(@"  uuid in array:%@", uuida);
		if([uuida isEqualToString:uuid])
		{
			[_purchaseInfoList removeObject:info];
			[[NSUserDefaults standardUserDefaults] setValue:_purchaseInfoList forKey:@"purchaseList"];
			[[NSUserDefaults standardUserDefaults] synchronize];
			break;
		}
	}	
}

-(void)showHUD
{
    Waitting::shared()->show();
}

- (void)hideHUD
{
    Waitting::shared()->hide();
}

@end
