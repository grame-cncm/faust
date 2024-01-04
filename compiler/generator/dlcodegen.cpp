/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2023 INRIA
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

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

string DlCodeGen::pointerSetup() const
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
