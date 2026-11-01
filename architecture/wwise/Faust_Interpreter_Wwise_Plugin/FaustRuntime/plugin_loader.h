#ifndef FAUST_PLUGIN_LOADER_H
#define FAUST_PLUGIN_LOADER_H

#include "PluginUtils/syscall.h"
// #include "Interpreter/debugDSP.h"
#include "Interpreter/wrapper.h"
#include "PluginTemplate/SourcePlugin.h"
#include "PluginTemplate/EffectPlugin.h"
#include "PluginInfo/plugin_state.h"

/*!
 * @brief Singleton class.
*/
class PluginLoader{

public:
    
    /*! @brief Get instance of the PluginLoader class. Singleton pattern.
    * @return PluginLoader& - a reference to the PluginLoader object.
    */
    static PluginLoader& getInstance(){
        static PluginLoader faust_plugin;
        return faust_plugin;
    }
    ~PluginLoader() = default;  // class destructor.
    PluginLoader(const PluginLoader&) = delete; // delete copy constructor
    PluginLoader& operator=(const PluginLoader&) = delete; // delete copy assignment operator
    PluginLoader(PluginLoader&&) = delete; // delete move constructor
    PluginLoader& operator=(PluginLoader&&) = delete; //  delete move assignement operator

    /* Returns the configuration */
    PluginConfiguration& getConfiguration() {   return cfg;     }
    /* Returns a list of parameters */
    ParameterList& getParameters()          {   return parameters;  }
    /* Returns the plugin state. Plugin state is an atomic variable. */
    PluginState getPluginState()            {   return pluginState.load();  }

    /* Function to create a new plugin. Called on previewing dsp code. */
    bool createPlugin(std::string&, int, std::string&);

    /* Shares the Sample Rate of the host environment*/
    int setupAudio(int);
    /* Function used to set the atomic variable to an exiting value.*/
    void unloadPlugin();
    /* Function used to reset all the internal structures to an null state .*/
    void resetPlugin();
    /* Audio callback function */
    void callback(std::vector<FAUSTFLOAT*>&, const AkUInt32);
    
    /* Function used to build plugin, calling faust2wwise behind the scenes. */
    bool buildPlugin(const std::string&, const std::string&, bool, bool, std::string&);
    /* returns the path created ('faust_' dir) with the Wwise root directory. */
    std::string& getExportPath() {   return cfg.path.exportPath;  }

    /* Compiles the dsp code and stores the cpp code on disk. */
    bool exportCPP(const std::string &filename, const std::string& dspCode, const std::string& filepath, bool doublePrecision, std::string& errorMessage);

private:
    /*! @brief Class constructor.
    */
    PluginLoader();

    InterpreterWrapper faustInterpreter;

    std::atomic<PluginState> pluginState;
    PluginConfiguration cfg;
    ParameterList parameters;
    
    AbstractPlugin *plugin;
    // preallocate
    WwiseEffectPlugin effectPlugin;
    WwiseSourcePlugin sourcePlugin;

};

#endif