
/************************************************************************
FAUST API
Copyright (C) 2015 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This file describe a simple C API for Faust objects including the audio
drivers.

 ************************************************************************
 ************************************************************************/
    
/*
 * Faust objects are first initialized with the desired name, and optionally 
 * sampling rate and buffer size. Then start() is called to open the drivers and 
 * start processing audio until stop() is called.
 */

#ifdef __cplusplus
extern "C"
{
#endif
 
typedef struct {} dsp;

enum { kPortAudioRenderer = 0, kJackRenderer, kCoreAudioRenderer };

const char* getLastError();

// Creation API
dsp* create1(const char* name_app, const char* dsp_content);
dsp* create2(const char* name_app, const char* dsp_content, const char* argv, const char* target, int opt_level);

void destroy(dsp* dsp);

bool init1(dsp* dsp, const char* name);                                     ///< init Faust object with default system values
bool init2(dsp* dsp, const char* name, int renderer, int sr, int bsize);	///< init the Faust object

bool start(dsp* dsp);			///< open the audio drivers and starts processing audio
void stop(dsp* dsp);			///< stop processing audio and closes the audio drivers

// Connection API 
int getNumInputs(dsp* dsp);
int getNumOutputs(dsp* dsp);

int getNumPhysicalInputs();
int getNumPhysicalOutputs();

void connect(dsp* dsp1, dsp* dsp2, int src, int dst);
void disconnect(dsp* dsp1, dsp* dsp2, int src, int dst);
bool isConnected(dsp* dsp1, dsp* dsp2, int src, int dst);

/*
 * Faust objects have control parameters that can be read and changed.
 * getParamsCount() returns the number n of such parameters
 *
 * getParamName(int index) retrieves the name of a parameter by its index
 * getParamIndex(const char* name) retrieves the index of a parameter by its name
 *
 * getNamedParam(const char* name) retrieves the value of a parameter by its name
 * getIndexParam(int i) retrieves the value of a parameter by its index
 */
const char* getJSON(dsp* dsp);					///< JSON description of the UI

int getParamsCount(dsp* dsp);					///< number of control parameters

int getParamIndex(dsp* dsp, const char* name); 	///< returns the index of parameter name or -1
const char* getParamName(dsp* dsp, int p); 		///< returns the name of parameter p
const char* getParamUnit(dsp* dsp, int p); 		///< returns the name of parameter p
float getParamMin(dsp* dsp, int p); 			///< returns the min value of parameter p
float getParamMax(dsp* dsp, int p); 			///< returns the max value of parameter p
float getParamStep(dsp* dsp, int p); 			///< returns the min value of parameter p
	
float getParamValue(dsp* dsp, int p); 			///< returns the value of parameter p
void  setParamValue(dsp* dsp, int p, float v); 	///< set the value of parameter p
	
float getParamRatio(dsp* dsp, int p); 			///< returns the ratio (normalized value in 0..1) of parameter p
void  setParamRatio(dsp* dsp, int p, float v); 	///< set the ratio (normalized value in 0..1) of parameter p

void propagateAccX(dsp* dsp, float a);			///< propagate x accelerometer influence to related parameters
void propagateAccY(dsp* dsp, float a);			///< propagate y accelerometer influence to related parameters
void propagateAccZ(dsp* dsp, float a);			///< propagate z accelerometer influence to related parameters

/************************************************************************
************************************************************************/

#ifdef __cplusplus
}
#endif
