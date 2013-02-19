/**
 * @brief   加载窗口类定义文件。
 * @author  赵一
 * @date    2012/01/07
 * @version 0.1
 */

package com.happybluefin.galaxyinvader;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ImageView;
import android.view.View;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.util.Log;

import com.google.analytics.tracking.android.EasyTracker;
import com.happybluefin.android.framework.store.SharePrefStore;
import com.happybluefin.android.framework.utility.system.Desktop;
import com.happybluefin.android.framework.window.WindowManager;

/**
 * @brief  加载窗口类。
 * @author 赵一
 * @note   提供复选列表对话框的显示与关闭处理。
 */
public class LogoWindow extends Activity {
    /**
     * @brief     窗口建立函数。
     * @param[in] savedInstanceState 保存状态。
     */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Log.d(TAG, "onCreate() start");

        //建立桌面快捷方式
        _addSesktopShortcut();

        //初始化控件
        _initView();

        //Log.d(TAG, "onCreate() end");
    }
	
	@Override
	public void onStart() {
	    super.onStart();
	    EasyTracker.getInstance().activityStart(this); // Add this method.
	}

	@Override
	public void onStop() {
	    super.onStop();
	    EasyTracker.getInstance().activityStop(this); // Add this method.
	}	

    /**
     * @brief  初始化控件函数。
     */
    private void _initView() {
        //Log.d(TAG, "_initView() start");

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

//        _startGameWindow();
        //Log.d(TAG, "_initView() end");
    }

    /**
     * @brief  启动游戏窗口函数。
     */
    private void _startGameWindow() {
        //Log.d(TAG, "_startTapBurstFreeWindow() start");

        //打开游戏窗口
        if (WindowManager.startWindow(this, GameWindow.class) != true) {
            Log.e(TAG, "_startMainWindow(): start GameWindow failed!");
        }

        //关闭加载窗口
        if (WindowManager.closeWindow(this) != true) {
            Log.e(TAG, "_startMainWindow(): close LogoWindow failed!");
        }

        //Log.d(TAG, "_startMainWindow() end");
    }

    /**
     * @brief  添加快捷方式函数。
     */
    private void _addSesktopShortcut() {
        //Log.d(TAG, "_addSesktopShortcut() start");

        //建立桌面快捷方式
        boolean flag = SharePrefStore.getBoolean(this, IS_FIRST_START_FLAG, false);
        if (flag != true) {
            //第一次进入游戏建立快捷方式
            if (Desktop.addShortcut(this,
                                    getString(R.string.app_name),
                                    LogoWindow.class,
                                    R.drawable.icon) != true) {
                Log.e(TAG, "_addSesktopShortcut(): add shortcut failed!");
            }
            SharePrefStore.setBoolean(this, IS_FIRST_START_FLAG, true);
        }

        //Log.d(TAG, "_addSesktopShortcut() end");
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
     * @brief 是否第一次进入游戏的数值判断键值。
     */
    private static final String IS_FIRST_START_FLAG = "IsFirstStartFlag";

    /**
     * @brief 动画时间长度。
     */
    private static final int ANIM_TIME = 1500;

    /**
     * @brief 日志标记。
     */
    private static final String TAG = "LogoWindow";
}
