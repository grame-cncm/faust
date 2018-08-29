package com.faust;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.content.ContextCompat;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;

class Radio{
	int ID = 0;
	float[] values;
	String address = "";
	RadioGroup radio;
	LinearLayout frame, localVerticalGroup;
	TextView textLabel;
	
	/*
	 * The constructor.
	 * addr: the tree address of the parameter controlled by the slider
	 * currentParameterID: the current parameter id in the parameters tree
	 * width: width of the view in pxs
	 * backgroundColor: grey level of the background of the view (0-255)
	 */
	public Radio(Context c, String addr, int currentParameterID,
			int width, int backgroundColor, String parsedParameters, 
			int orientation, int init, boolean visibility){
		ID = currentParameterID;
		address = addr;
		
		radio = new RadioGroup(c);
		radio.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        if (orientation == 0)
            radio.setOrientation(LinearLayout.VERTICAL);
        else
            radio.setOrientation(LinearLayout.HORIZONTAL);
		
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
		
		textLabel = new TextView(c);
		textLabel.setGravity(Gravity.CENTER);
		
		int length = parsedParameters.length();
		int nElements = countStringOccurrences(parsedParameters,";")+1;
		values = new float[nElements];
		// a menu item with a value assigned to it is created for each element of the array
		for (int i=0; i<nElements; i++) {
			String parameterName = parsedParameters.substring(1, parsedParameters.indexOf(":") - 1);
            if (parsedParameters.indexOf(";") != -1) {
                values[i] = Float.valueOf(parsedParameters.substring(parsedParameters.indexOf(":")+1, parsedParameters.indexOf(";")));
            } else {
                values[i] = Float.valueOf(parsedParameters.substring(parsedParameters.indexOf(":")+1));
            }
			parsedParameters = parsedParameters.substring(parsedParameters.indexOf(";") + 1, length);
			length = parsedParameters.length();
			
			RadioButton button = new RadioButton(c);
			button.setText(parameterName);
			button.setTextColor(ContextCompat.getColor(c,R.color.progress_gray));
			button.setId(i);
			if (init == i) {
				button.setChecked(true);
				FaustActivity.dspFaust.setParamValue(address, values[i]);
			}
			radio.addView(button);
		}
		if (visibility) {
            localVerticalGroup.addView(textLabel);
            localVerticalGroup.addView(radio);
            frame.addView(localVerticalGroup);
        }
	}
	
	public void setLabel(String label){
		textLabel.setText(label);
	}
	
	public void addTo(LinearLayout group){
		group.addView(frame);
	}
	
	public void linkTo(final ParametersInfo parametersInfo){
		radio.setOnCheckedChangeListener(new OnCheckedChangeListener() 
	    {
	        public void onCheckedChanged(RadioGroup group, int checkedId) {
	        	parametersInfo.values[ID] = (float) checkedId;
				FaustActivity.dspFaust.setParamValue(address, values[checkedId]);
	        }
	    });
	}
	
	private int countStringOccurrences(String input, String pattern){
		int lastIndex = 0, count = 0;
		while(lastIndex != -1){
			lastIndex = input.indexOf(pattern,lastIndex);
			if( lastIndex != -1){
				count ++;
				lastIndex += pattern.length();
			}
		}
		return count;
	}
}
