/************************** BEGIN fpe.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __fpe__
#define __fpe__

#include <cfenv>
#include <iostream>
#include <signal.h>

#ifndef HAVE_FEENABLEEXCEPT
#if defined(__APPLE__) && defined(__MACH__)

// Public domain polyfill for feenableexcept on OS X
// http://www-personal.umich.edu/~williams/archive/computation/fe-handling-example.c

inline int feenableexcept(unsigned int excepts)
{
    static fenv_t fenv;
    unsigned int new_excepts = excepts & FE_ALL_EXCEPT;
    // previous masks
    unsigned int old_excepts;
    
    if (fegetenv(&fenv)) {
        return -1;
    }
    old_excepts = fenv.__control & FE_ALL_EXCEPT;
    
    // unmask
    fenv.__control &= ~new_excepts;
    fenv.__mxcsr   &= ~(new_excepts << 7);
    
    return fesetenv(&fenv) ? -1 : old_excepts;
}

inline int fedisableexcept(unsigned int excepts)
{
    static fenv_t fenv;
    unsigned int new_excepts = excepts & FE_ALL_EXCEPT;
    // all previous masks
    unsigned int old_excepts;
    
    if (fegetenv(&fenv)) {
        return -1;
    }
    old_excepts = fenv.__control & FE_ALL_EXCEPT;
    
    // mask
    fenv.__control |= new_excepts;
    fenv.__mxcsr   |= new_excepts << 7;
    
    return fesetenv(&fenv) ? -1 : old_excepts;
}

#else
inline int feenableexcept(unsigned int excepts)
{
#pragma STDC FENV_ACCESS ON
    fexcept_t flags;
    /* Save current exception flags. */
    fegetexceptflag(&flags, FE_ALL_EXCEPT);
    
    feclearexcept(FE_ALL_EXCEPT);   /* clear all fp exception conditions */
    return fesetexceptflag(&flags, excepts) != 0 ? -1 : flags; /* set new flags */
    
}

inline int fedisableexcept(unsigned int excepts)
{
#pragma STDC FENV_ACCESS ON
    fexcept_t flags;
    /* Save current exception flags. */
    fegetexceptflag(&flags, FE_ALL_EXCEPT);
    
    feclearexcept(FE_ALL_EXCEPT);   /* clear all fp exception conditions */
    return fesetexceptflag(&flags, ~excepts) != 0 ? -1 : flags; /* set new flags */
}

#endif
#endif

// https://en.cppreference.com/w/c/numeric/fenv/FE_exceptions

static void fPEHandler(int sig, siginfo_t* sip, ucontext_t* scp)
{
    int fe_code = sip->si_code;
    
    switch (fe_code) {
    #ifdef FPE_NOOP  // occurs in OS X
        case FPE_NOOP: throw std::runtime_error("FE_NOOP"); break;
    #endif
        case FPE_FLTDIV: throw std::runtime_error("FE_DIVBYZERO"); break;   // divideByZero
        case FPE_FLTINV: throw std::runtime_error("FE_INVALID"); break;     // invalid
        case FPE_FLTOVF: throw std::runtime_error("FE_OVERFLOW"); break;    // overflow
        case FPE_FLTUND: throw std::runtime_error("FE_UNDERFLOW"); break;   // underflow
        case FPE_FLTRES: throw std::runtime_error("FE_INEXACT"); break;     // inexact
        case FPE_FLTSUB: throw std::runtime_error("FE_INVALID"); break;     // invalid
        case FPE_INTDIV: throw std::runtime_error("INT_DIVBYZERO"); break;  // divideByZero
        case FPE_INTOVF: throw std::runtime_error("INT_OVERFLOW"); break;   // overflow
        default: throw std::runtime_error("FE_NOOP"); break;
    }
}

static bool gSetFPEHandler = false;
static void setFPEHandler()
{
    feclearexcept(FE_ALL_EXCEPT);
    feenableexcept(FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
    
    if (!gSetFPEHandler) {
        gSetFPEHandler = true;
        
        struct sigaction act;
        act.sa_sigaction = (void(*)(int, siginfo_t*, void*))fPEHandler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;
        int res = sigaction(SIGFPE, &act, (struct sigaction*)0);
    }
}

/* 
 
TRY_FPE/CATCH_FPE to be used by wrapping code that needs for be protected
 
TRY_FPE
compute(...);
CATCH_FPE
 
*/

#define TRY_FPE     \
setFPEHandler();    \
try {               \

#define CATCH_FPE                   \
} catch (std::runtime_error e) {    \
    std::cerr << "Math exception : " << e.what() << std::endl;  \
    exit(-1);                       \
}                                   \

#endif

/**************************  END  fpe.h **************************/
