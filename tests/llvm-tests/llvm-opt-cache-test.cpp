// Check LLVM optimization and cache identity while all factories remain alive.
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/libfaust-signal.h"

// Use the exported C target accessor; the C++ inline getter has no standalone
// symbol in some shared-library builds. Returned strings belong to libfaust.
extern "C" LIBFAUST_API char* getCTarget(llvm_dsp_factory* factory);
extern "C" LIBFAUST_API void freeCMemory(void* pointer);

static std::string targetOf(llvm_dsp_factory* factory)
{
    char* target = getCTarget(factory);
    if (!target) throw std::runtime_error("Missing factory target");
    std::string result(target);
    freeCMemory(target);
    return result;
}

#ifndef LLVM_TEST_MAX_LEVEL
#define LLVM_TEST_MAX_LEVEL 3
#endif

static void require(bool condition, const std::string& message)
{
    if (!condition) throw std::runtime_error(message);
}

struct Factories {
    std::vector<llvm_dsp_factory*> held;
    llvm_dsp_factory* keep(llvm_dsp_factory* factory, const std::string& error)
    {
        require(factory != nullptr, "Factory creation failed: " + error);
        held.push_back(factory);
        return factory;
    }
    ~Factories()
    {
        for (auto it = held.rbegin(); it != held.rend(); ++it) deleteDSPFactory(*it);
    }
};

static int audioChecks = 0;

static void checkAudio(llvm_dsp_factory* factory)
{
    std::unique_ptr<llvm_dsp> processor(factory->createDSPInstance());
    require(processor != nullptr, "DSP instance creation failed");
    processor->init(44100);
    require(processor->getNumInputs() == 1 && processor->getNumOutputs() == 1,
            "Unexpected DSP dimensions");
    FAUSTFLOAT input[128], output[128];
    for (int i = 0; i < 128; ++i) input[i] = FAUSTFLOAT((i % 17 - 8) * 0.125);
    FAUSTFLOAT* inputs[] = {input};
    FAUSTFLOAT* outputs[] = {output};
    processor->compute(64, inputs, outputs);
    inputs[0] += 64;
    outputs[0] += 64;
    processor->compute(64, inputs, outputs);
    for (int i = 0; i < 128; ++i) {
        FAUSTFLOAT previous = i ? input[i - 1] : FAUSTFLOAT(0);
        require(output[i] == input[i] + previous, "Wrong audio sample " + std::to_string(i));
    }
    ++audioChecks;
}

static void checkLevels(llvm_dsp_factory* zero, llvm_dsp_factory* three,
                        const std::string& label)
{
    require(zero != three, label + ": optimization levels share a factory");
    require(zero->getSHAKey() != three->getSHAKey(), label + ": optimization levels share a SHA");
    std::string ir0 = writeDSPFactoryToIR(zero);
    std::string ir3 = writeDSPFactoryToIR(three);
    require(!ir0.empty() && !ir3.empty() && ir0 != ir3,
            label + ": O0 and O3 produce identical IR");
    checkAudio(zero);
    checkAudio(three);
    std::cout << "PASS " << label << ": distinct factories/IR; 256 audio samples compared\n";
}

int main()
{
    try {
        Factories factories;
        const char* options[] = {"-cn", "CacheDSP"};
        const std::string source = "process = _ <: _, @(1) : +;";
        const std::string native = getDSPMachineTarget();
        const std::string triple = native.substr(0, native.find(':'));
        const std::string generic = triple + ":generic";
        std::cout << "Targets under test: " << native << " / " << generic << '\n';
        std::string error;
        auto fromString = [&](const std::string& name, int level, const std::string& target) {
            auto* factory = createDSPFactoryFromString(name, source, 2, options, target, error, level);
            return factories.keep(factory, error);
        };
        auto* zero = fromString("CacheTest", 0, "");
        auto* three = fromString("CacheTest", 3, "");
        checkLevels(zero, three, "String 0 then 3");
        require(fromString("CacheTest", 0, "") == zero, "Repeated O0 request missed cache");
        require(fromString("CacheTest", 3, "") == three, "Repeated O3 request missed cache");
        require(fromString("CacheTest", 0, native) == zero, "Default/native targets do not alias");
        require(fromString("CacheTest", 0, triple) == zero, "Implicit host CPU does not alias");
        require(targetOf(zero) == native, "Factory does not report effective target");
        auto* maximum = fromString("CacheTest", -1, "");
        require(fromString("CacheTest", LLVM_TEST_MAX_LEVEL, "") == maximum,
                "Equivalent maximum levels do not alias");
        auto* other = fromString("CacheTest", 0, generic);
        require((other != zero) == (generic != native)
                    && (other->getSHAKey() != zero->getSHAKey()) == (generic != native),
                "Target cache identity does not match effective CPU");
        require(targetOf(other) == generic, "Wrong generic target");
        checkAudio(other);
        require(factories.keep(getDSPFactoryFromSHAKey(zero->getSHAKey()), error) == zero,
                "Factory SHA lookup failed");
        auto* reverse3 = fromString("ReverseTest", 3, "");
        auto* reverse0 = fromString("ReverseTest", 0, "");
        checkLevels(reverse0, reverse3, "String 3 then 0");

        const std::string ir = writeDSPFactoryToIR(zero);
        const std::string bitcode = writeDSPFactoryToBitcode(zero);
        for (bool binary : {false, true}) {
            auto read = [&](int level, const std::string& target) {
                auto* factory = binary ? readDSPFactoryFromBitcode(bitcode, target, error, level)
                                       : readDSPFactoryFromIR(ir, target, error, level);
                return factories.keep(factory, error);
            };
            auto* read0 = read(0, "");
            auto* read3 = read(3, "");
            checkLevels(read0, read3, binary ? "Bitcode" : "IR");
            require(read(0, native) == read0 && read(3, "") == read3, "Read cache reuse failed");
            require(read(-1, "") == read(LLVM_TEST_MAX_LEVEL, ""), "Read maximum alias failed");
            auto* genericFactory = read(0, generic);
            require((genericFactory != read0) == (generic != native)
                        && targetOf(genericFactory) == generic,
                    "Read cache ignored target");
            checkAudio(genericFactory);
        }

        createLibContext();
        Signal input = sigInput(0);
        Signal delay = sigInt(1);
        Signal delayed = sigDelay(input, delay);
        Signal output = sigAdd(input, delayed);
        std::vector<Signal> signals{output};
        auto fromSignals = [&](int level) {
            auto* factory = createDSPFactoryFromSignals("SignalTest", signals, 2, options,
                                                        "", error, level);
            return factories.keep(factory, error);
        };
        auto* signal0 = fromSignals(0);
        auto* signal3 = fromSignals(3);
        // Signals factories have no source cache key; check their actual emitted IR.
        require(writeDSPFactoryToIR(signal0) != writeDSPFactoryToIR(signal3),
                "Signals O0 and O3 produce identical IR");
        checkAudio(signal0);
        checkAudio(signal3);
        checkAudio(fromSignals(-1));
        require(createDSPFactoryFromSignals("Invalid", signals, 2, options, "", error, -2)
                    == nullptr && !error.empty(), "Invalid Signals level accepted");
        destroyLibContext();
        require(createDSPFactoryFromString("Invalid", source, 2, options, "", error, -2)
                    == nullptr && !error.empty(), "Invalid String level accepted");
        require(readDSPFactoryFromIR(ir, "", error, -2) == nullptr && !error.empty(),
                "Invalid IR level accepted");
        require(readDSPFactoryFromBitcode(bitcode, "", error, -2) == nullptr && !error.empty(),
                "Invalid bitcode level accepted");
        std::cout << "PASS Signals: O0/O3 IR, 384 audio samples; invalid levels rejected\n"
                  << "PASS cache reuse, target isolation, maximum aliases and SHA lookup\n"
                  << "Compared " << audioChecks << " DSP instances, " << audioChecks * 128
                  << " audio samples\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL LLVM optimization/cache test: " << error.what() << '\n';
        return 1;
    }
}
