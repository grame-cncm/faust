#ifndef TEMPLATE_ABSTRACT_PLUGIN_H
#define TEMPLATE_ABSTRACT_PLUGIN_H

#include "PluginInfo/plugin_config.h"
#include "Parameters/parameter.h"
// #include "Interpreter/debugDSP.h"
#include "Interpreter/wrapper.h"

typedef uint32_t AkUInt32;

class AbstractPlugin{
public:

    /* Constructor */
    AbstractPlugin(PluginConfiguration&, ParameterList&, InterpreterWrapper&);

    /* Destructor */
    virtual ~AbstractPlugin();
    
    /* Function that resets the plugin to its initial state. */
    virtual void reset();

    /* Function to allow any type of preprocessing before audio streaming commence. */
    virtual void setup();    

    /* Pure virtual audio callback function. Is implemented differently on the children classes (source, effect). */
    virtual void callback(std::vector<FAUSTFLOAT*>&, const AkUInt32)=0;
    
protected:

    void setParameters();

    PluginConfiguration& cfg;
    ParameterList& parameters;
    InterpreterWrapper& faustInterpreter;

    std::vector<FAUSTFLOAT*> faust_outputs;

};

#endif