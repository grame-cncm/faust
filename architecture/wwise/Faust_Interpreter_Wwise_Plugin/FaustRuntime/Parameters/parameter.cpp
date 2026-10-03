#include "parameter.h"

Parameter::Parameter()
    : type("")
    , label("")
    , shortname("")
    , index(-1)
    , init(0.0)
    , pmin(0.0)
    , pmax(1.0)
    , step(0.01)
    , value {0.0f}
{
    preview.id = -1;
}

 
 Parameter::Parameter(Parameter&& p) noexcept
    : type(p.type)
    , label(p.label)
    , shortname(p.shortname)
    , index(p.index)
    , init(p.init)
    , pmin (p.pmin)
    , pmax (p.pmax)
    , step (p.step)
    , value{p.value.load()}
{
    preview.id = p.preview.id;
}
        
Parameter& Parameter::operator=(Parameter&& p) noexcept
{
    type = std::move(p.type);
    label = std::move(p.label);
    shortname = std::move(p.shortname);
    index = p.index;
    init = p.init;
    pmin = p.pmin;
    pmax = p.pmax;
    step = p.step;
    value.store(p.value.load());
    preview.id = p.preview.id;
    return *this;
}
