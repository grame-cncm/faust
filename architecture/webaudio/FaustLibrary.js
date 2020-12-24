"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var Faust;
(function (Faust) {
    class LibFaustImp {
        constructor(module) {
            this.fModule = module;
            this.fCompiler = new module.libFaustWasm();
            this.fFileSystem = this.fModule.FS;
            Faust.FS = this.fFileSystem;
        }
        version() { return this.fCompiler.version(); }
        createDSPFactory(name, dsp_code, args, internal_memory) { return this.fCompiler.createDSPFactory(name, dsp_code, args, internal_memory); }
        deleteDSPFactory(cfactory) { this.fCompiler.deleteDSPFactory(cfactory); }
        expandDSP(name, dsp_code, args) { return this.fCompiler.expandDSP(name, dsp_code, args); }
        generateAuxFiles(name, dsp_code, args) { return this.fCompiler.generateAuxFiles(name, dsp_code, args); }
        deleteAllDSPFactories() { this.fCompiler.deleteAllDSPFactories(); }
        getErrorAfterException() { return this.fCompiler.getErrorAfterException(); }
        cleanupAfterException() { this.fCompiler.cleanupAfterException(); }
        module() { return this.fModule; }
        fs() { return this.fFileSystem; }
        getInfos(what) { return this.fCompiler.getInfos(what); }
        toString() { return "LibFaust module: " + this.fModule + " compiler: " + this.fCompiler; }
    }
    function createLibFaust(module) {
        return (!module || (typeof (module) == 'undefined')) ? null : new LibFaustImp(module);
    }
    Faust.createLibFaust = createLibFaust;
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    function createFaustJSON(json) { return JSON.parse(json); }
    Faust.createFaustJSON = createFaustJSON;
    function createCompiler(libfaust) { return new CompilerImp(libfaust); }
    Faust.createCompiler = createCompiler;
    class CompilerImp {
        constructor(libfaust) {
            this.fLibFaust = libfaust;
            this.fErrorMessage = "";
        }
        intVec2intArray(vec) {
            const size = vec.size();
            const ui8Code = new Uint8Array(size);
            for (let i = 0; i < size; i++) {
                ui8Code[i] = vec.get(i);
            }
            return ui8Code;
        }
        createDSPFactoryImp(name, dsp_code, args, poly) {
            return __awaiter(this, void 0, void 0, function* () {
                if (CompilerImp.gFactories.size > 10) {
                    CompilerImp.gFactories.clear();
                }
                let sha_key = Faust.hash(name + dsp_code + args + ((poly) ? "poly" : "mono"));
                if (CompilerImp.gFactories.has(sha_key)) {
                    return CompilerImp.gFactories.get(sha_key);
                }
                else {
                    try {
                        const faust_wasm = this.fLibFaust.createDSPFactory(name, dsp_code, args, !poly);
                        try {
                            const code = this.intVec2intArray(faust_wasm.data);
                            const module = yield WebAssembly.compile(code);
                            const factory = { cfactory: faust_wasm.cfactory, code: code, module: module, json: faust_wasm.json, poly: poly };
                            this.deleteDSPFactory(factory);
                            CompilerImp.gFactories.set(sha_key, factory);
                            return factory;
                        }
                        catch (e) {
                            console.error(e);
                            return null;
                        }
                    }
                    catch (_a) {
                        this.fErrorMessage = this.fLibFaust.getErrorAfterException();
                        console.error("=> exception raised while running createDSPFactory: " + this.fErrorMessage);
                        this.fLibFaust.cleanupAfterException();
                        return null;
                    }
                }
            });
        }
        version() { return this.fLibFaust.version(); }
        getErrorMessage() { return this.fErrorMessage; }
        createMonoDSPFactory(name, dsp_code, args) {
            return __awaiter(this, void 0, void 0, function* () {
                return this.createDSPFactoryImp(name, dsp_code, args, false);
            });
        }
        createPolyDSPFactory(name, dsp_code, args) {
            return __awaiter(this, void 0, void 0, function* () {
                return this.createDSPFactoryImp(name, dsp_code, args, true);
            });
        }
        deleteDSPFactory(factory) {
            this.fLibFaust.deleteDSPFactory(factory.cfactory);
            factory.cfactory = 0;
        }
        expandDSP(dsp_code, args) {
            try {
                return this.fLibFaust.expandDSP("FaustDSP", dsp_code, args);
            }
            catch (_a) {
                this.fErrorMessage = this.fLibFaust.getErrorAfterException();
                console.error("=> exception raised while running expandDSP: " + this.fErrorMessage);
                this.fLibFaust.cleanupAfterException();
                return null;
            }
        }
        generateAuxFiles(name, dsp_code, args) {
            try {
                return this.fLibFaust.generateAuxFiles(name, dsp_code, args);
            }
            catch (_a) {
                this.fErrorMessage = this.fLibFaust.getErrorAfterException();
                console.error("=> exception raised while running generateAuxFiles: " + this.fErrorMessage);
                this.fLibFaust.cleanupAfterException();
                return false;
            }
        }
        deleteAllDSPFactories() {
            this.fLibFaust.deleteAllDSPFactories();
        }
    }
    CompilerImp.gFactories = new Map();
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    function createInstanceAPI(exports) { return new InstanceAPIImpl(exports); }
    Faust.createInstanceAPI = createInstanceAPI;
    class InstanceAPIImpl {
        constructor(exports) { this.fExports = exports; }
        compute(dsp, count, input, output) { this.fExports.compute(dsp, count, input, output); }
        getNumInputs(dsp) { return this.fExports.getNumInputs(dsp); }
        getNumOutputs(dsp) { return this.fExports.getNumOutputs(dsp); }
        getParamValue(dsp, index) { return this.fExports.getParamValue(dsp, index); }
        getSampleRate(dsp) { return this.fExports.getSampleRate(dsp); }
        init(dsp, sampleRate) { this.fExports.init(dsp, sampleRate); }
        instanceClear(dsp) { this.fExports.instanceClear(dsp); }
        instanceConstants(dsp, sampleRate) { this.fExports.instanceConstants(dsp, sampleRate); }
        instanceInit(dsp, sampleRate) { this.fExports.instanceInit(dsp, sampleRate); }
        instanceResetUserInterface(dsp) { this.fExports.instanceResetUserInterface(dsp); }
        setParamValue(dsp, index, value) { this.fExports.setParamValue(dsp, index, value); }
    }
    Faust.InstanceAPIImpl = InstanceAPIImpl;
    function createGenerator() { return new GeneratorImp(); }
    Faust.createGenerator = createGenerator;
    class GeneratorImp {
        createWasmImport(memory) {
            return {
                env: {
                    memory: ((memory) ? memory : new WebAssembly.Memory({ initial: 100 })),
                    memoryBase: 0,
                    tableBase: 0,
                    _abs: Math.abs,
                    _acosf: Math.acos, _asinf: Math.asin, _atanf: Math.atan, _atan2f: Math.atan2,
                    _ceilf: Math.ceil, _cosf: Math.cos, _expf: Math.exp, _floorf: Math.floor,
                    _fmodf: (x, y) => x % y,
                    _logf: Math.log, _log10f: Math.log10, _max_f: Math.max, _min_f: Math.min,
                    _remainderf: (x, y) => x - Math.round(x / y) * y,
                    _powf: Math.pow, _roundf: Math.fround, _sinf: Math.sin, _sqrtf: Math.sqrt, _tanf: Math.tan,
                    _acoshf: Math.acosh, _asinhf: Math.asinh, _atanhf: Math.atanh,
                    _coshf: Math.cosh, _sinhf: Math.sinh, _tanhf: Math.tanh,
                    _acos: Math.acos, _asin: Math.asin, _atan: Math.atan, _atan2: Math.atan2,
                    _ceil: Math.ceil, _cos: Math.cos, _exp: Math.exp, _floor: Math.floor,
                    _fmod: (x, y) => x % y,
                    _log: Math.log, _log10: Math.log10, _max_: Math.max, _min_: Math.min,
                    _remainder: (x, y) => x - Math.round(x / y) * y,
                    _pow: Math.pow, _round: Math.fround, _sin: Math.sin, _sqrt: Math.sqrt, _tan: Math.tan,
                    _acosh: Math.acosh, _asinh: Math.asinh, _atanh: Math.atanh,
                    _cosh: Math.cosh, _sinh: Math.sinh, _tanh: Math.tanh,
                    table: new WebAssembly.Table({ initial: 0, element: "anyfunc" })
                }
            };
        }
        createWasmMemory(voices_in, sample_size, voice_JSON, effect_JSON, buffer_size) {
            const voices = Math.max(4, voices_in);
            const ptr_size = sample_size;
            const pow2limit = (x) => {
                let n = 65536;
                while (n < x) {
                    n *= 2;
                }
                return n;
            };
            const effect_size = (effect_JSON ? effect_JSON.size : 0);
            let memory_size = pow2limit(effect_size
                + voice_JSON.size * voices
                + (voice_JSON.inputs + voice_JSON.outputs * 2)
                    * (ptr_size + buffer_size * sample_size)) / 65536;
            memory_size = Math.max(2, memory_size);
            return new WebAssembly.Memory({ initial: memory_size, maximum: memory_size });
        }
        createMonoDSPInstanceAux(instance, factory) {
            const functions = instance.exports;
            const api = new InstanceAPIImpl(functions);
            const memory = instance.exports.memory;
            return { memory: memory, api: api, json: factory.json };
        }
        createMemoryAux(voices, voice_factory, effect_factory) {
            const voice_JSON = Faust.createFaustJSON(voice_factory.json);
            const effect_JSON = (effect_factory && effect_factory.json) ? Faust.createFaustJSON(effect_factory.json) : null;
            const sample_size = voice_JSON.compile_options.match("-double") ? 8 : 4;
            return this.createWasmMemory(voices, sample_size, voice_JSON, effect_JSON, 8192);
        }
        createMixerAux(mixer_module, memory) {
            const mix_import = {
                imports: { print: console.log },
                memory: { memory }
            };
            const mixer_instance = new WebAssembly.Instance(mixer_module, mix_import);
            const mixer_functions = mixer_instance.exports;
            return mixer_functions;
        }
        loadDSPFactory(wasm_path, json_path) {
            return __awaiter(this, void 0, void 0, function* () {
                const wasm_file = yield fetch(wasm_path);
                if (!wasm_file.ok) {
                    console.error("=> exception raised while running loadDSPFactory, file not found: " + wasm_path);
                    return null;
                }
                try {
                    const wasm_buffer = yield wasm_file.arrayBuffer();
                    const module = yield WebAssembly.compile(wasm_buffer);
                    const json_file = yield fetch(json_path);
                    const json = yield json_file.text();
                    const JSONDsp = Faust.createFaustJSON(json);
                    const c_options = JSONDsp.compile_options;
                    const poly = c_options.indexOf('wasm-e') !== -1;
                    return { cfactory: 0, code: wasm_buffer, module: module, json: json, poly: poly };
                }
                catch (e) {
                    console.error("=> exception raised while running loadDSPFactory: " + e);
                    return null;
                }
            });
        }
        loadDSPMixer(mixer_path) {
            return __awaiter(this, void 0, void 0, function* () {
                try {
                    let mixer_buffer = null;
                    if (Faust.FS) {
                        mixer_buffer = Faust.FS.readFile(mixer_path, { encoding: 'binary' });
                    }
                    else {
                        const mixer_file = yield fetch(mixer_path);
                        mixer_buffer = yield mixer_file.arrayBuffer();
                    }
                    return WebAssembly.compile(mixer_buffer);
                }
                catch (e) {
                    console.error("=> exception raised while running loadMixer: " + e);
                    return null;
                }
            });
        }
        createAsyncMonoDSPInstance(factory) {
            return __awaiter(this, void 0, void 0, function* () {
                const instance = yield WebAssembly.instantiate(factory.module, this.createWasmImport());
                return this.createMonoDSPInstanceAux(instance, factory);
            });
        }
        createSyncMonoDSPInstance(factory) {
            const instance = new WebAssembly.Instance(factory.module, this.createWasmImport());
            return this.createMonoDSPInstanceAux(instance, factory);
        }
        createAsyncPolyDSPInstance(voice_factory, mixer_module, voices, effect_factory) {
            return __awaiter(this, void 0, void 0, function* () {
                const memory = this.createMemoryAux(voices, voice_factory, effect_factory);
                const voice_instance = yield WebAssembly.instantiate(voice_factory.module, this.createWasmImport(memory));
                const voice_functions = voice_instance.exports;
                const voice_api = new InstanceAPIImpl(voice_functions);
                const mixer_api = this.createMixerAux(mixer_module, memory);
                if (effect_factory) {
                    const effect_instance = yield WebAssembly.instantiate(effect_factory.module, this.createWasmImport(memory));
                    const effect_functions = effect_instance.exports;
                    const effect_api = new InstanceAPIImpl(effect_functions);
                    return {
                        memory: memory,
                        voices: voices,
                        voice_api: voice_api,
                        effect_api: effect_api,
                        mixer_api: mixer_api,
                        voice_json: voice_factory.json,
                        effect_json: effect_factory.json
                    };
                }
                else {
                    return {
                        memory: memory,
                        voices: voices,
                        voice_api: voice_api,
                        effect_api: undefined,
                        mixer_api: mixer_api,
                        voice_json: voice_factory.json,
                        effect_json: undefined
                    };
                }
            });
        }
        createSyncPolyDSPInstance(voice_factory, mixer_module, voices, effect_factory) {
            const memory = this.createMemoryAux(voices, voice_factory, effect_factory);
            const voice_instance = new WebAssembly.Instance(voice_factory.module, this.createWasmImport(memory));
            const voice_functions = voice_instance.exports;
            const voice_api = new InstanceAPIImpl(voice_functions);
            const mixer_api = this.createMixerAux(mixer_module, memory);
            if (effect_factory) {
                const effect_instance = new WebAssembly.Instance(effect_factory.module, this.createWasmImport(memory));
                const effect_functions = effect_instance.exports;
                const effect_api = new InstanceAPIImpl(effect_functions);
                return {
                    memory: memory,
                    voices: voices,
                    voice_api: voice_api,
                    effect_api: effect_api,
                    mixer_api: mixer_api,
                    voice_json: voice_factory.json,
                    effect_json: effect_factory.json
                };
            }
            else {
                return {
                    memory: memory,
                    voices: voices,
                    voice_api: voice_api,
                    effect_api: undefined,
                    mixer_api: mixer_api,
                    voice_json: voice_factory.json,
                    effect_json: undefined
                };
            }
        }
    }
    Faust.GeneratorImp = GeneratorImp;
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    class BaseDSPImp {
        constructor(sample_size, buffer_size) {
            this.fOutputHandler = null;
            this.fComputeHandler = null;
            this.fCachedEvents = [];
            this.fBufferNum = 0;
            this.fPlotHandler = null;
            this.fBufferSize = buffer_size;
            this.fInChannels = [];
            this.fOutChannels = [];
            this.gPtrSize = sample_size;
            this.gSampleSize = sample_size;
            this.fOutputsTimer = 5;
            this.fInputsItems = [];
            this.fOutputsItems = [];
            this.fDescriptor = [];
            this.fPitchwheelLabel = [];
            this.fCtrlLabel = new Array(128).fill(null).map(() => []);
            this.fPathTable = {};
            this.fDestroyed = false;
            this.fUICallback = (item) => {
                if (item.type === "hbargraph" || item.type === "vbargraph") {
                    this.fOutputsItems.push(item.address);
                    this.fPathTable[item.address] = item.index;
                }
                else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
                    this.fInputsItems.push(item.address);
                    this.fPathTable[item.address] = item.index;
                    this.fDescriptor.push(item);
                    if (!item.meta)
                        return;
                    item.meta.forEach((meta) => {
                        const { midi } = meta;
                        if (!midi)
                            return;
                        const strMidi = midi.trim();
                        if (strMidi === "pitchwheel") {
                            this.fPitchwheelLabel.push({ path: item.address, min: item.min, max: item.max });
                        }
                        else {
                            const matched = strMidi.match(/^ctrl\s(\d+)/);
                            if (!matched)
                                return;
                            this.fCtrlLabel[parseInt(matched[1])].push({ path: item.address, min: item.min, max: item.max });
                        }
                    });
                }
            };
        }
        static remap(v, mn0, mx0, mn1, mx1) {
            return (v - mn0) / (mx0 - mn0) * (mx1 - mn1) + mn1;
        }
        static parseUI(ui, callback) {
            ui.forEach(group => BaseDSPImp.parseGroup(group, callback));
        }
        static parseGroup(group, callback) {
            if (group.items) {
                BaseDSPImp.parseItems(group.items, callback);
            }
        }
        static parseItems(items, callback) {
            items.forEach(item => BaseDSPImp.parseItem(item, callback));
        }
        static parseItem(item, callback) {
            if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
                BaseDSPImp.parseItems(item.items, callback);
            }
            else {
                callback(item);
            }
        }
        updateOutputs() {
            if (this.fOutputsItems.length > 0 && this.fOutputHandler && this.fOutputsTimer-- === 0) {
                this.fOutputsTimer = 5;
                this.fOutputsItems.forEach(item => { if (this.fOutputHandler)
                    this.fOutputHandler(item, this.getParamValue(item)); });
            }
        }
        metadata(handler) {
            if (this.fJSONDsp.meta) {
                this.fJSONDsp.meta.forEach(meta => handler(Object.keys(meta)[0], meta[Object.keys(meta)[0]]));
            }
        }
        compute(input, output) {
            return false;
        }
        setOutputParamHandler(handler) {
            this.fOutputHandler = handler;
        }
        getOutputParamHandler() {
            return this.fOutputHandler;
        }
        setComputeHandler(handler) {
            this.fComputeHandler = handler;
        }
        getComputeHandler() {
            return this.fComputeHandler;
        }
        setPlotHandler(handler) {
            this.fPlotHandler = handler;
        }
        getPlotHandler() {
            return this.fPlotHandler;
        }
        getNumInputs() {
            return -1;
        }
        getNumOutputs() {
            return -1;
        }
        midiMessage(data) {
            if (this.fPlotHandler)
                this.fCachedEvents.push({ data, type: "midi" });
            const cmd = data[0] >> 4;
            const channel = data[0] & 0xf;
            const data1 = data[1];
            const data2 = data[2];
            if (cmd === 11)
                return this.ctrlChange(channel, data1, data2);
            if (cmd === 14)
                return this.pitchWheel(channel, (data2 * 128.0 + data1));
        }
        ctrlChange(channel, ctrl, value) {
            if (this.fPlotHandler)
                this.fCachedEvents.push({ type: "ctrlChange", data: [channel, ctrl, value] });
            if (this.fCtrlLabel[ctrl].length) {
                this.fCtrlLabel[ctrl].forEach((ctrl) => {
                    const { path } = ctrl;
                    this.setParamValue(path, BaseDSPImp.remap(value, 0, 127, ctrl.min, ctrl.max));
                    if (this.fOutputHandler)
                        this.fOutputHandler(path, this.getParamValue(path));
                });
            }
        }
        pitchWheel(channel, wheel) {
            if (this.fPlotHandler)
                this.fCachedEvents.push({ type: "pitchWheel", data: [channel, wheel] });
            this.fPitchwheelLabel.forEach((pw) => {
                this.setParamValue(pw.path, BaseDSPImp.remap(wheel, 0, 16383, pw.min, pw.max));
                if (this.fOutputHandler)
                    this.fOutputHandler(pw.path, this.getParamValue(pw.path));
            });
        }
        setParamValue(path, value) { }
        getParamValue(path) { return 0; }
        getParams() { return this.fInputsItems; }
        getJSON() { return ""; }
        getUI() { return this.fJSONDsp.ui; }
        getDescriptors() { return this.fDescriptor; }
        destroy() {
            this.fDestroyed = true;
            this.fOutputHandler = null;
            this.fComputeHandler = null;
            this.fPlotHandler = null;
        }
    }
    Faust.BaseDSPImp = BaseDSPImp;
    function createMonoDSP(instance, sample_rate, sample_size, buffer_size) {
        return new MonoDSPImp(instance, sample_rate, sample_size, buffer_size);
    }
    Faust.createMonoDSP = createMonoDSP;
    class MonoDSPImp extends BaseDSPImp {
        constructor(instance, sample_rate, sample_size, buffer_size) {
            super(sample_size, buffer_size);
            this.fInstance = instance;
            this.fJSONDsp = Faust.createFaustJSON(this.fInstance.json);
            BaseDSPImp.parseUI(this.fJSONDsp.ui, this.fUICallback);
            this.initMemory();
            this.fInstance.api.init(this.fDSP, sample_rate);
        }
        initMemory() {
            this.fDSP = 0;
            const audio_ptr = this.fJSONDsp.size;
            this.fAudioInputs = audio_ptr;
            this.fAudioOutputs = this.fAudioInputs + this.getNumInputs() * this.gPtrSize;
            const audio_inputs_ptr = this.fAudioOutputs + this.getNumOutputs() * this.gPtrSize;
            const audio_outputs_ptr = audio_inputs_ptr + this.getNumInputs() * this.fBufferSize * this.gSampleSize;
            const HEAP = this.fInstance.memory.buffer;
            const HEAP32 = new Int32Array(HEAP);
            const HEAPF = (this.gSampleSize === 4) ? new Float32Array(HEAP) : new Float64Array(HEAP);
            if (this.getNumInputs() > 0) {
                for (let chan = 0; chan < this.getNumInputs(); chan++) {
                    HEAP32[(this.fAudioInputs >> 2) + chan] = audio_inputs_ptr + this.fBufferSize * this.gSampleSize * chan;
                }
                const dspInChans = HEAP32.subarray(this.fAudioInputs >> 2, (this.fAudioInputs + this.getNumInputs() * this.gPtrSize) >> 2);
                for (let chan = 0; chan < this.getNumInputs(); chan++) {
                    this.fInChannels[chan] = HEAPF.subarray(dspInChans[chan] >> Math.log2(this.gSampleSize), (dspInChans[chan] + this.fBufferSize * this.gSampleSize) >> Math.log2(this.gSampleSize));
                }
            }
            if (this.getNumOutputs() > 0) {
                for (let chan = 0; chan < this.getNumOutputs(); chan++) {
                    HEAP32[(this.fAudioOutputs >> 2) + chan] = audio_outputs_ptr + this.fBufferSize * this.gSampleSize * chan;
                }
                const dspOutChans = HEAP32.subarray(this.fAudioOutputs >> 2, (this.fAudioOutputs + this.getNumOutputs() * this.gPtrSize) >> 2);
                for (let chan = 0; chan < this.getNumOutputs(); chan++) {
                    this.fOutChannels[chan] = HEAPF.subarray(dspOutChans[chan] >> Math.log2(this.gSampleSize), (dspOutChans[chan] + this.fBufferSize * this.gSampleSize) >> Math.log2(this.gSampleSize));
                }
            }
        }
        toString() {
            let str = "============== Mono Memory layout ==============";
            str += "this.fBufferSize: " + this.fBufferSize;
            str += "this.fJSONDsp.size: " + this.fJSONDsp.size;
            str += "this.fAudioInputs: " + this.fAudioInputs;
            str += "this.fAudioOutputs: " + this.fAudioOutputs;
            str += "this.fDSP: " + this.fDSP;
            return str;
        }
        compute(input, output) {
            if (this.fDestroyed)
                return false;
            if (this.getNumInputs() > 0 && (!input || !input[0] || input[0].length === 0)) {
                return true;
            }
            if (this.getNumOutputs() > 0 && (!output || !output[0] || output[0].length === 0)) {
                return true;
            }
            if (input !== undefined) {
                for (let chan = 0; chan < Math.min(this.getNumInputs(), input.length); ++chan) {
                    const dspInput = this.fInChannels[chan];
                    dspInput.set(input[chan]);
                }
            }
            if (this.fComputeHandler)
                this.fComputeHandler(this.fBufferSize);
            this.fInstance.api.compute(this.fDSP, this.fBufferSize, this.fAudioInputs, this.fAudioOutputs);
            this.updateOutputs();
            if (output !== undefined) {
                for (let chan = 0; chan < Math.min(this.getNumOutputs(), output.length); chan++) {
                    const dspOutput = this.fOutChannels[chan];
                    output[chan].set(dspOutput);
                }
                if (this.fPlotHandler) {
                    this.fPlotHandler(output, this.fBufferNum++, (this.fCachedEvents.length ? this.fCachedEvents : undefined));
                    this.fCachedEvents = [];
                }
            }
            return true;
        }
        metadata(handler) { super.metadata(handler); }
        getNumInputs() {
            return this.fInstance.api.getNumInputs(this.fDSP);
        }
        getNumOutputs() {
            return this.fInstance.api.getNumOutputs(this.fDSP);
        }
        setParamValue(path, value) {
            if (this.fPlotHandler)
                this.fCachedEvents.push({ type: "param", data: { path, value } });
            this.fInstance.api.setParamValue(this.fDSP, this.fPathTable[path], value);
        }
        getParamValue(path) {
            return this.fInstance.api.getParamValue(this.fDSP, this.fPathTable[path]);
        }
        getJSON() { return this.fInstance.json; }
        getDescriptors() { return this.fDescriptor; }
        getUI() { return this.fJSONDsp.ui; }
    }
    Faust.MonoDSPImp = MonoDSPImp;
    class DspVoice {
        constructor(dsp, api, input_items, path_table, sample_rate) {
            DspVoice.kActiveVoice = 0;
            DspVoice.kFreeVoice = -1;
            DspVoice.kReleaseVoice = -2;
            DspVoice.kNoVoice = -3;
            DspVoice.VOICE_STOP_LEVEL = 0.0005;
            this.fKeyFun = (pitch) => { return DspVoice.midiToFreq(pitch); };
            this.fVelFun = (velocity) => { return velocity / 127.0; };
            this.fLevel = 0;
            this.fRelease = 0;
            this.fMaxRelease = sample_rate / 2;
            this.fNote = DspVoice.kFreeVoice;
            this.fDate = 0;
            this.fDSP = dsp;
            this.fAPI = api;
            this.fGateLabel = [];
            this.fGainLabel = [];
            this.fFreqLabel = [];
            this.fAPI.init(this.fDSP, sample_rate);
            this.extractPaths(input_items, path_table);
        }
        static midiToFreq(note) { return 440.0 * Math.pow(2, ((note - 69) / 12)); }
        extractPaths(input_items, path_table) {
            input_items.forEach((item) => {
                if (item.endsWith("/gate")) {
                    this.fGateLabel.push(path_table[item]);
                }
                else if (item.endsWith("/freq")) {
                    this.fKeyFun = (pitch) => { return DspVoice.midiToFreq(pitch); };
                    this.fFreqLabel.push(path_table[item]);
                }
                else if (item.endsWith("/key")) {
                    this.fKeyFun = (pitch) => { return pitch; };
                    this.fFreqLabel.push(path_table[item]);
                }
                else if (item.endsWith("/gain")) {
                    this.fVelFun = (velocity) => { return velocity / 127.0; };
                    this.fGainLabel.push(path_table[item]);
                }
                else if (item.endsWith("/vel") && item.endsWith("/velocity")) {
                    this.fVelFun = (velocity) => { return velocity; };
                    this.fGainLabel.push(path_table[item]);
                }
            });
        }
        keyOn(pitch, velocity) {
            this.fAPI.instanceClear(this.fDSP);
            this.fFreqLabel.forEach(index => this.fAPI.setParamValue(this.fDSP, index, this.fKeyFun(pitch)));
            this.fGateLabel.forEach(index => this.fAPI.setParamValue(this.fDSP, index, 1));
            this.fGainLabel.forEach(index => this.fAPI.setParamValue(this.fDSP, index, this.fVelFun(velocity)));
            this.fNote = pitch;
        }
        keyOff(hard = false) {
            this.fGateLabel.forEach(index => this.fAPI.setParamValue(this.fDSP, index, 0));
            if (hard) {
                this.fNote = DspVoice.kFreeVoice;
            }
            else {
                this.fRelease = this.fMaxRelease;
                this.fNote = DspVoice.kReleaseVoice;
            }
        }
        compute(buffer_size, inputs, outputs) {
            this.fAPI.compute(this.fDSP, buffer_size, inputs, outputs);
        }
        setParamValue(index, value) {
            this.fAPI.setParamValue(this.fDSP, index, value);
        }
        getParamValue(index) {
            return this.fAPI.getParamValue(this.fDSP, index);
        }
    }
    Faust.DspVoice = DspVoice;
    function createPolyDSP(instance, sample_rate, sample_size, buffer_size) {
        return new PolyDSPImp(instance, sample_rate, sample_size, buffer_size);
    }
    Faust.createPolyDSP = createPolyDSP;
    class PolyDSPImp extends BaseDSPImp {
        constructor(instance, sample_rate, sample_size, buffer_size) {
            super(sample_size, buffer_size);
            this.fInstance = instance;
            this.fJSONDsp = Faust.createFaustJSON(this.fInstance.voice_json);
            this.fJSONEffect = (this.fInstance.effect_api && this.fInstance.effect_json) ? Faust.createFaustJSON(this.fInstance.effect_json) : null;
            BaseDSPImp.parseUI(this.fJSONDsp.ui, this.fUICallback);
            if (this.fJSONEffect)
                BaseDSPImp.parseUI(this.fJSONEffect.ui, this.fUICallback);
            this.initMemory();
            this.fVoiceTable = [];
            for (let voice = 0; voice < this.fInstance.voices; voice++) {
                this.fVoiceTable.push(new DspVoice(this.fJSONDsp.size * voice, this.fInstance.voice_api, this.fInputsItems, this.fPathTable, sample_rate));
            }
            if (this.fInstance.effect_api)
                this.fInstance.effect_api.init(this.fEffect, sample_rate);
        }
        initMemory() {
            this.fEffect = this.fJSONDsp.size * this.fInstance.voices;
            const audio_ptr = this.fEffect + ((this.fJSONEffect) ? this.fJSONEffect.size : 0);
            this.fAudioInputs = audio_ptr;
            this.fAudioOutputs = this.fAudioInputs + this.getNumInputs() * this.gPtrSize;
            this.fAudioMixing = this.fAudioOutputs + this.getNumOutputs() * this.gPtrSize;
            const audio_inputs_ptr = this.fAudioMixing + this.getNumOutputs() * this.gPtrSize;
            const audio_outputs_ptr = audio_inputs_ptr + this.getNumInputs() * this.fBufferSize * this.gSampleSize;
            const audio_mixing_ptr = audio_outputs_ptr + this.getNumOutputs() * this.fBufferSize * this.gSampleSize;
            const HEAP = this.fInstance.memory.buffer;
            const HEAP32 = new Int32Array(HEAP);
            const HEAPF = (this.gSampleSize === 4) ? new Float32Array(HEAP) : new Float64Array(HEAP);
            if (this.getNumInputs() > 0) {
                for (let chan = 0; chan < this.getNumInputs(); chan++) {
                    HEAP32[(this.fAudioInputs >> 2) + chan] = audio_inputs_ptr + this.fBufferSize * this.gSampleSize * chan;
                }
                const dspInChans = HEAP32.subarray(this.fAudioInputs >> 2, (this.fAudioInputs + this.getNumInputs() * this.gPtrSize) >> 2);
                for (let chan = 0; chan < this.getNumInputs(); chan++) {
                    this.fInChannels[chan] = HEAPF.subarray(dspInChans[chan] >> Math.log2(this.gSampleSize), (dspInChans[chan] + this.fBufferSize * this.gSampleSize) >> Math.log2(this.gSampleSize));
                }
            }
            if (this.getNumOutputs() > 0) {
                for (let chan = 0; chan < this.getNumOutputs(); chan++) {
                    HEAP32[(this.fAudioOutputs >> 2) + chan] = audio_outputs_ptr + this.fBufferSize * this.gSampleSize * chan;
                    HEAP32[(this.fAudioMixing >> 2) + chan] = audio_mixing_ptr + this.fBufferSize * this.gSampleSize * chan;
                }
                const dspOutChans = HEAP32.subarray(this.fAudioOutputs >> 2, (this.fAudioOutputs + this.getNumOutputs() * this.gPtrSize) >> 2);
                for (let chan = 0; chan < this.getNumOutputs(); chan++) {
                    this.fOutChannels[chan] = HEAPF.subarray(dspOutChans[chan] >> Math.log2(this.gSampleSize), (dspOutChans[chan] + this.fBufferSize * this.gSampleSize) >> Math.log2(this.gSampleSize));
                }
            }
        }
        toString() {
            let str = "============== Poly Memory layout ==============";
            str += "this.fBufferSize: " + this.fBufferSize;
            str += "this.fJSONDsp.size: " + this.fJSONDsp.size;
            str += "this.fAudioInputs: " + this.fAudioInputs;
            str += "this.fAudioOutputs: " + this.fAudioOutputs;
            str += "this.fAudioMixing: " + this.fAudioMixing;
            return str;
        }
        allocVoice(voice) {
            this.fVoiceTable[voice].fDate++;
            this.fVoiceTable[voice].fNote = DspVoice.kActiveVoice;
            return voice;
        }
        getPlayingVoice(pitch) {
            let playing_voice = DspVoice.kNoVoice;
            let oldest_date_playing = Number.MAX_VALUE;
            for (let voice = 0; voice < this.fInstance.voices; voice++) {
                if (this.fVoiceTable[voice].fNote === pitch) {
                    if (this.fVoiceTable[voice].fDate < oldest_date_playing) {
                        oldest_date_playing = this.fVoiceTable[voice].fDate;
                        playing_voice = voice;
                    }
                }
            }
            return playing_voice;
        }
        getFreeVoice() {
            for (let voice = 0; voice < this.fInstance.voices; voice++) {
                if (this.fVoiceTable[voice].fNote === DspVoice.kFreeVoice)
                    return this.allocVoice(voice);
            }
            let voice_release = DspVoice.kNoVoice;
            let voice_playing = DspVoice.kNoVoice;
            let oldest_date_release = Number.MAX_VALUE;
            let oldest_date_playing = Number.MAX_VALUE;
            for (let voice = 0; voice < this.fInstance.voices; voice++) {
                if (this.fVoiceTable[voice].fNote === DspVoice.kReleaseVoice) {
                    if (this.fVoiceTable[voice].fDate < oldest_date_release) {
                        oldest_date_release = this.fVoiceTable[voice].fDate;
                        voice_release = voice;
                    }
                }
                else if (this.fVoiceTable[voice].fDate < oldest_date_playing) {
                    oldest_date_playing = this.fVoiceTable[voice].fDate;
                    voice_playing = voice;
                }
            }
            if (oldest_date_release !== Number.MAX_VALUE) {
                console.log(`Steal release voice : voice_date = ${this.fVoiceTable[voice_release].fDate} voice = ${voice_release}`);
                return this.allocVoice(voice_release);
            }
            if (oldest_date_playing !== Number.MAX_VALUE) {
                console.log(`Steal playing voice : voice_date = ${this.fVoiceTable[voice_playing].fDate} voice = ${voice_playing}`);
                return this.allocVoice(voice_playing);
            }
            return DspVoice.kNoVoice;
        }
        compute(input, output) {
            if (this.fDestroyed)
                return false;
            if (this.getNumInputs() > 0 && (!input || !input[0] || input[0].length === 0)) {
                return true;
            }
            if (this.getNumOutputs() > 0 && (!output || !output[0] || output[0].length === 0)) {
                return true;
            }
            if (input !== undefined) {
                for (let chan = 0; chan < Math.min(this.getNumInputs(), input.length); ++chan) {
                    const dspInput = this.fInChannels[chan];
                    dspInput.set(input[chan]);
                }
            }
            if (this.fComputeHandler)
                this.fComputeHandler(this.fBufferSize);
            this.fInstance.mixer_api.clearOutput(this.fBufferSize, this.getNumOutputs(), this.fAudioOutputs);
            this.fVoiceTable.forEach(voice => {
                if (voice.fNote !== DspVoice.kFreeVoice) {
                    voice.compute(this.fBufferSize, this.fAudioInputs, this.fAudioMixing);
                    voice.fLevel = this.fInstance.mixer_api.mixVoice(this.fBufferSize, this.getNumOutputs(), this.fAudioMixing, this.fAudioOutputs);
                    voice.fRelease -= this.fBufferSize;
                    if ((voice.fNote == DspVoice.kReleaseVoice) && ((voice.fLevel < DspVoice.VOICE_STOP_LEVEL) && (voice.fRelease < 0))) {
                        voice.fNote = DspVoice.kFreeVoice;
                    }
                }
            });
            if (this.fInstance.effect_api)
                this.fInstance.effect_api.compute(this.fEffect, this.fBufferSize, this.fAudioOutputs, this.fAudioOutputs);
            this.updateOutputs();
            if (output !== undefined) {
                for (let chan = 0; chan < Math.min(this.getNumOutputs(), output.length); chan++) {
                    const dspOutput = this.fOutChannels[chan];
                    output[chan].set(dspOutput);
                }
                if (this.fPlotHandler) {
                    this.fPlotHandler(output, this.fBufferNum++, (this.fCachedEvents.length ? this.fCachedEvents : undefined));
                    this.fCachedEvents = [];
                }
            }
            return true;
        }
        getNumInputs() {
            return this.fInstance.voice_api.getNumInputs(0);
        }
        getNumOutputs() {
            return this.fInstance.voice_api.getNumOutputs(0);
        }
        static findPath(o, p) {
            if (typeof o !== "object") {
                return false;
            }
            else if (o.address) {
                return (o.address === p);
            }
            else {
                for (const k in o) {
                    if (PolyDSPImp.findPath(o[k], p))
                        return true;
                }
                return false;
            }
        }
        setParamValue(path, value) {
            if (this.fPlotHandler)
                this.fCachedEvents.push({ type: "param", data: { path, value } });
            if (this.fJSONEffect && PolyDSPImp.findPath(this.fJSONEffect.ui, path) && this.fInstance.effect_api) {
                this.fInstance.effect_api.setParamValue(this.fEffect, this.fPathTable[path], value);
            }
            else {
                this.fVoiceTable.forEach(voice => { voice.setParamValue(this.fPathTable[path], value); });
            }
        }
        getParamValue(path) {
            if (this.fJSONEffect && PolyDSPImp.findPath(this.fJSONEffect.ui, path) && this.fInstance.effect_api) {
                return this.fInstance.effect_api.getParamValue(this.fEffect, this.fPathTable[path]);
            }
            else {
                return this.fVoiceTable[0].getParamValue(this.fPathTable[path]);
            }
        }
        getJSON() {
            const o = this.fJSONDsp;
            const e = this.fJSONEffect;
            const r = Object.assign({}, o);
            if (e) {
                r.ui = [{
                        type: "tgroup", label: "Sequencer", items: [
                            { type: "vgroup", label: "Instrument", items: o.ui },
                            { type: "vgroup", label: "Effect", items: e.ui }
                        ]
                    }];
            }
            else {
                r.ui = [{
                        type: "tgroup", label: "Polyphonic", items: [
                            { type: "vgroup", label: "Voices", items: o.ui }
                        ]
                    }];
            }
            return JSON.stringify(r);
        }
        getUI() {
            const o = this.fJSONDsp;
            const e = this.fJSONEffect;
            const r = Object.assign({}, o);
            if (e) {
                return [{
                        type: "tgroup", label: "Sequencer", items: [
                            { type: "vgroup", label: "Instrument", items: o.ui },
                            { type: "vgroup", label: "Effect", items: e.ui }
                        ]
                    }];
            }
            else {
                return [{
                        type: "tgroup", label: "Polyphonic", items: [
                            { type: "vgroup", label: "Voices", items: o.ui }
                        ]
                    }];
            }
        }
        getDescriptors() { return this.fDescriptor; }
        midiMessage(data) {
            const cmd = data[0] >> 4;
            const channel = data[0] & 0xf;
            const data1 = data[1];
            const data2 = data[2];
            if (cmd === 8 || (cmd === 9 && data2 === 0))
                return this.keyOff(channel, data1, data2);
            else if (cmd === 9)
                return this.keyOn(channel, data1, data2);
            else
                super.midiMessage(data);
        }
        ;
        ctrlChange(channel, ctrl, value) {
            if (ctrl === 123 || ctrl === 120) {
                this.allNotesOff(true);
            }
            else {
                super.ctrlChange(channel, ctrl, value);
            }
        }
        keyOn(channel, pitch, velocity) {
            const voice = this.getFreeVoice();
            this.fVoiceTable[voice].keyOn(pitch, velocity);
        }
        keyOff(channel, pitch, velocity) {
            const voice = this.getPlayingVoice(pitch);
            if (voice !== DspVoice.kNoVoice) {
                this.fVoiceTable[voice].keyOff();
            }
            else {
                console.log("Playing pitch = %d not found\n", pitch);
            }
        }
        allNotesOff(hard = true) {
            this.fCachedEvents.push({ type: "ctrlChange", data: [0, 123, 0] });
            this.fVoiceTable.forEach(voice => voice.keyOff(hard));
        }
    }
    Faust.PolyDSPImp = PolyDSPImp;
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    class FaustAudioWorkletNodeImp extends (window.AudioWorkletNode || null) {
        constructor(context, name, factory, options) {
            const JSONObj = Faust.createFaustJSON(factory.json);
            super(context, name, {
                numberOfInputs: JSONObj.inputs > 0 ? 1 : 0,
                numberOfOutputs: JSONObj.outputs > 0 ? 1 : 0,
                channelCount: Math.max(1, JSONObj.inputs),
                outputChannelCount: [JSONObj.outputs],
                channelCountMode: "explicit",
                channelInterpretation: "speakers",
                processorOptions: options
            });
            this.fJSONDsp = JSONObj;
            this.fJSON = factory.json;
            this.fOutputHandler = null;
            this.fComputeHandler = null;
            this.fPlotHandler = null;
            this.fDescriptor = [];
            this.fInputsItems = [];
            this.fUICallback = (item) => {
                if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
                    this.fInputsItems.push(item.address);
                    this.fDescriptor.push(item);
                }
            };
            Faust.BaseDSPImp.parseUI(this.fJSONDsp.ui, this.fUICallback);
            this.port.onmessage = (e) => {
                if (e.data.type === "param" && this.fOutputHandler) {
                    this.fOutputHandler(e.data.path, e.data.value);
                }
                else if (e.data.type === "plot" && this.fPlotHandler) {
                    this.fPlotHandler(e.data.value, e.data.index, e.data.events);
                }
            };
        }
        setOutputParamHandler(handler) {
            this.fOutputHandler = handler;
        }
        getOutputParamHandler() {
            return this.fOutputHandler;
        }
        setComputeHandler(handler) {
            this.fComputeHandler = handler;
        }
        getComputeHandler() {
            return this.fComputeHandler;
        }
        setPlotHandler(handler) {
            this.fPlotHandler = handler;
            if (this.fPlotHandler) {
                this.port.postMessage({ type: "setPlotHandler", data: true });
            }
            else {
                this.port.postMessage({ type: "setPlotHandler", data: false });
            }
        }
        getPlotHandler() {
            return this.fPlotHandler;
        }
        getNumInputs() {
            return this.fJSONDsp.inputs;
        }
        getNumOutputs() {
            return this.fJSONDsp.outputs;
        }
        compute(inputs, outputs) {
            return false;
        }
        metadata(handler) {
            if (this.fJSONDsp.meta) {
                this.fJSONDsp.meta.forEach(meta => handler(Object.keys(meta)[0], meta[Object.keys(meta)[0]]));
            }
        }
        midiMessage(data) {
            const cmd = data[0] >> 4;
            const channel = data[0] & 0xf;
            const data1 = data[1];
            const data2 = data[2];
            if (cmd === 11)
                this.ctrlChange(channel, data1, data2);
            else if (cmd === 14)
                this.pitchWheel(channel, data2 * 128.0 + data1);
            else
                this.port.postMessage({ type: "midi", data: data });
        }
        ctrlChange(channel, ctrl, value) {
            const e = { type: "ctrlChange", data: [channel, ctrl, value] };
            this.port.postMessage(e);
        }
        pitchWheel(channel, wheel) {
            const e = { type: "pitchWheel", data: [channel, wheel] };
            this.port.postMessage(e);
        }
        setParamValue(path, value) {
            const e = { type: "param", data: { path, value } };
            this.port.postMessage(e);
            const param = this.parameters.get(path);
            if (param)
                param.setValueAtTime(value, this.context.currentTime);
        }
        getParamValue(path) {
            const param = this.parameters.get(path);
            return (param) ? param.value : 0;
        }
        getParams() { return this.fInputsItems; }
        getJSON() { return this.fJSON; }
        getUI() { return this.fJSONDsp.ui; }
        getDescriptors() { return this.fDescriptor; }
        destroy() {
            this.port.postMessage({ type: "destroy" });
            this.port.close();
        }
    }
    class FaustMonoAudioWorkletNodeImp extends FaustAudioWorkletNodeImp {
        constructor(context, name, factory, sample_size) {
            super(context, name, factory, { name: name, factory: factory, sample_size: sample_size });
            this.onprocessorerror = (e) => {
                console.error("Error from " + this.fJSONDsp.name + " FaustMonoAudioWorkletNode");
                throw e;
            };
        }
    }
    Faust.FaustMonoAudioWorkletNodeImp = FaustMonoAudioWorkletNodeImp;
    class FaustPolyAudioWorkletNodeImp extends FaustAudioWorkletNodeImp {
        constructor(context, name, voice_factory, mixer_module, voices, sample_size, effect_factory) {
            super(context, name, voice_factory, {
                name: name,
                voice_factory: voice_factory,
                mixer_module: mixer_module,
                voices: voices,
                sample_size: sample_size,
                effect_factory: effect_factory
            });
            this.onprocessorerror = (e) => {
                console.error("Error from " + this.fJSONDsp.name + " FaustPolyAudioWorkletNode");
                throw e;
            };
            this.fJSONEffect = (effect_factory) ? Faust.createFaustJSON(effect_factory.json) : null;
            if (this.fJSONEffect) {
                Faust.BaseDSPImp.parseUI(this.fJSONEffect.ui, this.fUICallback);
            }
        }
        keyOn(channel, pitch, velocity) {
            const e = { type: "keyOn", data: [channel, pitch, velocity] };
            this.port.postMessage(e);
        }
        keyOff(channel, pitch, velocity) {
            const e = { type: "keyOff", data: [channel, pitch, velocity] };
            this.port.postMessage(e);
        }
        allNotesOff(hard) {
            const e = { type: "ctrlChange", data: [0, 123, 0] };
            this.port.postMessage(e);
        }
        getJSON() {
            const o = this.fJSONDsp;
            const e = this.fJSONEffect;
            const r = Object.assign({}, o);
            if (e) {
                r.ui = [{
                        type: "tgroup", label: "Sequencer", items: [
                            { type: "vgroup", label: "Instrument", items: o.ui },
                            { type: "vgroup", label: "Effect", items: e.ui }
                        ]
                    }];
            }
            else {
                r.ui = [{
                        type: "tgroup", label: "Polyphonic", items: [
                            { type: "vgroup", label: "Voices", items: o.ui }
                        ]
                    }];
            }
            return JSON.stringify(r);
        }
        getUI() {
            const o = this.fJSONDsp;
            const e = this.fJSONEffect;
            const r = Object.assign({}, o);
            if (e) {
                return [{
                        type: "tgroup", label: "Sequencer", items: [
                            { type: "vgroup", label: "Instrument", items: o.ui },
                            { type: "vgroup", label: "Effect", items: e.ui }
                        ]
                    }];
            }
            else {
                return [{
                        type: "tgroup", label: "Polyphonic", items: [
                            { type: "vgroup", label: "Voices", items: o.ui }
                        ]
                    }];
            }
        }
    }
    Faust.FaustPolyAudioWorkletNodeImp = FaustPolyAudioWorkletNodeImp;
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    Faust.FaustAudioWorkletProcessorGenerator = () => {
        class FaustConst {
        }
        FaustConst.dsp_name = faustData.dsp_name;
        FaustConst.dsp_JSON = faustData.dsp_JSON;
        FaustConst.effect_JSON = faustData.effect_JSON;
        class FaustAudioWorkletProcessorImp extends AudioWorkletProcessor {
            constructor(options) {
                super(options);
                this.port.onmessage = (e) => { this.handleMessageAux(e); };
            }
            static get parameterDescriptors() {
                const params = [];
                const callback = (item) => {
                    if (item.type === "vslider" || item.type === "hslider" || item.type === "nentry") {
                        params.push({ name: item.address, defaultValue: item.init || 0, minValue: item.min || 0, maxValue: item.max || 0 });
                    }
                    else if (item.type === "button" || item.type === "checkbox") {
                        params.push({ name: item.address, defaultValue: item.init || 0, minValue: 0, maxValue: 1 });
                    }
                };
                Faust.BaseDSPImp.parseUI(JSON.parse(FaustConst.dsp_JSON).ui, callback);
                if (FaustConst.effect_JSON)
                    Faust.BaseDSPImp.parseUI(JSON.parse(FaustConst.effect_JSON).ui, callback);
                return params;
            }
            process(inputs, outputs, parameters) {
                return this.fDSPCode.compute(inputs[0], outputs[0]);
            }
            handleMessageAux(e) {
                const msg = e.data;
                switch (msg.type) {
                    case "midi":
                        this.midiMessage(msg.data);
                        break;
                    case "ctrlChange":
                        this.ctrlChange(msg.data[0], msg.data[1], msg.data[2]);
                        break;
                    case "pitchWheel":
                        this.pitchWheel(msg.data[0], msg.data[1]);
                        break;
                    case "param":
                        this.setParamValue(msg.data.path, msg.data.value);
                        break;
                    case "setPlotHandler": {
                        if (msg.data) {
                            this.fDSPCode.setPlotHandler((output, index, events) => this.port.postMessage({ type: "plot", value: output, index: index, events: events }));
                        }
                        else {
                            this.fDSPCode.setPlotHandler(null);
                        }
                        break;
                    }
                    case "destroy": {
                        this.port.close();
                        this.fDSPCode.destroy();
                        break;
                    }
                    default:
                        break;
                }
            }
            setParamValue(path, value) {
                this.fDSPCode.setParamValue(path, value);
            }
            midiMessage(data) {
                this.fDSPCode.midiMessage(data);
            }
            ctrlChange(channel, ctrl, value) {
                this.fDSPCode.ctrlChange(channel, ctrl, value);
            }
            pitchWheel(channel, wheel) {
                this.fDSPCode.pitchWheel(channel, wheel);
            }
        }
        class FaustMonoAudioWorkletProcessorImp extends FaustAudioWorkletProcessorImp {
            constructor(options) {
                super(options);
                this.fDSPCode = Faust.createMonoDSP(new Faust.GeneratorImp().createSyncMonoDSPInstance(options.processorOptions.factory), sampleRate, options.processorOptions.sample_size, 128);
                this.fDSPCode.setOutputParamHandler((path, value) => this.port.postMessage({ path, value, type: "param" }));
            }
        }
        class FaustPolyAudioWorkletProcessorImp extends FaustAudioWorkletProcessorImp {
            constructor(options) {
                super(options);
                this.handleMessageAux = (e) => {
                    const msg = e.data;
                    switch (msg.type) {
                        case "keyOn":
                            this.keyOn(msg.data[0], msg.data[1], msg.data[2]);
                            break;
                        case "keyOff":
                            this.keyOff(msg.data[0], msg.data[1], msg.data[2]);
                            break;
                        default:
                            super.handleMessageAux(e);
                            break;
                    }
                };
                this.fDSPCode = Faust.createPolyDSP(new Faust.GeneratorImp().createSyncPolyDSPInstance(options.processorOptions.voice_factory, options.processorOptions.mixer_module, options.processorOptions.voices, options.processorOptions.effect_factory), sampleRate, options.processorOptions.sample_size, 128);
                this.port.onmessage = (e) => { this.handleMessageAux(e); };
                this.fDSPCode.setOutputParamHandler((path, value) => this.port.postMessage({ path, value, type: "param" }));
            }
            midiMessage(data) {
                const cmd = data[0] >> 4;
                const channel = data[0] & 0xf;
                const data1 = data[1];
                const data2 = data[2];
                if (cmd === 8 || (cmd === 9 && data2 === 0))
                    this.keyOff(channel, data1, data2);
                else if (cmd === 9)
                    this.keyOn(channel, data1, data2);
                else
                    super.midiMessage(data);
            }
            keyOn(channel, pitch, velocity) {
                this.fDSPCode.keyOn(channel, pitch, velocity);
            }
            keyOff(channel, pitch, velocity) {
                this.fDSPCode.keyOff(channel, pitch, velocity);
            }
            allNotesOff(hard) {
                this.fDSPCode.allNotesOff(hard);
            }
        }
        if (FaustConst.dsp_name.endsWith("_poly")) {
            registerProcessor(FaustConst.dsp_name || "mydsp_poly", FaustPolyAudioWorkletProcessorImp);
        }
        else {
            registerProcessor(FaustConst.dsp_name || "mydsp", FaustMonoAudioWorkletProcessorImp);
        }
    };
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    class FaustScriptProcessorNodeImp {
        setupNode(node) {
            this.fInputs = new Array(this.fDSPCode.getNumInputs());
            this.fOutputs = new Array(this.fDSPCode.getNumOutputs());
            let tmp = node;
            let spnode = tmp;
            spnode.onaudioprocess = (e) => {
                for (let chan = 0; chan < this.fDSPCode.getNumInputs(); chan++) {
                    this.fInputs[chan] = e.inputBuffer.getChannelData(chan);
                }
                for (let chan = 0; chan < this.fDSPCode.getNumOutputs(); chan++) {
                    this.fOutputs[chan] = e.outputBuffer.getChannelData(chan);
                }
                return this.fDSPCode.compute(this.fInputs, this.fOutputs);
            };
            node.setOutputParamHandler = (handler) => {
                this.fDSPCode.setOutputParamHandler(handler);
            };
            node.getOutputParamHandler = () => { return this.fDSPCode.getOutputParamHandler(); };
            node.setComputeHandler = (handler) => {
                this.fDSPCode.setComputeHandler(handler);
            };
            node.getComputeHandler = () => { return this.fDSPCode.getComputeHandler(); };
            node.setPlotHandler = (handler) => {
                this.fDSPCode.setPlotHandler(handler);
            };
            node.getPlotHandler = () => { return this.fDSPCode.getPlotHandler(); };
            node.getNumInputs = () => { return this.fDSPCode.getNumInputs(); };
            node.getNumOutputs = () => { return this.fDSPCode.getNumOutputs(); };
            node.metadata = (handler) => { };
            node.midiMessage = (data) => { this.fDSPCode.midiMessage(data); };
            node.ctrlChange = (chan, ctrl, value) => { this.fDSPCode.ctrlChange(chan, ctrl, value); };
            node.pitchWheel = (chan, value) => { this.fDSPCode.pitchWheel(chan, value); };
            node.setParamValue = (path, value) => { this.fDSPCode.setParamValue(path, value); };
            node.getParamValue = (path) => { return this.fDSPCode.getParamValue(path); };
            node.getParams = () => { return this.fDSPCode.getParams(); };
            node.getJSON = () => { return this.fDSPCode.getJSON(); };
            node.getDescriptors = () => { return this.fDSPCode.getDescriptors(); };
            node.getUI = () => { return this.fDSPCode.getUI(); };
            node.destroy = () => { this.fDSPCode.destroy(); };
        }
    }
    class FaustMonoScriptProcessorNodeImp extends FaustScriptProcessorNodeImp {
        init(context, instance, buffer_size) {
            const _super = Object.create(null, {
                setupNode: { get: () => super.setupNode }
            });
            return __awaiter(this, void 0, void 0, function* () {
                try {
                    this.fDSPCode = instance;
                    let node = context.createScriptProcessor(buffer_size, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs());
                    let faustnode = node;
                    _super.setupNode.call(this, faustnode);
                    return faustnode;
                }
                catch (e) {
                    console.log("Error in FaustMonoScriptProcessorNodeImp createScriptProcessor: " + e.message);
                    return null;
                }
            });
        }
    }
    Faust.FaustMonoScriptProcessorNodeImp = FaustMonoScriptProcessorNodeImp;
    class FaustPolyScriptProcessorNodeImp extends FaustScriptProcessorNodeImp {
        init(context, instance, buffer_size) {
            const _super = Object.create(null, {
                setupNode: { get: () => super.setupNode }
            });
            return __awaiter(this, void 0, void 0, function* () {
                try {
                    this.fDSPCode = instance;
                    let node = context.createScriptProcessor(buffer_size, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs());
                    let faustnode = node;
                    _super.setupNode.call(this, faustnode);
                    faustnode.keyOn = (channel, pitch, velocity) => {
                        this.fDSPCode.keyOn(channel, pitch, velocity);
                    };
                    faustnode.keyOff = (channel, pitch, velocity) => {
                        this.fDSPCode.keyOff(channel, pitch, velocity);
                    };
                    faustnode.allNotesOff = (hard) => {
                        this.fDSPCode.allNotesOff(hard);
                    };
                    return faustnode;
                }
                catch (e) {
                    console.log("Error in FaustPolyScriptProcessorNodeImp createScriptProcessor: " + e.message);
                    return null;
                }
            });
        }
    }
    Faust.FaustPolyScriptProcessorNodeImp = FaustPolyScriptProcessorNodeImp;
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    class FaustOfflineProcessorImp {
        constructor(instance, buffer_size) {
            this.fDSPCode = instance;
            this.fBufferSize = buffer_size;
            this.fInputs = new Array(this.fDSPCode.getNumInputs()).fill(null).map(() => new Float32Array(buffer_size));
            this.fOutputs = new Array(this.fDSPCode.getNumOutputs()).fill(null).map(() => new Float32Array(buffer_size));
        }
        plot(size) {
            const plotted = new Array(this.fDSPCode.getNumOutputs()).fill(null).map(() => new Float32Array(size));
            for (let frame = 0; frame < size; frame += this.fBufferSize) {
                this.fDSPCode.compute(this.fInputs, this.fOutputs);
                for (let chan = 0; chan < plotted.length; chan++) {
                    plotted[chan].set(size - frame > this.fBufferSize ? this.fOutputs[chan] : this.fOutputs[chan].subarray(0, size - frame), frame);
                }
            }
            return plotted;
        }
    }
    Faust.FaustOfflineProcessorImp = FaustOfflineProcessorImp;
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    function createMonoFactory() { return new MonoFactoryImp(); }
    Faust.createMonoFactory = createMonoFactory;
    function createPolyFactory() { return new PolyFactoryImp(); }
    Faust.createPolyFactory = createPolyFactory;
    class MonoFactoryImp {
        constructor() {
            this.fFactory = null;
        }
        compileNode(context, name, compiler, dsp_code, args, sp, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                this.fFactory = yield compiler.createMonoDSPFactory(name, dsp_code, args);
                return (this.fFactory) ? this.createNode(context, name, this.fFactory, sp, buffer_size) : null;
            });
        }
        createNode(context, name_aux, factory, sp, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                const JSONObj = Faust.createFaustJSON(factory.json);
                const sample_size = JSONObj.compile_options.match("-double") ? 8 : 4;
                if (sp) {
                    buffer_size = (buffer_size) ? buffer_size : 1024;
                    const instance = yield Faust.createGenerator().createAsyncMonoDSPInstance(factory);
                    const mono_dsp = Faust.createMonoDSP(instance, context.sampleRate, sample_size, buffer_size);
                    return new Faust.FaustMonoScriptProcessorNodeImp().init(context, mono_dsp, buffer_size);
                }
                else {
                    const name = name_aux + factory.cfactory.toString();
                    if (!MonoFactoryImp.gWorkletProcessors.has(name)) {
                        try {
                            const processor_code = `
                            // Create a Faust namespace
                            let Faust = {};
                            // DSP name and JSON string for DSP are generated
                            const faustData = { dsp_name: '${name}', dsp_JSON: '${factory.json}' };
                            // Implementation needed classes of functions
                            ${Faust.BaseDSPImp.toString()}
                            ${Faust.MonoDSPImp.toString()}
                            ${Faust.GeneratorImp.toString()} 
                            ${Faust.InstanceAPIImpl.toString()} 
                            ${Faust.createMonoDSP.toString()} 
                            ${Faust.createFaustJSON.toString()} 
                            // Put them in Faust namespace
                            Faust.BaseDSPImp = BaseDSPImp;
                            Faust.MonoDSPImp = MonoDSPImp;
                            Faust.GeneratorImp = GeneratorImp;
                            Faust.createMonoDSP = createMonoDSP;
                            Faust.createFaustJSON = createFaustJSON;
                            // Generate the actual AudioWorkletProcessor code
                            (${Faust.FaustAudioWorkletProcessorGenerator.toString()})(); `;
                            const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                            yield context.audioWorklet.addModule(url);
                            MonoFactoryImp.gWorkletProcessors.add(name);
                        }
                        catch (e) {
                            console.error("=> exception raised while running createMonoNode: " + e);
                            return null;
                        }
                    }
                    return new Faust.FaustMonoAudioWorkletNodeImp(context, name, factory, sample_size);
                }
            });
        }
        createOfflineProcessor(factory, sample_rate, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                const instance = yield Faust.createGenerator().createAsyncMonoDSPInstance(factory);
                const JSONObj = Faust.createFaustJSON(factory.json);
                const sample_size = JSONObj.compile_options.match("-double") ? 8 : 4;
                const mono_dsp = Faust.createMonoDSP(instance, sample_rate, sample_size, buffer_size);
                return new Faust.FaustOfflineProcessorImp(mono_dsp, buffer_size);
            });
        }
        getFactory() {
            return this.fFactory;
        }
    }
    MonoFactoryImp.gWorkletProcessors = new Set();
    class PolyFactoryImp {
        constructor() {
            this.fVoiceFactory = null;
            this.fEffectFactory = null;
        }
        compileNode(context, name, compiler, dsp_code, effect_code, args, voices, sp, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                const voice_dsp = dsp_code;
                const effect_dsp = effect_code ? effect_code :
                    `adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;
                                adaptor(F,G) = adapt(outputs(F),inputs(G));
                                dsp_code = environment{${dsp_code}};
                                process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;`;
                const voice_factory = yield compiler.createPolyDSPFactory(name, voice_dsp, args);
                if (!voice_factory)
                    return null;
                const effect_factory = yield compiler.createPolyDSPFactory(name, effect_dsp, args);
                const JSONObj = Faust.createFaustJSON(voice_factory.json);
                const is_double = JSONObj.compile_options.match("-double");
                const mixer_module = yield Faust.createGenerator().loadDSPMixer((is_double) ? '/usr/rsrc/mixer64.wasm' : '/usr/rsrc/mixer32.wasm');
                return (mixer_module) ? this.createNode(context, name, voice_factory, mixer_module, voices, sp, ((effect_factory) ? effect_factory : undefined), buffer_size) : null;
            });
        }
        createNode(context, name_aux, voice_factory, mixer_module, voices, sp, effect_factory, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                const JSONObj = Faust.createFaustJSON(voice_factory.json);
                const sample_size = JSONObj.compile_options.match("-double") ? 8 : 4;
                if (sp) {
                    buffer_size = (buffer_size) ? buffer_size : 1024;
                    const instance = yield Faust.createGenerator().createAsyncPolyDSPInstance(voice_factory, mixer_module, voices, effect_factory);
                    const poly_dsp = Faust.createPolyDSP(instance, context.sampleRate, sample_size, buffer_size);
                    return new Faust.FaustPolyScriptProcessorNodeImp().init(context, poly_dsp, buffer_size);
                }
                else {
                    const name = name_aux + voice_factory.cfactory.toString() + "_poly";
                    if (!PolyFactoryImp.gWorkletProcessors.has(name)) {
                        try {
                            const processor_code = `
                            // Create a Faust namespace
                            let Faust = {};
                            // DSP name and JSON strings for DSP and (possible) effect are generated
                            const faustData = { dsp_name: '${name}', dsp_JSON: '${voice_factory.json}', effect_JSON: '${(effect_factory) ? effect_factory.json : ""}'};
                            // Implementation needed classes of functions
                            ${Faust.BaseDSPImp.toString()}
                            ${Faust.PolyDSPImp.toString()}
                            ${Faust.DspVoice.toString()}
                            ${Faust.GeneratorImp.toString()} 
                            ${Faust.InstanceAPIImpl.toString()} 
                            ${Faust.createPolyDSP.toString()}
                            ${Faust.createFaustJSON.toString()}  
                            // Put them in Faust namespace
                            Faust.BaseDSPImp = BaseDSPImp;
                            Faust.PolyDSPImp = PolyDSPImp;
                            Faust.GeneratorImp = GeneratorImp;
                            Faust.createPolyDSP = createPolyDSP;
                            Faust.createFaustJSON = createFaustJSON;
                            // Generate the actual AudioWorkletProcessor code
                            (${Faust.FaustAudioWorkletProcessorGenerator.toString()})();`;
                            const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                            yield context.audioWorklet.addModule(url);
                            PolyFactoryImp.gWorkletProcessors.add(name);
                        }
                        catch (e) {
                            console.error("=> exception raised while running createPolyNode: " + e);
                            return null;
                        }
                    }
                    return new Faust.FaustPolyAudioWorkletNodeImp(context, name, voice_factory, mixer_module, voices, sample_size, effect_factory);
                }
            });
        }
        getVoiceFactory() {
            return this.fVoiceFactory;
        }
        getEffectFactory() {
            return this.fEffectFactory;
        }
    }
    PolyFactoryImp.gWorkletProcessors = new Set();
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    function compileAudioNode(audioCtx, module, dsp_code, effect_code, voices, is_double) {
        let sp = typeof (window.AudioWorkletNode) == "undefined";
        let libfaust = Faust.createLibFaust(module);
        if (libfaust) {
            let compiler = Faust.createCompiler(libfaust);
            const argv = (is_double) ? "-double -ftz 2" : "-ftz 2";
            if (voices === 0) {
                return Faust.createMonoFactory().compileNode(audioCtx, "FaustDSP", compiler, dsp_code, argv, sp, 0);
            }
            else {
                return Faust.createPolyFactory().compileNode(audioCtx, "FaustDSP", compiler, dsp_code, effect_code, argv, voices, sp, 0);
            }
        }
        return new Promise(() => { return null; });
    }
    Faust.compileAudioNode = compileAudioNode;
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    function hash(data) {
        let h = sha256.create();
        h.update(data);
        return h.hex();
    }
    Faust.hash = hash;
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    function createSVGDiagrams(libfaust, name, dsp_code, args) {
        return new SVGDiagramsImp(libfaust, name, dsp_code, args);
    }
    Faust.createSVGDiagrams = createSVGDiagrams;
    class SVGDiagramsImp {
        constructor(libfaust, name, dsp_code, args) {
            this.fLibFaust = libfaust;
            let compiler = Faust.createCompiler(libfaust);
            this.fSuccess = compiler.generateAuxFiles(name, dsp_code, "-lang wasm -svg " + args);
            this.fError = (this.fSuccess) ? "" : compiler.getErrorMessage();
            this.fFolder = name + "-svg";
        }
        debug(path) {
            console.log("getSVG file: " + path);
            let content = this.fLibFaust.module().FS.readdir(".");
            console.log("getSVG dir: " + content);
        }
        error() { return this.fError; }
        success() { return this.fSuccess; }
        getSVG(name) {
            if (!name)
                name = this.fFolder + "/process.svg";
            if (this.fSuccess) {
                let path = name;
                try {
                    return this.fLibFaust.module().FS.readFile(path, { encoding: "utf8" });
                }
                catch (e) {
                    console.log("SVGDiagrams: can't read file " + path);
                    return "";
                }
            }
            else {
                return "SVGDiagrams: not a valid diagram: " + this.fError;
            }
        }
    }
})(Faust || (Faust = {}));
var Faust;
(function (Faust) {
    function createMonoWAPFactory(context, baseURL = "") {
        return new MonoWAPFactoryImp(context, baseURL);
    }
    Faust.createMonoWAPFactory = createMonoWAPFactory;
    class MonoWAPFactoryImp {
        constructor(context, baseURL = "") {
            this.fContext = context;
            this.fBaseURL = baseURL;
        }
        makeMonoWAP(node) {
            const wap = node;
            if (wap) {
                wap.getMetadata = () => __awaiter(this, void 0, void 0, function* () {
                    const real_url = (wap.fBaseURL === "") ? "main.json" : (wap.fBaseURL + "/main.json");
                    const json_file = yield fetch(real_url);
                    return json_file.json();
                });
                wap.setParam = (path, value) => {
                    wap.setParamValue(path, value);
                };
                wap.getParam = (path) => {
                    return wap.getParamValue(path);
                };
                wap.inputChannelCount = () => {
                    return wap.getNumInputs();
                };
                wap.outputChannelCount = () => {
                    return wap.getNumOutputs();
                };
                wap.onMidi = (data) => {
                    return wap.midiMessage(data);
                };
                wap.getDescriptor = () => {
                    let desc = {};
                    const descriptor = wap.getDescriptors();
                    for (const item in descriptor) {
                        if (descriptor.hasOwnProperty(item)) {
                            if (descriptor[item].label != "bypass") {
                                desc = Object.assign({ [descriptor[item].label]: { minValue: descriptor[item].min, maxValue: descriptor[item].max, defaultValue: descriptor[item].init } }, desc);
                            }
                        }
                    }
                    return desc;
                };
                return wap;
            }
            else {
                return null;
            }
        }
        compileMonoWAPNode(context, name, compiler, dsp_code, args, sp, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                const node = yield Faust.createMonoFactory().compileNode(context, name, compiler, dsp_code, args, sp, buffer_size);
                return this.makeMonoWAP(node);
            });
        }
        createMonoWAPNode(context, name, factory, sp, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                const node = yield Faust.createMonoFactory().createNode(context, name, factory, sp, buffer_size);
                return this.makeMonoWAP(node);
            });
        }
        load(wasm_path_aux, json_path_aux, sp = false) {
            return __awaiter(this, void 0, void 0, function* () {
                const wasm_path = (this.fBaseURL === "") ? wasm_path_aux : (this.fBaseURL + '/' + wasm_path_aux);
                const json_path = (this.fBaseURL === "") ? json_path_aux : (this.fBaseURL + '/' + json_path_aux);
                const factory = yield Faust.createGenerator().loadDSPFactory(wasm_path, json_path);
                if (factory) {
                    const node = yield this.createMonoWAPNode(this.fContext, "FausDSP", factory, sp, 1024);
                    if (node)
                        node.fBaseURL = this.fBaseURL;
                    return node;
                }
                else {
                    return null;
                }
            });
        }
    }
    function createPolyWAPFactory(context, baseURL = "") {
        return new PolyWAPFactoryImp(context, baseURL);
    }
    Faust.createPolyWAPFactory = createPolyWAPFactory;
    class PolyWAPFactoryImp {
        constructor(context, baseURL = "") {
            this.fContext = context;
            this.fBaseURL = baseURL;
        }
        makePolyWAP(node) {
            const wap = node;
            if (wap) {
                wap.getMetadata = () => __awaiter(this, void 0, void 0, function* () {
                    const real_url = (wap.fBaseURL === "") ? "main.json" : (wap.fBaseURL + "/main.json");
                    const json_file = yield fetch(real_url);
                    return json_file.json();
                });
                wap.setParam = (path, value) => {
                    wap.setParamValue(path, value);
                };
                wap.getParam = (path) => {
                    return wap.getParamValue(path);
                };
                wap.inputChannelCount = () => {
                    return wap.getNumInputs();
                };
                wap.outputChannelCount = () => {
                    return wap.getNumOutputs();
                };
                wap.onMidi = (data) => {
                    return wap.midiMessage(data);
                };
                wap.getDescriptor = () => {
                    let desc = {};
                    const descriptor = wap.getDescriptors();
                    for (const item in descriptor) {
                        if (descriptor.hasOwnProperty(item)) {
                            if (descriptor[item].label != "bypass") {
                                desc = Object.assign({ [descriptor[item].label]: { minValue: descriptor[item].min, maxValue: descriptor[item].max, defaultValue: descriptor[item].init } }, desc);
                            }
                        }
                    }
                    return desc;
                };
                return wap;
            }
            else {
                return null;
            }
        }
        createPolyWAPNode(context, name_aux, voice_factory, mixer_module, voices, sp, effect_factory, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                const node = yield Faust.createPolyFactory().createNode(context, "FaustDSP", voice_factory, mixer_module, voices, sp, effect_factory, buffer_size);
                return this.makePolyWAP(node);
            });
        }
        load(voice_path_aux, voice_json_path_aux, effect_path_aux, effect_json_path_aux, mixer32_path_aux, mixer64_path_aux, voices, sp, buffer_size) {
            return __awaiter(this, void 0, void 0, function* () {
                const voice_path = (this.fBaseURL === "") ? voice_path_aux : (this.fBaseURL + '/' + voice_path_aux);
                const voice_json_path = (this.fBaseURL === "") ? voice_json_path_aux : (this.fBaseURL + '/' + voice_json_path_aux);
                const effect_path = (this.fBaseURL === "") ? effect_path_aux : (this.fBaseURL + '/' + effect_path_aux);
                const effect_json_path = (this.fBaseURL === "") ? effect_json_path_aux : (this.fBaseURL + '/' + effect_json_path_aux);
                const gen = Faust.createGenerator();
                const voice_factory = yield gen.loadDSPFactory(voice_path, voice_json_path);
                if (!voice_factory)
                    return null;
                const effect_factory = yield gen.loadDSPFactory(effect_path, effect_json_path);
                const JSONObj = Faust.createFaustJSON(voice_factory.json);
                const is_double = JSONObj.compile_options.match("-double");
                let mixer_path = null;
                if (is_double) {
                    mixer_path = (this.fBaseURL === "") ? mixer64_path_aux : (this.fBaseURL + '/' + mixer64_path_aux);
                }
                else {
                    mixer_path = (this.fBaseURL === "") ? mixer32_path_aux : (this.fBaseURL + '/' + mixer32_path_aux);
                }
                const mixer_module = yield gen.loadDSPMixer(mixer_path);
                if (!mixer_module)
                    return null;
                const node = yield this.createPolyWAPNode(this.fContext, "FaustDSP", voice_factory, mixer_module, voices, sp, ((effect_factory) ? effect_factory : undefined), 1024);
                if (node)
                    node.fBaseURL = this.fBaseURL;
                return node;
            });
        }
    }
})(Faust || (Faust = {}));
(function () {
    'use strict';
    var ERROR = 'input is invalid type';
    var WINDOW = typeof window === 'object';
    var root = WINDOW ? window : {};
    if (root.JS_SHA256_NO_WINDOW) {
        WINDOW = false;
    }
    var WEB_WORKER = !WINDOW && typeof self === 'object';
    var NODE_JS = !root.JS_SHA256_NO_NODE_JS && typeof process === 'object' && process.versions && process.versions.node;
    if (NODE_JS) {
        root = global;
    }
    else if (WEB_WORKER) {
        root = self;
    }
    var COMMON_JS = !root.JS_SHA256_NO_COMMON_JS && typeof module === 'object' && module.exports;
    var AMD = typeof define === 'function' && define.amd;
    var ARRAY_BUFFER = !root.JS_SHA256_NO_ARRAY_BUFFER && typeof ArrayBuffer !== 'undefined';
    var HEX_CHARS = '0123456789abcdef'.split('');
    var EXTRA = [-2147483648, 8388608, 32768, 128];
    var SHIFT = [24, 16, 8, 0];
    var K = [
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    ];
    var OUTPUT_TYPES = ['hex', 'array', 'digest', 'arrayBuffer'];
    var blocks = [];
    if (root.JS_SHA256_NO_NODE_JS || !Array.isArray) {
        Array.isArray = function (obj) {
            return Object.prototype.toString.call(obj) === '[object Array]';
        };
    }
    if (ARRAY_BUFFER && (root.JS_SHA256_NO_ARRAY_BUFFER_IS_VIEW || !ArrayBuffer.isView)) {
        ArrayBuffer.isView = function (obj) {
            return typeof obj === 'object' && obj.buffer && obj.buffer.constructor === ArrayBuffer;
        };
    }
    var createOutputMethod = function (outputType, is224) {
        return function (message) {
            return new Sha256(is224, true).update(message)[outputType]();
        };
    };
    var createMethod = function (is224) {
        var method = createOutputMethod('hex', is224);
        if (NODE_JS) {
            method = nodeWrap(method, is224);
        }
        method.create = function () {
            return new Sha256(is224);
        };
        method.update = function (message) {
            return method.create().update(message);
        };
        for (var i = 0; i < OUTPUT_TYPES.length; ++i) {
            var type = OUTPUT_TYPES[i];
            method[type] = createOutputMethod(type, is224);
        }
        return method;
    };
    var nodeWrap = function (method, is224) {
        var crypto = eval("require('crypto')");
        var Buffer = eval("require('buffer').Buffer");
        var algorithm = is224 ? 'sha224' : 'sha256';
        var nodeMethod = function (message) {
            if (typeof message === 'string') {
                return crypto.createHash(algorithm).update(message, 'utf8').digest('hex');
            }
            else {
                if (message === null || message === undefined) {
                    throw new Error(ERROR);
                }
                else if (message.constructor === ArrayBuffer) {
                    message = new Uint8Array(message);
                }
            }
            if (Array.isArray(message) || ArrayBuffer.isView(message) ||
                message.constructor === Buffer) {
                return crypto.createHash(algorithm).update(new Buffer(message)).digest('hex');
            }
            else {
                return method(message);
            }
        };
        return nodeMethod;
    };
    var createHmacOutputMethod = function (outputType, is224) {
        return function (key, message) {
            return new HmacSha256(key, is224, true).update(message)[outputType]();
        };
    };
    var createHmacMethod = function (is224) {
        var method = createHmacOutputMethod('hex', is224);
        method.create = function (key) {
            return new HmacSha256(key, is224);
        };
        method.update = function (key, message) {
            return method.create(key).update(message);
        };
        for (var i = 0; i < OUTPUT_TYPES.length; ++i) {
            var type = OUTPUT_TYPES[i];
            method[type] = createHmacOutputMethod(type, is224);
        }
        return method;
    };
    function Sha256(is224, sharedMemory) {
        if (sharedMemory) {
            blocks[0] = blocks[16] = blocks[1] = blocks[2] = blocks[3] =
                blocks[4] = blocks[5] = blocks[6] = blocks[7] =
                    blocks[8] = blocks[9] = blocks[10] = blocks[11] =
                        blocks[12] = blocks[13] = blocks[14] = blocks[15] = 0;
            this.blocks = blocks;
        }
        else {
            this.blocks = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
        }
        if (is224) {
            this.h0 = 0xc1059ed8;
            this.h1 = 0x367cd507;
            this.h2 = 0x3070dd17;
            this.h3 = 0xf70e5939;
            this.h4 = 0xffc00b31;
            this.h5 = 0x68581511;
            this.h6 = 0x64f98fa7;
            this.h7 = 0xbefa4fa4;
        }
        else {
            this.h0 = 0x6a09e667;
            this.h1 = 0xbb67ae85;
            this.h2 = 0x3c6ef372;
            this.h3 = 0xa54ff53a;
            this.h4 = 0x510e527f;
            this.h5 = 0x9b05688c;
            this.h6 = 0x1f83d9ab;
            this.h7 = 0x5be0cd19;
        }
        this.block = this.start = this.bytes = this.hBytes = 0;
        this.finalized = this.hashed = false;
        this.first = true;
        this.is224 = is224;
    }
    Sha256.prototype.update = function (message) {
        if (this.finalized) {
            return;
        }
        var notString, type = typeof message;
        if (type !== 'string') {
            if (type === 'object') {
                if (message === null) {
                    throw new Error(ERROR);
                }
                else if (ARRAY_BUFFER && message.constructor === ArrayBuffer) {
                    message = new Uint8Array(message);
                }
                else if (!Array.isArray(message)) {
                    if (!ARRAY_BUFFER || !ArrayBuffer.isView(message)) {
                        throw new Error(ERROR);
                    }
                }
            }
            else {
                throw new Error(ERROR);
            }
            notString = true;
        }
        var code, index = 0, i, length = message.length, blocks = this.blocks;
        while (index < length) {
            if (this.hashed) {
                this.hashed = false;
                blocks[0] = this.block;
                blocks[16] = blocks[1] = blocks[2] = blocks[3] =
                    blocks[4] = blocks[5] = blocks[6] = blocks[7] =
                        blocks[8] = blocks[9] = blocks[10] = blocks[11] =
                            blocks[12] = blocks[13] = blocks[14] = blocks[15] = 0;
            }
            if (notString) {
                for (i = this.start; index < length && i < 64; ++index) {
                    blocks[i >> 2] |= message[index] << SHIFT[i++ & 3];
                }
            }
            else {
                for (i = this.start; index < length && i < 64; ++index) {
                    code = message.charCodeAt(index);
                    if (code < 0x80) {
                        blocks[i >> 2] |= code << SHIFT[i++ & 3];
                    }
                    else if (code < 0x800) {
                        blocks[i >> 2] |= (0xc0 | (code >> 6)) << SHIFT[i++ & 3];
                        blocks[i >> 2] |= (0x80 | (code & 0x3f)) << SHIFT[i++ & 3];
                    }
                    else if (code < 0xd800 || code >= 0xe000) {
                        blocks[i >> 2] |= (0xe0 | (code >> 12)) << SHIFT[i++ & 3];
                        blocks[i >> 2] |= (0x80 | ((code >> 6) & 0x3f)) << SHIFT[i++ & 3];
                        blocks[i >> 2] |= (0x80 | (code & 0x3f)) << SHIFT[i++ & 3];
                    }
                    else {
                        code = 0x10000 + (((code & 0x3ff) << 10) | (message.charCodeAt(++index) & 0x3ff));
                        blocks[i >> 2] |= (0xf0 | (code >> 18)) << SHIFT[i++ & 3];
                        blocks[i >> 2] |= (0x80 | ((code >> 12) & 0x3f)) << SHIFT[i++ & 3];
                        blocks[i >> 2] |= (0x80 | ((code >> 6) & 0x3f)) << SHIFT[i++ & 3];
                        blocks[i >> 2] |= (0x80 | (code & 0x3f)) << SHIFT[i++ & 3];
                    }
                }
            }
            this.lastByteIndex = i;
            this.bytes += i - this.start;
            if (i >= 64) {
                this.block = blocks[16];
                this.start = i - 64;
                this.hash();
                this.hashed = true;
            }
            else {
                this.start = i;
            }
        }
        if (this.bytes > 4294967295) {
            this.hBytes += this.bytes / 4294967296 << 0;
            this.bytes = this.bytes % 4294967296;
        }
        return this;
    };
    Sha256.prototype.finalize = function () {
        if (this.finalized) {
            return;
        }
        this.finalized = true;
        var blocks = this.blocks, i = this.lastByteIndex;
        blocks[16] = this.block;
        blocks[i >> 2] |= EXTRA[i & 3];
        this.block = blocks[16];
        if (i >= 56) {
            if (!this.hashed) {
                this.hash();
            }
            blocks[0] = this.block;
            blocks[16] = blocks[1] = blocks[2] = blocks[3] =
                blocks[4] = blocks[5] = blocks[6] = blocks[7] =
                    blocks[8] = blocks[9] = blocks[10] = blocks[11] =
                        blocks[12] = blocks[13] = blocks[14] = blocks[15] = 0;
        }
        blocks[14] = this.hBytes << 3 | this.bytes >>> 29;
        blocks[15] = this.bytes << 3;
        this.hash();
    };
    Sha256.prototype.hash = function () {
        var a = this.h0, b = this.h1, c = this.h2, d = this.h3, e = this.h4, f = this.h5, g = this.h6, h = this.h7, blocks = this.blocks, j, s0, s1, maj, t1, t2, ch, ab, da, cd, bc;
        for (j = 16; j < 64; ++j) {
            t1 = blocks[j - 15];
            s0 = ((t1 >>> 7) | (t1 << 25)) ^ ((t1 >>> 18) | (t1 << 14)) ^ (t1 >>> 3);
            t1 = blocks[j - 2];
            s1 = ((t1 >>> 17) | (t1 << 15)) ^ ((t1 >>> 19) | (t1 << 13)) ^ (t1 >>> 10);
            blocks[j] = blocks[j - 16] + s0 + blocks[j - 7] + s1 << 0;
        }
        bc = b & c;
        for (j = 0; j < 64; j += 4) {
            if (this.first) {
                if (this.is224) {
                    ab = 300032;
                    t1 = blocks[0] - 1413257819;
                    h = t1 - 150054599 << 0;
                    d = t1 + 24177077 << 0;
                }
                else {
                    ab = 704751109;
                    t1 = blocks[0] - 210244248;
                    h = t1 - 1521486534 << 0;
                    d = t1 + 143694565 << 0;
                }
                this.first = false;
            }
            else {
                s0 = ((a >>> 2) | (a << 30)) ^ ((a >>> 13) | (a << 19)) ^ ((a >>> 22) | (a << 10));
                s1 = ((e >>> 6) | (e << 26)) ^ ((e >>> 11) | (e << 21)) ^ ((e >>> 25) | (e << 7));
                ab = a & b;
                maj = ab ^ (a & c) ^ bc;
                ch = (e & f) ^ (~e & g);
                t1 = h + s1 + ch + K[j] + blocks[j];
                t2 = s0 + maj;
                h = d + t1 << 0;
                d = t1 + t2 << 0;
            }
            s0 = ((d >>> 2) | (d << 30)) ^ ((d >>> 13) | (d << 19)) ^ ((d >>> 22) | (d << 10));
            s1 = ((h >>> 6) | (h << 26)) ^ ((h >>> 11) | (h << 21)) ^ ((h >>> 25) | (h << 7));
            da = d & a;
            maj = da ^ (d & b) ^ ab;
            ch = (h & e) ^ (~h & f);
            t1 = g + s1 + ch + K[j + 1] + blocks[j + 1];
            t2 = s0 + maj;
            g = c + t1 << 0;
            c = t1 + t2 << 0;
            s0 = ((c >>> 2) | (c << 30)) ^ ((c >>> 13) | (c << 19)) ^ ((c >>> 22) | (c << 10));
            s1 = ((g >>> 6) | (g << 26)) ^ ((g >>> 11) | (g << 21)) ^ ((g >>> 25) | (g << 7));
            cd = c & d;
            maj = cd ^ (c & a) ^ da;
            ch = (g & h) ^ (~g & e);
            t1 = f + s1 + ch + K[j + 2] + blocks[j + 2];
            t2 = s0 + maj;
            f = b + t1 << 0;
            b = t1 + t2 << 0;
            s0 = ((b >>> 2) | (b << 30)) ^ ((b >>> 13) | (b << 19)) ^ ((b >>> 22) | (b << 10));
            s1 = ((f >>> 6) | (f << 26)) ^ ((f >>> 11) | (f << 21)) ^ ((f >>> 25) | (f << 7));
            bc = b & c;
            maj = bc ^ (b & d) ^ cd;
            ch = (f & g) ^ (~f & h);
            t1 = e + s1 + ch + K[j + 3] + blocks[j + 3];
            t2 = s0 + maj;
            e = a + t1 << 0;
            a = t1 + t2 << 0;
        }
        this.h0 = this.h0 + a << 0;
        this.h1 = this.h1 + b << 0;
        this.h2 = this.h2 + c << 0;
        this.h3 = this.h3 + d << 0;
        this.h4 = this.h4 + e << 0;
        this.h5 = this.h5 + f << 0;
        this.h6 = this.h6 + g << 0;
        this.h7 = this.h7 + h << 0;
    };
    Sha256.prototype.hex = function () {
        this.finalize();
        var h0 = this.h0, h1 = this.h1, h2 = this.h2, h3 = this.h3, h4 = this.h4, h5 = this.h5, h6 = this.h6, h7 = this.h7;
        var hex = HEX_CHARS[(h0 >> 28) & 0x0F] + HEX_CHARS[(h0 >> 24) & 0x0F] +
            HEX_CHARS[(h0 >> 20) & 0x0F] + HEX_CHARS[(h0 >> 16) & 0x0F] +
            HEX_CHARS[(h0 >> 12) & 0x0F] + HEX_CHARS[(h0 >> 8) & 0x0F] +
            HEX_CHARS[(h0 >> 4) & 0x0F] + HEX_CHARS[h0 & 0x0F] +
            HEX_CHARS[(h1 >> 28) & 0x0F] + HEX_CHARS[(h1 >> 24) & 0x0F] +
            HEX_CHARS[(h1 >> 20) & 0x0F] + HEX_CHARS[(h1 >> 16) & 0x0F] +
            HEX_CHARS[(h1 >> 12) & 0x0F] + HEX_CHARS[(h1 >> 8) & 0x0F] +
            HEX_CHARS[(h1 >> 4) & 0x0F] + HEX_CHARS[h1 & 0x0F] +
            HEX_CHARS[(h2 >> 28) & 0x0F] + HEX_CHARS[(h2 >> 24) & 0x0F] +
            HEX_CHARS[(h2 >> 20) & 0x0F] + HEX_CHARS[(h2 >> 16) & 0x0F] +
            HEX_CHARS[(h2 >> 12) & 0x0F] + HEX_CHARS[(h2 >> 8) & 0x0F] +
            HEX_CHARS[(h2 >> 4) & 0x0F] + HEX_CHARS[h2 & 0x0F] +
            HEX_CHARS[(h3 >> 28) & 0x0F] + HEX_CHARS[(h3 >> 24) & 0x0F] +
            HEX_CHARS[(h3 >> 20) & 0x0F] + HEX_CHARS[(h3 >> 16) & 0x0F] +
            HEX_CHARS[(h3 >> 12) & 0x0F] + HEX_CHARS[(h3 >> 8) & 0x0F] +
            HEX_CHARS[(h3 >> 4) & 0x0F] + HEX_CHARS[h3 & 0x0F] +
            HEX_CHARS[(h4 >> 28) & 0x0F] + HEX_CHARS[(h4 >> 24) & 0x0F] +
            HEX_CHARS[(h4 >> 20) & 0x0F] + HEX_CHARS[(h4 >> 16) & 0x0F] +
            HEX_CHARS[(h4 >> 12) & 0x0F] + HEX_CHARS[(h4 >> 8) & 0x0F] +
            HEX_CHARS[(h4 >> 4) & 0x0F] + HEX_CHARS[h4 & 0x0F] +
            HEX_CHARS[(h5 >> 28) & 0x0F] + HEX_CHARS[(h5 >> 24) & 0x0F] +
            HEX_CHARS[(h5 >> 20) & 0x0F] + HEX_CHARS[(h5 >> 16) & 0x0F] +
            HEX_CHARS[(h5 >> 12) & 0x0F] + HEX_CHARS[(h5 >> 8) & 0x0F] +
            HEX_CHARS[(h5 >> 4) & 0x0F] + HEX_CHARS[h5 & 0x0F] +
            HEX_CHARS[(h6 >> 28) & 0x0F] + HEX_CHARS[(h6 >> 24) & 0x0F] +
            HEX_CHARS[(h6 >> 20) & 0x0F] + HEX_CHARS[(h6 >> 16) & 0x0F] +
            HEX_CHARS[(h6 >> 12) & 0x0F] + HEX_CHARS[(h6 >> 8) & 0x0F] +
            HEX_CHARS[(h6 >> 4) & 0x0F] + HEX_CHARS[h6 & 0x0F];
        if (!this.is224) {
            hex += HEX_CHARS[(h7 >> 28) & 0x0F] + HEX_CHARS[(h7 >> 24) & 0x0F] +
                HEX_CHARS[(h7 >> 20) & 0x0F] + HEX_CHARS[(h7 >> 16) & 0x0F] +
                HEX_CHARS[(h7 >> 12) & 0x0F] + HEX_CHARS[(h7 >> 8) & 0x0F] +
                HEX_CHARS[(h7 >> 4) & 0x0F] + HEX_CHARS[h7 & 0x0F];
        }
        return hex;
    };
    Sha256.prototype.toString = Sha256.prototype.hex;
    Sha256.prototype.digest = function () {
        this.finalize();
        var h0 = this.h0, h1 = this.h1, h2 = this.h2, h3 = this.h3, h4 = this.h4, h5 = this.h5, h6 = this.h6, h7 = this.h7;
        var arr = [
            (h0 >> 24) & 0xFF, (h0 >> 16) & 0xFF, (h0 >> 8) & 0xFF, h0 & 0xFF,
            (h1 >> 24) & 0xFF, (h1 >> 16) & 0xFF, (h1 >> 8) & 0xFF, h1 & 0xFF,
            (h2 >> 24) & 0xFF, (h2 >> 16) & 0xFF, (h2 >> 8) & 0xFF, h2 & 0xFF,
            (h3 >> 24) & 0xFF, (h3 >> 16) & 0xFF, (h3 >> 8) & 0xFF, h3 & 0xFF,
            (h4 >> 24) & 0xFF, (h4 >> 16) & 0xFF, (h4 >> 8) & 0xFF, h4 & 0xFF,
            (h5 >> 24) & 0xFF, (h5 >> 16) & 0xFF, (h5 >> 8) & 0xFF, h5 & 0xFF,
            (h6 >> 24) & 0xFF, (h6 >> 16) & 0xFF, (h6 >> 8) & 0xFF, h6 & 0xFF
        ];
        if (!this.is224) {
            arr.push((h7 >> 24) & 0xFF, (h7 >> 16) & 0xFF, (h7 >> 8) & 0xFF, h7 & 0xFF);
        }
        return arr;
    };
    Sha256.prototype.array = Sha256.prototype.digest;
    Sha256.prototype.arrayBuffer = function () {
        this.finalize();
        var buffer = new ArrayBuffer(this.is224 ? 28 : 32);
        var dataView = new DataView(buffer);
        dataView.setUint32(0, this.h0);
        dataView.setUint32(4, this.h1);
        dataView.setUint32(8, this.h2);
        dataView.setUint32(12, this.h3);
        dataView.setUint32(16, this.h4);
        dataView.setUint32(20, this.h5);
        dataView.setUint32(24, this.h6);
        if (!this.is224) {
            dataView.setUint32(28, this.h7);
        }
        return buffer;
    };
    function HmacSha256(key, is224, sharedMemory) {
        var i, type = typeof key;
        if (type === 'string') {
            var bytes = [], length = key.length, index = 0, code;
            for (i = 0; i < length; ++i) {
                code = key.charCodeAt(i);
                if (code < 0x80) {
                    bytes[index++] = code;
                }
                else if (code < 0x800) {
                    bytes[index++] = (0xc0 | (code >> 6));
                    bytes[index++] = (0x80 | (code & 0x3f));
                }
                else if (code < 0xd800 || code >= 0xe000) {
                    bytes[index++] = (0xe0 | (code >> 12));
                    bytes[index++] = (0x80 | ((code >> 6) & 0x3f));
                    bytes[index++] = (0x80 | (code & 0x3f));
                }
                else {
                    code = 0x10000 + (((code & 0x3ff) << 10) | (key.charCodeAt(++i) & 0x3ff));
                    bytes[index++] = (0xf0 | (code >> 18));
                    bytes[index++] = (0x80 | ((code >> 12) & 0x3f));
                    bytes[index++] = (0x80 | ((code >> 6) & 0x3f));
                    bytes[index++] = (0x80 | (code & 0x3f));
                }
            }
            key = bytes;
        }
        else {
            if (type === 'object') {
                if (key === null) {
                    throw new Error(ERROR);
                }
                else if (ARRAY_BUFFER && key.constructor === ArrayBuffer) {
                    key = new Uint8Array(key);
                }
                else if (!Array.isArray(key)) {
                    if (!ARRAY_BUFFER || !ArrayBuffer.isView(key)) {
                        throw new Error(ERROR);
                    }
                }
            }
            else {
                throw new Error(ERROR);
            }
        }
        if (key.length > 64) {
            key = (new Sha256(is224, true)).update(key).array();
        }
        var oKeyPad = [], iKeyPad = [];
        for (i = 0; i < 64; ++i) {
            var b = key[i] || 0;
            oKeyPad[i] = 0x5c ^ b;
            iKeyPad[i] = 0x36 ^ b;
        }
        Sha256.call(this, is224, sharedMemory);
        this.update(iKeyPad);
        this.oKeyPad = oKeyPad;
        this.inner = true;
        this.sharedMemory = sharedMemory;
    }
    HmacSha256.prototype = new Sha256();
    HmacSha256.prototype.finalize = function () {
        Sha256.prototype.finalize.call(this);
        if (this.inner) {
            this.inner = false;
            var innerHash = this.array();
            Sha256.call(this, this.is224, this.sharedMemory);
            this.update(this.oKeyPad);
            this.update(innerHash);
            Sha256.prototype.finalize.call(this);
        }
    };
    var exports = createMethod();
    exports.sha256 = exports;
    exports.sha224 = createMethod(true);
    exports.sha256.hmac = createHmacMethod();
    exports.sha224.hmac = createHmacMethod(true);
    if (COMMON_JS) {
        module.exports = exports;
    }
    else {
        root.sha256 = exports.sha256;
        root.sha224 = exports.sha224;
        if (AMD) {
            define(function () {
                return exports;
            });
        }
    }
})();
