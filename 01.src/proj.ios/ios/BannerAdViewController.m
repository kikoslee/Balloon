//
//  BannerAdViewController.h
//  tapburstfree
//
//  Created by Limin on 12-9-4.
//  Copyright HappyBluefin 2012年. All rights reserved.
//

#import "BannerAdViewController.h"
#import "AppController.h"
#import "HBKeys.h"

@implementation BannerAdViewController

#if Mediator_Platform == Mediator_Mogo
@synthesize adView;
#endif

- (void)dealloc {
#if Mediator_Platform == Mediator_Mogo
    adView.delegate = nil;
    adView.adWebBrowswerDelegate = nil;
#else    
    [adView removeFromSuperview];
    [adView release];
#endif
    [super dealloc];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];

#if Mediator_Platform == Mediator_Mogo
    
    AdViewType type;
    NSString* key;
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        type = AdViewTypeLargeBanner;
        key = [NSString stringWithFormat:@"%s", kAdsMogoKey_iPad];
    }
    else
    {
        type = AdViewTypeNormalBanner;
        key = [NSString stringWithFormat:@"%s", kAdsMogoKey];
    }
    
    adView = [[AdMoGoView alloc] initWithAppKey:key
                                         adType:type
                                    expressMode:YES
                             adMoGoViewDelegate:self];
    adView.adWebBrowswerDelegate = self;
    adView.frame = CGRectZero;
    [self.view addSubview:adView];
    [adView release];
#else
    adView = [AdSageView createAdSageBannerAdView:self sizeType:AdSageBannerAdViewSize_320X50];
    adView.frame = CGRectMake(0, 0, 320, 50);
    [self.view addSubview:adView];
#endif
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#if Mediator_Platform == Mediator_MobiSage
- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [adView pauseAdRequest];
}

- (void)viewDidAppear:(BOOL)animated {
    [adView continueAdRequest];
    [super viewDidAppear:animated];
}

#endif

#pragma mark - Ads delegate 
- (UIViewController *)viewControllerForPresentingModalView {
#if Mediator_Platform == Mediator_Mogo
    return self;
#else
    return (UIViewController*)[((AppController*)[[UIApplication sharedApplication] delegate]) viewController];
#endif
}

#if Mediator_Platform == Mediator_Mogo

- (void)adMoGoDidStartAd:(AdMoGoView *)adMoGoView {
//    NSLog(@"广告开始请求回调");
}

- (void)adMoGoDidReceiveAd:(AdMoGoView *)adMoGoView {
//    NSLog(@"广告接收成功回调");
    CGRect bounds = [[UIScreen mainScreen] applicationFrame];
    CGRect rc = adMoGoView.frame;
    rc.origin.x = (bounds.size.width - rc.size.width) / 2;
    adMoGoView.frame = rc;
}

- (void)adMoGoDidFailToReceiveAd:(AdMoGoView *)adMoGoView didFailWithError:(NSError *)error {
//    NSLog(@"广告接收失败回调");
}

- (void)adMoGoClickAd:(AdMoGoView *)adMoGoView {
//    NSLog(@"点击广告回调");
}

- (void)adMoGoDeleteAd:(AdMoGoView *)adMoGoView {
//    NSLog(@"广告关闭回调");
}

#pragma mark -
#pragma mark AdMoGoWebBrowserControllerUserDelegate delegate 

- (void)webBrowserWillAppear {
//    NSLog(@"浏览器将要展示");
}

- (void)webBrowserDidAppear {
//    NSLog(@"浏览器已经展示");
}

- (void)webBrowserWillClosed {
//    NSLog(@"浏览器将要关闭");
}

- (void)webBrowserDidClosed {
//    NSLog(@"浏览器已经关闭");
}

- (void)webBrowserShare:(NSString *)url {
    
}

#else
- (void)adSageDidReceiveBannerAd:(AdSageView *)adSageView {
//    NSLog(@"获取横幅广告成功");
}

- (void)adSageDidFailToReceiveBannerAd:(AdSageView *)adSageView {
//    NSLog(@"获取横幅广告失败");
}

- (void)adSageDidReceiveFullScreenAd:(AdSageView *)adSageView {
//    NSLog(@"获取全屏广告成功");
}

- (void)adSageDidFailToReceiveFullScreenAd:(AdSageView *)adSageView {
//    NSLog(@"获取全屏广告失败");
}

- (void)adSageDidCloseFullScreenAd:(AdSageView *)adSageView {
//    NSLog(@"全屏广告被关闭");
}

- (void)adSageWillPresentFullScreenModal:(AdSageView *)adSageView {
//    NSLog(@"内置浏览器弹出");
}

- (void)adSageDidDismissFullScreenModal:(AdSageView *)adSageView {
//    NSLog(@"内置浏览器关闭");
}

#endif

@end
