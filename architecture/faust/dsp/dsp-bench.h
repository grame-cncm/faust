/************************** BEGIN dsp-bench.h ***************************
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
************************************************************************/

#ifndef __dsp_bench__
#define __dsp_bench__

#include <cmath>
#include <limits.h>
#include <sys/time.h>
#include <stdio.h>
#include <fstream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"
#include "faust/dsp/dsp-adapter.h"

// number of vectors in BIG buffer (should exceed cache)
#define NBV 4096
#define BENCH_SAMPLE_RATE 44100.0

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

template <typename REAL>
class time_bench_real {
    
    typedef std::vector<uint64_t>::const_iterator vtype;
    
    protected:
    
        int fMeasure;
        int fCount;
        int fSkip;
    
        // These values are used to determine the number of ticks in a second
        uint64_t fFirstRDTSC;
        uint64_t fLastRDTSC;
    
        // These tables contains the last fCount in ticks
        uint64_t* fStarts;
        uint64_t* fStops;
    
        struct timeval fTv1;
        struct timeval fTv2;
    
        /**
         * Returns the number of clock cycles elapsed since the last reset of the processor
         */
        uint64_t getTicks()
        {
        #if defined(__x86_64__)
            union {
                uint32_t i32[2];
                uint64_t i64;
            } count;
            __asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
            return count.i64;
        #else
            timespec res;
            clock_gettime(CLOCK_MONOTONIC_RAW, &res);
            return static_cast<uint64_t>(res.tv_sec) * 1e9 + static_cast<uint64_t>(res.tv_nsec);
        #endif
        }

        /**
         * return the number of RDTSC ticks per seconds
         */
        double rdtscpersec()
        {
            // If the environment variable CLOCKSPERSEC is defined, we use it instead of our own measurement
            char* str = getenv("CLOCKSPERSEC");
            if (str) {
                int64_t cps = int64_t(atoll(str));
                if (cps > 1000000000) {
                    return cps;
                }
            }
            return double(fLastRDTSC - fFirstRDTSC)
                / (((double(fTv2.tv_sec) * 1000000. + double(fTv2.tv_usec)) - (double(fTv1.tv_sec) * 1000000. + double(fTv1.tv_usec)))
                / 1000000.);
        }
  
        /**
         * Converts a duration, expressed in RDTSC ticks, into seconds
         */
        double rdtsc2sec(uint64_t clk)
        {
            return double(clk) / rdtscpersec();
        }
        
        double rdtsc2sec(double clk)
        {
            return clk / rdtscpersec();
        }
    
        /**
         * Converts RDTSC ticks into MBytes/seconds according to the
         * number of frames processed during the period, the number of channels
         * and sizeof(REAL) bytes samples
         */
        double megapersec(int frames, int chans, uint64_t clk)
        {
            return (double(frames) * double(chans) * double(sizeof(REAL))) / (1024. * 1024. * rdtsc2sec(clk));
        }
        
        /**
         * Compute the mean value of a vector of measures
         */
        uint64_t meanValue(vtype a, vtype b)
        {
            uint64_t r = 0;
            unsigned int n = 0;
            while (a != b) { r += *a++; n++; }
            return (n > 0) ? r/n : 0;
        }
    
        /**
         * Compute the relative standard deviation of a vector of measures
         */
        double standardDeviation(vtype a, vtype b)
        {
            double mean = meanValue(a, b);
            double sum_sd = 0;
            unsigned int n = 0;
            while (a != b) {
                sum_sd += std::pow(mean - double(*a++), 2.0);
                n++;
            }
            return (n > 0) ? ((std::sqrt(sum_sd/double(n)) * 100)/mean) : 0;
        }
  
    public:
    
        time_bench_real(int count, int skip)
        {
            fSkip = skip;
            fCount = count;
            fMeasure = 0;
            fFirstRDTSC = 0;
            fLastRDTSC = 0;
            fStarts = new uint64_t[fCount];
            fStops = new uint64_t[fCount];
        }
    
        virtual ~time_bench_real()
        {
            delete [] fStarts;
            delete [] fStops;
        }
    
        void startMeasure() { fStarts[fMeasure % fCount] = getTicks(); }
    
        void stopMeasure() { fStops[fMeasure % fCount] = getTicks(); fMeasure++; }
        
        void openMeasure()
        {
            struct timezone tz;
            gettimeofday(&fTv1, &tz);
            fFirstRDTSC = getTicks();
            fMeasure = 0;
        }
        
        void closeMeasure()
        {
            struct timezone tz;
            gettimeofday(&fTv2, &tz);
            fLastRDTSC = getTicks();
        }
    
        double measureDurationUsec()
        {
            return ((double(fTv2.tv_sec) * 1000000. + double(fTv2.tv_usec)) - (double(fTv1.tv_sec) * 1000000. + double(fTv1.tv_usec)));
        }
    
        /**
         *  Returns best estimation
         */
        std::pair<double, double> getStats(int bsize, int ichans, int ochans)
        {
            assert(fMeasure > fCount);
            std::vector<uint64_t> V(fCount);
            for (int i = 0; i < fCount; i++) {
                V[i] = fStops[i] - fStarts[i];
            }
            sort(V.begin(), V.end());
            
            // Mean and standard deviation of 50 best values (gives relatively stable results)
            uint64_t meavalx = meanValue(V.begin(), V.begin() + 50);
            double sd = standardDeviation(V.begin(), V.begin() + 50);
            return std::make_pair(megapersec(bsize, ichans + ochans, meavalx), sd);
        }

        /**
         * Print the median value (in Megabytes/second) of fCount throughputs measurements
         */
        void printStats(const char* applname, int bsize, int ichans, int ochans)
        {
            assert(fMeasure > fCount);
            std::vector<uint64_t> V(fCount);
            for (int i = 0; i < fCount; i++) {
                V[i] = fStops[i] - fStarts[i];
            }
            sort(V.begin(), V.end());
            
            // Mean of 10 best values (gives relatively stable results)
            uint64_t meaval00 = meanValue(V.begin(), V.begin() + 5);
            uint64_t meaval25 = meanValue(V.begin() + fCount / 4 - 2, V.begin() + fCount / 4 + 3);
            uint64_t meaval50 = meanValue(V.begin() + fCount / 2 - 2, V.begin() + fCount / 2 + 3);
            uint64_t meaval75 = meanValue(V.begin() + 3 * fCount / 4 - 2, V.begin() + 3 * fCount / 4 + 3);
            uint64_t meaval100 = meanValue(V.end() - 5, V.end());
            
            // Printing
            fprintf(stdout, "%\t%f\t%f\t%f\t%f\t%f\n", applname,
                    megapersec(bsize, ichans+ochans, meaval00),
                    megapersec(bsize, ichans+ochans, meaval25),
                    megapersec(bsize, ichans+ochans, meaval50),
                    megapersec(bsize, ichans+ochans, meaval75),
                    megapersec(bsize, ichans+ochans, meaval100));
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
        for (const auto& it : fControls) {
            *it.fZone = it.fMin + (FAUSTFLOAT(rand())/FAUSTFLOAT(RAND_MAX)) * std::abs(it.fMax - it.fMin);
        }
    }
    
    void display()
    {
        if (fControls.size()) fprintf(stdout, "--------- RandomControlUI ---------\n");
        for (const auto& it : fControls) {
            fprintf(stdout, "Path: \"%s\" min: %f max: %f cur: %f\n", getParamAddress(it.fZone).c_str(), it.fMin, it.fMax, *it.fZone);
        }
    }
};

/*
A class to measure DSP CPU use
*/

template <typename REAL>
class measure_dsp_real : public decorator_dsp {
    
    protected:
    
        REAL** fInputs;
        REAL** fAllInputs;
        REAL** fOutputs;
        REAL** fAllOutputs;
        time_bench_real<REAL>* fBench;
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
                fprintf(stderr, "setRealtimePriority : pthread_getschedparam res = %d\n", err);
            }
            policy = SCHED_RR;
            param.sched_priority = 80;
            err = pthread_setschedparam(pthread_self(), policy, &param);
            if (err != 0) {
                fprintf(stderr, "setRealtimePriority : pthread_setschedparam res = %d\n", err);
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
         * @param count - the number of audio cycles used in 'computeAll'
         * @param trace - whether to log the trace
         * @param control - whether to activate random changes of all control values at each cycle
         * @param ds - downsampling factor
         * @param us - upsampling factor
         * @param filter - filter type
         *
         */
        measure_dsp_real(dsp* dsp,
                        int buffer_size,
                        int count,
                        bool trace = true,
                        bool control = false,
                        int ds = 0,
                        int us = 0,
                        int filter = 0)
            :decorator_dsp(createSRAdapter<REAL>(dsp, ds, us, filter)), fBufferSize(buffer_size), fCount(count), fControl(control)
        {
            init();
            fBench = new time_bench_real<REAL>(fCount, 10);
        }
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be measured.
         * @param buffer_size - the buffer size used when calling 'computeAll'
         * @param duration_in_sec - the wanted duration used in 'computeAll'
         * @param trace - whether to log the trace
         * @param control - whether to activate random changes of all control values at each cycle
         * @param ds - downsampling factor
         * @param us - upsampling factor
         * @param filter - filter type
         *
         */
        measure_dsp_real(dsp* dsp,
                        int buffer_size,
                        double duration_in_sec,
                        bool trace = true,
                        bool control = false,
                        int ds = 0,
                        int us = 0,
                        int filter = 0)
            :decorator_dsp(createSRAdapter<REAL>(dsp, ds, us, filter)), fBufferSize(buffer_size), fControl(control)
        {
            init();
            
            // Creates a first time_bench_real object to estimate the proper 'count' number of measure to do later
            fBench = new time_bench_real<REAL>(1000, 10);
            measure();
            double duration = fBench->measureDurationUsec();
            if (trace) {
                fprintf(stdout, "Duration %f\n",  (duration / 1e6));
                if (control) fprintf(stdout, "Random control is on\n");
            }
            fCount = int(1000 * (duration_in_sec * 1e6 / duration));
            delete fBench;
            
            // Then allocate final time_bench_real object with proper 'count' parameter
            fBench = new time_bench_real<REAL>(fCount, 10);
        }
    
        virtual ~measure_dsp_real()
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
            // Only measure the 'compute' method
            fBench->startMeasure();
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
        std::pair<double, double> getStats()
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
            return (fBench->measureDurationUsec() / 1000.0 * BENCH_SAMPLE_RATE) / (double(fBench->getCount()) * double(fBufferSize) * 1000.0);
        }
    
        int getCount() { return fCount; }
    
};

struct measure_dsp : measure_dsp_real<FAUSTFLOAT> {

    measure_dsp(dsp* dsp,
                int buffer_size,
                double duration_in_sec,
                bool trace = true,
                bool control = false)
        :measure_dsp_real(dsp, buffer_size, duration_in_sec, trace, control)
    {}
    virtual~ measure_dsp()
    {}
    
};

#endif
/************************** END dsp-bench.h **************************/
