// Smoke test of a libfaust build with the LLVM backend (see libfaust.yml).
//
//   libfaust-smoke run           compile a DSP with LLVM and run it
//   libfaust-smoke write <file>  same, then save it as machine code
//   libfaust-smoke read <file>   load the machine code and run it
//
// 'write' and 'read' run in two processes, so that loading machine code is
// tested in a process where no DSP was compiled before: that path
// initializes the LLVM targets on its own.

#include <cmath>
#include <cstdio>
#include <string>

#include "faust/dsp/llvm-dsp.h"

// y(n) = 1 + 0.5 * y(n-1)
static const char* kCode = "process = 1 : + ~ *(0.5);";

static bool check(llvm_dsp_factory* factory, const char* what)
{
    dsp* d = factory->createDSPInstance();
    if (!d) {
        std::fprintf(stderr, "%s: no DSP instance\n", what);
        return false;
    }
    d->init(44100);
    FAUSTFLOAT  out[4] = {0, 0, 0, 0};
    FAUSTFLOAT* outs[1] = {out};
    d->compute(4, nullptr, outs);
    delete d;

    const double expected[4] = {1.0, 1.5, 1.75, 1.875};
    for (int i = 0; i < 4; i++) {
        if (std::fabs(double(out[i]) - expected[i]) > 1e-6) {
            std::fprintf(stderr, "%s: sample %d is %g, expected %g\n", what, i, double(out[i]), expected[i]);
            return false;
        }
    }
    std::printf("%s: OK (%s)\n", what, getDSPMachineTarget().c_str());
    return true;
}

int main(int argc, char* argv[])
{
    std::string mode = (argc > 1) ? argv[1] : "run";
    std::string path = (argc > 2) ? argv[2] : "";
    if ((mode != "run" && path.empty()) || (mode != "run" && mode != "write" && mode != "read")) {
        std::fprintf(stderr, "usage: %s run | write <file> | read <file>\n", argv[0]);
        return 2;
    }

    std::string       error;
    llvm_dsp_factory* factory = nullptr;
    if (mode == "read") {
        factory = readDSPFactoryFromMachineFile(path, "", error);
    } else {
        factory = createDSPFactoryFromString("smoke", kCode, 0, nullptr, "", error, -1);
    }
    if (!factory) {
        std::fprintf(stderr, "%s: %s\n", mode.c_str(), error.c_str());
        return 1;
    }

    bool ok = check(factory, mode.c_str());
    if (ok && mode == "write" && !writeDSPFactoryToMachineFile(factory, path, "")) {
        std::fprintf(stderr, "write: cannot write %s\n", path.c_str());
        ok = false;
    }
    deleteDSPFactory(factory);
    return ok ? 0 : 1;
}
