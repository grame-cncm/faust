package com.grame.faust;

import android.content.SharedPreferences;

class ParametersInfo{
	// Saved Parameters
	String[] address;
	float[] values;
	int zoom;
	int[] accelState;
	int[] accelInverterState;
	float[] accelMin;
	float[] accelMax;
	float[] accelCenter;
	int[] accelItemFocus;
	
	// Multi interface parameters
	int nMultiParams;
	int[] order;
	String[] label;
	float[] min;
	float[] max;
	float[] step;
	
	// Other Parameters
	int[] parameterType;
	int[] localId;
	
	int nParams = 0;
	int saved = 1;
	boolean locked = true;
	
	public void init(int numberOfParams){
		nParams = numberOfParams;
		address = new String[nParams];
		values = new float[nParams];
		accelState = new int[nParams];
		accelInverterState = new int[nParams];
		accelMin = new float[nParams];
		accelMax = new float[nParams];
		accelCenter = new float[nParams];
		accelItemFocus = new int[nParams];
		parameterType = new int[nParams]; //0: hslider, 1: vslider
		localId = new int[nParams];
		
		order = new int[nParams];
		label = new String[nParams];
		min = new float[nParams];
		max = new float[nParams];
		step = new float[nParams];
		
		// assigning default values
		for(int i=0; i<nParams; i++){
			accelMin[i] = -100.0f;
			accelMax[i] = 100.0f;
			accelCenter[i] = 0.0f;
			accelInverterState[i] = 0;
			accelItemFocus[i] = 0;
			
			order[i] = -1;
			min[i] = 0;
			max[i] = 0;
			step[i] = 0;
		}
	}
	
	public void saveParemeters(SharedPreferences settings){
		SharedPreferences.Editor editor = settings.edit();
		editor.putInt("wasSaved",1);
		editor.putInt("zoom", zoom);
		editor.putBoolean("locked", locked);
		editor.putInt("nMultiParams", nMultiParams);
		for(int i=0; i<nParams; i++){
			editor.putFloat("value"+i, values[i]);
			editor.putInt("accelState"+i, accelState[i]);
			editor.putFloat("accelMin"+i, accelMin[i]);
			editor.putFloat("accelMax"+i, accelMax[i]);
			editor.putFloat("accelCenter"+i, accelCenter[i]);
			editor.putInt("accelInverterState"+i, accelInverterState[i]);
			
			editor.putInt("order"+i, order[i]);
			editor.putString("label"+i, label[i]);
			editor.putFloat("min"+i, min[i]);
			editor.putFloat("max"+i, max[i]);
			editor.putFloat("step"+i, step[i]);
		}
		editor.commit();
	}
	
	public boolean getSavedParameters(SharedPreferences settings){
		if(settings.getInt("wasSaved",0) == 1){
			zoom = settings.getInt("zoom", 0);
			locked = settings.getBoolean("locked",true);
			nMultiParams = settings.getInt("nMultiParams", 0);
			for(int i=0; i<nParams; i++){
				values[i] = settings.getFloat("value"+i,0.0f);
				accelState[i] = settings.getInt("accelState"+i, 0); //TODO: should be done only for parameters controlled 
				accelMin[i] = settings.getFloat("accelMin"+i, 0);
				accelMax[i] = settings.getFloat("accelMax"+i, 0);
				accelCenter[i] = settings.getFloat("accelCenter"+i, 0);
				accelInverterState[i] = settings.getInt("accelInverterState"+i, 0);
				
				// TODO perhaps this should be in a separate function for optimization saic...	
				order[i] = settings.getInt("order"+i, 0);
				label[i] = settings.getString("label"+i, null);
				min[i] = settings.getFloat("min"+i, 0f);
				max[i] = settings.getFloat("max"+i, 0f);
				step[i] = settings.getFloat("step"+i, 0f);
			}
			return true;
		}
		else return false;
	}
}