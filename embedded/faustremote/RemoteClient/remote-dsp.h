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
#include <map>
#include "faust/audio/dsp.h"
#include "faust/gui/meta.h"

#ifdef __cplusplus
extern "C"
{
#endif

using namespace std;

typedef struct remote_dsp_factory {};


    
/**
 * Create a Remote DSP factory from a DSP source code. The code is compiled by a server, that
 returns a JSON application.
 *
 * @param filename - DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of compilation parameters (-vec/-sch/...)
 * @param ipServer - IP of remote machine that will compile your DSP 
 * @param portServer - Port on which the remote Server started
 * @param error - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
remote_dsp_factory* createRemoteDSPFactoryFromFile(const string& filename, int argc, const char *argv[], const string& ipServer, int portServer, string& error, int opt_level = 3);
    
    
/**
 * Create a Remote DSP factory from a DSP source code. The code is compiled by a server, that returns a JSON application.
 *
 * @param name_app - the name of the Faust Application to be compiled
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of compilation parameters (-vec/-sch/...)
 * @param ipServer - IP of remote machine that will compile your DSP 
 * @param portServer - Port on which the remote Server started
 * @param error - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
remote_dsp_factory* createRemoteDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc, const char *argv[], const string& ipServer, int portServer, string& error, int opt_level =  3);


/**
 * Destroy a Faust DSP factory.
 * 
 * @param factory - the DSP factory to be deleted.
 */
void deleteRemoteDSPFactory(remote_dsp_factory* factory);

 /**
 * Call global declarations with the given meta object.
 * 
 * @param factory - the Faust DSP factory
 * @param meta - the meta object to be used.
 *
 */
void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m);

/**
 * Instance class
 */
class remote_dsp : public dsp{
    
    public: 
    
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
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters 
 *                  --NJ_ip ==> MULTICAST_DEFAULT_IP 
 *                  --NJ_port ==> MULTICAST_DEFAULT_PORT
 *                  --NJ_compression ==> default is -1
 *                  --NJ_latency ==> default is 2
 *                  --NJ_mtu ==> default is 1500
 *                  --NJ_partial ==> default is 'false'
 * @param samplingRate - NetJack slave sampling Rate
 * @param bufferSize - NetJack slave buffer Size
 * @param error - the error string to be filled
 * 
 * @return the remote DSP instance on success, otherwise a null pointer.
 */
remote_dsp*  createRemoteDSPInstance(remote_dsp_factory* factory, int argc, const char *argv[], int samplingRate, int bufferSize, string& error);


/**
 * Destroy a remote DSP instance.
 * 
 * @param dsp - the DSP instance to be deleted.
 */ 
void        deleteRemoteDSPInstance(remote_dsp* dsp);
    
/**
 *  Scan the network to find the available machines for remote processing
 *  @param list to be filled with <nameMachine, IPmachine>
 *  @return true if no error was encountered
 */
bool        getRemoteMachinesAvailable(map<string, pair<string, int> >* machineList);

#ifdef __cplusplus
}
#endif

#endif



