
#include "TStatement.hh"
#include "TValue.hh"

void TDeclareStatement::generate(ostream* dst, int n)
{
    tab(n, *dst);
    *dst << "Dec ";
    fVector->generate(dst, n);
}

void TDeclareTypeStatement::generate(ostream* dst, int n)
{
    tab(n, *dst);
    *dst << "DecType ";
    fType->generate(dst, n);
}

void TStoreStatement::generate(ostream* dst, int n)
{
    tab(n, *dst);
    fAddress->generate(dst, n);
    *dst << " = ";
    fValue->generate(dst, n);
}

void TBlockStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    for (it = fCode.begin(); it != fCode.end(); it++) {
        (*it)->generate(dst, n);
    }
}

void TLoopStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for ("; fIndex->generate(dst, n); *dst << ", "<< fSize << ") {" << endl;
    fCode->generate(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TSubLoopStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "nestedfor ("; fIndex->generate(dst, n); *dst << ", "<< fSize << ") {" << endl;
    fCode->generate(dst, n+1);
    tab(n, *dst); *dst << "}";
}

void TIfStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "if ("; fIndex->generate(dst, n); *dst << ") {" << endl;
    fCode->generate(dst, n+1);
    tab(n, *dst); *dst << "}";
}

//// CPP

void TDeclareStatement::generateCPP(ostream* dst, int n)
{
    tab(n, *dst);
    fVector->fType->generateDef(dst, n);
    *dst << endl << endl;
    fVector->fType->generateCPP(dst, n);
    *dst << " ";
    *dst << fVector->fName;
    *dst << "[" << fVector->fSize << "]";
    *dst << ";" << endl;
}

void TDeclareTypeStatement::generateCPP(ostream* dst, int n)
{
    tab(n, *dst);
    fType->generateDef(dst, n);
    *dst << endl << endl;
}

void TStoreStatement::generateCPP(ostream* dst, int n)
{
    tab(n, *dst);
    fAddress->generateCPP(dst, n);
    *dst << " = ";
    fValue->generateCPP(dst, n);
    *dst << ";";
}

void TBlockStatement::generateCPP(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    for (it = fCode.begin(); it != fCode.end(); it++) {
        (*it)->generateCPP(dst, n);
    }
}

void TLoopStatement::generateCPP(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for (int "; fIndex->generateCPP(dst, n);
        *dst << " = 0; ";
        fIndex->generateCPP(dst, n);
        *dst << " < " << fSize << "; ";
        fIndex->generateCPP(dst, n);
        *dst << "++) {" << endl;
    fCode->generateCPP(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TSubLoopStatement::generateCPP(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for (int "; fIndex->generateCPP(dst, n);
        *dst << " = 0; ";
        fIndex->generateCPP(dst, n);
        *dst << " < " << fSize << "; ";
        fIndex->generateCPP(dst, n);
        *dst << "++) {" << endl;
    fCode->generateCPP(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TIfStatement::generateCPP(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "if ("; fIndex->generateCPP(dst, n); *dst << " == 0) {" << endl;
    fCode->generateCPP(dst, n+1);
    tab(n, *dst); *dst << "}";
}
