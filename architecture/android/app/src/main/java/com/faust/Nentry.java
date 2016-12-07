package com.faust;

import android.content.Context;
import android.graphics.Color;
import android.text.Editable;
import android.text.InputType;
import android.text.TextWatcher;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnLongClickListener;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import android.util.Log;

class Nentry{
	float min = 0.0f, max = 100.0f, step = 1.0f, lastvalue = Float.MAX_VALUE;
   int id = 0;
	String  address = "";
	LinearLayout frame, nentryLayout, localVerticalGroup;
	EditText nentry;
	TextView textLabel;
	
	/*
	 * The constructor.
	 * addr: the tree address of the parameter controlled by the slider
	 * currentParameterID: the current parameter id in the parameters tree
	 * width: width of the view in pxs
	 * backgroundColor: grey level of the background of the view (0-255)
	 * padding: padding of the view in pxs
	 */
	public Nentry(Context c, String addr, int currentParameterID, 
			int width, int backgroundColor, boolean visibility) {
		id = currentParameterID;
		address = addr;
		
		nentry = new EditText(c);
		nentry.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		nentry.setInputType(InputType.TYPE_CLASS_NUMBER|InputType.TYPE_NUMBER_FLAG_DECIMAL|InputType.TYPE_NUMBER_FLAG_SIGNED);
		nentry.setGravity(Gravity.CENTER);
		
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
		
		if(visibility){
			localVerticalGroup.addView(nentry);
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
	}
	
	/*
	 * Set the nentry's value
	 */
    public void setValue(float theValue){
       if (theValue != lastvalue) {
            if ((theValue - (int)theValue) != 0) {
                nentry.setText(Float.toString(theValue));
            } else {
                nentry.setText(String.valueOf((int)theValue));
            }
            lastvalue = theValue;
        }
    }
	
	/*
	 * Set the value of the slider as a number between 0 and 1
	 */
	public void setNormizedValue(float theValue){
		setValue((max-min)*theValue + min);
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
	public void linkTo(final ParametersInfo parametersInfo, final ConfigWindow parametersWindow){
		localVerticalGroup.setOnLongClickListener(new OnLongClickListener(){
			public boolean onLongClick (View v){
				if(!parametersInfo.locked) parametersWindow.showWindow(parametersInfo, id);
				return true;
			}
		});
		
		nentry.addTextChangedListener(new TextWatcher() { 
		    @Override
		    public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
		    }
		    @Override
		    public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
               if (nentry.getText().length() > 0) {
                    nentry.setSelection(nentry.getText().length());
                }
            }
		    @Override
		    public void afterTextChanged(Editable editable) {
                String value = nentry.getText().toString();
                if (nentry.getText().length() == 0) return;
                
                try {
                    float numValue = Float.parseFloat(value);
                    
                    if (numValue >= min && numValue <= max){
                        parametersInfo.values[id] = numValue;
                        FaustActivity.dspFaust.setParamValue(address, parametersInfo.values[id]);
                    } else if(numValue < min) {
                        lastvalue = Float.MAX_VALUE;
                        setValue(min);
                    }  else if(numValue > max) {
                        lastvalue = Float.MAX_VALUE;
                        setValue(max);
                    }
                    
                } catch(NumberFormatException nfe) {
                    Log.i("FaustJava", "NumberFormatException ");
                }
            }
		});
	}
}
