/************************************************************************
 FAUST Architecture File
 Copyright (C) 2021-2022 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <efsw/efsw.h>

#include "cmajor-tools.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/misc.h"

using namespace std;

static bool endWith(const string& str, const string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != string::npos) && (i == (str.length() - suffix.length()));
}

struct HybridEditor {
    
    string fInFilename;
    string fOutFilename;
    int fArgc1;
    const char** fArgv1;
    efsw_watcher fEfsw;
    
    HybridEditor(const string& in_filename,
                 const string& out_filename,
                 int argc1,
                 const char* argv1[])
    :fInFilename(in_filename), fOutFilename(out_filename), fArgc1(argc1), fArgv1(argv1)
    {
        char temp[PATH_MAX + 1];
        char* path = realpath(in_filename.c_str(), temp);
        std::string dir = dirname(path);
        
        fEfsw = efsw_create(false);
        efsw_addwatch(fEfsw, dir.c_str(), watchCallback, false, this);
        efsw_watch(fEfsw);
        
        compilePatch();
        
        cout << "Type 'q' to Quit\n";
        char c;
        while ((c = getchar()) && (c != 'q')) {}
    }
    
    virtual ~HybridEditor()
    {
        efsw_release(fEfsw);
    }
    
    void compilePatch()
    {
        cout << "compilePatch : '" << fInFilename << "' to '" << fOutFilename << "' and '" << fOutFilename + "patch'" << endl;
        // We have a pure Cmajor file or a Faust/Cmajor file, parse it, compile the Faust part to Cmajor, generate the Cmajor result
        faust_cmajor_parser parser;
        if (!parser.parseCmajorFile(fInFilename, fOutFilename, fArgc1, fArgv1)) {
            cerr << "ERROR : file '" << fInFilename << "' cannot be opened or compiled!\n";
            return;
        }
        
        // Generate "cmajorpatch" file
        parser.createCmajorPatch(fOutFilename);
    }
    
    static void watchCallback(efsw_watcher watcher,
                              efsw_watchid watchid,
                              const char* dir,
                              const char* filename,
                              enum efsw_action action,
                              const char* old_filename,
                              void* param)
    {
        HybridEditor* editor = (HybridEditor*)param;
        if (action == EFSW_ADD
            || action == EFSW_DELETE
            || action == EFSW_MODIFIED
            || action == EFSW_MOVED) {
            // Check filename
            if (string(filename) == editor->fInFilename) {
                editor->compilePatch();
            }
        }
    }
    
};

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "Copyright (c) 2021-2022 Grame, version 0.2" << endl;
        cout << "Usage: cmajor-faust-editor [Faust options : any option (e.g. -ftz 1...)] <foo.cmajor> -o <output.cmajor>" << endl;
        exit(-1);
    }
    
    string in_filename;
    string out_filename = "hybrid.cmajor";
    int argc1 = 0;
    const char* argv1[64];
    for (int i = 1; i < argc; i++) {
        if (endWith(string(argv[i]), ".cmajor")) {
            in_filename = argv[i];
            continue;
        } else if (string(argv[i]) == "-o") {
            out_filename = argv[i+1];
            i++;
            continue;
        }
        argv1[argc1++] = argv[i];
    }
    
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    if (endWith(in_filename, "cmajor")) {
        HybridEditor editor(in_filename, out_filename, argc1, argv1);
    } else {
        cout << "ERROR : incorrect file type" << endl;
        exit(-1);
    }
    
    return 0;
}
