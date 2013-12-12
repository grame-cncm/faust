/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2013 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 
 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.
 
 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

import faust_dsp.Para;
import faust_dsp.SWIGTYPE_p_float;
import faust_dsp.SWIGTYPE_p_int;
import faust_dsp.faust;
import faust_dsp.faust_dsp;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.graphics.Point;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.text.Editable;
import android.text.InputType;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Display;
import android.view.Gravity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.MotionEvent;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.ToggleButton;

import java.lang.String;
import java.net.InetAddress;
import java.net.SocketException;

import osc.OSCListener;
import osc.OSCMessage;
import osc.OSCPacket;
import osc.OSCPortIn;
import osc.OSCPortOut;

public class faustApp extends Activity {
	
	// global elements
	public static final String PREFS_NAME = "faust2androidPrefs";
	Thread thread;
	float[] parVals; // values given by the different elements of the UI
	static float[] OSCval;
	boolean on = true; // process on/off
	float metaDatAccelVal[][];
	
	// C++ components
	faust f = new faust();
	faust_dsp o = new faust_dsp();
	
	// UI layouts
	LinearLayout[] currentGroup; // refers to the current group in the UI hierarchy
	int groupLevel = 0;
	
	OSCPortIn receiver = null;
	OSCPortOut sender = null;
	
	/****************************************************************
	 TOOLS FUNCTIONS 
	*****************************************************************/
	
	/*
	 * isNumeric check if a string is a number.
	 */
	public static boolean isNumeric(String str)  
	{  
	  try  
	  {  
	    double d = Double.parseDouble(str);  
	  }  
	  catch(NumberFormatException nfe)  
	  {  
	    return false;  
	  }  
	  return true;  
	}
	
	/****************************************************************
	 OSC support
	*****************************************************************/
	
	public static void OSCreceiver(OSCPortIn receiver, final String address, final int n) throws java.net.SocketException {
		OSCListener listener = new OSCListener() {
			float value;
			Object[] values;	
			public void acceptMessage(java.util.Date time, OSCMessage message) {
				// check for null pointer exception...
				if(message != null){ 
			        values = message.getArguments();
			        if(values.length>0){
			        	// Only the first OSC value is used
			        	if(values[0] != null){ 
			        		value = Float.parseFloat(values[0].toString());
			        		OSCval[n] = value;
			        	}
			        }
				}
				}
			};
			receiver.addListener(address, listener);
			receiver.startListening();
	 }
	
	private class sendOSCmessage extends AsyncTask<OSCMessage,Void,Void> {
		protected Void doInBackground(OSCMessage... msg) {
			try {
				sender.send((OSCPacket)msg[0]);
			} catch (Exception e) {
				Log.i("osc", "Couldn't send");
				Log.i("osc", e.toString());
			}
			return null;
	     }
	}
	
	/****************************************************************
	 UI FUNCTIONS 
	*****************************************************************/
    
	/*
	 * createAccelWindow creates the window that contains the elements to control how 
	 * the accelerometer modifies the value of a parameter.
	 */
    private void createAccelWindow(final boolean[] accelStatu, final PopupWindow popUp, final LinearLayout layAccel){
    	final LinearLayout layButtonsAccel, laySensibilityAccel;
    	final TextView accelTitle, sensT, assignation;
    	LayoutParams paramsLayAccel, paramsLayB, paramsLaySens;
    	final Button closeBut;
        
        layButtonsAccel = new LinearLayout(this);
        laySensibilityAccel = new LinearLayout(this);
        
        // Accelerometer Menu Title
        accelTitle = new TextView(this);
        accelTitle.setText("Accelerometer Control Panel");
        accelTitle.setTextSize(22);
        accelTitle.setPadding(0, 0, 0, 20);
        
        // Instantiating Accelerometers Buttons
        assignation = new TextView(this);
        assignation.setText("Assignation:");
        
        accel.bX = new ToggleButton(this);
        accel.bX.setText("X");
        accel.bX.setTextOff("X");
        accel.bX.setTextOn("X");
        
        accel.bY = new ToggleButton(this);
        accel.bY.setText("Y");
        accel.bY.setTextOn("Y");
        accel.bY.setTextOff("Y");
        
        accel.bZ = new ToggleButton(this);
        accel.bZ.setText("Z");
        accel.bZ.setTextOn("Z");
        accel.bZ.setTextOff("Z");

        accelStatu[0] = false;
        accelStatu[1] = false;
        accelStatu[2] = false;
        
        accel.bX.setOnCheckedChangeListener(new OnCheckedChangeListener(){
        	public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        		if(isChecked){
        			accelStatu[0] = true;
        			accel.bY.setChecked(false);
        			accel.bZ.setChecked(false);
        		}
        		else accelStatu[0] = false;
        	}
        });
        
        accel.bY.setOnCheckedChangeListener(new OnCheckedChangeListener(){
        	public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        		if(isChecked){
        			accelStatu[1] = true;
        			accel.bX.setChecked(false);
        			accel.bZ.setChecked(false);
        		}
        		else accelStatu[1] = false;
        	}
        });
        
        accel.bZ.setOnCheckedChangeListener(new OnCheckedChangeListener(){
        	public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        		if(isChecked){
        			accelStatu[2] = true;
        			accel.bX.setChecked(false);
        			accel.bY.setChecked(false);
        		}
        		else accelStatu[2] = false;
        	}
        });
        
        // Invert Button
        accel.invert = new ToggleButton(this);
        accel.invert.setText("Inverted");
        accel.invert.setTextOn("Inverted");
        accel.invert.setTextOff("Inverted");
        
        accel.invert.setOnCheckedChangeListener(new OnCheckedChangeListener(){
        	public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        		if(isChecked) accelStatu[3] = true;
        		else accelStatu[3] = false;
        	}
        });
        
        // Sensibility Control Bar
        sensT = new TextView(this);
        sensT.setText("Sensibilty:");
        accel.sensibility = new SeekBar(this);
        accel.sensibility.setMax(300);
        
        // Close Button
        closeBut = new Button(this);
        closeBut.setText("Close"); 
        closeBut.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	popUp.dismiss();
            	accel.focusOnSliderN = 0;
            	}
            }
        );  
        
        // Main Accel Layout
        paramsLayAccel = new LayoutParams(LayoutParams.MATCH_PARENT,
      	       LayoutParams.MATCH_PARENT);
        layAccel.setLayoutParams(paramsLayAccel);
        layAccel.setOrientation(LinearLayout.VERTICAL);
        
        // Title
        layAccel.addView(accelTitle);
        
        // Accelerometer Buttons Layout
        paramsLayB = new LayoutParams(LayoutParams.MATCH_PARENT,
       	       LayoutParams.WRAP_CONTENT);
        layButtonsAccel.setLayoutParams(paramsLayB);
        //assignation.setLayoutParams(paramsLayB);
        
        // TODO: easy fix for small screens: better?
        //layButtonsAccel.addView(assignation);
        layButtonsAccel.addView(accel.bX);
        layButtonsAccel.addView(accel.bY);
        layButtonsAccel.addView(accel.bZ);
        layButtonsAccel.addView(accel.invert);
        
        layAccel.addView(layButtonsAccel);
        
        // Sensibility Bar Layout
        paramsLaySens = new LayoutParams(LayoutParams.MATCH_PARENT,
        	       LayoutParams.WRAP_CONTENT);
        laySensibilityAccel.setLayoutParams(paramsLaySens);
        laySensibilityAccel.setOrientation(LinearLayout.VERTICAL);
        
        sensT.setLayoutParams(paramsLaySens);
        laySensibilityAccel.addView(sensT);
        
        accel.sensibility.setLayoutParams(paramsLaySens);
        laySensibilityAccel.addView(accel.sensibility);
        
        OnSeekBarChangeListener sensListener = new OnSeekBarChangeListener() {
			public void onStopTrackingTouch(SeekBar seekBar) {}
			public void onStartTrackingTouch(SeekBar seekBar) {}
			public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
	          	if(fromUser){ 
	          		accel.sensibilityVal = progress;
	          		sensT.setText("Sensibilty: " + Float.toString(progress));
	          	}
	          	}
	    };
	    accel.sensibility.setOnSeekBarChangeListener(sensListener);

        layAccel.addView(laySensibilityAccel);
        
        popUp.setContentView(layAccel);
        
        // Close Button
        layAccel.addView(closeBut);
    }
	
	// add a button to the UI
	private void addButton(final int n, final int m, final String label, final String address){ 
		UI.buttons[m] = new Button(this);
        LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        UI.buttons[m].setText(label);
        UI.buttons[m].setTextColor(Color.BLACK);
        UI.buttons[m].setLayoutParams(params);
        currentGroup[groupLevel-1].addView(UI.buttons[m]); // add the element to the current group
        
        UI.buttons[m].setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                	parVals[n] = 1.f;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                	parVals[n] = 0.f;
                }
                
                Object OSCarg[] = new Object[1]; 
				OSCarg[0] = new Float(parVals[n]);
	          	OSCMessage msg = new OSCMessage(address,OSCarg);
	          	new sendOSCmessage().execute(msg);
                
	          	return true;
            }
        });
	}
	
	// add a check box to the UI
	private void addCheckButton(final int n, final int m, final String label, final String address){
		UI.checkBoxes[m] = new CheckBox(this);
        LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        UI.checkBoxes[m].setText(label);
        UI.checkBoxes[m].setLayoutParams(params);
        parVals[n] = 0.f;
        currentGroup[groupLevel-1].addView(UI.checkBoxes[m]); // add the element to the current group
        
        UI.checkBoxes[m].setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
        	@Override
        	public void onCheckedChanged(CompoundButton buttonView,boolean isChecked) {
        		if (isChecked){
        			parVals[n] = 1.f;
        		}
        		else parVals[n] = 0.f;
        		Object OSCarg[] = new Object[1]; 
		    	OSCarg[0] = new Float(parVals[n]);
		    	OSCMessage msg = new OSCMessage(address,OSCarg);
		    	new sendOSCmessage().execute(msg);
        	}
        });
	}
	
	// add a numerical entry to the UI
	private void addNentry(final int n, final int m, final String label, final float init, final float min, final float max, final float step, final String address){
		// slider's label and value display
		UI.labels[n] = new TextView(this);
		LayoutParams paramsText = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		UI.labels[n].setLayoutParams(paramsText);
		UI.labels[n].setText(label+":");
		currentGroup[groupLevel-1].addView(UI.labels[n]);
				 
		UI.nEntries[m] = new EditText(this);
		LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		UI.nEntries[m].setLayoutParams(params);
		UI.nEntries[m].setGravity(Gravity.CENTER); // TODO nentry and buttons should be centered...
		UI.nEntries[m].setInputType(InputType.TYPE_CLASS_NUMBER|InputType.TYPE_NUMBER_FLAG_DECIMAL);
		UI.nEntries[m].setText(Float.toString(init));
		parVals[n] = init;
		this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
		currentGroup[groupLevel-1].addView(UI.nEntries[m]);
		
		TextWatcher textWatcher = new TextWatcher() { 
		    @Override
		    public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void afterTextChanged(Editable editable) {
		       //here, after we introduced something in the EditText we get the string from it
		       String value = UI.nEntries[m].getText().toString();
		       if(isNumeric(value)){
		    	   if(Float.parseFloat(value) >= min & Float.parseFloat(value) <= max) parVals[n] = Float.parseFloat(value);
		    	   else parVals[n] = init;
		    	   Object OSCarg[] = new Object[1]; 
		    	   OSCarg[0] = new Float(parVals[n]);
		    	   OSCMessage msg = new OSCMessage(address,OSCarg);
		    	   new sendOSCmessage().execute(msg);
		       }
		    }
		};
		UI.nEntries[m].addTextChangedListener(textWatcher);
	}
	
	// add a slider to the UI
	private void addSeekBar(final int n, final int m, final String label, final float init, final float min, final float max, final float step, final String address) {
		// slider's label and value display
		UI.labels[n] = new TextView(this);
		LinearLayout barLabel = new LinearLayout(this);
		LayoutParams paramsText = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		LayoutParams paramsBarLabel = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		barLabel.setLayoutParams(paramsBarLabel);
		UI.labels[n].setLayoutParams(paramsText);
		UI.labels[n].setText(label+": " + Float.toString(init));
		currentGroup[groupLevel-1].addView(UI.labels[n]);

		UI.labels[n].setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                	// we update the status of the accelerometer window in function of the slider being considered
                	if(accel.paramAccelState[m][0]==0){
                		accel.bX.setChecked(false);
                		accel.bY.setChecked(false);
                		accel.bZ.setChecked(false);
                	}
                	else if(accel.paramAccelState[m][0]==1){ 
                		accel.bX.setChecked(true);
                		accel.bY.setChecked(false);
                		accel.bZ.setChecked(false);
                	}
                	else if(accel.paramAccelState[m][0]==2){
                		accel.bX.setChecked(false);
                		accel.bY.setChecked(true);
                		accel.bZ.setChecked(false);
                	}
                	else if(accel.paramAccelState[m][0]==3){
                		accel.bX.setChecked(false);
                		accel.bY.setChecked(false);
                		accel.bZ.setChecked(true);
                	}
                	
                	if(accel.paramAccelState[m][1]==-1) accel.invert.setChecked(true);
                	else accel.invert.setChecked(false);
                	
                	accel.sensibility.setProgress(accel.paramAccelState[m][2]);
                	
                	accel.popUp.showAtLocation(accel.layout, Gravity.CENTER,0,0);
                    
                	Display display = getWindowManager().getDefaultDisplay();
                	Point size = new Point();
                	display.getSize(size);
                	      	
                	accel.popUp.update(0, 0, currentGroup[0].getWidth()-45, (int) (size.y*0.35));
                    accel.focusOnSliderN = m + 1;
                } 
                return true;
            }
        });
		
		UI.sliders[m] = new SeekBar(this);
		LayoutParams paramsSlider = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		UI.sliders[m].setLayoutParams(paramsSlider);
		UI.sliders[m].setPadding(20, 8, 8, 20);
		parVals[n] = init;
		int range = Math.round((max-min)*(1/step));
		UI.sliders[m].setMax(range);
		if(init<=0 && min<0) UI.sliders[m].setProgress(Math.round((init-min)*(1/step)));
		else UI.sliders[m].setProgress(Math.round((init+min)*(1/step)));
		currentGroup[groupLevel-1].addView(UI.sliders[m]);
		
		OnSeekBarChangeListener listener = new OnSeekBarChangeListener() {
			public void onStopTrackingTouch(SeekBar seekBar) {}
			public void onStartTrackingTouch(SeekBar seekBar) {}
			public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {					
				parVals[n] = (progress*step) + min;	
				
				Object OSCarg[] = new Object[1]; 
				OSCarg[0] = new Float(parVals[n]);
	          	OSCMessage msg = new OSCMessage(address,OSCarg);
	          	new sendOSCmessage().execute(msg);
	          		
	         	UI.labels[n].setText(label+": " + Float.toString(parVals[n]));
	          }
	    };
	    UI.sliders[m].setOnSeekBarChangeListener(listener);
	    //UI.sliders[m].setVisibility(4);
	}
	
	// create a vertical group for the UI
	private void addVerticalGroup(final int id, final String label){
		if(groupLevel==0){
			currentGroup = new LinearLayout[5];
			currentGroup[0] = (LinearLayout) findViewById(R.id.the_layout);
			groupLevel = 1;
		}
		LinearLayout l = new LinearLayout(this);
		LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		l.setLayoutParams(params);
		l.setId(id);
		l.setOrientation(LinearLayout.VERTICAL);
		l.setBackgroundColor(Color.rgb(groupLevel*15,groupLevel*15,groupLevel*15));
		l.setPadding(10,10,10,10);
		l.setGravity(Gravity.LEFT);
		currentGroup[groupLevel-1].addView(l);
		currentGroup[groupLevel] = l;
		groupLevel++;
		
		TextView t = new TextView(this);
		LayoutParams paramsText = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		t.setLayoutParams(paramsText);
		t.setText(label);
		t.setTextSize(24.f);
		l.addView(t);
	}
	
	// create an horizontal group for the UI 
	// TODO not used for now: all groups are vertical groups
	private void addHorizontalGroup(final int id, final String label){
		if(groupLevel==0){
			currentGroup = new LinearLayout[5];
			currentGroup[0] = (LinearLayout) findViewById(R.id.the_layout);
			groupLevel = 1;
		}
		LinearLayout l = new LinearLayout(this);
		LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		l.setLayoutParams(params);
		l.setId(id);
		l.setOrientation(LinearLayout.HORIZONTAL);
		l.setBackgroundColor(Color.rgb(groupLevel*15,groupLevel*15,groupLevel*15));
		l.setPadding(10,10,10,10);
		l.setGravity(Gravity.CENTER);
		currentGroup[groupLevel-1].addView(l);
		currentGroup[groupLevel] = l;
		groupLevel++;
		
		TextView t = new TextView(this);
		LayoutParams paramsText = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		t.setLayoutParams(paramsText);
		t.setText(label);
		t.setTextSize(24.f);
		l.addView(t);
	}
	
	// close a group in the UI
	private void closeGroup(){
		groupLevel--;
	}
	
	//*******************************
	// Accelerometer stuffs
	//*******************************
	
	private SensorManager mSensorManager;
	private float mAccelx; // acceleration apart from gravity
	private float mAccely;
	private float mAccelz;
	private float mAccelxDel; // acceleration apart from gravity
	private float mAccelyDel;
	private float mAccelzDel;
	private float mAccelCurrent; // current acceleration including gravity
	private float mAccelLast; // last acceleration including gravity

	private final SensorEventListener mSensorListener = new SensorEventListener() {
		public void onSensorChanged(SensorEvent se) {
			mAccelx = -se.values[0];
			mAccely = -se.values[1];
			mAccelz = -se.values[2];
		}
	    public void onAccuracyChanged(Sensor sensor, int accuracy) {
	    }
	};
	
	@Override
	protected void onStart() {
		super.onStart();
		on = true;
	}
	
	@Override
	protected void onResume() {
		super.onResume();
	    mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);
	    int oscSendPort;
        String oscIP;
        SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
	    oscSendPort = settings.getInt("OSCOutPort", 9002);
        oscIP = settings.getString("OSCip", "127.0.0.1");
        
        try {
        	InetAddress ipAdress =  InetAddress.getByName(oscIP);
			sender = new OSCPortOut(ipAdress, oscSendPort);
		} catch (Exception e) {
            Log.i("osc", e.toString());
		}
	    on = true;
	}
	
	/*
	 * In case the status of the app would need to be saved even after
	 * it is destroyed...
	 */
	
	/*
	@Override
	protected void onSaveInstanceState(Bundle state) {
	    super.onSaveInstanceState(state);
	}

	@Override
	protected void onRestoreInstanceState(Bundle savedInstanceState) {
	    super.onRestoreInstanceState(savedInstanceState);
	}
	*/
	
	
	// Compute 2-points mapping. The value <a> between <la> and <ha> is 
	// linearly mapped between <lv> and <hv>. It is assumed that <ha> != <la>
	
	float mapping2 (float a, float la, float ha, float lv, float hv)
	{
		if (a < la) {
			return lv;
		} else if (a > ha) {
			return hv;
		} else {
			return (a-la)/(ha-la)*(hv-lv)+lv;
		}
	}
	
	// Compute 3-points mapping. The value <a> between <la> and <ha> is mapped
	// between <lv> and <hv> in such a way that <ma> is mapped to <mv> 
	
	float mapping3(float a, float la, float ma, float ha, float lv, float mv, float hv)
	{
		if (a > ma) {
			return mapping2(a, ma, ha, mv, hv);
		} else {
			return mapping2(a, la, ma, lv, mv);
		}
	}
	
	/*
	 * Main view
	 */
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
        boolean firstOpen = true;
        firstOpen = settings.getBoolean("firstOpen", true);
        int oscReceiverPort, oscSendPort;
        String oscIP;
        if(firstOpen){ 
        	SharedPreferences.Editor editor = settings.edit();
        	editor.putBoolean("firstOpen", false);
        	editor.putInt("OSCInPort", 5511);
        	editor.putInt("OSCOutPort", 5510);
        	editor.putString("OSCip", "127.0.0.1");
        	editor.commit();
        	Intent intent = new Intent(this, DisplayWelcomeActivity.class);
        	startActivity(intent);
        }
        oscReceiverPort = settings.getInt("OSCInport", 5511);
        oscSendPort = settings.getInt("OSCOutPort", 5510);
        oscIP = settings.getString("OSCip", "127.0.0.1");
        
        try {
        	InetAddress ipAdress =  InetAddress.getByName(oscIP);
			sender = new OSCPortOut(ipAdress, oscSendPort);
		} catch (Exception e) {
            Log.i("osc", e.toString());
		}
        
        // init the parameters of the Faust object
        final Para parameters = f.initFaust();
        
        // layout parameters
        final int nbLayParams = parameters.getCntLay();
        SWIGTYPE_p_int layType = parameters.getTypeLay();
        SWIGTYPE_p_int labelLayPos = parameters.getLabelLayPos();
        String layLabels = parameters.getLabelLay();
        String[] groupLabels = new String[nbLayParams];
        
        // value parameters
        final int nbUIEl = parameters.getCntEl();
        final int nbParams = parameters.getCnt();
        SWIGTYPE_p_int UIElType = parameters.getTypeEl();
        final SWIGTYPE_p_int paramsTypes = parameters.getType();
        SWIGTYPE_p_int labelPos = parameters.getLabelPos();
        SWIGTYPE_p_float paramsInit = parameters.getInit();
        final SWIGTYPE_p_float paramsMin = parameters.getMin();
        final SWIGTYPE_p_float paramsMax = parameters.getMax();
        final SWIGTYPE_p_float paramsStep = parameters.getStep();
        String labels = parameters.getLabel();
        String[] paramLabel = new String[nbParams];
        String metadats = parameters.getMetadata();
        String[] metadatas = new String[nbParams];
        
        parVals = new float[nbParams];
        OSCval = new float[nbParams];
        
        // Initialisation of the accelerometer elements
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);
        mAccelx = 0.00f;
        mAccely = 0.00f;
        mAccelz = 0.00f;
        mAccelCurrent = SensorManager.GRAVITY_EARTH;
        mAccelLast = SensorManager.GRAVITY_EARTH;
        accel.focusOnSliderN = 0;
        accel.statu = new boolean [4];
        accel.popUp = new PopupWindow(this);
        accel.layout = new LinearLayout(this);
        
        // Declaring and initializing counters of UI elements
        int[] nElemType = new int [4];
        int[] elemCnt = new int [4];
        for(int j=0;j<4;j++){
        	nElemType[j] = 0;
        	elemCnt[j] = 0;
        }
        int i=0;
        
        // Counting UI elements
        for(int j=0;j<nbUIEl;j++){
        	if(o.intArray_getitem(UIElType, j)==1){
        		if(o.intArray_getitem(paramsTypes, i) == 0) nElemType[0] ++;
        		if(o.intArray_getitem(paramsTypes, i) == 1) nElemType[1] ++;
        		if(o.intArray_getitem(paramsTypes, i) == 2) nElemType[2] ++;
        		if(o.intArray_getitem(paramsTypes, i) == 3) nElemType[2] ++;
        		if(o.intArray_getitem(paramsTypes, i) == 4) nElemType[3] ++;
        		i++;
        	}
        }
        
        // Initializing UI elements
        UI.labels = new TextView[nbParams];
        UI.buttons = new Button [nElemType[0]];
        UI.checkBoxes = new CheckBox [nElemType[1]];
        UI.sliders = new SeekBar [nElemType[2]];
        UI.nEntries = new EditText [nElemType[3]];
        
        // reseting counters
        i=0;
        int y=0;
        int z=0;
        int oldGroupLevel = 0;
        int metIndex = 0, metIndexOld = 0;
        String OSCpath = "/";
        String OSCPathLev[] = new String[nbLayParams];
        
        // loop to create the UI in function of the specification contained in the Faust code
        
        try {
        	receiver = new OSCPortIn(oscReceiverPort);
    	
        for(int j=0;j<nbUIEl;j++){
        	if(o.intArray_getitem(UIElType, j)==0){
        		if(o.intArray_getitem(layType, y)==0 || o.intArray_getitem(layType, y)==1){
        			if(y==0) groupLabels[y] = layLabels.substring(0,o.intArray_getitem(labelLayPos, y));
        			else groupLabels[y] = layLabels.substring(o.intArray_getitem(labelLayPos, y-1-z),o.intArray_getitem(labelLayPos, y));
        			if(o.intArray_getitem(layType, y)==0) addVerticalGroup(100+y,groupLabels[y]);
        			if(o.intArray_getitem(layType, y)==1) addVerticalGroup(100+y,groupLabels[y]);
        			z = 0;
        		}
        		if(o.intArray_getitem(layType, y)==2){ 
        			closeGroup();
        			z++;
        		}
        		y++;
        	}
        	
        	if(o.intArray_getitem(UIElType, j)==1){
        		// extracting metadatas...
        		if(metadats.charAt(metIndex) != '%'){
        			metIndexOld = metIndex;
        			while(metadats.charAt(metIndex) != '*') metIndex++;
        		
        			metadatas[i] = metadats.substring(metIndexOld+1, metIndex);
        		}
        		else metadatas[i] = "0";
        		metIndex++;
        		
        		//if(metadatas[i].contains("accel")) System.out.println("Hey!");
        		//if(metadatas[i] != "0") System.out.println("Hey: " + metadatas[i]);
        		
        		// create an OSC address respecting the Faust standards
    			OSCpath = "/";
    			if(groupLevel>2) OSCPathLev[groupLevel-2] = groupLabels[y-1-z].replaceAll(" ","_");
    			OSCPathLev[0] = groupLabels[0].replaceAll(" ","_");
    			oldGroupLevel = groupLevel;
    			for(int lev=0;lev<=(groupLevel-2);lev++){
    				OSCpath += OSCPathLev[lev];
    				OSCpath += "/";
    			}
    			
        		if(i==0) paramLabel[i] = labels.substring(0,o.intArray_getitem(labelPos, i));
        		else paramLabel[i] = labels.substring(o.intArray_getitem(labelPos, i-1),o.intArray_getitem(labelPos, i));

        		if(o.intArray_getitem(paramsTypes, i) == 0){ 
        			OSCreceiver(receiver,OSCpath + paramLabel[i].replaceAll(" ","_"),i);
        			addButton(i,elemCnt[0],paramLabel[i],OSCpath + paramLabel[i].replaceAll(" ","_"));
        			elemCnt[0]++;
        		}
        		if(o.intArray_getitem(paramsTypes, i) == 1){ 
        			OSCreceiver(receiver,OSCpath + paramLabel[i].replaceAll(" ","_"),i);
        			addCheckButton(i,elemCnt[1],paramLabel[i],OSCpath + paramLabel[i].replaceAll(" ","_"));
        			elemCnt[1]++;
        		}
        		if(o.intArray_getitem(paramsTypes, i) == 2){ 
        			// create an OSC receiver for this parameter
        			OSCreceiver(receiver,OSCpath + paramLabel[i].replaceAll(" ","_"),i);
        			
        			addSeekBar(i,elemCnt[2],paramLabel[i],o.floatArray_getitem(paramsInit, i),
        				o.floatArray_getitem(paramsMin, i),o.floatArray_getitem(paramsMax, i),o.floatArray_getitem(paramsStep, i),OSCpath + paramLabel[i].replaceAll(" ","_"));
        			OSCreceiver(receiver,"/"+paramLabel[i].replaceAll(" ","_"),i);
        			elemCnt[2]++;
        			
        		}
        		if(o.intArray_getitem(paramsTypes, i) == 3){ 
        			// create an OSC receiver for this parameter
        			OSCreceiver(receiver,OSCpath + paramLabel[i].replaceAll(" ","_"),i);
        			
        			addSeekBar(i,elemCnt[2],paramLabel[i],o.floatArray_getitem(paramsInit, i),
            				o.floatArray_getitem(paramsMin, i),o.floatArray_getitem(paramsMax, i),o.floatArray_getitem(paramsStep, i),OSCpath + paramLabel[i].replaceAll(" ","_"));
        			elemCnt[2]++;
        		}
        		if(o.intArray_getitem(paramsTypes, i) == 4){ 
        			OSCreceiver(receiver,OSCpath + paramLabel[i].replaceAll(" ","_"),i);
        			addNentry(i,elemCnt[3],paramLabel[i],o.floatArray_getitem(paramsInit, i),
        				o.floatArray_getitem(paramsMin, i),o.floatArray_getitem(paramsMax, i),o.floatArray_getitem(paramsStep, i),OSCpath + paramLabel[i].replaceAll(" ","_"));
        			elemCnt[3]++;
        		}
        		i++;
        	}
        }
       
        
        // the accelerometer window is created and the default for its elements are set-up
        createAccelWindow(accel.statu,accel.popUp,accel.layout);
        accel.paramAccelState = new int [nbParams][3];
        float[] OSCvalOld = new float [nbParams];
        String metadataAccelVal;
        metaDatAccelVal = new float [nbParams][4];
        
        // TODO there should be a function for that...
        for(int j=0; j<nbParams; j++){ 
        	if(metadatas[j] != "0") {
        		if(metadatas[j].contains("accx")) {
        			accel.paramAccelState[j][0] = 1;
        			metadataAccelVal = metadatas[j].substring(metadatas[j].indexOf("accx;")+5);
        			for(int n=0; n<4; n++){
        				if(n<3){
        					metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal.substring(0,metadataAccelVal.indexOf(" ")));
        					metadataAccelVal = metadataAccelVal.substring(metadataAccelVal.indexOf(" ")+1);
        				}
        				else if(metadataAccelVal.contains("$"))metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal.substring(0,metadataAccelVal.indexOf("$")));
        				else metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal);
        			}
        			//Inverted?
        			if(metaDatAccelVal[j][0]<0) accel.paramAccelState[j][1] = -1;
        			else accel.paramAccelState[j][1] = 1;
        			//Sensibility
        			accel.paramAccelState[j][2] = (int) Math.abs(metaDatAccelVal[j][0]*100); 
        		}
        		else if(metadatas[j].contains("accy")){ 
        			accel.paramAccelState[j][0] = 2;
        			metadataAccelVal = metadatas[j].substring(metadatas[j].indexOf("accy;")+5);
        			for(int n=0; n<4; n++){
        				if(n<3){
        					metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal.substring(0,metadataAccelVal.indexOf(" ")));
        					metadataAccelVal = metadataAccelVal.substring(metadataAccelVal.indexOf(" ")+1);
        				}
        				else if(metadataAccelVal.contains("$"))metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal.substring(0,metadataAccelVal.indexOf("$")));
        				else metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal);
        			}
        			if(metaDatAccelVal[j][0]<0) accel.paramAccelState[j][1] = -1;
        			else accel.paramAccelState[j][1] = 1;
        			//Sensibility
        			accel.paramAccelState[j][2] = (int) Math.abs(metaDatAccelVal[j][0]*100); 
        		}
        		else if(metadatas[j].contains("accz")){ 
        			accel.paramAccelState[j][0] = 3;
        			metadataAccelVal = metadatas[j].substring(metadatas[j].indexOf("accz;")+5);
        			for(int n=0; n<4; n++){
        				if(n<3){
        					metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal.substring(0,metadataAccelVal.indexOf(" ")));
        					metadataAccelVal = metadataAccelVal.substring(metadataAccelVal.indexOf(" ")+1);
        				}
        				else if(metadataAccelVal.contains("$"))metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal.substring(0,metadataAccelVal.indexOf("$")));
        				else metaDatAccelVal[j][n] = Float.parseFloat(metadataAccelVal);
        			}
        			if(metaDatAccelVal[j][0]<0) accel.paramAccelState[j][1] = -1;
        			else accel.paramAccelState[j][1] = 1;
        			//Sensibility
        			accel.paramAccelState[j][2] = (int) Math.abs(metaDatAccelVal[j][0]*100); 
        		}
        		else accel.paramAccelState[j][0] = 0;
        	}
        	else{ 
        		accel.paramAccelState[j][0] = 0;
        		accel.paramAccelState[j][1] = 1;
        		accel.paramAccelState[j][2] = 100; 
        	}
        	//System.out.println("Here: " + accel.paramAccelState[j][0] + " " + accel.paramAccelState[j][1] + " " + accel.paramAccelState[j][2]);
        }
        
        // Initializing the variable for the accelerometer filter
        mAccelxDel = 0;
        mAccelxDel = 0;
        mAccelxDel = 0;
        
        
        // the main thread for DSP is created 
        thread = new Thread() {
			public void run() {
				setPriority(Thread.MAX_PRIORITY);
				
				float accelCurrentValue; // variable to store the value of the selected axis of the accelerometer
				
				f.startAudio(); 		// start the audio engine, etc. (C++ function)
				float old = 0.f; 		// here only for debugging
				
				float[] OSCvalOld = new float [nbParams];
				
				// processing loop
				while(on){
					SWIGTYPE_p_float paramValues = parameters.getZone();
					
					// counters for the different UI elements
					int[] elemCnt = new int [4];
					for(int j=0;j<4;j++) elemCnt[j] = 0;
					
					// if the accelerometer window is opened, the values of the parameter are updated
					if(accel.focusOnSliderN > 0){
						// X, Y or Z ?
						if(accel.statu[0]) accel.paramAccelState[accel.focusOnSliderN-1][0] = 1;
						else if(accel.statu[1]) accel.paramAccelState[accel.focusOnSliderN-1][0] = 2;
						else if(accel.statu[2]) accel.paramAccelState[accel.focusOnSliderN-1][0] = 3;
						else accel.paramAccelState[accel.focusOnSliderN-1][0] = 0;
						
						// reversed ?
						if(accel.statu[3]) accel.paramAccelState[accel.focusOnSliderN-1][1] = -1;
						else accel.paramAccelState[accel.focusOnSliderN-1][1] = 1;
						
						// sensibilty
						if(accel.sensibilityVal != 0) accel.paramAccelState[accel.focusOnSliderN-1][2] = accel.sensibilityVal;
					}
					
					// the values of the different parameters are sent to the audio process and are modified by the accelerometer
					for(int i=0;i<nbParams;i++){
						if(o.intArray_getitem(paramsTypes, i) == 0){
							if(OSCval[i] != OSCvalOld[i]){
								parVals[i] = OSCval[i];
								OSCvalOld[i] = OSCval[i];
							}
							elemCnt[0]++;
						}
						if(o.intArray_getitem(paramsTypes, i) == 1){
							if(OSCval[i] != OSCvalOld[i]){
								parVals[i] = OSCval[i];
								OSCvalOld[i] = OSCval[i];
								//if(OSCval[i] >= 1) UI.checkBoxes[elemCnt[1]].setChecked(true);
								//else UI.checkBoxes[elemCnt[1]].setChecked(false);
							}
							elemCnt[1]++;
						}
						if(o.intArray_getitem(paramsTypes, i) == 2 || o.intArray_getitem(paramsTypes, i) == 3){
							// X, Y, or Z?
							if(accel.paramAccelState[i][0] > 0) {
								
								if (accel.paramAccelState[i][0] == 1) {
									
									if(metaDatAccelVal[i][3] > 0) accelCurrentValue = (mAccelx + mAccelxDel)*0.5f;
									else accelCurrentValue = mAccelx;
								
								} else if (accel.paramAccelState[i][0] == 2) {
								
									if(metaDatAccelVal[i][3] > 0) accelCurrentValue = (mAccely + mAccelyDel)*0.5f;
									else accelCurrentValue = mAccely;
								
								} else if (accel.paramAccelState[i][0] == 3) {
								
									if(metaDatAccelVal[i][3] > 0) accelCurrentValue = (mAccelz + mAccelzDel)*0.5f;
									else accelCurrentValue = mAccelz;
								
								} else {
								
									accelCurrentValue = 0;
									
								}
								
								accelCurrentValue = mapping3( 	accelCurrentValue*metaDatAccelVal[i][0], 
																-9.81f, metaDatAccelVal[i][1], 9.81f, 
																o.floatArray_getitem(paramsMin, i), metaDatAccelVal[i][2], o.floatArray_getitem(paramsMax, i) );
								
								UI.sliders[elemCnt[2]].setProgress(Math.round((accelCurrentValue-o.floatArray_getitem(paramsMin, i))*(1/o.floatArray_getitem(paramsStep, i))));	
								
								parVals[i] = accelCurrentValue;
								
								// updating the values for the accelerometer filter
								mAccelxDel = mAccelx;
								mAccelyDel = mAccely;
								mAccelzDel = mAccelz;
							}
							// OSC messages change parameters values TODO: for now, only sliders can be controlled via OSC
							if(OSCval[i] != OSCvalOld[i]){ 
								UI.sliders[elemCnt[2]].setProgress(Math.round((OSCval[i]-o.floatArray_getitem(paramsMin, i))*(1/o.floatArray_getitem(paramsStep, i))));
								parVals[i] = OSCval[i];
								OSCvalOld[i] = OSCval[i];
							}
							elemCnt[2]++;
						}
						if(o.intArray_getitem(paramsTypes, i) == 4){
							if(OSCval[i] != OSCvalOld[i]){
								//UI.nEntries[elemCnt[3]].setText(Float.toString(OSCval[i]));
								parVals[i] = OSCval[i];
								OSCvalOld[i] = OSCval[i];
							}
							elemCnt[3]++;
						}
						o.floatArray_setitem(paramValues, i, parVals[i]);
					}
					f.setParam(paramValues);
					
					// the audio frame is processed
					f.processDSP();
				}
				
				// when the app closes, the audio process is killed and the OSC connection is closed
				f.stopAudio();
				receiver.stopListening();
				receiver.close();
			}
		};
		thread.start();
    } catch (SocketException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
		
	// Keep screen on in order to keep accelerometers action on
	getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }
    
    @Override
	protected void onPause() {
		mSensorManager.unregisterListener(mSensorListener);
		super.onPause();
		sender.close();
	}
    
    @Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_faust_app, menu);
		return true;
	}
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
        	case R.id.settings:
        		Intent settingsIntent = new Intent(this, Settings.class);
            	startActivity(settingsIntent);
        		return true;
        	case R.id.help:
        		Intent helpIntent = new Intent(this, DisplayWelcomeActivity.class);
            	startActivity(helpIntent);
        		return true;
        	case R.id.about:
        		Intent aboutIntent = new Intent(this, About.class);
            	startActivity(aboutIntent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
    
    public void onDestroy(){
    	super.onDestroy();
    	//receiver.close();
    	sender.close();
    	on = false;
    	try {
			thread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
    	thread = null;
    }
}
