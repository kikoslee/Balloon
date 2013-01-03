package com.happybluefin.balloon;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ImageView;
import android.view.View;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.util.Log;

import com.happybluefin.android.framework.window.WindowManager;

public class LogoWindow extends Activity {
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //初始化控件
        _initView();
    }

    private void _initView() {
        //加载窗口布局
        setContentView(R.layout.logowindow);

        //加载图标控件
        mImageViewLogo = (ImageView)findViewById(R.id.imageViewLogo);

        //设置图标显示动画
        mAnimAlphaShow.setDuration(ANIM_TIME);
        mAnimAlphaShow.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationEnd(Animation animation) {
                mImageViewLogo.startAnimation(mAnimAlphaHide);
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationStart(Animation animation) {
            }
        });

        //设置图标隐藏动画
        mAnimAlphaHide.setDuration(ANIM_TIME);
        mAnimAlphaHide.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationEnd(Animation animation) {
            	mImageViewLogo.setVisibility(View.INVISIBLE);
                _startGameWindow();
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationStart(Animation animation) {
            }
        });

        //启动动画
        mImageViewLogo.startAnimation(mAnimAlphaShow);
    }

    private void _startGameWindow() {
        //打开游戏窗口
        if (WindowManager.startWindow(this, GameWindow.class) != true) {
            Log.e(TAG, "_startMainWindow(): start GameWindow failed!");
        }

        //关闭加载窗口
        if (WindowManager.closeWindow(this) != true) {
            Log.e(TAG, "_startMainWindow(): close LogoWindow failed!");
        }
    }

    /**
     * @brief Logo图标控件。
     */
    private ImageView mImageViewLogo = null;

    /**
     * @brief Logo图标显示动画。
     */
    private AlphaAnimation mAnimAlphaShow = new AlphaAnimation(0.0f, 1.0f);

    /**
     * @brief Logo图标隐藏动画。
     */
    private AlphaAnimation mAnimAlphaHide = new AlphaAnimation(1.0f, 0.0f);

    /**
     * @brief 动画时间长度。
     */
    private static final int ANIM_TIME = 1500;

    /**
     * @brief 日志标记。
     */
    private static final String TAG = "LogoWindow";
}
