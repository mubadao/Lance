/**
 * @file
 * @brief   桌面类定义文件。
 * @author  赵一
 * @date    2012/10/29
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.utility.system 系统工具包。
 */
package com.happybluefin.android.framework.utility.system;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import android.app.WallpaperManager;
import android.content.Context;
import android.content.Intent;
import android.content.Intent.ShortcutIconResource;
import android.graphics.Bitmap;
import android.util.Log;
import android.view.View;

/**
 * @class  Desktop
 * @brief  桌面类。
 * @author 赵一
 */
public class Desktop {
    /**
     * @brief     设置桌面背景函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] path    背景图路径。
     * @return    true    成功。
     * @return    false   失败。
     */ 
    public static boolean setBackground(final Context context, final String path) {
        //Log.d(TAG, "setBackground() start");

        boolean result = false;

        if (context != null) {
            try {
                //读取文件
                File file = new File(path);
                InputStream data = new FileInputStream(file);

                //设置背景
                WallpaperManager wallpaperManager = WallpaperManager.getInstance(context);
                wallpaperManager.setStream(data);

                result = true;
            }
            catch (FileNotFoundException e) {
                e.printStackTrace();
                result = false;
            }
            catch (IOException e) {
                e.printStackTrace();
                result = false;
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "setBackground(): context is null.");
        }

        //Log.d(TAG, "setBackground() end");

        return result;
    }

    /**
     * @brief     设置桌面背景函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] data    背景图数据。
     * @return    true    成功。
     * @return    false   失败。
     */ 
    public static boolean setBackground(final Context context, final InputStream data) {
        //Log.d(TAG, "setBackground() start");

        boolean result = false;

        if (context != null) {
            try {
                //设置背景
                WallpaperManager wallpaperManager = WallpaperManager.getInstance(context);
                wallpaperManager.setStream(data);

                result = true;
            }
            catch (IOException e) {
                e.printStackTrace();
                result = false;
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "setBackground(): context is null.");
        }

        //Log.d(TAG, "setBackground() end");

        return result;
    }

    /**
     * @brief     设置桌面背景函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] data    背景图数据。
     * @return    true    成功。
     * @return    false   失败。
     */ 
    public static boolean setBackground(final Context context, final Bitmap data) {
        //Log.d(TAG, "setBackground() start");

        boolean result = false;

        if (context != null) {
            try {
                //设置背景
                WallpaperManager wallpaperManager = WallpaperManager.getInstance(context);
                wallpaperManager.setBitmap(data);

                result = true;
            }
            catch (IOException e) {
                e.printStackTrace();
                result = false;
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "setBackground(): context is null.");
        }

        //Log.d(TAG, "setBackground() end");

        return result;
    }

    /**
     * @brief     追加桌面快捷方式函数。
     * @author    赵一
     * @param[in] context  上下文。
     * @param[in] name     快捷方式名称。
     * @param[in] startCls 快捷方式图标所对应的启动窗口类。
     * @param[in] iconRes  快捷方式图标资源ID。
     * @return    true     成功。
     * @return    false    失败。
     */ 
    public static boolean addShortcut(final Context context, final String name, final Class<?> startCls, final int iconRes) {
        //Log.d(TAG, "addShortcut() start");

        boolean result = false;

        if ((context != null) && (name != null) && (startCls != null)) {
            try {
                Intent shortcut = new Intent("com.android.launcher.action.INSTALL_SHORTCUT");

                Intent intent = new Intent();
                intent.setClass(context, startCls);
                intent.setAction("android.intent.action.MAIN");
                intent.addCategory("android.intent.category.LAUNCHER");

                //设置快捷名称
                shortcut.putExtra(Intent.EXTRA_SHORTCUT_NAME, name);
                //
                shortcut.putExtra("duplicate", false);
                //设置快捷入口
                shortcut.putExtra(Intent.EXTRA_SHORTCUT_INTENT, intent);
                //设置快捷图标
                ShortcutIconResource icon = Intent.ShortcutIconResource.fromContext(context, iconRes);
                shortcut.putExtra(Intent.EXTRA_SHORTCUT_ICON_RESOURCE, icon);

                context.sendBroadcast(shortcut);

                result = true;
            }
            catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        else {
            Log.e(TAG, "addShortcut(): context is null.");
        }

        //Log.d(TAG, "addShortcut() end");

        return result;
    }

    /**
     * @brief     截屏处理函数。
     * @author    赵一
     * @param[in] view 所要截取的图像view。
     * @return    截取的屏幕图像。
     */
    public static Bitmap screenShot(final View view) {
        //Log.d(TAG, "screenShot() start");

        Bitmap bitmap = null;
        
        if (view != null) {
            try {
                View root = view.getRootView();
                root.setDrawingCacheEnabled(true);
                root.buildDrawingCache();
                bitmap = root.getDrawingCache();
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            Log.e(TAG, "screenShot(): view is null.");
        }

        //Log.d(TAG, "screenShot() end");

        return bitmap;
    }

    /**
     * @brief 日志标记。
     */
    private final static String TAG = "Desktop";
}
