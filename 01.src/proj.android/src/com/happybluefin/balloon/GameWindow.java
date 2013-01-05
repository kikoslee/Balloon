/**
 * @brief   游戏窗口类定义文件。
 * @author  赵一
 * @date    2012/01/07
 * @version 0.1
 */

package com.happybluefin.balloon;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.widget.Toast;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.happybluefin.android.framework.utility.system.Comment;
import com.happybluefin.android.framework.utility.system.Network;
import com.happybluefin.android.framework.utility.system.Utility;
import com.happybluefin.android.framework.utility.thirdpart.advertisement.Banner.GoogleAdmobSDK;
import com.happybluefin.android.framework.utility.thirdpart.rankinglist.ScoreloopSDK;
import com.happybluefin.android.framework.utility.thirdpart.statistics.UmengSDK;

import com.happybluefin.balloon.R;


/**
 * @brief  游戏窗口类。
 * @author 赵一
 */
public class GameWindow extends Cocos2dxActivity {
	
    /**
     * @brief     窗口建立函数。
     * @param[in] savedInstanceState 保存状态。
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Log.d(TAG, "onCreate() start");

        //初始化控件
        _initView();

        //初始化友盟
        UmengSDK.autoErrorReport(this);
//      UmengSDK.updateOnlineConfig(this);

        //初始化横幅广告
        GoogleAdmobSDK.createBanner(this, balloon.getAdmobUnitID(), Gravity.BOTTOM);

        //Log.d(TAG, "onCreate() end");
    }

    /**
     * @brief  窗口释放函数。
     */
    @Override
    public void onDestroy() {
        //Log.d(TAG, "onDestroy() start");

        //销毁横幅广告
        GoogleAdmobSDK.destoryBanner();

        // unregist receiver
        unregisterReceiver(mReceiver);
        
        super.onDestroy();

        //Log.d(TAG, "onDestroy() end");
    }

    /**
     * @brief  窗口暂停函数。
     */
    @Override
    protected void onPause() {
        //Log.d(TAG, "onPause() start");

        super.onPause();

        UmengSDK.onPause(this);

        //Log.d(TAG, "onPause() end");
    }

    /**
     * @brief  窗口再开始函数。
     */
    @Override
    protected void onResume() {
        //Log.d(TAG, "onResume() start");

        super.onResume();

        UmengSDK.onResume(this);

        //Log.d(TAG, "onResume() end");
    }

    /**
     * @brief  初始化控件函数。
     */
    private void _initView() {
        //Log.d(TAG, "_initView() start");

        //初始化消息接收器
        IntentFilter filter = new IntentFilter();
        filter.addAction(Define.Action.ACTION);
        registerReceiver(mReceiver, filter);

        //Log.d(TAG, "_initView() end");
    }
    
    /**
     * @brief 广播接收器。
     */
    private BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            //Log.d(TAG, "BroadcastReceiver::onReceive() start");

            if (intent != null) {
                Bundle bundle = intent.getExtras();

                int type = bundle.getInt("TYPE");

                String url = bundle.getString("URL");
                switch (type) {
                case Define.MessageID.SHOW_LEADERBOARD: {
                    //显示排行榜
                    if (Network.getConnectivityState(GameWindow.this) == true) {
                        //排行榜名称
                        String boardName = bundle.getString("BOARDNAME");
                        if (ScoreloopSDK.showLeaderboards(GameWindow.this) != true) {
                            Log.e(TAG, "BroadcastReceiver::onReceive(): show leaderboard failed!");
                        }
                    }
                    else {
                        //提示连接网络
                        Toast.makeText(GameWindow.this,
                                       R.string.can_not_connect_network,
                                       Toast.LENGTH_SHORT);
                    }
                    break;
				}
                case Define.MessageID.REPORT_SCORE: {
                    //提交得分
                    if (Network.getConnectivityState(GameWindow.this) == true) {
                        //排行榜名称
                        String boardName = bundle.getString("BOARDNAME");
                        //排行榜分值
                        int score = bundle.getInt("SCORE");
                        if (ScoreloopSDK.submit((double)score) != true) {
                            Log.e(TAG, "BroadcastReceiver::onReceive(): submit score failed!");
                        }
                    }
                    else {
                        //提示连接网络
                        Toast.makeText(GameWindow.this,
                                       R.string.can_not_connect_network,
                                       Toast.LENGTH_SHORT).show();
                    }
                    break;
				}
                case Define.MessageID.WEB_BROWSER: {
                    //显示网页
                    if (Network.getConnectivityState(GameWindow.this) == true) {
                        if (Utility.startBrowser(GameWindow.this, url) != true) {
                            Log.e(TAG, "BroadcastReceiver::onReceive(): start browser failed!");
                        }
                    }
                    else {
                        //提示连接网络
                        Toast.makeText(GameWindow.this,
                                       R.string.can_not_connect_network,
                                       Toast.LENGTH_SHORT).show();
                    }
                    break;
				}
                case Define.MessageID.GOTO_REVIEW: {
                    //提交评价
                    if (Network.getConnectivityState(GameWindow.this) == true) {
                        if (Comment.startGooglePlayComment(GameWindow.this, "com.happybluefin.balloon") != true) {
                            Log.e(TAG, "BroadcastReceiver::onReceive(): review failed!");
                        }
                    }
                    else {
                        //提示连接网络
                        Toast.makeText(GameWindow.this,
                                       R.string.can_not_connect_network,
                                       Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
				}
            }

            //Log.d(TAG, "BroadcastReceiver::onReceive() end");
        }
    };
    
    /**
     * @brief 日志标记。
     */
    private static final String TAG = "GameWindow";
}
