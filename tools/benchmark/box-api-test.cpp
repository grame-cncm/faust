/************************************************************************
 FAUST Architecture File
 Copyright (C) 2024 GRAME, Centre National de Creation Musicale
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

// Tests for newly exposed Box API constructors.
// Validates that constructors produce valid boxes and that
// isBox* destructors round-trip correctly.

#include <iostream>
#include <string>

#include "faust/dsp/libfaust-box.h"

using namespace std;

static bool compile(const string& name_app, Box box)
{
    string error_msg;
    string source = createSourceFromBoxes(name_app, box, "cpp", 0, nullptr, error_msg);
    if (source != "") {
        return true;
    } else {
        cerr << "  compile error: " << error_msg;
        return false;
    }
}

// Test boxIPar constructor and isBoxIPar destructor
static bool test_iPar()
{
    createLibContext();
    // Use boxWire() as placeholder for iterator variable (boxIdent is internal)
    Box box = boxIPar(boxWire(), boxInt(4), boxWire());
    Box x, y, z;
    bool ok = isBoxIPar(box, x, y, z);
    destroyLibContext();
    return ok;
}

// Test boxISeq constructor and isBoxISeq destructor
static bool test_iSeq()
{
    createLibContext();
    Box box = boxISeq(boxWire(), boxInt(4), boxWire());
    Box x, y, z;
    bool ok = isBoxISeq(box, x, y, z);
    destroyLibContext();
    return ok;
}

// Test boxISum constructor and isBoxISum destructor
static bool test_iSum()
{
    createLibContext();
    Box box = boxISum(boxWire(), boxInt(4), boxMul());
    Box x, y, z;
    bool ok = isBoxISum(box, x, y, z);
    destroyLibContext();
    return ok;
}

// Test boxIProd constructor and isBoxIProd destructor
static bool test_iProd()
{
    createLibContext();
    Box box = boxIProd(boxWire(), boxInt(4), boxAdd());
    Box x, y, z;
    bool ok = isBoxIProd(box, x, y, z);
    destroyLibContext();
    return ok;
}

// Test boxInputs and boxOutputs constructors and destructors
static bool test_inputs_outputs()
{
    createLibContext();
    Box inp = boxInputs(boxWire());
    Box out = boxOutputs(boxWire());
    Box x;
    bool ok1 = isBoxInputs(inp, x);
    bool ok2 = isBoxOutputs(out, x);
    destroyLibContext();
    return ok1 && ok2;
}

// Test boxDelay1 produces a valid box that compiles
static bool test_delay1()
{
    createLibContext();
    // delay1 is a 1-input, 1-output primitive: _ : mem
    Box box = boxSeq(boxWire(), boxDelay1());
    bool ok = compile("test_delay1", box);
    destroyLibContext();
    return ok;
}

// Test boxPrefix produces a valid box that compiles
static bool test_prefix()
{
    createLibContext();
    // prefix takes 3 inputs: prefix(init, x, y) -> y with init value
    // Use as: 0, _, _ : prefix
    Box box = boxSeq(boxPar3(boxInt(0), boxWire(), boxWire()), boxPrefix());
    bool ok = compile("test_prefix", box);
    destroyLibContext();
    return ok;
}

// Test boxEnable and boxControl produce valid boxes that compile
static bool test_enable_control()
{
    bool ok1, ok2;
    createLibContext();
    {
        // enable takes 2 inputs: signal, enable_flag
        Box enable_box = boxSeq(boxPar(boxWire(), boxInt(1)), boxEnable());
        ok1 = compile("test_enable", enable_box);
    }
    destroyLibContext();

    createLibContext();
    {
        // control takes 2 inputs: signal, control_flag
        Box control_box = boxSeq(boxPar(boxWire(), boxInt(1)), boxControl());
        ok2 = compile("test_control", control_box);
    }
    destroyLibContext();

    return ok1 && ok2;
}

// Test boxAssertBound, boxLowest, boxHighest produce valid boxes
static bool test_bounds()
{
    bool ok1, ok2, ok3;
    createLibContext();
    {
        // assertbounds takes 3 inputs: lo, hi, x
        Box assert_box = boxSeq(boxPar3(boxReal(-1.0), boxReal(1.0), boxWire()), boxAssertBound());
        ok1 = compile("test_assertbound", assert_box);
    }
    destroyLibContext();

    createLibContext();
    {
        // lowest takes 1 input
        Box lowest_box = boxSeq(boxWire(), boxLowest());
        ok2 = compile("test_lowest", lowest_box);
    }
    destroyLibContext();

    createLibContext();
    {
        // highest takes 1 input
        Box highest_box = boxSeq(boxWire(), boxHighest());
        ok3 = compile("test_highest", highest_box);
    }
    destroyLibContext();

    return ok1 && ok2 && ok3;
}

// Test boxEnvironment constructor and isBoxEnvironment destructor
static bool test_environment()
{
    createLibContext();
    Box box = boxEnvironment();
    bool ok = isBoxEnvironment(box);
    destroyLibContext();
    return ok;
}

// Test boxMetadata constructor and isBoxMetadata destructor
static bool test_metadata()
{
    createLibContext();
    // Use boxPar of two ints as a dummy metadata list
    Box box = boxMetadata(boxWire(), boxPar(boxInt(0), boxInt(0)));
    Box exp, mdlist;
    bool ok = isBoxMetadata(box, exp, mdlist);
    destroyLibContext();
    return ok;
}

// Test boxComponent and boxLibrary constructors and destructors
// (box construction only, not compilation since files don't exist)
static bool test_component_library()
{
    createLibContext();
    Box comp = boxComponent("foo.dsp");
    Box filename;
    bool ok1 = isBoxComponent(comp, filename);

    Box lib = boxLibrary("bar.dsp");
    bool ok2 = isBoxLibrary(lib, filename);
    destroyLibContext();
    return ok1 && ok2;
}

int main()
{
    int failures = 0;

    struct {
        const char* name;
        bool (*func)();
    } tests[] = {
        { "test_iPar",              test_iPar },
        { "test_iSeq",              test_iSeq },
        { "test_iSum",              test_iSum },
        { "test_iProd",             test_iProd },
        { "test_inputs_outputs",    test_inputs_outputs },
        { "test_delay1",            test_delay1 },
        { "test_prefix",            test_prefix },
        { "test_enable_control",    test_enable_control },
        { "test_bounds",            test_bounds },
        { "test_environment",       test_environment },
        { "test_metadata",          test_metadata },
        { "test_component_library", test_component_library },
    };

    for (const auto& t : tests) {
        bool pass = t.func();
        cout << (pass ? "PASS" : "FAIL") << ": " << t.name << endl;
        if (!pass) failures++;
    }

    cout << endl;
    if (failures == 0) {
        cout << "All tests passed." << endl;
    } else {
        cout << failures << " test(s) failed." << endl;
    }

    return failures;
}
