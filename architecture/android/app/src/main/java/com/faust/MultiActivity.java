package com.faust;

import com.faust.MultiParams.OnMultiParamsChangeListener;

import android.app.Activity;
import android.content.SharedPreferences;
import android.os.Bundle;

public class MultiActivity extends Activity {
	int nParams;
	float[] values;
	ParametersInfo parametersInfo;
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.multi);
        
        int numberOfParameters = FaustActivity.dspFaust.getParamsCount();
        parametersInfo = new ParametersInfo();
        parametersInfo.init(numberOfParameters);
        SharedPreferences settings = getSharedPreferences("savedParameters", 0);
        parametersInfo.loadParameters(settings);
        
        final MultiParams mp = (MultiParams) this.findViewById(R.id.MultiParams);
        int nMultiParams = parametersInfo.nMultiParams;
        nParams = parametersInfo.nParams;
        String[] labels = new String[nMultiParams];
        final String[] addresses = new String[nMultiParams];
		float[] min = new float[nMultiParams];
		float[] max = new float[nMultiParams];
		values = new float[nMultiParams];
		
		for(int i=0; i<nParams; i++){
			int currentIndex = parametersInfo.order[i];
			if(currentIndex != -1){	
				addresses[currentIndex] = FaustActivity.dspFaust.getParamAddress(i);
				labels[currentIndex] = parametersInfo.label[i];
				min[currentIndex] = parametersInfo.min[i];
				max[currentIndex] = parametersInfo.max[i];
				values[currentIndex] = FaustActivity.dspFaust.getParamValue(addresses[currentIndex]);
			}
		}
		mp.setParams(labels, min, max, values);
		
		mp.setOnMultiParamsChangeListener(new OnMultiParamsChangeListener(){
			@Override
			public void onParamChange(int paramID, float value) {
				FaustActivity.dspFaust.setParamValue(addresses[paramID], value);
			}	
		});
	}
   	
	@Override
	public void onDestroy(){
    	super.onDestroy();
    }
}
