package com.faust;

import android.content.SharedPreferences;

import android.util.Log;

class ParametersInfo{
    
    final String VERSION = "0.10";
	// Saved Parameters
	String[] address;
	float[] values;
	int zoom;
	int[] accelType;
	int[] accelCurve;
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
		accelType = new int[nParams];
		accelCurve = new int[nParams];
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
            accelType[i] = 0;
			accelMin[i] = -100.0f;
			accelMax[i] = 100.0f;
			accelCenter[i] = 0.0f;
  			accelCurve[i] = 0;
			accelItemFocus[i] = 0;
			
			order[i] = -1;
			min[i] = 0;
			max[i] = 0;
			step[i] = 0;
		}
	}
	
	public void saveParameters(SharedPreferences settings){
		SharedPreferences.Editor editor = settings.edit();
		editor.putInt("wasSaved" + VERSION,saved);
		editor.putInt("zoom", zoom);
		editor.putBoolean("locked", locked);
		editor.putInt("nMultiParams", nMultiParams);
        
        Log.d("FaustJava", "saveParameters : nParams " + nParams);
        
		for(int i=0; i<nParams; i++){
			editor.putFloat("value"+i, values[i]);
			editor.putInt("accelType"+i, accelType[i]);
			editor.putFloat("accelMin"+i, accelMin[i]);
			editor.putFloat("accelMax"+i, accelMax[i]);
			editor.putFloat("accelCenter"+i, accelCenter[i]);
            editor.putInt("accelCurve"+i, accelCurve[i]);
            //Log.d("FaustJava", "saveParameters accelCurve "+i + " " + accelCurve[i]);
            Log.d("FaustJava", "saveParameters accelType "+i + " " + accelType[i]);
			
			editor.putInt("order"+i, order[i]);
			editor.putString("label"+i, label[i]);
			editor.putFloat("min"+i, min[i]);
			editor.putFloat("max"+i, max[i]);
			editor.putFloat("step"+i, step[i]);
		}
		editor.commit();
	}
	
	public boolean loadParameters(SharedPreferences settings){
		if(settings.getInt("wasSaved" + VERSION,0) == 1){
			zoom = settings.getInt("zoom", 0);
			locked = settings.getBoolean("locked",true);
			nMultiParams = settings.getInt("nMultiParams", 0);
            
            Log.d("FaustJava", "loadParameters : nParams " + nParams);
            
			for(int i=0; i<nParams; i++){
				values[i] = settings.getFloat("value"+i,0.0f);
				accelType[i] = settings.getInt("accelType"+i, 0); //TODO: should be done only for controlled parameters
				accelMin[i] = settings.getFloat("accelMin"+i, 0);
				accelMax[i] = settings.getFloat("accelMax"+i, 0);
				accelCenter[i] = settings.getFloat("accelCenter"+i, 0);
    			accelCurve[i] = settings.getInt("accelCurve"+i, 0);
                //Log.d("FaustJava", "loadParameters accelCurve "+i + " " + accelCurve[i]);
                Log.d("FaustJava", "loadParameters accelType "+i + " " + accelType[i]);
				
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
