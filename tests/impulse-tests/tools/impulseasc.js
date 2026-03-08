#!/usr/bin/env node

/*
 * Experimental impulse runner for the Faust AssemblyScript backend.
 *
 * Pipeline:
 * 1) read generated `-lang asc` source
 * 2) append a wrapper that exposes function-style wasm exports
 * 3) compile wrapper with `asc`
 * 4) instantiate wasm in Node
 * 5) run impulse scenarios and print IR lines
 *
 * Why a wrapper exists:
 * - AssemblyScript `export class` is not a wasm export (`AS235` warning).
 * - Tests need stable callable exports regardless of class export behavior.
 *
 * Runtime knobs:
 * - `IMPULSEASC_ASCC`: AssemblyScript compiler command (default: `asc`)
 */

const fs = require("fs");
const os = require("os");
const path = require("path");
const { spawnSync } = require("child_process");

function usage() {
    console.error("usage: node tools/impulseasc.js <generated.asc.ts> [nbsamples]");
}

function decodeTSStringLiteralContent(content) {
    // Generated getJSON() strings may contain \' (valid in TS string literals,
    // invalid in JSON escape syntax). Normalize before JSON.parse decoding.
    const normalized = content.replace(/\\'/g, "'");
    return JSON.parse(`"${normalized}"`);
}

function sanitizeZero(value) {
    return Math.abs(value) < 5e-7 ? 0 : value;
}

function formatSample(value) {
    const v = Number.isFinite(value) ? sanitizeZero(value) : 0;
    return v.toFixed(6);
}

function walkUIItems(items, visitor) {
    for (const item of items || []) {
        if (item && (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup")) {
            walkUIItems(item.items || [], visitor);
        } else if (item) {
            visitor(item);
        }
    }
}

// Extract metadata JSON string literal without evaluating DSP code.
// Supported contract:
// - `getJSON(): string`
function extractMetadataJSONFromSource(source) {
    const getJSONMatch = source.match(/getJSON\(\)\s*:\s*string\s*\{[\s\S]*?return\s+"((?:[^"\\]|\\.)*)"\s*;/m);
    if (getJSONMatch) {
        try {
            return decodeTSStringLiteralContent(getJSONMatch[1]);
        } catch (_e) {
            return null;
        }
    }
    return null;
}

// Parse metadata into an object; return null when unavailable or invalid.
function parseMetadataSafe(source) {
    try {
        const json = extractMetadataJSONFromSource(source);
        if (!json) {
            return null;
        }
        return JSON.parse(json);
    } catch (_e) {
        return null;
    }
}

// Flatten UI items and assign stable integer indices.
// Invariant: first occurrence of a `varname` defines the index used by __setControl.
function collectUIControls(metadata) {
    const controls = [];
    if (!metadata) {
        return controls;
    }

    const seen = new Set();
    let index = 0;
    walkUIItems(metadata.ui || [], (item) => {
        if (!item || !item.varname) {
            return;
        }
        if (seen.has(item.varname)) {
            controls.push({ ...item, index: controls.find((c) => c.varname === item.varname).index });
            return;
        }
        seen.add(item.varname);
        controls.push({ ...item, index });
        index += 1;
    });

    return controls;
}

function collectUniqueControlVarNames(controls) {
    const names = [];
    const seen = new Set();
    for (const item of controls) {
        if (!item || !item.varname || seen.has(item.varname)) {
            continue;
        }
        seen.add(item.varname);
        names.push(item.varname);
    }
    return names;
}

// Gather unique indices for button controls.
// Buttons are pulsed on the first processing block only.
function collectButtonControlIndices(controls) {
    const indices = [];
    const seen = new Set();
    for (const item of controls) {
        if (!item || item.type !== "button") {
            continue;
        }
        if (!Number.isInteger(item.index) || seen.has(item.index)) {
            continue;
        }
        seen.add(item.index);
        indices.push(item.index);
    }
    return indices;
}

function controlAddress(item) {
    return String(item && item.address ? item.address : "").toLowerCase();
}

function setControlByPredicate(api, voice, controls, predicate, value) {
    const done = new Set();
    for (const item of controls) {
        if (!predicate(item)) {
            continue;
        }
        if (!Number.isInteger(item.index) || done.has(item.index)) {
            continue;
        }
        done.add(item.index);
        api.setControl(voice, item.index, value);
    }
}

function midiNoteToHz(note) {
    return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
}

// Generate wrapper source appended to original DSP class.
// Export contract used by this runner:
// - __dspInit(sr, maxFrames)
// - __getNumInputs(), __getNumOutputs()
// - __voiceInit(voice, sr)
// - __setControl(voice, index, value)
// - __computeVoice(voice, count)
// - __getInputPtr(ch), __getOutputPtr(ch)
function generateWrapperSource(source, className, usesF32, controlVarNames) {
    const sampleType = usesF32 ? "f32" : "f64";
    const arrayType = usesF32 ? "Float32Array" : "Float64Array";

    let setControlCases = "";
    for (let i = 0; i < controlVarNames.length; i++) {
        const name = controlVarNames[i];
        setControlCases += `\n        case ${i}:\n            __voices[voice].${name} = <${sampleType}>value;\n            return;`;
    }

    const shimSource = `\n// ---- impulseasc math shims ----\nfunction isnan(x: f64): bool { return x != x; }\nfunction isinf(x: f64): bool { return x == Infinity || x == -Infinity; }\nfunction acosh(x: f64): f64 { return Math.log(x + Math.sqrt(x * x - 1.0)); }\nfunction asinh(x: f64): f64 { return Math.log(x + Math.sqrt(x * x + 1.0)); }\nfunction atanh(x: f64): f64 { return 0.5 * Math.log((1.0 + x) / (1.0 - x)); }\nfunction cosh(x: f64): f64 { return 0.5 * (Math.exp(x) + Math.exp(-x)); }\nfunction sinh(x: f64): f64 { return 0.5 * (Math.exp(x) - Math.exp(-x)); }\nfunction tanh(x: f64): f64 {\n    let e1: f64 = Math.exp(x);\n    let e2: f64 = Math.exp(-x);\n    return (e1 - e2) / (e1 + e2);\n}\n`;

    return `${shimSource}\n${source}\n\n// ---- impulseasc wasm wrapper ----\nlet __numInputs: i32 = 0;\nlet __numOutputs: i32 = 0;\nlet __bufferFrames: i32 = 0;\nlet __voices = new Array<${className}>();\nlet __inputBuf = new Array<${arrayType}>();\nlet __outputBuf = new Array<${arrayType}>();\nlet __inputView = new Array<Array<${sampleType}>>();\nlet __outputView = new Array<Array<${sampleType}>>();\n\nfunction __ensureBuffers(maxFrames: i32): void {\n    if (__bufferFrames == maxFrames && __inputBuf.length == __numInputs && __outputBuf.length == __numOutputs) {\n        return;\n    }\n    __bufferFrames = maxFrames;\n    __inputBuf = new Array<${arrayType}>();\n    __outputBuf = new Array<${arrayType}>();\n    __inputView = new Array<Array<${sampleType}>>();\n    __outputView = new Array<Array<${sampleType}>>();\n\n    for (let ch: i32 = 0; ch < __numInputs; ch = ch + 1) {\n        let buf = new ${arrayType}(maxFrames);\n        __inputBuf.push(buf);\n        __inputView.push(changetype<Array<${sampleType}>>(buf));\n    }\n    for (let ch: i32 = 0; ch < __numOutputs; ch = ch + 1) {\n        let buf = new ${arrayType}(maxFrames);\n        __outputBuf.push(buf);\n        __outputView.push(changetype<Array<${sampleType}>>(buf));\n    }\n}\n\nfunction __ensureVoice(voice: i32): void {\n    while (__voices.length <= voice) {\n        __voices.push(new ${className}());\n    }\n}\n\nexport function __dspInit(sample_rate: i32, maxFrames: i32): void {\n    ${className}.classInit(sample_rate);\n    let probe = new ${className}();\n    __numInputs = probe.getNumInputs();\n    __numOutputs = probe.getNumOutputs();\n    __voices = new Array<${className}>();\n    __ensureBuffers(maxFrames);\n}\n\nexport function __getNumInputs(): i32 {\n    return __numInputs;\n}\n\nexport function __getNumOutputs(): i32 {\n    return __numOutputs;\n}\n\nexport function __voiceInit(voice: i32, sample_rate: i32): void {\n    __ensureVoice(voice);\n    __voices[voice].instanceInit(sample_rate);\n}\n\nexport function __setControl(voice: i32, index: i32, value: f64): void {\n    if (voice < 0 || voice >= __voices.length) {\n        return;\n    }\n    switch (index) {${setControlCases}\n        default:\n            return;\n    }\n}\n\nexport function __computeVoice(voice: i32, count: i32): void {\n    if (voice < 0 || voice >= __voices.length) {\n        return;\n    }\n    __voices[voice].compute(count, __inputView, __outputView);\n}\n\nexport function __getInputPtr(channel: i32): usize {\n    if (channel < 0 || channel >= __inputBuf.length) {\n        return 0;\n    }\n    return __inputBuf[channel].dataStart;\n}\n\nexport function __getOutputPtr(channel: i32): usize {\n    if (channel < 0 || channel >= __outputBuf.length) {\n        return 0;\n    }\n    return __outputBuf[channel].dataStart;\n}\n`;
}

// Compile temporary wrapped source to wasm and return temp paths.
function compileWrapper(sourcePath, source, className, usesF32, controls) {
    const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), "impulseasc-"));
    const wrapperPath = path.join(tmpDir, path.basename(sourcePath));
    const wasmPath = path.join(tmpDir, "runner.wasm");
    const ascc = process.env.IMPULSEASC_ASCC || "asc";

    const wrapperSource = generateWrapperSource(
        source,
        className,
        usesF32,
        collectUniqueControlVarNames(controls)
    );

    fs.writeFileSync(wrapperPath, wrapperSource);
    const result = spawnSync(ascc, [wrapperPath, "-O", "--runtime", "stub", "-o", wasmPath], {
        encoding: "utf8"
    });

    if (result.status !== 0) {
        const stderr = (result.stderr || "").trim();
        const stdout = (result.stdout || "").trim();
        const details = [stderr, stdout].filter(Boolean).join("\n");
        throw new Error(`asc wrapper compilation failed (${ascc}): ${details}`);
    }

    return { wasmPath, tmpDir };
}

// Build permissive host imports required for module instantiation.
// Most callbacks are placeholders because the wrapper path does not rely on them.
function makeImportObject(imports) {
    const importObject = {};
    for (const entry of imports) {
        if (!importObject[entry.module]) {
            importObject[entry.module] = {};
        }
        if (entry.kind === "function") {
            if (entry.module === "env" && entry.name === "abort") {
                importObject[entry.module][entry.name] = () => {
                    throw new Error("wasm abort called");
                };
            } else if (entry.module === "env" && entry.name === "trace") {
                importObject[entry.module][entry.name] = () => {};
            } else if (entry.module === "env" && entry.name === "seed") {
                importObject[entry.module][entry.name] = () => 1;
            } else {
                importObject[entry.module][entry.name] = () => 0;
            }
        } else if (entry.kind === "global") {
            importObject[entry.module][entry.name] = 0;
        } else if (entry.kind === "memory") {
            importObject[entry.module][entry.name] = new WebAssembly.Memory({ initial: 64 });
        } else if (entry.kind === "table") {
            importObject[entry.module][entry.name] = new WebAssembly.Table({
                initial: 1,
                element: "anyfunc"
            });
        }
    }
    return importObject;
}

function instantiateWrapperWasm(wasmPath) {
    const wasmBytes = fs.readFileSync(wasmPath);
    const module = new WebAssembly.Module(wasmBytes);
    const imports = WebAssembly.Module.imports(module);
    const importObject = makeImportObject(imports);
    const instance = new WebAssembly.Instance(module, importObject);
    return instance;
}

function main() {
    const input = process.argv[2];
    if (!input) {
        usage();
        process.exit(1);
    }

    const nbsamples = process.argv[3] ? parseInt(process.argv[3], 10) : 60000;
    if (!Number.isFinite(nbsamples) || nbsamples <= 0) {
        console.error("invalid sample count:", process.argv[3]);
        process.exit(1);
    }

    const sourcePath = path.resolve(input);
    const source = fs.readFileSync(sourcePath, "utf8");

    const classMatch = source.match(/\bexport\s+class\s+([A-Za-z_][A-Za-z0-9_]*)\b/);
    if (!classMatch) {
        throw new Error("cannot find exported DSP class in " + sourcePath);
    }

    const className = classMatch[1];
    const usesF32 = /\bcompute\s*\([^)]*Array<Array<f32>>/m.test(source);
    // Metadata drives control mapping (buttons, gate/freq/key/gain hints).
    const metadata = parseMetadataSafe(source);
    const uiControls = collectUIControls(metadata);
    const buttonControlIndices = collectButtonControlIndices(uiControls);

    const { wasmPath, tmpDir } = compileWrapper(sourcePath, source, className, usesF32, uiControls);

    let instance;
    try {
        instance = instantiateWrapperWasm(wasmPath);
    } finally {
        try {
            fs.rmSync(tmpDir, { recursive: true, force: true });
        } catch (_ignored) {
            // Ignore temp cleanup issues.
        }
    }

    const e = instance.exports;
    const required = [
        "memory",
        "__dspInit",
        "__getNumInputs",
        "__getNumOutputs",
        "__voiceInit",
        "__setControl",
        "__computeVoice",
        "__getInputPtr",
        "__getOutputPtr"
    ];
    for (const name of required) {
        if (!(name in e)) {
            throw new Error(`missing wasm export ${name}`);
        }
    }

    // Keep sample-rate and block size aligned with historical impulse-tests behavior.
    const kSampleRate = 44100;
    const kFrames = 64;
    e.__dspInit(kSampleRate, kFrames);

    const numInputs = e.__getNumInputs();
    const numOutputs = e.__getNumOutputs();

    const inputPtrs = Array.from({ length: numInputs }, (_, ch) => Number(e.__getInputPtr(ch)));
    const outputPtrs = Array.from({ length: numOutputs }, (_, ch) => Number(e.__getOutputPtr(ch)));

    // Recreate typed views each block in case wasm memory grows and replaces ArrayBuffer.
    const readChannels = () => {
        const memory = e.memory.buffer;
        if (usesF32) {
            return {
                inputs: inputPtrs.map((ptr) => new Float32Array(memory, ptr, kFrames)),
                outputs: outputPtrs.map((ptr) => new Float32Array(memory, ptr, kFrames)),
                zeroOut: (channels, nFrames) => {
                    for (const ch of channels) {
                        ch.fill(0, 0, nFrames);
                    }
                },
                zeroIn: (channels, nFrames) => {
                    for (const ch of channels) {
                        ch.fill(0, 0, nFrames);
                    }
                }
            };
        }
        return {
            inputs: inputPtrs.map((ptr) => new Float64Array(memory, ptr, kFrames)),
            outputs: outputPtrs.map((ptr) => new Float64Array(memory, ptr, kFrames)),
            zeroOut: (channels, nFrames) => {
                for (const ch of channels) {
                    ch.fill(0, 0, nFrames);
                }
            },
            zeroIn: (channels, nFrames) => {
                for (const ch of channels) {
                    ch.fill(0, 0, nFrames);
                }
            }
        };
    };

    const api = {
        setControl: (voice, index, value) => {
            e.__setControl(voice, index, value);
        }
    };

    const ChanArray = usesF32 ? Float32Array : Float64Array;
    const outputs = Array.from({ length: numOutputs }, () => new ChanArray(nbsamples));

    const segmentCount = (nbsamples % 4 === 0) ? 4 : 1;
    const segmentSize = nbsamples / segmentCount;

    // Segment model mirrors existing impulse-tests:
    // - segments 0/1: runDSP-like
    // - segments 2/3: runPolyDSP-like (voice sum)
    for (let seg = 0; seg < segmentCount; seg++) {
        const segOutputs = Array.from({ length: numOutputs }, () => new ChanArray(segmentSize));
        const isRunDSPStyle = seg < 2;

        if (isRunDSPStyle) {
            // runDSP-like mode:
            // - one voice
            // - input impulse on first frame of first block
            // - button controls = 1 on first block, 0 afterwards
            e.__voiceInit(0, kSampleRate);

            let firstBlock = true;
            let offset = 0;
            while (offset < segmentSize) {
                const nFrames = Math.min(kFrames, segmentSize - offset);
                const ch = readChannels();
                ch.zeroIn(ch.inputs, nFrames);
                ch.zeroOut(ch.outputs, nFrames);

                if (numInputs > 0 && firstBlock) {
                    for (let inCh = 0; inCh < numInputs; inCh++) {
                        ch.inputs[inCh][0] = 1.0;
                    }
                }

                for (const controlIndex of buttonControlIndices) {
                    api.setControl(0, controlIndex, firstBlock ? 1 : 0);
                }

                e.__computeVoice(0, nFrames);

                for (let outCh = 0; outCh < numOutputs; outCh++) {
                    for (let i = 0; i < nFrames; i++) {
                        segOutputs[outCh][offset + i] = ch.outputs[outCh][i];
                    }
                }

                offset += nFrames;
                firstBlock = false;
            }
        } else {
            const voiceCount = (seg === 2) ? 4 : 1;
            const velocity = 100.0 / 127.0;

            // runPolyDSP-like mode:
            // - initialize voices
            // - set MIDI-like controls from UI addresses when present
            // - sum each voice output into segment output
            for (let v = 0; v < voiceCount; v++) {
                e.__voiceInit(v, kSampleRate);
                const note = 60 + v * 2;
                const freq = midiNoteToHz(note);

                setControlByPredicate(api, v, uiControls, (item) => controlAddress(item).endsWith("/gate"), 1);
                setControlByPredicate(api, v, uiControls, (item) => controlAddress(item).endsWith("/freq"), freq);
                setControlByPredicate(api, v, uiControls, (item) => controlAddress(item).endsWith("/key"), note);
                setControlByPredicate(api, v, uiControls, (item) => controlAddress(item).endsWith("/gain"), velocity);
                setControlByPredicate(api, v, uiControls, (item) => {
                    const addr = controlAddress(item);
                    return addr.endsWith("/vel") || addr.endsWith("/velocity");
                }, 100.0);
            }

            let offset = 0;
            while (offset < segmentSize) {
                const nFrames = Math.min(kFrames, segmentSize - offset);
                for (let outCh = 0; outCh < numOutputs; outCh++) {
                    for (let i = 0; i < nFrames; i++) {
                        segOutputs[outCh][offset + i] = 0;
                    }
                }

                for (let v = 0; v < voiceCount; v++) {
                    const ch = readChannels();
                    ch.zeroIn(ch.inputs, nFrames);
                    ch.zeroOut(ch.outputs, nFrames);
                    e.__computeVoice(v, nFrames);

                    for (let outCh = 0; outCh < numOutputs; outCh++) {
                        for (let i = 0; i < nFrames; i++) {
                            segOutputs[outCh][offset + i] += ch.outputs[outCh][i];
                        }
                    }
                }
                offset += nFrames;
            }
        }

        const segOffset = seg * segmentSize;
        for (let ch = 0; ch < numOutputs; ch++) {
            outputs[ch].set(segOutputs[ch], segOffset);
        }
    }

    process.stdout.write(`number_of_inputs  :${String(numInputs).padStart(4, " ")}\n`);
    process.stdout.write(`number_of_outputs :${String(numOutputs).padStart(4, " ")}\n`);
    process.stdout.write(`number_of_frames  :${String(nbsamples).padStart(6, " ")}\n`);

    for (let i = 0; i < nbsamples; i++) {
        const values = [];
        for (let ch = 0; ch < numOutputs; ch++) {
            values.push(formatSample(outputs[ch][i]));
        }
        process.stdout.write(`${String(i).padStart(6, " ")} :  ${values.join(" ")}\n`);
    }
}

try {
    main();
} catch (err) {
    console.error("impulseasc error:", err && err.message ? err.message : err);
    process.exit(1);
}
