/**
 * @file
 * @brief   电源类定义文件。
 * @author  赵一
 * @date    2012/12/06
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.utility.system 系统工具包。
 */
package com.happybluefin.android.framework.utility.system;

import android.content.Context;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.Log;

/**
 * @class  Power
 * @brief  电源类。
 * @author 赵一
 */
public class Power {
    /**
     * @brief     启动唤醒锁定处理函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] tag     唤醒锁的标签。
     * @return    唤醒锁。
     */
    public static WakeLock startWakeLock(final Context context, final String tag) {
        //Log.d(TAG, "startWakeLock() start");

        WakeLock wakeLock = null;

        if (context != null) {
            try {
                PowerManager pm = (PowerManager)context.getSystemService(Context.POWER_SERVICE);
                Log.d(TAG, "PowerManager acquired");
                wakeLock = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, tag);
                wakeLock.acquire();
            }
            catch (Exception e) {
                e.printStackTrace();
                wakeLock = null;
            }
        }
        else {
            Log.e(TAG, "startWakeLock(): context is null.");
        }

        //Log.d(TAG, "startWakeLock() end");

        return wakeLock;
    }

    /**
     * @brief     关闭唤醒锁定处理函数。
     * @author    赵一
     * @param[in] wakeLock 唤醒锁。
     * @return    true     成功。
     * @return    false    失败。
     */
    public static boolean stopWakeLock(WakeLock wakeLock) {
        //Log.d(TAG, "stopWakeLock() start");

        boolean result = false;

        if (wakeLock != null) {
            try {
                wakeLock.release();
                result = true;
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "stopWakeLock(): wakeLock is null.");
        }

        //Log.d(TAG, "stopWakeLock() end");

        return result;
    }

    /**
     * @brief 日志标记。
     */
    private static final String TAG = "Power";
}
