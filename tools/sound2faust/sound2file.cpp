/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sndfile.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#ifndef _WIN32
#include <libgen.h>
#endif

#include "faust/misc.h"

using namespace std;

#define BUFFER_SIZE 1024

// g++ -O3 sound2file.cpp -lsndfile -o sound2file

static string RemoveEnding(const string& name)
{
    int match = name.rfind(".");
    return (match != string::npos) ? name.substr(0, match) : name;
}

int main(int argc, char* argv[])
{
	SNDFILE* soundfile;
	SF_INFO	snd_info;
    char* base_name;
    
    const char* output = lopts(argv, "-o", "");
    bool is_double = isopt(argv, "-d");
    bool is_interleaved = isopt(argv, "-i");
    
#ifndef _WIN32
	base_name = basename(argv[1]);
#else
	base_name = new char[_MAX_FNAME];
	_splitpath(argv[1], NULL, NULL, base_name, NULL);
#endif
    if (argc < 2) {
        printf("sound2file <sound> [-d] (for 'double' samples) [-i] -o <file>\n");
        exit(1);
    }
    
    if (isdigit(base_name[0])) {
        printf("soundfile '%s' start with a digit, please rename it\n", base_name);
        exit(0); 
    }
     
    snd_info.format = 0;
    soundfile = sf_open(argv[1], SFM_READ, &snd_info);
    
    if (!soundfile) { 
        printf("soundfile '%s' cannot be opened\n", base_name);
        exit(0); 
    }
    
    std::ostream* dst;
    if (strcmp(output, "") == 0) {
        dst = &cout;
    } else {
        dst = new ofstream(output);
    }
    
    double buffer[BUFFER_SIZE * snd_info.channels];
    string name_aux = RemoveEnding(base_name);
    char sep;
    
    // Generates one interleaved table
    if (is_interleaved) {
        
        if (is_double) {
            *dst << std::setprecision(std::numeric_limits<double>::max_digits10);
            *dst << "double " << name_aux << "_sample(int channel, int index) {" << std::endl;
            *dst << "static const double " << name_aux << "[" << snd_info.channels << " * " << snd_info.frames << "] = ";
        } else {
            *dst << std::setprecision(std::numeric_limits<float>::max_digits10);
            *dst << "float " << name_aux << "_sample(int channel, int index) {" << std::endl;
            *dst << "static const float " << name_aux << "[" << snd_info.channels << " * " << snd_info.frames << "] = ";
        }
        
        int nbf;
        sep = '{';
        do {
            nbf = sf_readf_double(soundfile, buffer, BUFFER_SIZE);
            for (int sample = 0; sample < nbf * snd_info.channels; sample++) {
                *dst << sep << buffer[sample];
                sep = ',';
            }
        } while (nbf == BUFFER_SIZE);
        
        *dst << "};" << std::endl;
        *dst << "return " << name_aux << "[(index % " <<  snd_info.frames << ") * " << snd_info.channels << " + channel];" << std::endl;
        *dst << "};" << std::endl;
        *dst << "int " << name_aux << "_size()" << " { return " << snd_info.frames << "; }" << std::endl;
        *dst << "int " << name_aux << "_channels()" << " { return " << snd_info.channels << "; }" << std::endl;
        
    // Generates several non-interleaved tables
    } else {
        
        if (is_double) {
            *dst << std::setprecision(std::numeric_limits<double>::max_digits10);
            *dst << "static const double " << name_aux << "[" << snd_info.channels << "]" << "[" << snd_info.frames << "] = { ";
        } else {
            *dst << std::setprecision(std::numeric_limits<float>::max_digits10);
            *dst << "static const float " << name_aux << "[" << snd_info.channels << "]" << "[" << snd_info.frames << "] = { ";
        }
        
        int nbf;
        for (int chan = 0; chan < snd_info.channels; chan++) {
            *dst << '{';
            sep = ' ';
            do {
                nbf = sf_readf_double(soundfile, buffer, BUFFER_SIZE);
                for (int frame = 0; frame < nbf; frame++) {
                    *dst << sep << buffer[frame + chan];
                    sep = ',';
                }
            } while (nbf == BUFFER_SIZE);
            *dst << '}';
            if (chan < snd_info.channels-1) *dst << ',';
            sf_seek(soundfile, 0, SEEK_SET);
        }
        
        *dst << "};" << std::endl;
        if (is_double) {
            *dst << "double " << name_aux << "_sample(int channel, int index) { ";
            *dst << "return " << name_aux << "[channel][index]; }" << std::endl;
            *dst << "const double* " << name_aux << "_channel(int channel) { ";
            *dst << "return " << name_aux << "[channel]; }" << std::endl;
        } else {
            *dst << "float " << name_aux << "_sample(int channel, int index) { ";
            *dst << "return " << name_aux << "[channel][index]; }" << std::endl;
            *dst << "const float* " << name_aux << "_channel(int channel) { ";
            *dst << "return " << name_aux << "[channel]; }" << std::endl;
        }
        *dst << "int " << name_aux << "_size()" << " { return " << snd_info.frames << "; }" << std::endl;
        *dst << "int " << name_aux << "_channels()" << " { return " << snd_info.channels << "; }" << std::endl;
    }
        
    dst->flush();
}
