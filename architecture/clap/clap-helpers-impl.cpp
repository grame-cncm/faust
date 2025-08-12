// clap-helpers-impl.cpp
// Implementation file for CLAP helpers template instantiations
// This provides the missing template implementations needed for linking

#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>
#include <clap/helpers/host-proxy.hh>
#include <clap/helpers/host-proxy.hxx>

// Minimal stub implementations for any missing GUI functions
// These prevent linking errors but don't provide actual GUI functionality
#include <list>

// Forward declaration for Faust GUI class
class FaustGUI;

namespace GUI {
    // Static GUI list that real Faust would maintain
    std::list<FaustGUI*> fGuiList;
    
    void updateAllGuis() {
        // Stub implementation - does nothing
        // Real implementation would update all GUI instances
    }
}

// Explicit template instantiation for the Plugin class we use
namespace clap { namespace helpers {

// Template instantiation for Plugin with Terminate handler and Minimal checking
template class Plugin<MisbehaviourHandler::Terminate, CheckingLevel::Minimal>;
template class HostProxy<MisbehaviourHandler::Terminate, CheckingLevel::Minimal>;

}} // namespace clap::helpers