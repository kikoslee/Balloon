/**
 * @brief   应用程序类定义文件。
 * @author  赵一
 * @date    2012/01/07
 * @version 0.1
 */

package com.happybluefin.balloon;

import java.util.Locale;

import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.happybluefin.android.framework.utility.thirdpart.rankinglist.ScoreloopSDK;
import com.happybluefin.android.framework.utility.thirdpart.statistics.UmengSDK;

/**
 * @brief  应用程序类。
 * @author 赵一
 */
public class balloon extends Application {
	
	/**
     * @brief  取得Admob广告ID函数。
     */
    public static native String getAdmobUnitID();
	
	/**
     * @brief  取得设备语言编码。
     */
    public static native int nativeSetLang(String a);
	
    /**
     * @brief  取得ScoreLoopID函数。
     * @return ScoreLoopID。
     */
    public static native String getScoreLoopSecretID();
	
    /**
     * @brief  应用程序建立函数。
     */
    public void onCreate() {
        //Log.d(TAG, "onCreate() start");

        mContext = this;

        //设定设备语言代码
        _initLanguage();

        //初始化排行榜
       _initLeaderboards();
               
		//Log.d(TAG, "onCreate() end");
    }

    /**
     * @brief     提交分数函数。
     * @param[in] boardName 排行榜名称。
     * @param[in] score     分数。
     */
    public static void reportScore(String boardName, int score) {
        //Log.d(TAG, "reportScore() start");

        if (mContext != null) {
            Bundle bundle = new Bundle();
            Intent intent = new Intent(Define.Action.ACTION);
            bundle.putInt("TYPE", Define.MessageID.REPORT_SCORE);
            bundle.putString("BOARDNAME", boardName);
            bundle.putInt("SCORE", score);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }
        else {
            Log.e(TAG, "reportScore(): mContext is NULL.");
        }

        //Log.d(TAG, "reportScore() end");
    }

    /**
     * @brief     显示排行榜函数。
     * @param[in] boardName 排行榜名称。
     */
    public static void showLeaderBoard(String boardName) {
        //Log.d(TAG, "showLeaderBoard() start");

        if (mContext != null) {
            Bundle bundle = new Bundle();
            Intent intent = new Intent(Define.Action.ACTION);
            bundle.putInt("TYPE", Define.MessageID.SHOW_LEADERBOARD);
            bundle.putString("BOARDNAME", boardName);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }
        else {
            Log.e(TAG, "showLeaderBoard(): mContext is NULL.");
        }

        //Log.d(TAG, "showLeaderBoard() end");
    }

    /**
     * @brief     打开网页函数。
     * @param[in] url 网页地址。
     */
    public static void gotoUrl(String url) {
        //Log.d(TAG, "gotoUrl() start");

        if (mContext != null) {
            Bundle bundle = new Bundle();
            Intent intent = new Intent(Define.Action.ACTION);
            bundle.putInt("TYPE", Define.MessageID.WEB_BROWSER);
            bundle.putString("URL", url);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }
        else {
            Log.e(TAG, "gotoUrl(): mContext is NULL.");
        }

        //Log.d(TAG, "gotoUrl() end");
    }

    /**
     * @brief  评价函数。
     */
    public static void gotoReview() {
        //Log.d(TAG, "gotoReview() start");

        if (mContext != null) {
            Bundle bundle = new Bundle();
            Intent intent = new Intent(Define.Action.ACTION);
            bundle.putInt("TYPE", Define.MessageID.GOTO_REVIEW);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }
        else {
            Log.e(TAG, "gotoReview(): mContext is NULL.");
        }

        //Log.d(TAG, "gotoReview() end");
    }
    
    /**
     * @brief     跳转到GooglePlay游戏列表
     * @param[in] context 上下文。
     */
    public static void gotoMoreGame() {
        //Log.d(TAG, "gotoMoreGame() start");

        if (mContext != null) {
            Bundle bundle = new Bundle();
            Intent intent = new Intent(Define.Action.ACTION);
            bundle.putInt("TYPE", Define.MessageID.GOTO_MOREGAME);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }
        else {
            Log.e(TAG, "gotoMoreGame(): mContext is NULL.");
        }

        //Log.d(TAG, "gotoMoreGame() end");
    }
    
    /**
     * @brief     Umeng取得在线参数函数。
     * @param[in] name 在线参数键值。
     * @return    Umeng在线参数。
     */
    public static int umengGetParamValue(String name) {
        //Log.d(TAG, "umengGetParamValue() start");

        int ret = UmengSDK.getConfigIntParams(mContext, name, 0);

        //Log.d(TAG, "umengGetParamValue() end");

        return ret;
    }

    /**
     * @brief     Umeng自定义事件函数。
     * @param[in] name  自定义事件键值。
     * @param[in] value 自定义事件数值。
     */
    public static void umengCustomEvent(String name, String value) {
        //Log.d(TAG, "umengCustomEvent() start");

        if (mContext != null) {
            UmengSDK.customEvent(mContext, name, value);
        }

        //Log.d(TAG, "umengCustomEvent() end");
    }
    
    /**
     * @brief  设定语言代码
     */
    private void _initLanguage() {
		 String language1 = "";
		 String language2 = "";
		 
		 language1 = Locale.getDefault().getLanguage();
		 Log.i("jnitest", "------language1:-----"+language1);
		 language2 = Locale.getDefault().toString();
		 Log.i("jnitest", "------language2:-----"+language2);
		
		
		 if(language1.compareTo("zh") == 0)
			 nativeSetLang(language2);
		 else
			 nativeSetLang(language1); 
    }
    
    /**
     * @brief  初始化排行榜函数。
     */
	private void _initLeaderboards() {
		//Log.d(TAG, "_initLeaderboards() start");

		ScoreloopSDK.init(this, getScoreLoopSecretID());

		//Log.d(TAG, "_initLeaderboards() end");
	}

    static {
        try {
            System.loadLibrary("game");
        }
        catch (UnsatisfiedLinkError e) {
            e.printStackTrace();
            throw e;
        }
    }
    
    /**
     * @brief 上下文。
     */
    private static Context mContext = null;

    /**
     * @brief 日志标记。
     */
    private static final String TAG = "balloon";

}