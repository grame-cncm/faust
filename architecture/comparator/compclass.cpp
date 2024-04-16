#include <libgen.h>
#include <sndfile.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "faust/dsp/dsp-tools.h"

// Auto-generated
#include "float.cpp"
#include "fixed.cpp"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

using namespace std;

typedef sf_count_t (* sample_write)(SNDFILE* sndfile, void* buffer, sf_count_t frames);

class comparator {

    private:
        
        int buffersize = 24;
        FAUSTFLOAT** inputs;
        FAUSTFLOAT** FX_outputs;
        FAUSTFLOAT** FL_outputs;
        FAUSTFLOAT** comp;
        dsp* FL;
        dsp* FX;
        int sizechosen;
        float snr;

    public : 
        
        FAUSTFLOAT** createbuffer(int chan, int buffer_size)
        {
            FAUSTFLOAT** buffer = new FAUSTFLOAT*[chan];
            for (int i = 0; i < chan; i++) {
                buffer[i] = new FAUSTFLOAT[buffer_size];
                memset(buffer[i], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            return buffer;
        }

        void deletebuffer(FAUSTFLOAT** buffer, int chan)
        {
            for (int i = 0; i <chan; i++) {
                delete [] buffer[i];
            }
            delete [] buffer;
        }

        comparator(dsp* fl, dsp* fx)
        {
            FL = fl;
            FX = fx; 
            inputs = createbuffer(FL->getNumInputs(), buffersize);
            FL_outputs = createbuffer(FL->getNumOutputs(), buffersize);
            FX_outputs = createbuffer(FX->getNumOutputs(), buffersize);
            comp = nullptr;
        }

        void compare(int size, bool logging, const string& name = "")
        {
            if (comp != nullptr) {
                deletebuffer(comp, FL->getNumOutputs());
            }
            
            ofstream logging_file;
            
            if (logging) {
                string filename = "samples-"+name+".log";
                logging_file.open(filename.c_str());
            }
            
            sizechosen = size;
            int slice = size;

            comp = createbuffer(FL->getNumOutputs(),size);
            
            snr = 0; //signal to noise ratio
            float power_signal = 0;
            float power_noise = 0;
            
            int t = 0;
            do {
                int block_size = min(buffersize, slice);
                FX->compute(block_size, inputs, FX_outputs);
                FL->compute(block_size, inputs, FL_outputs);
                
                for (int chan = 0; chan < FL->getNumOutputs(); ++chan) {
                    FAUSTFLOAT* sub_comp = comp[chan];
                    FAUSTFLOAT* sub_FL_outputs = FL_outputs[chan];
                    FAUSTFLOAT* sub_FX_outputs = FX_outputs[chan];
                    for (int frame = 0; frame < block_size; ++frame) {
                        cout << "FL " << sub_FL_outputs[frame] << " | FX " << sub_FX_outputs[frame] << endl;
                        sub_comp[frame+(t*buffersize)] = sub_FL_outputs[frame] - sub_FX_outputs[frame];
                        
                        if (logging and chan == 0) // we only log one channel
                            logging_file << sub_FL_outputs[frame] << ";" << sub_FX_outputs[frame] << ";" << endl;
                        
                        power_signal += sub_FL_outputs[frame]*sub_FL_outputs[frame];
                        power_noise += sub_comp[frame+(t*buffersize)]*sub_comp[frame+(t*buffersize)];
                    }
                }
                ++t;
                slice = slice - buffersize;
            } while (slice > 0);
            
            snr = log(power_signal/power_noise);
        }
                    
        void display()
        {   
            FAUSTFLOAT totalcomp = 0;
            FAUSTFLOAT compmax = 0;
            
            for (int frame = 0; frame < sizechosen; ++frame) {
                cout << "frame: "<< frame;
                for (int chan = 0; chan< FL->getNumOutputs(); ++chan)  {
                    FAUSTFLOAT* sub_comp = comp[chan];
                    cout << " | Channel " << chan+1 << " :" << sub_comp[frame] << "\t";
                    totalcomp = totalcomp + abs(sub_comp[frame]);
                    compmax = max(compmax,abs(sub_comp[frame]));
                }
                cout << endl;
            }
            cout << "Total Amount : " << totalcomp << endl;
            cout << "Relative error : " << totalcomp/(FL->getNumOutputs()*sizechosen) << endl;
            cout << "Max : " << compmax << endl;
            cout << "SNR : " << snr << endl;
        }

        virtual ~comparator()
        {
            deletebuffer(inputs, FL->getNumInputs());
            deletebuffer(FL_outputs, FL->getNumOutputs());
            deletebuffer(FX_outputs, FX->getNumOutputs());
        }
};

int main(int argc, char* argv[])
{
    // sample rate and buffer size
    int samplerate = 44100;
    int buffersize = 512;
    
    // parsing of options
    int opt;
    
    bool execute = false;
    bool logging = false;
    bool help = false;

    int window_size = 200;
    
    while ((opt = getopt(argc, argv, ":lwhn:")) != -1) {
        switch (opt) {
            case 'l':
                logging = true;
                break;
            case 'w':
                execute = true;
                break;
            case 'h':
                help = true;
                break;
            case 'n':
                window_size = atoi(optarg);
                break;
        }
    }
    
    if (help) {
        cout << "Usage: "
        << argv[0] << " [options]" << endl
        << "Options :"<< endl
        << "\t -w : writes the floating-point and fixed-point outputs to sound files" << endl
        << "\t -l : logs the floating-point and fixed-point samples to a text file" << endl
        << "\t -n : number of samples over which to compute the statistical indicators" << endl
        << "\t -h : displays this help message" << endl;
        return 0;
    }
    
    // init
    fldsp FL;
    fxdsp FX;
    FL.init(samplerate);
    FX.init(samplerate);
    
    string executable_name(argv[0]);
    string filename = executable_name.substr(executable_name.rfind("/")+1);
    
    if (execute) {
        // number of samples to compute for each DSP
        int audio_length = 3;
        int sample_nb = audio_length * samplerate;

        // representation of real numbers
        // double or float, but NO PCM otherwise samples over 1 wrap and distortion ensues
        int subtype_format = 0;
            
        sample_write writer;
        if (sizeof(FAUSTFLOAT) == 4) {
            writer = reinterpret_cast<sample_write>(sf_writef_float);
            subtype_format = SF_FORMAT_FLOAT;
        } else {
            writer = reinterpret_cast<sample_write>(sf_writef_double);
            subtype_format = SF_FORMAT_DOUBLE;
        }
        
        ////////////////////////////////////
        // execute floating-point version //
        ////////////////////////////////////
        char name[256];
        snprintf(name, 256, "%s", ("float-"+filename+".wav").c_str());
        
        /* FAUSTFLOAT** inputs = new FAUSTFLOAT*[FL.getNumInputs()];
         for (int i = 0; i < FL.getNumInputs(); i++) {
            inputs[i] = new FAUSTFLOAT[buffersize];
            memset(inputs[i], 0, sizeof(FAUSTFLOAT) * buffersize);
        }*/
        
        SF_INFO out_info = {
            sample_nb,
            samplerate,
            FL.getNumOutputs(),
            SF_FORMAT_WAV|
            subtype_format|
            SF_ENDIAN_LITTLE,
            0,
            0
        };
        
        SNDFILE* out_sf_fl = sf_open(name, SFM_WRITE, &out_info);
        if (!out_sf_fl) {
            cerr << "ERROR : cannot write output file " << name << endl;
            sf_perror(out_sf_fl);
            exit(1);
        }
        Interleaver ilvFL(buffersize, FL.getNumOutputs(), FL.getNumOutputs());
        
        // compute samples
        int cur_frame = 0;
        do {
            int block_size = min(buffersize, sample_nb - cur_frame);
            FL.compute(block_size, nullptr, ilvFL.inputs());
            ilvFL.interleave();
            writer(out_sf_fl, ilvFL.output(), block_size);
            cur_frame += block_size;
        } while (cur_frame < sample_nb);
        
        sf_close(out_sf_fl);
        
        /////////////////////////////////
        // execute fixed-point version //
        /////////////////////////////////
        snprintf(name, 256, "%s", ("fixed-"+filename+".wav").c_str());
        
        out_info = {
            sample_nb,
            samplerate,
            FX.getNumOutputs(),
            SF_FORMAT_WAV|
            subtype_format|
            SF_ENDIAN_LITTLE,
            0,
            0
        };

        SNDFILE* out_sf_fx = sf_open(name, SFM_WRITE, &out_info);
        if (!out_sf_fx) {
            cerr << "ERROR : cannot write output file " << name << endl;
            sf_perror(out_sf_fx);
            exit(1);
        }
        Interleaver ilvFX(buffersize, FX.getNumOutputs(), FX.getNumOutputs());
        
        // compute samples
        cur_frame = 0;
        do {
            int block_size = min(buffersize, sample_nb - cur_frame);
            FX.compute(block_size, nullptr, ilvFX.inputs());
            ilvFX.interleave();
            writer(out_sf_fx, ilvFX.output(), block_size);
            cur_frame += block_size;
        } while (cur_frame < sample_nb);
        
        sf_close(out_sf_fx);
    }
    
    FL.init(48000);
    FX.init(48000);
    
    comparator comp((dsp*)&FL, (dsp*)&FX);
    comp.compare(window_size, logging, filename);
    comp.display();
}
