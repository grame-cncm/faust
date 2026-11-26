#include "SourcePlugin.h"

WwiseSourcePlugin::WwiseSourcePlugin
(
    PluginConfiguration& config, 
    ParameterList& params, 
    InterpreterWrapper& interpreter
)
    : AbstractPlugin(config, params, interpreter)
{}

void WwiseSourcePlugin::reset()
{
    AbstractPlugin::reset();
}

void WwiseSourcePlugin::setup()
{
    AbstractPlugin::setup();
}

void WwiseSourcePlugin::callback(std::vector<FAUSTFLOAT*>& outputs, const AkUInt32 bufferSize)
{

    setParameters();
    
    for (AkUInt32 ch = 0; ch < cfg.num_outputs; ++ch)
    {
        faust_outputs[ch] = outputs[ch];
    }
        
    faustInterpreter.callback(bufferSize, nullptr, faust_outputs.data());


}