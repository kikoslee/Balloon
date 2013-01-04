package com.happybluefin.balloon;

import java.util.Locale;

import android.app.Application;
import android.content.Context;
import android.util.Log;

import com.happybluefin.android.framework.utility.thirdpart.statistics.UmengSDK;

public class balloon extends Application {
	
	/**
     * @brief  取得设备语音。
     */
	private native int nativeSetLang(String a);
 
    public void onCreate() {
        mContext = this;

        //设定设备语言代码
        _initLanguage();

        //��ʼ�����а�
//        _initLeaderboards();
    }
    
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
     * @brief     提交分数函数。
     * @author    赵一
     * @param[in] boardName 排行榜名称。
     * @param[in] score     分数。
     */
//    public static void reportScore(String boardName, int score) {
//        //Log.d(TAG, "reportScore() start");
//
//        if (mContext != null) {
//            Bundle bundle = new Bundle();
//            Intent intent = new Intent(Define.Action.ACTION);
//            bundle.putInt("TYPE", Define.MessageID.REPORT_SCORE);
//            bundle.putString("BOARDNAME", boardName);
//            bundle.putInt("SCORE", score);
//            intent.putExtras(bundle);
//            mContext.sendBroadcast(intent);
//        }
//        else {
//            Log.e(TAG, "reportScore(): mContext is NULL.");
//        }
//
//        //Log.d(TAG, "reportScore() end");
//    }

    /**
     * @brief     显示排行榜函数。
     * @author    赵一
     * @param[in] boardName 排行榜名称。
     */
//    public static void showLeaderBoard(String boardName) {
//        //Log.d(TAG, "showLeaderBoard() start");
//
//        if (mContext != null) {
//            Bundle bundle = new Bundle();
//            Intent intent = new Intent(Define.Action.ACTION);
//            bundle.putInt("TYPE", Define.MessageID.SHOW_LEADERBOARD);
//            bundle.putString("BOARDNAME", boardName);
//            intent.putExtras(bundle);
//            mContext.sendBroadcast(intent);
//        }
//        else {
//            Log.e(TAG, "showLeaderBoard(): mContext is NULL.");
//        }
//
//        //Log.d(TAG, "showLeaderBoard() end");
//    }

    /**
     * @brief     打开网页函数。
     * @author    赵一
     * @param[in] url 网页地址。
     */
//    public static void gotoUrl(String url) {
//        //Log.d(TAG, "gotoUrl() start");
//
//        if (mContext != null) {
//            Bundle bundle = new Bundle();
//            Intent intent = new Intent(Define.Action.ACTION);
//            bundle.putInt("TYPE", Define.MessageID.WEB_BROWSER);
//            bundle.putString("URL", url);
//            intent.putExtras(bundle);
//            mContext.sendBroadcast(intent);
//        }
//        else {
//            Log.e(TAG, "gotoUrl(): mContext is NULL.");
//        }
//
//        //Log.d(TAG, "gotoUrl() end");
//    }

    /**
     * @brief     Umeng取得在线参数函数。
     * @author    赵一
     * @param[in] name 参数键值。
     * @return    参数数值。
     */
    public static int getParamValue(String name) {
        return UmengSDK.getConfigIntParams(mContext, name, 0);
    }

    /**
     * @brief     Umeng自定义事件函数。
     * @author    赵一
     * @param[in] name  自定义事件键值。
     * @param[in] value 自定义事件数值。
     */
    public static void customEvent(String name, String value) {
    	  UmengSDK.customEvent(mContext, name, value);
    }
    
    /**
     * @brief  评价函数。
     * @author 赵一
     */
//    public static void gotoReview() {
//        //Log.d(TAG, "gotoReview() start");
//
//        if (mContext != null) {
//            Bundle bundle = new Bundle();
//            Intent intent = new Intent(Define.Action.ACTION);
//            bundle.putInt("TYPE", Define.MessageID.GOTO_REVIEW);
//            intent.putExtras(bundle);
//            mContext.sendBroadcast(intent);
//        }
//        else {
//            Log.e(TAG, "gotoReview(): mContext is NULL.");
//        }
//
//        //Log.d(TAG, "gotoReview() end");
//    }

    /**
     * @brief  初始化排行榜函数。
     * @author 赵一
     */
//    private void _initLeaderboards() {
//        //Log.d(TAG, "_initLeaderboards() start");
//
//        ScoreloopSDK.init(this, getScoreLoopSecretID());
//
//        //Log.d(TAG, "_initLeaderboards() end");
//    }

    /**
     * @brief  取得ScoreLoopID函数。
     * @author 赵一
     * @return ScoreLoopID。
     */
//    public static native String getScoreLoopSecretID();
    
    

    /**
     * @brief 上下文。
     */
    private static Context mContext = null;

    /**
     * @brief 日志标记。
     */
    private static final String TAG = "balloon";

}