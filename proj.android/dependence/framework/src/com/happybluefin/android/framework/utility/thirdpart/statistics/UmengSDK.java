/**
 * @file
 * @brief   友盟SDK类定义文件。
 * @author  赵一
 * @date    2012/10/26
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.utility.thirdpart.statistics 统计定义包。
 */
package com.happybluefin.android.framework.utility.thirdpart.statistics;

import com.umeng.analytics.MobclickAgent;
import com.umeng.update.UmengUpdateAgent;

import android.content.Context;
import android.util.Log;

/**
 * @class  UmengSDK
 * @brief  友盟SDK类。
 * @author 赵一
 */
public class UmengSDK {
    /**
     * @brief     自动更新函数。
     * @author    赵一
     * @param[in] context 上下文。
     */
    public static void autoUpdate(Context context) {
        //Log.d(TAG, "autoUpdate() start");

        if (context != null) {
            UmengUpdateAgent.update(context);
        }
        else {
            Log.e(TAG, "customEvent(): context is null.");
        }

        //Log.d(TAG, "autoUpdate() end");
    }

    /**
     * @brief     自动发送错误报告函数。
     * @author    赵一
     * @param[in] context 上下文。
     */
    public static void autoErrorReport(Context context) {
        //Log.d(TAG, "autoErrorReport() start");

        if (context != null) {
            MobclickAgent.onError(context);
        }
        else {
            Log.e(TAG, "customEvent(): context is null.");
        }

        //Log.d(TAG, "autoErrorReport() end");
    }

    /**
     * @brief     手动发送错误报告函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] error   错误文本。
     */
    public static void manualErrorReport(Context context, String error) {
        //Log.d(TAG, "manualErrorReport() start");

        if (context != null) {
            if (error != null) {
                MobclickAgent.reportError(context, error);
            }
            else {
                Log.e(TAG, "customEvent(): error is null.");
            }
        }
        else {
            Log.e(TAG, "customEvent(): context is null.");
        }

        //Log.d(TAG, "manualErrorReport() end");
    }

    /**
     * @brief     在线参数配置函数。
     * @author    赵一
     * @param[in] context 上下文。
     */
    public static void updateOnlineConfig(Context context) {
        //Log.d(TAG, "updateOnlineConfig() start");

        if (context != null) {
            MobclickAgent.updateOnlineConfig(context);
        }
        else {
            Log.e(TAG, "updateOnlineConfig(): context is null.");
        }

        //Log.d(TAG, "updateOnlineConfig() end");
    }

    /**
     * @brief     取得在线参数配置函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] context 上下文。
     * @return    在线参数数据内容。
     */
    public static String getConfigStringParams(Context context, String key, String defValue) {
        //Log.d(TAG, "getConfigStringParams() start");

        String value = defValue;

        if (context != null) {
            if (key != null) {
                try {
                    value = MobclickAgent.getConfigParams(context, key);
                }
                catch (Exception e) {
                    e.printStackTrace();
                    value = defValue;
                }
            }
            else {
                Log.e(TAG, "getConfigStringParams(): key is null.");
            }
        }
        else {
            Log.e(TAG, "getConfigStringParams(): context is null.");
        }

        //Log.d(TAG, "getConfigStringParams() end");

        return value;
    }

    /**
     * @brief     取得在线参数配置函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] context 上下文。
     * @return    在线参数数据内容。
     */
    public static int getConfigIntParams(Context context, String key, int defValue) {
        //Log.d(TAG, "getConfigIntParams() start");

        int value = defValue;

        if (context != null) {
            if (key != null) {
                try {
                    String param = MobclickAgent.getConfigParams(context, key);
                    value = Integer.parseInt(param);
                }
                catch (Exception e) {
                    e.printStackTrace();
                    value = defValue;
                }
            }
            else {
                Log.e(TAG, "getConfigIntParams(): key is null.");
            }
        }
        else {
            Log.e(TAG, "getConfigIntParams(): context is null.");
        }

        //Log.d(TAG, "getConfigIntParams() end");

        return value;
    }

    /**
     * @brief     umeng sdk 重新开始函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @note      调用源的activity中的onResume函数中调用该方法。
     */
    public static void onResume(Context context) {
        //Log.d(TAG, "onResume() start");

        if (context != null) {
            MobclickAgent.onResume(context);
        }
        else {
            Log.e(TAG, "onResume(): context is null.");
        }

        //Log.d(TAG, "onResume() end");
    }

    /**
     * @brief     umeng sdk 暂停函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @note      调用源的activity中的onPause函数中调用该方法。
     */
    public static void onPause(Context context) {
        //Log.d(TAG, "onPause() start");

        if (context != null) {
            MobclickAgent.onPause(context);
        }
        else {
            Log.e(TAG, "onPause(): context is null.");
        }

        //Log.d(TAG, "onPause() end");
    }

    /**
     * @brief     umeng自定义事件函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] name    事件名称。
     * @param[in] event   事件名称。
     */
    public static void customEvent(Context context, String name, String event) {
        //Log.d(TAG, "customEvent() start");

        if (context != null) {
            MobclickAgent.onEvent(context, name, event);
        }
        else {
            Log.e(TAG, "customEvent(): context is null.");
        }

        //Log.d(TAG, "customEvent() end");
    }

    /**
     * @brief     umeng自定义事件函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] event   事件名称。
     */
    public static void customEvent(Context context, String event) {
        //Log.d(TAG, "customEvent() start");

        if (context != null) {
            MobclickAgent.onEvent(context, event);
        }
        else {
            Log.e(TAG, "customEvent(): context is null.");
        }

        //Log.d(TAG, "customEvent() end");
    }

    /**
     * @brief 日志
     */
    private static final String TAG = "UmengSDK";
}
