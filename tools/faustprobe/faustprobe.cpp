/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// faustprobe: compile a Faust program with the LLVM JIT, set its controls from
// the command line, render it offline, and print numbers. It answers what
// reading a program does not: does it compile, what does it output, is it
// finite, how does it move with this control. See README.md.

#include <pthread.h>

#include <cstdio>
#include <cstdlib>
#include <string>

#include "report.h"

// Chooses the mode the command line asks for, after the checks that concern
// more than one of them.
static void run(Args args)
{
    bool impulseTest = args.protocol == ProtocolKind::ImpulseTest;
    if (impulseTest) {
        // Defaults are the reference values already, so only an explicitly
        // conflicting flag is an error. --format ir is implied.
        if (args.format == Format::Csv) {
            args.format = Format::Ir;
        }
        rejectProtocolConflicts(args);
    }
    if (args.effect && args.nvoices == 0) {
        throw Failure("--effect requires --nvoices > 0");
    }
    if (args.trainVerbose && args.train.empty()) {
        throw Failure("--train-verbose adds the gradients to the rows of --train");
    }
    if (args.compile.externalControl || args.compile.oneSample) {
        std::vector<std::string> given;
        if (args.compile.externalControl) {
            given.push_back("-ec");
        }
        if (args.compile.oneSample) {
            given.push_back("-os");
        }
        throw Failure(join(given, " and ") + " compile a `control` or `frame` entry point, and this tool runs `compute`");
    }
    if (args.compile.memoryManager) {
        throw Failure("-mem0 needs a memory manager from the host, which a probe does not supply");
    }
    if (args.compile.processName != "process" && !args.evals.empty()) {
        throw Failure("--process-name cannot be combined with --eval: the expressions are the program");
    }
    if (args.svg) {
        runSvg(args);
        return;
    }
    if (args.nvoices > 0) {
        runPoly(args);
        return;
    }
    if (!args.train.empty() || args.fdCheck) {
        runTrain(args);
        return;
    }
    if (args.linearityTolerance && !args.freqresp) {
        throw Failure("--linearity-tolerance is the tolerance of --freqresp's checks");
    }
    if (args.settle != 0 && !args.freqresp) {
        throw Failure("--settle delays the impulse of --freqresp; a plain render has --skip");
    }
    if (args.freqresp) {
        runFreqresp(args);
        return;
    }
    runRender(args, impulseTest);
}

// What the worker thread is given and answers.
struct Worker {
    Args args;
    int  status = 0;
};

// The body of the worker: a failure ends here, with its message and exit status 1.
// stdout is flushed first, so that what the run printed comes before the verdict.
static void* work(void* data)
{
    Worker* worker = static_cast<Worker*>(data);
    try {
        if (worker->args.determinismWorker) {
            determinismWorker(worker->args);
        } else {
            run(worker->args);
        }
    } catch (const std::exception& error) {
        fflush(stdout);
        fprintf(stderr, "faustprobe: %s\n", error.what());
        worker->status = 1;
    }
    return nullptr;
}

// Parses the command line on the main thread, runs on a worker with a large stack.
int main(int argc, char* argv[])
{
    // By default libfaust marks every floating-point call of its LLVM IR
    // 'fast', and from -O1 up LLVM then computes pow(C, x) as exp2(log2(C) * x):
    // pow(53, 1) is 52.999999999999986, and a delay length made from it loses a
    // sample. A probe owes the samples of the program, so a FAUST_OPT of the
    // user's own takes precedence, and nothing else does.
    setenv("FAUST_OPT", "FAUST_LLVM_NO_FM", 0);

    Worker worker;
    try {
        worker.args = parseArgs(argc, argv);
    } catch (const std::exception& error) {
        fprintf(stderr, "faustprobe: %s\n", error.what());
        return 1;
    }
    // the compiler recurses deeply: run on a large stack
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_attr_setstacksize(&attributes, 256 * 1024 * 1024);
    pthread_t thread;
    if (pthread_create(&thread, &attributes, work, &worker) != 0) {
        fprintf(stderr, "faustprobe: cannot start the worker thread\n");
        return 1;
    }
    pthread_join(thread, nullptr);
    fflush(stdout);
    return worker.status;
}
