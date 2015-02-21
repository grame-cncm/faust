/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
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


 ************************************************************************
 ************************************************************************/

#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/audio/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/jsonfaustui.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"

//**************************************************************
// Intrinsic
//**************************************************************

<<includeIntrinsic>>
	
//**************************************************************
// Class
//**************************************************************

<<includeclass>>
	
//**************************************************************
// Polyphony
//**************************************************************

#include "faust/audio/poly-dsp.h"

//**************************************************************
// IOS Coreaudio
//**************************************************************

#include "faust/audio/coreaudio-ios-dsp.h"

//**************************************************************
// Interface
//**************************************************************

#include <stdio.h>
#include <string.h>

using namespace std;

class dsp_faust {

private:

    int polyMax;
    int inChanNumb;
    int outChanNumb;
    bool on;
    
    TiPhoneCoreAudioRenderer fAudioDevice;
    mydsp DSP;
    mydsp_poly *DSPpoly;
    MapUI mapUI;
    JSONUI json;
    string jsonString;
    
public:

    dsp_faust() : json(DSP.getNumInputs(), DSP.getNumOutputs()),DSPpoly(0),on(false) {}
    virtual ~dsp_faust() { delete DSPpoly; }
    
    /*
     * init(samplingRate, bufferFrames)
     * Initializes the Audio engine and the DSP code
     * with samplingRate and bufferFrames.
     * This method also looks for the [style:poly]
     * metadata in the Faust code and initializes a
     * polyphonic object or not based on that. init
     * should be called before start.
     */
    bool init(int samplingRate, int bufferSize) {
        DSP.init(samplingRate);
        inChanNumb = DSP.getNumInputs();
        outChanNumb = DSP.getNumOutputs();
        
        DSP.buildUserInterface(&mapUI);
        DSP.buildUserInterface(&json);
        
        jsonString = json.JSON();
        
        if (jsonString.find("keyboard") != std::string::npos ||
           jsonString.find("poly") != std::string::npos){
            polyMax = 4;
            DSPpoly = new mydsp_poly(bufferSize, polyMax);
            DSPpoly->init(samplingRate);
        } else{
            polyMax = 0;
        }
        
        return (fAudioDevice.Open(((polyMax > 0) ? DSPpoly : &DSP), inChanNumb, outChanNumb, bufferSize, samplingRate) == 0);
    }
    
    /*
     * start()
     * Begins the processing and return 1 if the connection
     * with the audio device was successful and 0 if not.
     * On Android it also creates the native thread where the
     * DSP tasks will be computed.
     */
    bool start() {
        on = true;
        return (fAudioDevice.Start() == 0);
    }
    
    /*
     * stop()
     * Stops the processing, closes the audio engine and terminates
     * the native thread on Android.
     */
    void stop() {
        on = false;
        fAudioDevice.Stop();
    }
    
    /*
     * isRunning()
     * returns true if the DSP frames are being computed and
     * false if not.
     */
    bool isRunning() {
        return on;
    }
    
    /*
     * keyOn(pitch, velocity)
     * Instantiates a new polyphonic voice where velocity
     * and pitch are MIDI numbers (0-127). keyOn can only
     * be used if the [style:poly] metadata is used in the
     * Faust code. keyOn will return 0 if the object is not
     * polyphonic and 1 otherwise.
     */
    int keyOn(int pitch, int velocity) {
        if (polyMax > 0) {
            DSPpoly->keyOn(0, pitch, velocity);
            return 1;
        } else {
            return 0;
        }
    }
    
    /*
     * keyOff(pitch)
     * De-instantiates a polyphonic voice where pitch is the
     * MIDI number of the note (0-127). keyOff can only be
     * used if the [style:poly] metadata is used in the Faust
     * code. keyOn will return 0 if the object is not polyphonic
     * and 1 otherwise.
     */
    int keyOff(int pitch) {
        if (polyMax > 0) {
            DSPpoly->keyOff(0, pitch);
            return 1;
        } else {
            return 0;
        }
    }
    
    /*
     * pitchBend(refPitch, pitch)
     * Replaces refPitch in the voice associated with it with pitch.
     * pitch is a MIDI number expressed as a decimal number.
     * pitchBend can only be used if the [style:poly] metadata
     * is used in the Faust code. pitchBend will return 0
     * if the object is not polyphonic and 1 otherwise.
     */
    int pitchBend(int refPitch, float pitch) {
        if (polyMax > 0) {
            DSPpoly->pitchBend(0,refPitch, pitch);
            return 1;
        } else {
            return 0;
        }
    }
    
    /*
     * getJSON()
     * Returns a string containing a JSON description of the
     * UI of the Faust object.
     */
    const char *getJSON() {
        return jsonString.c_str();
    }
    
    /*
     * getParamsCount()
     * Returns the number of parameters of the Faust object.
     */
    int getParamsCount() {
        return mapUI.getParamsCount();
    }
    
    /*
     * getParam(address)
     * Takes the address of a parameter and returns its current
     * value.
     */
    float getParam(const char* address) {
        return (polyMax == 0) ? mapUI.getValue(address) : DSPpoly->getValue(address);
     }
    
    /*
     * setParam(address,value)
     * Sets the value of the parameter associated with address.
     */
    void setParam(const char* address, float value) {
        if (polyMax == 0) {
            mapUI.setValue(address, value);
        } else {
            DSPpoly->setValue(address, value);
        }
    }
    
    /*
     * setVoiceParam(address,pitch,value)
     * Sets the value of the parameter associated with address for
     * the voice associated with pitch. setVoiceParam can only be
     * used if the [style:poly] metadata is used in the Faust code.
     * setVoiceParam will return 0 if the object is not polyphonic
     * and 1 otherwise.
     */
    int setVoiceParam(const char* address, int pitch, float value) {
        if (polyMax > 0) {
            DSPpoly->setValue(address, pitch, value);
            return 1;
        } else {
            return 0;
        }
    }
    
    /*
     * setVoiceGain(pitch,gain)
     * Sets the gain (0-1) of the voice associated with pitch.
     * setVoiceGain can only be used if the [style:poly] metadata
     * is used in the Faust code. setVoiceGain will return 0 if the
     * object is not polyphonic and 1 otherwise.
     */
    int setVoiceGain(int pitch, float gain) {
        if (polyMax > 0) {
            setVoiceParam(DSPpoly->fGainLabel.c_str(),pitch,gain);
            return 1;
        } else {
            return 0;
        }
    }
    
    /*
     * getParamAddress(id)
     * Returns the address of a parameter in function of its "id".
     */
    const char *getParamAddress(int id) {
        return mapUI.getParamPath(id).c_str();
    }  
};
