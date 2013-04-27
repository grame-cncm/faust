
/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <pthread.h>
#include <sys/wait.h>
#include <list>

#include <iostream>
#include <sstream>

#include "faust/llvm-dsp.h"
#include "faust/misc.h"

#include <map>
#include <vector>
#include <sys/time.h>

using namespace std;

#define MEGABYTE 1048576.0

// handle 32/64 bits int size issues

#ifdef __x86_64__

#define uint32	unsigned int
#define uint64	unsigned long int

#define int32	int
#define int64	long int

#else

#define uint32	unsigned int
#define uint64	unsigned long long int

#define int32	int
#define int64	long long int
#endif

#define KSKIP 20
#define KMESURE 600

#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#include <mach/thread_policy.h>
#include <mach/thread_act.h>

static void get_affinity(pthread_t thread)
{
    thread_affinity_policy theTCPolicy;
    mach_msg_type_number_t count = THREAD_AFFINITY_POLICY_COUNT;
    boolean_t get_default = false;
    kern_return_t res = thread_policy_get(pthread_mach_thread_np(thread), THREAD_AFFINITY_POLICY, (thread_policy_t)&theTCPolicy, &count, &get_default);
    if (res == KERN_SUCCESS)  {
        printf("get_affinity = %d\n", theTCPolicy.affinity_tag);
    }
}

static void set_affinity(pthread_t thread, int tag)
{
    thread_affinity_policy theTCPolicy;
    theTCPolicy.affinity_tag = tag;
    kern_return_t res = thread_policy_set(pthread_mach_thread_np(thread), THREAD_AFFINITY_POLICY, (thread_policy_t)&theTCPolicy, THREAD_AFFINITY_POLICY_COUNT);
    if (res == KERN_SUCCESS)  {
        printf("set_affinity = %d\n", theTCPolicy.affinity_tag);
    }
}

class FaustLLVMOptimizer {

    private:
        
        #define STARTMESURE fStarts[fMeasure % KMESURE] = rdtsc();
        #define STOPMESURE fStops[fMeasure % KMESURE] = rdtsc(); fMeasure = fMeasure + 1;

        FAUSTFLOAT* fBuffer;    // a buffer of NV*VSize samples

        unsigned int COUNT;     // number of measures
        unsigned int NV;        // number of vectors in BIG buffer (should exceed cache)
        unsigned int ITER;      // number of iterations per measure
        unsigned int VSIZE;     // size of a vector in samples
        unsigned int IDX ;      // current vector number (0 <= VIdx < NV)
        
        llvm_dsp_factory* fFactory;
        llvm_dsp* fDSP;
        
        string fFilename;
        string fInput;
        
        string fLibraryPath;
        string fTarget;
        
        int fMeasure;
        
        char fError[256];
        
        vector<vector <string > > fOptionsTable;
        
        // these values are used to determine the number of clocks in a second
        uint64 fFirstRDTSC;
        uint64 fLastRDTSC;

        // these tables contains the last KMESURE in clocks
        uint64 fStarts[KMESURE];
        uint64 fStops[KMESURE];

        struct timeval fTv1;
        struct timeval fTv2;
   
        /**
         * Returns the number of clock cycles elapsed since the last reset
         * of the processor
         */
        __inline__ uint64 rdtsc(void)
        {
            union {
                uint32 i32[2];
                uint64 i64;
            } count;
            
            __asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
             return count.i64;
        }
 
        void openMesure()
        {
            struct timezone tz;
            gettimeofday(&fTv1, &tz);
            fFirstRDTSC = rdtsc();
            fMeasure = 0;
        }

        void closeMesure()
        {
            struct timezone tz;
            gettimeofday(&fTv2, &tz);
            fLastRDTSC = rdtsc();
        }
            
        /**
         * return the number of RDTSC clocks per seconds
         */
        double rdtscpersec()
        {
            // If the environment variable CLOCKSPERSEC is defined
            // we use it instead of our own measurement
            /*
            char* str = getenv("CLOCKSPERSEC");
            if (str) {
                int64 cps = (int64)atoll(str);
                if (cps > 1000000000) {
                    return cps;
                } 
            }
            */
            
            if (fTv2.tv_sec != fTv1.tv_sec) {
                return double(fLastRDTSC - fFirstRDTSC) / double(fTv2.tv_sec - fTv1.tv_sec);
            } else {
                return (double(fLastRDTSC - fFirstRDTSC) / (double(fTv2.tv_usec - fTv1.tv_usec) / 1000000.));
            }
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
            return (double(frames) * double(chans) * 4) / (double(1024 * 1024) * rdtsc2sec(clk));
        }

        /**
         * Compute the mean value of a vector of measures
         */
        uint64 meanValue(vector<uint64>::const_iterator a, vector<uint64>::const_iterator b)
        {
            uint64 r = 0;
            unsigned int n = 0;
            while (a != b) { r += *a++; n++; }
            return (n > 0) ? r/n : 0;
        }   

        double getstats(int bsize, int ichans, int ochans)
        {
            assert(fMeasure > KMESURE);
            vector<uint64> V(KMESURE);

            for (int i = 0; i < KMESURE; i++) {
                V[i] = fStops[i] - fStarts[i];
            }

            sort(V.begin(), V.end());
          
            // Mean of 10 best values (gives relatively stable results)
            uint64 meavalx = meanValue(V.begin(), V.begin() + 10);		
          
            return megapersec(bsize, ichans + ochans, meavalx);
        }
        
        bool setRealtimePriority()
        {
            struct passwd *         pw;
            int                     err;
            uid_t                   uid;
            int                     policy;
            struct sched_param      param;

            uid = getuid();
            pw = getpwnam ("root");
            setuid(pw->pw_uid);

            pthread_getschedparam(pthread_self(), &policy, &param);
            policy = SCHED_RR;
            param.sched_priority = 50;
            err = pthread_setschedparam(pthread_self(), policy, &param);

            setuid(uid);
            return (err != -1);
        }

        void allocBuffers(int numOutChan, FAUSTFLOAT** outChannel)
        {
            unsigned int BSIZE = NV * VSIZE;
            fBuffer = (FAUSTFLOAT*)calloc(BSIZE, sizeof(FAUSTFLOAT));
            
            int R0_0 = 0;
            for (int j = 0; j < BSIZE; j++) {
                int R0temp0 = (12345 + (1103515245 * R0_0));
                fBuffer[j] = 4.656613e-10f * R0temp0;
                R0_0 = R0temp0;
            }
            
            // allocate output channels (not initialized)
            for (int i = 0; i < numOutChan; i++) {
                outChannel[i] = (FAUSTFLOAT*)calloc(VSIZE, sizeof(FAUSTFLOAT));
            }
        }

        void freeBuffers(int numOutChan, FAUSTFLOAT** outChannel)
        {
            for (int i = 0; i < numOutChan; i++) {
                free(outChannel[i]);
            }
            
            free(fBuffer);
        }

        FAUSTFLOAT* nextVect()
        {
            IDX = (1 + IDX) % NV;
            return &fBuffer[IDX*VSIZE];
        }
        
        double bench()
        {
            int numInChan = fDSP->getNumInputs();
            int numOutChan = fDSP->getNumOutputs();

            FAUSTFLOAT* inChannel[numInChan];
            FAUSTFLOAT* outChannel[numOutChan];
            
            openMesure();

            // allocate input buffers (initialized with white noise)
            allocBuffers(numOutChan, outChannel);
            
            // init the dsp with a reasonable sampling rate
            fDSP->init(48000);
       
            AVOIDDENORMALS;
            bool running = true;
            
            while (running) {
                // allocate new input buffers to avoid L2 cache
                for (int c = 0; c < numInChan; c++) { inChannel[c] = nextVect(); }
                STARTMESURE
                fDSP->compute(VSIZE, inChannel, outChannel);
                STOPMESURE
                running = fMeasure <= (KMESURE + KSKIP);	 
            }
            
            closeMesure();
            double res = getstats(VSIZE, fDSP->getNumInputs(), fDSP->getNumOutputs());
            
            printf("VSIZE = %d getstats = %f\n", VSIZE, res);
             
            freeBuffers(numOutChan, outChannel);
            return res;
        }
        
    public:
    
        void init()
        {
            // Scalar mode
            vector <string> t0;
            fOptionsTable.push_back(t0);
            
            fMeasure = 0;
            
            // vec -lv 0
            for (int size = 16; size <= VSIZE; size *= 2) {
                stringstream num;
                num << size;
                vector <string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            } 
            
            // vec -lv 1
            for (int size = 16; size <= VSIZE; size *= 2) {
                stringstream num;
                num << size;
                vector <string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            } 
            
            /*
            // vec -lv 0 -dfs
            for (int size = 16; size <= VSIZE; size *= 2) {
                stringstream num;
                num << size;
                vector <string> t1;
                t1.push_back("-dfs");
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            } 
            
            // vec -lv 1 -dfs
            for (int size = 16; size <= VSIZE; size *= 2) {
                stringstream num;
                num << size;
                vector <string> t1;
                t1.push_back("-dfs");
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            } 
            */
        }
    
        FaustLLVMOptimizer(const char* filename, const string& library_path, const string& target, int count, int size)
        {
            fBuffer = 0;
            fFilename = filename;
            fInput = "";
            fLibraryPath = library_path;
            fTarget = target;
            
            COUNT   = count;    // number of measures
            NV      = 4096;     // number of vectors in BIG buffer (should exceed cache)
            ITER    = 10;       // number of iterations per measure
            VSIZE   = size;     // size of a vector in samples
            IDX     = 0;        // current vector number (0 <= VIdx < NV)
            
            init();
        }
        
        FaustLLVMOptimizer(const string& input, const string& library_path, const string& target, int count, int size)
        {
            fBuffer = 0;
            fFilename = "";
            fInput = input;
            fLibraryPath = library_path;
            fTarget = target;
           
            COUNT   = count;    // number of measures
            NV      = 4096;     // number of vectors in BIG buffer (should exceed cache)
            ITER    = 10;       // number of iterations per measure
            VSIZE   = size;     // size of a vector in samples
            IDX     = 0;        // current vector number (0 <= VIdx < NV)
            
            init();
        }
        
        ~FaustLLVMOptimizer()
        {}
        
        static bool myfunction(pair <int, double > i, pair <int, double > j) { return (i.second > j.second); }
        
        vector<string> findOptimize()
        {
            vector< pair <int, double > > table_res;
            double res;
             
            for (int i = 0; i < fOptionsTable.size(); i++) {
                if (computeOne(i, res)) {
                    table_res.push_back(make_pair(i, res));
                } else {
                    printf("computeOne error...\n");
                }
            }
            
            sort(table_res.begin(), table_res.end(), myfunction);
             
            if (table_res.size() > 0) {
                return fOptionsTable[table_res[0].first];
            } else {
                // Scalar...
                printf("findOptimize no options found...\n");
                return fOptionsTable[0];
            }
        }
        
        const char* getError() { return fError; }
        
        bool computeOne(int index, double& res)
        {
            vector <string> item = fOptionsTable[index];
            
            if (fInput == "") { 
            
                int argc = item.size() + 1;
                const char* argv[argc];
                argv[0] = fFilename.c_str();
                for (int i = 0; i < item.size(); i++) {
                    argv[i + 1] = item[i].c_str();
                }
            
                fFactory = createDSPFactory(argc, argv, fLibraryPath, "", "", "", fTarget, fError, 3);
                
            } else {
                
                int argc = item.size();
                const char* argv[argc];
                for (int i = 0; i < item.size(); i++) {
                    argv[i] = item[i].c_str();
                }
                
                fFactory = createDSPFactory(argc, argv, fLibraryPath, "", "", fInput, fTarget, fError, 3);
            }
            
            if (!fFactory)  {
                printf("Cannot create factory... %s\n", fError);
                return false;
            } 
            
            fDSP = createDSPInstance(fFactory);
            
            if (!fDSP)  {
                printf("Cannot create instance...\n");
                return false;
            } 
            
            res = bench();
            
            deleteDSPInstance(fDSP);
            deleteDSPFactory(fFactory);
            fFactory = 0;
            fDSP = 0;
            
            return true;
        }
    
};

int getStackSize()
{
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    size_t size;
    int res;
    
    if ((res = pthread_attr_getstacksize(&attributes, &size))) {
        printf("pthread_attr_getstacksize error %d\n", res);
        return 0;
    } else {
        printf("getStackSize size = %d\n", size);
        return size;
    }
}

void setStackSize(size_t size)
{
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    int res;
    
    if ((res = pthread_attr_setstacksize(&attributes, size))) {
        printf("pthread_attr_setstacksize error %d\n", res);
    } 
    
    printf("setStackSize size = %d\n", size);
}

#ifdef MAIN_LLVM
int main(int argc, char* argv[])
{
    int COUNT = lopt(argv, "-count", 2000);
    int VSIZE = lopt(argv, "-vec",  512);
    
    FaustLLVMOptimizer optimizer(argv[1], "", "", COUNT, VSIZE);
    
    vector<string> options = optimizer.findOptimize();
    
    cout << argv[1] << " ";
    
    for (int i = 0; i < options.size(); i++) {
        cout << options[i] << " ";
    }
    
    cout  << endl;
  	return 0;
}
#endif 


