/************************** BEGIN llvm-dsp-multi.h **************************/
/************************************************************************
 ************************************************************************
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 ************************************************************************
 ************************************************************************/

#ifndef LLVM_mydsp_multi_H
#define LLVM_mydsp_multi_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <assert.h>

// CPUs
#ifdef core2
#include "mydspcore2.h"
#endif

#ifdef penryn
#include "mydsppenryn.h"
#endif

#ifdef nehalem
#include "mydspnehalem.h"
#endif

#ifdef westmere
#include "mydspwestmere.h"
#endif

#ifdef sandybridge
#include "mydspsandybridge.h"
#endif

#ifdef ivybridge
#include "mydspivybridge.h"
#endif

#ifdef haswell
#include "mydsphaswell.h"
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

#ifdef cannonlake
#include "mydspcannonlake.h"
#endif

// Always included
#include "mydspgeneric.h"

// For 'llvm::sys::getHostCPUName' function
#include <llvm/Support/Host.h>

/*
    A DSP decorator that loads the CPU optimised version of the code and instantiate it.
    This file ise used by the 'faust2object' tool to produce several CPU specific .h and .o files,
    to be compiled and linked with the mydspmulti class.
 
    // To test: c++ -std=c++11 FOOmulti.cpp -I `llvm-config --includedir` `llvm-config --ldflags --libs all --system-libs` FOO*.o -dead_strip -o FOOmulti
 */
class mydspmulti : public decorator_dsp {
    
    private:
    
        bool is_cpu(const std::string& name) { return llvm::sys::getHostCPUName().str() == name; }
    
    public:
    
        mydspmulti()
        {
            
        #ifdef core2
            if (!fDSP && is_cpu("core2")) {
                std::cout << "Allocate for core2" << std::endl;
                fDSP = createmydspcore2();
                return;
            }
        #endif
            
        #ifdef penryn
            if (!fDSP && is_cpu("penryn")) {
                std::cout << "Allocate for penryn" << std::endl;
                fDSP = createmydsppenryn();
                return;
            }
        #endif
            
        #ifdef nehalem
            if (!fDSP && is_cpu("nehalem")) {
                std::cout << "Allocate for nehalem" << std::endl;
                fDSP = createmydspnehalem();
                return;
            }
        #endif
            
        #ifdef westmere
            if (!fDSP && is_cpu("westmere")) {
                std::cout << "Allocate for westmere" << std::endl;
                fDSP = createmydspwestmere();
                return;
            }
        #endif
            
        #ifdef sandybridge
            if (!fDSP && is_cpu("sandybridge")) {
                std::cout << "Allocate for sandybridge" << std::endl;
                fDSP = createmydspsandybridge();
                return;
            }
        #endif
            
        #ifdef ivybridge
            if (!fDSP && is_cpu("ivybridge")) {
                std::cout << "Allocate for ivybridge" << std::endl;
                fDSP = createmydspivybridge();
                return;
            }
        #endif
            
        #ifdef haswell
            if (!fDSP && is_cpu("haswell")) {
                std::cout << "Allocate for haswell" << std::endl;
                fDSP = createmydsphaswell();
                return;
            }
        #endif
            
        #ifdef broadwell
            if (!fDSP && is_cpu("broadwell")) {
                std::cout << "Allocate for broadwell" << std::endl;
                fDSP = createmydspbroadwell();
                return;
            }
        #endif
            
        #ifdef skylake
            if (!fDSP && is_cpu("skylake")) {
                std::cout << "Allocate for skylake" << std::endl;
                fDSP = createmydspskylake();
                return;
            }
        #endif
            
        #ifdef skylake_avx512
            if (!fDSP && is_cpu("skylake-avx512")) {
                std::cout << "Allocate for skylake_avx512" << std::endl;
                fDSP = createmydspskylake_avx512();
                return;
            }
        #endif
            
        #ifdef cannonlake
            if (!fDSP && is_cpu("cannonlake")) {
                std::cout << "Allocate for cannonlake" << std::endl;
                fDSP = createmydspcannonlake();
                return;
            }
        #endif
            
            // Default case: allocate generic
            if (!fDSP) {
                std::cout << "Allocate for generic" << std::endl;
                fDSP = createmydspgeneric();
                return;
            }
            
            // Finally check fDSP
            assert(fDSP != nullptr);
        }
        
        virtual ~mydspmulti()
        {}
  
};

// Factory API
dsp* createmydspmulti() { return new mydspmulti(); }

#endif
/**************************  END  llvm-dsp-multi.h **************************/

//#define TEST
#ifdef TEST
int main()
{
    mydspmulti multi;
    std::cout << multi.getNumInputs() << std::endl;
    std::cout << multi.getNumOutputs() << std::endl;
}
#endif
