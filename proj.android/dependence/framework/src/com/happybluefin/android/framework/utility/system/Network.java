/**
 * @file
 * @brief   网络类定义文件。
 * @author  赵一
 * @date    2012/10/29
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.utility.system 系统工具包。
 */
package com.happybluefin.android.framework.utility.system;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;

/**
 * @class  Network
 * @brief  网络类。
 * @author 赵一
 */
public class Network {
    /**
     * @brief  取得网络连接状态函数。
     * @author 赵一
     * @return true  已连接。
     * @return false 非已连接。
     */
    public static boolean getConnectivityState(final Context context) {
        //Log.d(TAG, "getConnectivityState() start");

        boolean result = false;

        if (context != null) {
            try {
                //获取系统的连接服务
                ConnectivityManager mgr = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);

                //获取网络信息
                NetworkInfo info = mgr.getActiveNetworkInfo();
                if (info != null) {
                    NetworkInfo.State state = info.getState();
                    if (state == NetworkInfo.State.CONNECTED) {
                        //已经连接
                        result = true;
                    }
                    else if (state == NetworkInfo.State.CONNECTING) {
                        //正在连接
                    }
                    else if (state == NetworkInfo.State.DISCONNECTED) {
                        //已断开
                    }
                    else if (state == NetworkInfo.State.DISCONNECTING) {
                        //正在断开
                    }
                    else if (state == NetworkInfo.State.SUSPENDED) {
                        //
                    }
                    else if (state == NetworkInfo.State.UNKNOWN) {
                        //未知
                    }
                    else {
                        //未知
                    }
                }
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "getConnectivityState(): connect is null.");
        }

        //Log.d(TAG, "getConnectivityState() end");

        return result;
    }

    /**
     * @brief     判断当前网络是否是wifi网络函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @return    true    是wifi网络。
     * @return    false   不是wifi网络。
     */
    public static boolean isWifiNetwork(final Context context) {
        boolean result = false;

        //Log.d(TAG, "isWifiNetwork() start");

        if (context != null) {
            try {
                //获取系统的连接服务
                ConnectivityManager mgr = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);

                //获取网络信息
                NetworkInfo info = mgr.getActiveNetworkInfo();
                if (info != null) {
                    if (info.getType() == ConnectivityManager.TYPE_WIFI) {
                        result = true;
                    }
                }
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "isWifiNetwork(): context is null.");
        }

        //Log.d(TAG, "isWifiNetwork() end");

        return result;
    }

    /**
     * @brief     判断当前网络是否是有线网络函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @return    true    是有线网络。
     * @return    false   不是有线网络。
     */
    public static boolean isEthernetNetwork(final Context context) {
        boolean result = false;

        //Log.d(TAG, "isEthernetNetwork() start");

        if (context != null) {
            try {
                //获取系统的连接服务
                ConnectivityManager mgr = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);

                //获取网络信息
                NetworkInfo info = mgr.getActiveNetworkInfo();
                if (info != null) {
                    if (info.getType() == ConnectivityManager.TYPE_ETHERNET) {
                        result = true;
                    }
                }
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "isEthernetNetwork(): context is null.");
        }

        //Log.d(TAG, "isEthernetNetwork() end");

        return result;
    }

    /**
     * @brief 日志标记。
     */
    private final static String TAG = "Network";
}
