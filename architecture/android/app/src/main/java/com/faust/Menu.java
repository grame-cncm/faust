package com.faust;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Color;
import android.view.Gravity;
import android.view.ViewGroup;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;

class Menu{
	int ID = 0;
	float[] values;
	String address = "";
	Spinner menu;
	List<String> parametersList;
	LinearLayout frame, localVerticalGroup;
	TextView textLabel;
	
	/*
	 * The constructor.
	 * addr: the tree address of the parameter controlled by the slider
	 * currentParameterID: the current parameter id in the parameters tree
	 * width: width of the view in pxs
	 * backgroundColor: grey level of the background of the view (0-255)
	 */
	public Menu(Context c, String addr, int currentParameterID,
			int width, int backgroundColor, String parsedParameters, boolean visibility){
		ID = currentParameterID;
		address = addr;
		
		parametersList = new ArrayList<String>();
		
		menu = new Spinner(c);
		menu.setLayoutParams(new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		
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
		
		// length of the elements array
		int length = parsedParameters.length(); 
		int nElements = countStringOccurrences(parsedParameters,";")+1;
		values = new float[nElements];
		// a menu item with a value assigned to it is created for each element of the array
		for(int i=0; i<nElements; i++){
			String parameterName = parsedParameters.substring(1, parsedParameters.indexOf(":") - 1);
			if(parsedParameters.indexOf(";") != -1) values[i] = Float.valueOf(parsedParameters.substring(
					parsedParameters.indexOf(":")+1, parsedParameters.indexOf(";")));
			else values[i] = Float.valueOf(parsedParameters.substring(
					parsedParameters.indexOf(":")+1));
			parsedParameters = parsedParameters.substring(parsedParameters.indexOf(";") + 1, length);
			length = parsedParameters.length();
			
			parametersList.add(parameterName);	
		}
		// the menu is configured with the list created in the previous step
        ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>
        (c, android.R.layout.simple_spinner_item,parametersList);
        dataAdapter.setDropDownViewResource
        (android.R.layout.simple_spinner_dropdown_item);
        menu.setAdapter(dataAdapter);

        if(visibility) {
            localVerticalGroup.addView(textLabel);
            localVerticalGroup.addView(menu);
            frame.addView(localVerticalGroup);
        }
	}
	
	public void setLabel(String label){
		textLabel.setText(label);
	}
	
	public void addTo(LinearLayout group){
		group.addView(frame);
	}
	
	public void setSelection(int item){
		menu.setSelection(item);
	}
	
	public void linkTo(final ParametersInfo parametersInfo){
		menu.setOnItemSelectedListener(new OnItemSelectedListener(){
        	public void onItemSelected(AdapterView parent, View view, int pos, long id) {
        		parametersInfo.values[ID] = pos;
        		FaustActivity.dspFaust.setParamValue(address, values[pos]);
        	} 
        	public void onNothingSelected(AdapterView parent) {	 		
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
