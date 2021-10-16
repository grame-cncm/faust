/************************************************************************
 FAUST Architecture File
 Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>
#include <iostream>
#include <string>
#include <vector>

#include "faust/dsp/libfaust-box.h"
//#include "faust/dsp/llvm-dsp.h"
//#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/audio/jack-dsp.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/misc.h"

using namespace std;

/**
 * Return the current runtime sample rate.
 *
 * Reproduce the 'SR' definition in platform.lib: SR = min(192000.0, max(1.0, fconstant(int fSamplingFreq, <dummy.h>)));
 *
 * @return the current runtime sample rate.
 */

inline Box getSampleRate()
{
    return boxMin(boxReal(192000.0), boxMax(boxReal(1.0), boxFConst(SType::kSInt, "fSamplingFreq", "<dummy.h>")));
}

/**
 * Return the current runtime buffer size.
 *
 * Reproduce the 'BS' definition in platform.lib: BS = fvariable(int count, <dummy.h>);
 *
 * @return the current runtime buffer size.
 */
inline Box getBufferSize()
{
    return boxFVar(SType::kSInt, "count", "<dummy.h>");
}

#define COMPILER(exp)    \
{                        \
    createLibContext();  \
    exp                  \
    destroyLibContext(); \
}                        \
    
static void compile(const string& name, Box box, int argc = 0, const char* argv[] = nullptr)
{
    string error_msg;
    dsp_factory_base* factory = createCPPDSPFactoryFromBoxes(name, box, argc, argv, error_msg);
    if (factory) {
        factory->write(&cout);
        delete(factory);
    } else {
        cerr << error_msg;
    }
}

// process = 7, 3.14;

static void test1()
{
    COMPILER
    (
        Box box = boxPar(boxInt(7), boxReal(3.14));
        compile("test1", box);
    )
}

// process = 7, 3.14 : +;

static void test2()
{
    COMPILER
    (
        Box box = boxSeq(boxPar(boxInt(7), boxReal(3.14)), boxAdd());
        compile("test2", box);
    )
}

// process = _,_ : +;

static void test3()
{
    COMPILER
    (
        Box box = boxSeq(boxPar(boxWire(), boxWire()), boxAdd());
        compile("test3", box);
    )
}

// process = _ : +;  ==> connection error

static void test4()
{
    COMPILER
    (
        Box box = boxSeq(boxWire(), boxMul());
        compile("test4", box);
    )
}

// process = _,7 : @;

static void test5()
{
    COMPILER
    (
        Box box = boxSeq(boxPar(boxWire(), boxInt(7)), boxDelay());
        compile("test5", box);
    )
}

// process = _,hslider("Freq [midi:ctrl 7][style:knob]", 100, 100, 2000, 1) : *;

static void test6()
{
    COMPILER
    (
        Box box = boxSeq(boxPar(boxWire(), boxHSlider("Freq [midi:ctrl 7][style:knob]", boxReal(100), boxReal(100), boxReal(2000), boxReal(1))), boxMul());
        compile("test6", box);
    )
}

// import("stdfaust.lib");
// process = ma.SR, ma.BS;
static void test7()
{
    COMPILER
    (
        Box box = boxPar(getSampleRate(), getBufferSize());
        compile("test7", box);
    )
}

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    
    return 0;
}

