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
TBlockStatement* gCurBlock = NULL;

TSignal* test1()
{
    return new TInt(5);
}

TSignal* test2()
{
    return new TFloat(10.f);
}

TSignal* test3()
{
    return new TInput(0);
}

TSignal* test4()
{
    return new TPrimOp(new TInput(0), new TInput(1), "+");
}

TSignal* test5()
{
    return new TPrimOp(new TPrimOp(new TInput(0), new TFloat(10.f), "+"), new TPrimOp(new TInput(0), new TInput(1), "+"), "*");
}

TSignal* test6()
{
    return new TPrimOp(new TPrimOp(new TInput(0), new TFloat(10.f), "+"), new TFloat(10.f), "*");
}

TSignal* test10()
{
    return new TVectorize(new TInput(0), 4);
}

TSignal* test11()
{
    return new TSerialize(new TVectorize(new TInput(0), 4));
}

TSignal* test21()
{
    return new TConcat(new TVectorize(new TInput(0), 4), new TVectorize(new TInput(1), 3));
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
    //compiler.compileTop(test3());
    //compiler.compileTop(test4());
    compiler.compileTop(test5());
    //compiler.compileTop(test6());
    //compiler.compileTop(test10());
    //compiler.compileTop(test21());

	return 0;
}
