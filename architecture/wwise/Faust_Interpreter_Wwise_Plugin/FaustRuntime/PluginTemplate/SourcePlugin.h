#ifndef TEMPLATE_SOURCE_PLUGIN_H
#define TEMPLATE_SOURCE_PLUGIN_H

#include "abstract.h"

class WwiseSourcePlugin: public AbstractPlugin
{
public:
    WwiseSourcePlugin(PluginConfiguration&, ParameterList&, InterpreterWrapper&);
    ~WwiseSourcePlugin() = default;
    void reset() override final;
    void setup() override final;
    void callback(std::vector<FAUSTFLOAT*>&, const AkUInt32) override final;
};

#endif