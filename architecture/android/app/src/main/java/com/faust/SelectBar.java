package com.faust;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

public class SelectBar{
	LinearLayout mainLayout;
	Context mainContext;
	TextView[] parameterLabel;
	LinearLayout[] imgs;
	int length; 
	int id = 0;
	int[] itemsOn, itemsOff;
	
	public SelectBar(Context c){
		mainContext = c;
		mainLayout = new LinearLayout(mainContext);
		mainLayout.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		mainLayout.setOrientation(LinearLayout.HORIZONTAL);
	}
	
	public void addTo(LinearLayout upperLayout){
		upperLayout.addView(mainLayout);
	}
	
	public void setItems(int[] itOn, int[] itOff){
		length = itOn.length;
		itemsOn = itOn;
		itemsOff = itOff;
		imgs = new LinearLayout[length];
		
		for(int i=0; i<length; i++){
			LinearLayout frame = new LinearLayout(mainContext);
			imgs[i] = new LinearLayout(mainContext);
			frame.setBackgroundColor(Color.rgb(69,160,197));
			frame.setPadding(1, 1, 1, 1);
			frame.addView(imgs[i]);
			mainLayout.addView(frame);
		}
		selectImgItem(0);
	}
	
	public void setItems(String[] items){
		length = items.length;
		parameterLabel = new TextView[length];
		
		for(int i=0; i<length; i++){
			LinearLayout frame = new LinearLayout(mainContext);
			parameterLabel[i] = new TextView(mainContext);
			frame.setBackgroundColor(Color.rgb(69,160,197));
			frame.setPadding(1, 1, 1, 1);
			parameterLabel[i].setBackgroundColor(Color.rgb(70,70,70));
			parameterLabel[i].setPadding(20, 10, 20, 10); // TODO: adjust in function of screen size
			parameterLabel[i].setText(items[i]);
			frame.addView(parameterLabel[i]);
			mainLayout.addView(frame);
		}
		selectTextItem(0);
	}
	
	public void selectTextItem(int item){
		id = item;
		for(int i=0; i<length; i++){
			if(i == id){ 
				parameterLabel[i].setBackgroundColor(Color.rgb(69,160,197));
				parameterLabel[i].setTextColor(Color.rgb(70,70,70));
			}
			else{
				parameterLabel[i].setBackgroundColor(Color.rgb(70,70,70));
				parameterLabel[i].setTextColor(Color.rgb(69,160,197));
			}
		}
	}
	
	public void selectImgItem(int item){
		id = item;
		for(int i=0; i<length; i++){
			if(i == id){ 
				imgs[i].setBackgroundResource(itemsOn[i]);
			}
			else{
				imgs[i].setBackgroundResource(itemsOff[i]);
			}
		}
	}
}
