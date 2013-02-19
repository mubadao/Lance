/**
 * @file
 * @brief   提交评价类定义文件。
 * @author  赵一
 * @date    2012/11/06
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.utility.system 系统工具包。
 */
package com.happybluefin.android.framework.utility.system;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

/**
 * @class  Comment
 * @brief  提交评价类。
 * @author 赵一
 */
public class Comment {
    /**
     * @brief     启动Google Play评价窗口函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] name    应用在Google Play中的名称。
     * @return    true    成功。
     * @return    false   失败。
     */
    public static boolean startGooglePlayComment(final Context context, final String name) {
        //Log.d(TAG, "startGooglePlayComment() start");

        boolean result = false;

        if (context != null) {
            try {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("market://details?id=" + name));
                if (_startWindow(context, intent) != true) {
                    intent.setData(Uri.parse("https://play.google.com/store/apps/details?id=" + name));
                    if (_startWindow(context, intent) != true) {
                        Log.e(TAG, "startGooglePlayHappyBluefinComment(): _startWindow() error");
                    }
                    else {
                        result = true;
                    }
                }
                else {
                    result = true;
                }
            }
            catch (NullPointerException e) {
                e.printStackTrace();
                result = false;
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "startGooglePlayComment(): context is null.");
        }

        //Log.d(TAG, "startGooglePlayComment() end");

        return result;
    }

    /**
     * @brief     启动Google Play的HappyBluefin的更多游戏窗口函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @return    true    成功。
     * @return    false   失败。
     */
    public static boolean gotoMoreGame(final Activity window) {
        //Log.d(TAG, "gotoMoreGame() start");

        boolean result = false;

        if (window != null) {
            try {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("market://search?q=pub:HappyBluefin"));
                if (_startWindowByActivity(window, intent) != true) {
                    intent.setData(Uri.parse("http://play.google.com/store/search?q=pub:HappyBluefin"));
                    if (_startWindowByActivity(window, intent) != true) {
                        Log.e(TAG, "gotoMoreGame(): _startWindow() error");
                    }
                    else {
                        result = true;
                    }
                }
                else {
                    result = true;
                }
            }
            catch (NullPointerException e) {
                e.printStackTrace();
                result = false;
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "gotoMoreGame(): context is null.");
        }

        //Log.d(TAG, "gotoMoreGame() end");

        return result;
    }

    /**
     * @brief     启动启动窗口函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] name    应用在Google Play中的名称。
     * @return    true    成功。
     * @return    false   失败。
     */
    private static boolean _startWindow(final Context context, final Intent intent) {
        //Log.d(TAG, "_startWindow() start");

        boolean result = false;

        if (context != null) {
            try {
                context.startActivity(intent);
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
            Log.e(TAG, "_startWindow(): context is null.");
        }

        //Log.d(TAG, "_startWindow() end");

        return result;
    }

    /**
     * @brief     启动启动窗口函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] name    应用在Google Play中的名称。
     * @return    true    成功。
     * @return    false   失败。
     */
    private static boolean _startWindowByActivity(final Activity window, final Intent intent) {
        //Log.d(TAG, "_startWindow() start");

        boolean result = false;

        if (window != null) {
            try {
            	window.startActivityForResult(intent, 1);
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
            Log.e(TAG, "_startWindow(): context is null.");
        }

        //Log.d(TAG, "_startWindow() end");

        return result;
    }

    /**
     * @brief 日志标记。
     */
    private static String TAG = "Comment";
}
