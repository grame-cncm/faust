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
#include <faust/gui/UI.h>
#include <iostream>
#include <ostream>
#include <string>

#include "faust/audio/channels.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/console.h"
#include "faust/gui/DecoratorUI.h"
//#ifdef FIXED_POINT
//#include "faust/dsp/fixed-point.h"
//#endif
#include "faust/misc.h"

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif


#include "plot.h"
#include "heatmap.h"

using namespace std;

// A class to display Bargraph values
struct DisplayUI : public GenericUI 
{

    map<string, FAUSTFLOAT*> fProbeMap;
     
    void displayProbeHeaders()
    {
        int c = 0;
        if (fProbeMap.size() > 0)
        {
            printf(",\t");
            for (const auto& it : fProbeMap) 
            {
                if (c > 0)
                {
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

    void displayProbe(signalsmith::plot::Plot2D &plot, signalsmith::plot::Line2D &probe, int frame, int chan, float &value)
    {
        if (fProbeMap.size() > 0)
        {
            for (int c=0; c<fProbeMap.size(); c++) 
            {
                for (const auto& it : fProbeMap) 
                {
                    if( c == chan)
                    {
                    //printf(",\t");
                    //cout << *it.second;
                    probe.add(frame, (*it.second));
                    value = (*it.second);
                    //debug
                    ////cout << std::endl;
                    ////cout << "Frame : "<< frame << " it : " << *it.second;
                    ////cout << std::endl;
                    }
                    c++;
                }
            }
        }
    }


    void declare(FAUSTFLOAT* zone,const char* key,const char* val)
    {
        if (strcmp(key,"probe") == 0) 
        {
            fProbeMap[std::string(val)]=zone;
        }
    }
    
};


class faust2svgplot {

    private:
        
        //DSP
        FAUSTFLOAT** DSP_inputs;
        FAUSTFLOAT** DSP_outputs;
        dsp* DSP;
        //args
        FAUSTFLOAT nsamples;
        FAUSTFLOAT srate;
        FAUSTFLOAT bsize;
        FAUSTFLOAT strsample;
        FAUSTFLOAT splt;
        //global plot
        signalsmith::plot::Plot2D plot;
        //plot for probes in split mode
        signalsmith::plot::Plot2D splot;
        //plot for lines in split mode
        signalsmith::plot::Plot2D stplot;

    public : 
        //Function to create a ** inputs or outputs buffers 
        FAUSTFLOAT** createbuffer (int chan, int buffer_size)
        {
            
            FAUSTFLOAT** buffer = new FAUSTFLOAT*[chan];
                for (int i = 0; i < chan; i++) 
                {
                    buffer[i] = new FAUSTFLOAT[buffer_size];
                    memset(buffer[i], 0, sizeof(FAUSTFLOAT) * buffer_size);
                }
                return buffer;
        }
        //function to delete a buffer
        void deletebuffer (FAUSTFLOAT** buffer, int chan)
        {
                for (int i = 0; i <chan; i++) 
                {
                    delete [] buffer[i];
                }
                delete [] buffer;
        }
        //Constructor
        faust2svgplot(dsp* dsp, FAUSTFLOAT sample_rate, FAUSTFLOAT nb_samples, FAUSTFLOAT buffer_size, FAUSTFLOAT start_at_sample, FAUSTFLOAT split)
        {   
            //Args
            DSP = dsp; 
            nsamples= nb_samples;
            srate = sample_rate;
            bsize = buffer_size;
            splt = split;
            strsample = start_at_sample;
            //create the buffers
            DSP_inputs = createbuffer(DSP->getNumInputs(), nsamples);
            DSP_outputs = createbuffer(DSP->getNumOutputs(),nsamples);
        }


        void exec()
        {
            //custom UI functions
            DisplayUI disp;
            DSP->buildUserInterface(&disp);
            //init position for max and min
            FAUSTFLOAT max = DSP_outputs[0][0]; 
            FAUSTFLOAT min =  DSP_outputs[0][0]; 
                        
            //init signal processor and the user interface values
            DSP->init(srate);

            //create the graph legend 
            auto &legend = plot.legend(0, -1);
            //compute
            DSP->compute(nsamples, DSP_inputs, DSP_outputs);

            //go through the different channels
            for (int chan=0; chan< DSP->getNumOutputs(); ++chan) 
            {
                //reset for straight line and no dotted line
                plot.styleCounter.dash = 0;
                //create a line for the actual channel
                auto &line = plot.line();
                //temporary line
                auto &sline = stplot.line();
                auto &slegend = stplot.legend(0, -1);
                //fixed Index colour position similar to channel
                line.styleIndex.colour = chan;
                //
                for (int frame=0+strsample; frame < nsamples; ++frame) 
                {
                    //debug
                    ////std::cout << "frame: "<< frame;
                    FAUSTFLOAT* sub_outputs = DSP_outputs[chan];
                    ////std::cout << " | Channel " << chan+1 << " :" << sub_outputs[frame] << "\t";
                    ////std::cout << std::endl;
                    
                    //write points in line
                    line.add(frame, sub_outputs[frame]);
                    //check for max and min in order to create proportional axes
                    
                    if (max <= sub_outputs[frame]) 
                    {
                        max = sub_outputs[frame];
                    }
                    if (min >= sub_outputs[frame]) 
                    {
                        min = sub_outputs[frame];
                    }
                    
                    sline.add(frame, sub_outputs[frame]);
                    if (splt==1)
                    {
                        //disp.returnProbe(splot, spr:wobe, curpos, numbprobes, valuepro);
                    }
                }
                //add legend name 
                legend.line(line,"Channel "+std::to_string(chan+1));
                if (splt == 1) 
                {
                    stplot.y.blank(1);
                    stplot.x.blank(1);
                    stplot.y.blankLabels(1);
                    stplot.x.blankLabels(1);
                    //
                    slegend.line(sline,"Channel "+std::to_string(chan+1));
                    //
                    stplot.x.linear(0+strsample,nsamples).major(0+strsample).minor(nsamples).label("Samples");
	                stplot.y.minors(min,max).label("Values");
                    stplot.y.majors(0);
                    //create the svg file
                    stplot.write("mydsp_Channel"+std::to_string(chan+1)+".svg");
                    //auto &sprobe=splot.fill();
                    cout<<"mydsp_Channel"+std::to_string(chan+1)+".svg;"<<std::endl;
                    //
                    sline.toFrame(0);
                    sline.clearFrames();
                }
            }
                     

            //if probe metadata in the dsp code
            if (disp.getNumProbes()>0) 
            {
                for (int numbprobes=0; numbprobes< disp.getNumProbes(); ++numbprobes) 
                {
                    float minpro=0.0;
                    float maxpro=0.0;
                    float valuepro=0.0;
                    auto &slegend = splot.legend(0, -1);
                    DSP->init(srate);
                    //probegraph_init
                    //reset for dotted line and no straight line
                    plot.styleCounter.dash = 5; 
                    //create a line
                    auto &probe = plot.line();
                    //fixed Index colour position similar to probe number
                    probe.styleIndex.colour = numbprobes;

                    //temporary probe 
                    splot.styleCounter.dash = 5; 
                    auto &sprobe = splot.line();
                    sprobe.styleIndex.colour = numbprobes;

                    /////////////////////////////////////////////
                    //buffer counter
                    int bcount = 0;
                    //samples with start point
                    int nbsamples=int(nsamples)-strsample;
                    if (strsample>0) 
                    {
                        DSP->compute(strsample,DSP_inputs,DSP_outputs);
                    }
                    do
                    {
                        //compute on the buffer size
                        DSP->compute(bsize, DSP_inputs, DSP_outputs);
                        //increment buffer counter
                        ++bcount;
                        //reduce total samples number by buffer size
                        nbsamples -= bsize;
                        //create a current frame position for probes
                        int curpos = strsample-1+bcount*int(bsize);
                        //
                        disp.displayProbe(plot, probe, curpos, numbprobes,valuepro);
                        if (splt==1)
                        {
                            disp.displayProbe(splot, sprobe, curpos, numbprobes,valuepro);

                            if (valuepro < minpro) 
                            {
                                minpro = valuepro;
                            }
                            if (valuepro > maxpro)
                            {
                                maxpro = valuepro;
                            }
                        }
                    }while(nbsamples > 0);
                    //create a legend for the current line
                    legend.line(probe,"Probe "+std::to_string(numbprobes+1));
                    //split option
                    if (splt == 1) 
                    {
                        //reset axes
                        splot.y.blank(1);
                        splot.x.blank(1);
                        //reset axes labels
                        splot.y.blankLabels(1);
                        splot.x.blankLabels(1);
                        //line legend
                        slegend.line(sprobe,"Probe "+std::to_string(numbprobes+1));
                        //sample axe
                        splot.x.linear(0+strsample,nsamples).major(0+strsample).minor(nsamples).label("Samples");
	                    //value axe
                        splot.y.minors(minpro,maxpro).label("Values");
                        splot.y.majors(0);
                        //create the svg file
                        splot.write("mydsp_Probe"+std::to_string(numbprobes+1)+".svg");
                        //auto &sprobe=splot.fill();
                        cout<<"mydsp_Probe"+std::to_string(numbprobes+1)+".svg;"<<std::endl;
                        //reset the current plot
                        sprobe.toFrame(0);
                        sprobe.clearFrames();
                    }

                }
                GenerateHtml(DSP->getNumOutputs(),disp.getNumProbes(),splt);

            }
        //create the axes
        plot.x.linear(0+strsample,nsamples).major(0+strsample).minor(nsamples).label("Samples");
	    plot.y.minors(min, max).label("Values");
        plot.y.majors(0);
        //create the svg file
        plot.write("mydsp.svg");
        cout<<"mydsp.svg;"<<std::endl; 
        }

        void GenerateHtml(int channels,  int numbprobes, int split)
        {
            std::ofstream file("output.html"); // Create a file named "output.html"
            if (file.is_open()) 
            {
                file << "<html>\n";
                file << "<head>\n";
                file << "<title>SVG Gallery</title>\n";
                file << "</head>\n";
                file << "<body>\n";
                file << "<img src=mydsp.svg>\n";
                if (split==1) 
                {
                    for (int i=0; i<channels; i++) {
                        file << "<img src=" <<"mydsp_Channel"+std::to_string(i+1)<<".svg>\n";
                    }
                    for (int i=0; i<numbprobes; i++) {
                        file << "<img src=" <<"mydsp_Probe"+std::to_string(i+1)<<".svg>\n";
                    }

                }
                    file << "</body>\n";
                    file << "</html>\n";
                    file.close();
                
                std::cout << "SVG Gallery generated successfully!" << std::endl;
                std::cout << "output.html;" << std::endl;
            } else 
            {
                std::cerr << "Failed to create the SVG Gallery!" << std::endl;
            }
        }
        virtual ~faust2svgplot()
        {
            deletebuffer(DSP_inputs, DSP->getNumInputs());
            deletebuffer(DSP_outputs, DSP->getNumOutputs());
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


std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#define kFrames 1

int main(int argc, char* argv[])
{
    dsp* DSP = new mydsp();
    
    FAUSTFLOAT nb_samples,sample_rate, buffer_size, start_at_sample, split; 
    CMDUI* interface = new CMDUI(argc, argv);
    DSP->buildUserInterface(interface);
    
    interface->addOption("-n", &nb_samples, 4096.0, 0.0, 100000000.0);
    interface->addOption("-r", &sample_rate, 44100.0, 0.0, 192000.0);
    interface->addOption("-bs", &buffer_size, kFrames, 0.0, kFrames * 16);
    interface->addOption("-s", &start_at_sample, 0, 0.0, 100000000.0);
    interface->addOption("-sp", &split, 0, 0.0, 1.0);
    
    if (DSP->getNumInputs() > 0) 
    {
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

    faust2svgplot* f2svg= new faust2svgplot(DSP, sample_rate, nb_samples, buffer_size, start_at_sample, split);

    f2svg->exec();

    delete f2svg;
    delete interface;
    delete DSP;
}

/******************** END svgplot.cpp ****************/

