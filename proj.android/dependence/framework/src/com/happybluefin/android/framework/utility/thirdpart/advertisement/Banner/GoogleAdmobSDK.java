/**
 * @file
 * @brief   Google Admob广告类定义文件。
 * @author  赵一
 * @date    2012/11/06
 * @version 0.1
 */

/**
 * @package com.happybluefin.android.utility.thirdpart.advertisement.Banner 横幅广告工具包。
 */
package com.happybluefin.android.framework.utility.thirdpart.advertisement.Banner;

import android.app.Activity;
import android.util.Log;
import android.widget.FrameLayout;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

/**
 * @class  GoogleAdmobSDK
 * @brief  Google Admob广告类。
 * @author 赵一
 */
public class GoogleAdmobSDK {
    /**
     * @brief     建立横幅广告函数。
     * @author    赵一
     * @param[in] context 上下文。
     * @param[in] uid     广告id。
     * @param[in] pos     广告位置。(参照Gravity.TOP、Gravity.BOTTOM、Gravity.LEFT、Gravity.RIGHT)
     * @return    true    成功。
     * @return    false   失败。
     */
    public static boolean createBanner(Activity parent, final String uid, final int pos) {
        //Log.d(TAG, "createBanner() start");

        boolean result = false;

        if (parent != null) {
            if (uid != null) {
                mBannerAdView = new AdView(parent, AdSize.BANNER, uid);

                FrameLayout framelayout = (FrameLayout)parent.getWindow().getDecorView();
                
                FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                                                                               FrameLayout.LayoutParams.WRAP_CONTENT);                
                params.topMargin = 0;
                params.leftMargin = 0;
                params.gravity = pos;
                framelayout.addView(mBannerAdView, params);

                AdRequest adRequest = new AdRequest();

                mBannerAdView.loadAd(adRequest);

                result = true;
            }
            else {
                Log.e(TAG, "createBanner(): uid is null.");
            }
        }
        else {
            Log.e(TAG, "createBanner(): parent is null.");
        }

        //Log.d(TAG, "createBanner() end");

        return result;
    }

    /**
     * @brief  删除横幅广告函数。
     * @author 赵一
     */
    public static void destoryBanner() {
        //Log.d(TAG, "destoryBanner() start");

        if (mBannerAdView != null) {
            mBannerAdView.destroy();
            mBannerAdView = null;
        }

        //Log.d(TAG, "destoryBanner() end");
    }

    /**
     * @brief 横幅广告控件。
     */
    private static AdView mBannerAdView = null;

    /**
     * @brief 日志标记。
     */
    private static String TAG = "GoogleAdmobSDK";
}
