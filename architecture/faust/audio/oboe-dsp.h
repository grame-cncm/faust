/************************** BEGIN oboe-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef __oboe_dsp__
#define __oboe_dsp__

#include <android/log.h>
#include <oboe/Oboe.h>
#include <time.h>
#include <assert.h>
#include <vector>

#include "faust/audio/audio.h"
#include "faust/dsp/dsp-tools.h"

#define CPU_TABLE_SIZE 16

//http://stackoverflow.com/questions/17188761/how-to-obtain-computation-time-in-ndk

class oboeaudio : public audio, public oboe::AudioStreamCallback {
    
    protected:
    
        dsp* fDSP;
    
        int32_t fSampleRate;
        int32_t fBufferSize;
    
        oboe::ManagedStream fInputStream;
        oboe::ManagedStream fOutputStream;
    
        int64_t fCPUTable[CPU_TABLE_SIZE];
        int64_t fCPUTableIndex;
    
        AudioChannels* fInputs;
        AudioChannels* fOutputs;
    
        std::vector<int> fCpuIds;
        bool fIsThreadAffinitySet;
    
        void setThreadAffinity()
        {
            pid_t current_thread_id = gettid();
            cpu_set_t cpu_set;
            CPU_ZERO(&cpu_set);
            
            // If the callback cpu ids aren't specified then bind to the current cpu
            if (fCpuIds.empty()) {
                int current_cpu_id = sched_getcpu();
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "Binding to current CPU ID %d", current_cpu_id);
                CPU_SET(current_cpu_id, &cpu_set);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "Binding to %d CPU IDs", static_cast<int>(fCpuIds.size()));
                for (size_t i = 0; i < fCpuIds.size(); i++) {
                    int cpu_id = fCpuIds.at(i);
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "CPU ID %d added to cores set", cpu_id);
                    CPU_SET(cpu_id, &cpu_set);
                }
            }
            
            int res = sched_setaffinity(current_thread_id, sizeof(cpu_set_t), &cpu_set);
            if (res == 0) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "Thread affinity set");
            } else {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "Error setting thread affinity error no: %d", res);
            }
            
            fIsThreadAffinitySet = true;
        }
  
        int64_t getTimeUsec() 
        {
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            return ((int64_t) now.tv_sec * 1000000000LL + now.tv_nsec)/1000;
        }
    
        oboe::DataCallbackResult onAudioReady(oboe::AudioStream* audioStream, void* outbuffer, int32_t framesWrite)
        {
            fBufferSize = framesWrite;
            int64_t t1 = getTimeUsec();
            if (!fIsThreadAffinitySet) setThreadAffinity();
            
            // Duplex case
            if (fDSP->getNumInputs() > 0) {
                
                // Read inputs
                float* inbuffer = static_cast<float*>(alloca(fDSP->getNumInputs() * sizeof(float) * framesWrite));
                oboe::ResultWithValue<int32_t> res = fInputStream->read(inbuffer, framesWrite, 0);
                
                if (res) {
                    int32_t framesRead = res.value();
                    fInputs->interleavedRead(inbuffer, framesWrite, fDSP->getNumInputs());
                
                    // Call compute only when 'read frames' == 'frames to write'
                    if (framesRead == framesWrite) {
                        fDSP->compute(framesWrite, fInputs->buffers(), fOutputs->buffers());
                        fOutputs->interleavedWrite(static_cast<float*>(outbuffer), framesWrite, fDSP->getNumOutputs());
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, "Faust", "onAudioReady framesRead %d framesWrite %d", framesRead, framesWrite);
                    }
                    
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "onAudioReady fInputStream->read fails");
                }
                
            } else {
                
                // Output only
                fDSP->compute(framesWrite, nullptr, fOutputs->buffers());
                fOutputs->interleavedWrite(static_cast<float*>(outbuffer), framesWrite, fDSP->getNumOutputs());
            }
            
            runControlCallbacks();
            
            int64_t t2 = getTimeUsec();
            fCPUTable[(fCPUTableIndex++)&(CPU_TABLE_SIZE-1)] = t2 - t1;
            return oboe::DataCallbackResult::Continue;
        }
 
    public:
    
        oboeaudio(long srate):
        fDSP(NULL),
        fSampleRate(srate),
        fBufferSize(512),
        fCPUTableIndex(0),
        fInputs(nullptr),
        fOutputs(nullptr),
        fIsThreadAffinitySet(false)
        {}

        virtual ~oboeaudio()
        {
            delete fInputs;
            delete fOutputs;
        }
    
        virtual bool init(const char* name, dsp* DSP)
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "init");
            fDSP = DSP;
            oboe::AudioStreamBuilder builder;
            
            // Possibly set SR
            if (fSampleRate != -1) {
                builder.setSampleRate(fSampleRate);
            }
            
            if (fDSP->getNumInputs() > 0) {
                if (builder.setDirection(oboe::Direction::Input)
                    ->setFormat(oboe::AudioFormat::Float)
                    ->setChannelCount(fDSP->getNumInputs())
                    ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
                    ->setSharingMode(oboe::SharingMode::Exclusive)
                    ->openManagedStream(fInputStream) != oboe::Result::OK) return false;
                // Allocate the stream adapter
                fInputs = new AudioChannels(4096, fDSP->getNumInputs());
                // Keep the input SR
                fSampleRate = fInputStream->getSampleRate();
            } else {
                fInputs = nullptr;
            }
            
            if (fDSP->getNumOutputs() > 0) {
                
                // Common setup
                builder.setDirection(oboe::Direction::Output)
                    ->setCallback(this)
                    ->setFormat(oboe::AudioFormat::Float)
                    ->setChannelCount(fDSP->getNumOutputs())
                    ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
                    ->setSharingMode(oboe::SharingMode::Exclusive);
                
                // If fSampleRate was given at initialisation time, or has been set when opening the input
                if (fSampleRate != -1) {
                    // Force output to use the same SR as input, and possibly setup resampler
                    if (builder.setSampleRate(fSampleRate)
                        ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Fastest)
                        ->openManagedStream(fOutputStream) != oboe::Result::OK) return false;
                } else {
                    // Open with the native SR
                    if (builder.openManagedStream(fOutputStream) != oboe::Result::OK) return false;
                }
                
                // Allocate the stream adapter
                fOutputs = new AudioChannels(4096, fDSP->getNumOutputs());
                // Keep the output SR
                fSampleRate = fOutputStream->getSampleRate();
            } else {
                fOutputs = nullptr;
            }
            
            // Init with the stream SR
            fDSP->init(fSampleRate);
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "init fSampleRate %d", fSampleRate);
            return true;
        }
    
        virtual bool start()
        {
            // Start output first
            if (fDSP->getNumOutputs() > 0) {
                if (fOutputStream->requestStart() != oboe::Result::OK) return false;
            }
            if (fDSP->getNumInputs() > 0) {
                if (fInputStream->requestStart() != oboe::Result::OK) return false;
            }
            return true;
        }
        
        virtual void stop()
        {
            // Stop output first (since the output stream calls the onAudioReady callback)
            if (fDSP->getNumOutputs() > 0) {
                fOutputStream->requestStop();
                fOutputStream->close();
            }
            if (fDSP->getNumInputs() > 0) {
                fInputStream->requestStop();
                fInputStream->close();
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
            return fDSP->getNumInputs();
        }
        
        virtual int getNumOutputs()
        {
            return fDSP->getNumOutputs();
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
/**************************  END  oboe-dsp.h **************************/
