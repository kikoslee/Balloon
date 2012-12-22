//
//  tapburstfreeAppController.h
//  tapburstfree
//
//  Created by Limin on 12-9-4.
//  Copyright HappyBluefin 2012年. All rights reserved.
//

#import <UIKit/UIKit.h>

#define Mediator_Mogo       1    // 芒果
#define Mediator_MobiSage   2    // 艾德思奇

#define Mediator_Platform   Mediator_Mogo


#if Mediator_Platform == Mediator_Mogo

#import "AdMoGoDelegateProtocol.h"
#import "AdMoGoView.h"
#import "AdMoGoWebBrowserControllerUserDelegate.h"

@interface BannerAdViewController : UIViewController<AdMoGoDelegate,AdMoGoWebBrowserControllerUserDelegate> {
    AdMoGoView *adView;
}
@property (nonatomic, retain) AdMoGoView *adView;
@end

#else

#import "AdSageDelegate.h"
#import "AdSageView.h"
@interface BannerAdViewController : UIViewController <AdSageDelegate> {
    AdSageView *adView;
}
@end

#endif