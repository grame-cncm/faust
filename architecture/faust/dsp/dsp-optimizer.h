
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
#include <typeinfo>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-bench.h"

#define SAMPLE_RATE 44100.0
/*
    A class to find optimal Faust compiler parameters for a given DSP.
*/
template <typename SAMPLE_TYPE>
class dsp_optimizer {

    private:
    
        int fBufferSize;     // size of a vector in samples
    
        int fArgc;
        const char** fArgv;
    
        int fOptLevel;      
        llvm_dsp_factory* fFactory;
        llvm_dsp* fDSP;
    
        int fRun;
        int fCount;
        bool fTrace;
    
        std::string fFilename;
        std::string fInput;
        std::string fTarget;
        std::string fError;
    
        std::vector<std::vector <std::string> > fOptionsTable;
    
        double bench(int run)
        {
            // First call with fCount = -1 will be used to estimate fCount by giving the wanted measure duration
            if (fCount == -1) {
                measure_dsp mes(fDSP, fBufferSize, 5., fTrace);
                mes.measure();
                // fCount is kept from the first duration measure
                fCount = mes.getCount();
                return mes.getStats();
            } else {
                measure_dsp mes(fDSP, fBufferSize, fCount, fTrace);
                for (int i = 0; i < run; i++) {
                    mes.measure();
                    if (fTrace) std::cout << mes.getStats() << " " << "(DSP CPU % : " << (mes.getCPULoad() * 100) << ")" << std::endl;
                    FAUSTBENCH_LOG<double>(mes.getStats());
                }
                return mes.getStats();
            }
        }
    
        void init()
        {
            // Scalar mode
            std::vector <std::string> t0;
            if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t0.push_back("-double"); }
            t0.push_back("-scal");
            fOptionsTable.push_back(t0);
            
            // Scalar mode with exp10
            std::vector <std::string> t0_exp10;
            if (typeid(SAMPLE_TYPE).name() == typeid(double).name()) { t0_exp10.push_back("-double"); }
            t0_exp10.push_back("-scal");
            t0_exp10.push_back("-exp10");
            fOptionsTable.push_back(t0_exp10);
       
            SAMPLE_TYPE var;
            
            // vec -lv 0
            for (int size = 4; size <= fBufferSize; size *= 2) {
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
            for (int size = 4; size <= fBufferSize; size *= 2) {
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
            for (int size = 4; size <= fBufferSize; size *= 2) {
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
            for (int size = 4; size <= fBufferSize; size *= 2) {
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
            for (int size = 4; size <= fBufferSize; size *= 2) {
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
            for (int size = 4; size <= fBufferSize; size *= 2) {
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
            for (int size = 4; size <= fBufferSize; size *= 2) {
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
            for (int size = 4; size <= fBufferSize; size *= 2) {
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
        
        bool computeOne(const std::vector<std::string>& item, int run, double& res)
        {
            if (fTrace) printItem(item);
            
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
            res = bench(run);
            // fDSP is deallocated by bench calling measure_dsp
            
            deleteDSPFactory(fFactory);
            fFactory = 0;
            fDSP = 0;
            
            return true;
        }
    
        std::pair<double, std::vector<std::string> > findOptimizedParametersAux(const std::vector<std::vector <std::string> >& options)
        {
            std::vector<std::pair<int, double > > table_res;
            double res = 0.;
            
            for (int i = 0; i < options.size(); i++) {
                if (computeOne(addArgvItems(options[i], fArgc, fArgv), fRun, res)) {
                    table_res.push_back(std::make_pair(i, res));
                } else {
                    std::cerr << "computeOne error..." << std::endl;
                }
            }
            
            sort(table_res.begin(), table_res.end(), compareFun);
            return std::make_pair(table_res[0].second, options[table_res[0].first]);
        }

        static bool compareFun(std::pair<int, double> i, std::pair<int, double> j) { return (i.second > j.second); }
    
        bool init(const std::string& filename, const std::string input,
                  int argc, const char* argv[],
                  const std::string& target,
                  int buffer_size, int run,
                  int opt_level_max,
                  bool trace)
        {
            fFilename = filename;
            fInput = input;
            fTarget = target;
            fOptLevel = opt_level_max;
            fRun = run;
            fBufferSize = buffer_size;  // size of a vector in samples
            fArgc = argc;
            fArgv = argv;
            fCount = -1;
            fTrace = trace;
            
            init();
            
            if (fTrace) std::cout << "Estimate timing parameters" << std::endl;
            double res;
            return computeOne(addArgvItems(fOptionsTable[0], fArgc, fArgv), 1, res);
        }
    
    public:
    
        /**
         * Constructor.
         *
         * @param filename - the DSP filename
         * @param argc - the number of parameters in argv array 
         * @param argv - the array of parameters
         * @param target - the LLVM machine target (using empty string will take current machine settings)
         * @param buffer_size - the buffer size in samples
         * @param run - the number of time each test must be run
         * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
         * since the maximum value may change with new LLVM versions)
         */
        dsp_optimizer(const char* filename,
                      int argc,
                      const char* argv[],
                      const std::string& target,
                      int buffer_size,
                      int run = 1,
                      int opt_level = -1,
                      bool trace = true)
        {
            if (!init(filename, "", argc, argv, target, buffer_size, run, opt_level, trace)) {
                throw std::bad_alloc();
            }
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
            if (!init("", input, argc, argv, target, buffer_size, opt_level)) {
                throw std::bad_alloc();
            }
        }
    
        virtual ~dsp_optimizer()
        {}
    
        /**
         * Returns the best compilations parameters.
         *
         * @return the best result (in Megabytes/seconds), and compilation parameters in a vector.
         */
        std::pair<double, std::vector<std::string> > findOptimizedParameters()
        {
            if (fTrace) std::cout << "Discover best parameters option" << std::endl;
            std::pair<double, std::vector<std::string> > best1 = findOptimizedParametersAux(fOptionsTable);
            
            if (fTrace) std::cout << "Refined with -mcd" << std::endl;
            std::vector<std::vector <std::string> > options_table;
            for (int size = 2; size <= 256; size *= 2) {
                std::vector<std::string> best2 = best1.second;
                std::stringstream num;
                num << size;
                best2.push_back("-mcd");
                best2.push_back(num.str());
                options_table.push_back(best2);
            }
            
            return findOptimizedParametersAux(options_table);
        }
    
        /**
         * Returns the error (in case on compilation error).
         *
         * @return the compilation error as a string.
         */
        const char* getError() { return fError.c_str(); }
    
};

#endif
