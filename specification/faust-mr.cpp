#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <map>

using namespace std;

#include "TType.hh"
#include "Text.hh"
#include "TLang.hh"
#include "TCompiler.hh"

int gVecSize = 32;
TBlockStatement* gExternalBlock = NULL;
TBlockStatement* gDecBlock = NULL;

bool gPrim = true;
bool gVec = true;
bool gSer = true;
bool gConcat = true;

static void Display(const string& test)
{
    cout << "// ====================="<< endl;
    cout << "// "<< test<< endl;
    cout << "// ====================="<< endl;
}

// Not compatible type  (input ==> int)
TSignal* test1(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test1");
    return new TInt(5);
}

TSignal* test2(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test2");
    return new TFloat(10.f);
}

TSignal* test3(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test3");
    return new TInput(0, 1);
}

TSignal* test4(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test4");
    return new TPrimOp(new TInput(0, 1), new TInput(1, 1), "+");
}

TSignal* test5(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test5");
    return new TPrimOp(new TPrimOp(new TInput(0, 1), new TFloat(10.f), "+"), new TPrimOp(new TInput(0, 1), new TInput(1, 1), "+"), "*");
}

TSignal* test6(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test6");
    return new TPrimOp(new TPrimOp(new TInput(0, 1), new TFloat(10.f), "+"), new TFloat(10.f), "*");
}

// Not compatible type  (input ==> float[4])
TSignal* test10(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test10");
    return new TVectorize(new TInput(0, 4), 4);
}

TSignal* test11(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    Display("test11");
    return new TSerialize(new TVectorize(new TInput(0, 4), 4));
}

// Not compatible type  (input ==> float[4][3])
TSignal* test11bis(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gConcat = concat;
    gSer = ser;
    Display("test11bis");
    return new TVectorize(new TVectorize(new TInput(0, 12), 4), 3);
}

TSignal* test12(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test12");
    return new TSerialize(new TSerialize(new TVectorize(new TVectorize(new TInput(0, 12), 4), 3)));
}

TSignal* test13(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test13");
    return new TSerialize(new TVectorize(new TSerialize(new TVectorize(new TInput(0, 12), 4)), 3));
}

// Not compatible type  (input ==> float[4])
TSignal* test14(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test14");
    return new TPrimOp(new TVectorize(new TInput(0, 4), 4), new TVectorize(new TInput(1, 4), 4), "+");
}

TSignal* test15(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test15");
    return new TSerialize(new TPrimOp(new TVectorize(new TInput(0, 4), 4), new TVectorize(new TInput(1, 4), 4), "+"));
}

TSignal* test15bis(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test15bis");
    return new TPrimOp(new TSerialize(new TVectorize(new TInput(0, 4), 4)), new TSerialize(new TVectorize(new TInput(1, 4), 4)), "+");
}

TSignal* test15ter(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test15ter");
    return new TSerialize(new TSerialize(new TPrimOp(
        new TVectorize(new TVectorize(new TInput(0, 12), 4), 3),
        new TVectorize(new TVectorize(new TInput(1, 12), 4), 3), "+")));
}

TSignal* test16(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test16");
    return new TSerialize(new TSerialize(new TPrimOp(new TVectorize(new TVectorize(new TInput(0, 12), 4), 3), new TVectorize(new TVectorize(new TInput(1, 12), 4), 3), "+")));
}

TSignal* test21(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test21");
    return new TSerialize(new TConcat(new TVectorize(new TInput(0, 4), 4), new TVectorize(new TInput(1, 3), 3)));
}

TSignal* test22(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test22");
    return new TVectorAt(new TVectorize(new TInput(0, 4), 4), new TInt(3));
}

TSignal* test23(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test23");
    return new TVectorAt(new TConcat(new TVectorize(new TInput(0, 4), 4), new TVectorize(new TInput(1, 3), 3)), new TInt(0));
}

TSignal* test30(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test30");
    return new TDelayAt(new TDelayLine(new TInput(0, 1), 100), new TInt(3));
}

TSignal* test40(bool prim, bool vec, bool ser, bool concat)
{
    gPrim = prim;
    gVec = vec;
    gSer = ser;
    gConcat = concat;
    Display("test40");
    TRecGroup* rec_group = new TRecGroup("RecGroup1");
    rec_group->fCode.push_back(new TPrimOp(new TInput(0, 1), new TRecProj(rec_group, 0), "+"));
    rec_group->fCode.push_back(new TPrimOp(new TInput(1, 1), new TRecProj(rec_group, 1), "*"));
    rec_group->fCode.push_back(new TInput(2, 1));
    return new TRecProj(rec_group, 1);
}

// vectorize(4):*(2):serialize:+(1);
TSignal* test50(bool prim, bool vec, bool ser, bool concat)
{
    return new TPrimOp(new TSerialize(new TPrimOp(new TVectorize(new TInput(0, 4), 4), new TFloat(2.f), "*")),  new TFloat(1.f), "+");
}

int main()
{
    TCompiler compiler;

    //compiler.compileTop(test1());
    //compiler.compileTop(test2(true, true, true, true));
    //compiler.compileTop(test3(true, true, true, true));
    //compiler.compileTop(test4(true, true, true, true));
    //compiler.compileTop(test5(true, true, true, true));
    //compiler.compileTop(test6(true, true, true, true));

    //compiler.compileTop(test10(true, true, true, true));

    //compiler.compileTop(test11(true, true, true, true));
    //compiler.compileTop(test11(true, false, true, true));
    //compiler.compileTop(test11(true, true, false, true));
    //compiler.compileTop(test11(true, false, false, true));

    //compiler.compileTop(test11bis(true, true, true, true));
    //compiler.compileTop(test12(true, true, true, true));
    //compiler.compileTop(test12(true, false, true, true));
    //compiler.compileTop(test12(true, true, false, true));
    //compiler.compileTop(test12(true, false, false, true));

    //compiler.compileTop(test13(true, true, true, true));
    //compiler.compileTop(test13(true, false, true, true));
    //compiler.compileTop(test13(true, true, false, true));
    //compiler.compileTop(test13(true, false, false, true));

    //compiler.compileTop(test14(true, true, true, true));

    //compiler.compileTop(test15(true, true, true, true));
    //compiler.compileTop(test15(true, false, true, true));
    //compiler.compileTop(test15(true, true, false, true));
    //compiler.compileTop(test15(true, false, false, true));

    //compiler.compileTop(test15(false, true, true, true));
    //compiler.compileTop(test15(false, false, true, true));
    //compiler.compileTop(test15(false, true, false, true));
    //compiler.compileTop(test15(false, false, false, true));

    //compiler.compileTop(test15bis(true, true, true, true));
    //compiler.compileTop(test15bis(true, false, true, true));
    //compiler.compileTop(test15bis(true, true, false, true));
    //compiler.compileTop(test15bis(true, false, false, true));

    //compiler.compileTop(test15bis(false, true, true, true));
    //compiler.compileTop(test15bis(false, false, true, true));
    //compiler.compileTop(test15bis(false, true, false, true));
    //compiler.compileTop(test15bis(false, false, false, true));

    //compiler.compileTop(test15ter(false, true, true, true));
    //compiler.compileTop(test15ter(false, false, true, true));
    //compiler.compileTop(test15ter(false, true, false, true));
    //compiler.compileTop(test15ter(false, false, false, true));

    //compiler.compileTop(test16(true, true, true, true));

    //compiler.compileTop(test21(true, true, true, true));
    //compiler.compileTop(test21(true, false, true, true));
    //compiler.compileTop(test21(true, true, false, true));
    //compiler.compileTop(test21(true, false, false, true));

    //compiler.compileTop(test21(true, true, true, false));
    //compiler.compileTop(test21(true, false, true, false));
    //compiler.compileTop(test21(true, true, false, false));
    //compiler.compileTop(test21(true, false, false, false));

    //compiler.compileTop(test22(true, true, true, false));
    //compiler.compileTop(test22(true, false, true, false));
    //compiler.compileTop(test22(true, true, false, false));
    //compiler.compileTop(test22(true, false, false, false));


    //compiler.compileTop(test22(true, true, true, true));

    //compiler.compileTop(test23(true, true, true, true));
    //compiler.compileTop(test23(true, false, true, true));
    //compiler.compileTop(test23(true, true, false, true));
    //compiler.compileTop(test23(true, false, false, true));

    //compiler.compileTop(test30(true, true, true, true));

    //compiler.compileTop(test40(true, true, true, true));

    compiler.compileTop(test50(true, true, true, true));

	return 0;
}
