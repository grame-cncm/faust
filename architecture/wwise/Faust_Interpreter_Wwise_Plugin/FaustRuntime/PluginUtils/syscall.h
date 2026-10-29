#ifndef FPLUGIN_SYSCALL_H
#define FPLUGIN_SYSCALL_H

#include <string>

namespace SysCall{
    
    /* Function that is used to get the Wwise env path. */
    std::string getEnvVar(const std::string& varName);

    /* Function used to call system commands (i.e. faust --dspdir). */
    std::string execCommand(const std::string& cmd);

}

#endif