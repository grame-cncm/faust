
=========================================== FAUSTREMOTE ======================================

With Faust Remote you will be able to compile and process your Faust DSP on a remote machine.

------------------------------ REMOTE SERVER ------------------

The server launches a compilation service, waiting for DSPs to compile.

Dependencies :		
	- LLVM			through macport
	- faust			make + sudo make install at the root of faust project
	- HTTPDFaust		make httpd + sudo make install at the root of faust project
	- microhttpd		through macport
	- jacknet		download JackOSX package at : http://www.jackosx.com/

1 -------- THE API --------

a. remote_dsp_server* createRemoteDSPServer();

b. void deleteRemoteDSPServer(remote_dsp_server* server);

C. Use the server class to start/stop the compilation service

class remote_dsp_server {
    
    public: 
        
        bool start(int port = 7777); /* Start the DSP compilation service on a given port. */
        void stop();                 /* Sop the DSP compilation. */

	 void setCreateDSPFactoryCallback(createFactoryDSPCallback callback, void* callback_arg);
        void setDeleteDSPFactoryCallback(deleteFactoryDSPCallback callback, void* callback_arg);
        
        void setCreateDSPInstanceCallback(createInstanceDSPCallback callback, void* callback_arg);
        void setDeleteDSPInstanceCallback(deleteInstanceDSPCallback callback, void* callback_arg);
};


---------------- REMOTE CLIENT ---------------

1 -------- THE API --------

To easily include remote processing in your projects, this API has been created. 
It has the same prototype as dynamic dsp, llvm-dsp.

a. createRemoteDSPFactoryFromFile(const std::string& filename, int argc, const char *argv[],
	 const string& ipServer, int portServer, string& error, int opt_level);

b. createRemoteDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc, const char *argv[],
	 const string& ipServer, int portServer, string& error, int opt_level);

c. createRemoteDSPInstance(remote_dsp_factory* factory, int argc, const char *argv[], int samplingRate, int bufferSize, string& error)

d. Use instances as any "static" DSP 

	virtual int     getNumInputs();
       	virtual int     getNumOutputs();

        virtual void    init(int samplingFreq);
  
        virtual void    buildUserInterface(UI* ui);

        virtual void    compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);

e. deleteRemoteDSPInstance(remote_dsp* dsp)

f. deleteRemoteDSPFactory(remote_dsp_factory* factory)

2 ------- THE EXAMPLE

This example shows how to use the API. In this example you can pass in command line:
	
a. The IP of remote Server you want to use
b. NetJack parameters of slave to be open on remote machine (localIP/Port/Latency/Compression)
c. The dsp files you want to run in JACK/QT environment and the number of instances for each
d. Syntax is given with ./RemoteClient --help

LINK:	-lfaustremote
	-lcurl
	-ljacknet


