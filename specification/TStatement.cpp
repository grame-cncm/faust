
#include "TStatement.hh"
#include "TValue.hh"

// Pseudo code generation

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

// CPP generation

void TDeclareStatement::generateCPP(ostream* dst, int n)
{
    tab(n, *dst);
    fVector->fType->generateDef(dst, n);
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
    *dst << endl;
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

// CPP generation no alias

void TDeclareStatement::generateCPPNoAlias(ostream* dst, int n)
{
    tab(n, *dst);
    fVector->fType->generateDefNoAlias(dst, n);
    fVector->fType->generateCPPNoAlias(dst, n);
    *dst << " ";
    *dst << fVector->fName;
    *dst << "[" << fVector->fSize << "]";
    *dst << ";" << endl;
}

void TDeclareTypeStatement::generateCPPNoAlias(ostream* dst, int n)
{
    tab(n, *dst);
    fType->generateDefNoAlias(dst, n);
    *dst << endl;
}

void TStoreStatement::generateCPPNoAlias(ostream* dst, int n)
{
    // TODO : generate additional nested loops to access complex typed addresses and values
    tab(n, *dst);
    fAddress->generateCPPNoAlias(dst, n);
    fAddress->getType()->generate(dst, n);
    *dst << " = ";
    fValue->generateCPPNoAlias(dst, n);
    fValue->getType()->generate(dst, n);
    *dst << ";";
}

void TBlockStatement::generateCPPNoAlias(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    for (it = fCode.begin(); it != fCode.end(); it++) {
        (*it)->generateCPPNoAlias(dst, n);
    }
}

void TLoopStatement::generateCPPNoAlias(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for (int "; fIndex->generateCPPNoAlias(dst, n);
        *dst << " = 0; ";
        fIndex->generateCPPNoAlias(dst, n);
        *dst << " < " << fSize << "; ";
        fIndex->generateCPPNoAlias(dst, n);
        *dst << "++) {" << endl;
    fCode->generateCPPNoAlias(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TSubLoopStatement::generateCPPNoAlias(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for (int "; fIndex->generateCPPNoAlias(dst, n);
        *dst << " = 0; ";
        fIndex->generateCPPNoAlias(dst, n);
        *dst << " < " << fSize << "; ";
        fIndex->generateCPPNoAlias(dst, n);
        *dst << "++) {" << endl;
    fCode->generateCPPNoAlias(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TIfStatement::generateCPPNoAlias(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "if ("; fIndex->generateCPPNoAlias(dst, n); *dst << " == 0) {" << endl;
    fCode->generateCPPNoAlias(dst, n+1);
    tab(n, *dst); *dst << "}";
}
