/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN sndfile.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2021 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************
 ************************************************************************/

#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sndfile.h>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <iostream>

#include "faust/dsp/dsp.h"
#include "faust/gui/console.h"
#include "faust/gui/FUI.h"
#include "faust/gui/ControlSequenceUI.h"
#include "faust/dsp/dsp-tools.h"
#include "faust/misc.h"

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

typedef sf_count_t (* sample_read)(SNDFILE* sndfile, void* buffer, sf_count_t frames);
typedef sf_count_t (* sample_write)(SNDFILE* sndfile, void* buffer, sf_count_t frames);

using namespace std;

// loptrm : scan command-line arguments and remove and return long int value when found
static long loptrm(int* argcP, char* argv[], const char* longname, const char* shortname, long def)
{
    int argc = *argcP;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            int optval = atoi(argv[i]);
            for (int j = i-1; j < argc-2; j++) {  // make it go away for sake of "faust/gui/console.h"
                argv[j] = argv[j+2];
            }
            *argcP -= 2;
            return optval;
        }
    }
    return def;
}

mydsp DSP;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#define kBufferSize  64
#define kSampleRate  44100

int main(int argc_aux, char* argv_aux[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    snprintf(name, 256, "%s", basename(argv_aux[0]));
    snprintf(rcfilename, 256, "%s/.%src", home, name);
    string cfilename;
    
    int argc = 0;
    char* argv[64];
    for (int i = 0; i < argc_aux; i++) {
        if (string(argv_aux[i]) == "-ct") {
            cfilename = argv_aux[i+1];
            i++;
            continue;
        }
        argv[argc++] = argv_aux[i];
    }
    
    // Recall state before handling commands
    FUI finterface;
    DSP.buildUserInterface(&finterface);
    
    CMDUI* interface = new CMDUI(argc, argv, true);
    DSP.buildUserInterface(interface);
    
    interface->process_command(FILE_MODE);
    interface->printhelp_command(FILE_MODE);
    
    sample_read reader;
    sample_write writer;
    if (sizeof(FAUSTFLOAT) == 4) {
        reader = reinterpret_cast<sample_read>(sf_readf_float);
        writer = reinterpret_cast<sample_write>(sf_writef_float);
    } else {
        reader = reinterpret_cast<sample_read>(sf_readf_double);
        writer = reinterpret_cast<sample_write>(sf_writef_double);
    }
    
    bool is_rc = loptrm(&argc, argv, "--rcfile", "-rc", 0);
    
    int buffer_size = loptrm(&argc, argv, "--buffer-size", "-bs", kBufferSize);
    
    if (FILE_MODE == INPUT_OUTPUT_FILE) {
        
        int num_samples = loptrm(&argc, argv, "--continue", "-c", 0);
        
        SF_INFO in_info;
        memset(&in_info, 0, sizeof(in_info));
        SNDFILE* in_sf = sf_open(interface->input_file(), SFM_READ, &in_info);
        if (!in_sf) {
            cerr << "ERROR : input file not found" << endl;
            sf_perror(in_sf);
            exit(1);
        }
        
        SF_INFO out_info = in_info;
        out_info.format = in_info.format;
        out_info.channels = DSP.getNumOutputs();
        SNDFILE* out_sf = sf_open(interface->output_file(), SFM_WRITE, &out_info);
        if (!out_sf) {
            cerr << "ERROR : cannot write output file" << endl;
            sf_perror(out_sf);
            exit(1);
        }
        
        // Handling of the file containing sequence of time-stamped OSC messages
        ControlSequenceUI sequenceUI(OSCSequenceReader::read(cfilename, in_info.samplerate));
        DSP.buildUserInterface(&sequenceUI);
        
        // Init DSP with SR
        DSP.init(in_info.samplerate);
        
        // Possibly restore saved state
        if (is_rc) {
            finterface.recallState(rcfilename);
        }
        
        // Modify the UI values according to the command line options, after init
        interface->process_init();
        
        // Create deinterleaver and interleaver
        Deinterleaver dilv(buffer_size, in_info.channels, DSP.getNumInputs());
        Interleaver ilv(buffer_size, DSP.getNumOutputs(), DSP.getNumOutputs());
        
        // Process all samples
        int nbf;
        uint64_t cur_frame = 0;
        do {
            // Read samples
            nbf = reader(in_sf, dilv.input(), buffer_size);
            dilv.deinterleave();
            // Update controllers
            sequenceUI.process(cur_frame, cur_frame + nbf);
            cur_frame += nbf;
            // Compute DSP
            DSP.compute(nbf, dilv.outputs(), ilv.inputs());
            // Write samples
            ilv.interleave();
            writer(out_sf, ilv.output(), nbf);
        } while (nbf == buffer_size);
        
        sf_close(in_sf);
        
        // Compute tail, if any
        if (num_samples > 0) {
            FAUSTFLOAT* input = (FAUSTFLOAT*)calloc(num_samples * DSP.getNumInputs(), sizeof(FAUSTFLOAT));
            FAUSTFLOAT* inputs[1] = { input };
            Interleaver ilv(num_samples, DSP.getNumOutputs(), DSP.getNumOutputs());
            DSP.compute(num_samples, inputs, ilv.inputs());
            ilv.interleave();
            writer(out_sf, ilv.output(), num_samples);
        }
        
        sf_close(out_sf);
        
        // Possibly save state
        if (is_rc) {
            finterface.saveState(rcfilename);
        }
        
    } else {
        
        int sample_rate = loptrm(&argc, argv, "--sample-rate", "-sr", kSampleRate);
        
        // Handling of the file containing sequence of time-stamped OSC messages
        ControlSequenceUI sequenceUI(OSCSequenceReader::read(cfilename, sample_rate));
        uint64_t begin, end;
        sequenceUI.getRange(begin, end);
        DSP.buildUserInterface(&sequenceUI);
        
        int num_samples = loptrm(&argc, argv, "--samples", "-s", ((end > 0) ? (end + kSampleRate) : kSampleRate * 5));
        int bit_depth = loptrm(&argc, argv, "--bith-depth (16|24|32)", "-bd", 16);
        int bd = (bit_depth == 16) ? SF_FORMAT_PCM_16 : ((bit_depth == 24) ? SF_FORMAT_PCM_24 : SF_FORMAT_PCM_32);
        
        SF_INFO out_info = { num_samples, sample_rate, DSP.getNumOutputs(), SF_FORMAT_WAV|bd|SF_ENDIAN_LITTLE, 0, 0};
        SNDFILE* out_sf = sf_open(interface->input_file(), SFM_WRITE, &out_info);
        if (!out_sf) {
            cerr << "ERROR : cannot write output file" << endl;
            sf_perror(out_sf);
            exit(1);
        }
        
        // Init DSP with SR
        DSP.init(sample_rate);
        
        // Possibly restore saved state
        if (is_rc) {
            finterface.recallState(rcfilename);
        }
        
        // Modify the UI values according to the command line options, after init
        interface->process_init();
        
        // Create interleaver
        Interleaver ilv(buffer_size, DSP.getNumOutputs(), DSP.getNumOutputs());
        
        // Process all samples
        uint64_t cur_frame = 0;
        do {
            int nbf = std::min(int(num_samples - cur_frame), int(buffer_size));
            // Update controllers
            sequenceUI.process(cur_frame, cur_frame + nbf);
            // Compute DSP
            DSP.compute(nbf, nullptr, ilv.inputs());
            // Write samples
            ilv.interleave();
            writer(out_sf, ilv.output(), nbf);
            cur_frame += nbf;
        } while (cur_frame < num_samples);
        
        sf_close(out_sf);
        
        // Possibly save state
        if (is_rc) {
            finterface.saveState(rcfilename);
        }
    }
}

/******************* END sndfile.cpp ****************/
