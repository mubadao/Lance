/**
 * @file
 * @brief   窗口管理器类定义文件。
 * @author  赵一
 * @date    2012/11/06
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.window 窗口工具包。
 */
package com.happybluefin.android.framework.window;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.util.Log;

/**
 * @class  WindowManager
 * @brief  窗口管理器类。
 * @author 赵一
 */
public class WindowManager {
    /**
     * @brief     启动窗口处理函数。
     * @author    赵一
     * @param[in] window 启动源窗口实例。
     * @param[in] cls    启动目标窗口类。
     * @return    true   成功。
     * @return    false  失败。
     */
    public static boolean startWindow(Activity window, Class<?> cls) {
        //Log.d(TAG, "startWindow(): start");

        boolean result = false;

        if ((window != null) && (cls != null)) {
            try {
                Intent intent = new Intent(window, cls);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                window.startActivity(intent);

                result = true;
            }
            catch (ActivityNotFoundException e) {
                e.printStackTrace();
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            Log.e(TAG, "startWindow(): window or cls is null.");
        }

        //Log.d(TAG, "startWindow(): end");

        return result;
    }

    /**
     * @brief     启动窗口处理函数。
     * @author    赵一
     * @param[in] window    启动源窗口实例。
     * @param[in] cls       启动目标窗口类。
     * @param[in] enterAnim 进入动画。
     * @param[in] exitAnim  退出动画。
     * @return    true      成功。
     * @return    false     失败。
     */
    public static boolean startWindow(Activity window, Class<?> cls, int enterAnim, int exitAnim) {
        //Log.d(TAG, "startWindow(): start");

        boolean result = false;

        if ((window != null) && (cls != null)) {
            try {
                Intent intent = new Intent(window, cls);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                window.startActivity(intent);
                window.overridePendingTransition(enterAnim, exitAnim);

                result = true;
            }
            catch (ActivityNotFoundException e) {
                e.printStackTrace();
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            Log.e(TAG, "startWindow(): window or cls is null.");
        }

        //Log.d(TAG, "startWindow(): end");

        return result;
    }

    /**
     * @brief     关闭窗口处理函数。
     * @author    赵一
     * @param[in] window 关闭源窗口实例。
     * @return    true   成功。
     * @return    false  失败。
     */
    public static boolean closeWindow(Activity window) {
        //Log.d(TAG, "closeWindow(): start");

        boolean result = false;

        if (window != null) {
            try {
                window.finish();

                result = true;
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            Log.e(TAG, "closeWindow(): window is null.");
        }

        //Log.d(TAG, "closeWindow(): end");

        return result;
    }

    /**
     * @brief     关闭窗口处理函数。
     * @author    赵一
     * @param[in] window    关闭源窗口实例。
     * @param[in] enterAnim 进入动画。
     * @param[in] exitAnim  退出动画。
     * @return    true      成功。
     * @return    false     失败。
     */
    public static boolean closeWindow(Activity window, int enterAnim, int exitAnim) {
        //Log.d(TAG, "closeWindow(): start");

        boolean result = false;

        if (window != null) {
            try {
                window.finish();
                window.overridePendingTransition(enterAnim, exitAnim);

                result = true;
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            Log.e(TAG, "closeWindow(): window is null.");
        }

        //Log.d(TAG, "closeWindow(): end");

        return result;
    }

    /**
     * @brief 日志标记。
     */
    private final static String TAG = "WindowManager";
}
