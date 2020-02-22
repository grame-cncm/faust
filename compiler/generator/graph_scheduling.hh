#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

#include "ppsig.hh"
#include "signals.hh"

using namespace std;

struct Scheduling {
    // Dictionnary  fDic;
    vector<Tree> fInitLevel;
    vector<Tree> fBlockLevel;
    vector<Tree> fExecLevel;

    void print(ostream& f)
    {
        f << "// INIT SCHEDULING " << endl;
        for (Tree i : fInitLevel) {
            f << i << ":\t" << ppsig(i) << endl;
        }
        f << endl;

        f << "// CONTROL SCHEDULING " << endl;
        for (Tree i : fBlockLevel) {
            f << i << ":\t" << ppsig(i) << endl;
        }
        f << endl;

        f << "// SCALAR SCHEDULING " << endl;
        for (Tree i : fExecLevel) {
            f << i << ":\t" << ppsig(i) << endl;
        }
        f << endl;
    }

    void print(const string& filename)
    {
        ofstream f;
        f.open(filename);
        this->print(f);
        f.close();
    }

    friend ostream& operator<<(ostream& file, Scheduling& S)
    {
        S.print(file);
        return file;
    }
};
