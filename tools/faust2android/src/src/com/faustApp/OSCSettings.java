package com.faustApp;

import android.os.Bundle;
import android.app.Activity;
import android.content.SharedPreferences;
import android.widget.EditText;
import android.text.Editable;
import android.text.TextWatcher;

public class OSCSettings extends Activity {
	
	int oscReceiverPort;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_oscsettings);
		
		final SharedPreferences settings = getSharedPreferences("faust2androidPrefs", 0);
		oscReceiverPort = settings.getInt("OSCport", 9001);
		
		final EditText portNumber = (EditText) findViewById(R.id.portNumber);
		portNumber.setText(Integer.toString(oscReceiverPort));
		
		TextWatcher textWatcher = new TextWatcher() {
			@Override
		    public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void afterTextChanged(Editable editable) {
		    	oscReceiverPort = Integer.parseInt(portNumber.getText().toString());
		    	SharedPreferences.Editor editor = settings.edit();
		    	editor.putInt("OSCport", oscReceiverPort);
		    	editor.commit();
		    }
		};
		portNumber.addTextChangedListener(textWatcher);
	}

}
