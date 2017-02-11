// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Exponential smoothing by a unity-dc-gain one-pole lowpass

#ifndef SMOOTH_H_INCLUDED
#define SMOOTH_H_INCLUDED

class Smooth{
private:
    double delay,s;
    
public:
    Smooth():delay(0.0),s(0.0){}
    
    ~Smooth(){}
    
    void reset(){
        delay = 0;
    }
    
    // set the smoothing (pole)
    void setSmooth(double smooth){
        s = smooth;
    }
    
    // compute one sample
    double tick(double input){
        double currentSample = input*(1.0-s);
        currentSample = currentSample + delay;
        delay = currentSample*s;
        return currentSample;
    }
};

#endif  // SMOOTH_H_INCLUDED
