#ifndef __VST_DSP_H__
#define __VST_DSP_H__

#include "UI.h"

//----------------------------------------------------------------
//  Base dsp class for this architecture
//----------------------------------------------------------------
			
class dsp {
protected:
  // Sampling frequency
  int fSamplingFreq;

public:
  // Constructor
  dsp() {}

  // Destructor
  virtual ~dsp() {}

  virtual int getNumInputs() = 0;
  virtual int getNumOutputs() = 0;
  virtual void buildUserInterface(UI* interface) = 0;
	virtual void instanceInit(int samplingRate) = 0;
  virtual void init(int samplingRate) = 0;
  virtual void compute(int len, float** inputs, float** outputs) = 0;
};

#endif
