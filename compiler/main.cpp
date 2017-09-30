/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <iostream>
#include "compatibility.hh"
#include "dsp_factory.hh"

using namespace std;

// Standalone compiler uses the real 'alarm' function
unsigned faust_alarm(unsigned seconds)
{
    return alarm(seconds);
}

int main(int argc, const char* argv[])
{
    string error_msg;
    dsp_factory_base* factory = compileFaustFactory(argc, argv, "FaustDSP", 0, error_msg, true);
    delete factory;
    if (error_msg == "") {
        return 0;
    } else {
        cerr << error_msg;
        return 1;
    }
}
