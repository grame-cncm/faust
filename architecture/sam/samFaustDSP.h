/************************************************************************
  SHARC Audio Module Faust Architecture File
  Copyright (c) 2018 Analog Devices, Inc. All rights reserved.
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __sam_faust_dsp__
#define __sam_faust_dsp__

//==========================================

#define SAM_SAMPLERATE AUDIO_SAMPLE_RATE

class FaustPolyEngine;
class MidiUI;
class samAudio;
class mydsp;

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class samFaustDSP
{
    
    private:
    
        // the polyphonic engine
        FaustPolyEngine* fPolyEngine;
    
        // the audio driver
        samAudio* fAudioDriver;
     
    public:
    
        //--------------`samFaustDSP()`----------------
        // Default constructor, the audio driver will set
        // the sampleRate and buffer size
        //----
        samFaustDSP(int sampleRate, int bufferSize, int numInputs, int numOutputs);
    
        // destructor
        ~samFaustDSP();
    
        // setup the the hardware buffer pointers.
        void setDSP_ChannelBuffers(FAUSTFLOAT* AudioChannelA_0_Left,
                                   FAUSTFLOAT* AudioChannelA_0_Right,
                                   FAUSTFLOAT* AudioChannelA_1_Left,
                                   FAUSTFLOAT* AudioChannelA_1_Right,
                                   FAUSTFLOAT* AudioChannelA_2_Left,
                                   FAUSTFLOAT* AudioChannelA_2_Right,
                                   FAUSTFLOAT* AudioChannelA_3_Left,
                                   FAUSTFLOAT* AudioChannelA_3_Right,
                                   FAUSTFLOAT* AudioChannelB_0_Left,
                                   FAUSTFLOAT* AudioChannelB_0_Right,
                                   FAUSTFLOAT* AudioChannelB_1_Left,
                                   FAUSTFLOAT* AudioChannelB_1_Right,
                                   FAUSTFLOAT* AudioChannelB_2_Left,
                                   FAUSTFLOAT* AudioChannelB_2_Right,
                                   FAUSTFLOAT* AudioChannelB_3_Left,
                                   FAUSTFLOAT* AudioChannelB_3_Right);
    
        //-----------------`void stop()`--------------------------
        // Callback to render a buffer.
        //--------------------------------------------------------
        void processAudioCallback();
        
        //-------`void propagateMidi(int count, double time, int type, int channel, int data1, int data2)`--------
        // Take a raw MIDI message and propagate it to the Faust
        // DSP object. This method can be used concurrently with
        // [`keyOn`](#keyOn) and [`keyOff`](#keyOff).
        //
        // `propagateMidi` can
        // only be used if the `[style:poly]` metadata is used in
        // the Faust code or if `-nvoices` flag has been
        // provided before compilation.
        //
        // #### Arguments
        //
        // * `count`: size of the message (1-3)
        // * `time`: time stamp
        // * `type`: message type (byte)
        // * `channel`: channel number
        // * `data1`: first data byte (should be `null` if `count<2`)
        // * `data2`: second data byte (should be `null` if `count<3`)
        //--------------------------------------------------------
        void propagateMidi(int, double, int, int, int, int);
};

#endif
