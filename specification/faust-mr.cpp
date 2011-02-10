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

static void Display(const string& test)
{
    cout << "====================="<< endl;
    cout << test<< endl;
    cout << "====================="<< endl;
}

TSignal* test1()
{
    Display("test1");
    return new TInt(5);
}

TSignal* test2()
{
    Display("test2");
    return new TFloat(10.f);
}

TSignal* test3()
{
    Display("test3");
    return new TInput(0, 1);
}

TSignal* test4()
{
    Display("test4");
    return new TPrimOp(new TInput(0, 1), new TInput(1, 1), "+");
}

TSignal* test5()
{
    Display("test5");
    return new TPrimOp(new TPrimOp(new TInput(0, 1), new TFloat(10.f), "+"), new TPrimOp(new TInput(0, 1), new TInput(1, 1), "+"), "*");
}

TSignal* test6()
{
    Display("test6");
    return new TPrimOp(new TPrimOp(new TInput(0, 1), new TFloat(10.f), "+"), new TFloat(10.f), "*");
}

TSignal* test10()
{
    Display("test10");
    return new TVectorize(new TInput(0, 4), 4);
}

TSignal* test11()
{
    Display("test11");
    return new TSerialize(new TVectorize(new TInput(0, 4), 4));
}

TSignal* test11bis()
{
    Display("test11bis");
    return new TVectorize(new TVectorize(new TInput(0, 12), 4), 3);
}

TSignal* test12()
{
    /*
    TSignal* t1 = new TVectorize(new TVectorize(new TInput(0), 4), 3);
    TSignal* t2 = new TVectorize(new TInput(0), 4);
    cerr << "test12 " << t1->getRate() << endl;
    cerr << "test12 " << t2->getRate() << endl;
    */
    Display("test12");
    return new TSerialize(new TSerialize(new TVectorize(new TVectorize(new TInput(0, 12), 4), 3)));
}

TSignal* test13()
{
    Display("test13");
    return new TSerialize(new TVectorize(new TSerialize(new TVectorize(new TInput(0, 12), 4)), 3));
}

TSignal* test14()
{
    Display("test14");
    return new TPrimOp(new TVectorize(new TInput(0, 4), 4), new TVectorize(new TInput(1, 4), 4), "+");
}

TSignal* test15()
{
    Display("test15");
    return new TSerialize(new TPrimOp(new TVectorize(new TInput(0, 4), 4), new TVectorize(new TInput(1, 4), 4), "+"));
}

TSignal* test16()
{
    Display("test16");
    return new TSerialize(new TSerialize(new TPrimOp(new TVectorize(new TVectorize(new TInput(0, 12), 4), 3), new TVectorize(new TVectorize(new TInput(1, 12), 4), 3), "+")));
}

TSignal* test21()
{
    Display("test21");
    return new TConcat(new TVectorize(new TInput(0, 4), 4), new TVectorize(new TInput(1, 3), 3));
}

TSignal* test22()
{
    Display("test22");
    return new TVectorAt(new TVectorize(new TInput(0, 4), 4), new TInt(3));
}

TSignal* test23()
{
    Display("test23");
    return new TVectorAt(new TConcat(new TVectorize(new TInput(0, 4), 4), new TVectorize(new TInput(1, 3), 3)), new TInt(3));
}

TSignal* test30()
{
    Display("test30");
    return new TDelayAt(new TDelayLine(new TInput(0, 1), 100), new TInt(3));
}

TSignal* test40()
{
    Display("test40");
    TRecGroup* rec_group = new TRecGroup("RecGroup1");
    rec_group->fCode.push_back(new TPrimOp(new TInput(0, 1), new TRecProj(rec_group, 0), "+"));
    rec_group->fCode.push_back(new TPrimOp(new TInput(1, 1), new TRecProj(rec_group, 1), "*"));
    rec_group->fCode.push_back(new TInput(2, 1));
    return new TRecProj(rec_group, 1);
}


int main()
{
    /*
	TExp* e = new TGroup(2, new TGroup(8, new TOp(new TInput(16), new TNumber(16,10)) ) );
	TExp* f = new TLin(cprod(new TNumber(1, 0.5), new TOp(new TInput(1), new TNumber(1, 10))));
	TExp* g = new TAccess( cprod( new TNumber(1, 0.5),
	                              new TNumber(1, 10) ),
	                       new TNumber(1, 0.0) );

	TType t = f->type();
	cout << "type of f is : " << t.str() << endl;
	cout << "speed of f is : " << f->speed() << endl;

	cout << "for (int i=0; i<count; i++) {" << endl;
	e->compile(1, "output1", TIndex("i"), TIndex("i"));
	f->compile(1, "output2", TIndex("i").mult(2), TIndex("i"));
	g->compile(1, "output3", TIndex("i"), TIndex("i"));
	cout << "}" << endl;
    */

    TCompiler compiler;

    //compiler.compileTop(test1());
    //compiler.compileTop(test2());
    compiler.compileTop(test3());
    //compiler.compileTop(test4());
    //compiler.compileTop(test5());
    //compiler.compileTop(test6());

    //compiler.compileTop(test10());
    //compiler.compileTop(test11());
    //compiler.compileTop(test11bis());
    //compiler.compileTop(test12());
    compiler.compileTop(test13());
    //compiler.compileTop(test14());
    //compiler.compileTop(test15());
    //compiler.compileTop(test16());

    compiler.compileTop(test21());
    //compiler.compileTop(test22());
    //compiler.compileTop(test23());
    //compiler.compileTop(test30());

    //compiler.compileTop(test40());


	return 0;
}
