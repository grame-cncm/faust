
=========================================== FAUSTREMOTE ======================================

With Faust Remote you will be able to compile and process your Faust DSP on a remote machine.

------------------------------REMOTE SERVER------------------

The server launches a server, waiting for DSPs to compile.

Dependencies :		
	- LLVM			through macport
	- faust			make + sudo make install at the root of faust project
	- HTTPDFaust		make httpd + sudo make install at the root of faust project
	- microhttpd		through macport
	- boost			through macport
	- jacknet		download jack on : http://www.jackosx.com/

----------------REMOTE CLIENT---------------

1 -------- THE API

	To easily include remote processing in your projects, this API has been created. 
It has the same prototype as Dynamic dsp, llvm-dsp.

a. CreateRemoteDSPFactory(const string& ipServer, const string& dspContent, int argc, 
				char** argv, int opt_level, string& error);

b. CreateRemoteDSPInstance(remote_dsp_factory* factory, int samplingRate, int bufferSize,
				 string& error)

c. Use instances as any "static" DSP 

	virtual int     getNumInputs();
        virtual int     getNumOutputs();

        virtual void    init(int samplingFreq);
  
        virtual void    buildUserInterface(UI* ui);
    
        virtual void    compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);

d. deleteRemoteDSPInstance(remote_dsp* dsp)

e. deleteRemoteDSPFactory(remote_dsp_factory* factory)

2 ------- THE EXAMPLE

	This example shows how to use the API. In this example you can pass in command line:
	
a. The IP of remote Server you want to use
b. NetJack parameters of slave to be open on remote machine (localIP/Port/Latency/Compression)
c. The dsp files you want to run in JACK/QT environment and the number of instances for each
d. Syntax is given with ./RemoteClient --help

LINK:	-faustremote
	-curl
	-jacknet


