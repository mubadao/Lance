/**
 * @brief   共通定义类定义文件。
 * @author  赵一
 * @date    2012/01/07
 * @version 0.1
 */

package com.happybluefin.galaxyinvader;

import android.util.Log;

/**
 * @brief  共通定义类。
 * @author 赵一
 */
public class HBDefine {
    /**
     * @brief  动作定义类。
     * @author 赵一
     */
    public class Action {
        /**
         * @brief 消息动作。
         */
        public static final String ACTION = "com.happybluefin";
    }

    /**
     * @brief  消息定义类。
     * @author 赵一
     */
    public class MessageID {
        /**
         * @brief 消息ID（显示排行榜）。
         */
        public static final int SHOW_LEADERBOARD = 0x0;

        /**
         * @brief 消息ID（提交排行榜分数）。
         */
        public static final int REPORT_SCORE = 0x1;

        /**
         * @brief 消息ID（分享文本）。
         */
        public static final int SHARE_TEXT = 0x2;

        /**
         * @brief 消息ID（分享数据）。
         */
        public static final int SHARE_DATA = 0x3;

        /**
         * @brief 消息ID（浏览器）。
         */
        public static final int WEB_BROWSER = 0x4;

        /**
         * @brief 消息ID（评价）。
         */
        public static final int GOTO_REVIEW = 0x5;

        /**
         * @brief 消息ID（更多游戏）。
         */
        public static final int GOTO_MOREGAME = 0x6;

        /**
         * @brief 消息ID（退出应用）。
         */
        public static final int EXIT_APPLICATION = 0xff;
    }
    
    public static final String HBTag = "HBJava";
    public static final Boolean HBDebug = false;
    public static final String TAG = "HBPay";
    
    public static void HBLog(String msg) {
    	if(HBDefine.HBDebug)
    		Log.d(HBDefine.HBTag, msg);
    }
    
}
