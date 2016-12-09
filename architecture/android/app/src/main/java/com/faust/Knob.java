package com.faust;

import com.triggertrap.seekarc.SeekArc;
import com.triggertrap.seekarc.SeekArc.OnSeekArcChangeListener;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Point;
import android.view.Display;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.View.OnLongClickListener;
import android.widget.FrameLayout;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;
import android.widget.TextView;

/*
 * Create a knob. 
 */

class Knob {
	float min = 0.0f, max = 100.0f, step = 1.0f;
	int id = 0;
	String decimalsDisplay = "", address = "";
	FrameLayout knobLayout;
	LinearLayout frame, localVerticalGroup;
	SeekArc knob;
	TextView textValue, textLabel;
	Point size;
	
	/*
	 * The constructor.
	 * addr: the tree address of the parameter controlled by the slider
	 * currentParameterID: the current parameter id in the parameters tree
	 * width: width of the view in pxs
	 * backgroundColor: grey level of the background of the view (0-255)
	 */
	public Knob(Context c, String addr, int currentParameterID,
			int width, int backgroundColor, int padding, boolean visibility) {
		WindowManager wm = (WindowManager) c.getSystemService(Context.WINDOW_SERVICE);
		Display display = wm.getDefaultDisplay();
		size = new Point();
		display.getSize(size);
		
		id = currentParameterID;
		address = addr;
		
		knob = new SeekArc(c);
		knob.setPadding(padding, padding, padding, padding);
		knob.setRotation(180);
		knob.setStartAngle(30);
		knob.setSweepAngle(300);
		knob.setTouchInSide(true);
		
		frame = new LinearLayout(c);
		frame.setLayoutParams(new ViewGroup.LayoutParams(
				width, ViewGroup.LayoutParams.WRAP_CONTENT));
		frame.setOrientation(LinearLayout.VERTICAL);
		frame.setBackgroundColor(Color.rgb(backgroundColor, 
				backgroundColor, backgroundColor));
		frame.setPadding(2,2,2,2);
		
		knobLayout = new FrameLayout(c);
		knobLayout.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT, width));
		
		localVerticalGroup = new LinearLayout(c);
		localVerticalGroup.setOrientation(LinearLayout.VERTICAL);
		//localVerticalGroup.setGravity(Gravity.CENTER);
		localVerticalGroup.setBackgroundColor(Color.rgb(backgroundColor+15, 
				backgroundColor+15, backgroundColor+15));
		
		textLabel = new TextView(c);
		textLabel.setGravity(Gravity.CENTER);
		
		textValue = new TextView(c);
		textValue.setGravity(Gravity.CENTER);
		
		if (visibility) {
			knobLayout.addView(textValue);
			knobLayout.addView(knob);
			localVerticalGroup.addView(knobLayout);
			localVerticalGroup.addView(textLabel);
			frame.addView(localVerticalGroup);
		}
	}
	
	/*
	 * Set the slider parameters
	 * label: the name of the parameter
	 * minimum: the slider's minimum value
	 * maximum: the slider's maximum value
	 * stp: the slider's step
	 */
	public void setParams(String label, float minimum, float maximum, float stp){
		textLabel.setText(label);
		min = minimum;
		max = maximum;
		step = stp;
		int decimals = 0;
		if(step>=1) decimals = 1;
		else if(step<1 && step>=0.1) decimals = 1;
		else decimals = 2;
		decimalsDisplay = "%."+decimals+"f";
	}
	
	/*
	 * Set the value displayed next to the slider
	 */
	public void setDisplayedValue(float theValue){
		textValue.setText(String.format(decimalsDisplay, theValue));
	}
	
	/*
	 * Set the slider's value
	 */
	public void setValue(float theValue){
		// the initial value of the knob is set (SeekArc's range is 0-100)
		knob.setProgress(Math.round(((theValue-min)*100)/(max-min)));
		setDisplayedValue(theValue);
	}
	
	/*
	 * Set the value of the slider as a number between 0 and 1
	 */
	public void setNormizedValue(float theValue){
		knob.setProgress(Math.round(theValue*100));
	}
	
	/*
	 * Add the slider to group
	 */
	public void addTo(LinearLayout group){
		group.addView(frame);
	}
	
	/*
	 * Set the slider's listeners
	 */
	public void linkTo(final ParametersInfo parametersInfo, final ConfigWindow parametersWindow, final HorizontalScrollView horizontalScroll){
		localVerticalGroup.setOnLongClickListener(new OnLongClickListener(){
			public boolean onLongClick (View v){
				if(!parametersInfo.locked) parametersWindow.showWindow(parametersInfo, id);
				return true;
			}
		});
		
		knob.setOnSeekArcChangeListener( new OnSeekArcChangeListener() {
			public void onStopTrackingTouch(SeekArc seekArc) {
				parametersInfo.accgyrItemFocus[id] = 0;
			}
			public void onStartTrackingTouch(SeekArc seekArc) {
				parametersInfo.accgyrItemFocus[id] = 1;
			}
			public void onProgressChanged(SeekArc seekArc, int progress, boolean fromUser) {
				parametersInfo.values[id] = (float) progress*0.01f*(max-min) + min;
				FaustActivity.dspFaust.setParamValue(address, parametersInfo.values[id]);
				setDisplayedValue(parametersInfo.values[id]);
	          }
	    });
		
		/*
		knob.setOnTouchListener(new OnTouchListener()
	    {
	        public boolean onTouch(final View view, final MotionEvent event)
	        {
	          if (event.getAction() == MotionEvent.ACTION_DOWN || event.getAction() == MotionEvent.ACTION_MOVE)
	            horizontalScroll.requestDisallowInterceptTouchEvent(true);
	          return false;
	        }
	    });
	    */
	}
}
