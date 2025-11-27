/**
 * JS equivalents of selected samples from tools/benchmark/signal-tester.cpp.
 * Assumes the Emscripten-generated module is available as `createFaustModule`.
 *
 * Usage:
 *   import createFaustModule from './faust-wasm.js';
 *   import { runSignalExamples } from './examples/signal-tester.js';
 *
 *   const Module = await createFaustModule();
 *   await runSignalExamples(Module);
 */

async function emitCpp(Module, name, signals, args = []) {
    const res = Module.createSourceFromSignals(name, signals, "cpp", args);
    if (res.error) throw new Error(res.error);
    return res.source;
}

function SR(Module) {
    return Module.sigMin(
        Module.sigReal(192000.0),
        Module.sigMax(
            Module.sigReal(1.0),
            Module.sigFConst(Module.SType.kSInt, "fSamplingFreq", "<math.h>")
        )
    );
}

function BS(Module) { return Module.sigFVar(Module.SType.kSInt, "count", "<math.h>"); }

function SINH(Module) {
    const args = new Module['vector<CTree*>']();
    args.push_back(Module.sigInput(0));
    return Module.sigFFun(
        Module.SType.kSReal,
        ["sinhf", "sinh", "sinhl", "sinhfx"],
        [Module.SType.kSReal],
        "<FOO.h>",
        "",
        args
    );
}

function decimalpart(Module, x) { return Module.sigSub(x, Module.sigIntCast(x)); }

function phasor(Module, f) {
    return Module.sigRecursion(
        decimalpart(Module, Module.sigAdd(Module.sigSelf(), Module.sigDiv(f, SR(Module)))))
}

function osc(Module, f) {
    return Module.sigSin(
        Module.sigMul(
            phasor(Module, f),
            Module.sigMul(Module.sigReal(2.0), Module.sigReal(3.141592653))
        )
    );
}

export async function runSignalExamples(Module) {
    Module.createLibContext();
    try {
        // test0: foreign function
        {
            const sigs = new Module['vector<CTree*>']();
            sigs.push_back(SINH(Module));
            console.log(await emitCpp(Module, "sig-test0", sigs));
        }

        // test2: _ <: +(0.5), *(1.5)
        {
            const sigs = new Module['vector<CTree*>']();
            const x = Module.sigInput(0);
            sigs.push_back(Module.sigAdd(x, Module.sigReal(0.5)));
            sigs.push_back(Module.sigMul(x, Module.sigReal(1.5)));
            console.log(await emitCpp(Module, "sig-test2", sigs));
        }

        // test4: _ <: @(500)+0.5, @(3000)*1.5
        {
            const sigs = new Module['vector<CTree*>']();
            const x = Module.sigInput(0);
            sigs.push_back(Module.sigAdd(Module.sigDelay(x, Module.sigInt(500)), Module.sigReal(0.5)));
            sigs.push_back(Module.sigMul(Module.sigDelay(x, Module.sigInt(3000)), Module.sigReal(1.5)));
            console.log(await emitCpp(Module, "sig-test4", sigs));
        }

        // normal form and intervals
        {
            const sigs = new Module['vector<CTree*>']();
            const s1 = Module.sigAdd(
                Module.sigAdd(Module.sigDelay(Module.sigDelay(Module.sigInput(0), Module.sigReal(500)), Module.sigReal(200)), Module.sigReal(0.5)),
                Module.sigReal(3)
            );
            const s2 = Module.sigMul(Module.sigMul(Module.sigDelay(Module.sigInput(0), Module.sigInt(500)), Module.sigReal(0.5)), Module.sigReal(4));
            sigs.push_back(s1);
            sigs.push_back(s2);

            // intervals
            const i3 = { fLo: 0, fHi: 0, fLSB: 48 };
            const i4 = { fLo: -10, fHi: 10, fLSB: 48 };
            Module.setSigInterval(s1, i3);
            Module.setSigInterval(s2, i4);

            console.log(await emitCpp(Module, "sig-intervals", sigs));

            const nf = Module.simplifyToNormalForm2(sigs);
            console.log("normal form count:", nf.size ? nf.size() : nf.length);
        }

        // test8: slider * delayed add
        {
            const sigs = new Module['vector<CTree*>']();
            const x = Module.sigInput(0);
            const slider = Module.sigVSlider("Vol", Module.sigReal(0.5), Module.sigReal(0.0), Module.sigReal(1.0), Module.sigReal(0.01));
            sigs.push_back(Module.sigMul(slider, Module.sigDelay(Module.sigAdd(x, Module.sigReal(0.5)), Module.sigInt(500))));
            console.log(await emitCpp(Module, "sig-test8", sigs));
        }

        // test10: recursion + ~ _
        {
            const sigs = new Module['vector<CTree*>']();
            const in1 = Module.sigInput(0);
            sigs.push_back(Module.sigRecursion(Module.sigAdd(Module.sigSelf(), in1)));
            console.log(await emitCpp(Module, "sig-test10", sigs));
        }

        // test12: waveform {0,100,200,300,400}
        {
            const wf = new Module['vector<CTree*>']();
            [0, 100, 200, 300, 400].forEach(v => wf.push_back(Module.sigReal(v)));
            const sigs = new Module['vector<CTree*>']();
            sigs.push_back(Module.sigInt(wf.size ? wf.size() : wf.length));
            sigs.push_back(Module.sigWaveform(wf));
            console.log(await emitCpp(Module, "sig-test12", sigs));
        }

        // test17: phasor(440)
        {
            const sigs = new Module['vector<CTree*>']();
            sigs.push_back(phasor(Module, Module.sigReal(440.0)));
            console.log(await emitCpp(Module, "sig-test17", sigs));
        }

        // test19: soundfile helpers
        {
            const sigs = new Module['vector<CTree*>']();
            const sf = Module.sigSoundfile("sound[url:{'tango.wav'}]");
            const ridx = Module.sigInt(0);
            const part = Module.sigInt(0);
            const wridx = Module.sigIntCast(Module.sigMax(Module.sigInt(0),
                Module.sigMin(ridx, Module.sigSub(Module.sigSoundfileLength(sf, Module.sigInt(0)), Module.sigInt(1)))));
            sigs.push_back(Module.sigSoundfileLength(sf, part));
            sigs.push_back(Module.sigSoundfileRate(sf, part));
            sigs.push_back(Module.sigSoundfileBuffer(sf, Module.sigInt(0), part, wridx));
            sigs.push_back(Module.sigSoundfileBuffer(sf, Module.sigInt(1), part, wridx));
            console.log(await emitCpp(Module, "sig-test19", sigs));
        }

        // test20/test21: tables
        {
            const sigs = new Module['vector<CTree*>']();
            sigs.push_back(Module.sigReadOnlyTable(Module.sigInt(10), Module.sigInt(1), Module.sigIntCast(Module.sigInput(0))));
            console.log(await emitCpp(Module, "sig-test20", sigs));
        }
        {
            const sigs = new Module['vector<CTree*>']();
            sigs.push_back(Module.sigWriteReadTable(
                Module.sigInt(10), Module.sigInt(1),
                Module.sigIntCast(Module.sigInput(0)),
                Module.sigIntCast(Module.sigInput(1)),
                Module.sigIntCast(Module.sigInput(2))
            ));
            console.log(await emitCpp(Module, "sig-test21", sigs));
        }

        // test25: DSPToBoxes -> boxesToSignals -> createSourceFromSignals
        {
            const langs = ["c", "cpp", "cmajor", "codebox", "csharp", "dlang", "fir", "interp", "jax", "jsfx", "julia", "rust", "wast"];
            const dsp = 'import("stdfaust.lib"); process = os.osc(440);';
            for (const lang of langs) {
                const boxRes = Module.DSPToBoxes("FaustDSP", dsp, []);
                if (!boxRes.box || boxRes.error) continue;
                const sigRes = Module.boxesToSignals(boxRes.box);
                if (sigRes.error || !sigRes.signals) continue;
                const src = Module.createSourceFromSignals("FaustDSP", sigRes.signals, lang, []);
                if (!src.error) console.log(`${lang}: ${src.source.slice(0, 80)}...`);
            }
        }
    } finally {
        Module.destroyLibContext();
    }
}
