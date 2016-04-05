package com.faust;

public class AccelUtil{
    public float normalize(float accelValue){
        return accelValue*0.005f+0.5f;
    }
	
	// TODO: curve mode doesn't work properly
	public float transform(float currentValue, float min, float max, float centerAccel, float centerSlider, int shape){
		float out = 0.0f;

        float accelMax = 100.0f;

        currentValue = currentValue*-1.0f; //For some reasons the accelerometer orientation is reversed

        if(shape == 1) currentValue = currentValue*-1.0f;

        if(currentValue <= 0.0f) {
            float downRange = centerAccel - min;
            float downScaler = downRange/accelMax;
            //float shiftThreshold = downRange/2;
            out = centerAccel + currentValue/downScaler;
            //if(shape == 2 && out < shiftThreshold) out = shiftThreshold - out;
        }
        else{
            float upRange = max - centerAccel;
            float upScaler = upRange/accelMax;
            out = centerAccel + currentValue/upScaler;
        };

        if(out <= 0.0f) {
            float downRange = centerSlider + 100.0f;
            float downScaler = downRange/100.0f;
            out = centerSlider + out*downScaler;
        }
        else{
            float upRange = 100.0f - centerSlider;
            float upScaler = upRange/accelMax;
            out = centerSlider + out*upScaler;
        };

        out = normalize(out);

		return out;
	}
}
