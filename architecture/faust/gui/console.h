/************************** BEGIN console.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/


#ifndef __faustconsole__
#define __faustconsole__

#include <stack>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <atomic>
#include <stdio.h>

#include "faust/gui/GUI.h"

/******************************************************************************
 *******************************************************************************
 
 USER INTERFACE
 
 *******************************************************************************
 *******************************************************************************/

#define NO_FILE             0
#define OUTPUT_FILE         1
#define INPUT_OUTPUT_FILE   2

class CMDUI : public UI
{
    private:
    
        std::thread* fThread;
        std::atomic<bool> fRun;
    
        struct param {
            FAUSTFLOAT* fZone; FAUSTFLOAT fMin; FAUSTFLOAT fMax;
            param(FAUSTFLOAT* z, FAUSTFLOAT init, FAUSTFLOAT a, FAUSTFLOAT b) : fZone(z), fMin(a), fMax(b) { *z = init; }
        };
    
        int                           fArgc;
        char**                        fArgv;
        std::vector<char*>            fFiles;
        std::stack<std::string>       fPrefix;
        std::map<std::string, param>  fKeyParam;
        bool                          fIgnoreParam;
    
        void openAnyBox(const char* label)
        {
            std::string prefix;
            
            if (label && label[0]) {
                prefix = fPrefix.top() + "-" + label;
            } else {
                prefix = fPrefix.top();
            }
            fPrefix.push(prefix);
        }
    
        std::string simplify(const std::string& src)
        {
            int i = 0;
            int level = 0;
            std::string dst;
            
            while (src[i]) {
                
                switch (level) {
                        
                    case 0 :
                    case 1 :
                    case 2 :
                        // Skip the begin of the label "--foo-" until 3 '-' have been read
                        if (src[i] == '-') { level++; }
                        break;
                        
                    case 3 :
                        // copy the content, but skip non alphanum and content in parenthesis
                        switch (src[i]) {
                            case '(' :
                            case '[' :
                                level++;
                                break;
                            case '-' :
                                dst += '-';
                                break;
                            default :
                                if (isalnum(src[i])) {
                                    dst+= tolower(src[i]);
                                }
                        }
                        break;
                        
                    default :
                        // here we are inside parenthesis and we skip the content until we are back to level 3
                        switch (src[i]) {
                            case '(' :
                            case '[' :
                                level++;
                                break;
                            case ')' :
                            case ']' :
                                level--;
                                break;
                            default :
                                break;
                        }
                }
                i++;
            }
            return dst;
        }
    
    public:
    
        CMDUI(int argc, char* argv[], bool ignore_param = false)
        : UI(), fThread(nullptr), fRun(true),
        fArgc(argc), fArgv(argv),
        fIgnoreParam(ignore_param)
        {
            fPrefix.push("-");
        }
    
        virtual ~CMDUI() { delete fThread; }
    
        // Can be used as public method
        void addOption(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            std::string fullname = "-" + simplify(fPrefix.top() + "-" + label);
            fKeyParam.insert(make_pair(fullname, param(zone, init, min, max)));
        }
    
        virtual void openTabBox(const char* label) { openAnyBox(label); }
        virtual void openHorizontalBox(const char* label) { openAnyBox(label); }
        virtual void openVerticalBox(const char* label) { openAnyBox(label); }
        virtual void closeBox() { fPrefix.pop(); }
    
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addOption(label, zone, 0, 0, 1);
        }
    
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addOption(label, zone, 0, 0, 1);
        }
    
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addOption(label, zone, init, min, max);
        }
    
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addOption(label, zone, init, min, max);
        }
    
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addOption(label, zone, init, min, max);
        }
    
        // -- passive widgets
    
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
        static void update_gui(CMDUI* ui)
        {
            while (ui->fRun) {
                usleep(40 * 1000); // 25Hz
                GUI::updateAllGuis();
            }
        }
    
        virtual bool run()
        {
            fThread = new std::thread(update_gui, this);
            std::cout << "Type 'q' to quit\n";
            char c;
            while ((c = getchar()) && (c != 'q')) {
                usleep(100 * 1000); 
            }
            fRun = false;
            fThread->join();
            return true;
        }
    
        void printhelp_command(int file_mode = NO_FILE)
        {
            if ((file_mode == OUTPUT_FILE && files() < 1)
                || (file_mode == INPUT_OUTPUT_FILE && files() < 2)) {
                std::cout << fArgv[0] << " ";
                for (const auto& i : fKeyParam) {
                    std::cout << "[ " << i.first << " " << i.second.fMin << ".." << i.second.fMax <<" ] ";
                }
                if (file_mode == INPUT_OUTPUT_FILE) {
                    std::cout << "infile outfile\n";
                } else if (file_mode == OUTPUT_FILE) {
                    std::cout << "outfile\n";
                }
                exit(1);
            }
        }
    
        void printhelp_init()
        {
            std::cout << fArgv[0] << " option list : ";
            for (const auto& i : fKeyParam) {
                std::cout << "[ " << i.first << " " << i.second.fMin << ".." << i.second.fMax <<" ] ";
            }
            std::cout << std::endl;
            exit(1);
        }
    
        void process_command(int file_mode = NO_FILE)
        {
            std::map<std::string, param>::iterator p;
            for (int i = 1; i < fArgc; i++) {
                if (fArgv[i][0] == '-') {
                    if ((strcmp(fArgv[i], "-help") == 0) || (strcmp(fArgv[i], "-h") == 0)) {
                        printhelp_command(file_mode);
                    }
                    p = fKeyParam.find(fArgv[i]);
                    if (p == fKeyParam.end()) {
                        if (!fIgnoreParam) {
                            std::cout << fArgv[0] << " : unrecognized option " << fArgv[i] << "\n";
                            printhelp_command(file_mode);
                        } else {
                            // Argument with a value, so also ignore the value
                            if ((i+1 < fArgc) && (fArgv[i+1][0] != '-')) i++;
                        }
                    } else {
                        char* end;
                        *(p->second.fZone) = FAUSTFLOAT(std::strtod(fArgv[i+1], &end));
                        i++;
                    }
                } else {
                    fFiles.push_back(fArgv[i]);
                }
            }
        }
    
        void process_init()
        {
            std::map<std::string, param>::iterator p;
            for (int i = 1; i < fArgc; i++) {
                if (fArgv[i][0] == '-') {
                    if ((strcmp(fArgv[i], "-help") == 0)
                        || (strcmp(fArgv[i], "-h") == 0)
                        || (strcmp(fArgv[i], "--help") == 0)) {
                        printhelp_init();
                    }
                    p = fKeyParam.find(fArgv[i]);
                    if (p == fKeyParam.end()) {
                        std::cout << fArgv[0] << " : unrecognized option " << fArgv[i] << "\n";
                        printhelp_init();
                    }
                    char* end;
                    *(p->second.fZone) = FAUSTFLOAT(std::strtod(fArgv[i+1], &end));
                    i++;
                }
            }
        }
    
        // check if exist and process one single parameter
        void process_one_init(const char* param1)
        {
            for (int i = 1; i < fArgc; i++) {
                if (fArgv[i][0] == '-') {
                    std::map<std::string, param>::iterator p = fKeyParam.find(fArgv[i]);
                    if ((p != fKeyParam.end()) && (strcmp(fArgv[i], param1) == 0)) {
                        char* end;
                        *(p->second.fZone) = FAUSTFLOAT(std::strtod(fArgv[i+1], &end));
                        break;
                    }
                    i++;
                }
            }
        }
    
        unsigned long files() { return fFiles.size(); }
        char* file(int n) { return fFiles[n]; }
    
        char* input_file() { return fFiles[0]; }
        char* output_file() { return fFiles[1]; }
    
};

#endif

/**************************  END  console.h **************************/
