/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

/*
 Audio hosts often call libfaust from a thread where subnormal values are flushed
 to zero (DAZ and FTZ on x86, FZ on AArch64). The compilation must give the same
 result as in the default floating-point environment (issue #1117: the interval
 analysis of pow failed), and must leave the caller's environment as it was.

 simplifyToNormalForm runs in the caller's thread, createSourceFromSignals in a
 compilation thread: both are checked against the results obtained before the
 flush mode is set.
 */

#include "faust/dsp/libfaust-signal.h"
#include <cstdint>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#if defined(__SSE__) || defined(_M_X64) || (defined(_M_IX86_FP) && (_M_IX86_FP >= 1))
#include <xmmintrin.h>
#define FLUSH_MODE "DAZ+FTZ"
static void setFlushMode()
{
    _mm_setcsr(_mm_getcsr() | 0x8040);
}
static bool hasFlushMode()
{
    return (_mm_getcsr() & 0x8040) == 0x8040;
}
#elif defined(__aarch64__)
#define FLUSH_MODE "FZ"
static uint64_t getFPCR()
{
    uint64_t fpcr;
    __asm__ __volatile__("mrs %0, fpcr" : "=r"(fpcr));
    return fpcr;
}
static void setFlushMode()
{
    uint64_t fpcr = getFPCR() | (uint64_t(1) << 24);
    __asm__ __volatile__("msr fpcr, %0" : : "r"(fpcr));
}
static bool hasFlushMode()
{
    return (getFPCR() & (uint64_t(1) << 24)) != 0;
}
#endif

// The signals of the test
static tvec signals()
{
    Signal x = sigInput(0);
    // The reduction of issue #1117, the example of PR #1341, and a product of
    // constants whose value is subnormal, which FTZ flushes to zero
    Signal tiny = sigMul(sigReal(1e-300), sigReal(1e-10));
    return {sigMul(x, x), sigPow(x, sigReal(0.4)), sigMul(x, sigGT(tiny, sigReal(0.0)))};
}

// The normal forms of the signals, then the code generated from them, each in its own context
static std::vector<std::string> compile()
{
    std::vector<std::string> res;
    createLibContext();
    for (Signal s : signals()) {
        try {
            res.push_back(printSignal(simplifyToNormalForm(s), false, 4096));
        } catch (std::exception& e) {
            res.push_back(std::string("simplifyToNormalForm: ") + e.what());
        }
    }
    destroyLibContext();

    createLibContext();
    std::string error;
    std::string code = createSourceFromSignals("FloatEnv", signals(), "cpp", 0, nullptr, error);
    res.push_back((error == "") ? code : "createSourceFromSignals: " + error);
    destroyLibContext();
    return res;
}

// The first line of <a> that differs from the same line of <b>
static std::string firstDifferentLine(const std::string& a, const std::string& b)
{
    std::istringstream sa(a), sb(b);
    std::string        la, lb;
    while (std::getline(sa, la)) {
        if (!std::getline(sb, lb) || la != lb) {
            return la;
        }
    }
    return "(end of text)";
}

int main()
{
#ifdef FLUSH_MODE
    std::vector<std::string> reference = compile();

    setFlushMode();
    volatile double subnormal = 1e-310;
    if (!hasFlushMode() || subnormal * 1.0 != 0.0) {
        std::cerr << "cannot set " FLUSH_MODE "\n";
        return 1;
    }
    std::vector<std::string> flushed  = compile();
    bool                     restored = hasFlushMode();
    if (!restored) {
        std::cerr << "the caller's " FLUSH_MODE " mode is not restored\n";
    }

    std::size_t same = 0;
    for (std::size_t i = 0; i < reference.size(); i++) {
        if (flushed[i] == reference[i]) {
            same++;
        } else {
            std::cerr << "result " << i << " differs with " FLUSH_MODE ":\n  "
                      << firstDifferentLine(flushed[i], reference[i]) << "\ninstead of\n  "
                      << firstDifferentLine(reference[i], flushed[i]) << "\n";
        }
    }
    std::cout << "with " FLUSH_MODE ": " << same << "/" << reference.size()
              << " compilation results identical to the default environment\n";
    return (restored && same == reference.size()) ? 0 : 1;
#else
    std::cout << "no flush-to-zero mode known on this machine: test skipped\n";
    return 0;
#endif
}
