/*
 faust2wasm: GRAME 2017-2019
 */

'use strict';

if (typeof (AudioWorkletNode) === "undefined") {
    alert("AudioWorklet is not supported in this browser !")
}

const faust_module = FaustModule(); // Emscripten generated module

class mydspNode extends AudioWorkletNode {
    
    constructor(context, baseURL, options)
    {
        super(context, 'mydsp', options);
        
        this.baseURL = baseURL;
        this.json = options.processorOptions.json;
        this.json_object = JSON.parse(this.json);
        
        // JSON parsing functions
        this.parse_ui = function(ui, obj)
        {
            for (var i = 0; i < ui.length; i++) {
                this.parse_group(ui[i], obj);
            }
        }
        
        this.parse_group = function(group, obj)
        {
            if (group.items) {
                this.parse_items(group.items, obj);
            }
        }
        
        this.parse_items = function(items, obj)
        {
            for (var i = 0; i < items.length; i++) {
                this.parse_item(items[i], obj);
            }
        }
        
        this.parse_item = function(item, obj)
        {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                this.parse_items(item.items, obj);
            } else if (item.type === "hbargraph"
                       || item.type === "vbargraph") {
                // Keep bargraph adresses
                obj.outputs_items.push(item.address);
            } else if (item.type === "vslider"
                       || item.type === "hslider"
                       || item.type === "button"
                       || item.type === "checkbox"
                       || item.type === "nentry") {
                // Keep inputs adresses
                obj.inputs_items.push(item.address);
                obj.descriptor.push(item);
                // Decode MIDI
                if (item.meta !== undefined) {
                    for (var i = 0; i < item.meta.length; i++) {
                        if (item.meta[i].midi !== undefined) {
                            if (item.meta[i].midi.trim() === "pitchwheel") {
                                obj.fPitchwheelLabel.push({ path:item.address,
                                      min:parseFloat(item.min),
                                      max:parseFloat(item.max) });
                            } else if (item.meta[i].midi.trim().split(" ")[0] === "ctrl") {
                                obj.fCtrlLabel[parseInt(item.meta[i].midi.trim().split(" ")[1])]
                                .push({ path:item.address,
                                      min:parseFloat(item.min),
                                      max:parseFloat(item.max) });
                            }
                        }
                    }
                }
                // Define setXXX/getXXX, replacing '/c' with 'C' everywhere in the string
                var set_name = "set" + item.address;
                var get_name = "get" + item.address;
                set_name = set_name.replace(/\/./g, (x) => { return x.substr(1,1).toUpperCase(); });
                get_name = get_name.replace(/\/./g, (x) => { return x.substr(1,1).toUpperCase(); });
                obj[set_name] = (val) => { obj.setParamValue(item.address, val); };
                obj[get_name] = () => { return obj.getParamValue(item.address); };
                //console.log(set_name);
                //console.log(get_name);
            }
        }
        
        this.output_handler = null;
        
        // input/output items
        this.inputs_items = [];
        this.outputs_items = [];
        this.descriptor = [];
        
        // MIDI
        this.fPitchwheelLabel = [];
        this.fCtrlLabel = new Array(128);
        for (var i = 0; i < this.fCtrlLabel.length; i++) { this.fCtrlLabel[i] = []; }
        
        // Parse UI
        this.parse_ui(this.json_object.ui, this);
        
        // Set message handler
        this.port.onmessage = this.handleMessage.bind(this);
    }
    
    // To be called by the message port with messages coming from the processor
    handleMessage(event)
    {
        var msg = event.data;
        if (this.output_handler) {
            this.output_handler(msg.path, msg.value);
        }
    }
    
    // Public API
    
    /**
     * Destroy the node, deallocate resources.
     */
    destroy()
    {
        this.port.postMessage({ type: "destroy" });
        this.port.close();
    }
    
    /**
     *  Returns a full JSON description of the DSP.
     */
    getJSON()
    {
        return this.json;
    }
    
    // For WAP
    async getMetadata()
    {
        return new Promise(resolve => {
            let real_url = (this.baseURL === "") ? "main.json" : (this.baseURL + "/main.json");
            fetch(real_url).then(responseJSON => {
                return responseJSON.json();
            }).then(json => {
                resolve(json);
            })
        });
    }
    
    /**
     *  Set the control value at a given path.
     *
     * @param path - a path to the control
     * @param val - the value to be set
     */
    setParamValue(path, val)
    {
        // Needed for sample accurate control
        this.parameters.get(path).setValueAtTime(val, 0);
    }
    
    // For WAP
    setParam(path, val)
    {
        // Needed for sample accurate control
        this.parameters.get(path).setValueAtTime(val, 0);
    }
    
    /**
     *  Get the control value at a given path.
     *
     * @return the current control value
     */
    getParamValue(path)
    {
        return this.parameters.get(path).value;
    }
    
    // For WAP
    getParam(path)
    {
        return this.parameters.get(path).value;
    }
    
    /**
     * Setup a control output handler with a function of type (path, value)
     * to be used on each generated output value. This handler will be called
     * each audio cycle at the end of the 'compute' method.
     *
     * @param handler - a function of type function(path, value)
     */
    setOutputParamHandler(handler)
    {
        this.output_handler = handler;
    }
    
    /**
     * Get the current output handler.
     */
    getOutputParamHandler()
    {
        return this.output_handler;
    }
    
    getNumInputs()
    {
        return parseInt(this.json_object.inputs);
    }
    
    getNumOutputs()
    {
        return parseInt(this.json_object.outputs);
    }
    
    // For WAP
    inputChannelCount()
    {
        return parseInt(this.json_object.inputs);
    }
    
    outputChannelCount()
    {
        return parseInt(this.json_object.outputs);
    }
    
    /**
     * Returns an array of all input paths (to be used with setParamValue/getParamValue)
     */
    getParams()
    {
        return this.inputs_items;
    }
    
    // For WAP
    getDescriptor()
    {
        var desc = {};
        for (const item in this.descriptor) {
            if (this.descriptor.hasOwnProperty(item)) {
                if (this.descriptor[item].label != "bypass") {
                    desc = Object.assign({ [this.descriptor[item].label]: { minValue: this.descriptor[item].min, maxValue: this.descriptor[item].max, defaultValue: this.descriptor[item].init } }, desc);
                }
            }
        }
        return desc;
    }
    
    /**
     * Control change
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param ctrl - the MIDI controller number (0..127)
     * @param value - the MIDI controller value (0..127)
     */
    ctrlChange(channel, ctrl, value)
    {
        if (this.fCtrlLabel[ctrl] !== []) {
            for (var i = 0; i < this.fCtrlLabel[ctrl].length; i++) {
                var path = this.fCtrlLabel[ctrl][i].path;
                this.setParamValue(path, mydspNode.remap(value, 0, 127, this.fCtrlLabel[ctrl][i].min, this.fCtrlLabel[ctrl][i].max));
                if (this.output_handler) {
                    this.output_handler(path, this.getParamValue(path));
                }
            }
        }
    }
    
    /**
     * PitchWeel
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param value - the MIDI controller value (0..16383)
     */
    pitchWheel(channel, wheel)
    {
        for (var i = 0; i < this.fPitchwheelLabel.length; i++) {
            var pw = this.fPitchwheelLabel[i];
            this.setParamValue(pw.path, mydspNode.remap(wheel, 0, 16383, pw.min, pw.max));
            if (this.output_handler) {
                this.output_handler(pw.path, this.getParamValue(pw.path));
            }
        }
    }
    
    /**
     * Generic MIDI message handler.
     */
    midiMessage(data)
    {
        var cmd = data[0] >> 4;
        var channel = data[0] & 0xf;
        var data1 = data[1];
        var data2 = data[2];
        
        if (channel === 9) {
            return;
        } else if (cmd === 11) {
            this.ctrlChange(channel, data1, data2);
        } else if (cmd === 14) {
            this.pitchWheel(channel, (data2 * 128.0 + data1));
        }
    }
    
    // For WAP
    onMidi(data)
    {
        midiMessage(data);
    }
    
    /**
     * @returns {Object} describes the path for each available param and its current value
     */
    async getState()
    {
        var params = new Object();
        for (let i = 0; i < this.getParams().length; i++) {
            Object.assign(params, { [this.getParams()[i]]: `${this.getParam(this.getParams()[i])}` });
        }
        return new Promise(resolve => { resolve(params) });
    }
    
    /**
     * Sets each params with the value indicated in the state object
     * @param {Object} state
     */
    async setState(state)
    {
        return new Promise(resolve => {
           for (const param in state) {
                if (state.hasOwnProperty(param)) this.setParam(param, state[param]);
           }
           try {
                this.gui.setAttribute('state', JSON.stringify(state));
           } catch (error) {
                console.warn("Plugin without gui or GUI not defined", error);
           }
           resolve(state);
        })
    }
    
    /**
     * A different call closer to the preset management
     * @param {Object} patch to assign as a preset to the node
     */
    setPatch(patch)
    {
        this.setState(this.presets[patch])
    }
    
    static remap(v, mn0, mx0, mn1, mx1)
    {
        return (1.0 * (v - mn0) / (mx0 - mn0)) * (mx1 - mn1) + mn1;
    }
    
}

// Factory class
class mydsp {
    
    /**
     * Factory constructor.
     *
     * @param context - the audio context
     * @param baseURL - the baseURL of the plugin folder
     */
    constructor(context, baseURL = "")
    {
        console.log("baseLatency " + context.baseLatency);
        console.log("outputLatency " + context.outputLatency);
        console.log("sampleRate " + context.sampleRate);
        
        this.context = context;
        this.baseURL = baseURL;
        this._log = [];
    }
    
    log(str)
    {
        this._log.push(str);
        if (this.debug) console.log(str);
    }
    
    error(str)
    {
        this._log.push(str);
        console.error(str);
    }
    
    async asyncForEach(array, callback) {
        for (let index = 0; index < array.length; index++) {
            await callback(array[index], index, array);
        }
    }
    
    async loadAudioFiles(json)
    {
        // Get filenames in JSON
        let json_object = JSON.parse(json);
        let soundfiles_name = [];
        let soundfiles = [];
        let parse_ui = ui => ui.forEach(group => parse_group(group));
        let parse_group = group => group.items ? parse_items(group.items) : null;
        let parse_items = items => items.forEach(item => parse_item(item));
        let parse_item = item => {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                parse_items(item.items);
            } else if (item.type === "soundfile") {
                item.url.slice(1, -1).split(';').forEach(item => soundfiles_name.push(item));
            }
        }
        parse_ui(json_object.ui);
        
        // Load each file.
        await this.asyncForEach(soundfiles_name, async name_aux => {
                                let name = name_aux.slice(1, -1);
                                console.log(name);
                                const soundfile = await fetch(name);
                                const data = await soundfile.arrayBuffer();
                                soundfiles.push({ name: name, data: data });
                                });
        return soundfiles;
    }
    
    /**
     * Load additionnal resources to prepare the custom AudioWorkletNode. Returns a promise to be used with the created node.
     */
    async load()
    {
        try {
            
            let real_url = (this.baseURL === "") ? "mydsp.wasm" : (this.baseURL + "/mydsp.wasm");
            const wasm_file = await fetch(real_url);
            const wasm_buffer = await wasm_file.arrayBuffer();
            const wasm_module = await WebAssembly.compile(wasm_buffer);
            const json = faust_module.wasm_dsp_factory.extractJSON(wasm_buffer);
            
            // Load soundfiles
            let soundfiles = await this.loadAudioFiles(json);
            
            return new Promise((resolve, reject) => {
               
               let json_object = JSON.parse(json);
               let options = { wasm_module: wasm_module, json: json, soundfiles: soundfiles };
               
               let re = /JSON_STR/g;
               let mydspProcessorString1 = mydspProcessorString.replace(re, json);
               let real_url = window.URL.createObjectURL(new Blob([mydspProcessorString1], { type: 'text/javascript' }));
               
               this.context.audioWorklet.addModule(real_url).then(() => {
                  this.node = new mydspNode(this.context, this.baseURL,
                                            { numberOfInputs: (parseInt(json_object.inputs) > 0) ? 1 : 0,
                                            numberOfOutputs: (parseInt(json_object.outputs) > 0) ? 1 : 0,
                                            channelCount: Math.max(1, parseInt(json_object.inputs)),
                                            outputChannelCount: [parseInt(json_object.outputs)],
                                            channelCountMode: "explicit",
                                            channelInterpretation: "speakers",
                                            processorOptions: options });
                  this.node.onprocessorerror = () => { console.log('An error from mydsp-processor was detected.');}
                  
                  return (this.node);
                }).then((node) => {
                    resolve(node);
                }).catch((e) => {
                    reject(e);
                });
            });
            
        } catch (e) {
            this.error(e);
            this.error("Faust " + this.name + " cannot be loaded or compiled");
            return null;
        }
    }
    
    async loadGui()
    {
        return new Promise((resolve, reject) => {
            try {
               // DO THIS ONLY ONCE. If another instance has already been added, do not add the html file again
               let real_url = (this.baseURL === "") ? "main.html" : (this.baseURL + "/main.html");
               if (!this.linkExists(real_url)) {
                   // LINK DOES NOT EXIST, let's add it to the document
                   var link = document.createElement('link');
                   link.rel = 'import';
                   link.href = real_url;
                   document.head.appendChild(link);
                   link.onload = (e) => {
                       // the file has been loaded, instanciate GUI
                       // and get back the HTML elem
                       // HERE WE COULD REMOVE THE HARD CODED NAME
                       var element = createmydspGUI(this.node);
                       resolve(element);
                   }
               } else {
                   // LINK EXIST, WE AT LEAST CREATED ONE INSTANCE PREVIOUSLY
                   // so we can create another instance
                   var element = createmydspGUI(this.node);
                   resolve(element);
               }
               } catch (e) {
                    console.log(e);
                    reject(e);
               }
               });
    };
    
    linkExists(url) 
    {
    	return document.querySelectorAll(`link[href="${url}"]`).length > 0;
    }
    
}

// Template string for AudioWorkletProcessor

let mydspProcessorString = `

    'use strict';

    import FaustModule from 'http://127.0.0.1:8000/libfaust-worklet-glue.js';

    AudioWorkletGlobalScope.faust_module = FaustModule(); // Emscripten generated module
    AudioWorkletGlobalScope.faust_module.faust = AudioWorkletGlobalScope.faust_module.faust || {};
    AudioWorkletGlobalScope.faust_module.faust.wasm_instance = AudioWorkletGlobalScope.faust_module.faust.wasm_instance || [];

    // Monophonic Faust DSP
    class mydspProcessor extends AudioWorkletProcessor {
        
        // JSON parsing functions
        static parse_ui(ui, obj, callback)
        {
            for (var i = 0; i < ui.length; i++) {
                mydspProcessor.parse_group(ui[i], obj, callback);
            }
        }
        
        static parse_group(group, obj, callback)
        {
            if (group.items) {
                mydspProcessor.parse_items(group.items, obj, callback);
            }
        }
        
        static parse_items(items, obj, callback)
        {
            for (var i = 0; i < items.length; i++) {
                callback(items[i], obj, callback);
            }
        }
        
        static parse_item1(item, obj, callback)
        {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                mydspProcessor.parse_items(item.items, obj, callback);
            } else if (item.type === "hbargraph"
                       || item.type === "vbargraph") {
                // Nothing
            } else if (item.type === "vslider"
                       || item.type === "hslider"
                       || item.type === "button"
                       || item.type === "checkbox"
                       || item.type === "nentry") {
                obj.push({ name: item.address,
                         defaultValue: item.init,
                         minValue: item.min,
                         maxValue: item.max });
            }
        }
        
        static parse_item2(item, obj, callback)
        {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                mydspProcessor.parse_items(item.items, obj, callback);
            } else if (item.type === "hbargraph"
                       || item.type === "vbargraph") {
                // Keep bargraph adresses
                obj.outputs_items.push(item.address);
            }
        }
        
        static get parameterDescriptors()
        {
            // Analyse JSON to generate AudioParam parameters
            var params = [];
            mydspProcessor.parse_ui(JSON.parse(\`JSON_STR\`).ui, params, mydspProcessor.parse_item1);
            return params;
        }
        
        handleMessage(event)
        {
            var msg = event.data;
            switch (msg.type) {
                case "destroy": this.running = false; break;
            }
        }
        
        constructor(options)
        {
            super(options);
            this.running = true;
            
            // To connect memory
            AudioWorkletGlobalScope.faust_module.wasm_dsp_factory.extractJSON("");
            
            const importObject = {
                env: {
                    memoryBase: 0,
                    tableBase: 0,
                        
                    // Integer version
                    _abs: Math.abs,
                        
                    // Float version
                    _acosf: Math.acos,
                    _asinf: Math.asin,
                    _atanf: Math.atan,
                    _atan2f: Math.atan2,
                    _ceilf: Math.ceil,
                    _cosf: Math.cos,
                    _expf: Math.exp,
                    _floorf: Math.floor,
                    _fmodf: function(x, y) { return x % y; },
                    _logf: Math.log,
                    _log10f: Math.log10,
                    _max_f: Math.max,
                    _min_f: Math.min,
                    _remainderf: function(x, y) { return x - Math.round(x/y) * y; },
                    _powf: Math.pow,
                    _roundf: Math.fround,
                    _sinf: Math.sin,
                    _sqrtf: Math.sqrt,
                    _tanf: Math.tan,
                    _acoshf: Math.acosh,
                    _asinhf: Math.asinh,
                    _atanhf: Math.atanh,
                    _coshf: Math.cosh,
                    _sinhf: Math.sinh,
                    _tanhf: Math.tanh,
                        
                    // Double version
                    _acos: Math.acos,
                    _asin: Math.asin,
                    _atan: Math.atan,
                    _atan2: Math.atan2,
                    _ceil: Math.ceil,
                    _cos: Math.cos,
                    _exp: Math.exp,
                    _floor: Math.floor,
                    _fmod: function(x, y) { return x % y; },
                    _log: Math.log,
                    _log10: Math.log10,
                    _max_: Math.max,
                    _min_: Math.min,
                    _remainder:function(x, y) { return x - Math.round(x/y) * y; },
                    _pow: Math.pow,
                    _round: Math.fround,
                    _sin: Math.sin,
                    _sqrt: Math.sqrt,
                    _tan: Math.tan,
                    _acosh: Math.acosh,
                    _asinh: Math.asinh,
                    _atanh: Math.atanh,
                    _cosh: Math.cosh,
                    _sinh: Math.sinh,
                    _tanh: Math.tanh,
                    
                    memory : AudioWorkletGlobalScope.faust_module.faust.memory,
                    
                    table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
                }
            };
            
            options.processorOptions.soundfiles.forEach(item => {
                                                        console.log(item.name);
                                                        let stream = AudioWorkletGlobalScope.faust_module.FS.open(item.name, 'w+');
                                                        let buf = new Uint8Array(item.data);
                                                        let res1 = AudioWorkletGlobalScope.faust_module.FS.write(stream, buf, 0, buf.length, 0);
                                                        console.log(res1);
                                                        AudioWorkletGlobalScope.faust_module.FS.close(stream);
                                                        });
            
            this.wasm_instance = new WebAssembly.Instance(options.processorOptions.wasm_module, importObject);
            AudioWorkletGlobalScope.faust_module.faust.wasm_instance.push(this.wasm_instance);
            this.json_object = JSON.parse(options.processorOptions.json);
            this.factory = AudioWorkletGlobalScope.faust_module.wasm_dsp_factory.createWasmDSPFactory(0, options.processorOptions.json);
            this.dsp = this.factory.createDSPInstance();
            
            this.output_handler = function(path, value) { this.port.postMessage({ path: path, value: value }); };
            
            this.ins = null;
            this.outs = null;
            
            this.dspInChannnels = [];
            this.dspOutChannnels = [];
            
            this.numIn = parseInt(this.json_object.inputs);
            this.numOut = parseInt(this.json_object.outputs);
            
            // Memory allocator
            this.ptr_size = 4;
            this.sample_size = 4;
            
            // bargraph
            this.outputs_timer = 5;
            this.outputs_items = [];
            
            // Send output values to the AudioNode
            this.update_outputs = function ()
            {
                if (this.outputs_items.length > 0 && this.output_handler && this.outputs_timer-- === 0) {
                    this.outputs_timer = 5;
                    this.outputs_items.forEach(item => this.output_handler(item, this.dsp.getParamValue(item)));
                }
            }
            
            this.initAux = function ()
            {
                if (this.numIn > 0) {
                    this.ins = AudioWorkletGlobalScope.faust_module._malloc(this.numIn * this.ptr_size);
                    for (let i = 0; i < this.numIn; i++) {
                        AudioWorkletGlobalScope.faust_module.HEAP32[(this.ins >> 2) + i] = AudioWorkletGlobalScope.faust_module._malloc(NUM_FRAMES * this.sample_size);
                    }
                    // Prepare Ins buffer tables
                    const dspInChans =  AudioWorkletGlobalScope.faust_module.HEAP32.subarray(this.ins >> 2, (this.ins + this.numIn * this.ptr_size) >> 2);
                    for (let i = 0; i < this.numIn; i++) {
                        this.dspInChannnels[i] = AudioWorkletGlobalScope.faust_module.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + NUM_FRAMES * this.sample_size) >> 2);
                    }
                } else {
                    // Null pointer for C++ side
                    this.ins = 0;
                }
                
                if (this.numOut > 0) {
                    this.outs = AudioWorkletGlobalScope.faust_module._malloc(this.numOut * this.ptr_size);
                    for (let i = 0; i < this.numOut; i++) {
                        AudioWorkletGlobalScope.faust_module.HEAP32[(this.outs >> 2) + i] = AudioWorkletGlobalScope.faust_module._malloc(NUM_FRAMES * this.sample_size);
                    }
                    // Prepare Out buffer tables
                    const dspOutChans = AudioWorkletGlobalScope.faust_module.HEAP32.subarray(this.outs >> 2, (this.outs + this.numOut * this.ptr_size) >> 2);
                    for (let i = 0; i < this.numOut; i++) {
                        this.dspOutChannnels[i] = AudioWorkletGlobalScope.faust_module.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + NUM_FRAMES * this.sample_size) >> 2);
                    }
                } else {
                    // Null pointer for C++ side
                    this.outs = 0;
                }
                
                // Parse UI
                mydspProcessor.parse_ui(this.json_object.ui, this, mydspProcessor.parse_item2);
                
                // Init DSP
                this.dsp.init(sampleRate);
            }
            
            this.destroy = function ()
            {
                if (this.numIn > 0) {
                    for (let i = 0; i < this.numIn; i++) {
                        AudioWorkletGlobalScope.faust_module._free(AudioWorkletGlobalScope.faust_module.HEAP32[(this.ins >> 2) + i]);
                    }
                    AudioWorkletGlobalScope.faust_module._free(this.ins);
                }
                if (this.numOut > 0) {
                    for (let i = 0; i < this.numOut; i++) {
                        AudioWorkletGlobalScope.faust_module._free(AudioWorkletGlobalScope.faust_module.HEAP32[(this.outs >> 2) + i]);
                    }
                    AudioWorkletGlobalScope.faust_module._free(this.outs);
                }
                
                this.factory.deleteDSPInstance(this.dsp);
                AudioWorkletGlobalScope.faust_module.wasm_dsp_factory.deleteWasmDSPFactory(this.factory);
            }
            
            this.setParamValue = function (path, val)
            {
                this.dsp.setParamValue(path, parseFloat(val));
            }
            
            this.getParamValue = function (path)
            {
                return this.dsp.getParamValue(path);
            }
            
            // Init resulting DSP
            this.initAux();
            
            // Setup port
            this.port.onmessage = this.handleMessage.bind(this);
            this.port.start();
        }
        
        process(inputs, outputs, parameters)
        {
            var input = inputs[0];
            var output = outputs[0];
            
            // Check inputs
            if (this.numIn > 0 && (!input || !input[0] || input[0].length === 0)) {
                //console.log("Process input error");
                return true;
            }
            // Check outputs
            if (this.numOut > 0 && (!output || !output[0] || output[0].length === 0)) {
                //console.log("Process output error");
                return true;
            }
            
            // Copy inputs
            if (input !== undefined) {
                for (var chan = 0; chan < Math.min(this.numIn, input.length); ++chan) {
                    var dspInput = this.dspInChannnels[chan];
                    dspInput.set(input[chan]);
                }
            }
            
            /*
            TODO: sample accurate control change is not yet handled
            When no automation occurs, params[i][1] has a length of 1,
            otherwise params[i][1] has a length of NUM_FRAMES with possible control change each sample
            */
            
            // Update controls
            for (const path in parameters) {
                const paramArray = parameters[path];
                this.setParamValue(path, paramArray[0]);
            }
            
            // Compute
            try {
            	this.dsp.compute(NUM_FRAMES, this.ins, this.outs);
            } catch(e) {
            	console.log("ERROR in compute (" + e + ")");
            } 
            
            // Update bargraph
            this.update_outputs();
            
            // Copy outputs
            if (output !== undefined) {
                for (var chan = 0; chan < Math.min(this.numOut, output.length); ++chan) {
                    var dspOutput = this.dspOutChannnels[chan];
                    output[chan].set(dspOutput);
                }
            }
            
            if (this.running) {
                return true;
            } else {
                this.destroy();
                return false;
            }
        }
    }

    // Globals
    const NUM_FRAMES = 128;
    try {
        registerProcessor('mydsp', mydspProcessor);
    } catch (error) {
        console.warn(error);
    }
`;

const dspName = "mydsp";

// WAP factory or npm package module
if (typeof module === "undefined") {
    window.mydsp = mydsp;
    window.Faustmydsp = mydsp;
    window[dspName] = mydsp;
} else {
    module.exports = { mydsp };
}

