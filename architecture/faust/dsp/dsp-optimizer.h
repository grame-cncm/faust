
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

#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <unistd.h>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-bench.h"

class dsp_optimizer {

    private:
        
        dsp_bench fBench;

        FAUSTFLOAT* fBuffer;    // a buffer of fNV * fVSize samples

        unsigned int fNV;        // number of vectors in BIG buffer (should exceed cache)
        unsigned int fITER;      // number of iterations per measure
        unsigned int fVSIZE;     // size of a vector in samples
        unsigned int fIDX;       // current vector number (0 <= VIdx < fNV)
        
        int fOptLevel;      
        llvm_dsp_factory* fFactory;
        llvm_dsp* fDSP;
        
        std::string fFilename;
        std::string fInput;
        std::string fLibraryPath;
        std::string fTarget;
        std::string fError;
        
        std::vector< std::vector <std::string > > fOptionsTable;
    
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

        void allocBuffers(int numOutChan, FAUSTFLOAT** outChannel)
        {
            unsigned int BSIZE = fNV * fVSIZE;
            fBuffer = (FAUSTFLOAT*)calloc(BSIZE, sizeof(FAUSTFLOAT));
            
            int R0_0 = 0;
            for (int j = 0; j < BSIZE; j++) {
                int R0temp0 = (12345 + (1103515245 * R0_0));
                fBuffer[j] = 4.656613e-10f * R0temp0;
                R0_0 = R0temp0;
            }
            
            // Allocate output channels (not initialized)
            for (int i = 0; i < numOutChan; i++) {
                outChannel[i] = (FAUSTFLOAT*)calloc(fVSIZE, sizeof(FAUSTFLOAT));
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
            fIDX = (1 + fIDX) % fNV;
            return &fBuffer[fIDX * fVSIZE];
        }
        
        double bench()
        {
            int numInChan = fDSP->getNumInputs();
            int numOutChan = fDSP->getNumOutputs();
            
            FAUSTFLOAT* inChannel[numInChan];
            FAUSTFLOAT* outChannel[numOutChan];
            
            fBench.openMeasure();
            
            // Allocate input buffers (initialized with white noise)
            allocBuffers(numOutChan, outChannel);
            
            // Init the dsp with a reasonable sampling rate
            fDSP->init(48000);
            
            AVOIDDENORMALS;
            
            while (fBench.isRunning()) {
                // Allocate new input buffers to avoid L2 cache
                for (int c = 0; c < numInChan; c++) { inChannel[c] = nextVect(); }
                fBench.startMeasure();
                fDSP->compute(fVSIZE, inChannel, outChannel);
                fBench.stopMeasure();
            }
            
            fBench.closeMeasure();
            double res = fBench.getStats(fVSIZE, fDSP->getNumInputs(), fDSP->getNumOutputs());
            std::cout << res <<  std::endl;
            
            freeBuffers(numOutChan, outChannel);
            return res;
        }
    
        void init()
        {
            setRealtimePriority();
            
            // Scalar mode
            std::vector <std::string> t0;
            t0.push_back("-scal");
            fOptionsTable.push_back(t0);
            
            /*
             std::stringstream num;
             num << 32;
             std::vector <string> t1;
             t1.push_back("-sch");
             t1.push_back("-vs");
             t1.push_back(num.str());
             fOptionsTable.push_back(t1);
             
             
             std::stringstream num;
             num << 512;
             std::vector <string> t1;
             t1.push_back("-vec");
             t1.push_back("-lv");
             t1.push_back("1");
             t1.push_back("-vs");
             t1.push_back(num.str());
             fOptionsTable.push_back(t1);
             */
            
            // vec -lv 0
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 1
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 0 -dfs
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                t1.push_back("-dfs");
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 1 -dfs
            for (int size = 4; size <= fVSIZE; size *= 2) {
                std::stringstream num;
                num << size;
                std::vector <std::string> t1;
                t1.push_back("-dfs");
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(num.str());
                fOptionsTable.push_back(t1);
            }
            
            /*
             // sch
             for (int size = 8; size <= fVSIZE; size *= 2) {
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
    
        const char* getError() { return fError.c_str(); }
        
        void printItem(const std::vector <std::string>& item)
        {
            for (int i = 0; i < item.size(); i++) {
                std::cout << " " << item[i];
            }
            std::cout << " : ";
        }
        
        bool computeOne(int index, double& res)
        {
            std::vector <std::string> item = fOptionsTable[index];
            printItem(item);
            
            if (fInput == "") {
                
                int argc = item.size() + 2;
                const char* argv[argc];
                argv[0] = "-I";
                argv[1] = fLibraryPath.c_str();
                for (int i = 0; i < item.size(); i++) {
                    argv[i + 2] = item[i].c_str();
                }
                
                fFactory = createDSPFactoryFromFile(fFilename.c_str(), argc, argv, fTarget, fError, fOptLevel);
                
            } else {
                
                int argc = item.size();
                const char* argv[argc];
                for (int i = 0; i < item.size(); i++) {
                    argv[i] = item[i].c_str();
                }
                
                fFactory = createDSPFactoryFromString("FaustDSP", fInput, argc, argv, fTarget, fError, fOptLevel);
            }
            
            if (!fFactory)  {
                std::cout << "Cannot create factory : " << fError.c_str() << std::endl;
                return false;
            } else {
                //std::cout << "Factory correctly generated" << endl;
            }
            
            /*
             std::vector<std::string> path_list = getLibraryList(fFactory);
             std::vector<std::string>::iterator it;
             for (it = path_list.begin(); it != path_list.end(); it++) {
                std::string file = *it;
                std::cout << "file " << file.c_str() << endl;
             }
             */
            
            fDSP = fFactory->createDSPInstance();
            
            if (!fDSP)  {
                std::cout << "Cannot create instance..." << std::endl;
                return false;
            }
            
            res = bench();
            
            delete fDSP;
            deleteDSPFactory(fFactory);
            fFactory = 0;
            fDSP = 0;
            
            return true;
        }
    
        static int getStackSize()
        {
            pthread_attr_t attributes;
            pthread_attr_init(&attributes);
            size_t size;
            int res;
            
            if ((res = pthread_attr_getstacksize(&attributes, &size))) {
                std::cout << "pthread_attr_getstacksize error " << res <<  std::endl;
                return 0;
            } else {
                std::cout << "getStackSize size = " << size <<  std::endl;
                return size;
            }
        }
        
        static void setStackSize(size_t size)
        {
            pthread_attr_t attributes;
            pthread_attr_init(&attributes);
            int res;
            
            if ((res = pthread_attr_setstacksize(&attributes, size))) {
                 std::cout << "pthread_attr_setstacksize error " << res <<  std::endl;
            } 
            
             std::cout << "setStackSize size = " << size <<  std::endl;
        }
       
    public:
    
        dsp_optimizer(const char* filename,
                      const std::string& library_path,
                      const std::string& target,
                      int size,
                      int opt_level_max = -1)
            :fBench(20000, 10)
        {
            fBuffer = 0;
            fFilename = filename;
            fInput = "";
            fLibraryPath = library_path;
            fTarget = target;
            fOptLevel = opt_level_max;
            
            fNV = 4096;     // number of vectors in BIG buffer (should exceed cache)
            fITER = 10;     // number of iterations per measure
            fVSIZE = size;  // size of a vector in samples
            fIDX = 0;       // current vector number (0 <= VIdx < NV)
            
            init();
        }
        
        dsp_optimizer(const std::string& input,
                      const std::string& library_path,
                      const std::string& target,
                      int size,
                      int opt_level_max = -1)
            :fBench(20000, 10)
         {
            fBuffer = 0;
            fFilename = "";
            fInput = input;
            fLibraryPath = library_path;
            fTarget = target;
            fOptLevel = opt_level_max;
           
            fNV = 4096;     // number of vectors in BIG buffer (should exceed cache)
            fITER = 10;     // number of iterations per measure
            fVSIZE = size;  // size of a vector in samples
            fIDX = 0;       // current vector number (0 <= VIdx < fNV)
            
            init();
        }
    
        static bool myfunction(std::pair <int, double > i, std::pair <int, double > j) { return (i.second > j.second); }
    
        virtual ~dsp_optimizer()
        {}
    
        std::vector<std::string> findOptimizedParameters()
        {
            std::vector<  std::pair <int, double > > table_res;
            double res;
             
            for (int i = 0; i < fOptionsTable.size(); i++) {
                if (computeOne(i, res)) {
                    table_res.push_back(std::make_pair(i, res));
                } else {
                    std::cout << "computeOne error..." << std::endl;
                }
            }
            
            sort(table_res.begin(), table_res.end(), myfunction);
             
            if (table_res.size() > 0) {
                return fOptionsTable[table_res[0].first];
            } else {
                // Scalar...
                std::cout << "findOptimize no options found..." << std::endl;
                return fOptionsTable[0];
            }
        }
    
};


