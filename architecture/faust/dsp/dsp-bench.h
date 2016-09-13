/************************************************************************
    FAUST Architecture File
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#include <limits.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>

#include "faust/dsp/dsp.h"

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

/*
    A class to do do timing measurements
*/

class time_bench {
    
    protected:
    
        int fMeasure;
        int fMeasureCount;
        int fSkip;
    
        // These values are used to determine the number of clocks in a second
        uint64 fFirstRDTSC;
        uint64 fLastRDTSC;
    
        // These tables contains the last fMeasureCount in clocks
        uint64* fStarts;
        uint64* fStops;
    
        struct timeval fTv1;
        struct timeval fTv2;
    
        /**
         * Returns the number of clock cycles elapsed since the last reset of the processor
         */
        inline uint64 rdtsc(void)
        {
            union {
                uint32 i32[2];
                uint64 i64;
            } count;
            
            __asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
            return count.i64;
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
            fMeasureCount = count;
            fMeasure = 0;
            fFirstRDTSC = 0;
            fLastRDTSC = 0;
            fStarts = new uint64[fMeasureCount];
            fStops = new uint64[fMeasureCount];
        }
    
        virtual ~time_bench()
        {
            delete [] fStarts;
            delete [] fStops;
        }
    
        void startMeasure() { fStarts[fMeasure % fMeasureCount] = rdtsc(); }
    
        void stopMeasure() { fStops[fMeasure % fMeasureCount] = rdtsc(); fMeasure++; }
        
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
    
        /**
         *  Returns best estimation.
         */
        double getStats(int bsize, int ichans, int ochans)
        {
            assert(fMeasure > fMeasureCount);
            std::vector<uint64> V(fMeasureCount);
            
            for (int i = 0; i < fMeasureCount; i++) {
                V[i] = fStops[i] - fStarts[i];
            }
            
            sort(V.begin(), V.end());
            
            // Mean of 10 best values (gives relatively stable results)
            uint64 meavalx = meanValue(V.begin(), V.begin() + 10);
            return megapersec(bsize, ichans + ochans, meavalx);
        }

        /**
         * Print the median value (in Megabytes/second) of fMeasureCount throughputs measurements.
         */
        void printStats(const char* applname, int bsize, int ichans, int ochans)
        {
            assert(fMeasure > fMeasureCount);
            std::vector<uint64> V(fMeasureCount);
            
            for (int i = 0; i < fMeasureCount; i++) {
                V[i] = fStops[i] - fStarts[i];
            }
            
            sort(V.begin(), V.end());
            
            // Mean of 10 best values (gives relatively stable results)
            uint64 meaval00 = meanValue(V.begin(), V.begin()+ 5);
            uint64 meaval25 = meanValue(V.begin() + fMeasureCount / 4 - 2, V.begin()+fMeasureCount / 4 + 3);
            uint64 meaval50 = meanValue(V.begin() + fMeasureCount / 2 - 2, V.begin()+fMeasureCount / 2 + 3);
            uint64 meaval75 = meanValue(V.begin() + 3 * fMeasureCount / 4 - 2, V.begin() + 3 * fMeasureCount / 4 + 3);
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
    
        bool isRunning() { return (fMeasure <= (fMeasureCount + fSkip)); }

};

/*
    A class to measure DSP CPU use.
*/

class measure_dsp : public decorator_dsp {
    
    protected:
    
        FAUSTFLOAT* fInputs[256];
        FAUSTFLOAT* fOutputs[256];
        time_bench fBench;
        int fBufferSize;
    
    public:
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be measured.
         * @param buffer_size - the buffer size used when calling 'computeAll'
         * @param count - the number of cycles using in 'computeAll'
         * @param skip - ??
         *
         */
        measure_dsp(dsp* dsp, int buffer_size, int count, int skip)
        :decorator_dsp(dsp), fBench(count, skip), fBufferSize(buffer_size)
        {
            assert(fDSP->getNumInputs() < 256);
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                fInputs[i] = new FAUSTFLOAT[buffer_size];
                memset(fInputs[i], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            assert(fDSP->getNumOutputs() < 256);
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                fOutputs[i] = new FAUSTFLOAT[buffer_size];
                memset(fOutputs[i], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
        }
    
        virtual ~measure_dsp()
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete [] fInputs[i];
            }
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete [] fOutputs[i];
            }
        }
    
        /*
            Measure the duration of the compute call.
        */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fBench.startMeasure();
            fDSP->compute(count, inputs, outputs);
            fBench.stopMeasure();
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
        /*
            Measure the duration of 'count' (given in constructor) calls to compute.
        */
        void computeAll()
        {
            AVOIDDENORMALS;
            do {
                compute(0, fBufferSize, fInputs, fOutputs);
            } while (fBench.isRunning());
        }
    
        /**
         *  Initialize measure datas.
         */
        void openMeasure() { fBench.openMeasure(); }
    
        /**
         *  Terminate measurement.
         */
        void closeMeasure() { fBench.closeMeasure(); }
    
    
        /**
         *  Returns best estimation.
         */
        void getStats()
        {
            fBench.getStats(fBufferSize, fDSP->getNumInputs(), fDSP->getNumOutputs());
        }
    
        /**
         * Print the median value (in Megabytes/second) of fMeasureCount throughputs measurements.
         */
        void printStats(const char* applname)
        {
            fBench.printStats(applname, fBufferSize, fDSP->getNumInputs(), fDSP->getNumOutputs());
        }
    
        bool isRunning() { return fBench.isRunning(); }
    
};

#endif