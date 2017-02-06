package com.ccrma.faust;

public class Smooth {
    private float delay = 0;
    private float s = 0;

    public void reset(){
        delay = 0;
    }

    // set the smoothing (pole)
    public void setSmooth(float smooth){
        s = smooth;
    }

    // compute one sample
    public double tick(float input){
        float currentSample = input*(1.0f-s);
        currentSample = currentSample + delay;
        delay = currentSample*s;
        return currentSample;
    }
}
