/**
 * @file
 * @brief   共享配置参数存储类定义文件。
 * @author  赵一
 * @date    2012/11/06
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.store 数据读取与保存包。
 */
package com.happybluefin.android.framework.store;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.preference.PreferenceManager;
import android.util.Log;

/**
 * @class  SharePrefStore
 * @brief  共享配置参数存储类。
 * @author 赵一
 * @note   本类主要通过系统的共享配置参数累提供数据读取与保存。
 */
public class SharePrefStore {
    /**
     * @brief     取得整型数据函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] key     键值。
     * @param[in] def     默认数据。
     * @return    整型数据。
     */
    public static int getInt(final Context context, final String key, final int def) {
        //Log.d(TAG, "getInt() start");

        int result = def;

        if (context != null) {
            if (key != null) {
                try {
                    SharedPreferences shared = _getPreferences(context);
                    if (shared != null) {
                        result = shared.getInt(key, def);
                    }
                    else {
                        Log.e(TAG, "getInt(): shared is null.");
                    }
                }
                catch (Exception e) {
                    e.printStackTrace();
                }
            }
            else {
                Log.e(TAG, "getInt(): key is null.");
            }
        }
        else {
            Log.e(TAG, "getInt(): context is null.");
        }

        //Log.d(TAG, "getInt() end");

        return result;
    }

    /**
     * @brief     取得字符串数据函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] key     键值。
     * @param[in] def     默认数据。
     * @return    字符串数据。
     */
    public static String getString(final Context context, final String key, final String def) {
        //Log.d(TAG, "getString() start");

        String result = def;

        if (context != null) {
            if (key != null) {
                try {
                    SharedPreferences shared = _getPreferences(context);
                    if (shared != null) {
                        result = shared.getString(key, def);
                    }
                    else {
                        Log.e(TAG, "getString(): shared is null.");
                    }
                }
                catch (Exception e) {
                    e.printStackTrace();
                }
            }
            else {
                Log.e(TAG, "getString(): key is null.");
            }
        }
        else {
            Log.e(TAG, "getString(): context is null.");
        }

        //Log.d(TAG, "getString() end");

        return result;
    }

    /**
     * @brief     取得布尔数据函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] key     键值。
     * @param[in] def     默认数据。
     * @return    布尔数据。
     */
    public static boolean getBoolean(final Context context, final String key, final boolean def) {
        //Log.d(TAG, "getString() start");

        boolean result = def;

        if (context != null) {
            if (key != null) {
                try {
                    SharedPreferences shared = _getPreferences(context);
                    if (shared != null) {
                        result = shared.getBoolean(key, def);
                    }
                    else {
                        Log.e(TAG, "getString(): shared is null.");
                    }
                }
                catch (Exception e) {
                    e.printStackTrace();
                }
            }
            else {
                Log.e(TAG, "getString(): key is null.");
            }
        }
        else {
            Log.e(TAG, "getString(): context is null.");
        }

        //Log.d(TAG, "getString() end");

        return result;
    }

    /**
     * @brief     设置整型数据函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] key     键值。
     * @param[in] data    value。
     * @return    true    成功。
     * @return    false   失败。
     */
    public static boolean setInt(final Context context, String key, int value) {
        //Log.d(TAG, "setInt() start");

        boolean result = false;

        if (context != null) {
            if (key != null) {
                try {
                    SharedPreferences shared = _getPreferences(context);
                    if (shared != null) {
                        Editor editor = shared.edit();
                        if (editor != null) {
                            editor.putInt(key, value);
                            result = editor.commit();
                        }
                        else {
                            Log.e(TAG, "setInt(): editor is null.");
                        }
                    }
                    else {
                        Log.e(TAG, "setInt(): setInt is null.");
                    }
                }
                catch (Exception e) {
                    e.printStackTrace();
                    result = false;
                }
            }
            else {
                Log.e(TAG, "setInt(): key is null.");
            }
        }
        else {
            Log.e(TAG, "setInt(): context is null.");
        }

        //Log.d(TAG, "setInt() end");

        return result;
    }

    /**
     * @brief     设置字符串数据函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] key     键值。
     * @param[in] data    value。
     * @return    true    成功。
     * @return    false   失败。
     */
    public static boolean setString(final Context context, String key, String value) {
        //Log.d(TAG, "setString() start");

        boolean result = false;

        if (context != null) {
            if (key != null) {
                try {
                    SharedPreferences shared = _getPreferences(context);
                    if (shared != null) {
                        Editor editor = shared.edit();
                        if (editor != null) {
                            editor.putString(key, value);
                            result = editor.commit();
                        }
                        else {
                            Log.e(TAG, "setString(): editor is null.");
                        }
                    }
                    else {
                        Log.e(TAG, "setString(): setInt is null.");
                    }
                }
                catch (Exception e) {
                    e.printStackTrace();
                    result = false;
                }
            }
            else {
                Log.e(TAG, "setString(): key is null.");
            }
        }
        else {
            Log.e(TAG, "setString(): context is null.");
        }

        //Log.d(TAG, "setString() end");

        return result;
    }

    /**
     * @brief     设置布尔数据函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] key     键值。
     * @param[in] data    value。
     * @return    true    成功。
     * @return    false   失败。
     */
    public static boolean setBoolean(final Context context, String key, boolean value) {
        //Log.d(TAG, "setBoolean() start");

        boolean result = false;

        if (context != null) {
            if (key != null) {
                try {
                    SharedPreferences shared = _getPreferences(context);
                    if (shared != null) {
                        Editor editor = shared.edit();
                        if (editor != null) {
                            editor.putBoolean(key, value);
                            result = editor.commit();
                        }
                        else {
                            Log.e(TAG, "setBoolean(): editor is null.");
                        }
                    }
                    else {
                        Log.e(TAG, "setBoolean(): setInt is null.");
                    }
                }
                catch (Exception e) {
                    e.printStackTrace();
                    result = false;
                }
            }
            else {
                Log.e(TAG, "setBoolean(): key is null.");
            }
        }
        else {
            Log.e(TAG, "setBoolean(): context is null.");
        }

        //Log.d(TAG, "setInt() end");

        return result;
    }

    /**
     * @brief  取得默认共享存储实例函数。
     * @author 赵一
     * @return 默认共享存储实例。
     */
    private static SharedPreferences _getPreferences(final Context context) {
        //Log.d(TAG, "_getPreferences() start");

        SharedPreferences shared = null;

        if (context != null) {
            try {
                shared = PreferenceManager.getDefaultSharedPreferences(context);
            }
            catch (Exception e) {
                e.printStackTrace();
                shared = null;
            }
        }

        //Log.d(TAG, "_getPreferences() end");

        return shared;
    }

    /**
     * @brief 日志标记。
     */
    private final static String TAG = "SharePrefStore";
}
