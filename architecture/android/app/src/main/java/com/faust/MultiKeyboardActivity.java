package com.faust;

import com.faust.MultiParams.OnMultiParamsChangeListener;
import com.faust.PianoKeyboard.PianoKey;
import com.faust.PianoKeyboard.OnKeyboardChangeListener;

import android.app.Activity;
import android.content.SharedPreferences;
import android.os.Bundle;

public class MultiKeyboardActivity extends Activity {
	int nParams;
	float[] values;
	ParametersInfo parametersInfo;
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.combined);
        
        final PianoKeyboard keyboard = (PianoKeyboard)this.findViewById(R.id.PianoKeyboard);
        keyboard.setOnKeyboardChangeListener(new OnKeyboardChangeListener(){
			@Override
	       public void onKeyChanged(int note, int velocity, boolean status) {
               if (status) {
                    keyboard.keys[note - keyboard.baseNote].voice = FaustActivity.dspFaust.keyOn(note, velocity);
                } else {
                    FaustActivity.dspFaust.keyOff(note);
                    keyboard.keys[note - keyboard.baseNote].voice = -1;
                }
			}
			
            @Override
            public void onPitchBend(long voice, float pitch) {
                FaustActivity.dspFaust.setVoiceParamValue("freq", voice, (float)(440.0 * Math.pow(2.0, (pitch-69.0)/12.0)));
            }
            @Override
            public void onYChanged(long voice, float y) {
                FaustActivity.dspFaust.setVoiceParamValue("gain", voice, y);
            }
        });
        
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
