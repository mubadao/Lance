//
//  ShopIAPHelper.h
//  Lance
//
//  Created by Limin on 12-12-03.
//  Copyright 2011年 HappyBluefin. All rights reserved.
//

#import "IAPHelper.h"

#define LANCE_IAP_COUNT     6
extern NSString* gIapName[LANCE_IAP_COUNT];

@interface ShopIAPHelper : IAPHelper

@property (nonatomic, retain) NSMutableArray* purchaseInfoList;	// 已购买但未核实的单,为避免丢单而做

+ (ShopIAPHelper *) sharedHelper;
- (void) purchaseItem:(int)index;
- (void) removePurchaseByUUID:(NSString*)uuid;
- (void) checkLostPurchase;

- (NSString*)getItemCost:(NSString*)identifier;
- (NSArray*) getItemCost;

-(void)showHUD;
-(void)hideHUD;

@end
