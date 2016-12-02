package com.faust;

import android.content.Context;
import android.graphics.Color;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.LinearLayout;

class PushButton{
	int id = 0;
	String address = "";
	Button button;
	
	/*
	 * The constructor.
	 * addr: the tree address of the parameter controlled by the slider
	 * currentParameterID: the current parameter id in the parameters tree
	 * width: width of the view in pxs
	 * backgroundColor: grey level of the background of the view (0-255)
	 * label: the parameter's name
	 */
	public PushButton(Context c, String addr, int currentParameterID,
			int width, int backgroundColor, String label){
		id = currentParameterID;
		address = addr;
		
		button = new Button(c);
		button.setLayoutParams(new ViewGroup.LayoutParams(
				width, ViewGroup.LayoutParams.WRAP_CONTENT));
		button.setText(label);
		button.setTextColor(Color.WHITE);
	}
	
	/*
	 * Add the checkbox to group
	 */
	public void addTo(LinearLayout group){
		group.addView(button);
	}
	
	/*
	 * Set the checkbox's listeners
	 */
	public void linkTo(final ParametersInfo parametersInfo){
		button.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                	parametersInfo.values[id] = 1.f;
                	FaustActivity.dspFaust.setParamValue(address, parametersInfo.values[id]);
                } else if (event.getAction() == MotionEvent.ACTION_UP || !inViewBounds(v, event)) {
                	parametersInfo.values[id] = 0.f;
                	FaustActivity.dspFaust.setParamValue(address, parametersInfo.values[id]);
                }
	          	return true;
            }
        });
	}
	
	/*
	 * Test if event happened within view
	 */
	private boolean inViewBounds(View v, MotionEvent event){
		int vWidth = v.getWidth();
		int vHeight = v.getHeight();
		if(event.getY() >= 0 && event.getY() <= vHeight && event.getX() >= 0 && event.getX() <= vWidth)
			return true;
		else return false;
	}
}
