#include "wrapper.h"
#include <faust/dsp/libfaust.h> 
#include <iostream>

InterpreterWrapper::InterpreterWrapper()
    : factory(nullptr)
    , mdsp(nullptr)
    , mapui(nullptr)
{}

InterpreterWrapper::~InterpreterWrapper()
{
    reset();
}

void InterpreterWrapper::reset()
{
    if (mapui)
    {
        delete mapui;
        mapui = nullptr;
    }

    if (mdsp)
    {
        delete mdsp;
        mdsp = nullptr;
    }

    if (factory)
    {
        deleteInterpreterDSPFactory(factory);
        factory = nullptr;
    }
}

bool InterpreterWrapper::compileDSP(const std::string dspCode, const PluginConfiguration &cfg, std::string& errorMessage)
{

    if(factory){
        deleteInterpreterDSPFactory(factory);
        factory = nullptr;
    }

    std::vector<const char*> args { 
        "-I", cfg.path.faust_dspdir.c_str(),
    };
    int argc = args.size();
    const char** argv = args.data();

    factory = createInterpreterDSPFactoryFromString(
        cfg.name_app,
        dspCode,
        argc,
        argv,
        errorMessage
    );

    if (!factory) 
    {
        std::cerr << "Faust compilation failed : " << errorMessage << std::endl;
        return false;
    }

    // update shaKey
    currentSHA = factory->getSHAKey();
    return true;
}

bool InterpreterWrapper::createDSPandUI()
{
    mdsp = factory->createDSPInstance();
    if (!mdsp) {
        std::cerr << "Cannot create instance " << std::endl;
        return false;
    }

    mapui = new myMapUI();
    if (!mapui)
    {
        std::cerr<<" Cannot create mapui "<<std::endl;
        return false;
    }

    return true;
}

bool InterpreterWrapper::configurePlugin(PluginConfiguration &cfg, ParameterList& parameters)
{
    mdsp->buildUserInterface(mapui);
    mapui->fillShortNames();
    setPluginConfiguration(cfg);
    setParameterList(parameters, cfg);
    return true; // TODO change return?
}

void InterpreterWrapper::setupDSP(int sampleRate)
{
    mdsp->init(sampleRate);
}

FAUSTFLOAT InterpreterWrapper::getParameter(const std::string& name)
{
    return mapui->getParamValue(name); 
}

void InterpreterWrapper::setPluginConfiguration(PluginConfiguration &cfg)
{
    // Extract inputs/outputs
    cfg.num_inputs = mdsp->getNumInputs();
    cfg.num_outputs = mdsp->getNumOutputs();

    // Determine plugin type based on inputs
    if (cfg.num_inputs > 0) {
        cfg.plugin_type = "effect";
    } else {
        cfg.plugin_type = "source";
    }

    // Extract project name & override in case it is provided as a declaration in faust dsp file
    // i.e. declare name "Name"
    std::string pluginName = factory->getName(); // in case a declare name "name" is assigned by the user, otherwise cfg.app_name.
    cfg.plugin_name = PluginUtils::ensure_valid_plugin_name(pluginName);
    std::cout << "PLUGIN_NAME changed to " << cfg.plugin_name << std::endl;

    // @TODO: author name? description?
    cfg.author = "Unknown";
    cfg.description = "No description provided";
}

void InterpreterWrapper::setParameterList(ParameterList& parameters, PluginConfiguration& cfg)
{
    
    const int numParams = mapui->getParamsCount(); 
    parameters.resize(numParams);

    for (const auto& control : mapui->controls)
    {
        myMapUI::itemInfo item = control.second;
        Parameter param;
        param.type = item.type;
        param.label = item.label;
        param.shortname = item.shortname;
        param.index = item.index;
        param.init = item.init;
        param.pmin = item.fmin;
        param.pmax = item.fmax;
        param.step = item.step;
        param.value.store(item.init);
        
        parameters[item.index] = std::move(param);
    }
}

void InterpreterWrapper::callback(int bufferSize, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
    mdsp->compute(bufferSize, inputs, outputs);
}

bool InterpreterWrapper::exportCPP(
    const std::string& faust_dspdir, 
    const std::string &filename, 
    const std::string& dspCode, 
    const std::string& filepath, 
    bool doublePrecision,
    std::string& errorMessage)
{

    interpreter_dsp_factory* fct;

    std::vector<const char*> args { 
        "-I", faust_dspdir.c_str(),
        "-lang", "cpp", 
        "-json"
    };
    if (doublePrecision)
        args.push_back("-double");
    int argc = args.size();
    const char** argv = args.data();

    fct = createInterpreterDSPFactoryFromString(
        filename,
        dspCode,
        argc,
        argv,
        errorMessage
    );

    if (!fct) 
    {
        std::cerr << "Faust compilation failed : " << errorMessage << std::endl;
        return false;
    }

    writeInterpreterDSPFactoryToBitcodeFile(fct, filepath);
    
    deleteInterpreterDSPFactory(fct);

    return true;
}
