/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN svgplot.cpp ****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2023 GRAME, Centre National de Creation Musicale
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

#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

#include "faust/gui/UI.h"
#include "faust/audio/channels.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/console.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/misc.h"

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

#include "plot.h"
#include "heatmap.h"

using namespace std;

// A class to count Probe
struct ProbeCounter : public GenericUI
{

    map<string, FAUSTFLOAT*> fProbeMap;
     
    void displayProbeHeaders()
    {
        int c = 0;
        if (fProbeMap.size() > 0) {
            printf(",\t");
            for (const auto& it : fProbeMap) {
                if (c > 0) {
                    printf(",\t");
                    printf("Probe %d", c + 1);
                }
                c++;
            }
        }
    }
    
    int getNumProbes()
    {
        return fProbeMap.size();
    }

    void displayProbe(signalsmith::plot::Plot2D &plot, signalsmith::plot::Line2D &probe, int frame, int chan, float& value)
    {
        if (fProbeMap.size() > 0) {
            for (int c = 0; c < fProbeMap.size(); c++) {
                for (const auto& it : fProbeMap) {
                    if (c == chan) {
                        probe.add(frame, (*it.second));
                        value = (*it.second);
                    }
                    c++;
                }
            }
        }
    }

    void declare(FAUSTFLOAT* zone,const char* key,const char* val)
    {
        if (strcmp(key,"probe") == 0) {
            fProbeMap[std::string(val)]=zone;
        }
    }
    
};

// The main SVG and HTML files creation class
class SVGPlot {

    private:
        
        // DSP
        FAUSTFLOAT** fDSPInputs;
        FAUSTFLOAT** fDSPOutputs;
        dsp* fDSP;
    
        // args
        FAUSTFLOAT fCountSamples;
        FAUSTFLOAT fSampleRate;
        FAUSTFLOAT fBufferSize;
        FAUSTFLOAT fStartSample;
        bool fSplit;
    
        // global plot
        signalsmith::plot::Plot2D fPlot;
        // plot for probes in split mode
        signalsmith::plot::Plot2D fSplot;
        // plot for lines in split mode
        signalsmith::plot::Plot2D fStplot;
    
        // Function to create buffers
        FAUSTFLOAT** createbuffer(int chan, int buffer_size)
        {
            FAUSTFLOAT** buffer = new FAUSTFLOAT*[chan];
            for (int i = 0; i < chan; i++) {
                buffer[i] = new FAUSTFLOAT[buffer_size];
                memset(buffer[i], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            return buffer;
        }
        
        // Function to delete a buffer
        void deletebuffer (FAUSTFLOAT** buffer, int chan)
        {
            for (int i = 0; i <chan; i++) {
                delete [] buffer[i];
            }
            delete [] buffer;
        }
    
        void generateHTML(int channels, int num_probes, bool split)
        {
            ofstream file("mydsp.html"); // Create a file named "output.html"
            if (file.is_open()) {
                file << "<html>\n";
                file << "<head>\n";
                file << "<title>SVG Gallery</title>\n";
                file << "</head>\n";
                file << "<body>\n";
                file << "<img src=mydsp.svg>\n";
                if (split) {
                    for (int i = 0; i < channels; i++) {
                        file << "<img src=" << "mydsp_Channel" + std::to_string(i+1) << ".svg>\n";
                    }
                    for (int i = 0; i < num_probes; i++) {
                        file << "<img src=" << "mydsp_Probe" + std::to_string(i+1) << ".svg>\n";
                    }
                }
                file << "</body>\n";
                file << "</html>\n";
                file.close();
                
                cout << "mysvg.html;" << endl;
            } else {
                cerr << "Failed to create the SVG Gallery!" << endl;
            }
        }

    public:
    
        // Constructor
        SVGPlot(dsp* dsp,
                FAUSTFLOAT sample_rate,
                FAUSTFLOAT nb_samples,
                FAUSTFLOAT buffer_size,
                FAUSTFLOAT start_at_sample,
                FAUSTFLOAT split)
        {   
            // Args
            fDSP = dsp;
            fCountSamples = nb_samples;
            fSampleRate = sample_rate;
            fBufferSize = buffer_size;
            fSplit = split;
            fStartSample = start_at_sample;
            
            // Create the buffers
            fDSPInputs = createbuffer(fDSP->getNumInputs(), fCountSamples);
            fDSPOutputs = createbuffer(fDSP->getNumOutputs(), fCountSamples);
        }
    
        virtual ~SVGPlot()
        {
            deletebuffer(fDSPInputs, fDSP->getNumInputs());
            deletebuffer(fDSPOutputs, fDSP->getNumOutputs());
        }

        void exec()
        {
            // Custom UI functions
            ProbeCounter probe_counter;
            fDSP->buildUserInterface(&probe_counter);
        
            // Init position for max and min
            FAUSTFLOAT max = fDSPOutputs[0][0];
            FAUSTFLOAT min = fDSPOutputs[0][0];
                        
            // Init signal processor and the user interface values
            fDSP->init(fSampleRate);

            // Create the graph legend
            auto& legend = fPlot.legend(0, -1);
        
            // Compute
            fDSP->compute(fCountSamples, fDSPInputs, fDSPOutputs);

            // Go through the different channels
            for (int chan = 0; chan< fDSP->getNumOutputs(); ++chan) {
                // reset for straight line and no dotted line
                fPlot.styleCounter.dash = 0;
                // create a line for the actual channel
                auto& line = fPlot.line();
                // temporary line
                auto& sline = fStplot.line();
                auto& slegend = fStplot.legend(0, -1);
                // fixed Index colour position similar to channel
                line.styleIndex.colour = chan;
                for (int frame = fStartSample; frame < fCountSamples; ++frame) {
                    
                    FAUSTFLOAT* sub_outputs = fDSPOutputs[chan];
                    
                    // write points in line
                    line.add(frame, sub_outputs[frame]);
                
                    // check for max and min in order to create proportional axes
                    max = std::max(max, sub_outputs[frame]);
                    min = std::min(min, sub_outputs[frame]);
                     
                    sline.add(frame, sub_outputs[frame]);
                    if (fSplit) {
                        //probe_counter.returnProbe(fSplot, spr:wobe, curpos, num_probes, valuepro);
                    }
                }
                // add legend name
                legend.line(line, "Channel " + std::to_string(chan+1));
                if (fSplit) {
                    fStplot.y.blank(1);
                    fStplot.x.blank(1);
                    fStplot.y.blankLabels(1);
                    fStplot.x.blankLabels(1);
                    
                    slegend.line(sline,"Channel " + std::to_string(chan+1));
                    
                    fStplot.x.linear(fStartSample, fCountSamples).major(fStartSample).minor(fCountSamples).label("Samples");
	                fStplot.y.minors(min, max).label("Values");
                    fStplot.y.majors(0);
                
                    // create the svg file
                    fStplot.write("mydsp_Channel" + std::to_string(chan + 1) + ".svg");
                    // auto& sprobe = fSplot.fill();
                    cout << "mydsp_Channel" + std::to_string(chan+1) + ".svg;" << endl;
                
                    sline.toFrame(0);
                    sline.clearFrames();
                }
            }

            // if probe metadata in the dsp code
            if (probe_counter.getNumProbes() > 0) {
                for (int num_probes = 0; num_probes < probe_counter.getNumProbes(); ++num_probes) {
                    float minpro = 0.0;
                    float maxpro = 0.0;
                    float valuepro = 0.0;
                    auto& slegend = fSplot.legend(0, -1);
                    fDSP->init(fSampleRate);
                    // probegraph_init
                    // reset for dotted line and no straight line
                    fPlot.styleCounter.dash = 5;
                    // create a line
                    auto& probe = fPlot.line();
                    // fixed Index colour position similar to probe number
                    probe.styleIndex.colour = num_probes;

                    // temporary probe
                    fSplot.styleCounter.dash = 5;
                    auto& sprobe = fSplot.line();
                    sprobe.styleIndex.colour = num_probes;

                    // buffer counter
                    int bcount = 0;
                    // samples with start point
                    int nbsamples = int(fCountSamples)-fStartSample;
                    if (fStartSample > 0) {
                        fDSP->compute(fStartSample, fDSPInputs, fDSPOutputs);
                    }
                    do {
                        // compute on the buffer size
                        fDSP->compute(fBufferSize, fDSPInputs, fDSPOutputs);
                        // increment buffer counter
                        ++bcount;
                        // reduce total samples number by buffer size
                        nbsamples -= fBufferSize;
                        // create a current frame position for probes
                        int curpos = fStartSample - 1 + bcount * int(fBufferSize);
                      
                        probe_counter.displayProbe(fPlot, probe, curpos, num_probes, valuepro);
                        if (fSplit) {
                            probe_counter.displayProbe(fSplot, sprobe, curpos, num_probes, valuepro);
                            minpro = std::min(minpro, valuepro);
                            maxpro = std::max(maxpro, valuepro);
                        }
                    } while (nbsamples > 0);
                    
                    // create a legend for the current line
                    legend.line(probe, "Probe " + std::to_string(num_probes + 1));
                    // split option
                    if (fSplit) {
                        // reset axes
                        fSplot.y.blank(1);
                        fSplot.x.blank(1);
                        // reset axes labels
                        fSplot.y.blankLabels(1);
                        fSplot.x.blankLabels(1);
                        // line legend
                        slegend.line(sprobe, "Probe " + std::to_string(num_probes + 1));
                        // sample axe
                        fSplot.x.linear(fStartSample, fCountSamples).major(fStartSample).minor(fCountSamples).label("Samples");
	                    // value axe
                        fSplot.y.minors(minpro, maxpro).label("Values");
                        fSplot.y.majors(0);
                        // create the svg file
                        fSplot.write("mydsp_Probe" + std::to_string(num_probes + 1) + ".svg");
                        // auto& sprobe = fSplot.fill();
                        cout << "mydsp_Probe" + std::to_string(num_probes + 1) + ".svg;" << endl;
                        // reset the current plot
                        sprobe.toFrame(0);
                        sprobe.clearFrames();
                    }
                }
                generateHTML(fDSP->getNumOutputs(), probe_counter.getNumProbes(), fSplit);
            }
        
            // create the axes
            fPlot.x.linear(fStartSample, fCountSamples).major(fStartSample).minor(fCountSamples).label("Samples");
            fPlot.y.minors(min, max).label("Values");
            fPlot.y.majors(0);
        
            // create the svg file
            fPlot.write("mydsp.svg");
            cout << "mydsp.svg;" << endl;
        }

};

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


list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#define kFrames 1

int main(int argc, char* argv[])
{
    dsp* DSP = new mydsp();
    
    FAUSTFLOAT nb_samples, sample_rate, buffer_size, start_at_sample, split;
    CMDUI* interface = new CMDUI(argc, argv);
    DSP->buildUserInterface(interface);
    
    interface->addOption("-n", &nb_samples, 4096.0, 0.0, 100000000.0);
    interface->addOption("-r", &sample_rate, 44100.0, 0.0, 192000.0);
    interface->addOption("-bs", &buffer_size, kFrames, 0.0, kFrames * 16);
    interface->addOption("-s", &start_at_sample, 0, 0.0, 100000000.0);
    interface->addOption("-sp", &split, 0, 0.0, 1.0);
    
    if (DSP->getNumInputs() > 0) {
        cerr << "no inputs allowed " << endl;
        exit(1);
    }

    // SR has to be read before DSP init
    interface->process_one_init("-r");
    
    // modify the UI values according to the command line options, after init
    interface->process_init();

#ifdef SOUNDFILE
    SoundUI soundinterface;
    DSP->buildUserInterface(&soundinterface);
#endif

    SVGPlot* svg_plot = new SVGPlot(DSP, sample_rate, nb_samples, buffer_size, start_at_sample, bool(split));
    svg_plot->exec();

    delete svg_plot;
    delete interface;
    delete DSP;
}

/******************** END svgplot.cpp ****************/

