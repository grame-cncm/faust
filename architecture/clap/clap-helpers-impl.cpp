// clap-helpers-impl.cpp
// implementation file for CLAP helpers template instantiations
// this provides the missing template implementations needed for linking

#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>
#include <clap/helpers/host-proxy.hh>
#include <clap/helpers/host-proxy.hxx>

// minimal stub implementations for any missing GUI functions
// these prevent linking errors but don't provide actual GUI functionality
#include <list>

// forward declaration for Faust GUI class
class FaustGUI;

namespace GUI {
    // static GUI list that real Faust would maintain
    std::list<FaustGUI*> fGuiList;
    
    void updateAllGuis() {
        // stub implementation - does nothing
        // real implementation would update all GUI instances
    }
}

// explicit template instantiation for the Plugin class we use
namespace clap { namespace helpers {

// template instantiation for Plugin with Terminate handler and Minimal checking
template class Plugin<MisbehaviourHandler::Terminate, CheckingLevel::Minimal>;
template class HostProxy<MisbehaviourHandler::Terminate, CheckingLevel::Minimal>;

}} // namespace clap::helpers