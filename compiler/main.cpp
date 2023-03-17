/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
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
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifdef FAUST_LIB
// 'libfaust' compiler uses an empty 'alarm' function
unsigned faust_alarm(unsigned seconds)
{
    return 0;
}
#else

#include <iostream>
#include "compatibility.hh"
#include "dsp_factory.hh"
#include "global.hh"

using namespace std;

// Standalone compiler uses the real 'alarm' function
unsigned faust_alarm(unsigned seconds)
{
    return alarm(seconds);
}

int main(int argc, const char* argv[])
{
    string error_msg;
    dsp_factory_base* factory = createFactory("FaustDSP", "", argc, argv, error_msg, true);
    
    // Possibly print warnings
    if (factory) {
        vector<string> warnings = factory->getWarningMessages();
        if (gAllWarning && warnings.size() > 0) {
            set<string> warnings_set;
            for (const auto& it : warnings) {
                warnings_set.insert(it);
            }
            cerr << endl << "===== Warnings ======" << endl;
            for (const auto& it : warnings_set) {
                cerr << it << endl;
            }
            cerr << "=====================" << endl;
        }
    }
    delete factory;
    if (error_msg == "") {
        return EXIT_SUCCESS;
    } else {
        cerr << error_msg;
        return EXIT_FAILURE;
    }
}

#endif
