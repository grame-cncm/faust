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

// Reference: https://apple.stackexchange.com/questions/238777/how-do-i-identify-which-cpu-a-macbook-uses

class mydspmulti : public decorator_dsp {
    
    private:
    
        std::string fCPU;
    
        std::string getCPUModel()
        {
            char name[65] = {0};
            size_t size = sizeof(name) - 1;
            return (sysctlbyname("machdep.cpu.brand_string", &name, &size, nullptr, 0) >= 0) ? name : "";
        }
    
        bool is_core2() { return false; }
        bool is_penryn() { return false; }
        bool is_nehalem() { return false; }
        bool is_westmere() { return false; }
        bool is_sandybridge() { return (fCPU == "i3-2") || (fCPU == "i5-2") || (fCPU == "i7-2"); }
        bool is_ivybridge() { return (fCPU == "i3-3") || (fCPU == "i5-3") || (fCPU == "i7-3"); }
        bool is_haswell() { return (fCPU == "i3-4") || (fCPU == "i5-4") || (fCPU == "i7-4"); }
        bool is_broadwell() { return (fCPU == "i3-5") || (fCPU == "i5-5") || (fCPU == "i7-5"); }
        bool is_skylake() { return (fCPU == "i3-6") || (fCPU == "i5-6") || (fCPU == "i7-6"); }
        bool is_skylake_avx512() { return (fCPU == "i3-7") || (fCPU == "i5-7") || (fCPU == "i7-7"); }
        bool is_cannonlake() { return (fCPU == "i3-8") || (fCPU == "i5-8") || (fCPU == "i7-8"); }
    
    public:
    
        mydspmulti()
        {
            std::string name = getCPUModel();
            std::stringstream reader(name);
            std::string tok1, tok2, tok3;
            reader >> tok1;
            reader >> tok2;
            reader >> tok3;
            fCPU = tok3.substr(0,4);
            
        #ifdef core2
            if (!fDSP && is_core2()) {
                std::cout << "Allocate for core2" << std::endl;
                fDSP = new mydspcore2();
            }
        #endif
            
        #ifdef penryn
            if (!fDSP && is_penryn()) {
                std::cout << "Allocate for penryn" << std::endl;
                fDSP = new mydsppenryn();
            }
        #endif
            
        #ifdef nehalem
            if (!fDSP && is_nehalem()) {
                std::cout << "Allocate for nehalem" << std::endl;
                fDSP = new mydspnehalem();
            }
        #endif
            
        #ifdef westmere
            if (!fDSP && is_westmere()) {
                std::cout << "Allocate for westmere" << std::endl;
                fDSP = new mydspwestmere();
            }
        #endif
            
        #ifdef sandybridge
            if (!fDSP && is_sandybridge()) {
                std::cout << "Allocate for sandybridge" << std::endl;
                fDSP = new mydspsandybridge();
            }
        #endif
            
        #ifdef ivybridge
            if (!fDSP && is_ivybridge()) {
                std::cout << "Allocate for ivybridge" << std::endl;
                fDSP = new mydspivybridge();
            }
        #endif
            
        #ifdef haswell
            if (!fDSP && is_haswell()) {
                std::cout << "Allocate for haswell" << std::endl;
                fDSP = new mydsphaswell();
            }
        #endif
            
        #ifdef broadwell
            if (!fDSP && is_broadwell()) {
                std::cout << "Allocate for broadwell" << std::endl;
                fDSP = new mydspbroadwell();
            }
        #endif
            
        #ifdef skylake
            if (!fDSP && is_skylake()) {
                std::cout << "Allocate for skylake" << std::endl;
                fDSP = new mydspskylake();
            }
        #endif
            
        #ifdef skylake_avx512
            if (!fDSP && is_skylake_avx512()) {
                std::cout << "Allocate for skylake_avx512" << std::endl;
                fDSP = new mydspskylake_avx512();
            }
        #endif
            
        #ifdef cannonlake
            if (!fDSP && is_cannonlake()) {
                std::cout << "Allocate for cannonlake" << std::endl;
                fDSP = new mydspcannonlake();
            }
        #endif
            
            // Default case: allocate generic
            if (!fDSP) {
                std::cout << "Allocate for generic" << std::endl;
                fDSP = new mydspgeneric();
            }
        }
        
        virtual ~mydspmulti()
        {}
  
};

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
