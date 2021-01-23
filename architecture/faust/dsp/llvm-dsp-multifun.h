/************************** BEGIN llvm-dsp-multifun.h **************************/
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

#ifndef LLVM_mydsp_multifun_H
#define LLVM_mydsp_multifun_H

#include <string>
#include <iostream>
#include <assert.h>

#include "mydspgeneric.h"

/*
    A DSP decorator that loads the CPU optimised version of the code and instantiate it.
    This file is used by the 'faust2object' tool to produce a single multi CPU aware .o file,
    to be compiled and linked with the mydspmulti class.
 
    To test: c++ -std=c++11 FOOmulti.cpp FOOgeneric.cpp -o FOOmulti
 */
class mydspmulti : public decorator_dsp {
    
    public:
    
        mydspmulti():decorator_dsp(createmydspgeneric())
        {}
    
        virtual ~mydspmulti()
        {}
  
};

// Factory API
dsp* createmydspmulti() { return new mydspmulti(); }

#endif
/**************************  END  llvm-dsp-multifun.h **************************/

#ifdef TEST
int main()
{
    mydspmulti multi;
    std::cout << multi.getNumInputs() << std::endl;
    std::cout << multi.getNumOutputs() << std::endl;
}
#endif
