/************************** BEGIN voice.h **************************/
//////////////////////////////////////////////////////
// Faust VST Voice
//////////////////////////////////////////////////////

#ifndef __VST_VOICE_H__
#define __VST_VOICE_H__

class Voice : public vstUI {
    
    public:
        Voice(int sample_rate)
            : vstUI(), m_dsp() 
        {
            m_dsp.init(sample_rate);
            m_dsp.buildUserInterface(this);
        }

        mydsp m_dsp;
    
}; //end of Voice vlass

#endif
/**************************  END  voice.h **************************/
