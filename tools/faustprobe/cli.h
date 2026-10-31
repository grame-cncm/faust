/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// The command line. A usage error exits with status 2, any other failure with
// status 1: a command that was not understood is not a program that failed.

#ifndef __faustprobe_cli__
#define __faustprobe_cli__

#include <set>
#include <string>
#include <vector>

#include "poly.h"
#include "text.h"
#include "train.h"

enum class Format { Csv, Ir, Json };
enum class ProtocolKind { Free, ImpulseTest };
enum class FdWhere { Start, End, Both };

// The compiler options, spelled as faust takes them. Those that differ from
// their default reach every compilation of the run.
struct CompileOptions {
    bool        isDouble = false;
    std::string processName = "process";
    bool        vec = false;
    Optional<std::string> vs, lv, scheduling, mcd, dlt, checkTable, ftz;
    bool externalControl = false;
    bool oneSample       = false;
    bool memoryManager   = false;

    // As the libfaust argv spells them, less the precision.
    std::vector<std::string> argv() const;
};

struct Args {
    bool                     determinismWorker = false;
    std::string              file;
    std::vector<std::string> evals;
    std::vector<std::string> importDirs;
    int                      optLevel = 0;
    int                      sr       = 44100;
    size_t                   block    = 64;
    size_t                   render   = 15000;
    std::vector<std::string> sets;
    bool                     clamp = false;
    std::string              input = "impulse";
    size_t                   skip  = 0;
    size_t                   every = 1;
    bool                     listParams = false;
    bool                     bargraphs  = false;
    bool                     quiet      = false;
    Optional<std::string>    precision;
    Optional<std::string>    out;
    Optional<std::string>    compare;
    Optional<std::string>    reference;
    std::vector<std::string> setA, setB;
    Optional<double>         tolerance, relTolerance;
    std::vector<size_t>      compareOutputs;
    std::vector<std::string> checks;
    Optional<double>         failAbove;
    Format                   format = Format::Csv;
    std::vector<std::string> sweeps;
    Optional<std::string>    points;
    Optional<std::string>    reduce;
    Optional<double>         f0;
    Optional<std::string>    describe;
    double                   describeHop = 0.01;
    size_t                   describeFft = 2048;
    std::vector<std::string> ats;  // FRAME, PATH=VALUE, FRAME, PATH=VALUE...
    std::vector<std::string> notes, chords;
    ProtocolKind             protocol = ProtocolKind::Free;
    size_t                   nvoices  = 0;
    Optional<std::string>    effect;
    double                   voiceStopLevel = kDefaultVoiceStopLevel;
    std::vector<std::string> train;
    size_t                   lossLane = 0;
    size_t                   gradLane = 1;
    OptimizerKind            optimizer = OptimizerKind::Adam;
    double                   lr     = 0.01;
    size_t                   blocks = 100;
    bool                     resetPerBlock = false;
    Optional<FdWhere>        fdCheck;
    double                   fdStep      = 1e-3;
    double                   fdTolerance = 0.02;
    bool                     trainVerbose = false;
    bool                     time = false;
    Optional<std::string>    freqresp;
    size_t                   settle = 0;
    Optional<double>         linearityTolerance;
    Optional<std::string>    svg;
    Optional<size_t>         fold, foldComplexity, maxNameSize;
    bool                     simplifyDiagrams = false;
    bool                     scaledSvg        = false;
    bool                     shadowBlur       = false;
    bool                     drawRouteFrame   = false;
    CompileOptions           compile;

    // The long names of the flags that were given.
    std::set<std::string> given;
};

// Parses the command line; prints and exits on --help, --version and a usage error.
Args parseArgs(int argc, char* argv[]);

// Refuses the first flag that was given, with the message made of it: what a
// mode does not take is an error, never a flag that is ignored.
struct Refusal {
    std::string flag;
    bool        given;
};
void refuse(const std::vector<Refusal>& conflicts, const std::string& before, const std::string& after);

void rejectProtocolConflicts(const Args& args);
bool verificationRequested(const Args& args);

#endif
