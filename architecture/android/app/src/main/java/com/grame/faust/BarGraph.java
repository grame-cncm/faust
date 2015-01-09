package com.grame.faust;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.ProgressBar;

class BarGraph extends ProgressBar{
	int id;
	float min = 0.0f, max = 100.0f;
	
	public BarGraph(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		this.setMax(1000);
	}
	
	public void setValue(float value){
		this.setProgress((int) ((value-min)*1000/(max-min)));
	}
}