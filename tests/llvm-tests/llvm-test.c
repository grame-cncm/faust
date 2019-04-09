/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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

#include <faust/dsp/llvm-c-dsp.h>
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, const char** argv)
{
    int argc1 = 0;
    const char* argv1[2];
    argv1[argc1++] = "-vec";
    argv1[argc1] = 0;
    
    char err[4096] = {};
    auto fac = createCDSPFactoryFromString("score",
                                           "process = +;",
                                           argc1, argv1, "", err, -1);
    cout << err << endl;
    assert(fac);
}
