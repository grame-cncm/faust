import android.os.Bundle;
import android.app.Activity;
import android.content.SharedPreferences;
import android.widget.EditText;
import android.text.Editable;
import android.text.TextWatcher;

public class OSCSettings extends Activity {
	
	int oscReceiverPort, oscSenderPort;
	String ipAddress;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_oscsettings);
		
		final SharedPreferences settings = getSharedPreferences("faust2androidPrefs", 0);
		oscReceiverPort = settings.getInt("OSCInPort", 5511);
		oscSenderPort = settings.getInt("OSCOutPort", 5510);
		ipAddress = settings.getString("OSCip","127.0.0.1");
		
		final EditText portInNumber = (EditText) findViewById(R.id.rPortNumber);
		portInNumber.setText(Integer.toString(oscReceiverPort));
		
		final EditText portOutNumber = (EditText) findViewById(R.id.sPortNumber);
		portOutNumber.setText(Integer.toString(oscSenderPort));
		
		final EditText oscIP = (EditText) findViewById(R.id.ipAddress);
		oscIP.setText(ipAddress);
		
		TextWatcher textWatcherReceiver = new TextWatcher() {
			@Override
		    public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void afterTextChanged(Editable editable) {
		    	oscReceiverPort = Integer.parseInt(portInNumber.getText().toString());
		    	SharedPreferences.Editor editor = settings.edit();
		    	editor.putInt("OSCInPort", oscReceiverPort);
		    	editor.commit();
		    }
		};
		portInNumber.addTextChangedListener(textWatcherReceiver);
		
		TextWatcher textWatcherSender = new TextWatcher() {
			@Override
		    public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void afterTextChanged(Editable editable) {
		    	oscSenderPort = Integer.parseInt(portOutNumber.getText().toString());
		    	SharedPreferences.Editor editor = settings.edit();
		    	editor.putInt("OSCOutPort", oscSenderPort);
		    	editor.commit();
		    }
		};
		portOutNumber.addTextChangedListener(textWatcherSender);
		
		TextWatcher textWatcherIP = new TextWatcher() {
			@Override
		    public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void afterTextChanged(Editable editable) {
		    	ipAddress = oscIP.getText().toString();
		    	SharedPreferences.Editor editor = settings.edit();
		    	editor.putString("OSCip",ipAddress);
		    	editor.commit();
		    }
		};
		oscIP.addTextChangedListener(textWatcherIP);
	}
}
