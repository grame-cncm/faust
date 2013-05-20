package com.faustApp;

import android.os.Bundle;
import android.app.Activity;
import android.webkit.WebView;

public class DisplayWelcomeActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_display_welcome);
		WebView myWebView = (WebView) findViewById(R.id.webview);
		myWebView.loadUrl("file:///android_asset/welcome.html");
	}

}
