package com.happybluefin.pay;

import java.util.Locale;

import com.happybluefin.galaxyinvader.GameWindow;
import com.happybluefin.galaxyinvader.HBDefine;
import com.happybluefin.galaxyinvader.R;
import com.happybluefin.pay.google.BillingService;
import com.happybluefin.pay.google.Consts;
import com.happybluefin.pay.google.MyPurchaseObserver;
import com.happybluefin.pay.google.ResponseHandler;
import com.happybluefin.pay.google.Security;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Handler;

public class PayGoogle {
	public static final int DIALOG_CANNOT_CONNECT_ID = 1;
	public static final int DIALOG_BILLING_NOT_SUPPORTED_ID = 2;

	private Activity mParent;

	private MyPurchaseObserver myPurchaseObserver;
	private BillingService mBillingService;
	private String mItemName;
	
	private static PayGoogle sPayGoogleInstance;
	
	public static PayGoogle getInstance() {
		if (sPayGoogleInstance == null) {
			sPayGoogleInstance = new PayGoogle();
		}
		return sPayGoogleInstance;
	}
	
	private PayGoogle() {
		mParent = GameWindow.getInstance();
	}
	
	public Activity getParent() {
		return mParent;
	}	

	
	public void initPlatformInfo(String publishKey) {
        HBDefine.HBLog("PayGoogle::initPlatformInfo() start");

		Security.googleBase64EncodedPublicKey = publishKey;
		myPurchaseObserver = new MyPurchaseObserver(this, mItemName, mParent, new Handler());
		ResponseHandler.register(myPurchaseObserver);
		mBillingService = new BillingService();
		mBillingService.setContext(mParent);
		
        HBDefine.HBLog("PayGoogle::initPlatformInfo() end");
	}

	public void pay(String itemName) {
        HBDefine.HBLog("PayGoogle::pay() start");

		mItemName = itemName;
		boolean isSupport = mBillingService.checkBillingSupported(Consts.ITEM_TYPE_INAPP);
        HBDefine.HBLog("PayGoogle::pay() checkBillingSupported:" + isSupport);

		if (!isSupport)
			initFailed();

        HBDefine.HBLog("PayGoogle::pay() end");
	}

	public void doPay() {
        HBDefine.HBLog("PayGoogle::doPay() start");		

		mBillingService.requestPurchase(mItemName, Consts.ITEM_TYPE_INAPP, "1");

        HBDefine.HBLog("PayGoogle::doPay() end");
	}

	public void initFailed() {
        HBDefine.HBLog("PayGoogle::initFailed() start");		

		onCreateDialog(DIALOG_BILLING_NOT_SUPPORTED_ID);

        HBDefine.HBLog("PayGoogle::initFailed() end");		
	}

	public String getItemName() {
		return mItemName;
	}

	IPayEventListener mOnPayListener;
	
	public void setPayEventListener(IPayEventListener iPayEventListener) {
		mOnPayListener = iPayEventListener;
	}
	
	public void onSuccessPay(String productId, String orderId) {
        HBDefine.HBLog("PayGoogle::onSuccessPay() start");		

		if (mOnPayListener != null) {
			mOnPayListener.onSuccessPay(productId, orderId);
		}

        HBDefine.HBLog("PayGoogle::onSuccessPay() end");		
	}

	public void onFailedPay(String productId, String reason) {
        HBDefine.HBLog("PayGoogle::onFailedPay() start");		

		if (mOnPayListener != null) {
			mOnPayListener.onFailedPay(productId, reason);
		}

		HBDefine.HBLog("PayGoogle::onFailedPay() end");
	}

	public static interface IPayEventListener {
		public void onSuccessPay(String productId, String orderId);
		public void onFailedPay(String productId, String reason);
	}
	
	public void onCreateDialog(int id) {
		switch (id) {
		case DIALOG_CANNOT_CONNECT_ID:
			createDialog(R.string.cannot_connect_title, R.string.cannot_connect_message);
		case DIALOG_BILLING_NOT_SUPPORTED_ID:
			createDialog(R.string.billing_not_supported_title, R.string.billing_not_supported_message);
		}
	}

	private void createDialog(int titleId, int messageId) {
		String helpUrl = replaceLanguageAndRegion(mParent.getString(R.string.help_url));
		final Uri helpUri = Uri.parse(helpUrl);

		AlertDialog.Builder builder = new AlertDialog.Builder(mParent);
		builder.setTitle(titleId)
				.setIcon(android.R.drawable.stat_sys_warning)
				.setMessage(messageId)
				.setCancelable(false)
				.setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {}
				})
				.setNegativeButton(R.string.learn_more, new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						Intent intent = new Intent(Intent.ACTION_VIEW, helpUri);
						mParent.startActivity(intent);
					}
				}).create();
		builder.show();
	}

	/**
	 * Replaces the language and/or country of the device into the given string.
	 * The pattern "%lang%" will be replaced by the device's language code and
	 * the pattern "%region%" will be replaced with the device's country code.
	 * 
	 * @param str
	 *            the string to replace the language/country within
	 * @return a string containing the local language and region codes
	 */
	private String replaceLanguageAndRegion(String str) {
		// Substitute language and or region if present in string
		if (str.contains("%lang%") || str.contains("%region%")) {
			Locale locale = Locale.getDefault();
			str = str.replace("%lang%", locale.getLanguage().toLowerCase());
			str = str.replace("%region%", locale.getCountry().toLowerCase());
		}
		return str;
	}
}
