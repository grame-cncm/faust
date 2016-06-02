
/************************************************************************
FAUST API
Copyright (C) 2015-2016 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This file describe a simple C API for Faust objects including the audio drivers.

************************************************************************
************************************************************************/
    
/*
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

    // Dynamic DSP creation using libfaust and LLLVM
    dsp* create1Dsp(const char* name_app, const char* dsp_content);
    dsp* create2Dsp(const char* name_app, const char* dsp_content, const char* argv, const char* target, int opt_level);

    // Static DSP creation
    dsp* create3Dsp();

    void destroyDsp(dsp* dsp);

    bool init1Dsp(dsp* dsp, const char* name);                                      ///< init Faust object with default system values
    bool init2Dsp(dsp* dsp, const char* name, int renderer, int sr, int bsize);     ///< init the Faust object

    bool startDsp(dsp* dsp);    ///< open the audio drivers and starts processing audio
    void stopDsp(dsp* dsp);     ///< stop processing audio and closes the audio drivers

    // Connection API
    int getNumInputsDsp(dsp* dsp);  // Using NULL means physical input
    int getNumOutputsDsp(dsp* dsp); // Using NULL means physical output

    // When used with JACK : using NULL for dsp1 means physical input,
    // NULL for dsp2 means physical output
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
    const char* getJSONDsp(dsp* dsp);					///< JSON description of the UI

    int getParamsCountDsp(dsp* dsp);					///< number of control parameters
    int getParamIndexDsp(dsp* dsp, const char* name); 	///< returns the index of parameter name or -1
    
    const char* getParamAddressDsp(dsp* dsp, int p); 	///< returns the name of parameter p
    const char* getParamUnitDsp(dsp* dsp, int p); 		///< returns the name of parameter p
    FAUSTFLOAT getParamMinDsp(dsp* dsp, int p);         ///< returns the min value of parameter p
    FAUSTFLOAT getParamMaxDsp(dsp* dsp, int p);         ///< returns the max value of parameter p
    FAUSTFLOAT getParamStepDsp(dsp* dsp, int p);        ///< returns the min value of parameter p

    FAUSTFLOAT getParamValueDsp(dsp* dsp, int p);           ///< returns the value of parameter p
    void  setParamValueDsp(dsp* dsp, int p, FAUSTFLOAT v); 	///< set the value of parameter p
        
    FAUSTFLOAT getParamRatioDsp(dsp* dsp, int p);           ///< returns the ratio (normalized value in 0..1) of parameter p
    void  setParamRatioDsp(dsp* dsp, int p, FAUSTFLOAT v); 	///< set the ratio (normalized value in 0..1) of parameter p

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
    

/************************************************************************
************************************************************************/

#ifdef __cplusplus
}
#endif
