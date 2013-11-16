
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

// g++ -O3 faust-sound-converter.cpp -lsndfile -o faust-sound-converter

static string RemoveEnding(const string& name)
{
    int match = name.rfind(".");
    return (match != string::npos) ? name.substr(0, match) : name;
}

int main(int argc, char *argv[])
{
	SNDFILE* soundfile;
	SF_INFO	snd_info;
    
    if (argc < 2) {
        printf("faust-sound-converter <soundfile> \n");
        exit(0);
    }

    snd_info.format = 0;
	soundfile = sf_open(argv[1], SFM_READ, &snd_info);
	if (soundfile == NULL) { 
        printf("soundfile '%s' cannot be opened\n", argv[1]);
        sf_perror(soundfile); 
        exit(0); 
    }
    
    string new_name = RemoveEnding(argv[1]);
    string out_name = new_name + ".h";
    float buffer[BUFFER_SIZE * snd_info.channels] ;
    std::ofstream dst;
    dst.open(out_name.c_str());
  
    printf("Sound file channels = channels %d\n", (int)snd_info.channels);
    printf("Sound file length = %d\n", (int)snd_info.frames);
    printf("Produced header = %s\n", out_name.c_str());
    
    dst << "int soundFileSize_" << new_name << "() { return " << (snd_info.frames + 1) << "; }" << std::endl;
    dst << "float readSoundFile_" << new_name << "(int index) { " << std::endl;
    dst << "static float soundFile["<< (snd_info.frames + 1) << "] = { " << std::endl;
    
    int nbf;
    do {
        nbf = sf_readf_float(soundfile, buffer, BUFFER_SIZE);
        for (int i = 0; i < nbf; i++) {
            dst << buffer[i] << ", ";
        }
        dst << std::endl;
    } while (nbf == BUFFER_SIZE);
    
    dst << "0. };" << std::endl;
    dst << "return soundFile[index];" << std::endl;
    dst << "};" << std::endl;
    
    dst.close();
}
