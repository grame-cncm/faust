
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
dsp* create1Dsp(const char* name_app, const char* dsp_content);
dsp* create2Dsp(const char* name_app, const char* dsp_content, const char* argv, const char* target, int opt_level);

void destroyDsp(dsp* dsp);

bool init1Dsp(dsp* dsp, const char* name);                                      ///< init Faust object with default system values
bool init2Dsp(dsp* dsp, const char* name, int renderer, int sr, int bsize);     ///< init the Faust object

bool startDsp(dsp* dsp);    ///< open the audio drivers and starts processing audio
void stopDsp(dsp* dsp);     ///< stop processing audio and closes the audio drivers

// Connection API
int getNumInputsDsp(dsp* dsp);  // Using NULL means physical input
int getNumOutputsDsp(dsp* dsp); // Using NULL means physical output

// Using NULL for dsp1 means physical input, NULL for dsp2 means physical output
void connectDsp(dsp* dsp1, dsp* dsp2, int src, int dst);        
void disconnectDsp(dsp* dsp1, dsp* dsp2, int src, int dst);
bool isConnectedDsp(dsp* dsp1, dsp* dsp2, int src, int dst);

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
const char* getJSONDsp(dsp* dsp);					///< JSON description of the UI

int getParamsCountDsp(dsp* dsp);					///< number of control parameters

int getParamIndexDsp(dsp* dsp, const char* name); 	///< returns the index of parameter name or -1
const char* getParamNameDsp(dsp* dsp, int p); 		///< returns the name of parameter p
const char* getParamUnitDsp(dsp* dsp, int p); 		///< returns the name of parameter p
float getParamMinDsp(dsp* dsp, int p);              ///< returns the min value of parameter p
float getParamMaxDsp(dsp* dsp, int p);              ///< returns the max value of parameter p
float getParamStepDsp(dsp* dsp, int p); 			///< returns the min value of parameter p
	
float getParamValueDsp(dsp* dsp, int p); 			///< returns the value of parameter p
void  setParamValueDsp(dsp* dsp, int p, float v); 	///< set the value of parameter p
	
float getParamRatioDsp(dsp* dsp, int p); 			///< returns the ratio (normalized value in 0..1) of parameter p
void  setParamRatioDsp(dsp* dsp, int p, float v); 	///< set the ratio (normalized value in 0..1) of parameter p

void propagateAccXDsp(dsp* dsp, float a);			///< propagate x accelerometer influence to related parameters
void propagateAccYDsp(dsp* dsp, float a);			///< propagate y accelerometer influence to related parameters
void propagateAccZDsp(dsp* dsp, float a);			///< propagate z accelerometer influence to related parameters

void propagateGyrXDsp(dsp* dsp, float a);			///< propagate x gyroscope influence to related parameters
void propagateGyrYDsp(dsp* dsp, float a);			///< propagate y gyroscope influence to related parameters
void propagateGyrZDsp(dsp* dsp, float a);			///< propagate z gyroscope influence to related parameters

/************************************************************************
************************************************************************/

#ifdef __cplusplus
}
#endif
