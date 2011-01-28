
#include "TStatement.hh"
#include "TValue.hh"

void TDeclareStatement::generate(ostream* dst, int n)
{
    fType->generate(dst, n);
    *dst << " " << fName;
}

void TStoreStatement::generate(ostream* dst, int n)
{
    tab(n, *dst);
    fAddress->generate(dst, n);
    fIndex->generate(dst, n);
    *dst << " = ";
    fValue->generate(dst, n);

}

void TBlockStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst);
    *dst << "block {" << endl;
    for (it = fCode.begin(); it != fCode.end(); it++) {
        (*it)->generate(dst, n+1);
    }
    tab(n, *dst); *dst << "}" << endl;
}

void TLoopStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for ("; fIndex->generate(dst, n); *dst << ", "<< fSize << ") {" << endl;;
    fCode->generate(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TSubLoopStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "nestedfor ("; fIndex->generate(dst, n); *dst << ", "<< fSize << ") {" << endl;;
    fCode->generate(dst, n+1);
    tab(n, *dst); *dst << "}";
}
