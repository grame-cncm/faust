
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

using namespace std;

#define BUFFER_SIZE 128

// g++ -O3 faust-waveform-converter.cpp -lsndfile -o faust-waveform-converter

static string RemoveEnding(const string& name)
{
    int match = name.rfind(".");
    return (match != string::npos) ? name.substr(0, match) : name;
}

int main(int argc, char *argv[])
{
	SNDFILE* soundfile;
	SF_INFO	snd_info;
    
    snd_info.format = 0;
    soundfile = sf_open(argv[1], SFM_READ, &snd_info);
    if (soundfile == NULL) { 
        printf("soundfile '%s' cannot be opened\n", argv[1]);
        sf_perror(soundfile); 
        exit(0); 
    }
    std::ostream* dst = &cout;
    float buffer[BUFFER_SIZE * snd_info.channels] ;
     
    *dst << RemoveEnding(argv[1]) << " = {";
    
    int nbf;
    do {
        nbf = sf_readf_float(soundfile, buffer, BUFFER_SIZE);
        for (int i = 0; i < nbf; i++) {
            *dst << buffer[i];
            if (i < nbf - 1) {
                *dst << ", ";
            }
        }
    } while (nbf == BUFFER_SIZE);
  
    *dst << "};" << std::endl;
}
