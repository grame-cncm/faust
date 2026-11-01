#ifndef FAUST_INTERPRETER_WRAPPER_H
#define FAUST_INTERPRETER_WRAPPER_H

#include "faust/dsp/interpreter-dsp.h"
#include "PluginInfo/plugin_config.h"
#include "PluginUtils/plugin_utils.h"
#include "Parameters/myMapUI.h"
#include "Parameters/parameter.h"
#include <faust/dsp/dsp.h>
#include <string>
#include <filesystem>

class InterpreterWrapper {

public:
    /* class constructor */
    InterpreterWrapper();
    
    /* class destructor */
    ~InterpreterWrapper();

    /* function used to reset the object to a null state, where mdsp, mapui and factory are all null pointers. */
    void reset();

    /* function used to compile dsp input using the faust interpreter. */
    bool compileDSP(const std::string dspCode, const PluginConfiguration& cfg, std::string& errorMessage);
    
    /* function used to initialize mdsp and mapui after the dsp code is compiled.*/
    bool createDSPandUI();

    /* configures the plugin creation on many different steps, including UI initialization, 
     * establishing the plugin configuration (i.e. setting num I/O, plugin type, name of plugin etc.).  */
    bool configurePlugin(PluginConfiguration&, ParameterList&);

    /* function used to set the sample rate variable to the plugin. */
    void setupDSP(int);

    /* audio callback function */
    void callback(int, FAUSTFLOAT**, FAUSTFLOAT**);

    /* function used to set a parameter's value, by using its name. */
    template <typename T>
    void setParameter(const std::string name, T value)
    {
        mapui->setParamValue(name, static_cast<FAUSTFLOAT>(value)); 
    }

    /* function used to get a parameter's value, by using its name. */
    FAUSTFLOAT getParameter(const std::string& name);

    /* Compiles dsp code and store its cpp output into a file on disk. */
    bool exportCPP(const std::string& faust_dspdir, const std::string &filename, const std::string& dspCode, const std::string& filepath, bool doublePrecision, std::string& errorMessage);

private:

    interpreter_dsp_factory* factory;
    dsp* mdsp;
    myMapUI* mapui;
    std::string currentSHA;
    
    void setPluginConfiguration(PluginConfiguration&);
    void setParameterList(ParameterList&, PluginConfiguration&); 
};

#endif