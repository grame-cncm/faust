/************************** BEGIN android-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __android_dsp__
#define __android_dsp__

#include <android/log.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <time.h>

#include "faust/audio/audio.h"

#define CONV16BIT 32767.f
#define CONVMYFLT (1.f/32767.f)

#define NUM_INPUTS 2
#define NUM_OUTPUTS 2
#define CPU_TABLE_SIZE 16

static const char* res_str(SLresult result)
{
    switch(result)
    {
        case SL_RESULT_SUCCESS: return "Success";
        case SL_RESULT_PRECONDITIONS_VIOLATED: return "Preconditions violated";
        case SL_RESULT_PARAMETER_INVALID: return "Parameter invalid";
        case SL_RESULT_MEMORY_FAILURE: return "Memory failure";
        case SL_RESULT_RESOURCE_ERROR: return "Resource error";
        case SL_RESULT_RESOURCE_LOST: return "Resource lost";
        case SL_RESULT_IO_ERROR: return "I/O error";
        case SL_RESULT_BUFFER_INSUFFICIENT: return "Buffer insufficient";
        case SL_RESULT_CONTENT_CORRUPTED: return "Content corrupted";
        case SL_RESULT_CONTENT_UNSUPPORTED: return "Content unsupported";
        case SL_RESULT_CONTENT_NOT_FOUND: return "Content not found";
        case SL_RESULT_PERMISSION_DENIED: return "Permission denied";
        case SL_RESULT_FEATURE_UNSUPPORTED: return "Feature unsupported";
        case SL_RESULT_INTERNAL_ERROR: return "Internal error";
        case SL_RESULT_UNKNOWN_ERROR: return "Unknown error";
        case SL_RESULT_OPERATION_ABORTED: return "Operation aborted";
        case SL_RESULT_CONTROL_LOST: return "Control lost";
#ifdef SL_RESULT_READONLY
        case SL_RESULT_READONLY: return "ReadOnly";
#endif
#ifdef SL_RESULT_ENGINEOPTION_UNSUPPORTED
        case SL_RESULT_ENGINEOPTION_UNSUPPORTED: return "Engine option unsupported";
#endif
#ifdef SL_RESULT_SOURCE_SINK_INCOMPATIBLE
        case SL_RESULT_SOURCE_SINK_INCOMPATIBLE: return "Source/Sink incompatible";
#endif
    }
    return "Unknown error code";
}

struct CircularBuffer {
    
    short* fBuffer;
    int fReadIndex;
    int fWriteIndex;
    int fSize;
    int fChan;
    
    CircularBuffer(int frames, int chan)
    {
        fBuffer = new short[frames * chan];
        memset(fBuffer, 0, sizeof(short) * frames * chan);
        fSize = frames;
        fChan = chan;
        fReadIndex = 0;
        fWriteIndex = frames/2; // Set write index in the middle
    }
    
    ~CircularBuffer()
    {
        delete [] fBuffer;
    }
    
    short* getWritePtr() { return &fBuffer[fWriteIndex * fChan]; }
    short* getReadPtr() { return &fBuffer[fReadIndex * fChan]; }
    
    void moveWritePtr(int frames)
    {
        //__android_log_print(ANDROID_LOG_ERROR, "Faust", "moveWritePtr %x fWriteIndex = %ld", this, fWriteIndex);
        fWriteIndex = (fWriteIndex + frames) % fSize;
    }
    void moveReadPtr(int frames)
    {
        //__android_log_print(ANDROID_LOG_ERROR, "Faust", "moveReadPtr %x fReadIndex = %ld", this,  fReadIndex);
        fReadIndex = (fReadIndex + frames) % fSize;
    }
    
};

//http://stackoverflow.com/questions/17188761/how-to-obtain-computation-time-in-ndk

class androidaudio : public audio {
    
    protected:
    
        dsp* fDSP;
        
        int	fNumInChans;
        int	fNumOutChans;
        
        unsigned int fSampleRate;
        unsigned int fBufferSize;
    
        int64_t fCPUTable[CPU_TABLE_SIZE];
        int64_t fCPUTableIndex;
    
        float** fInputs;
        float** fOutputs;
    
        CircularBuffer fOpenSLInputs;
        CircularBuffer fOpenSLOutputs;
    
        SLObjectItf fOpenSLEngine, fOutputMix, fInputBufferQueue, fOutputBufferQueue;
        SLAndroidSimpleBufferQueueItf fOutputBufferQueueInterface, fInputBufferQueueInterface;
    
        SLRecordItf fRecordInterface;
        SLPlayItf fPlayInterface;
    
        int64_t getTimeUsec() 
        {
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            return ((int64_t) now.tv_sec * 1000000000LL + now.tv_nsec)/1000;
        }
    
        void processAudio()
        {
            int64_t t1 = getTimeUsec();
       
            // Converting short input to float
            if (fNumInChans > 0) {
                short* input = fOpenSLInputs.getReadPtr();
                for (int chan = 0; chan < NUM_INPUTS; chan++) {
                    for (int i  = 0; i < fBufferSize; i++) {
                        fInputs[chan][i] = float(input[i * NUM_INPUTS + chan] * CONVMYFLT);
                    }
                }
                fOpenSLInputs.moveReadPtr(fBufferSize);
            }
            
            // Compute DSP
            fDSP->compute(fBufferSize, fInputs, fOutputs);
            
            runControlCallbacks();
            
            // Converting float to short output
            if (fNumOutChans > 0) {
                short* output = fOpenSLOutputs.getWritePtr();
                for (int chan = 0; chan < NUM_OUTPUTS; chan++) {
                    for (int i = 0; i < fBufferSize; i++) {
                        output[i * NUM_OUTPUTS + chan] = short(min(1.f, max(-1.f, fOutputs[chan][i])) * CONV16BIT);
                    }
                }
                fOpenSLOutputs.moveWritePtr(fBufferSize);
            }
            
            int64_t t2 = getTimeUsec();
            fCPUTable[(fCPUTableIndex++)&(CPU_TABLE_SIZE-1)] = t2 - t1;
        }
    
        static void inputCallback(SLAndroidSimpleBufferQueueItf caller, void* arg)
        {
            androidaudio* obj = (androidaudio*)arg;
            obj->inputCallback(caller);
        }
    
        void inputCallback(SLAndroidSimpleBufferQueueItf caller)
        {
            SLresult result = (*caller)->Enqueue(caller, fOpenSLInputs.getWritePtr(), fBufferSize * sizeof(short) * NUM_INPUTS);
            fOpenSLInputs.moveWritePtr(fBufferSize);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "inputCallback Enqueue error = %s", res_str(result));
            }
        }
    
        static void outputCallback(SLAndroidSimpleBufferQueueItf caller, void* arg)
        {
            androidaudio* obj = (androidaudio*)arg;
            obj->outputCallback(caller);
        }
    
        void outputCallback(SLAndroidSimpleBufferQueueItf caller)
        {
            // Output callback drives DSP computation
            processAudio();
            
            SLresult result = (*caller)->Enqueue(caller, fOpenSLOutputs.getReadPtr(), fBufferSize * sizeof(short) * NUM_OUTPUTS);
            fOpenSLOutputs.moveReadPtr(fBufferSize);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "outputCallback Enqueue error = %s", res_str(result));
            }
        }
    
        void destroy()
        {
            if (fInputBufferQueue) {
                (*fInputBufferQueue)->Destroy(fInputBufferQueue);
                fInputBufferQueue = NULL;
            }
            
            if (fOutputBufferQueue) {
                (*fOutputBufferQueue)->Destroy(fOutputBufferQueue);
                fOutputBufferQueue = NULL;
            }
            
            if (fOutputMix) {
                (*fOutputMix)->Destroy(fOutputMix);
                fOutputMix = NULL;
            }
            
            if (fOpenSLEngine) {
                (*fOpenSLEngine)->Destroy(fOpenSLEngine);
                fOpenSLEngine = NULL;
            }
        }
    
    public:
    
        androidaudio(long srate, long bsize)
        : fDSP(NULL), fSampleRate(srate),
        fBufferSize(bsize), fCPUTableIndex(0), fNumInChans(0), fNumOutChans(0),
        fOpenSLEngine(NULL), fOutputMix(NULL), fInputBufferQueue(NULL), fOutputBufferQueue(NULL),
        fOpenSLInputs(bsize * 4, NUM_INPUTS), fOpenSLOutputs(bsize * 4, NUM_OUTPUTS)
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "Constructor");
            
            // Allocating memory for input channels.
            fInputs = new float*[NUM_INPUTS];
            for (int i = 0; i < NUM_INPUTS; i++) {
                fInputs[i] = new float[fBufferSize];
                memset(fInputs[i], 0, fBufferSize * sizeof(float));
            }
    
            // Allocating memory for output channels.
            fOutputs = new float*[NUM_OUTPUTS];
            for (int i = 0; i < NUM_OUTPUTS; i++) {
                fOutputs[i] = new float[fBufferSize];
                memset(fOutputs[i], 0, fBufferSize * sizeof(float));
            }
        }

        virtual ~androidaudio()
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "Destructor");
            destroy();
            
            for (int i = 0; i < NUM_INPUTS; i++) {
                delete [] fInputs[i];
            }
            delete [] fInputs;
           
            for (int i = 0; i < NUM_OUTPUTS; i++) {
                delete [] fOutputs[i];
            }
            delete [] fOutputs;
        }
    
        virtual bool init(const char* name, dsp* DSP)
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "init");
            
            fDSP = DSP;
            fNumInChans = fDSP->getNumInputs();
            fNumOutChans = fDSP->getNumOutputs();
            fDSP->init(fSampleRate);
            
            static const SLboolean requireds[2] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
            SLresult result;
            SLuint32 sr;
            
            switch (fSampleRate) {
                    
                case 8000:
                    sr = SL_SAMPLINGRATE_8;
                    break;
                case 11025:
                    sr = SL_SAMPLINGRATE_11_025;
                    break;
                case 16000:
                    sr = SL_SAMPLINGRATE_16;
                    break;
                case 22050:
                    sr = SL_SAMPLINGRATE_22_05;
                    break;
                case 24000:
                    sr = SL_SAMPLINGRATE_24;
                    break;
                case 32000:
                    sr = SL_SAMPLINGRATE_32;
                    break;
                case 44100:
                    sr = SL_SAMPLINGRATE_44_1;
                    break;
                case 48000:
                    sr = SL_SAMPLINGRATE_48;
                    break;
                case 64000:
                    sr = SL_SAMPLINGRATE_64;
                    break;
                case 88200:
                    sr = SL_SAMPLINGRATE_88_2;
                    break;
                case 96000:
                    sr = SL_SAMPLINGRATE_96;
                    break;
                case 192000:
                    sr = SL_SAMPLINGRATE_192;
                    break;
                default:
                    return false;
            }
            
            destroy();
          
            // Create the OpenSL ES engine.
            result = slCreateEngine(&fOpenSLEngine, 0, NULL, 0, NULL, NULL);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "slCreateEngine/fOpenSLEngine error = %s", res_str(result));
                return false;
            }
            
            result = (*fOpenSLEngine)->Realize(fOpenSLEngine, SL_BOOLEAN_FALSE);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "Realize/fOpenSLEngine error = %s", res_str(result));
                return false;
            }
            
            SLEngineItf openSLEngineInterface = NULL;
            result = (*fOpenSLEngine)->GetInterface(fOpenSLEngine, SL_IID_ENGINE, &openSLEngineInterface);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "GetInterface/fOpenSLEngine error = %s", res_str(result));
                return false;
            }
            
            // Create the output mix.
            result = (*openSLEngineInterface)->CreateOutputMix(openSLEngineInterface, &fOutputMix, 0, NULL, NULL);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "CreateOutputMix/openSLEngineInterface error = %s", res_str(result));
                return false;
            }
            
            result = (*fOutputMix)->Realize(fOutputMix, SL_BOOLEAN_FALSE);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "Realize/fOutputMix error = %s", res_str(result));
                return false;
            }
        
            SLDataLocator_OutputMix outputMixLocator = { SL_DATALOCATOR_OUTPUTMIX, fOutputMix };
            
            if (fNumInChans > 0) {
                // Create the input buffer queue.
                SLDataLocator_IODevice deviceInputLocator = { SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT, SL_DEFAULTDEVICEID_AUDIOINPUT, NULL };
                SLDataSource inputSource = { &deviceInputLocator, NULL };
                SLDataLocator_AndroidSimpleBufferQueue inputLocator = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 1 };
                SLDataFormat_PCM inputFormat = { SL_DATAFORMAT_PCM, 2, sr, SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16, SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN };
                SLDataSink inputSink = { &inputLocator, &inputFormat };
                const SLInterfaceID inputInterfaces[2] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE, SL_IID_ANDROIDCONFIGURATION };
                
                result = (*openSLEngineInterface)->CreateAudioRecorder(openSLEngineInterface, &fInputBufferQueue, &inputSource, &inputSink, 2, inputInterfaces, requireds);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "CreateAudioRecorder/openSLEngineInterface error = %s", res_str(result));
                    return false;
                }
                
            #if DISABLE_AGC
                SLAndroidConfigurationItf configObject;
                result = (*fInputBufferQueue)->GetInterface(fInputBufferQueue, SL_IID_ANDROIDCONFIGURATION, &configObject);
                if (result == SL_RESULT_SUCCESS) {
                    //SLuint32 mode = SL_ANDROID_RECORDING_PRESET_GENERIC;
                    SLuint32 mode = SL_ANDROID_RECORDING_PRESET_VOICE_RECOGNITION;
                    result = (*configObject)->SetConfiguration(configObject, SL_ANDROID_KEY_RECORDING_PRESET, &mode, sizeof(mode));
                    if (result != SL_RESULT_SUCCESS) {
                       __android_log_print(ANDROID_LOG_ERROR, "Faust", "SetConfiguration SL_ANDROID_KEY_RECORDING_PRESET error = %s", res_str(result));
                    }
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "GetInterface SL_IID_ANDROIDCONFIGURATION error = %s", res_str(result));
                }
            #endif
                
                result = (*fInputBufferQueue)->Realize(fInputBufferQueue, SL_BOOLEAN_FALSE);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "Realize/fInputBufferQueue error = %s", res_str(result));
                    return false;
                }
            }
            
            if (fNumOutChans > 0) {
                // Create the output buffer queue.
                SLDataLocator_AndroidSimpleBufferQueue outputLocator = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 1 };
                SLDataFormat_PCM outputFormat = { SL_DATAFORMAT_PCM, 2, sr, SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16, SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN };
                SLDataSource outputSource = { &outputLocator, &outputFormat };
                const SLInterfaceID outputInterfaces[1] = { SL_IID_BUFFERQUEUE };
                SLDataSink outputSink = { &outputMixLocator, NULL };
                
                result = (*openSLEngineInterface)->CreateAudioPlayer(openSLEngineInterface, &fOutputBufferQueue, &outputSource, &outputSink, 1, outputInterfaces, requireds);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "CreateAudioPlayer/openSLEngineInterface error  = %s", res_str(result));
                    return false;
                }
                
                result = (*fOutputBufferQueue)->Realize(fOutputBufferQueue, SL_BOOLEAN_FALSE);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "Realize/fOutputBufferQueue error = %s", res_str(result));
                    return false;
                }
            }
            
            if (fNumInChans > 0) { // Initialize
                
                result = (*fInputBufferQueue)->GetInterface(fInputBufferQueue, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &fInputBufferQueueInterface);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "GetInterface/fInputBufferQueue error = %s", res_str(result));
                    return false;
                }
                
                result = (*fInputBufferQueueInterface)->RegisterCallback(fInputBufferQueueInterface, inputCallback, this);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "RegisterCallback/fInputBufferQueueInterface error = %s", res_str(result));
                    return false;
                }
                
                result = (*fInputBufferQueue)->GetInterface(fInputBufferQueue, SL_IID_RECORD, &fRecordInterface);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "GetInterface/fInputBufferQueue error = %s", res_str(result));
                    return false;
                }
                
                result = (*fInputBufferQueueInterface)->Enqueue(fInputBufferQueueInterface,
                                                                fOpenSLInputs.getWritePtr(),
                                                                fBufferSize * sizeof(short) * NUM_INPUTS);
                fOpenSLInputs.moveWritePtr(fBufferSize);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "Enqueue/fInputBufferQueueInterface error = %s", res_str(result));
                    return false;
                }
                
                result = (*fRecordInterface)->SetRecordState(fRecordInterface, SL_RECORDSTATE_STOPPED);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "SetRecordState/fRecordInterface error = %s", res_str(result));
                }
            }
            
            if (fNumOutChans > 0) { // Initialize
              
                result = (*fOutputBufferQueue)->GetInterface(fOutputBufferQueue, SL_IID_BUFFERQUEUE, &fOutputBufferQueueInterface);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "GetInterface/fOutputBufferQueue error = %s", res_str(result));
                    return false;
                }
                
                result = (*fOutputBufferQueueInterface)->RegisterCallback(fOutputBufferQueueInterface, outputCallback, this);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "RegisterCallback/fOutputBufferQueueInterface error = %s", res_str(result));
                    return false;
                }
                
                result = (*fOutputBufferQueue)->GetInterface(fOutputBufferQueue, SL_IID_PLAY, &fPlayInterface);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "GetInterface/fOutputBufferQueue error = %s", res_str(result));
                    return false;
                }
                
                result = (*fOutputBufferQueueInterface)->Enqueue(fOutputBufferQueueInterface,
                                                                 fOpenSLOutputs.getReadPtr(),
                                                                 fBufferSize * sizeof(short) * NUM_OUTPUTS);
                fOpenSLOutputs.moveReadPtr(fBufferSize);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "Enqueue/fOutputBufferQueueInterface error = %s", res_str(result));
                    return false;
                }
                
                result = (*fPlayInterface)->SetPlayState(fPlayInterface, SL_PLAYSTATE_STOPPED);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "SetPlayState/fPlayInterface error = %s", res_str(result));
                }
            }
            
            return true;
        }
    
        virtual bool start()
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "start");
            SLresult result;
            
            if (fNumInChans > 0) {
                // start the inout buffer queue.
                result = (*fRecordInterface)->SetRecordState(fRecordInterface, SL_RECORDSTATE_RECORDING);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "SetRecordState/fRecordInterface error = %s", res_str(result));
                }
            }
            
            if (fNumOutChans > 0) {
                // start the output buffer queue.
                result = (*fPlayInterface)->SetPlayState(fPlayInterface, SL_PLAYSTATE_PLAYING);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "SetPlayState/fPlayInterface error = %s", res_str(result));
                }
            }
            
            return true;
        }
        
        virtual void stop()
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "stop");
            SLresult result;
            
            if (fNumInChans > 0) {
                result = (*fRecordInterface)->SetRecordState(fRecordInterface, SL_RECORDSTATE_PAUSED);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "SetRecordState/fRecordInterface error = %s", res_str(result));
                }
            }
            
            if (fNumOutChans > 0) {
                result = (*fPlayInterface)->SetPlayState(fPlayInterface, SL_PLAYSTATE_PAUSED);
                if (result != SL_RESULT_SUCCESS) {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "SetPlayState/fPlayInterface error = %s", res_str(result));
                }
            }
        }
    
        virtual int getBufferSize()
        {
            return fBufferSize;
        }
        
        virtual int getSampleRate()
        {
            return fSampleRate;
        }
        
        virtual int getNumInputs()
        {
            return fNumInChans;
        }
        
        virtual int getNumOutputs()
        {
            return fNumOutChans;
        }
    
        // Returns the average proportion of available CPU being spent inside the audio callbacks (between 0 and 1.0).
        float getCPULoad()
        {
            float sum = 0.f;
            for (int i = 0; i < CPU_TABLE_SIZE; i++) {
                sum += fCPUTable[i];
            }
            return (sum/float(CPU_TABLE_SIZE))/(1000000.f*float(fBufferSize)/float(fSampleRate));
        }
    
};

#endif
/**************************  END  android-dsp.h **************************/
