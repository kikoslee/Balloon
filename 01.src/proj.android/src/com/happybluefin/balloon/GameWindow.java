package com.happybluefin.balloon;

import android.os.Bundle;
import android.view.Gravity;

import org.cocos2dx.lib.Cocos2dxActivity;

//import com.happybluefin.android.dialog.MessageDialog;
import com.happybluefin.android.framework.utility.thirdpart.advertisement.Banner.GoogleAdmobSDK;
import com.happybluefin.android.framework.utility.thirdpart.statistics.UmengSDK;
//import com.happybluefin.android.utility.thirdpart.rankinglist.ScoreloopSDK;
//import com.happybluefin.android.utility.system.Comment;
//import com.happybluefin.android.utility.system.Network;
//import com.happybluefin.android.utility.system.Share;
//import com.happybluefin.android.utility.system.Utility;
//import com.happybluefin.tapburstfree.R;
//import com.happybluefin.tapburstfree.message.Define;
//import com.happybluefin.tapburstfree.application.TapBurstFreeApplication;

//import android.content.BroadcastReceiver;
//import android.content.Context;
//import android.content.DialogInterface;
//import android.content.Intent;
//import android.content.IntentFilter;
//import android.util.Log;
//import android.widget.Toast;

public class GameWindow extends Cocos2dxActivity {
	
	/**
     * @brief  取得Admob广告ID函数。
     */
    private native String getAdmobUnitID();
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //初始化控件
//        _initView();

        //初始化友盟
        UmengSDK.autoErrorReport(this);
//      UmengSDK.updateOnlineConfig(this);

        //初始化横幅广告
        GoogleAdmobSDK.createBanner(this, getAdmobUnitID(), Gravity.BOTTOM);
    }

    @Override
    public void onDestroy() {
        //销毁横幅广告
        GoogleAdmobSDK.destoryBanner();

        // unregist receiver
//        unregisterReceiver(mReceiver);
        super.onDestroy();
    }

    @Override
    protected void onPause() {
        super.onPause();
        UmengSDK.onPause(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        UmengSDK.onResume(this);
    }

    private void _initView() {
        //初始化消息接收器
//        IntentFilter filter = new IntentFilter();
//        filter.addAction(Define.Action.ACTION);
//        registerReceiver(mReceiver, filter);
    }
    
    /**
     * @brief 广播接收器。
     */
//    private BroadcastReceiver mReceiver = new BroadcastReceiver() {
//        @Override
//        public void onReceive(Context context, Intent intent) {
//            //Log.d(TAG, "BroadcastReceiver::onReceive() start");
//
//            if (intent != null) {
//                Bundle bundle = intent.getExtras();
//
//                int type = bundle.getInt("TYPE");
//
//                String url = bundle.getString("URL");
//                switch (type) {
//                case Define.MessageID.SHOW_LEADERBOARD:
//                    //显示排行榜
//                    if (Network.getConnectivityState(TapBurstFreeWindow.this) == true) {
//                        //排行榜名称
//                        String boardName = bundle.getString("BOARDNAME");
//                        if (ScoreloopSDK.showLeaderboards(TapBurstFreeWindow.this) != true) {
//                            Log.e(TAG, "BroadcastReceiver::onReceive(): show leaderboard failed!");
//                        }
//                    }
//                    else {
//                        //提示连接网络
//                        Toast.makeText(TapBurstFreeWindow.this,
//                                       R.string.can_not_connect_network,
//                                       Toast.LENGTH_SHORT);
//                    }
//                    break;
//
//                case Define.MessageID.REPORT_SCORE:
//                    //提交得分
//                    if (Network.getConnectivityState(TapBurstFreeWindow.this) == true) {
//                        //排行榜名称
//                        String boardName = bundle.getString("BOARDNAME");
//                        //排行榜分值
//                        int score = bundle.getInt("SCORE");
//                        if (ScoreloopSDK.submit((double)score) != true) {
//                            Log.e(TAG, "BroadcastReceiver::onReceive(): submit score failed!");
//                        }
//                    }
//                    else {
//                        //提示连接网络
//                        Toast.makeText(TapBurstFreeWindow.this,
//                                       R.string.can_not_connect_network,
//                                       Toast.LENGTH_SHORT);
//                    }
//                    break;
//
//                case Define.MessageID.SHARE_TEXT:
//                    //共享文本
//                    String text = bundle.getString("TEXT");
//                    if (Network.getConnectivityState(TapBurstFreeWindow.this) == true) {
//                        //分享文本
//                        if (Share.shareText(TapBurstFreeWindow.this,
//                                            getString(R.string.app_name),
//                                            getString(R.string.app_name),
//                                            text) != true) {
//                            Log.e(TAG, "BroadcastReceiver::onReceive(): share text failed!");
//                        }
//                    }
//                    else {
//                        //提示连接网络
//                        Toast.makeText(TapBurstFreeWindow.this,
//                                       R.string.can_not_connect_network,
//                                       Toast.LENGTH_SHORT);
//                    }
//                    break;
//
//                case Define.MessageID.WEB_BROWSER:
//                    //显示网页
//                    if (Network.getConnectivityState(TapBurstFreeWindow.this) == true) {
//                        if (Utility.startBrowser(TapBurstFreeWindow.this, url) != true) {
//                            Log.e(TAG, "BroadcastReceiver::onReceive(): start browser failed!");
//                        }
//                    }
//                    else {
//                        //提示连接网络
//                        Toast.makeText(TapBurstFreeWindow.this,
//                                       R.string.can_not_connect_network,
//                                       Toast.LENGTH_SHORT);
//                    }
//                    break;
//
//                case Define.MessageID.GOTO_REVIEW:
//                    //提交评价
//                    if (Network.getConnectivityState(TapBurstFreeWindow.this) == true) {
//                        if (Comment.startGooglePlayComment(TapBurstFreeWindow.this, "com.happybluefin.tapburstfree") != true) {
//                            Log.e(TAG, "BroadcastReceiver::onReceive(): review failed!");
//                        }
//                    }
//                    else {
//                        //提示连接网络
//                        Toast.makeText(TapBurstFreeWindow.this,
//                                       R.string.can_not_connect_network,
//                                       Toast.LENGTH_SHORT);
//                    }
//                    break;
//
//                case Define.MessageID.EXIT_APPLICATION:
//                    //退出
//                    _exitApplication();
//                    break;
//
//                default:
//                    break;
//                }
//            }
//
//            //Log.d(TAG, "BroadcastReceiver::onReceive() end");
//        }
//    };
    
    private static final String TAG = "Balloon";
}
