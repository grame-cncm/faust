
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

int main(int argc, char *argv[])
{
	SNDFILE* soundfile;
	SF_INFO	snd_info;
    char* base_name;
    
    const char* output = lopts(argv, "-o", "");
    bool is_double = isopt(argv, "-d");
    
#ifndef _WIN32
	base_name = basename(argv[1]);
#else
	base_name = new char[_MAX_FNAME];
	_splitpath(argv[1], NULL, NULL, base_name, NULL);
#endif
    if (argc < 2) {
        printf("sound2file <sound> -d (for 'double' samples) -o <file>\n");
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
    
    *dst << "#define FAUSTFLOAT " << ((is_double) ? "double" : "float") << std::endl;

    // Generates one interleaved table
    *dst << "FAUSTFLOAT " << name_aux << "_sample(int channel, int index) {" << std::endl;
    *dst << "static FAUSTFLOAT " << name_aux << "[" << snd_info.channels << " * " << snd_info.frames << "] = ";
    int nbf;
    sep = '{';
    do {
        nbf = sf_readf_double(soundfile, buffer, BUFFER_SIZE);
        for (int i = 0; i < nbf * snd_info.channels; i++) {
            *dst << sep << buffer[i];
            sep = ',';
        }
        
    } while (nbf == BUFFER_SIZE);
    *dst << "};" << std::endl;
    *dst << "return " << name_aux << "[(index % " <<  snd_info.frames << ") * " << snd_info.channels << " + channel];" << std::endl;
    *dst << "};" << std::endl;
    *dst << "int " << name_aux << "_size()" << " {return " << snd_info.frames << ";}" << std::endl;
    *dst << "int " << name_aux << "_channels()" << " {return " << snd_info.channels << ";}" << std::endl;
        
    dst->flush();
}
