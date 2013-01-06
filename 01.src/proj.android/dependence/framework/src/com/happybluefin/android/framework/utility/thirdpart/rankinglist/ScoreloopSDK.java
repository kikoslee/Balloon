/**
 * @file
 * @brief   Scoreloop UI类定义文件。
 * @author  赵一
 * @date    2012/11/06
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.utility.thirdpart.rankinglist 积分墙工具包。
 */
package com.happybluefin.android.framework.utility.thirdpart.rankinglist;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.scoreloop.client.android.core.controller.RequestController;
import com.scoreloop.client.android.core.controller.RequestControllerObserver;
import com.scoreloop.client.android.core.controller.ScoreController;
import com.scoreloop.client.android.core.model.Score;
import com.scoreloop.client.android.ui.LeaderboardsScreenActivity;
//import com.scoreloop.client.android.ui.OnScoreSubmitObserver;
import com.scoreloop.client.android.ui.ScoreloopManagerSingleton;

/**
 * @class  ScoreloopSDK
 * @brief  Scoreloop UI类。
 * @author 赵一
 */
public class ScoreloopSDK {
    /**
     * @brief     初始化函数。
     * @author    赵一
     * @param[in] context  上下文。
     * @param[in] secretID Scoreloop id。
     */
    public static void init(Context context, String secretID) {
        //Log.d(TAG, "init() start");

        ScoreloopManagerSingleton.init(context, secretID);

        //Log.d(TAG, "init() end");
    }

    /**
     * @brief  释放函数。
     * @author 赵一
     */
    public static void destory() {
        //Log.d(TAG, "destory() start");

        ScoreloopManagerSingleton.destroy();

        //Log.d(TAG, "destory() end");
    }

    /**
     * @brief     显示排行榜函数。
     * @author    赵一
     * @param[in] parent 父窗口。
     * @return    true   成功。
     * @return    false  失败。
     */
    public static boolean showLeaderboards(Activity parent) {
        //Log.d(TAG, "showLeaderboards() start");

        boolean result = false;
        if (parent != null) {
            try {
                parent.startActivity(new Intent(parent, LeaderboardsScreenActivity.class));
                result = true;
            }
            catch (ActivityNotFoundException e) {
                e.printStackTrace();
                result = false;
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "showLeaderboards(): parent is null.");
        }

        //Log.d(TAG, "showLeaderboards() end");
        return result;
    }

    /**
     * @brief     提交分数函数。
     * @author    赵一
     * @param[in] value 分值。
     * @return    true  成功。
     * @return    false 失败。
     */
    public static boolean submit(Double value) {
        //Log.d(TAG, "submit() start");

        boolean result = false;
/*
        ScoreloopManagerSingleton.get().setOnScoreSubmitObserver(new OnScoreSubmitObserver() {
            public void onScoreSubmit(int status, Exception error) {
            }
        });
        ScoreloopManagerSingleton.get().onGamePlayEnded(value, null);
*/
        //The Score to be submitted
        final Score score = new Score(value, null);

        //Other code will go here
        //...
        
        RequestControllerObserver requiestControllerObserver = new RequestControllerObserver() {
            public void requestControllerDidFail(RequestController arg0, Exception arg1) {
                //TODO: 提交失败
            }

            public void requestControllerDidReceiveResponse(RequestController arg0) {
                //TODO: 提交成功
            }
        };

        //Create the ScoreController instance
        final ScoreController myScoreController = new ScoreController(requiestControllerObserver);

        //Use the controller to submit to the server
        myScoreController.submitScore(score);

        //Log.d(TAG, "submit() end");

        return result;
    }

    /**
     * @brief 日志标记。
     */
    private final static String TAG = "ScoreloopSDK";
}
