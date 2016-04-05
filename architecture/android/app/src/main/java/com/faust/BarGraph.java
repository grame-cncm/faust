package com.faust;

import android.content.Context;
import android.graphics.Color;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnLongClickListener;
import android.view.View.OnTouchListener;

import android.util.AttributeSet;
import android.widget.ProgressBar;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

import android.util.Log;

class BarGraph {
    int id = 0;
	float min = 0.0f, max = 100.0f;
    LinearLayout barLayout;
    String address = "";
    LinearLayout frame, localVerticalGroup;
    ProgressBar bar;
	
	public BarGraph(Context c, String addr, int currentParameterID,  AttributeSet attrs, int defStyle, int width, int backgroundColor, boolean visibility) {
	       
        id = currentParameterID;
        address = addr;
        
        bar = new ProgressBar(c, attrs, defStyle);
        bar.setMax(1000);
        //bar.setLayoutParams(new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        bar.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,100));
        
        frame = new LinearLayout(c);
        frame.setLayoutParams(new ViewGroup.LayoutParams(width, ViewGroup.LayoutParams.WRAP_CONTENT));
        frame.setOrientation(LinearLayout.VERTICAL);
        frame.setBackgroundColor(Color.rgb(backgroundColor, backgroundColor, backgroundColor));
        frame.setPadding(2,2,2,2);
        
        barLayout = new LinearLayout(c);
        barLayout.setLayoutParams(new ViewGroup.LayoutParams(width, ViewGroup.LayoutParams.MATCH_PARENT));
        
        
        localVerticalGroup = new LinearLayout(c);
        localVerticalGroup.setOrientation(LinearLayout.VERTICAL);
        localVerticalGroup.setBackgroundColor(Color.rgb(backgroundColor+15,
                                                        backgroundColor+15, backgroundColor+15));
        
        if (visibility) {
            barLayout.addView(bar);
            localVerticalGroup.addView(barLayout);
            frame.addView(localVerticalGroup);
        }
	}
	
	public void setValue(float value){
        bar.setProgress((int) ((value-min)*1000/(max-min)));
	}
    
    /*
     * Add the slider to group
     */
    public void addTo(LinearLayout group){
        group.addView(frame);
    }
}
