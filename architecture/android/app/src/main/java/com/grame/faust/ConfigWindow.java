package com.grame.faust;

import android.content.Context;
import android.graphics.Point;
import android.view.Display;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.SeekBar.OnSeekBarChangeListener;

/*
 * TODO:
 * - the min, max and center slider should be aligned
 */

public class ConfigWindow{
	PopupWindow mainWindow;
	LinearLayout mainWindowLayout, minSliderLayout, maxSliderLayout, centerSliderLayout, windowLayout, titleLayout;
	SelectBar axisSelection, axisOrientation;
	TextView closeButton,minSliderValue, maxSliderValue, centerSliderValue, windowLabel;
	SeekBar minSlider, maxSlider, centerSlider;
	Point size;
	
	public void buildWindow(Context c){
		WindowManager wm = (WindowManager) c.getSystemService(Context.WINDOW_SERVICE);
		Display display = wm.getDefaultDisplay();
		size = new Point();
		display.getSize(size);
		// the global elements are instantiated
		mainWindowLayout = new LinearLayout(c);
		minSliderLayout = new LinearLayout(c);
		maxSliderLayout = new LinearLayout(c);
		centerSliderLayout = new LinearLayout(c);
		
		mainWindow = new PopupWindow(c);
		
		closeButton = new TextView(c);
		minSliderValue = new TextView(c);
		maxSliderValue = new TextView(c);
		centerSliderValue = new TextView(c);
		
		axisSelection = new SelectBar(c);
		axisOrientation = new SelectBar(c);
		
		minSlider = new SeekBar(c);
		maxSlider = new SeekBar(c);
		centerSlider = new SeekBar(c);
		
		windowLayout = new LinearLayout(c);
		titleLayout = new LinearLayout(c);
		windowLabel = new TextView(c);
		TextView axisLabel = new TextView(c);
		TextView orientationLabel = new TextView(c);
		
		LayoutParams wrapped = new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		
		windowLayout.setLayoutParams(wrapped);
		windowLayout.setOrientation(LinearLayout.VERTICAL);
		windowLayout.setPadding(10, 0, 10, 0); // TODO adjust in function of screen size
		
		titleLayout.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		titleLayout.setOrientation(LinearLayout.HORIZONTAL);
		
		closeButton.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		closeButton.setGravity(Gravity.RIGHT);
		closeButton.setTextSize(20);
		closeButton.setText("X");
			
		windowLabel.setText("Accelerometer Parameters");
		windowLabel.setTextSize(22.f);
		
		axisLabel.setText("Axis: ");
		orientationLabel.setText("Orientation: ");
		
		String[] items = {"0","X","Y","Z"};
		axisSelection.setItems(items);
		
		int[] iconsOn = {R.drawable.ic_accelnormon,R.drawable.ic_accelinverton,R.drawable.ic_accelcurveon};
		int[] iconsOff = {R.drawable.ic_accelnormoff,R.drawable.ic_accelinvertoff,R.drawable.ic_accelcurveoff};
		axisOrientation.setItems(iconsOn,iconsOff);
		
		minSlider.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		minSlider.setMax(1000);
		
		maxSlider.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		maxSlider.setMax(1000);
		
		centerSlider.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		centerSlider.setMax(1000);
						
		titleLayout.addView(windowLabel);
		titleLayout.addView(closeButton);
		
		windowLayout.addView(titleLayout);
		windowLayout.addView(axisLabel);
		axisSelection.addTo(windowLayout);
		
		windowLayout.addView(orientationLabel);
		axisOrientation.addTo(windowLayout);
		
		minSliderLayout.addView(minSliderValue);
		minSliderLayout.addView(minSlider);
		
		maxSliderLayout.addView(maxSliderValue);
		maxSliderLayout.addView(maxSlider);
		
		centerSliderLayout.addView(centerSliderValue);
		centerSliderLayout.addView(centerSlider);
		
		windowLayout.addView(minSliderLayout);
		windowLayout.addView(maxSliderLayout);
		windowLayout.addView(centerSliderLayout);
				
		mainWindow.setContentView(windowLayout);
	}
	
	public void showWindow(final ParametersInfo parametersInfo, final int currentParameterNumber){
		// Saved state is used
		axisSelection.selectTextItem(parametersInfo.accelState[currentParameterNumber]);
		axisOrientation.selectImgItem(parametersInfo.accelInverterState[currentParameterNumber]);
		
		setValue(minSlider,minSliderValue,"Min: ",parametersInfo.accelMin[currentParameterNumber]);
		setValue(maxSlider,maxSliderValue,"Max: ",parametersInfo.accelMax[currentParameterNumber]);
		setValue(centerSlider,centerSliderValue,"Center: ",parametersInfo.accelCenter[currentParameterNumber]);
		
		mainWindow.showAtLocation(mainWindowLayout, Gravity.CENTER,0,0);
		mainWindow.update(0, 0, size.x*700/800, ViewGroup.LayoutParams.WRAP_CONTENT);
		
		titleLayout.setOnClickListener(new OnClickListener(){
			public void onClick(View v){
				mainWindow.dismiss();
			}
		});
		
		for(int i=0; i<axisSelection.length; i++){
			final int index = i;
			axisSelection.parameterLabel[i].setOnClickListener(new OnClickListener(){
				public void onClick(View v){
					axisSelection.selectTextItem(index);
					parametersInfo.accelState[currentParameterNumber] = index;
				}
			});
		}
		
		for(int i=0; i<axisOrientation.length; i++){
			final int index = i;
			axisOrientation.imgs[i].setOnClickListener(new OnClickListener(){
				public void onClick(View v){
					axisOrientation.selectImgItem(index);
					parametersInfo.accelInverterState[currentParameterNumber] = index;
				}	
			});
		}
		
		minSlider.setOnSeekBarChangeListener( new OnSeekBarChangeListener() {
			public void onStopTrackingTouch(SeekBar seekBar) {}
			public void onStartTrackingTouch(SeekBar seekBar) {}
			public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
				float scaledProgress = progress*0.2f - 100.0f;
				if(scaledProgress >= parametersInfo.accelMax[currentParameterNumber])
					setValue(minSlider,minSliderValue,"Min: ",parametersInfo.accelMax[currentParameterNumber]);
				else{ 
					parametersInfo.accelMin[currentParameterNumber] = scaledProgress;
					minSliderValue.setText("Min: " + String.format("%.1f", scaledProgress));
				}
	          }
	    });
		
		maxSlider.setOnSeekBarChangeListener( new OnSeekBarChangeListener() {
			public void onStopTrackingTouch(SeekBar seekBar) {}
			public void onStartTrackingTouch(SeekBar seekBar) {}
			public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
				float scaledProgress = progress*.2f - 100.0f;
				if(scaledProgress <= parametersInfo.accelMin[currentParameterNumber])
					setValue(maxSlider,maxSliderValue,"Max: ",parametersInfo.accelMin[currentParameterNumber]);
				else{ 
					parametersInfo.accelMax[currentParameterNumber] = scaledProgress;
					maxSliderValue.setText("Max: " + String.format("%.1f", scaledProgress));
				}
	          }
	    });
		
		centerSlider.setOnSeekBarChangeListener( new OnSeekBarChangeListener() {
			public void onStopTrackingTouch(SeekBar seekBar) {}
			public void onStartTrackingTouch(SeekBar seekBar) {}
			public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
				float scaledProgress = progress*0.2f - 100.0f;
				if(scaledProgress <= parametersInfo.accelMin[currentParameterNumber])
					setValue(centerSlider,centerSliderValue,"Center: ",parametersInfo.accelMin[currentParameterNumber]);
				else if(scaledProgress >= parametersInfo.accelMax[currentParameterNumber])
					setValue(centerSlider,centerSliderValue,"Center: ",parametersInfo.accelMax[currentParameterNumber]);
				else{ 
					parametersInfo.accelCenter[currentParameterNumber] = scaledProgress;	
					centerSliderValue.setText("Center: " + String.format("%.1f", scaledProgress));
				}
	          }
	    });
	}
	
	void setValue(SeekBar s, TextView t, String name, float x){
		t.setText(name + String.format("%.1f",x));
		s.setProgress(Math.round((x+10.0f)*5.0f));
	}
	
	/*
	public void registerParameters(int[] UIelementsParameters){
		UIelementsParameters[0] = axisSelection.id;
	}
	*/
}