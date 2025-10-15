// Created by Facundo Franchino 
/********************************************************************
                                                                   
                    clap-helpers-impl.cpp                  
               (c) GRAME & Facundo Franchino, 2025                 
                                                                  
********************************************************************/

/*
This is the implementation file for CLAP helpers template instantiations.
It provides the missing template implementations needed for linking and
minimal stub implementations for any missing GUI functions to prevent 
linking errors, as we don't use the GUI functionality here.
*/


#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>
#include <clap/helpers/host-proxy.hh>
#include <clap/helpers/host-proxy.hxx>
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