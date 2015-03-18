package com.grame.faust;

import com.grame.faust.MultiParams.OnMultiParamsChangeListener;
import com.grame.dsp_faust.dsp_faust;

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
        
        int numberOfParameters = dsp_faust.getParamsCount();
        parametersInfo = new ParametersInfo();
        parametersInfo.init(numberOfParameters);
        SharedPreferences settings = getSharedPreferences("savedParameters", 0);
        parametersInfo.getSavedParameters(settings);
        
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
				addresses[currentIndex] = dsp_faust.getParamAddress(i);
				labels[currentIndex] = parametersInfo.label[i];
				min[currentIndex] = parametersInfo.min[i];
				max[currentIndex] = parametersInfo.max[i];
				values[currentIndex] = dsp_faust.getParam(addresses[currentIndex]);
			}
		}
		mp.setParams(labels, min, max, values);
		
		mp.setOnMultiParamsChangeListener(new OnMultiParamsChangeListener(){
			@Override
			public void onParamChange(int paramID, float value) {
				dsp_faust.setParam(addresses[paramID], value);
			}	
		});
	}
	
	@Override
	public void onDestroy(){
    	super.onDestroy();
    }
}