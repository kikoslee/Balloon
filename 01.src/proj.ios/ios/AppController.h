//
//  tapburstfreeAppController.h
//  tapburstfree
//
//  Created by Limin on 12-9-4.
//  Copyright HappyBluefin 2012年. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate>
{
    UIWindow *window;    
}

@property (nonatomic, readonly) RootViewController* viewController;

@end

