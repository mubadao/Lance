package com.happybluefin.pay.google;

import android.app.Activity;
import android.os.Handler;

import com.happybluefin.galaxyinvader.HBDefine;
import com.happybluefin.pay.google.BillingService.RequestPurchase;
import com.happybluefin.pay.google.BillingService.RestoreTransactions;
import com.happybluefin.pay.google.Consts.PurchaseState;
import com.happybluefin.pay.google.Consts.ResponseCode;
import com.happybluefin.pay.PayGoogle;

public class MyPurchaseObserver extends PurchaseObserver {
	private PayGoogle mGooglePay;

	public MyPurchaseObserver(PayGoogle googlePay, String itemName, Activity activity, Handler handler) {
		super(activity, handler);
		mGooglePay = googlePay;
	}

	@Override
	public void onBillingSupported(boolean supported, String type) {
        HBDefine.HBLog("MyPurchaseObserver::onBillingSupported() start");
        HBDefine.HBLog("MyPurchaseObserver::onBillingSupported() onBillingSupported:" + supported);

		if (!supported) {
			mGooglePay.initFailed();
		} else {
			mGooglePay.doPay();
		}

        HBDefine.HBLog("MyPurchaseObserver::onBillingSupported() end");
	}

	@Override
	public void onPurchaseStateChange(PurchaseState purchaseState, String itemId, int quantity,
			long purchaseTime, String developerPayload, final String orderId) {
        HBDefine.HBLog("MyPurchaseObserver::onPurchaseStateChange() start");
        HBDefine.HBLog("MyPurchaseObserver::onPurchaseStateChange() state=" + purchaseState + " orderId=" + orderId);

		if (purchaseState == PurchaseState.PURCHASED) {
			PayGoogle.getInstance().onSuccessPay(itemId, orderId);
		} else if (purchaseState == PurchaseState.CANCELED) {
			PayGoogle.getInstance().onFailedPay(itemId, "Cancel");
		} else {
			PayGoogle.getInstance().onFailedPay(itemId, "Other");
		}

        HBDefine.HBLog("MyPurchaseObserver::onPurchaseStateChange() end");
	}

	@Override
	public void onRequestPurchaseResponse(RequestPurchase request, ResponseCode responseCode) {
        HBDefine.HBLog("MyPurchaseObserver::onRequestPurchaseResponse() start");
        HBDefine.HBLog("MyPurchaseObserver::onRequestPurchaseResponse() responseCode=" + responseCode );
		if (responseCode != ResponseCode.RESULT_OK)
			PayGoogle.getInstance().onFailedPay("0", "Other");
        HBDefine.HBLog("MyPurchaseObserver::onRequestPurchaseResponse() end");
	}

	@Override
	public void onRestoreTransactionsResponse(RestoreTransactions request, ResponseCode responseCode) {
	}
}
