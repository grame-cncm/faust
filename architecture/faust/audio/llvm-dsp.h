/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
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

 ************************************************************************
 ************************************************************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <string>
#include "faust/audio/dsp.h"

class llvmdspaux;

class llvmdsp : public dsp {

    private:
    
        llvmdspaux* fDSP;
        
    public:
  
        llvmdsp(int argc, char *argv[], const std::string& library_path, const std::string& name, const std::string& input, const std::string& target, char* error_msg, int opt_level = 3);
        llvmdsp(int argc, char *argv[], const std::string& library_path, const std::string& name, const std::string& input, char* error_msg, int opt_level = 3);
        llvmdsp(int argc, char *argv[], const std::string& library_path, const std::string& target, char* error_msg, int opt_level = 3);
        llvmdsp(int argc, char *argv[], const std::string& library_path, char* error_msg, int opt_level = 3);
        
        virtual ~llvmdsp();
        
        bool init();
     
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        static void classInit(int samplingFreq);
        virtual void instanceInit(int samplingFreq);
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* interface);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
     
};


