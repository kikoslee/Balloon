//
//  tapburstfreeAppController.mm
//  tapburstfree
//
//  Created by Limin on 12-9-4.
//  Copyright Elex 2012年. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "RootViewController.h"

//#import "BannerAdViewController.h"

@implementation AppController

@synthesize viewController = _viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Override point for customization after application launch.
//    HBUmeng::startup();
//    HBUmeng::updateConfig();
    
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0 ];

    // Use RootViewController manage EAGLView
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = __glView;

    // Set RootViewController to window
    [window addSubview: _viewController.view];
    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden: YES];
    
//    if (HBUmeng::getParamValue("isBannerEnable") != 0)
//    {
//        BannerAdViewController* vc = [[BannerAdViewController alloc] init];
//        [vc.view setMultipleTouchEnabled:YES];
//        [_viewController.view addSubview:vc.view];
//    }
    
    [_viewController.view setMultipleTouchEnabled:YES];

    cocos2d::CCApplication::sharedApplication()->run();
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    cocos2d::CCDirector::sharedDirector()->stopAnimation();
    cocos2d::CCDirector::sharedDirector()->pause();
    
	//玩家两天未进入游戏,则再第二天晚上7点50提示
	{
		//获取当前时间在一天后的时间
		NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
		[dateFormatter setDateFormat:@"yyyy-MM-dd"];
		NSString *strDate = [dateFormatter stringFromDate:[[NSDate date] dateByAddingTimeInterval:60*60*24]];
        
		//第二天的晚上8点
		strDate = [NSString stringWithFormat:@"%@ 19:50:00",strDate];
		//NSLog(@"date1:%@",strDate);
		[dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
		NSDate *date = [dateFormatter dateFromString:strDate];
		UILocalNotification * ln = [[UILocalNotification alloc] init];
		ln.fireDate = date;
		ln.timeZone = [NSTimeZone defaultTimeZone];
        ln.repeatInterval = NSDayCalendarUnit;
        ln.applicationIconBadgeNumber = 1;
		NSArray* array = [NSArray arrayWithObjects:
						  @"Come to challange highest score!",
						  @"Your friend get a new higher score. Beat It!",
						  nil];
        NSString* str = [array objectAtIndex:rand()%2];
		ln.alertBody = NSLocalizedString(str, @"");
		[[UIApplication sharedApplication] scheduleLocalNotification:ln];
		[ln release];
		[dateFormatter release];
	}    
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    cocos2d::CCDirector::sharedDirector()->startAnimation();
    cocos2d::CCDirector::sharedDirector()->resume();
//    HBUmeng::updateConfig();
	//LN:打开游戏时,将之前的所有本地通知取消
	[[UIApplication sharedApplication] cancelAllLocalNotifications];
    [[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application
{
}

#pragma mark - Memory management
- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}

- (void)dealloc {
    [super dealloc];
}

@end

