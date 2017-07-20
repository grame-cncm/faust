package com.faust;

/*
 * TODO
 * - Make all accel meta data compatible
 * - The knob class could be greatly improved
 * - Drop down menu for actions for small screens
 * - Vertical sliders are fucked up with accelerometers.
 * - Bargraphs are disabled and need more work
 * - Interface elements could be normalized using android standards
 * (that would take forever and the difference would be hard to notice)
 * - The accelerometers window should be finished: weird stuff with up and down
 * 		- Fancy slider to control min, max and center
 * - Settings menu should be added actually not sure about that...
 * - Multitouch zoom
 * - Try complex examples for debuging
 * - The compilation script should be tested on OSX
 * - OSC should be enabled
 * - If keyboard mode is enabled, elements that removed from the interface should be scaled
 * - Write a proper documentation
 * - Make the native API OSX compatible
 * - Ideally, the C++ API should be able to return min, max, etc... it would be very convenient
 * when an app uses several activities.
 * - Xruns sometimes, not sure why...
 * - Polymax should be defined by "keyboard" in the Faust code...
 * - It seems that when polyphonic, voices are always computed which is highly ineficient...
 * - Multi Params
 * 		- Cosmetic: Big dots when the parameter is being touched.
 * 		- Accelerometer should be enabled in function of what was
 * 		configured in the main interface.
 * - Piano Keyboard
 * 		- Add a dot that would follow the finger when going
 * 		outside of a key.
 * 		- The way the position of the keys on the keyboard is set
 * 		is kind of flumsy: this could be improved.
 * SL : 08/13/15
 * - use index instead of adresses in JNI to access parameters
 */

import com.DspFaust.DspFaust;

import android.os.Build;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.Window;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import android.util.Log;
import android.net.wifi.WifiManager;

import android.media.AudioManager;

public class FaustActivity extends Activity {
    
    private int sampleRate = 44100;
    private int bufferSize = 512;
    private int sensorIntervalMs = 0;
    
	private SensorManager mSensorManager;
	private int numberOfParameters;
	private UI ui = new UI();
	private ParametersInfo parametersInfo = new ParametersInfo();
    private long lastUIDateMs = 0;
    private long lastSensorDateMs = 0;
    private WifiManager.MulticastLock lock;
    private boolean fBuildUI;
    private MonochromeView fMonoView;
    public static DspFaust dspFaust;
    

    /**
     * Detects and toggles immersive mode (also known as "hidey bar" mode).
     */
    public void toggleHideyBar() {

        // BEGIN_INCLUDE (get_current_ui_flags)
        // The UI options currently enabled are represented by a bitfield.
        // getSystemUiVisibility() gives us that bitfield.
        int uiOptions = getWindow().getDecorView().getSystemUiVisibility();
        int newUiOptions = uiOptions;
        // END_INCLUDE (get_current_ui_flags)
        // BEGIN_INCLUDE (toggle_ui_flags)
        boolean isImmersiveModeEnabled =
                ((uiOptions | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY) == uiOptions);
        if (isImmersiveModeEnabled) {
            Log.i("FaustJava", "Turning immersive mode mode off.");
        } else {
            Log.i("FaustJava", "Turning immersive mode mode on.");
        }

        // Navigation bar hiding:  Backwards compatible to ICS.
        if (Build.VERSION.SDK_INT >= 14) {
            newUiOptions ^= View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;
        }

        // Status bar hiding: Backwards compatible to Jellybean
        if (Build.VERSION.SDK_INT >= 16) {
            newUiOptions ^= View.SYSTEM_UI_FLAG_FULLSCREEN;
        }

        // Immersive mode: Backward compatible to KitKat.
        // Note that this flag doesn't do anything by itself, it only augments the behavior
        // of HIDE_NAVIGATION and FLAG_FULLSCREEN.  For the purposes of this sample
        // all three flags are being toggled together.
        // Note that there are two immersive mode UI flags, one of which is referred to as "sticky".
        // Sticky immersive mode differs in that it makes the navigation and status bars
        // semi-transparent, and the UI flag does not get cleared when the user interacts with
        // the screen.
        if (Build.VERSION.SDK_INT >= 19) {
            newUiOptions ^= View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
        }

        getWindow().getDecorView().setSystemUiVisibility(newUiOptions);
        //END_INCLUDE (set_ui_flags)
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        
        Log.d("FaustJava", "onCreate");
        sensorIntervalMs = bufferSize/sampleRate*1000;
        
        if (dspFaust == null) {

            WifiManager wifi = (WifiManager)getSystemService(Context.WIFI_SERVICE);
            if (wifi != null) {
                WifiManager.MulticastLock lock = wifi.createMulticastLock("Log_Tag");
                lock.acquire();
            }
            // attempting to open a new OSC port, if default not available create a new one
            int oscPortNumber = 5510;
            while (!Osc.init(oscPortNumber)) oscPortNumber++;
            Log.d("FaustJava", "onCreate : OSC In Port " + oscPortNumber);

            // Use machine buffer size and sample rate
            AudioManager audioManager = (AudioManager) this.getSystemService(Context.AUDIO_SERVICE);
            
            // Do not work on Android 4.xx
            /*
            String rate = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
            String size = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
            Log.d("FaustJava", "Size :" + size + " Rate: " + rate);
            dsp_faust.init(Integer.parseInt(rate), Integer.parseInt(size));
            */

            // TODO: sr and buffer length should change in function of the device for best latency perfs
            dspFaust = new DspFaust(sampleRate, bufferSize);

            Osc.startListening();
        }

        fBuildUI = (dspFaust.getScreenColor() < 0);
        if (!fBuildUI) {
            requestWindowFeature(Window.FEATURE_NO_TITLE);
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        }
        super.onCreate(savedInstanceState);
        if (fBuildUI) {
            setContentView(R.layout.main);
        } else {
            fMonoView = new MonochromeView(getApplicationContext());
            setContentView(fMonoView);
        }

        numberOfParameters = dspFaust.getParamsCount();

        Log.d("FaustJava", "onCreate : numberOfParameters " + numberOfParameters);

        parametersInfo.init(numberOfParameters);
        SharedPreferences settings = getSharedPreferences("savedParameters", 0);

        if (fBuildUI) {
            LinearLayout mainGroup = (LinearLayout) findViewById(R.id.the_layout);
            HorizontalScrollView horizontalScroll = (HorizontalScrollView) findViewById(R.id.horizontalScroll);
            ui.horizontalScroll = horizontalScroll;
            ui.initUI(parametersInfo,settings);
            ui.buildUI(this, mainGroup);
        } else {
            Log.d("FaustJava", "Don't create User Interface");
            toggleHideyBar();
        }

        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
    }

    private void updatecolor(double x, double y, double z) {
        fMonoView.setRed(x/10.0);
        fMonoView.setGreen(y/10.0);
        fMonoView.setBlue(z/10.0);
    }

    private void updatecolor2(int c) {
        fMonoView.setColor(c);
    }

    private final SensorEventListener mSensorListener = new SensorEventListener() {

		public void onSensorChanged(SensorEvent se) {

            long curDate = java.lang.System.currentTimeMillis();
            long uiDeltaMs = curDate - lastUIDateMs;
            long sensorDeltaMs = curDate - lastSensorDateMs;
    
            if (sensorDeltaMs > sensorIntervalMs) {
                lastSensorDateMs = curDate;
                if (se.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                    // Update mapping at sensor rate, values are inverted to be coherent with iOS
                    dspFaust.propagateAcc(0, -se.values[0]);
                    dspFaust.propagateAcc(1, -se.values[1]);
                    dspFaust.propagateAcc(2, -se.values[2]);
                    if (!fBuildUI) {
                        fMonoView.setColor(dspFaust.getScreenColor());
                    }
                }

                if (se.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
                    // Update mapping at sensor rate
                    dspFaust.propagateGyr(0, se.values[0]);
                    dspFaust.propagateGyr(1, se.values[1]);
                    dspFaust.propagateGyr(2, se.values[2]);
                }
            }

            // Update UI less often
            if (uiDeltaMs > 100) {
                lastUIDateMs = curDate;
                //Log.d("FaustJava", "CPULoad " + dsp_faust.getCPULoad());
                ui.updateUIstate();
            }
		}
	    public void onAccuracyChanged(Sensor sensor, int accuracy) {}
	};

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        Log.d("FaustJava", "onCreateOptionsMenu");
        if (fBuildUI) {
            // Inflate the menu items for use in the action bar
            MenuInflater inflater = getMenuInflater();
            inflater.inflate(R.menu.main_activity_actions, menu);
            MenuItem lockItem = menu.getItem(3); // retrieving the registered ID doesn't seem to work -> hardcoded here
            MenuItem keybItem = menu.getItem(0);
            if (!parametersInfo.locked) {
                lockItem.setIcon(R.drawable.ic_lockiconopen);
            } else {
                lockItem.setIcon(R.drawable.ic_lockiconclose);
                setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LOCKED);
            }
            // display the keyboard icon if the Faust code enables keyboard interfaces
            if (!ui.hasKeyboard && !ui.hasMulti) keybItem.setVisible(false);
            return super.onCreateOptionsMenu(menu);
        } else {
            Log.d("FaustJava", "Don't create Menu");
            return false;
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle presses on the action bar items
        switch (item.getItemId()) {
        	case R.id.action_keyboard:
        		if(ui.hasKeyboard && !ui.hasMulti){
        			Intent pianoIntent = new Intent(this, PianoActivity.class);
        			startActivity(pianoIntent);
        		}
        		else if(ui.hasMulti && !ui.hasKeyboard){
        			SharedPreferences settings = getSharedPreferences("savedParameters", 0);
        		    parametersInfo.saveParameters(settings);
        			Intent multiIntent = new Intent(this, MultiActivity.class);
        			startActivity(multiIntent);
        		}
        		else if(ui.hasMulti && ui.hasKeyboard){
        			SharedPreferences settings = getSharedPreferences("savedParameters", 0);
        		    parametersInfo.saveParameters(settings);
        			Intent multiIntent = new Intent(this, MultiKeyboardActivity.class);
        			startActivity(multiIntent);
        		}
        		return true;
            case R.id.action_zoomin:
            	parametersInfo.zoom++;
                recreate();
                return true;
            case R.id.action_zoomout:
            	if (parametersInfo.zoom > 0) {
            		parametersInfo.zoom--;
            		recreate();
            	}
                return true;
            case R.id.action_reset:
                parametersInfo.saved = 0;
                recreate();
                return true;
            case R.id.action_lock:
            	if (parametersInfo.locked) {
            		item.setIcon(R.drawable.ic_lockiconopen);
            		parametersInfo.locked = false;
            		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
            	} else {
            		item.setIcon(R.drawable.ic_lockiconclose);
            		parametersInfo.locked = true;
            		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LOCKED);
            	}
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
   	protected void onPause() {
        Log.d("FaustJava", "onPause");
   		mSensorManager.unregisterListener(mSensorListener);
   		super.onPause();
   	}

    @Override
    protected void onResume() {
        Log.d("FaustJava", "onResume");
		super.onResume();
        mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(
	    		Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);
   }

    @Override
    protected void onStart() {
        Log.d("FaustJava", "onStart");
        super.onStart();
        if (!isChangingConfigurations()) {
            dspFaust.start();
        }
        ui.updateUIstate();
    }

    @Override
    protected void onRestart() {
        Log.d("FaustJava", "onRestart");
        super.onRestart();
    }

    @Override
    protected void onStop() {
        Log.d("FaustJava", "onStop");
        super.onStop();
        // 15/03/2016 : desactivated so that dynamic activity change (like switch to MultiKeyboardActivity or PianoKeyboard)
        // correctly work
        /*
        if (!isChangingConfigurations()) {
            dsp_faust.stop();
        }
        */
    }

    @Override
    public void onDestroy() {
        Log.d("FaustJava", "onDestroy");
    	// only stops audio when the user press the return button (and not when the screen is rotated)
    	if (!isChangingConfigurations()) {
            Osc.stopListening();
            dspFaust.stop(); // TODO: not sure if needed
    		dspFaust.delete();
        }
        SharedPreferences settings = getSharedPreferences("savedParameters", 0);
        parametersInfo.saveParameters(settings);
        super.onDestroy();
    }
}
