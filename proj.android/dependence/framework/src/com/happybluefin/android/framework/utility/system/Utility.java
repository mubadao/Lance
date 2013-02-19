/**
 * @file
 * @brief   工具类定义文件。
 * @author  赵一
 * @date    2012/11/06
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.utility.system 系统工具包。
 */
package com.happybluefin.android.framework.utility.system;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.telephony.TelephonyManager;
import android.util.Log;

/**
 * @class  Utility
 * @brief  工具类。
 * @author 赵一
 */
public class Utility {
    /**
     * @brief     取得应用列表函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] effect  音效id(使用AudioManager类中的音效ID定义)。
     * @param[in] volume  音效音量。
     * @return    应用列表。
     */
    public static ArrayList<PackInfo> getApplicationList(final Context context) {
        //Log.d(TAG, "getApplicationList() start");

        ArrayList<PackInfo> list = null;

        if (context != null) {
            try {
                list = new ArrayList<PackInfo>();

                //得到PackageManager对象
                PackageManager pm = context.getPackageManager();
                //得到系统安装的所有程序包的PackageInfo对象
//                List<PackageInfo> packs = pm.getInstalledPackages(0);
                List<PackageInfo> packs = pm.getInstalledPackages(PackageManager.GET_ACTIVITIES);
                for(PackageInfo pack:packs) {
                    PackInfo info = new PackInfo();
                    info.icon = pack.applicationInfo.loadIcon(pm);
                    info.lable = pack.applicationInfo.loadLabel(pm).toString();
                    info.packageName = pack.applicationInfo.packageName;
                    info.description = pack.applicationInfo.loadDescription(pm).toString();

                    list.add(info);
                }
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            Log.e(TAG, "getApplicationList(): context is null.");
        }

        //Log.d(TAG, "getApplicationList() end");

        return list;
    }

    /**
     * @brief     启动浏览器处理函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] url     网址名称。
     * @return    true    成功。
     * @return    false   失败。
     */
    public static boolean startBrowser(final Context context, final String url) {
        //Log.d(TAG, "startBrowser() start");

        boolean result = false;

        if (context != null) {
            if (url != null) {
                try {
                    Uri uri = Uri.parse(url);
                    Intent intent = new Intent(Intent.ACTION_VIEW, uri);
                    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    context.startActivity(intent);

                    result = true;
                }
                catch (NullPointerException e) {
                    e.printStackTrace();
                    result = false;
                }
                catch (ActivityNotFoundException e) {
                    e.printStackTrace();
                    result = false;
                }
            }
            else {
                Log.e(TAG, "startBrowser(): url is null.");
            }
        }
        else {
            Log.e(TAG, "startBrowser(): context is null.");
        }

        //Log.d(TAG, "startBrowser() end");

        return result;
    }

    /**
     * @brief     启动apk函数。
     * @author    赵一
     * @param[in] parent      父窗口。
     * @param[in] packageName 目标apk的包名称。
     * @param[in] anmi        动画标志。
     * @return    true        成功。
     * @return    false       失败。
     */
    public static boolean startApk(final Activity parent, final String packageName, final boolean anmi) {
        //Log.d(TAG, "startApk() start");

        boolean result = false;

        if (parent != null) {
            try {
                PackageManager pm = parent.getApplicationContext().getPackageManager();
                Intent intent = pm.getLaunchIntentForPackage(packageName);
                if (intent != null) {
                    parent.startActivity(intent);
                    if (anmi == false) {
                        parent.overridePendingTransition(0, 0);
                    }

                    result = true;
                }
                else {
                    Log.e(TAG, "startApk(): intent is null.");
                }
            }
            catch (ActivityNotFoundException e) {
                e.printStackTrace();
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            Log.e(TAG, "startApk(): parent is null.");
        }

        //Log.d(TAG, "startApk() end");

        return result;
    }

    /**
     * @brief     启动apk函数。
     * @author    赵一
     * @param[in] parent      父窗口。
     * @param[in] packageName 目标apk的包名称。
     * @param[in] packageName 目标apk的启动窗口名称。
     * @param[in] anmi        动画标志。
     * @return    true        成功。
     * @return    false       失败。
     */
    public static boolean startApk(final Activity parent, final String packageName, final String windowName, final boolean anmi) {
        //Log.d(TAG, "startApk() start");

        boolean result = false;

        try {
            Intent intent = new Intent();
            intent.setComponent(new ComponentName(packageName, windowName));
            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            parent.startActivityForResult(intent, 0);
            if (anmi == false) {
                parent.overridePendingTransition(0, 0);
            }

            result = true;
        }
        catch (ActivityNotFoundException e) {
            e.printStackTrace();
        }
        catch (Exception e) {
            e.printStackTrace();
            result = false;
        }

        //Log.d(TAG, "startApk() end");

        return result;
    }

    /**
     * @brief     取得设备ID标识函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @return    设备ID标识。
     */
    public static String getDeviceId(final Context context) {
        //Log.d(TAG, "getDeviceId() start");

        String deviceId = null;

        if (context != null) {
            try {
                TelephonyManager tm = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
                deviceId = tm.getDeviceId();
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            Log.e(TAG, "getDeviceId(): context is null.");
        }

        //Log.d(TAG, "getDeviceId() end");

        return deviceId;
    }

    /**
     * @brief     执行Linux命令行函数。
     * @author    赵一
     * @param[in] cmd 命令行。
     * @return    输出结果。
     */
    public static InputStream executeCommand(final String cmd) {
        Log.e(TAG, "executeCommand() start");

        InputStream result = null;

        try {
            Process process = Runtime.getRuntime().exec(cmd);
            int status = process.waitFor();
            if (status == 0) {
                //成功
                result = process.getInputStream();
            }
            else {
                //失败
                result = process.getErrorStream();
                Log.e(TAG, "executeCommand(): process.waitFor() result: " + status);
            }
        }
        catch (IOException e) {
            e.printStackTrace();
            result = null;
        }
        catch (InterruptedException e) {
            e.printStackTrace();
            result = null;
        }

        Log.e(TAG, "executeCommand() end");

        return result;
    }
    
    /**
     * @class  PackInfo
     * @brief  应用包信息类。
     * @author 赵一
     */
    public static class PackInfo {
        /**
         * @brief 应用的标题。
         */
        public String lable = null;

        /**
         * @brief 应用包的名称。
         */
        public String packageName = null;

        /**
         * @brief 应用的详情。
         */
        public String description = null;

        /**
         * @brief 应用的图标。
         */
        public Drawable icon = null;
    }

    /**
     * @brief 日志标记。
     */
    private final static String TAG = "Utility";
}
