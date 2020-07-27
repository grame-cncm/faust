/************************** BEGIN dsp-bench.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016-2020 GRAME, Centre National de Creation Musicale
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

#ifndef __dsp_bench__
#define __dsp_bench__

#include <cmath>
#include <limits.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"

// Handle 32/64 bits int size issues
#ifdef __x86_64__
    #define uint32 unsigned int
    #define uint64 unsigned long int
    #define int32 int
    #define int64 long int
#else
    #define uint32 unsigned int
    #define uint64 unsigned long long int
    #define int32 int
    #define int64 long long int
#endif

#ifdef TARGET_OS_IPHONE
#include <mach/mach_time.h>
#endif

#define BENCH_SAMPLE_RATE 44100.0
#define NBV 4096     // number of vectors in BIG buffer (should exceed cache)

template <typename VAL_TYPE>
void FAUSTBENCH_LOG(VAL_TYPE val)
{
    const char* log = getenv("FAUSTBENCH_LOG");
    if (log && (strcasecmp(log, "on") == 0)) {
        std::ofstream gFaustbenchLog;
        gFaustbenchLog.open("Faustbench.csv", std::ofstream::app);
        gFaustbenchLog << val << std::endl;
    }
}

/*
    A class to do do timing measurements
*/

class time_bench {
    
    protected:
    
    #ifdef TARGET_OS_IPHONE
        mach_timebase_info_data_t fTimeInfo;
    #endif
    
        int fMeasure;
        int fCount;
        int fSkip;
    
        // These values are used to determine the number of clocks in a second
        uint64 fFirstRDTSC;
        uint64 fLastRDTSC;
    
        // These tables contains the last fCount in clocks
        uint64* fStarts;
        uint64* fStops;
    
        struct timeval fTv1;
        struct timeval fTv2;
    
        /**
         * Returns the number of clock cycles elapsed since the last reset of the processor
         */
        uint64 rdtsc(void)
        {
        #ifdef TARGET_OS_IPHONE
            return (uint64)(mach_absolute_time() * (double)fTimeInfo.numer / (double)fTimeInfo.denom);
        #else  
            union {
                uint32 i32[2];
                uint64 i64;
            } count;
            __asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
            return count.i64;
        #endif
        }

        /**
         * return the number of RDTSC clocks per seconds
         */
        double rdtscpersec()
        {
            // If the environment variable CLOCKSPERSEC is defined
            // we use it instead of our own measurement
            char* str = getenv("CLOCKSPERSEC");
            if (str) {
                int64 cps = (int64)atoll(str);
                if (cps > 1000000000) {
                    return cps;
                }
            }
            
            return double(fLastRDTSC - fFirstRDTSC)
                / (((double(fTv2.tv_sec) * 1000000 + double(fTv2.tv_usec)) - (double(fTv1.tv_sec) * 1000000 + double(fTv1.tv_usec)))
                / 1000000);
        }
  
        /**
         * Converts a duration, expressed in RDTSC clocks, into seconds
         */
        double rdtsc2sec(uint64 clk)
        {
            return double(clk) / rdtscpersec();
        }
        
        double rdtsc2sec(double clk)
        {
            return clk / rdtscpersec();
        }
    
        /**
         * Converts RDTSC clocks into Megabytes/seconds according to the
         * number of frames processed during the period, the number of channels
         * and 4 bytes samples.
         */
        double megapersec(int frames, int chans, uint64 clk)
        {
            return double(frames) * double(chans) * 4 / double(1024 * 1024 * rdtsc2sec(clk));
        }
        
        /**
         * Compute the mean value of a vector of measures
         */
        uint64 meanValue(std::vector<uint64>::const_iterator a, std::vector<uint64>::const_iterator b)
        {
            uint64 r = 0;
            unsigned int n = 0;
            while (a != b) { r += *a++; n++; }
            return (n > 0) ? r/n : 0;
        }
  
    public:
    
        time_bench(int count, int skip)
        {
            fSkip = skip;
            fCount = count;
            fMeasure = 0;
            fFirstRDTSC = 0;
            fLastRDTSC = 0;
            fStarts = new uint64[fCount];
            fStops = new uint64[fCount];
        #ifdef TARGET_OS_IPHONE
            mach_timebase_info(&fTimeInfo);
        #endif
        }
    
        virtual ~time_bench()
        {
            delete [] fStarts;
            delete [] fStops;
        }
    
        void startMeasure() { fStarts[fMeasure % fCount] = rdtsc(); }
    
        void stopMeasure() { fStops[fMeasure % fCount] = rdtsc(); fMeasure++; }
        
        void openMeasure()
        {
            struct timezone tz;
            gettimeofday(&fTv1, &tz);
            fFirstRDTSC = rdtsc();
            fMeasure = 0;
        }
        
        void closeMeasure()
        {
            struct timezone tz;
            gettimeofday(&fTv2, &tz);
            fLastRDTSC = rdtsc();
        }
    
        double measureDurationUsec()
        {
            return ((double(fTv2.tv_sec) * 1000000 + double(fTv2.tv_usec)) - (double(fTv1.tv_sec) * 1000000 + double(fTv1.tv_usec)));
        }
    
        /**
         *  Returns best estimation.
         */
        double getStats(int bsize, int ichans, int ochans)
        {
            assert(fMeasure > fCount);
            std::vector<uint64> V(fCount);
            
            for (int i = 0; i < fCount; i++) {
                V[i] = fStops[i] - fStarts[i];
            }
            
            sort(V.begin(), V.end());
            
            // Mean of 10 best values (gives relatively stable results)
            uint64 meavalx = meanValue(V.begin(), V.begin() + 10);
            return megapersec(bsize, ichans + ochans, meavalx);
        }

        /**
         * Print the median value (in Megabytes/second) of fCount throughputs measurements.
         */
        void printStats(const char* applname, int bsize, int ichans, int ochans)
        {
            assert(fMeasure > fCount);
            std::vector<uint64> V(fCount);
            
            for (int i = 0; i < fCount; i++) {
                V[i] = fStops[i] - fStarts[i];
            }
            
            sort(V.begin(), V.end());
            
            // Mean of 10 best values (gives relatively stable results)
            uint64 meaval00 = meanValue(V.begin(), V.begin()+ 5);
            uint64 meaval25 = meanValue(V.begin() + fCount / 4 - 2, V.begin()+fCount / 4 + 3);
            uint64 meaval50 = meanValue(V.begin() + fCount / 2 - 2, V.begin()+fCount / 2 + 3);
            uint64 meaval75 = meanValue(V.begin() + 3 * fCount / 4 - 2, V.begin() + 3 * fCount / 4 + 3);
            uint64 meaval100 = meanValue(V.end() - 5, V.end());
            
            // Printing
            std::cout << applname
            << '\t' << megapersec(bsize, ichans+ochans, meaval00)
            << '\t' << megapersec(bsize, ichans+ochans, meaval25)
            << '\t' << megapersec(bsize, ichans+ochans, meaval50)
            << '\t' << megapersec(bsize, ichans+ochans, meaval75)
            << '\t' << megapersec(bsize, ichans+ochans, meaval100)
            << std::endl;
        }
    
        bool isRunning() { return (fMeasure <= (fCount + fSkip)); }
    
        int getCount()
        {
            return fMeasure;
        }

};

/*
 A class to randomly change control values
 */

struct RandomControlUI : public MapUI {
    
    struct Range {
        const char* fLabel;
        FAUSTFLOAT* fZone;
        FAUSTFLOAT fInit;
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        Range(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init = 0, FAUSTFLOAT min = 0, FAUSTFLOAT max = 0)
        :fLabel(label), fZone(zone), fInit(init), fMin(min), fMax(max)
        {}
    };
    
    std::vector<Range> fControls;
    
    RandomControlUI()
    {
        /* initialize random seed: */
        srand(time(NULL));
    }
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        MapUI::addButton(label, zone);
        fControls.push_back(Range(label, zone, 1, 0, 1));
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        MapUI::addCheckButton(label, zone);
        fControls.push_back(Range(label, zone, 1, 0, 1));
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
         MapUI::addVerticalSlider(label, zone, init, min, max, step);
        fControls.push_back(Range(label, zone, init, min, max));
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        MapUI::addHorizontalSlider(label, zone, init, min, max, step);
        fControls.push_back(Range(label, zone, init, min, max));
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        MapUI::addNumEntry(label, zone, init, min, max, step);
        fControls.push_back(Range(label, zone, init, min, max));
    }
    
    void update()
    {
        for (auto& it : fControls) {
            *it.fZone = it.fMin + (FAUSTFLOAT(rand())/FAUSTFLOAT(RAND_MAX)) * std::abs(it.fMax - it.fMin);
        }
    }
    
    void display()
    {
        std::cout << "--------- RandomControlUI ---------\n";
        for (auto& it : fControls) {
            std::cout << "Path: \"" << getParamAddress(it.fZone) << "\" min: " << it.fMin << " max: " << it.fMax << " cur: " << *it.fZone << std::endl;
        }
    }
};

/*
A class to measure DSP CPU use
*/

template <typename REAL>
class measure_dsp_aux : public decorator_dsp {
    
    protected:
    
        REAL** fInputs;
        REAL** fAllInputs;
        REAL** fOutputs;
        REAL** fAllOutputs;
        time_bench* fBench;
        int fBufferSize;
        int fInputIndex;
        int fOutputIndex;
        int fCount;
        bool fControl;
        RandomControlUI fRandomUI;
    
        void init()
        {
            fDSP->init(BENCH_SAMPLE_RATE);
            fDSP->buildUserInterface(&fRandomUI);
            
            fInputIndex = 0;
            fOutputIndex = 0;
            
            fInputs = new REAL*[fDSP->getNumInputs()];
            fAllInputs = new REAL*[fDSP->getNumInputs()];
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                fAllInputs[i] = new REAL[fBufferSize * NBV];
                fInputs[i] = fAllInputs[i];
                // Write noise in inputs (to avoid 'speedup' effect due to null values)
                int R0_0 = 0;
                for (int j = 0; j < fBufferSize * NBV; j++) {
                    int R0temp0 = (12345 + (1103515245 * R0_0));
                    fAllInputs[i][j] = REAL(4.656613e-10f * R0temp0);
                    R0_0 = R0temp0;
                }
            }
            
            fOutputs = new REAL*[fDSP->getNumOutputs()];
            fAllOutputs = new REAL*[fDSP->getNumOutputs()];
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                fAllOutputs[i] = new REAL[fBufferSize * NBV];
                fOutputs[i] = fAllOutputs[i];
                // Write zero in outputs
                memset(fAllOutputs[i], 0, sizeof(REAL) * fBufferSize * NBV);
            }
        }
    
        bool setRealtimePriority()
        {
            struct passwd* pw;
            struct sched_param param;
            int policy;
            uid_t uid = getuid();
            pw = getpwnam("root");
            setuid(pw->pw_uid);
            
            int err = pthread_getschedparam(pthread_self(), &policy, &param);
            if (err != 0) {
                std::cerr << "setRealtimePriority : pthread_getschedparam res = %d" << err << std::endl;
            }
            policy = SCHED_RR;
            param.sched_priority = 80;
            err = pthread_setschedparam(pthread_self(), policy, &param);
            if (err != 0) {
                std::cerr << "setRealtimePriority : pthread_setschedparam res = %d" << err << std::endl;
            }
            
            setuid(uid);
            return (err != -1);
        }
    
    public:
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be measured.
         * @param buffer_size - the buffer size used when calling 'computeAll'
         * @param count - the number of cycles using in 'computeAll'
         * @param trace - whether to log the trace
         * @param control - whether to activate random changes of all control values at each cycle
         *
         */
        measure_dsp_aux(dsp* dsp, int buffer_size, int count, bool trace = true, bool control = false)
            :decorator_dsp(dsp), fBufferSize(buffer_size), fCount(count), fControl(control)
        {
            init();
            fBench = new time_bench(fCount, 10);
        }
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be measured.
         * @param buffer_size - the buffer size used when calling 'computeAll'
         * @param duration_in_sec - the wanted duration used in 'computeAll'
         * @param trace - whether to log the trace
         * @param random - whether to activate random changes of all control values at each cycle
         *
         */
        measure_dsp_aux(dsp* dsp, int buffer_size, double duration_in_sec, bool trace = true, bool control = false)
            :decorator_dsp(dsp), fBufferSize(buffer_size), fControl(control)
        {
            init();
            
            // Creates a first time_bench object to estimate the proper 'count' number of measure to do later
            fBench = new time_bench(1000, 10);
            measure();
            double duration = fBench->measureDurationUsec();
            if (trace) std::cout << "duration " << (duration / 1e6) << std::endl;
            fCount = int(1000 * (duration_in_sec * 1e6 / duration));
            delete fBench;
            
            // Then allocate final time_bench object with proper 'count' parameter
            fBench = new time_bench(fCount, 10);
        }
    
        virtual ~measure_dsp_aux()
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete [] fAllInputs[i];
            }
            delete [] fInputs;
            delete [] fAllInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete [] fAllOutputs[i];
            }
            delete [] fOutputs;
            delete [] fAllOutputs;
            
            delete fBench;
            // DSP is deallocated by the decorator_dsp class.
        }
    
        /**
         *  Measure the duration of the compute call
         */
        virtual void compute(int count, REAL** inputs, REAL** outputs)
        {
            AVOIDDENORMALS;
            // Possibly update all controllers
            if (fControl) fRandomUI.update();
            fBench->startMeasure();
            // Only measure the 'compute' method
            fDSP->compute(count, reinterpret_cast<FAUSTFLOAT**>(inputs), reinterpret_cast<FAUSTFLOAT**>(outputs));
            fBench->stopMeasure();
        }
    
        virtual void compute(double date_usec, int count, REAL** inputs, REAL** outputs)
        {
            compute(count, inputs, outputs);
        }
    
        /**
         *  Measure the duration of 'count' calls to compute
         */
        void computeAll()
        {
            do {
                for (int i = 0; i < fDSP->getNumInputs(); i++) {
                    REAL* allinputs = fAllInputs[i];
                    fInputs[i] = &allinputs[fInputIndex * fBufferSize];
                    fInputIndex = (1 + fInputIndex) % NBV;
                }
                for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                    REAL* alloutputs = fAllOutputs[i];
                    fOutputs[i] = &alloutputs[fOutputIndex * fBufferSize];
                    fOutputIndex = (1 + fOutputIndex) % NBV;
                }
                compute(0, fBufferSize, fInputs, fOutputs);
            } while (fBench->isRunning());
        }
    
        /**
         *  Initialize measure datas
         */
        void openMeasure() { fBench->openMeasure(); }
    
        /**
         *  Terminate measurement
         */
        void closeMeasure() { fBench->closeMeasure(); }
    
        double measureDurationUsec()
        {
            return fBench->measureDurationUsec();
        }
    
        void measure()
        {
            setRealtimePriority();
            openMeasure();
            computeAll();
            closeMeasure();
        }
    
        /**
         *  Returns best estimation
         */
        double getStats()
        {
            return fBench->getStats(fBufferSize, fDSP->getNumInputs(), fDSP->getNumOutputs());
        }
    
        /**
         * Print the median value (in Megabytes/second) of fCount throughputs measurements
         */
        void printStats(const char* applname)
        {
            fBench->printStats(applname, fBufferSize, fDSP->getNumInputs(), fDSP->getNumOutputs());
        }
    
        bool isRunning() { return fBench->isRunning(); }
    
        float getCPULoad()
        {
            return (fBench->measureDurationUsec() / 1000.0 * BENCH_SAMPLE_RATE) / (fBench->getCount() * fBufferSize * 1000.0);
        }
    
        int getCount() { return fCount; }
    
};

struct measure_dsp : measure_dsp_aux<FAUSTFLOAT> {

    measure_dsp(dsp* dsp,
                int buffer_size,
                double duration_in_sec,
                bool trace = true,
                bool control = false)
        :measure_dsp_aux(dsp, buffer_size, duration_in_sec, trace, control)
    {}
    virtual~ measure_dsp()
    {}
    
};

#endif
/**************************  END  dsp-bench.h **************************/
