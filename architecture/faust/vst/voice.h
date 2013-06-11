//////////////////////////////////////////////////////
// Faust VST Voice
//////////////////////////////////////////////////////

#ifndef __VST_VOICE_H__
#define __VST_VOICE_H__

#include "dsp.h"

class Voice : public vstUI {
public:
	Voice(int samplingRate) 
		: vstUI(), m_dsp() 
	{
		m_dsp.init(samplingRate);
		m_dsp.buildUserInterface(this);
	}

	mydsp m_dsp;
}; //end of Voice vlass

#endif
