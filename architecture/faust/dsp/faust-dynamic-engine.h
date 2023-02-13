/************************** BEGIN faust-dynamic-engine.h **********************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***************************************************************************/

/* This file describe a simple C API for Faust objects including the audio drivers.
 * Faust objects are first initialized with the desired name, and optionally
 * sampling rate and buffer size. Then start() is called to open the drivers and
 * start processing audio until stop() is called.
 */

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    
    typedef struct {} dsp;
    
    enum { kPortAudioRenderer = 0, kJackRenderer, kCoreAudioRenderer, kiOSRenderer, kAlsaRenderer, kAndroidRenderer };
    
    const char* getLastError();
    
    // Creation API
    
    // Dynamic DSP creation using libfaust and LLVM
    dsp* create1Dsp(const char* name_app, const char* dsp_content);
    dsp* create2Dsp(const char* name_app, const char* dsp_content, const char* argv, const char* target, int opt_level);
    
    // Static DSP creation
    dsp* create3Dsp();
    
    void destroyDsp(dsp* dsp);
    
    bool init1Dsp(dsp* dsp, const char* name);                                     ///< init Faust object with default system values
    bool init2Dsp(dsp* dsp, const char* name, int renderer, int sr, int bsize);     ///< init the Faust object
    
    bool startDsp(dsp* dsp);    ///< open the audio drivers and starts processing audio
    void stopDsp(dsp* dsp);     ///< stop processing audio and closes the audio drivers
    
    // Connection API
    int getNumInputsDsp(dsp* dsp);  // Using NULL means physical input
    int getNumOutputsDsp(dsp* dsp); // Using NULL means physical output
    
    // When used with JACK : using nullptr for dsp1 means physical input,
    // nullptr for dsp2 means physical output
    void connectDsp(dsp* dsp1, dsp* dsp2, int src, int dst);
    void disconnectDsp(dsp* dsp1, dsp* dsp2, int src, int dst);
    bool isConnectedDsp(dsp* dsp1, dsp* dsp2, int src, int dst);
    
    /*
     * Faust objects have control parameters that can be read and changed.
     * getParamsCount() returns the number n of such parameters
     *
     * getParamAddress(int index) retrieves the name of a parameter by its index
     * getParamIndex(const char* name) retrieves the index of a parameter by its name
     *
     * getNamedParam(const char* name) retrieves the value of a parameter by its name
     * getIndexParam(int i) retrieves the value of a parameter by its index
     */
    const char* getJSONDsp(dsp* dsp);                    ///< JSON description of the UI
    
    int getParamsCountDsp(dsp* dsp);                    ///< number of control parameters
    int getParamIndexDsp(dsp* dsp, const char* name);    ///< returns the index of parameter name or -1
    
    const char* getParamAddressDsp(dsp* dsp, int p);     ///< returns the name of parameter p
    const char* getParamUnitDsp(dsp* dsp, int p);        ///< returns the name of parameter p
    FAUSTFLOAT getParamMinDsp(dsp* dsp, int p);         ///< returns the min value of parameter p
    FAUSTFLOAT getParamMaxDsp(dsp* dsp, int p);         ///< returns the max value of parameter p
    FAUSTFLOAT getParamStepDsp(dsp* dsp, int p);        ///< returns the min value of parameter p
    
    FAUSTFLOAT getParamValueDsp(dsp* dsp, int p);           ///< returns the value of parameter p
    void  setParamValueDsp(dsp* dsp, int p, FAUSTFLOAT v);  ///< set the value of parameter p
    
    FAUSTFLOAT getParamRatioDsp(dsp* dsp, int p);           ///< returns the ratio (normalized value in 0..1) of parameter p
    void  setParamRatioDsp(dsp* dsp, int p, FAUSTFLOAT v);  ///< set the ratio (normalized value in 0..1) of parameter p
    
    ///< propagate 'acc' accelerometer influence to related parameters
    void propagateAccDsp(dsp* dsp, int acc, FAUSTFLOAT a);
    ///<Used to edit accelerometer curves and mapping. Set curve and related mapping for a given UI parameter.
    void setAccConverterDsp(dsp* dsp, int p, int acc, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax);
    ///<Used to edit accelerometer curves and mapping. Set curve and related mapping for a given UI parameter.
    void getAccConverterDsp(dsp* dsp, int p, int* acc, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax);
    
    ///< propagate 'acc' gyroscope influence to related parameters
    void propagateGyrDsp(dsp* dsp, int acc, FAUSTFLOAT a);
    ///<Used to edit gyroscope curves and mapping. Set curve and related mapping for a given UI parameter.
    void setGyrConverterDsp(dsp* dsp, int p, int acc, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax);
    ///<Used to edit gyroscope curves and mapping. Set curve and related mapping for a given UI parameter.
    void getGyrConverterDsp(dsp* dsp, int p, int* acc, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax);
    
#ifdef __cplusplus
}
#endif
/************************** END faust-dynamic-engine.h **************************/
