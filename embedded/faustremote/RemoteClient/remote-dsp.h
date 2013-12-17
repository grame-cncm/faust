/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************
 ************************************************************************/


#ifndef REMOTE_DSP_H
#define REMOTE_DSP_H

#include <string>
#include "faust/audio/dsp.h"

#ifdef __cplusplus
extern "C"
{
#endif

using namespace std;

typedef struct remote_dsp_factory {};

/**
 * Create a Remote DSP factory from a DSP source code. The code is compiled by a server, that returns a JSON applicatio.
 * 
 * @param ipServer - IP of remote machine that will compile your DSP 
 * @param dspContent - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters 
 *                  --NJ_ip ==> MULTICAST_DEFAULT_IP 
 *                  --NJ_port ==> MULTICAST_DEFAULT_PORT
 *                  --NJ_compression ==> default is -1
 *                  --NJ_latency ==> default is 2
 *
 *                  -vec/sch/... faust compilation options
 *
 * @param error - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
remote_dsp_factory* createRemoteDSPFactory(const string& ipServer, const string& dspContent, int argc, char** argv, int opt_level, string& error);


/**
 * Destroy a Faust DSP factory.
 * 
 * @param factory - the DSP factory to be deleted.
 */
void deleteRemoteDSPFactory(remote_dsp_factory* factory);


/**
 * Instance class
 */
class remote_dsp : public dsp{
    
    public: 
    
        remote_dsp();
        virtual ~remote_dsp();
    
        virtual int     getNumInputs();
        virtual int     getNumOutputs();

        virtual void    init(int samplingFreq);
    
        virtual void    buildUserInterface(UI* ui);
    
        virtual void    compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
};

/**
 * Create a remote DSP instance. A NetJack connexion is initialized with a certain samplingRate and bufferSize.
 * 
 * @param factory - the Remote DSP factory
 * @param samplingRate - NetJack slave sampling Rate
 * @param bufferSize - NetJack slave buffer Size
 * @param error - the error string to be filled
 * 
 * @return the remote DSP instance on success, otherwise a null pointer.
 */
remote_dsp*  createRemoteDSPInstance(remote_dsp_factory* factory, int samplingRate, int bufferSize, string& error);


/**
 * Destroy a remote DSP instance.
 * 
 * @param dsp - the DSP instance to be deleted.
 */ 
void        deleteRemoteDSPInstance(remote_dsp* dsp);

#ifdef __cplusplus
}
#endif

#endif



