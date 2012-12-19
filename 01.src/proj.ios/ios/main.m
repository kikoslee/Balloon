//
//  main.m
//  tapburstfree
//
//  Created by Limin on 12-9-4.
//  Copyright Elex 2012年. All rights reserved.
//

#import <UIKit/UIKit.h>

// #import "AdSageManager.h"

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//    [[AdSageManager getInstance] setAdSageKey:@"a1ff9b67a24f4d35bfaa405ae0a5172d"];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retVal;
}
