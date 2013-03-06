/*
TODO header needed
*/

package com.faustApp;

import faust_dsp.Para;
import faust_dsp.SWIGTYPE_p_float;
import faust_dsp.SWIGTYPE_p_int;
import faust_dsp.faust;
import faust_dsp.faust_dsp;
import faust_dsp.faust_dspJNI;
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
import android.view.View;
import android.view.MotionEvent;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import java.lang.String;

public class faustApp extends Activity {
    /** Called when the activity is first created. */
	Thread thread;
	float[] parVals = new float[30]; // this should be allocated dynamically TODO
	
	faust f = new faust();
	boolean on = true;
	faust_dsp o = new faust_dsp();
	
	private void addButton(final int n, final String label){
		Button b = new Button(this);
        LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        b.setText(label);
        b.setTextColor(Color.BLACK);
        b.setLayoutParams(params);
        LinearLayout ll = (LinearLayout) findViewById(R.id.the_layout);
        ll.addView(b);
        
        b.setOnTouchListener(new OnTouchListener() {
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
	
	private void addNentry(final int n, final String label, final float init, final float min, final float max, final float step){
		// slider's label and value display
		final TextView t = new TextView(this);
		LayoutParams paramsText = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		t.setLayoutParams(paramsText);
		t.setText(label+":");
		LinearLayout ll = (LinearLayout) findViewById(R.id.the_layout);
		ll.addView(t);
				
		final EditText v = new EditText(this);
		LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		v.setLayoutParams(params);
		v.setInputType(InputType.TYPE_CLASS_NUMBER|InputType.TYPE_NUMBER_FLAG_DECIMAL);
		v.setText(Float.toString(init));
		this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
		ll.addView(v);
		
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
		       String value = v.getText().toString();
		       if(isNumeric(value)) parVals[20] = Float.parseFloat(value);
		    }
		};
		v.addTextChangedListener(textWatcher);
	}
	
	private void addGroup(final int level, final String label){
		TextView t = new TextView(this);
		LayoutParams paramsText = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		t.setLayoutParams(paramsText);
		t.setText(label);
		t.setTextSize(24.f);
		LinearLayout llText = (LinearLayout) findViewById(R.id.the_layout);
		llText.addView(t);
	}
	
	private void addSeekBar(final int n, final String label, final float init, final float min, final float max, final float step) {
		// slider's label and value display
		final TextView t = new TextView(this);
		LayoutParams paramsText = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		t.setLayoutParams(paramsText);
		t.setText(label+": " + Float.toString(init));
		LinearLayout llText = (LinearLayout) findViewById(R.id.the_layout);
		llText.addView(t);
		
		SeekBar s = new SeekBar(this);
		LayoutParams paramsSlider = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		s.setLayoutParams(paramsSlider);
		s.setPadding(20, 8, 8, 20);
		parVals[n] = init;
		int range = Math.round((max-min)*(1/step));
		s.setMax(range);
		if(init<=0 && min<0) s.setProgress(Math.round((init-min)*(1/step)));
		else s.setProgress(Math.round((init+min)*(1/step)));
		LinearLayout llSlider = (LinearLayout) findViewById(R.id.the_layout);
		llSlider.addView(s);
		
		OnSeekBarChangeListener listener = new OnSeekBarChangeListener() {
			public void onStopTrackingTouch(SeekBar seekBar) { }
			public void onStartTrackingTouch(SeekBar seekBar) { }
			public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
	          	if(fromUser){ 
	          		parVals[n] = (progress*step) + min;
	          		t.setText(label+": " + Float.toString(parVals[n]));
	          	}
	          	}
	    };
	    s.setOnSeekBarChangeListener(listener);
	}
	
	//*******************************
	// test accel
	//*******************************
	/*
	private SensorManager mSensorManager;
	private float mAccel; // acceleration apart from gravity
	private float mAccelCurrent; // current acceleration including gravity
	private float mAccelLast; // last acceleration including gravity

	private final SensorEventListener mSensorListener = new SensorEventListener() {
		public void onSensorChanged(SensorEvent se) {
			float x = se.values[0];
			float y = se.values[1];
			float z = se.values[2];
			mAccelLast = mAccelCurrent;
			mAccelCurrent = (float) Math.sqrt((double) (x*x + y*y + z*z));
			mAccel = x;
			//float delta = mAccelCurrent - mAccelLast;
			//mAccel = mAccel * 0.9f + delta; // perform low-cut filter
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
	*/
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        final Para parameters = f.initFaust();
        
        // layout parameters
        final int nbLayParams = parameters.getCntLay();
        String layLabels = parameters.getLabel();
        String[] paramLayLabel = new String[nbLayParams];
        
        // value parameters
        final int nbParams = parameters.getCnt();
        SWIGTYPE_p_int paramsTypes = parameters.getType();
        SWIGTYPE_p_int paramLayoutEl = parameters.getLayoutEl();
        SWIGTYPE_p_int labelPos = parameters.getLabelPos();
        SWIGTYPE_p_float paramsInit = parameters.getInit();
        SWIGTYPE_p_float paramsMin = parameters.getMin();
        SWIGTYPE_p_float paramsMax = parameters.getMax();
        SWIGTYPE_p_float paramsStep = parameters.getStep();
        String labels = parameters.getLabel();
        String[] paramLabel = new String[nbParams];
        
        TextView appName = (TextView) findViewById(R.id.app_name);
        appName.setText("Faust App Interface");
        
        //addGroup(0,"First Group");
        //addNentry(1,"tt",15f,0f,100f,0.01f);
        
        //************************************
        // Accel test
        //************************************
        /*
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
        mAccel = 0.00f;
        mAccelCurrent = SensorManager.GRAVITY_EARTH;
        mAccelLast = SensorManager.GRAVITY_EARTH;
        */
        
        
        for(int i=0;i<nbParams;i++){
        	if(i==0) paramLabel[i] = labels.substring(0,o.intArray_getitem(labelPos, i));
        	else paramLabel[i] = labels.substring(o.intArray_getitem(labelPos, i-1),o.intArray_getitem(labelPos, i));
        	
        	//System.out.println("Hello: " + o.intArray_getitem(paramLayoutEl, i));
        	//System.out.println("Hello: " + mAccel);
        	
        	if(o.intArray_getitem(paramsTypes, i) == 0) addButton(i,paramLabel[i]);
        	if(o.intArray_getitem(paramsTypes, i) == 2) addSeekBar(i,paramLabel[i],o.floatArray_getitem(paramsInit, i),
        			o.floatArray_getitem(paramsMin, i),o.floatArray_getitem(paramsMax, i),o.floatArray_getitem(paramsStep, i));
        	if(o.intArray_getitem(paramsTypes, i) == 3) addSeekBar(i,paramLabel[i],o.floatArray_getitem(paramsInit, i),
        			o.floatArray_getitem(paramsMin, i),o.floatArray_getitem(paramsMax, i),o.floatArray_getitem(paramsStep, i));
		}
        
        //System.out.println("Hello: " + labels);
        
        thread = new Thread() {
			public void run() {
				setPriority(Thread.MAX_PRIORITY);
				f.startAudio();
				float old = 0;
				while(on){
					SWIGTYPE_p_float paramValues = parameters.getZone();
					
					if(old != parVals[20]) System.out.println("Hello: " + parVals[20]);
					old = parVals[20];
					/*
					if(old != mAccel) System.out.println("Hello: " + mAccel);
					old = mAccel;
					*/
					
					for(int i=0;i<nbParams;i++){
						o.floatArray_setitem(paramValues, i, parVals[i]);
					}
					
					f.setParam(paramValues);
					f.processDSP();
				}
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
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	thread = null;
    	
    }
}
