
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

#ifndef __dsp_optimizer__
#define __dsp_optimizer__

#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-bench.h"

/*
    A class to find optimal Faust compiler parameters for a given DSP.
*/
template <typename SAMPLE_TYPE>
class dsp_optimizer {

    private:
        
        time_bench* fBench;

        SAMPLE_TYPE* fBuffer;    // a buffer of fNV * fVSize samples

        unsigned int fNV;        // number of vectors in BIG buffer (should exceed cache)
        unsigned int fITER;      // number of iterations per measure
        unsigned int fVSIZE;     // size of a vector in samples
        unsigned int fIDX;       // current vector number (0 <= VIdx < fNV)
    
        int fArgc;
        const char** fArgv;
    
        int fOptLevel;      
        llvm_dsp_factory* fFactory;
        llvm_dsp* fDSP;
        
        std::string fFilename;
        std::string fInput;
        std::string fTarget;
        std::string fError;
        
        std::vector<std::vector <std::string> > fOptionsTable;
    
        bool setRealtimePriority()
        {
            struct passwd* pw;
            int err;
            uid_t uid;
            int policy;
            struct sched_param param;

            uid = getuid();
            pw = getpwnam("root");
            setuid(pw->pw_uid);

            pthread_getschedparam(pthread_self(), &policy, &param);
            policy = SCHED_RR;
            param.sched_priority = 80;
            err = pthread_setschedparam(pthread_self(), policy, &param);

            setuid(uid);
            return (err != -1);
        }

        void allocBuffers(int numOutChan, SAMPLE_TYPE** outChannel)
        {
            unsigned int BSIZE = fNV * fVSIZE;
            fBuffer = (SAMPLE_TYPE*)calloc(BSIZE, sizeof(SAMPLE_TYPE));
            
            int R0_0 = 0;
            for (int j = 0; j < BSIZE; j++) {
                int R0temp0 = (12345 + (1103515245 * R0_0));
                fBuffer[j] = 4.656613e-10f * R0temp0;
                R0_0 = R0temp0;
            }
            
            // Allocate output channels (not initialized)
            for (int i = 0; i < numOutChan; i++) {
                outChannel[i] = (SAMPLE_TYPE*)calloc(fVSIZE, sizeof(SAMPLE_TYPE));
            }
        }

        void freeBuffers(int numOutChan, SAMPLE_TYPE** outChannel)
        {
            for (int i = 0; i < numOutChan; i++) {
                free(outChannel[i]);
            }
            
            free(fBuffer);
        }

        SAMPLE_TYPE* nextVect()
        {
            fIDX = (1 + fIDX) % fNV;
            return &fBuffer[fIDX * fVSIZE];
        }
        
        double bench()
        {
            int numInChan = fDSP->getNumInputs();
            int numOutChan = fDSP->getNumOutputs();
            
            SAMPLE_TYPE* inChannel[numInChan];
            SAMPLE_TYPE* outChannel[numOutChan];
            
            fBench->openMeasure();
            
            // Allocate input buffers (initialized with white noise)
            allocBuffers(numOutChan, outChannel);
            
            // Init the dsp with a reasonable sampling rate
            fDSP->init(48000);
            
            AVOIDDENORMALS;
            
            while (fBench->isRunning()) {
                // Allocate new input buffers to avoid L2 cache
                for (int c = 0; c < numInChan; c++) { inChannel[c] = nextVect(); }
                fBench->startMeasure();
                // Force FAUSTFLOAT type even if dynamic one is different...
                fDSP->compute(fVSIZE, (FAUSTFLOAT**)inChannel, (FAUSTFLOAT**)outChannel);
                fBench->stopMeasure();
            }
            
            fBench->closeMeasure();
            double res = fBench->getStats(fVSIZE, fDSP->getNumInputs(), fDSP->getNumOutputs());
            std::cout << res << std::endl;
            
            freeBuffers(numOutChan, outChannel);
            return res;
        }
    
        void init()
        {
            setRealtimePriority();
         
            // Scalar mode
            std::vector <std::string> t0;
            if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t0.push_back("-double"); }
            t0.push_back("-scal");
            fOptionsTable.push_back(t0);
            
            SAMPLE_TYPE var;
            
            // vec -lv 0
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t1.push_back("-double"); }
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 0
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t1.push_back("-double"); }
                t1.push_back("-vec");
                t1.push_back("-fun");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 0 -g
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t1.push_back("-double"); }
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(num.str());
                t1.push_back("-g");
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 0 -dfs
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t1.push_back("-double"); }
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(num.str());
                t1.push_back("-dfs");
                fOptionsTable.push_back(t1);
            }
      
            // vec -lv 1
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t1.push_back("-double"); }
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 1 -g
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t1.push_back("-double"); }
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(num.str());
                t1.push_back("-g");
                fOptionsTable.push_back(t1);
            }
         
            // vec -lv 1 -dfs
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t1.push_back("-double"); }
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(num.str());
                t1.push_back("-dfs");
                fOptionsTable.push_back(t1);
            }
            
            /*
            // sch
            for (int size = 4; size <= fVSIZE; size *= 2) {
                 std::stringstream num;
                 num << size;
                 std::vector <std::string> t1;
                 t1.push_back("-sch");
                 t1.push_back("-vs");
                 t1.push_back(num.str());
                 fOptionsTable.push_back(t1);
             }
             */
        }
    
        void printItem(const std::vector <std::string>& item)
        {
            for (int i = 0; i < item.size(); i++) {
                std::cout << " " << item[i];
            }
            std::cout << " : ";
        }
    
        std::vector <std::string> addArgvItems(const std::vector <std::string>& item, int argc, const char* argv[])
        {
            std::vector <std::string> res_item = item;
            for (int i = 0; i < argc ; i++) {
                res_item.push_back(argv[i]);
            }
            return res_item;
        }
        
        bool computeOne(const std::vector<std::string>& item, double& res)
        {
            printItem(item);
            
            int argc = 0;
            const char* argv[64];
            for (int i = 0; i < item.size(); i++) {
                argv[argc++] = item[i].c_str();
            }
            argv[argc] = 0;  // NULL terminated argv
            
            if (fInput == "") {
                fFactory = createDSPFactoryFromFile(fFilename.c_str(), argc, argv, fTarget, fError, fOptLevel);
            } else {
                fFactory = createDSPFactoryFromString("FaustDSP", fInput, argc, argv, fTarget, fError, fOptLevel);
            }
            
            if (!fFactory) {
                std::cerr << "Cannot create factory : " << fError << std::endl;
                return false;
            }
            
            fDSP = fFactory->createDSPInstance();
            
            if (!fDSP) {
                std::cerr << "Cannot create instance..." << std::endl;
                return false;
            }
            
            res = bench();
            
            delete fDSP;
            deleteDSPFactory(fFactory);
            fFactory = 0;
            fDSP = 0;
            
            return true;
        }
    
        std::vector<std::string> findOptimizedParametersAux(const std::vector<std::vector <std::string> >& options, double& best)
        {
            std::vector<std::pair<int, double > > table_res;
            double res = 0.;
            
            for (int i = 0; i < options.size(); i++) {
                if (computeOne(addArgvItems(options[i], fArgc, fArgv), res)) {
                    table_res.push_back(std::make_pair(i, res));
                } else {
                    std::cerr << "computeOne error..." << std::endl;
                }
            }
            
            sort(table_res.begin(), table_res.end(), compareFun);
            best = table_res[0].second;
            return options[table_res[0].first];
        }

        static bool compareFun(std::pair<int, double> i, std::pair<int, double> j) { return (i.second > j.second); }
    
        static int getStackSize()
        {
            pthread_attr_t attributes;
            pthread_attr_init(&attributes);
            size_t size;
            int res;
            
            if ((res = pthread_attr_getstacksize(&attributes, &size))) {
                std::cerr << "pthread_attr_getstacksize error " << res << std::endl;
                return 0;
            } else {
                std::cerr << "getStackSize size = " << size << std::endl;
                return size;
            }
        }
        
        static void setStackSize(size_t size)
        {
            pthread_attr_t attributes;
            pthread_attr_init(&attributes);
            int res;
            
            if ((res = pthread_attr_setstacksize(&attributes, size))) {
                std::cerr << "pthread_attr_setstacksize error " << res << std::endl;
            }
            
            std::cout << "setStackSize size = " << size << std::endl;
        }
    
        void init(const std::string& filename, const std::string input, int argc, const char* argv[], const std::string& target, int size, int opt_level_max)
        {
            fBuffer = 0;
            fFilename = filename;
            fInput = input;
            fTarget = target;
            fOptLevel = opt_level_max;
            
            fNV = 4096;     // number of vectors in BIG buffer (should exceed cache)
            fITER = 10;     // number of iterations per measure
            fVSIZE = size;  // size of a vector in samples
            fIDX = 0;       // current vector number (0 <= VIdx < NV)
            
            fArgc = argc;
            fArgv = argv;
            
            init();
            
            std::cout << "Estimate timing parameters" << std::endl;
            double res;
            fBench = new time_bench(500, 10);
            if (computeOne(addArgvItems(fOptionsTable[0], fArgc, fArgv), res)) {
                double duration = fBench->measureDurationUsec();
                int cout = int (500 * (5 * 1e6 / duration));
                std::cout << "duration = " << duration/1e6 << " count = " << cout << std::endl;
                delete fBench;
                fBench = new time_bench(cout, 10);
            } else {
                std::cerr << "Error in dsp_optimizer constructor" << std::endl;
                throw std::bad_alloc();
            }
        }
    
    public:
    
        /**
         * Constructor.
         *
         * @param filename - the DSP filename
         * @param argc - the number of parameters in argv array 
         * @param argv - the array of parameters
         * @param target - the LLVM machine target (using empty string will take current machine settings)
         * @param buffer_size - the buffer size in sampels
         * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
         * since the maximum value may change with new LLVM versions)
         */
        dsp_optimizer(const char* filename,
                      int argc,
                      const char* argv[],
                      const std::string& target,
                      int buffer_size,
                      int opt_level = -1)
        {
            init(filename, "", argc, argv, target, buffer_size, opt_level);
        }
    
        /**
         * Constructor.
         *
         * @param input - the Faust program as a string
         * @param argc - the number of parameters in argv array
         * @param argv - the array of parameters
         * @param target - the LLVM machine target (using empty string will take current machine settings)
         * @param buffer_size - the buffer size in sampels
         * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
         * since the maximum value may change with new LLVM versions)
         */
        dsp_optimizer(const std::string& input,
                      int argc,
                      const char* argv[],
                      const std::string& target,
                      int buffer_size,
                      int opt_level = -1)
        {
            init("", input, argc, argv, target, buffer_size, opt_level);
        }
    
        virtual ~dsp_optimizer()
        {}
    
        /**
         * Returns the best compilation parameters in a vector.
         *
         * @param best - returns the best result (in Megabytes/seconds)
         *
         * @return the best compilation parameters in a vector.
         */
        std::vector<std::string> findOptimizedParameters(double& best)
        {
            std::cout << "Discover best parameters option" << std::endl;
            std::vector<std::string> best1 = findOptimizedParametersAux(fOptionsTable, best);
            
            std::cout << "Refined with -mcd" << std::endl;
            std::vector<std::vector <std::string> > options_table;
            for (int size = 2; size <= 256; size *= 2) {
                std::vector<std::string> best2 = best1;
                std::stringstream num;
                num << size;
                best2.push_back("-mcd");
                best2.push_back(num.str());
                options_table.push_back(best2);
            }
            
            return findOptimizedParametersAux(options_table, best);
        }
    
        /**
         * Returns the error (in case on compilation error).
         *
         * @return the compilation error as a string.
         */
        const char* getError() { return fError.c_str(); }
    
};

#endif
