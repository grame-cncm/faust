/************************************************************************

    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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

************************************************************************
************************************************************************/

#include "faust/dsp/llvm-c-dsp.h"
#include <stdlib.h>
#include <sstream>

#ifdef _WIN32
#define STRDUP _strdup
#else
#define STRDUP strdup
#endif

using namespace std;

static char gLastError[256];

llvm_dsp_factory* createCDSPFactoryFromFileAux(const char* filename,
                                               const char* argv,
                                               const char* target,
                                               int opt_level)
{
    int argc1 = 0;
    const char* argv1[64];
    stringstream os(argv);
    string token;  
               
    // Allocate parameters
    while (os >> token) {               
        argv1[argc1++] = STRDUP(token.c_str());
    }
        
    llvm_dsp_factory* factory = createCDSPFactoryFromFile(filename, argc1, argv1, target, gLastError, opt_level);
    
    // Free parameters
    for (int i = 0; i < argc1; i++) {
        free((void*)argv1[i]);
    }
    return factory;
}
      
llvm_dsp_factory* createCDSPFactoryFromStringAux(const char* name_app,
                                                 const char* dsp_content,
                                                 const char* argv,
                                                 const char* target,
                                                 int opt_level)
{
    int argc1 = 0;
    const char* argv1[64];
    stringstream os(argv);
    string token;    
    
    // Allocate parameters             
    while (os >> token) {               
        argv1[argc1++] = STRDUP(token.c_str());
    }
    
    llvm_dsp_factory* factory = createCDSPFactoryFromString(name_app, dsp_content, argc1, argv1, target, gLastError, opt_level);
    
    // Free parameters
    for (int i = 0; i < argc1; i++) {
        free((void*)argv1[i]);
    }
    return factory;
}
                                                                                    
const char* getCDSPLastError() 
{
    return gLastError;
}
