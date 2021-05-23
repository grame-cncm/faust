
## The libfaustremote library

The `libfaustremote` library allows to compile and process a Faust DSP program on a remote machine.

### Remote server 

The server launches a compilation service, waiting for DSPs to compile. Dependencies are:        
* `LLVM` using macport
* `faust` make + sudo make install at the root of Faust project
* `HTTPDFaust` make httpd + sudo make install at the root of Faust project
* `libmicrohttpd` using macport
* `libjacknet` download JackOSX package at: https://jackaudio.org

Here is the API:

* `remote_dsp_server* createRemoteDSPServer()`
* `void deleteRemoteDSPServer(remote_dsp_server* server)`

Use the server class to start/stop the compilation service:

```
class remote_dsp_server {
    public: 

    bool start(int port = 7777); /* Start the DSP compilation service on a given port */
    void stop();                 /* Stop the DSP compilation */

    void setCreateDSPFactoryCallback(createFactoryDSPCallback callback, void* callback_arg);
    void setDeleteDSPFactoryCallback(deleteFactoryDSPCallback callback, void* callback_arg);

    void setCreateDSPInstanceCallback(createInstanceDSPCallback callback, void* callback_arg);
    void setDeleteDSPInstanceCallback(deleteInstanceDSPCallback callback, void* callback_arg);
};
```

### Remote client 

Here is the API:

To easily include remote processing in your projects, this API has been created. It has the similar prototype as `llvm-dsp` dynamic dsp:

* `createRemoteDSPFactoryFromFile(const std::string& filename, int argc, const char* argv[], const string& ipServer, int portServer, string& error, int opt_level)`
* `createRemoteDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc, const char* argv[], const string& ipServer, int portServer, string& error, int opt_level)`
* `createRemoteDSPInstance(remote_dsp_factory* factory, int argc, const char* argv[], int samplingRate, int bufferSize, string& error)`

Use instance as any static DSP:

* `virtual int getNumInputs()`
* `virtual int getNumOutputs()`
* `virtual void init(int samplingFreq)`
* `virtual void buildUserInterface(UI* ui)`
* `virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)`

* `void deleteRemoteDSPInstance(remote_dsp* dsp)`
* `void deleteRemoteDSPFactory(remote_dsp_factory* factory)`

This example shows how to use the API. In this example you can pass in command line:

* the IP of remote Server you want to use
* NetJack parameters of slave to be open on remote machine (localIP/Port/Latency/Compression)
* the dsp files you want to run in JACK/QT environment and the number of instances for each
* syntax is given with `./RemoteClient --help`

The following has to be added at link time: `-lfaustremote -lcurl -ljacknet`.
