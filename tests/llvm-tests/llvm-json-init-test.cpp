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

// Check what the LLVM backend reads back from its own JSON description, and
// FAUST_LLVM_RELOAD. FAUST_LLVM_RELOAD is read when the JIT is built, and the factory
// cache does not know about it: each factory is deleted before the next one is asked for.
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "faust/dsp/llvm-dsp.h"

static void require(bool condition, const std::string& message)
{
    if (!condition) throw std::runtime_error(message);
}

class Factory {
   public:
    Factory(const std::string& source, std::vector<const char*> options, int opt_level)
    {
        std::string error;
        fFactory = createDSPFactoryFromString("test", source, int(options.size()),
                                              options.data(), "", error, opt_level);
        require(fFactory != nullptr, "Factory creation failed: " + error);
    }
    explicit Factory(llvm_dsp_factory* factory) : fFactory(factory)
    {
        require(fFactory != nullptr, "No factory");
    }
    ~Factory() { deleteDSPFactory(fFactory); }

    llvm_dsp_factory* get() const { return fFactory; }

   private:
    Factory(const Factory&);
    Factory&          operator=(const Factory&);
    llvm_dsp_factory* fFactory;
};

// Renders 'frames' frames, with no input, in the sample type of the compiled DSP.
template <typename REAL>
static std::vector<std::vector<REAL>> render(llvm_dsp* processor, int frames)
{
    std::vector<std::vector<REAL>> channels(processor->getNumOutputs(),
                                            std::vector<REAL>(frames));
    std::vector<REAL*> outputs;
    for (std::vector<REAL>& channel : channels) outputs.push_back(channel.data());
    processor->compute(frames, nullptr, reinterpret_cast<FAUSTFLOAT**>(outputs.data()));
    return channels;
}

template <typename REAL>
static void checkValue(llvm_dsp_factory* factory, double expected, const std::string& what)
{
    std::unique_ptr<llvm_dsp> processor(factory->createDSPInstance());
    require(processor != nullptr, "DSP instance creation failed");
    processor->init(44100);
    require(render<REAL>(processor.get(), 1)[0][0] == REAL(expected), what + ": wrong init");
    processor->instanceResetUserInterface();
    require(render<REAL>(processor.get(), 1)[0][0] == REAL(expected), what + ": wrong reset");
}

// Each value needs all 17 digits. The widgets take it from the JSON of the factory.
static void checkWidgetInit()
{
    const double      values[] = {-0.9999990463256836, 0.30000000000000004, 1.0 / 3.0,
                                  1.0000000000000002, 1.0e-300};
    const char* const widgets[] = {"hslider", "vslider", "nentry"};
    int               checks = 0;
    for (double value : values) {
        for (const char* widget : widgets) {
            char source[256];
            std::snprintf(source, sizeof(source), "process = %s(\"v\", %.17g, -2, 2, 1e-9);",
                          widget, value);
            const std::string what(source);
            {
                Factory factory(source, {"-double"}, 0);
                checkValue<double>(factory.get(), value, what);
            }
            {
                Factory factory(source, {"-single"}, 0);
                checkValue<float>(factory.get(), value, what + " -single");
            }
            ++checks;
        }
    }
    std::cout << "PASS widget init: " << checks << "\n";
}

// The JSON travels with the bitcode, and comes back with its digits.
static void checkInitThroughBitcode()
{
    const char* source = "process = hslider(\"v\", -0.9999990463256836, -2, 2, 1e-9);";
    std::string bitcode;
    {
        Factory factory(source, {"-double"}, 0);
        bitcode = writeDSPFactoryToBitcode(factory.get());
    }
    std::string error;
    Factory     factory(readDSPFactoryFromBitcode(bitcode, "", error, 0));
    checkValue<double>(factory.get(), -0.9999990463256836, "bitcode");
    std::cout << "PASS init through bitcode\n";
}

// Folded to -1 at the instruction selection of the JIT on AArch64: the second output
// follows the first one in the correct code.
static const char* const kMiscompiled =
    "c = 1 : + ~ _;\n"
    "b = c < 10;\n"
    "d = 16 + 112*b;\n"
    "process = d, max(-1, d);\n";

static bool isCorrect(llvm_dsp_factory* factory)
{
    std::unique_ptr<llvm_dsp> processor(factory->createDSPInstance());
    require(processor != nullptr, "DSP instance creation failed");
    processor->init(44100);
    std::vector<std::vector<double>> channels = render<double>(processor.get(), 32);
    for (int i = 0; i < 32; ++i) {
        double expected = (i < 9) ? 128.0 : 16.0;
        if (channels[0][i] != expected || channels[1][i] != expected) return false;
    }
    return true;
}

static void checkReload()
{
    const int levels[] = {0, 1, -1};

    unsetenv("FAUST_LLVM_RELOAD");
    {
        Factory factory(kMiscompiled, {"-double"}, 0);
        std::cout << "INFO without FAUST_LLVM_RELOAD the JIT at -O0 is "
                  << (isCorrect(factory.get()) ? "correct" : "miscompiling") << "\n";
    }
    setenv("FAUST_LLVM_RELOAD", "1", 1);
    for (int level : levels) {
        Factory factory(kMiscompiled, {"-double"}, level);
        require(isCorrect(factory.get()), "Miscompiled at level " + std::to_string(level));
    }
    unsetenv("FAUST_LLVM_RELOAD");
    std::cout << "PASS reload at every level\n";
}

// State, tables and widgets go through the reload: same samples with and without it.
static void checkReloadKeepsTheProgram()
{
    const char* source =
        "t = waveform{0.25, 0.5, 0.75, 1.0};\n"
        "i = (+(1) ~ _) : %(4);\n"
        "process = (t, i : rdtable) * hslider(\"g\", 0.3, 0, 1, 0.01) : + ~ (@(7) : *(0.5));\n";
    std::vector<std::vector<double>> references[2];
    for (int reload = 0; reload < 2; ++reload) {
        if (reload) setenv("FAUST_LLVM_RELOAD", "1", 1);
        Factory                   factory(source, {"-double"}, 3);
        std::unique_ptr<llvm_dsp> processor(factory.get()->createDSPInstance());
        require(processor != nullptr, "DSP instance creation failed");
        processor->init(44100);
        references[reload] = render<double>(processor.get(), 1024);
        unsetenv("FAUST_LLVM_RELOAD");
    }
    require(references[0] == references[1], "The reload changed the samples");
    std::cout << "PASS reload keeps the program\n";
}

// crossCompile() comes back to the JIT with a JIT in place. The factory has to compile
// and to work afterwards. That the reload stays out of it, the JIT owning the module, does
// not show here: deleting that module anyway goes unnoticed without a memory sanitizer.
static void checkCrossCompileWithReload(const std::string& object_path)
{
    setenv("FAUST_LLVM_RELOAD", "1", 1);
    {
        Factory     factory(kMiscompiled, {"-double"}, 0);
        std::string target = getDSPMachineTarget();
        target = target.substr(0, target.rfind(':')) + ":generic";
        require(writeDSPFactoryToObjectcodeFile(factory.get(), object_path, target),
                "Cross compilation failed for " + target);
        std::ifstream object(object_path.c_str(), std::ios::binary | std::ios::ate);
        require(object && object.tellg() > 0, "Empty object file");
        require(isCorrect(factory.get()), "Miscompiled after the cross compilation");
    }
    unsetenv("FAUST_LLVM_RELOAD");
    std::remove(object_path.c_str());
    std::cout << "PASS cross compilation with reload\n";
}

int main(int argc, char* argv[])
{
    std::string object_path = (argc > 1) ? argv[1] : "/tmp/faust-llvm-json-init-test.o";
    try {
        checkWidgetInit();
        checkInitThroughBitcode();
        checkReload();
        checkReloadKeepsTheProgram();
        checkCrossCompileWithReload(object_path);
    } catch (const std::exception& e) {
        std::cerr << "FAIL: " << e.what() << "\n";
        return 1;
    }
    std::cout << "PASS llvm-json-init\n";
    return 0;
}
