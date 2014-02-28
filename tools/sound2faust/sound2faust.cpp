
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
#include <libgen.h>

#include "../../architecture/faust/misc.h"

using namespace std;

#define BUFFER_SIZE 128

// g++ -O3 sound2faust.cpp -lsndfile -o sound2faust

static string RemoveEnding(const string& name)
{
    int match = name.rfind(".");
    return (match != string::npos) ? name.substr(0, match) : name;
}

int main(int argc, char *argv[])
{
	SNDFILE* soundfile;
	SF_INFO	snd_info;
    
    const char* base_name = basename(argv[1]);
    
    if (argc < 2) {
        printf("sound2faust <soundfile>  -d (deinterleave channels : default off) -o <file>\n");
        exit(1);
    }
    
    const char* output = lopts(argv, "-o", "");
    bool deinterleave = isopt(argv, "-d");
    
    snd_info.format = 0;
    soundfile = sf_open(argv[1], SFM_READ, &snd_info);
    if (soundfile == NULL) { 
        printf("soundfile '%s' cannot be opened\n", base_name);
        sf_perror(soundfile); 
        exit(0); 
    }

    std::ostream* dst;
    if (strcmp(output, "") == 0) {
        dst = &cout;
    } else {
        dst = new ofstream(output);
    }
    
    float buffer[BUFFER_SIZE * snd_info.channels];
    
    if (!deinterleave) {
     
        // Generates one interleaved waveform
        *dst << RemoveEnding(base_name) << " = waveform";
        int nbf;
        char sep = '{';
        do {
            nbf = sf_readf_float(soundfile, buffer, BUFFER_SIZE);
            for (int i = 0; i < nbf * snd_info.channels; i++) {
                *dst << sep << buffer[i];
                sep = ',';
            }
            
        } while (nbf == BUFFER_SIZE);
       *dst << "};" << std::endl;
       
    } else {
        
        // Generates separated mono waveforms
        for (int chan = 0; chan < snd_info.channels; chan++) {
            sf_seek(soundfile, 0, SEEK_SET);
            *dst << RemoveEnding(base_name) << chan << " = waveform";
            int nbf;
            char sep = '{';
            do {
                nbf = sf_readf_float(soundfile, buffer, BUFFER_SIZE);
                for (int i = 0; i < nbf * snd_info.channels; i++) {
                    if (i % snd_info.channels == chan) {
                        *dst << sep << buffer[i];
                        sep = ',';
                    }
                }
                
            } while (nbf == BUFFER_SIZE);
            *dst << "};" << std::endl;
        }
        
        // And generates one multi-channels waveform
        *dst << RemoveEnding(base_name) << " = ";
        
        char sep = '(';
        for (int chan = 0; chan < snd_info.channels; chan++) {
            *dst << sep << RemoveEnding(base_name) << chan;
             sep = ',';
        }
        
        *dst << "):";
        
        sep = '(';
        for (int chan = 0; chan < snd_info.channels; chan++) {
            *dst << sep << "(!,_)";
             sep = ',';
        }
        
        *dst << ");" << std::endl;
    }
    
    dst->flush();
}
