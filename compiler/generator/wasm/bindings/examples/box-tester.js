/**
 * JS equivalents of the native samples in tools/benchmark/box-tester.cpp.
 * Assumes the Emscripten-generated module is available as `createFaustModule`.
 *
 * Usage:
 *   import createFaustModule from './faust-wasm.js';
 *   import { runExamples } from './examples/box-tester.js';
 *
 *   const Module = await createFaustModule();
 *   await runExamples(Module);
 */

async function emitCpp(Module, name, box, args = []) {
    const res = Module.createSourceFromBoxes(name, box, "cpp", args);
    if (res.error) {
        throw new Error(res.error);
    }
    return res.source;
}

function SR(Module) {
    return Module.boxMin(
        Module.boxReal(192000.0),
        Module.boxMax(
            Module.boxReal(1.0),
            Module.boxFConst(Module.SType.kSInt, "fSamplingFreq", "<math.h>")
        )
    );
}

function BS(Module) { return Module.boxFVar(Module.SType.kSInt, "count", "<math.h>"); }

function decimalpart(Module) { return Module.boxSub(Module.boxWire(), Module.boxIntCast(Module.boxWire())); }

function phasor(Module, f) {
    return Module.boxSeq(
        Module.boxDiv(f, SR(Module)),
        Module.boxRec(Module.boxSplit(Module.boxAdd(), decimalpart(Module)), Module.boxWire())
    );
}

function osc(Module, f) {
    return Module.boxSin(
        Module.boxMul(
            Module.boxMul(Module.boxReal(2.0), Module.boxReal(3.141592653)),
            phasor(Module, f)
        )
    );
}

export async function runExamples(Module) {
    Module.createLibContext();
    try {
        // test0: foreign function
        const SINH = Module.boxFFun(
            Module.SType.kSReal,
            ["sinhf", "sinh", "sinhl", "sinhfx"],
            [Module.SType.kSReal],
            "<FOO.h>",
            ""
        );
        console.log(await emitCpp(Module, "test0", SINH));

        // test1: process = 7,3.14;
        console.log(await emitCpp(Module, "test1",
            Module.boxPar(Module.boxInt(7), Module.boxReal(3.14))));

        // test2: process = _,3.14 : +;
        console.log(await emitCpp(Module, "test2",
            Module.boxSeq(
                Module.boxPar(Module.boxWire(), Module.boxReal(3.14)),
                Module.boxAdd()
            )));

        // test3: process = +(_,3.14);
        console.log(await emitCpp(Module, "test3",
            Module.boxAdd(Module.boxWire(), Module.boxReal(3.14))));

        // test8: _ <: @(500)+0.5, @(3000)*1.5
        console.log(await emitCpp(Module, "test8",
            Module.boxSplit(
                Module.boxWire(),
                Module.boxPar(
                    Module.boxAdd(Module.boxDelay(Module.boxWire(), Module.boxReal(500)), Module.boxReal(0.5)),
                    Module.boxMul(Module.boxDelay(Module.boxWire(), Module.boxReal(3000)), Module.boxReal(1.5))
                )
            )));

        // test11: process = SR, BS
        console.log(await emitCpp(Module, "test11", Module.boxPar(SR(Module), BS(Module))));

        // test12: waveform {0,100,200,300,400}
        {
            const wf = new Module['vector<CTree*>']();
            [0, 100, 200, 300, 400].forEach(v => wf.push_back(Module.boxReal(v)));
            console.log(await emitCpp(Module, "test12", Module.boxWaveform(wf)));
        }

        // test14: _,_ <: !,_,_,! :> _,_;
        console.log(await emitCpp(Module, "test14",
            Module.boxSplit(
                Module.boxPar(Module.boxWire(), Module.boxWire()),
                Module.boxMerge(
                    Module.boxPar4(Module.boxCut(), Module.boxWire(), Module.boxWire(), Module.boxCut()),
                    Module.boxPar(Module.boxWire(), Module.boxWire())
                )
            )));

        // test16: phasor(440)
        console.log(await emitCpp(Module, "test16", phasor(Module, Module.boxReal(440))));

        // test18: soundfile
        console.log(await emitCpp(Module, "test18",
            Module.boxSoundfile("sound[url:{'tango.wav'}]", Module.boxInt(2), Module.boxInt(0), Module.boxInt(0))));

        // test25: DSPToBoxes -> multiple languages
        {
            const langs = ["c", "cpp", "cmajor", "codebox", "csharp", "dlang", "fir", "interp", "jax", "jsfx", "julia", "rust", "wast"];
            const dsp = 'import("stdfaust.lib"); process = os.osc(440);';
            for (const lang of langs) {
                const res = Module.DSPToBoxes("FaustDSP", dsp, []);
                if (!res.box || res.error) continue;
                const src = Module.createSourceFromBoxes("FaustDSP", res.box, lang, []);
                if (!src.error) {
                    console.log(`${lang}: ${src.source.slice(0, 80)}...`);
                }
            }
        }

        // test26: reuse DSPToBoxes result in another expression
        {
            const filter = Module.DSPToBoxes("FaustDSP", 'import("stdfaust.lib"); process = fi.lowpass(5);', []);
            if (filter.box && !filter.error) {
                const cutoff = Module.boxHSlider("cutoff",
                    Module.boxReal(300), Module.boxReal(100), Module.boxReal(2000), Module.boxReal(0.01));
                const filteredInput = Module.boxSeq(Module.boxPar(cutoff, Module.boxWire()), filter.box);
                const bt = Module.getBoxType(filteredInput);
                console.log(`filter IO -> inputs: ${bt.inputs}, outputs: ${bt.outputs}`);
                const src = Module.createSourceFromBoxes("FaustDSP", filteredInput, "cpp", []);
                if (!src.error) console.log(src.source.slice(0, 120) + "...");
            }
        }
    } finally {
        Module.destroyLibContext();
    }
}
