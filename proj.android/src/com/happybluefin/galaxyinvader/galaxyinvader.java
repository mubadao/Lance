/**
 * @brief   应用程序类定义文件。
 * @author  赵一
 * @date    2012/01/07
 * @version 0.1
 */

package com.happybluefin.galaxyinvader;

import java.util.Locale;

import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.happybluefin.android.framework.utility.thirdpart.statistics.UmengSDK;

/**
 * @brief  应用程序类。
 * @author 赵一
 */
public class galaxyinvader extends Application {
	
	/**
     * @brief  取得Admob广告ID函数。
     */
    public static native String getAdmobUnitID();
	
	/**
     * @brief  取得设备语言编码。
     */
    public static native int nativeSetLang(String a);
	
    /**
     * @brief  应用程序建立函数。
     */
    public void onCreate() {
    	super.onCreate();
        HBDefine.HBLog("galaxyinvader::onCreate() start");

        mContext = this;

        //设定设备语言代码
        _initLanguage();
        
        HBDefine.HBLog("galaxyinvader::onCreate() end");
    }
    
    /**
     * @brief     打开网页函数。
     * @param[in] url 网页地址。
     */
    public static void gotoUrl(String url) {
        HBDefine.HBLog("galaxyinvader::gotoUrl() start");

        if (mContext != null) {
            Bundle bundle = new Bundle();
            Intent intent = new Intent(HBDefine.Action.ACTION);
            bundle.putInt("TYPE", HBDefine.MessageID.WEB_BROWSER);
            bundle.putString("URL", url);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }
        else {
            Log.e(TAG, "gotoUrl(): mContext is NULL.");
        }

        HBDefine.HBLog("galaxyinvader::gotoUrl() end");
    }

    /**
     * @brief  评价函数。
     */
    public static void gotoReview() {
        HBDefine.HBLog("galaxyinvader::gotoReview() start");

        if (mContext != null) {
            Bundle bundle = new Bundle();
            Intent intent = new Intent(HBDefine.Action.ACTION);
            bundle.putInt("TYPE", HBDefine.MessageID.GOTO_REVIEW);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }
        else {
            Log.e(TAG, "gotoReview(): mContext is NULL.");
        }

        HBDefine.HBLog("galaxyinvader::gotoReview() end");
    }
    
    /**
     * @brief     跳转到GooglePlay游戏列表
     * @param[in] context 上下文。
     */
    public static void gotoMoreGame() {
        HBDefine.HBLog("galaxyinvader::gotoMoreGame() start");

        if (mContext != null) {
            Bundle bundle = new Bundle();
            Intent intent = new Intent(HBDefine.Action.ACTION);
            bundle.putInt("TYPE", HBDefine.MessageID.GOTO_MOREGAME);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }
        else {
            Log.e(TAG, "gotoMoreGame(): mContext is NULL.");
        }

        HBDefine.HBLog("galaxyinvader::gotoMoreGame() end");
    }
    
    /**
     * @brief     Umeng取得在线参数函数。
     * @param[in] name 在线参数键值。
     * @return    Umeng在线参数。
     */
    public static int umengGetParamValue(String name) {
        HBDefine.HBLog("galaxyinvader::umengGetParamValue() start");

        int ret = UmengSDK.getConfigIntParams(mContext, name, 0);

        HBDefine.HBLog("galaxyinvader::umengGetParamValue() end");

        return ret;
    }

    /**
     * @brief     Umeng自定义事件函数。
     * @param[in] name  自定义事件键值。
     * @param[in] value 自定义事件数值。
     */
    public static void umengCustomEvent(String name, String value) {
        HBDefine.HBLog("galaxyinvader::umengCustomEvent() start");

        if (mContext != null) {
            UmengSDK.customEvent(mContext, name, value);
        }

        HBDefine.HBLog("galaxyinvader::umengCustomEvent() end");
    }
    
    /**
     * @brief  设定语言代码
     */
    private void _initLanguage() {
    	String language1 = "";
		String language2 = "";
		 
		language1 = Locale.getDefault().getLanguage();
		language2 = Locale.getDefault().toString();
		
		Log.i(galaxyinvader.TAG, "_initLanguage() Locale.Language=" + language1 + ", Locale=" + language2);

		 if(language1.compareTo("zh") == 0)
			 nativeSetLang(language2);
		 else
			 nativeSetLang(language1); 
    }
    
    static {
        try {
            System.loadLibrary("game");
        }
        catch (UnsatisfiedLinkError e) {
            e.printStackTrace();
            throw e;
        }
    }
    
    /**
     * @brief 上下文。
     */
    private static Context mContext = null;

    /**
     * @brief 日志标记。
     */
    private static final String TAG = "galaxyinvader";

}