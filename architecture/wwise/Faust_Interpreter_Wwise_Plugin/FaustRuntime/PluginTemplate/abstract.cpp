#include "abstract.h"

AbstractPlugin::AbstractPlugin(PluginConfiguration& config, ParameterList& params, InterpreterWrapper& interpreter)
    : cfg(config)
    , parameters(params)
    , faustInterpreter(interpreter)
{
}

AbstractPlugin::~AbstractPlugin(){
    reset();
}

void AbstractPlugin::setup()
{
    faust_outputs.resize(cfg.num_outputs);
}

void AbstractPlugin::reset()
{
    faust_outputs.clear();

}

void AbstractPlugin::setParameters()
{
    for (auto& p : parameters){

        if (p.type!="bargraph")
        {
            faustInterpreter.setParameter(p.shortname,p.value.load());
        }
        else
        {
            p.value.store(faustInterpreter.getParameter(p.shortname));
        }

    }

}