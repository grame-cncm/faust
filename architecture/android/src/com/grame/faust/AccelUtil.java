package com.grame.faust;

public class AccelUtil{
	public float normalize(float accelValue){
		return (accelValue+10)*0.05f;
	}
	
	// TODO: curve mode doesn't work properly
	public float transform(float currentValue, float min, float max, float center, int shape){
		float out = 0.0f;
		float range = max-min;
		float scaleMin = (10 + min*20/range)*-1;
		
		if(currentValue >= min && currentValue <= max) out = currentValue*20/range + scaleMin;
		else if(currentValue > max) out = 10.0f;
		else if(currentValue < min) out = -10.0f;
		
		out = normalize(out);
		center = normalize(center);
		if(shape == 2){
			if(out <= 0.5) out = out/center;
			else if(out > 0.5) out = 1 - (out-0.5f)/(1-center);
		}
		else{
			if(shape == 1) center = 1 - center;
			if(out <= 0.5) out = out*center*2;
			else if(out > 0.5) out = center + (1-center)*(out-0.5f)*2;
			if(shape == 1) out = 1 - out;
		}
		
		return out;
	}
}