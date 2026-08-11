// modified by Facundo Franchino
//
// Explicit template instantiations for clap::helpers::Plugin and HostProxy.
//
// clap-helpers is header-only but splits declaration (.hh) from definition
// (.hxx). Instantiating here, once, keeps every architecture file free of the
// .hxx include and its compile cost.
//
// Only the combination the Faust architectures actually use is instantiated.
// This file used to emit all four Plugin/HostProxy pairs; seven of the eight
// were referenced by nothing and cost about a megabyte of object code in every
// plugin built. An architecture built on another combination should add its own
// line here rather than have every plugin carry all of them.

#include <clap/helpers/host-proxy.hh>
#include <clap/helpers/host-proxy.hxx>
#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>
#include <clap/helpers/reducing-param-queue.hh>
#include <clap/helpers/reducing-param-queue.hxx>

// Used by clap-arch.cpp (static) and dynamic-faust.cpp (dynamic).
template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                     clap::helpers::CheckingLevel::Minimal>;
template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Terminate,
                                        clap::helpers::CheckingLevel::Minimal>;
