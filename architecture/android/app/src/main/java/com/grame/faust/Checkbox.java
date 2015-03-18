package com.grame.faust;

import com.grame.dsp_faust.dsp_faust;

import android.content.Context;
import android.graphics.Color;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.LinearLayout;

class Checkbox{
	int id = 0;
	String address = "";
	LinearLayout frame, localVerticalGroup;
	CheckBox checkbox;
	
	/*
	 * The constructor.
	 * addr: the tree address of the parameter controlled by the slider
	 * currentParameterID: the current parameter id in the parameters tree
	 * width: width of the view in pxs
	 * backgroundColor: grey level of the background of the view (0-255)
	 * label: the parameter's name
	 */
	public Checkbox(Context c, String addr, int currentParameterID,
			int width, int height, int backgroundColor, String label){
		id = currentParameterID;
		address = addr;
		
		checkbox = new CheckBox(c);
		checkbox.setGravity(Gravity.CENTER);
		checkbox.setText(label);
		
		frame = new LinearLayout(c);
		frame.setLayoutParams(new ViewGroup.LayoutParams(
				width, ViewGroup.LayoutParams.WRAP_CONTENT));
		frame.setOrientation(LinearLayout.VERTICAL);
		frame.setBackgroundColor(Color.rgb(backgroundColor, 
				backgroundColor, backgroundColor));
		frame.setPadding(2,2,2,2);
		
		localVerticalGroup = new LinearLayout(c);
		localVerticalGroup.setOrientation(LinearLayout.VERTICAL);
		localVerticalGroup.setGravity(Gravity.CENTER);
		localVerticalGroup.setBackgroundColor(Color.rgb(backgroundColor+15, 
				backgroundColor+15, backgroundColor+15));
		
		localVerticalGroup.addView(checkbox);
	    frame.addView(localVerticalGroup);
	}
	
	public void setStatus(float value){
		if(value == 0.0f) checkbox.setChecked(false);
		else if(value == 1.0f) checkbox.setChecked(true);
	}
	
	/*
	 * Add the checkbox to group
	 */
	public void addTo(LinearLayout group){
		group.addView(frame);
	}
	
	/*
	 * Set the checkbox's listeners
	 */
	public void linkTo(final ParametersInfo parametersInfo){
		checkbox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
        	@Override
        	public void onCheckedChanged(CompoundButton buttonView,boolean isChecked) {
        		if (isChecked) parametersInfo.values[id] = 1.f;
        		else parametersInfo.values[id] = 0.f;
        		dsp_faust.setParam(address, parametersInfo.values[id]);
        	}
        });
	}
}