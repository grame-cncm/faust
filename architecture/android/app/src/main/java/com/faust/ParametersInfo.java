package com.faust;

import android.content.SharedPreferences;

import android.util.Log;

class ParametersInfo {

    final String VERSION = "0.11";
	// Saved Parameters
	String[] address;
	float[] values;
	int zoom;
	int[] accgyrType;
	int[] accgyrCurve;
	float[] accgyrMin;
	float[] accgyrMax;
	float[] accgyrCenter;
    int[] accgyrItemFocus;

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

	//OSC SETTING
	String ipAddress = "192.168.1.5";
	int inPort = 5510;
	int outPort = 5511;
	int xmit = 1;

	public void init(int numberOfParams){
		nParams = numberOfParams;
		address = new String[nParams];
		values = new float[nParams];
		accgyrType = new int[nParams];
		accgyrCurve = new int[nParams];
		accgyrMin = new float[nParams];
		accgyrMax = new float[nParams];
		accgyrCenter = new float[nParams];
		accgyrItemFocus = new int[nParams];
		parameterType = new int[nParams]; //0: hslider, 1: vslider
		localId = new int[nParams];

		order = new int[nParams];
		label = new String[nParams];
		min = new float[nParams];
		max = new float[nParams];
		step = new float[nParams];

		// assigning default values
		for(int i=0; i<nParams; i++){
            accgyrType[i] = 0;
			accgyrMin[i] = -100.0f;
			accgyrMax[i] = 100.0f;
			accgyrCenter[i] = 0.0f;
  			accgyrCurve[i] = 0;
			accgyrItemFocus[i] = 0;

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
		editor.putString("ipAddress",ipAddress);
		editor.putInt("inPort",inPort);
		editor.putInt("outPort",outPort);
		editor.putInt("xMit",xmit);

        Log.d("FaustJava", "saveParameters : nParams " + nParams);

		for (int i = 0; i < nParams; i++){
			editor.putFloat("value"+i, values[i]);
			editor.putInt("accgyrType"+i, accgyrType[i]);
			editor.putFloat("accgyrMin"+i, accgyrMin[i]);
			editor.putFloat("accgyrMax"+i, accgyrMax[i]);
			editor.putFloat("accgyrCenter"+i, accgyrCenter[i]);
            editor.putInt("accgyrCurve"+i, accgyrCurve[i]);
            //Log.d("FaustJava", "saveParameters accgyrCurve "+i + " " + accgyrCurve[i]);
            Log.d("FaustJava", "saveParameters accgyrType "+i + " " + accgyrType[i]);

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
			ipAddress = settings.getString("ipAddress","192.168.1.5");
			inPort = settings.getInt("inPort",5510);
			outPort = settings.getInt("outPort",5511);
			xmit = settings.getInt("xMit", 1);

            Log.d("FaustJava", "loadParameters : nParams " + nParams);

			for (int i = 0; i < nParams; i++){
				values[i] = settings.getFloat("value"+i,0.0f);
				accgyrType[i] = settings.getInt("accgyrType"+i, 0); //TODO: should be done only for controlled parameters
				accgyrMin[i] = settings.getFloat("accgyrMin"+i, 0);
				accgyrMax[i] = settings.getFloat("accgyrMax"+i, 0);
				accgyrCenter[i] = settings.getFloat("accgyrCenter"+i, 0);
    			accgyrCurve[i] = settings.getInt("accgyrCurve"+i, 0);
                //Log.d("FaustJava", "loadParameters accgyrCurve "+i + " " + accgyrCurve[i]);
                Log.d("FaustJava", "loadParameters accgyrType "+i + " " + accgyrType[i]);

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
