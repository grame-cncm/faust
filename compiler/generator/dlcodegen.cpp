#include "dlcodegen.hh"
#include "Text.hh"

using namespace std;

string DlCodeGen::globalDeclare() const
{
    // we store State[0] = fVec0[1], State[1] = fVec0[2], State[2] = fVec0[3], ...
    // or State = fRetard[1]
    if (fDlMaxDelay > 1) {
        string s = fDlType + "\t" + fDlName + "State[" + T(fDlMaxDelay) + "];\n";
        return s;
    } else {
        string s = fDlType + "\t" + fDlName + "State;\n";
        return s;
    }
}

string DlCodeGen::globalInit() const
{
    // we store State[0] = fVec0[1], State[1] = fVec0[2], State[2] = fVec0[3], ...
    // or State = fRetard[1]
    if (fDlMaxDelay > 1) {
        string s = "for (int j = 0; j < " + T(fDlMaxDelay) + "; j++) { ";
        s += "    " + fDlName + "State[j] = 0; ";
        s += "}\n";
        return s;
    } else {
        string s = fDlName + "State = 0;\n";
        return s;
    }
}

string DlCodeGen::localDeclare() const
{
    if (fMono) {
        string s = fDlType + "\t" + fDlName + ";  // local copy of the delay line";
        return s;

    } else if (fDlMaxDelay == 1) {
        string s = fDlType + "\t" + fDlName + "[2];  // local copy of the delay line";
        return s;
    } else if (fDlMaxDelay == 2) {
        string s = fDlType + "\t" + fDlName + "[3];  // local copy of the delay line";
        return s;
    } else if (fDlMaxDelay > 2) {
        string s = fDlType + "\t" + fDlName + "cache[" + T(fBlockSize) + " + " + T(fDlMaxDelay) +
                        "];  // local copy of the delay line";
        return s;
    } else {
        return "ERROR1";
    }
}

string DlCodeGen::PointerSetup() const
{
    if (fDlMaxDelay > 2) {
        string s = fDlType + "*\t" + fDlName + " = " + fDlName + "cache + " + T(fBlockSize) +
                        " - 1;  // pointer to the delay line in the local copy";
        return s;
    } else {
        return "";
    }
}

string DlCodeGen::copyGlobalToLocal() const
{
    if (fDlMaxDelay > 2) {
        string s = "for (int j = 0; j < " + T(fDlMaxDelay) + "; j++) { ";
        s += fDlName + "[j+1] = " + fDlName + "State[j];";
        s += " }\n";
        return s;
    } else if (fDlMaxDelay == 2) {
        string s = fDlName + "[1] = " + fDlName + "State[0] ; " + fDlName + "[2] = " + fDlName + "State[1];\n";
        return s;
    } else if (fMono) {
        string s = fDlName + " = " + fDlName + "State;\n";
        return s;
    } else {
        string s = fDlName + "[1] = " + fDlName + "State;";
        return s;
    }
}

string DlCodeGen::copyLocalToGlobal() const
{
    if (fDlMaxDelay > 2) {
        string s = "for (int j = 0; j < " + T(fDlMaxDelay) + "; j++) { ";
        s += fDlName + "State[j] = " + fDlName + "[j+1];";
        s += " }\n";
        return s;
    } else if (fDlMaxDelay == 2) {
        string s = fDlName + "State[0] = " + fDlName + "[1]; " + fDlName + "State[1] = " + fDlName + "[2];\n";
        return s;
    } else if (fMono) {
        string s = fDlName + "State = " + fDlName + ";\n";
        return s;
    } else {
        string s = fDlName + "State = " + fDlName + "[1];\n";
        return s;
    }
}

string DlCodeGen::advance() const
{
    if (fMono) {
        return "// nothing to do for mono";
    } else if (fDlMaxDelay > 2) {
        string s = "--" + fDlName + ";";
        return s;
    }
    if (fDlMaxDelay == 2) {
        string s = fDlName + "[2] = " + fDlName + "[1]; " + fDlName + "[1] = " + fDlName + "[0];";
        return s;
    } else {
        string s = fDlName + "[1] = " + fDlName + "[0];";
        return s;
    }
}

string DlCodeGen::write(const string& exp) const
{
    if (fMono) {
        string s = fDlName + " = " + exp + ";\n";
        return s;
    } else {
        string s = fDlName + "[0] = " + exp + ";\n";
        return s;
    }
}

string DlCodeGen::read(const string& index) const
{
    if (fMono) {
        return fDlName;
    } else {
        string s = fDlName + "[" + index + "]";
        return s;
    }
}
