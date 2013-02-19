/**
 * @brief   游戏窗口类定义文件。
 * @author  赵一
 * @date    2012/01/07
 * @version 0.1
 */

package com.happybluefin.galaxyinvader;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.widget.Toast;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.google.analytics.tracking.android.EasyTracker;
import com.happybluefin.android.framework.utility.system.Comment;
import com.happybluefin.android.framework.utility.system.Network;
import com.happybluefin.android.framework.utility.system.Utility;
import com.happybluefin.android.framework.utility.thirdpart.advertisement.Banner.GoogleAdmobSDK;
import com.happybluefin.android.framework.utility.thirdpart.statistics.UmengSDK;

import com.happybluefin.galaxyinvader.R;
import com.happybluefin.pay.PayGoogle;
import com.happybluefin.pay.PayGoogle.IPayEventListener;

/**
 * @brief  游戏窗口类。
 * @author 赵一
 */
public class GameWindow extends Cocos2dxActivity {
	
	public static native int nativePurchaseSuccess(String name);
	public static native int nativePurchaseFailed(String reason);
	
	private static final String sGooglePublishKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAheI9bXergkxwb1wi0kVQNxfrJTWUbaeJNTo9h8U/r45n6JaiiHZ2guzeuGpuGN4/VgBz52dDUXv1QH31P1iiln6FBMxu5DL68Q+av/zRuTmejx+x+A+VgJXpk9GHDvq78PSMXdF3auAE35tR6wzgodS+VmRULp5cGYRbrSxF08D48NmHLqbM1T4eGo39YzmhqLKdGmrFrr086bRNaG4vsydI3afYEaFPZ+1TDYsyAb1xhi8vtDCdDdShqGOpoMox8M7ESROW/6zkadaDOVEoZ/YyaIay3Aa7wf3xTy07BhHKTaY8eyuYr7DfKoqIkoaDn3zfRFtx6T0ZPZWfGTiBYwIDAQAB";

	private static GameWindow sGameWindowInstance;

	public static GameWindow getInstance() {
		return sGameWindowInstance;
	}
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        HBDefine.HBLog("GameWindow::onCreate() start");

        sGameWindowInstance = this;
        //初始化控件
        _initView();

        //初始化友盟
        UmengSDK.autoErrorReport(this);
//      UmengSDK.updateOnlineConfig(this);

        //初始化横幅广告
        GoogleAdmobSDK.createBanner(this, galaxyinvader.getAdmobUnitID(), Gravity.BOTTOM | Gravity.LEFT);
        
        //初始化支付
        _initPay();
        HBDefine.HBLog("GameWindow::onCreate() end");
    }

    @Override
    public void onDestroy() {
        HBDefine.HBLog("GameWindow::onDestroy() start");

        //销毁横幅广告
        GoogleAdmobSDK.destoryBanner();

        // unregist receiver
        unregisterReceiver(mReceiver);
        
        super.onDestroy();
        HBDefine.HBLog("GameWindow::onDestroy() end");
    }

	@Override
	public void onStart() {
	    super.onStart();
	    EasyTracker.getInstance().activityStart(this);
	}

	@Override
	public void onStop() {
	    super.onStop();
	    EasyTracker.getInstance().activityStop(this);
	}	

	@Override
    protected void onPause() {
        HBDefine.HBLog("GameWindow::onPause() start");
        super.onPause();
        UmengSDK.onPause(this);
        HBDefine.HBLog("GameWindow::onPause() end");
    }

    @Override
    protected void onResume() {
        HBDefine.HBLog("GameWindow::onResume() start");
        super.onResume();
        UmengSDK.onResume(this);
        HBDefine.HBLog("GameWindow::onResume() end");
    }
        
    /**
     * @brief     按键处理函数。
     * @param[in] keyCode 按键键值。
     * @param[in] event   事件。
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        HBDefine.HBLog("GameWindow::onKeyDown() start");
        boolean result = false;

        if(keyCode == KeyEvent.KEYCODE_BACK) {
            //什么也不做，将result设置为true，不让系统处理该按键

            result = true;
        }
        else {
            result = super.onKeyDown(keyCode, event);
        }

        HBDefine.HBLog("GameWindow::onKeyDown() end");

        return result;
    }    

    /**
     * @brief  初始化控件函数。
     */
    private void _initView() {
        HBDefine.HBLog("GameWindow::_initView() start");

        //初始化消息接收器
        IntentFilter filter = new IntentFilter();
        filter.addAction(HBDefine.Action.ACTION);
        registerReceiver(mReceiver, filter);

        HBDefine.HBLog("GameWindow::_initView() end");
    }
    
    /**
     * @brief 广播接收器。
     */
    private BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            HBDefine.HBLog("GameWindow::BroadcastReceiver::onReceive() start");

            if (intent != null) {
                Bundle bundle = intent.getExtras();

                int type = bundle.getInt("TYPE");

                String url = bundle.getString("URL");
                switch (type) {
                case HBDefine.MessageID.WEB_BROWSER: {
                    //显示网页
                    if (Network.getConnectivityState(GameWindow.this) == true) {
                        if (Utility.startBrowser(GameWindow.this, url) != true) {
                            Log.e(TAG, "BroadcastReceiver::onReceive(): start browser failed!");
                        }
                    }
                    else {
                        //提示连接网络
                        Toast.makeText(GameWindow.this, R.string.can_not_connect_network, Toast.LENGTH_SHORT).show();
                    }
                    break;
				}
                case HBDefine.MessageID.GOTO_REVIEW: {
                    //提交评价
                    if (Network.getConnectivityState(GameWindow.this) == true) {
                        if (Comment.startGooglePlayComment(GameWindow.this, "com.happybluefin.happybluefin") != true) {
                            Log.e(TAG, "BroadcastReceiver::onReceive(): review failed!");
                        }
                    }
                    else {
                        //提示连接网络
                        Toast.makeText(GameWindow.this, R.string.can_not_connect_network, Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case HBDefine.MessageID.GOTO_MOREGAME: {
                    //提交评价
                    if (Network.getConnectivityState(GameWindow.this) == true) {
//                        if (Comment.gotoMoreGame(GameWindow.this) != true) {
                    	if (Comment.gotoMoreGame(GameWindow.this) != true) {
                            Log.e(TAG, "BroadcastReceiver::onReceive(): moregame failed!");
                        }
                    }
                    else {
                        //提示连接网络
                        Toast.makeText(GameWindow.this, R.string.can_not_connect_network, Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
				}
            }

            HBDefine.HBLog("GameWindow::BroadcastReceiver::onReceive() end");
        }
    };
    
    /**
     * @brief	初始化支付
     */
    private void _initPay() {        
    	PayGoogle.getInstance().initPlatformInfo(sGooglePublishKey);
    	PayGoogle.getInstance().setPayEventListener(new IPayEventListener() {
			@Override
			public void onSuccessPay(String productId, String orderId) {
				_purchaseSuccess(productId);
			}
			@Override
			public void onFailedPay(String productId, String reason) {
				_purchaseFailed(reason);
			}
		});
    }
    
    public static void purchaseItem(String name) {
        HBDefine.HBLog("GameWindow::purchaseItem() start");
        HBDefine.HBLog("GameWindow::purchaseItem() name=" + name);
    	PayGoogle.getInstance().pay(name);
        HBDefine.HBLog("GameWindow::purchaseItem() end");
    }
    
    private void _purchaseSuccess(String name) {
        HBDefine.HBLog("GameWindow::_purchaseSuccess() start");
        HBDefine.HBLog("GameWindow::_purchaseSuccess() name=" + name);
    	galaxyinvader.umengCustomEvent("Purchase", "Success");
    	nativePurchaseSuccess(name);
        HBDefine.HBLog("GameWindow::_purchaseSuccess() end");
    }
    
    private void _purchaseFailed(String reason) {
        HBDefine.HBLog("GameWindow::_purchaseFailed() start");
        HBDefine.HBLog("GameWindow::_purchaseFailed() reason=" + reason);
    	galaxyinvader.umengCustomEvent("Purchase", "Failed");
    	nativePurchaseFailed(reason);
        HBDefine.HBLog("GameWindow::_purchaseFailed() end");
    }
    
    /**
     * @brief 日志标记。
     */
    private static final String TAG = "GameWindow";

}
