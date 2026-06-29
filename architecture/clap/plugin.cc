//modified by Facundo Franchino
//explicit template instantiations for clap::helpers::Plugin and HostProxy

#include <clap/helpers/host-proxy.hxx>
#include <clap/helpers/param-queue.hh>
#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>
#include <clap/helpers/reducing-param-queue.hh>
#include <clap/helpers/reducing-param-queue.hxx>

//instantiate combinations of Plugin<MisbehaviourHandler, CheckingLevel>

template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                     clap::helpers::CheckingLevel::Maximal>;
template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                     clap::helpers::CheckingLevel::Minimal>;
template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                     clap::helpers::CheckingLevel::None>;
template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Ignore,
                                     clap::helpers::CheckingLevel::Maximal>;

//instantiate combinations of HostProxy<MisbehaviourHandler, CheckingLevel>

template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Terminate,
                                        clap::helpers::CheckingLevel::Maximal>;
template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Terminate,
                                        clap::helpers::CheckingLevel::Minimal>;
template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Terminate,
                                        clap::helpers::CheckingLevel::None>;
template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Ignore,
                                        clap::helpers::CheckingLevel::Maximal>;
