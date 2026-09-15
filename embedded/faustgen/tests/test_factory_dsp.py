"""Tests for DSP factory selection, sample adaptation, and polyphony."""

import tempfile
import unittest

from cpp_test_support import FACTORY_SOURCE, compile_and_run, definitions


STUBS = r'''
#include <cassert>
#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define INTERP_BACKEND_NAME "interpreter"
#define DEFAULT_CODE "process = 0,0;"

vector<string> posts;
void post(const char* format, ...) {
    char text[512];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(text, sizeof(text), format, arguments);
    va_end(arguments);
    posts.push_back(text);
}

struct Meta {
    virtual ~Meta() = default;
    virtual void declare(const char*, const char*) = 0;
};

struct dsp {
    int inputs;
    int outputs;
    map<string, string> metadata_values;
    explicit dsp(int ins = 0, int outs = 0, map<string, string> metadata = {})
        : inputs(ins), outputs(outs), metadata_values(std::move(metadata)) {}
    virtual ~dsp() = default;
    virtual int getNumInputs() { return inputs; }
    virtual int getNumOutputs() { return outputs; }
    virtual void metadata(Meta* meta) {
        for (const auto& item : metadata_values) meta->declare(item.first.c_str(), item.second.c_str());
    }
};

struct dsp_factory {
    int inputs = 0;
    int outputs = 0;
    map<string, string> metadata_values;
    int creations = 0;
    dsp_factory(int ins = 0, int outs = 0, map<string, string> metadata = {})
        : inputs(ins), outputs(outs), metadata_values(std::move(metadata)) {}
    virtual ~dsp_factory() = default;
    virtual dsp* createDSPInstance() {
        ++creations;
        return new dsp(inputs, outputs, metadata_values);
    }
};

template <typename Internal, typename External>
struct dsp_sample_adapter : dsp {
    dsp* owned;
    explicit dsp_sample_adapter(dsp* value)
        : dsp(value->getNumInputs(), value->getNumOutputs()), owned(value) {}
    ~dsp_sample_adapter() override { delete owned; }
};

struct mydsp_poly : dsp {
    dsp* owned;
    int voices;
    mydsp_poly(dsp* value, int count, bool)
        : dsp(value->getNumInputs(), value->getNumOutputs()), owned(value), voices(count) {}
    ~mydsp_poly() override { delete owned; }
};

struct MyMeta : Meta, map<string, string> {
    void declare(const char* key, const char* value) override { (*this)[key] = value; }
    const string get(const char* key, const char* fallback) {
        return count(key) ? (*this)[key] : fallback;
    }
};

struct FaustPluginMeta : Meta {
    explicit FaustPluginMeta(dsp* value) { value->metadata(this); }
    void declare(const char* key, const char* value) override {
        if (string(key) == "name" || string(key) == "author") post("%s : %s", key, value);
    }
};

string getTarget() { return "test-target"; }
dsp_factory* default_factory = nullptr;
int default_compilations = 0;
dsp_factory* createDSPFactoryFromString(const string&, const string&, int, const char* const*,
                                        const string&, string&, int) {
    ++default_compilations;
    return default_factory;
}
dsp_factory* createInterpreterDSPFactoryFromString(const string&, const string&, int,
                                                   const char* const*, string&) {
    ++default_compilations;
    return default_factory;
}

class faustgen_factory {
public:
    enum sampleFormat { kFloat, kDouble, kNone };
    dsp_factory* fDSPfactory = nullptr;
    dsp_factory* bitcode_result = nullptr;
    dsp_factory* source_result = nullptr;
    int bitcode_attempts = 0;
    int source_attempts = 0;
    long fBitCodeSize = 0;
    long fSourceCodeSize = 0;
    sampleFormat fSampleFormat = kNone;
    int m_siginlets = 0;
    int m_sigoutlets = 0;
    int json_builds = 0;

    dsp_factory* create_factory_from_bitcode() { ++bitcode_attempts; return bitcode_result; }
    dsp_factory* create_factory_from_sourcecode() { ++source_attempts; return source_result; }
    dsp* create_dsp_instance(int = 0);
    dsp* create_dsp_aux();
    void make_json(dsp* value) {
        ++json_builds;
        assert(value->getNumInputs() == m_siginlets);
        assert(value->getNumOutputs() == m_sigoutlets);
    }
};
'''


CASES = r'''
static dsp* unwrap_poly(dsp* value, int expected_voices) {
    auto poly = dynamic_cast<mydsp_poly*>(value);
    assert(poly && poly->voices == expected_voices);
    return poly->owned;
}

int main() {
    // Explicit polyphony wraps the sample adapter, and both preserve I/O counts.
    dsp_factory voice_factory(2, 3, {{"nvoices", "9"}});
    faustgen_factory factory;
    factory.fDSPfactory = &voice_factory;
    factory.fSampleFormat = faustgen_factory::kFloat;
    dsp* explicit_poly = factory.create_dsp_instance(4);
    dsp* inner = unwrap_poly(explicit_poly, 4);
    assert((dynamic_cast<dsp_sample_adapter<float, double>*>(inner)));
    assert(explicit_poly->getNumInputs() == 2 && explicit_poly->getNumOutputs() == 3);
    delete explicit_poly;

    // nvoices metadata is used only when no explicit voice count is supplied.
    factory.fSampleFormat = faustgen_factory::kDouble;
    dsp* metadata_poly = factory.create_dsp_instance();
    assert(unwrap_poly(metadata_poly, 9));
    delete metadata_poly;

    dsp_factory negative_factory(1, 1, {{"nvoices", "-3"}});
    factory.fDSPfactory = &negative_factory;
    dsp* negative = factory.create_dsp_instance();
    assert(!dynamic_cast<mydsp_poly*>(negative));
    delete negative;

    dsp_factory invalid_factory(1, 1, {{"nvoices", "not-a-number"}});
    factory.fDSPfactory = &invalid_factory;
    dsp* invalid = factory.create_dsp_instance();
    assert(!dynamic_cast<mydsp_poly*>(invalid));
    delete invalid;

    // An already allocated factory has priority over every stored representation.
    dsp_factory allocated(4, 5);
    faustgen_factory existing;
    existing.fDSPfactory = &allocated;
    existing.fBitCodeSize = 10;
    existing.fSourceCodeSize = 10;
    dsp* from_existing = existing.create_dsp_aux();
    assert(from_existing->getNumInputs() == 4 && from_existing->getNumOutputs() == 5);
    assert(existing.bitcode_attempts == 0 && existing.source_attempts == 0);
    assert(existing.m_siginlets == 4 && existing.m_sigoutlets == 5 && existing.json_builds == 1);
    delete from_existing;

    // A valid cache wins over source compilation.
    dsp_factory cached(2, 6, {{"name", "cached"}});
    faustgen_factory cache;
    cache.fBitCodeSize = 10;
    cache.fSourceCodeSize = 20;
    cache.bitcode_result = &cached;
    dsp* from_cache = cache.create_dsp_aux();
    assert(cache.fDSPfactory == &cached);
    assert(cache.bitcode_attempts == 1 && cache.source_attempts == 0);
    assert(from_cache->getNumOutputs() == 6);
    delete from_cache;

    // A rejected cache falls through to source.
    dsp_factory compiled(7, 8, {{"author", "Faust"}});
    faustgen_factory source;
    source.fBitCodeSize = 10;
    source.fSourceCodeSize = 20;
    source.source_result = &compiled;
    dsp* from_source = source.create_dsp_aux();
    assert(source.fDSPfactory == &compiled);
    assert(source.bitcode_attempts == 1 && source.source_attempts == 1);
    assert(from_source->getNumInputs() == 7 && from_source->getNumOutputs() == 8);
    delete from_source;

    // If neither persisted form compiles, the silent 0-in/0-out fallback is used.
    dsp_factory fallback(0, 0);
    default_factory = &fallback;
    faustgen_factory failed;
    failed.fBitCodeSize = 10;
    failed.fSourceCodeSize = 20;
    dsp* from_fallback = failed.create_dsp_aux();
    assert(failed.fDSPfactory == &fallback);
    assert(failed.bitcode_attempts == 1 && failed.source_attempts == 1);
    assert(default_compilations == 1);
    assert(from_fallback->getNumInputs() == 0 && from_fallback->getNumOutputs() == 0);
    assert(failed.json_builds == 1);
    delete from_fallback;

    cout << "factory priority, fallback, format adaptation, and polyphony: OK\n";
}
'''


class FactoryDSPTest(unittest.TestCase):
    def test_dsp_creation_paths(self):
        methods = definitions(
            FACTORY_SOURCE.read_text(),
            (
                "::dsp* faustgen_factory::create_dsp_instance",
                "::dsp* faustgen_factory::create_dsp_aux",
            ),
        )
        with tempfile.TemporaryDirectory(prefix="faustgen-factory-dsp-") as temporary:
            for flags in ((), ("-DINTERP_BACKEND",)):
                with self.subTest(backend=flags or ("LLVM",)):
                    compile_and_run(
                        STUBS + methods + CASES,
                        temporary,
                        name="factory-dsp",
                        flags=flags,
                    )


if __name__ == "__main__":
    unittest.main()
