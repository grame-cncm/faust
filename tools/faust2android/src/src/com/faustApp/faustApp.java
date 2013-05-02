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

package com.faustApp;

import faust_dsp.Para;
import faust_dsp.SWIGTYPE_p_float;
import faust_dsp.SWIGTYPE_p_int;
import faust_dsp.faust;
import faust_dsp.faust_dsp;
import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.RectShape;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.text.Editable;
import android.text.InputType;
import android.text.TextWatcher;
import android.view.Gravity;
import android.view.View;
import android.view.MotionEvent;
import android.view.View.OnClickListener;
import android.view.View.OnLongClickListener;
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
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import java.lang.String;

public class faustApp extends Activity {
	
	// global elements
	Thread thread; // main thread for DSP and stuff
	float[] parVals; // values given by the different elements of the UI
	boolean on = true; // process on/off
	
	// C++ components
	faust f = new faust();
	faust_dsp o = new faust_dsp();
	
	// UI layouts
	LinearLayout[] currentGroup; // refers to the current group in the UI hierarchy
	int groupLevel = 0;
	
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
        assignation.setText("Assignation: ");
        
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
        
        layButtonsAccel.addView(assignation);
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
	private void addButton(final int n, final int m, final String label){ 
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
                return true;
            }
        });
	}
	
	// add a check box to the UI
	private void addCheckButton(final int n, final int m, final String label){
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
        	}
        });
	}
	
	// add a numerical entry to the UI
	private void addNentry(final int n, final int m, final String label, final float init, final float min, final float max, final float step){
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
		       }
		    }
		};
		UI.nEntries[m].addTextChangedListener(textWatcher);
	}
	
	// add a slider to the UI
	private void addSeekBar(final int n, final int m, final String label, final float init, final float min, final float max, final float step) {
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
                    accel.popUp.update(0, 0, currentGroup[0].getWidth()-45, 300);
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
	          		UI.labels[n].setText(label+": " + Float.toString(parVals[n]));
	          	}
	    };
	    UI.sliders[m].setOnSeekBarChangeListener(listener);
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
	private float mAccelCurrent; // current acceleration including gravity
	private float mAccelLast; // last acceleration including gravity

	private final SensorEventListener mSensorListener = new SensorEventListener() {
		public void onSensorChanged(SensorEvent se) {
			mAccelx = se.values[0];
			mAccely = se.values[1];
			mAccelz = se.values[2];
		}
	    public void onAccuracyChanged(Sensor sensor, int accuracy) {
	    }
	};

	
	
	@Override
	protected void onResume() {
		super.onResume();
	    mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
	}
	
	@Override
	protected void onPause() {
		mSensorManager.unregisterListener(mSensorListener);
	    super.onPause();
	}
	
	/*
	 * Main view
	 */
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
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
        
        parVals = new float[nbParams];
        
        // Initialisation of the accelerometer elements
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
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
        
        // loop to create the UI in function of the specification contained in the Faust code
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
        		if(i==0) paramLabel[i] = labels.substring(0,o.intArray_getitem(labelPos, i));
        		else paramLabel[i] = labels.substring(o.intArray_getitem(labelPos, i-1),o.intArray_getitem(labelPos, i));

        		if(o.intArray_getitem(paramsTypes, i) == 0){ 
        			addButton(i,elemCnt[0],paramLabel[i]);
        			elemCnt[0]++;
        		}
        		if(o.intArray_getitem(paramsTypes, i) == 1){ 
        			addCheckButton(i,elemCnt[1],paramLabel[i]);
        			elemCnt[1]++;
        		}
        		if(o.intArray_getitem(paramsTypes, i) == 2){ 
        			addSeekBar(i,elemCnt[2],paramLabel[i],o.floatArray_getitem(paramsInit, i),
        				o.floatArray_getitem(paramsMin, i),o.floatArray_getitem(paramsMax, i),o.floatArray_getitem(paramsStep, i));
        			elemCnt[2]++;
        		}
        		if(o.intArray_getitem(paramsTypes, i) == 3){ 
        			addSeekBar(i,elemCnt[2],paramLabel[i],o.floatArray_getitem(paramsInit, i),
        				o.floatArray_getitem(paramsMin, i),o.floatArray_getitem(paramsMax, i),o.floatArray_getitem(paramsStep, i));
        			elemCnt[2]++;
        		}
        		if(o.intArray_getitem(paramsTypes, i) == 4){ 
        			addNentry(i,elemCnt[3],paramLabel[i],o.floatArray_getitem(paramsInit, i),
        				o.floatArray_getitem(paramsMin, i),o.floatArray_getitem(paramsMax, i),o.floatArray_getitem(paramsStep, i));
        			elemCnt[3]++;
        		}
        		i++;
        	}
        }
        
        // the accelerometer window is created and the default for its elements are set-up
        createAccelWindow(accel.statu,accel.popUp,accel.layout);
        accel.paramAccelState = new int [nbParams][3];
        for(int j=0; j<nbParams; j++){ 
        	accel.paramAccelState[j][0] = 0;
        	accel.paramAccelState[j][1] = 1;
        	accel.paramAccelState[j][2] = 10;
        }
        
        // the main thread for DSP is created 
        thread = new Thread() {
			public void run() {
				setPriority(Thread.MAX_PRIORITY);
				
				float accelCurrentValue; // variable to store the value of the selected axis of the accelerometer
				
				f.startAudio(); // start the audio engine, etc. (C++ function)
				int old = 0; // here only for debugging
				
				// processing loop
				while(on){
					SWIGTYPE_p_float paramValues = parameters.getZone();

					/*
					if(old != accelSensibility) System.out.println("Hello: " + accelSensibility);
					old = accelSensibility;
					*/
					
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
						
						// sensibilty
						if(accel.sensibilityVal != 0) accel.paramAccelState[accel.focusOnSliderN-1][2] = accel.sensibilityVal;
					}
					
					// the values of the different parameters are sent to the audio process and are modified by the accelerometer
					for(int i=0;i<nbParams;i++){
						if(o.intArray_getitem(paramsTypes, i) == 2 || o.intArray_getitem(paramsTypes, i) == 3){
							// X, Y, or Z?
							if(accel.paramAccelState[i][0] > 0){
								if (accel.paramAccelState[i][0] == 1){
									accelCurrentValue = mAccelx;
								}
								else if (accel.paramAccelState[i][0] == 2){
									accelCurrentValue = mAccely;
								}
								else if (accel.paramAccelState[i][0] == 3){
									accelCurrentValue = mAccelz;
								}
								else accelCurrentValue = 0;
								
								// parameter value is modified by the accelerometer
								if(o.floatArray_getitem(paramsMin, i)<0) accelCurrentValue = ((accelCurrentValue*((float) accel.paramAccelState[i][2]/10)*accel.paramAccelState[i][1]/10)+1)/2*(o.floatArray_getitem(paramsMax, i)+o.floatArray_getitem(paramsMin, i));
								else accelCurrentValue = ((accelCurrentValue*((float) accel.paramAccelState[i][2]/10)*accel.paramAccelState[i][1]/10)+1)/2*(o.floatArray_getitem(paramsMax, i)-o.floatArray_getitem(paramsMin, i));
								UI.sliders[elemCnt[2]].setProgress(Math.round((accelCurrentValue-o.floatArray_getitem(paramsMin, i))*(1/o.floatArray_getitem(paramsStep, i))));	
								parVals[i] = accelCurrentValue;
							}
							elemCnt[2]++;
						}
						o.floatArray_setitem(paramValues, i, parVals[i]);
					}
					f.setParam(paramValues);
					
					// the audio frame is processed
					f.processDSP();
				}
				
				// when the app closes, the audio process is killed
				f.stopAudio();
			}
		};
		thread.start();   
    }
    
    public void onDestroy(){
    	
    	super.onDestroy();
    	on = false;
    	try {
			thread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
    	thread = null;
    	
    }
}
