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
 */

import com.dsp_faust.dsp_faust;
import com.illposed.osc.OSCListener;
import com.illposed.osc.OSCMessage;
import com.illposed.osc.OSCPort;
import com.illposed.osc.OSCPortIn;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import android.util.Log;

//import android.view.WindowManager;
//import android.view.WindowManager.LayoutParams;

import java.net.SocketException;

public class FaustActivity extends Activity {
	int accelUpdateRate = 30; //in ms
	private SensorManager mSensorManager;
	float[] rawAccel = new float[3];
	int numberOfParameters;
	boolean activityJustCreated;
	
	//Thread displayThread, accelThread;
	Thread accelThread;
	boolean on = true; // process on/off
	
	UI ui = new UI(); 
	ParametersInfo parametersInfo = new ParametersInfo();
	AccelUtil accelUtil = new AccelUtil();
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.d("FaustJava", "onCreate");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
		//getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        
        activityJustCreated = true; // used to load the saved parameters only once
        
        if (!dsp_faust.isRunning()) dsp_faust.init(44100,512);

		// attempting to open a new OSC port, if default not available create a new one
		int oscPortNumber = 5511;
		while(!Osc.init(oscPortNumber)) oscPortNumber++;
		//System.out.println("Osc In Port: " + oscPortNumber);
        
        numberOfParameters = dsp_faust.getParamsCount();
        
        parametersInfo.init(numberOfParameters);
        SharedPreferences settings = getSharedPreferences("savedParameters", 0);

        LinearLayout mainGroup = (LinearLayout) findViewById(R.id.the_layout);
        HorizontalScrollView horizontalScroll = (HorizontalScrollView) findViewById(R.id.horizontalScroll);
        ui.horizontalScroll = horizontalScroll;
        
        ui.initUI(parametersInfo,settings);	
        ui.buildUI(this, mainGroup);

        Osc.startListening();

        /*
         * ACCELEROMETERS
         */
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(
        		Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);
       
        /*
        final int displayThreadUpdateRate = 30;
        displayThread = new Thread() {
        	public void run() {
        		while(on){
        			if(ui.parametersCounters[2] > 0){
        				for(int i=0; i<ui.parametersCounters[2]; i++){
        					//UI.bargraphs[i].setValue(UI.faust.getParam(UI.parametersInfo.address[UI.bargraphs[i].id]));
        				}
        			}
        			try {
						displayThread.sleep(1000/displayThreadUpdateRate);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
        		}
        	}
        };
        displayThread.start();
        */
		
        // System.out.println("Voila: ");
		accelThread = new Thread() {
			public void run() {
				float finalParameterValue = 0.0f;
				// TODO: the accelerometer class should be used to clean this a little bit
				while(on){
					// for each UI element we control the accelerometer parameters
					for(int i = 0; i<numberOfParameters; i++){
						if(parametersInfo.accelState[i] >= 1 && parametersInfo.accelItemFocus[i] == 0){
							if(parametersInfo.accelState[i] == 1){ 
								finalParameterValue = accelUtil.transform(rawAccel[0], parametersInfo.accelMin[i], 
										parametersInfo.accelMax[i], parametersInfo.accelCenter[i], parametersInfo.sliderCenter[i], parametersInfo.accelInverterState[i]);
							}
							else if(parametersInfo.accelState[i] == 2){
								finalParameterValue = accelUtil.transform(rawAccel[1], parametersInfo.accelMin[i], 
										parametersInfo.accelMax[i], parametersInfo.accelCenter[i], parametersInfo.sliderCenter[i], parametersInfo.accelInverterState[i]);
							}
							else if(parametersInfo.accelState[i] == 3){
								finalParameterValue = accelUtil.transform(rawAccel[2], parametersInfo.accelMin[i], 
										parametersInfo.accelMax[i], parametersInfo.accelCenter[i], parametersInfo.sliderCenter[i], parametersInfo.accelInverterState[i]);
							}	
							// the slider value is modified by the accelerometer 
							final float finalParamValue = finalParameterValue;
							final int index = i;
							// the UI elements must be updated within the UI thread...
							runOnUiThread(new Runnable() {
		        	        	@Override 
		        	        	public void run() {
		        	        		setPriority(Thread.MAX_PRIORITY);
		        	        		if(parametersInfo.parameterType[index] == 0) 
		        	        			ui.hsliders[parametersInfo.localId[index]].setNormizedValue(finalParamValue);
		        	        		else if(parametersInfo.parameterType[index] == 1) 
		        	        			ui.vsliders[parametersInfo.localId[index]].setNormizedValue(finalParamValue);
		        	        		else if(parametersInfo.parameterType[index] == 2) 
		        	        			ui.knobs[parametersInfo.localId[index]].setNormizedValue(finalParamValue);
		        	        		else if(parametersInfo.parameterType[index] == 3) 
		        	        			ui.nentries[parametersInfo.localId[index]].setNormizedValue(finalParamValue);  	}
							});
						}
					}
					try {
						accelThread.sleep(accelUpdateRate);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
                    //System.out.println("Here");
				}		
			}
		};
		accelThread.start();
    }
    
    private final SensorEventListener mSensorListener = new SensorEventListener() {
		public void onSensorChanged(SensorEvent se) {
			rawAccel[0] = se.values[0];
			rawAccel[1] = se.values[1];
			rawAccel[2] = se.values[2];
		}
	    public void onAccuracyChanged(Sensor sensor, int accuracy) {
	    }
	};
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        Log.d("FaustJava", "onCreateOptionsMenu");
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
            	if(parametersInfo.zoom > 0){
            		parametersInfo.zoom--;
            		recreate();
            	}
                return true;
            case R.id.action_reset:
                parametersInfo.saved = 0;
                recreate();
                return true;
            case R.id.action_lock:
            	if(parametersInfo.locked){
            		item.setIcon(R.drawable.ic_lockiconopen);
            		parametersInfo.locked = false;
            		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
            	}
            	else{
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
   		activityJustCreated = false;
   		super.onPause();
   	}

    @Override
    protected void onResume() {
        Log.d("FaustJava", "onResume");
		super.onResume();
		if (!activityJustCreated) ui.updateUIstate();
        mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(
	    		Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);
	    on = true; // TODO: why?
    }

    @Override
    protected void onStart() {
        Log.d("FaustJava", "onStart");
        super.onStart();
        if (!isChangingConfigurations()) {
            dsp_faust.start();
        }
    }

    @Override
    protected void onRestart() {
        Log.d("FaustJava", "onRestart");
        super.onRestart();
    }

    @Override
    protected void onStop(){
        Log.d("FaustJava", "onStop");
        super.onStop();
        if (!isChangingConfigurations()) {
            dsp_faust.stop();
        }
        SharedPreferences settings = getSharedPreferences("savedParameters", 0);
        parametersInfo.saveParameters(settings);
    }

    @Override
    public void onDestroy(){
        Log.d("FaustJava", "onDestroy");
    	super.onDestroy();
    	on = false;
    	// only stops audio when the user press the return button (and not when the screen is rotated)
    	if (!isChangingConfigurations()) {
    		dsp_faust.destroy();
    	}
    	try {
			//displayThread.join();
			accelThread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
    	//displayThread = null;
    	accelThread = null;
    }
}
