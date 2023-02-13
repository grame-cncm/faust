/************************** BEGIN dsp-optimizer.h ***************************
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
***************************************************************************/

#ifndef __dsp_optimizer__
#define __dsp_optimizer__

#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <typeinfo>
#include <tuple>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-bench.h"

typedef std::vector<std::string> TOption;
typedef std::vector<TOption> TOptionTable;

/*
    A class to find optimal Faust compiler parameters for a given DSP.
*/
template <typename REAL>
class dsp_optimizer_real {

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
        bool fControl;
        bool fNeedExp10;
        int fDownSampling;
        int fUpSampling;
        int fFilter;
    
        std::string fFilename;
        std::string fInput;
        std::string fTarget;
        std::string fError;
    
        TOptionTable fOptionsTable;
    
        std::tuple<double, double, double> bench(int run)
        {
            // First call with fCount = -1 will be used to estimate fCount by giving the wanted measure duration
            if (fCount == -1) {
                measure_dsp_real<REAL> mes(fDSP, fBufferSize, 5., fTrace, fControl, fDownSampling, fUpSampling, fFilter);
                mes.measure();
                // fCount is kept from the first duration measure
                fCount = mes.getCount();
                std::pair<double, double> res = mes.getStats();
                return std::make_tuple(res.first, res.second, mes.getCPULoad());
            } else {
                measure_dsp_real<REAL> mes(fDSP, fBufferSize, fCount, fTrace, fControl, fDownSampling, fUpSampling, fFilter);
                for (int i = 0; i < run; i++) {
                    mes.measure();
                    std::pair<double, double> res = mes.getStats();
                    if (fTrace) {
                        fprintf(stdout, "%f MBytes/sec, SD : %f%% (DSP CPU : %f%% at %d Hz)\n", res.first, res.second, (mes.getCPULoad() * 100), int(BENCH_SAMPLE_RATE));
                    }
                    FAUSTBENCH_LOG<double>(res.first);
                }
                std::pair<double, double> res = mes.getStats();
                return std::make_tuple(res.first, res.second, mes.getCPULoad());
            }
        }
    
        void init()
        {
            // Scalar mode
            std::vector <std::string> t0;
            t0.push_back("-scal");
            fOptionsTable.push_back(t0);
            
            // Scalar mode with exp10
            std::vector <std::string> t0_exp10;
            t0_exp10.push_back("-scal");
            t0_exp10.push_back("-exp10");
            fOptionsTable.push_back(t0_exp10);
          
            // vec -lv 0
            for (int size = 4; size <= fBufferSize; size *= 2) {
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(std::to_string(size));
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 0 -fun
            for (int size = 4; size <= fBufferSize; size *= 2) {
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-fun");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(std::to_string(size));
                fOptionsTable.push_back(t1);
            }
        
            /*
            // vec -lv 0 -g
            for (int size = 4; size <= fBufferSize; size *= 2) {
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(std::to_string(size));
                t1.push_back("-g");
                fOptionsTable.push_back(t1);
            }
            
            // vec -lv 0 -dfs
            for (int size = 4; size <= fBufferSize; size *= 2) {
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("0");
                t1.push_back("-vs");
                t1.push_back(std::to_string(size));
                t1.push_back("-dfs");
                fOptionsTable.push_back(t1);
            }
            */
            
            // vec -lv 1
            for (int size = 4; size <= fBufferSize; size *= 2) {
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(std::to_string(size));
                fOptionsTable.push_back(t1);
            }
             
            // vec -lv 1 -fun
            for (int size = 4; size <= fBufferSize; size *= 2) {
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-fun");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(std::to_string(size));
                fOptionsTable.push_back(t1);
            }
            
            /*
            // vec -lv 1 -g
            for (int size = 4; size <= fBufferSize; size *= 2) {
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(std::to_string(size));
                t1.push_back("-g");
                fOptionsTable.push_back(t1);
            }
         
            // vec -lv 1 -dfs
            for (int size = 4; size <= fBufferSize; size *= 2) {
                std::vector <std::string> t1;
                t1.push_back("-vec");
                t1.push_back("-lv");
                t1.push_back("1");
                t1.push_back("-vs");
                t1.push_back(std::to_string(size));
                t1.push_back("-dfs");
                fOptionsTable.push_back(t1);
            }
            
            // sch
            for (int size = 4; size <= fBufferSize; size *= 2) {
                 std::vector <std::string> t1;
                 t1.push_back("-sch");
                 t1.push_back("-vs");
                 t1.push_back(std::to_string(size));
                 fOptionsTable.push_back(t1);
             }
             */
        }
    
        void printItem(const std::vector <std::string>& item)
        {
            for (int i = 0; i < item.size(); i++) {
                fprintf(stdout, " %s", item[i].c_str());
            }
            fprintf(stdout, " : ");
        }
    
        std::vector <std::string> addArgvItems(const std::vector <std::string>& item, int argc, const char* argv[])
        {
            std::vector <std::string> res_item = item;
            for (int i = 0; i < argc ; i++) {
                res_item.push_back(argv[i]);
            }
            return res_item;
        }
        
        bool computeOne(const TOption& item, int run, std::tuple<double, double, double>& res)
        {
            int argc = 0;
            const char* argv[64];
            for (int i = 0; i < item.size(); i++) {
                argv[argc++] = item[i].c_str();
            }
            argv[argc] = nullptr;  // NULL terminated argv
            
            if (fInput == "") {
                fFactory = createDSPFactoryFromFile(fFilename.c_str(), argc, argv, fTarget, fError, fOptLevel);
            } else {
                fFactory = createDSPFactoryFromString("FaustDSP", fInput, argc, argv, fTarget, fError, fOptLevel);
            }
            
            if (!fFactory) {
                fprintf(stderr, "Cannot create factory : %s\n", fError.c_str());
                return false;
            }
            
            fDSP = fFactory->createDSPInstance();
            if (!fDSP) {
                fprintf(stderr, "Cannot create instance...\n");
                return false;
            }
            
            if (fTrace) printItem(item);
            
            res = bench(run);
            // fDSP is deallocated by bench calling measure_dsp
            
            deleteDSPFactory(fFactory);
            fFactory = nullptr;
            fDSP = nullptr;
            
            return true;
        }
    
        std::tuple<double, double, double, TOption> findOptimizedParametersAux(const TOptionTable& options)
        {
            std::vector<std::tuple<int, double, double, double> > table_res;
            std::tuple<double, double, double> res = {0., 0., 0.};
            
            for (int i = 0; i < options.size(); i++) {
                if (computeOne(addArgvItems(options[i], fArgc, fArgv), fRun, res)) {
                    table_res.push_back(std::make_tuple(i, std::get<0>(res), std::get<1>(res), std::get<2>(res)));
                } else {
                    fprintf(stderr, "computeOne error...\n");
                }
            }
            
            sort(table_res.begin(), table_res.end(), compareFun);
            return std::make_tuple(std::get<1>(table_res[0]),
                                   std::get<2>(table_res[0]),
                                   std::get<3>(table_res[0]),
                                   options[std::get<0>(table_res[0])]);
        }

        static bool compareFun(std::tuple<int, double, double, double> i, std::tuple<int, double, double, double> j)
        {
            return (std::get<1>(i) > std::get<1>(j));
        }
    
        bool init(const std::string& filename,
                  const std::string& input,
                  int argc,
                  const char* argv[],
                  const std::string& target,
                  int buffer_size,
                  int run,
                  int opt_level_max,
                  bool trace,
                  bool control,
                  int ds,
                  int us,
                  int filter)
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
            fControl = control;
            fNeedExp10 = false;
            fDownSampling = ds;
            fUpSampling = us;
            fFilter = filter;
            
            init();
            
            if (fTrace) fprintf(stdout, "Estimate timing parameters\n");
            std::tuple<double, double, double> res1 = {0., 0., 0.};
            if (!computeOne(addArgvItems(fOptionsTable[0], fArgc, fArgv), 1, res1)) {
                fprintf(stderr, "computeOne error...\n");
                return false;
            }
            if (fTrace) fprintf(stdout, "Testing -exp10 need\n");
            std::tuple<double, double, double> res2 = {0., 0., 0.};
            if (!computeOne(addArgvItems(fOptionsTable[1], fArgc, fArgv), 1, res2)) {
                fprintf(stderr, "computeOne error...\n");
                return false;
            }
            fNeedExp10 = (std::get<0>(res2) > (std::get<0>(res1) * 1.05)); // If more than 5% faster
            return true;
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
         * @param trace - whether to log the trace
         * @param control - whether to activate random changes of all control values at each cycle
         * @param ds - downsampling factor
         * @param us - upsampling factor
         * @param filter - filter type
         * since the maximum value may change with new LLVM versions)
         */
        dsp_optimizer_real(const std::string& filename,
                           int argc,
                           const char* argv[],
                           const std::string& target,
                           int buffer_size,
                           int run = 1,
                           int opt_level = -1,
                           bool trace = true,
                           bool control = false,
                           int ds = 0,
                           int us = 0,
                           int filter = 0)
        {
            if (!init(filename, "", argc, argv, target, buffer_size, run, opt_level, trace, control, ds, us, filter)) {
                throw std::bad_alloc();
            }
        }
    
        virtual ~dsp_optimizer_real()
        {}
    
        /**
         * Returns the best compilations parameters.
         *
         * @return the best result (in Megabytes/seconds) and DSP CPU (in 0..1), and compilation parameters in a vector.
         */
        std::tuple<double, double, double, TOption> findOptimizedParameters()
        {
            if (fTrace) fprintf(stdout, "Discover best parameters option\n");
            std::tuple<double, double, double, TOption> best1 = findOptimizedParametersAux(fOptionsTable);
            
            if (fTrace) fprintf(stdout, "Refined with -mcd\n");
            TOptionTable options_table;
        
            // Start from 0
            TOption best2 = std::get<3>(best1);
            best2.push_back("-mcd");
            best2.push_back("0");
            options_table.push_back(best2);
            for (int size = 2; size <= 256; size *= 2) {
                TOption best2 = std::get<3>(best1);
                best2.push_back("-mcd");
                best2.push_back(std::to_string(size));
                options_table.push_back(best2);
            }
            
            if (fNeedExp10) {
                if (fTrace) fprintf(stdout, "Use -exp10\n");
                TOption t0_exp10;
                t0_exp10.push_back("-exp10");
                options_table.push_back(t0_exp10);
            }
            
            std::tuple<double, double, double, TOption> best3 = findOptimizedParametersAux(options_table);
           
            if (std::get<3>(best3)[0] == "-vec") {
                if (fTrace) fprintf(stdout, "Check with -g or -dfs\n");
                // Current best
                TOptionTable options_table1;
                {
                    TOption best2 = std::get<3>(best3);
                    options_table1.push_back(best2);
                }
                // Add -g
                {
                    TOption best2 = std::get<3>(best3);
                    best2.push_back("-g");
                    options_table1.push_back(best2);
                }
                // Add -dfs
                {
                    TOption best2 = std::get<3>(best3);
                    best2.push_back("-dfs");
                    options_table1.push_back(best2);
                }
                // Add -g and -dfs
                {
                    TOption best2 = std::get<3>(best3);
                    best2.push_back("-g");
                    best2.push_back("-dfs");
                    options_table1.push_back(best2);
                }
                return findOptimizedParametersAux(options_table1);
            } else {
                return best3;
            }
        }
    
        /**
         * Returns the error (in case on compilation error).
         *
         * @return the compilation error as a string.
         */
        const char* getError() { return fError.c_str(); }
    
};

class dsp_optimizer : public dsp_optimizer_real<FAUSTFLOAT> {

    public:
    
        dsp_optimizer(const std::string& filename,
                       int argc,
                       const char* argv[],
                       const std::string& target,
                       int buffer_size,
                       int run = 1,
                       int opt_level = -1,
                       bool trace = true,
                       bool control = false,
                       int ds = 0,
                       int us = 0,
                       int filter = 0)
        :dsp_optimizer_real<FAUSTFLOAT>(filename, argc, argv,
                                        target, buffer_size,
                                        run, opt_level,
                                        trace, control,
                                        ds, us, filter)
        {}
    
};
    
#endif

/************************** END dsp-optimizer.h **************************/
