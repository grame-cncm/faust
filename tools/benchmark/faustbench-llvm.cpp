
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#include "faust/dsp/dsp-optimizer.h"
#include "faust/misc.h"

using namespace std;

template <typename T>
static void bench(dsp_optimizer<T> optimizer, const string& name)
{
    double value;
    vector<string> options = optimizer.findOptimizedParameters(value);
    cout << "Best value is for '" << name << "' is : " << value << " with ";
    for (int i = 0; i < options.size(); i++) {
        cout << options[i] << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "faustbench-llvm [options] <foo.dsp>" << endl;
        return 0;
    }
    
    int index = 1;
    bool is_double = isopt(argv, "-double");
    int buffer_size = 512;
    
    cout << "Libfaust version : " << getCLibFaustVersion () << std::endl;
    
    const char* argv1[64];
    int argc1 = 0;
    
    cout << "Compiled with additional options : ";
    for (argc1 = 0; argc1 < (argc - 2); argc1++) {
        argv1[argc1] = argv[index + argc1];
        cout << argv1[argc1] << " ";
    }
    cout << endl;
    
    // Add library
    argv1[argc1++] = "-I";
    argv1[argc1++] = "/usr/local/share/faust";
  
    try {
        if (is_double) {
            bench(dsp_optimizer<double>(argv[argc-1], argc1, argv1, "", buffer_size), argv[1]);
        } else {
            bench(dsp_optimizer<float>(argv[argc-1], argc1, argv1, "", buffer_size), argv[1]);
        }
    } catch (...) {}
    
  	return 0;
}
