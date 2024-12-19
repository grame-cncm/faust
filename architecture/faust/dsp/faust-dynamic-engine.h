/************************** BEGIN faust-dynamic-engine.h **********************
 FAUST Architecture File
 Copyright (C) 2003-2023 GRAME, Centre National de Creation Musicale
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

/*
 * This file describes a simple C API for Faust objects including the audio drivers.
 * Faust objects are built with createDsp, then initialized with initDsp and the sampling rate and buffer size.
 * Then start() is called to open the drivers and start processing audio until stop() is called.
 * All parameters can be accessed and controlled (typically using getParamsCountDsp/setParamValueDsp/getParamValueDsp).
 *
 * To be compiled with something like:
 * c++ -std=c++11 -DLLVM_DSP -DPORTAUDIO_DRIVER -DSOUNDFILE faust-dynamic-engine.cpp
 * and linked with libfaust (either static or dynamic version, libsndfile (https://github.com/libsndfile/libsndfile)
 * and PortAudio (https://www.portaudio.com).
 *
 * The Interpreter backend can possibly be used instead of LLVM, using INTERP_DSP compilation flag as in:
 * c++ -std=c++11 -DINTERP_DSP -DPORTAUDIO_DRIVER -DSOUNDFILE faust-dynamic-engine.cpp
 *
 * Several different audio drivers can possibly be compiled (to be chosen at init time). With something like:
 * c++ -std=c++11 -DLLVM_DSP -DPORTAUDIO_DRIVER -DRTAUDIO_DRIVER -DJACK_DRIVER -DSOUNDFILE faust-dynamic-engine.cpp
 * and adding the needed libraries at link time.
 *
 * JACK (https://jackaudio.org) can possibly be used instead of PortAudio to provide a "multiple connectable DSP" experience:
 * each DSP is created with createDsp/initDsp, then connected to other with getNumInputsDsp/getNumOutputsDsp and
 * connectDsp/disconnectDsp/isConnectedDsp functions, or using an external connection tool
 * like QjackCtl (https://qjackctl.sourceforge.io).
 */

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef CTree_DEFINED
#ifdef _MSC_VER
    typedef void CTree;
#else
    typedef struct {} CTree;
#endif
#endif
    
    typedef CTree* Box;
    typedef CTree* Signal;
    
    /**
     * @brief Opaque structure representing a DSP object.
     */
    typedef struct {} dsp;
    
    /**
     * @brief Renderer types for different platforms.
     */
    enum RendererType {
        kPortAudioRenderer,   ///< PortAudio
        kRtAudioRenderer,     ///< RtAudio
        kJackRenderer,        ///< JACK Audio Connection Kit
        kCoreAudioRenderer,   ///< Apple Core Audio
        kiOSRenderer,         ///< iOS Audio
        kAlsaRenderer,        ///< Advanced Linux Sound Architecture
        kAndroidRenderer      ///< Android Audio
    };
    
    /**
     * @brief Get the last error message.
     *
     * @return A pointer to the last error message.
     */
    const char* getLastError();
    
    /**
     * @brief Create a DSP object.
     *
     * This function creates a new DSP object using the provided parameters. The created DSP object can be used for audio processing.
     *
     * @param name_app - the name of the Faust program.
     * @param dsp_content - the Faust program as a string
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters (like -vec.etc.)
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *               using an empty string takes the current machine settings,
     *               and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor, not used if compiled with INTERP_DSP mode.
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'),
     * not used if compiled with INTERP_DSP mode.
     *
     * @return A pointer to the created DSP object on success, otherwise a null pointer. Use getLastError to access the error.
     */
    dsp* createDsp(const char* name_app, const char* dsp_content, int argc, const char* argv[], const char* target, int opt_level);
    
    /**
     * @brief Create a DSP object.
     *
     * This function creates a new DSP object using the provided parameters. The created DSP object can be used for audio processing.
     *
     * @param name_app - the name of the Faust program
     * @param box - the box expression
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters (like -vec.etc.)
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'),
     * not used if compiled with INTERP_DSP mode.
     *
     * @return A pointer to the created DSP object on success, otherwise a null pointer. Use getLastError to access the error.
     */
    dsp* createDspFromBoxes(const char* name_app, Box box, int argc, const char* argv[], const char* target, int opt_level);
    
    /**
     * @brief Create a DSP object.
     *
     * This function creates a new DSP object using the provided parameters. The created DSP object can be used for audio
     * processing.
     *
     * @param name_app - the name of the Faust program
     * @param signals - the null terminated array of output signals
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters (like -vec.etc.)
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'),
     * not used if compiled with INTERP_DSP mode.
     *
     * @return A pointer to the created DSP object on success, otherwise a null pointer. Use getLastError to access the error.
     */
    dsp* createDspFromSignals(const char* name_app, Signal* signals, int argc, const char* argv[], const char* target, int opt_level);
    
    /**
     * @brief Destroy a DSP object.
     *
     * @param dsp Pointer to the DSP object to destroy.
     */
    void destroyDsp(dsp* dsp);
    
    /**
     * @brief Initialize the DSP object.
     *
     * @param dsp - pointer to the DSP object
     * @param renderer - renderer type
     * @param sr - sample rate in Hz. Not used when kJackRenderer is used, since sr will be imposed by the JACK server
     * @param bsize - buffer size in samples. Not used when kJackRenderer is used, since bs will be imposed by the JACK server
     *
     * @return True if initialization is successful, false otherwise.
     */
    bool initDsp(dsp* dsp, RendererType renderer, int sr, int bsize);
    
    /**
     * @brief Start processing audio.
     *
     * @param dsp - pointer to the DSP object
     *
     * @return True if the start is successful, false otherwise.
     */
    bool startDsp(dsp* dsp);
    
    /**
     * @brief Stop processing audio.
     *
     * @param dsp - pointer to the DSP object
     */
    void stopDsp(dsp* dsp);
    
    /*
     * When used with JACK:
     * - using NULL for dsp1 means physical input
     * - using NULL for dsp2 means physical output
     */
    
    /**
     * @brief Get the number of input ports.
     *
     * @param dsp - pointer to the DSP object
     * @return The number of input ports.
     */
    int getNumInputsDsp(dsp* dsp);
    
    /**
     * @brief Get the number of output ports.
     *
     * @param dsp - pointer to the DSP object
     *
     * @return The number of output ports.
     */
    int getNumOutputsDsp(dsp* dsp);
    
    /**
     * @brief Connect two DSP objects.
     *
     * @param dsp1 - source DSP object
     * @param dsp2 - destination DSP object
     * @param src - source port index
     * @param dst - destination port index
     */
    void connectDsp(dsp* dsp1, dsp* dsp2, int src, int dst);
    
    /**
     * @brief Disconnect two DSP objects.
     *
     * @param dsp1 - source DSP object
     * @param dsp2 - destination DSP object
     * @param src - source port index
     * @param dst - destination port index
     */
    void disconnectDsp(dsp* dsp1, dsp* dsp2, int src, int dst);
    
    /**
     * @brief Check if two DSP objects are connected.
     *
     * @param dsp1 - source DSP object
     * @param dsp2 - destination DSP object
     * @param src - source port index
     * @param dst - destination port index
     *
     * @return True if connected, false otherwise.
     */
    bool isConnectedDsp(dsp* dsp1, dsp* dsp2, int src, int dst);
    
    /**
     * @brief Retrieve JSON description of the UI.
     *
     * @param dsp - pointer to the DSP object
     *
     * @return A pointer to the JSON description.
     */
    const char* getJSONDsp(dsp* dsp);
    
    /**
     * @brief Get the count of parameters in the DSP object.
     *
     * @param dsp_ext - pointer to the DSP object
     *
     * @return The count of parameters.
     */
    int getParamsCountDsp(dsp* dsp_ext);
    
    /**
     * @brief Get the index of a parameter by its name.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param name - name of the parameter
     *
     * @return The index of the parameter, or -1 if not found.
     */
    int getParamIndexDsp(dsp* dsp_ext, const char* name);
    
    /**
     * @brief Get the address of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     *
     * @return The memory address of the parameter.
     */
    const char* getParamAddressDsp(dsp* dsp_ext, int p);
    
    /**
     * @brief Get the unit of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     * 
     * @return The unit of the parameter, or NULL if not specified.
     */
    const char* getParamUnitDsp(dsp* dsp_ext, int p);
    
    /**
     * @brief Get the minimum value of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     *
     * @return The minimum value of the parameter.
     */
    FAUSTFLOAT getParamMinDsp(dsp* dsp_ext, int p);
    
    /**
     * @brief Get the maximum value of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     *
     * @return The maximum value of the parameter.
     */
    FAUSTFLOAT getParamMaxDsp(dsp* dsp_ext, int p);
    
    /**
     * @brief Get the step value of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     *
     * @return The step value of the parameter.
     */
    FAUSTFLOAT getParamStepDsp(dsp* dsp_ext, int p);
    
    /**
     * @brief Get the value of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     *
     * @return The current value of the parameter.
     */
    FAUSTFLOAT getParamValueDsp(dsp* dsp_ext, int p);
    
    /**
     * @brief Set the value of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter.
     * @param val - new value for the parameter.
     */
    void setParamValueDsp(dsp* dsp_ext, int p, FAUSTFLOAT val);
    
    /**
     * @brief Get the ratio value of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     *
     * @return The ratio value of the parameter.
     */
    FAUSTFLOAT getParamRatioDsp(dsp* dsp_ext, int p);
    
    /**
     * @brief Set the ratio value of a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     * @param v - new ratio value for the parameter
     */
    void setParamRatioDsp(dsp* dsp_ext, int p, FAUSTFLOAT v);
    
    /**
     * @brief Convert a value to a ratio using a parameter's settings.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     * @param r - raw value to be converted
     *
     * @return The converted ratio value.
     */
    FAUSTFLOAT value2ratioDsp(dsp* dsp_ext, int p, FAUSTFLOAT r);
    
    /**
     * @brief Convert a ratio to a value using a parameter's settings.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     * @param r - ratio value to be converted
     *
     * @return The converted raw value.
     */
    FAUSTFLOAT ratio2valueDsp(dsp* dsp_ext, int p, FAUSTFLOAT r);
    
    /**
     * @brief Propagate accelerometer influence to related parameters.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param acc - accelerometer type
     * @param val - accelerometer value
     */
    void propagateAccDsp(dsp* dsp_ext, int acc, FAUSTFLOAT val);
    
    /**
     * @brief Set accelerometer converter settings for a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     * @param acc - accelerometer type
     * @param curve - accelerometer curve
     * @param amin - minimum value
     * @param amid - middle value
     * @param amax - maximum value
     */
    void setAccConverterDsp(dsp* dsp_ext, int p, int acc, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax);
    
    /**
     * @brief Get accelerometer converter settings for a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     * @param acc - pointer to store accelerometer type
     * @param curve - pointer to store accelerometer curve
     * @param amin - pointer to store minimum value
     * @param amid - pointer to store middle value
     * @param amax - pointer to store maximum value
     */
    void getAccConverterDsp(dsp* dsp_ext, int p, int* acc, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax);
    
    /**
     * @brief Propagate gyroscope influence to related parameters.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param gyr - gyroscope type
     * @param val - gyroscope value
     */
    void propagateGyrDsp(dsp* dsp_ext, int gyr, FAUSTFLOAT val);
    
    /**
     * @brief Set gyroscope converter settings for a parameter.
     *
     * @param dsp_ext - pointer to the DSP object.
     * @param p - index of the parameter
     * @param gyr - gyroscope type
     * @param curve - gyroscope curve.
     * @param amin - minimum value.
     * @param amid - middle value.
     * @param amax - maximum value.
     */
    void setGyrConverterDsp(dsp* dsp_ext, int p, int gyr, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax);
    
    /**
     * @brief Get gyroscope converter settings for a parameter.
     *
     * @param dsp_ext - pointer to the DSP object
     * @param p - index of the parameter
     * @param gyr - pointer to store gyroscope type
     * @param curve - pointer to store gyroscope curve
     * @param amin - pointer to store minimum value
     * @param amid - pointer to store middle value
     * @param amax - pointer to store maximum value
     */
    void getGyrConverterDsp(dsp* dsp_ext, int p, int* gyr, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax);
    
#ifdef __cplusplus
}
#endif

/************************** END faust-dynamic-engine.h **************************/
