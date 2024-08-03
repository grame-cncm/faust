/************************** BEGIN dsp-multi.h ******************************
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

#ifndef dsp_multi_H
#define dsp_multi_H

#include <string>
#include <iostream>
#include <assert.h>

#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/meta.h"

// CPUs

#ifdef nocona
#include "mydspnocona.h"
#endif

#ifdef core2
#include "mydspcore2.h"
#endif

#ifdef penryn
#include "mydsppenryn.h"
#endif

#ifdef bonnell
#include "mydspbonnell.h"
#endif

#ifdef atom
#include "mydspatom.h"
#endif

#ifdef silvermont
#include "mydspsilvermont.h"
#endif

#ifdef slm
#include "mydspslm.h"
#endif

#ifdef goldmont
#include "mydspgoldmont.h"
#endif

#ifdef goldmont_plus
#include "mydspgoldmont_plus.h"
#endif

#ifdef tremont
#include "mydsptremont.h"
#endif

#ifdef nehalem
#include "mydspnehalem.h"
#endif

#ifdef corei7
#include "mydspcorei7.h"
#endif

#ifdef westmere
#include "mydspwestmere.h"
#endif

#ifdef sandybridge
#include "mydspsandybridge.h"
#endif

#ifdef corei7_avx
#include "mydspcorei7_avx.h"
#endif

#ifdef ivybridge
#include "mydspivybridge.h"
#endif

#ifdef core_avx_i
#include "mydspcore_avx_i.h"
#endif

#ifdef haswell
#include "mydsphaswell.h"
#endif

#ifdef core_avx2
#include "mydspcore_avx2.h"
#endif

#ifdef broadwell
#include "mydspbroadwell.h"
#endif

#ifdef skylake
#include "mydspskylake.h"
#endif

#ifdef skylake_avx512
#include "mydspskylake_avx512.h"
#endif

#ifdef skx
#include "mydspskx.h"
#endif

#ifdef cascadelake
#include "mydspcascadelake.h"
#endif

#ifdef cooperlake
#include "mydspcooperlake.h"
#endif

#ifdef cannonlake
#include "mydspcannonlake.h"
#endif

#ifdef icelake_client
#include "mydspicelake_client.h"
#endif

#ifdef icelake_server
#include "mydspicelake_server.h"
#endif

#ifdef tigerlake
#include "mydsptigerlake.h"
#endif

#ifdef knl
#include "mydspknl.h"
#endif

#ifdef knm
#include "mydspknm.h"
#endif

#ifdef k8
#include "mydspk8.h"
#endif

#ifdef athlon64
#include "mydspathlon64.h"
#endif

#ifdef athlon_fx
#include "mydspathlon_fx.h"
#endif

#ifdef opteron
#include "mydspopteron.h"
#endif

#ifdef k8_sse3
#include "mydspk8_sse3.h"
#endif

#ifdef athlon64_sse3
#include "mydspathlon64_sse3.h"
#endif

#ifdef opteron_sse3
#include "mydspopteron_sse3.h"
#endif

#ifdef amdfam10
#include "mydspamdfam10.h"
#endif

#ifdef barcelona
#include "mydspbarcelona.h"
#endif

#ifdef btver1
#include "mydspbtver1.h"
#endif

#ifdef btver2
#include "mydspbtver2.h"
#endif

#ifdef bdver1
#include "mydspbdver1.h"
#endif

#ifdef bdver2
#include "mydspbdver2.h"
#endif

#ifdef bdver3
#include "mydspbdver3.h"
#endif

#ifdef bdver4
#include "mydspbdver4.h"
#endif

#ifdef znver1
#include "mydspznver1.h"
#endif

#ifdef znver2
#include "mydspznver2.h"
#endif

#ifdef x86_64
#include "mydspx86_64.h"
#endif

#ifdef apple_m1
#include "mydspapple_m1.h"
#endif

#ifdef apple_m2
#include "mydspapple_m2.h"
#endif

#ifdef apple_m3
#include "mydspapple_m3.h"
#endif

// Always included
#include "mydspgeneric.h"

// For 'llvm::sys::getHostCPUName' function
#include <llvm/TargetParser/Host.h>
#include <llvm/ADT/StringRef.h>

/*
    A DSP decorator that loads the CPU optimised version of the code and instantiate it.
    This file is used by the 'faust2object' tool to produce several CPU specific .h and .o files,
    to be compiled and linked with the mydspmulti class.
 
    // To test: c++ -std=c++11 FOOmulti.cpp -I `llvm-config --includedir` `llvm-config --ldflags --libs all --system-libs` FOO*.o -dead_strip -o FOOmulti
 */
class mydspmulti : public decorator_dsp {
    
    private:
    
        struct Meta1 : Meta
        {
            std::string fOptions;
            
            void declare(const char* key, const char* value)
            {
                if (strcmp("compile_options", key) == 0) {
                    fOptions = value;
                }
            }
        };
    
        bool is_cpu(const std::string& name) { return llvm::sys::getHostCPUName().str() == name; }
    
    public:
    
        mydspmulti()
        {
            
        #ifdef nocona
            if (!fDSP && is_cpu("nocona")) {
                std::cout << "Allocate for nocona" << std::endl;
                fDSP = createmydspnocona();
                goto adapter;
            }
        #endif
            
        #ifdef core2
            if (!fDSP && is_cpu("core2")) {
                std::cout << "Allocate for core2" << std::endl;
                fDSP = createmydspcore2();
                goto adapter;
            }
        #endif
            
        #ifdef penryn
            if (!fDSP && is_cpu("penryn")) {
                std::cout << "Allocate for penryn" << std::endl;
                fDSP = createmydsppenryn();
                goto adapter;
            }
        #endif
            
        #ifdef bonnell
            if (!fDSP && is_cpu("bonnell")) {
                std::cout << "Allocate for bonnell" << std::endl;
                fDSP = createmydspbonnell();
                goto adapter;
            }
        #endif
            
        #ifdef atom
            if (!fDSP && is_cpu("atom")) {
                std::cout << "Allocate for atom" << std::endl;
                fDSP = createmydspatom();
                goto adapter;
            }
        #endif
            
        #ifdef silvermont
            if (!fDSP && is_cpu("silvermont")) {
                std::cout << "Allocate for silvermont" << std::endl;
                fDSP = createmydspsilvermont();
                goto adapter;
            }
        #endif
            
        #ifdef slm
            if (!fDSP && is_cpu("slm")) {
                std::cout << "Allocate for slm" << std::endl;
                fDSP = createmydspslm();
                goto adapter;
            }
        #endif
            
        #ifdef goldmont
            if (!fDSP && is_cpu("goldmont")) {
                std::cout << "Allocate for goldmont" << std::endl;
                fDSP = createmydspgoldmont();
                goto adapter;
            }
        #endif
            
        #ifdef goldmont_plus
            if (!fDSP && is_cpu("goldmont-plus")) {
                std::cout << "Allocate for goldmont-plus" << std::endl;
                fDSP = createmydspgoldmont_plus();
                goto adapter;
            }
        #endif
            
        #ifdef tremont
            if (!fDSP && is_cpu("tremont")) {
                std::cout << "Allocate for tremont" << std::endl;
                fDSP = createmydsptremont();
                goto adapter;
            }
        #endif
            
        #ifdef nehalem
            if (!fDSP && is_cpu("nehalem")) {
                std::cout << "Allocate for nehalem" << std::endl;
                fDSP = createmydspnehalem();
                goto adapter;
            }
        #endif
            
        #ifdef corei7
            if (!fDSP && is_cpu("corei7")) {
                std::cout << "Allocate for corei7" << std::endl;
                fDSP = createmydspcorei7();
                goto adapter;
            }
        #endif
            
        #ifdef westmere
            if (!fDSP && is_cpu("westmere")) {
                std::cout << "Allocate for westmere" << std::endl;
                fDSP = createmydspwestmere();
                goto adapter;
            }
        #endif
            
        #ifdef sandybridge
            if (!fDSP && is_cpu("sandybridge")) {
                std::cout << "Allocate for sandybridge" << std::endl;
                fDSP = createmydspsandybridge();
                goto adapter;
            }
        #endif
            
        #ifdef corei7_avx
            if (!fDSP && is_cpu("corei7-avx")) {
                std::cout << "Allocate for corei7-avx" << std::endl;
                fDSP = createmydspcorei7_avx();
                goto adapter;
            }
        #endif
            
        #ifdef ivybridge
            if (!fDSP && is_cpu("ivybridge")) {
                std::cout << "Allocate for ivybridge" << std::endl;
                fDSP = createmydspivybridge();
                goto adapter;
            }
        #endif
            
        #ifdef core_avx_i
            if (!fDSP && is_cpu("core-avx-i")) {
                std::cout << "Allocate for core-avx-i" << std::endl;
                fDSP = createmydspcore_avx_i();
                goto adapter;
            }
        #endif
            
        #ifdef haswell
            if (!fDSP && is_cpu("haswell")) {
                std::cout << "Allocate for haswell" << std::endl;
                fDSP = createmydsphaswell();
                goto adapter;
            }
        #endif
            
        #ifdef core_avx2
            if (!fDSP && is_cpu("core-avx2")) {
                std::cout << "Allocate for core-avx2" << std::endl;
                fDSP = createmydspcore_avx2();
                goto adapter;
            }
        #endif
            
        #ifdef broadwell
            if (!fDSP && is_cpu("broadwell")) {
                std::cout << "Allocate for broadwell" << std::endl;
                fDSP = createmydspbroadwell();
                goto adapter;
            }
        #endif
            
        #ifdef skylake
            if (!fDSP && is_cpu("skylake")) {
                std::cout << "Allocate for skylake" << std::endl;
                fDSP = createmydspskylake();
                goto adapter;
            }
        #endif
            
        #ifdef skylake_avx512
            if (!fDSP && is_cpu("skylake-avx512")) {
                std::cout << "Allocate for skylake_avx512" << std::endl;
                fDSP = createmydspskylake_avx512();
                goto adapter;
            }
        #endif
            
        #ifdef skx
            if (!fDSP && is_cpu("skx")) {
                std::cout << "Allocate for skx" << std::endl;
                fDSP = createmydspskx();
                goto adapter;
            }
        #endif
            
        #ifdef cascadelake
            if (!fDSP && is_cpu("cascadelake")) {
                std::cout << "Allocate for cascadelake" << std::endl;
                fDSP = createmydspcascadelake();
                goto adapter;
            }
        #endif
            
        #ifdef cooperlake
            if (!fDSP && is_cpu("cooperlake")) {
                std::cout << "Allocate for cooperlake" << std::endl;
                fDSP = createmydspcooperlake();
                goto adapter;
            }
        #endif
            
        #ifdef cannonlake
            if (!fDSP && is_cpu("cannonlake")) {
                std::cout << "Allocate for cannonlake" << std::endl;
                fDSP = createmydspcannonlake();
                goto adapter;
            }
        #endif
            
        #ifdef icelake_client
            if (!fDSP && is_cpu("icelake-client")) {
                std::cout << "Allocate for icelake-client" << std::endl;
                fDSP = createmydspicelake_client();
                goto adapter;
            }
        #endif
            
        #ifdef icelake_server
            if (!fDSP && is_cpu("icelake-server")) {
                std::cout << "Allocate for icelake-server" << std::endl;
                fDSP = createmydspicelake_server();
                goto adapter;
            }
        #endif
            
        #ifdef tigerlake
            if (!fDSP && is_cpu("tigerlake")) {
                std::cout << "Allocate for tigerlake" << std::endl;
                fDSP = createmydsptigerlake();
                goto adapter;
            }
        #endif
            
        #ifdef knl
            if (!fDSP && is_cpu("knl")) {
                std::cout << "Allocate for knl" << std::endl;
                fDSP = createmydspknl();
                goto adapter;
            }
        #endif
            
        #ifdef knm
            if (!fDSP && is_cpu("knm")) {
                std::cout << "Allocate for knm" << std::endl;
                fDSP = createmydspknm();
                goto adapter;
            }
        #endif

        #ifdef k8
            if (!fDSP && is_cpu("k8")) {
                std::cout << "Allocate for k8" << std::endl;
                fDSP = createmydspk8();
                goto adapter;
            }
        #endif
            
        #ifdef athlon64
            if (!fDSP && is_cpu("athlon64")) {
                std::cout << "Allocate for athlon64" << std::endl;
                fDSP = createmydspathlon64();
                goto adapter;
            }
        #endif
            
        #ifdef athlon_fx
            if (!fDSP && is_cpu("athlon-fx")) {
                std::cout << "Allocate for athlon-fx" << std::endl;
                fDSP = createmydspathlon_fx();
                goto adapter;
            }
        #endif
            
        #ifdef opteron
            if (!fDSP && is_cpu("opteron")) {
                std::cout << "Allocate for opteron" << std::endl;
                fDSP = createmydspopteron();
                goto adapter;
            }
        #endif
            
        #ifdef k8_sse3
            if (!fDSP && is_cpu("k8-sse3")) {
                std::cout << "Allocate for k8-sse3" << std::endl;
                fDSP = createmydspk8_sse3();
                goto adapter;
            }
        #endif
            
        #ifdef athlon64_sse3
            if (!fDSP && is_cpu("athlon64-sse3")) {
                std::cout << "Allocate for athlon64-sse3" << std::endl;
                fDSP = createmydspathlon64_sse3();
                goto adapter;
            }
        #endif
            
        #ifdef opteron_sse3
            if (!fDSP && is_cpu("opteron-sse3")) {
                std::cout << "Allocate for opteron-sse3" << std::endl;
                fDSP = createmydspopteron_sse3();
                goto adapter;
            }
        #endif
            
        #ifdef amdfam10
            if (!fDSP && is_cpu("amdfam10")) {
                std::cout << "Allocate for amdfam10" << std::endl;
                fDSP = createmydspamdfam10();
                goto adapter;
            }
        #endif
            
        #ifdef barcelona
            if (!fDSP && is_cpu("barcelona")) {
                std::cout << "Allocate for barcelona" << std::endl;
                fDSP = createmydspbarcelona();
                goto adapter;
            }
        #endif
            
        #ifdef btver1
            if (!fDSP && is_cpu("btver1")) {
                std::cout << "Allocate for btver1" << std::endl;
                fDSP = createmydspbtver1();
                goto adapter;
            }
        #endif
            
        #ifdef btver2
            if (!fDSP && is_cpu("btver2")) {
                std::cout << "Allocate for btver2" << std::endl;
                fDSP = createmydspbtver2();
                goto adapter;
            }
        #endif
            
        #ifdef bdver1
            if (!fDSP && is_cpu("bdver1")) {
                std::cout << "Allocate for bdver1" << std::endl;
                fDSP = createmydspbdver1();
                goto adapter;
            }
        #endif
            
        #ifdef bdver2
            if (!fDSP && is_cpu("bdver2")) {
                std::cout << "Allocate for bdver2" << std::endl;
                fDSP = createmydspbdver2();
                goto adapter;
            }
        #endif
            
        #ifdef bdver3
            if (!fDSP && is_cpu("bdver3")) {
                std::cout << "Allocate for bdver3" << std::endl;
                fDSP = createmydspbdver3();
                goto adapter;
            }
        #endif
            
        #ifdef bdver4
            if (!fDSP && is_cpu("bdver4")) {
                std::cout << "Allocate for bdver4" << std::endl;
                fDSP = createmydspbdver4();
                goto adapter;
            }
        #endif
            
        #ifdef znver1
            if (!fDSP && is_cpu("znver1")) {
                std::cout << "Allocate for znver1" << std::endl;
                fDSP = createmydspznver1();
                goto adapter;
            }
        #endif
            
        #ifdef znver2
            if (!fDSP && is_cpu("znver2")) {
                std::cout << "Allocate for znver2" << std::endl;
                fDSP = createmydspznver2();
                goto adapter;
            }
        #endif
            
        #ifdef x86_64
            if (!fDSP && is_cpu("x86-64")) {
                std::cout << "Allocate for x86-64" << std::endl;
                fDSP = createmydspx86_64();
                goto adapter;
            }
        #endif
        
        #ifdef apple_m1
            if (!fDSP && is_cpu("apple-m1")) {
                std::cout << "Allocate for apple-m1" << std::endl;
                fDSP = createmydspapple_m1();
                goto adapter;
            }
        #endif
        
        #ifdef apple_m2
            if (!fDSP && is_cpu("apple-m1")) {
                std::cout << "Allocate for apple-m2" << std::endl;
                fDSP = createmydspapple_m2();
                goto adapter;
            }
        #endif
                
        #ifdef apple_m3
            if (!fDSP && is_cpu("apple-m3")) {
                std::cout << "Allocate for apple-m3" << std::endl;
                fDSP = createmydspapple_m3();
                goto adapter;
            }
        #endif
            
            // Default case: allocate generic
            if (!fDSP) {
                std::cout << "Allocate for generic" << std::endl;
                fDSP = createmydspgeneric();
                goto adapter;
            }
       
        adapter:
            
            // Finally check fDSP
            assert(fDSP);
            
            // Create a DS/US + Filter adapted DSP
            std::string error;
            fDSP = createSRAdapter<float>(fDSP, error, DOWN_SAMPLING, UP_SAMPLING, FILTER_TYPE);
            
            Meta1 meta;
            fDSP->metadata(&meta);
            std::cout << "Faust compile options : " << meta.fOptions << std::endl;
        }
    
        virtual ~mydspmulti()
        {}
  
};

// Factory API
dsp* createmydspmulti() { return new mydspmulti(); }

#endif

#ifdef TEST
int main()
{
    mydspmulti multi;
    std::cout << multi.getNumInputs() << std::endl;
    std::cout << multi.getNumOutputs() << std::endl;
}
#endif

/************************** END dsp-multi.h **************************/
