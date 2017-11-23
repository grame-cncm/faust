/*
 faust2wasm
 
 Additional code: GRAME 2017
*/
 
'use strict';

var faust = faust || {};

faust.error_msg = null;
faust.getErrorMessage = function() { return faust.error_msg; };

// Audio buffer size
faust.buffer_size = 128;

faust.createMemory = function (inputs, outputs, buffer_size, polyphony) {
    
    // Memory allocator
    var ptr_size = 4;
    var sample_size = 4;
    
    function pow2limit(x)
    {
        var n = 65536; // Minimum = 64 kB
        while (n < x) { n = 2 * n; }
        return n;
    }
    
    var memory_size = pow2limit(getSizemydsp() * polyphony + ((inputs + outputs * 2) * (ptr_size + (buffer_size * sample_size)))) / 65536;
    memory_size = Math.max(2, memory_size); // As least 2
    return new WebAssembly.Memory({initial:memory_size, maximum:memory_size});
}

// Polyphony
faust.polyphony = 16;

faust.importObject = {
    env: {
        memoryBase: 0,
        tableBase: 0,
            
        absf: Math.abs,
        acosf: Math.acos,
        asinf: Math.asin,
        atanf: Math.atan,
        atan2f: Math.atan2,
        ceilf: Math.ceil,
        cosf: Math.cos,
        expf: Math.exp,
        floorf: Math.floor,
        fmodf: function(x, y) { return x % y; },
        logf: Math.log,
        log10f: Math.log10,
        max_f: Math.max,
        min_f: Math.min,
        remainderf: function(x, y) { return x - Math.round(x/y) * y; },
        powf: Math.pow,
        roundf: Math.fround,
        sinf: Math.sin,
        sqrtf: Math.sqrt,
        tanf: Math.tan,
            
        abs: Math.abs,
        acos: Math.acos,
        asin: Math.asin,
        atan: Math.atan,
        atan2: Math.atan2,
        ceil: Math.ceil,
        cos: Math.cos,
        exp: Math.exp,
        floor: Math.floor,
        fmod: function(x, y) { return x % y; },
        log: Math.log,
        log10: Math.log10,
        max_: Math.max,
        min_: Math.min,
        remainder:function(x, y) { return x - Math.round(x/y) * y; },
        pow: Math.pow,
        round: Math.fround,
        sin: Math.sin,
        sqrt: Math.sqrt,
        tan: Math.tan,
            
        table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
    }
};

faust.mixObject = { imports: { print: arg => console.log(arg) } }
faust.mixObject["memory"] = { "memory": memory };

// WebAssembly instance
faust.mydsp_instance = null;
faust.mixer_instance = null;

// JSON parsing functions
faust.parse_ui = function (ui, callback)
{
    for (var i = 0; i < ui.length; i++) {
        faust.parse_group(ui[i], callback);
    }
}

faust.parse_group = function (group, callback)
{
    if (group.items) {
        faust.parse_items(group.items, callback);
    }
}

faust.parse_items = function (items, callback)
{
    for (var i = 0; i < items.length; i++) {
        callback(items[i]);
    }
}

// Polyphonic Faust DSP
class mydsp_polyProcessor extends AudioWorkletProcessor {
    
    static get parameterDescriptors () {
        
        // Analyse JSON to generate AudioParam parameters
        var params = [];
        
        faust.parse_ui(JSON.parse(getJSONmydsp()).ui,
                       function (item) {
                           if (item.type === "vgroup"
                               || item.type === "hgroup"
                               || item.type === "tgroup") {
                                faust.parse_items(item.items);
                           } else if (item.type === "hbargraph"
                                      || item.type === "vbargraph") {
                                // Keep bargraph adresses
                                ///this.outputs_items.push(item.address);
                           } else if (item.type === "vslider"
                                      || item.type === "hslider"
                                      || item.type === "button"
                                      || item.type === "checkbox"
                                      || item.type === "nentry") {
                                params.push({ name: item.address,
                                       defaultValue: item.init,
                                       minValue: item.min,
                                       maxValue: item.max });
                           }
                       });
        
        return params;
    }
    
    constructor (options)
    {
        super(options);
        
        this.json_object = JSON.parse(getJSONmydsp());
        
        this.output_handler = null;
        this.ins = null;
        this.outs = null;
        this.mixing = null;
        this.compute_handler = null;
        
        this.dspInChannnels = [];
        this.dspOutChannnels = [];
        
        this.fFreqLabel = "";
        this.fGateLabel = "";
        this.fGainLabel = "";
        this.fDate = 0;
        
        this.numIn = parseInt(this.json_object.inputs);
        this.numOut = parseInt(this.json_object.outputs);
        
        // Memory allocator
        this.ptr_size = 4;
        this.sample_size = 4;
        
        this.factory = faust.mydsp_instance.exports;
        this.HEAP = faust.createMemory(this.numIn, this.numOut, faust.buffer_size, faust.polyphony).buffer;
        this.HEAP32 = new Int32Array(this.HEAP);
        this.HEAPF32 = new Float32Array(this.HEAP);
        
        console.log(this.HEAP);
        console.log(this.HEAP32);
        console.log(this.HEAPF32);
        
        // bargraph
        this.outputs_timer = 5;
        this.outputs_items = [];
        
        // input items
        this.inputs_items = [];
        
        // Start of HEAP index
        this.audio_heap_ptr = 0;
        
        // Setup pointers offset
        this.audio_heap_ptr_inputs = this.audio_heap_ptr;
        this.audio_heap_ptr_outputs = this.audio_heap_ptr_inputs + (this.numIn * this.ptr_size);
        this.audio_heap_ptr_mixing = this.audio_heap_ptr_outputs + (this.numOut * this.ptr_size);
        
        // Setup buffer offset
        this.audio_heap_inputs = this.audio_heap_ptr_mixing + (this.numOut * this.ptr_size);
        this.audio_heap_outputs = this.audio_heap_inputs + (this.numIn * faust.buffer_size * this.sample_size);
        this.audio_heap_mixing = this.audio_heap_outputs + (this.numOut * faust.buffer_size * this.sample_size);
        
        // Setup DSP voices offset
        this.dsp_start = this.audio_heap_mixing + (this.numOut * faust.buffer_size * this.sample_size);
        
        // wasm mixer
        this.mixer = faust.mixer_instance.exports;
        
        console.log(this.mixer);
        console.log(this.factory);
        
        // Start of DSP memory ('polyphony' DSP voices)
        this.dsp_voices = [];
        this.dsp_voices_state = [];
        this.dsp_voices_level = [];
        this.dsp_voices_date = [];
        this.dsp_voices_trigger = [];
        
        this.kActiveVoice = 0;
        this.kFreeVoice = -1;
        this.kReleaseVoice = -2;
        this.kNoVoice = -3;
     
        this.pathTable = getPathTablemydsp();
        
        // Allocate table for 'setParamValue'
        this.value_table = [];
        
        for (var i = 0; i < polyphony; i++) {
            this.dsp_voices[i] = this.dsp_start + i * getSizemydsp();
            this.dsp_voices_state[i] = this.kFreeVoice;
            this.dsp_voices_level[i] = 0;
            this.dsp_voices_date[i] = 0;
            this.dsp_voices_trigger[i] = false;
        }
        
        this.getPlayingVoice = function(pitch)
        {
            var voice_playing = this.kNoVoice;
            var oldest_date_playing = Number.MAX_VALUE;
            
            for (var i = 0; i < polyphony; i++) {
                if (this.dsp_voices_state[i] === pitch) {
                    // Keeps oldest playing voice
                    if (this.dsp_voices_date[i] < oldest_date_playing) {
                        oldest_date_playing = this.dsp_voices_date[i];
                        voice_playing = i;
                    }
                }
            }
            
            return voice_playing;
        }
        
        // Always returns a voice
        this.allocVoice = function(voice)
        {
            this.dsp_voices_date[voice] = this.fDate++;
            this.dsp_voices_trigger[voice] = true;    //so that envelop is always re-initialized
            this.dsp_voices_state[voice] = this.kActiveVoice;
            return voice;
        }
        
        this.getFreeVoice = function()
        {
            for (var i = 0; i < polyphony; i++) {
                if (this.dsp_voices_state[i] === this.kFreeVoice) {
                    return this.allocVoice(i);
                }
            }
            
            var voice_release = this.kNoVoice;
            var voice_playing = this.kNoVoice;
            var oldest_date_release = Number.MAX_VALUE;
            var oldest_date_playing = Number.MAX_VALUE;
            
            // Scan all voices
            for (var i = 0; i < polyphony; i++) {
                // Try to steal a voice in kReleaseVoice mode...
                if (this.dsp_voices_state[i] === this.kReleaseVoice) {
                    // Keeps oldest release voice
                    if (this.dsp_voices_date[i] < oldest_date_release) {
                        oldest_date_release = this.dsp_voices_date[i];
                        voice_release = i;
                    }
                } else {
                    if (this.dsp_voices_date[i] < oldest_date_playing) {
                        oldest_date_playing = this.dsp_voices_date[i];
                        voice_playing = i;
                    }
                }
            }
            
            // Then decide which one to steal
            if (oldest_date_release != Number.MAX_VALUE) {
                console.log("Steal release voice : voice_date = %d cur_date = %d voice = %d\n", this.dsp_voices_date[voice_release], this.fDate, voice_release);
                return this.allocVoice(voice_release);
            } else if (oldest_date_playing != Number.MAX_VALUE) {
                console.log("Steal playing voice : voice_date = %d cur_date = %d voice = %d\n", this.dsp_voices_date[voice_playing], this.fDate, voice_playing);
                return this.allocVoice(voice_playing);
            } else {
                return this.kNoVoice;
            }
        }
        
        this.update_outputs = function ()
        {
            if (this.outputs_items.length > 0 && this.output_handler && this.outputs_timer-- === 0) {
                this.outputs_timer = 5;
                for (var i = 0; i < this.outputs_items.length; i++) {
                    this.output_handler(this.outputs_items[i], this.factory.getParamValue(this.dsp, this.pathTable[this.outputs_items[i]]));
                }
            }
        }
        
        this.midiToFreq = function (note)
        {
            return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
        }
        
        this.initAux = function ()
        {
            var i;
            
            console.log("buffer_size %d", faust.buffer_size);
            this.onaudioprocess = this.compute;
            
            if (this.numIn > 0) {
                this.ins = this.audio_heap_ptr_inputs;
                for (i = 0; i < this.numIn; i++) {
                    this.HEAP32[(this.ins >> 2) + i] = this.audio_heap_inputs + ((faust.buffer_size * this.sample_size) * i);
                }
                
                // Prepare Ins buffer tables
                var dspInChans = this.HEAP32.subarray(this.ins >> 2, (this.ins + this.numIn * this.ptr_size) >> 2);
                for (i = 0; i < this.numIn; i++) {
                    this.dspInChannnels[i] = this.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + faust.buffer_size * this.sample_size) >> 2);
                }
            }
            
            if (this.numOut > 0) {
                // allocate memory for output and mixing arrays
                this.outs = this.audio_heap_ptr_outputs;
                this.mixing = this.audio_heap_ptr_mixing;
                
                for (i = 0; i < this.numOut; i++) {
                    this.HEAP32[(this.outs >> 2) + i] = this.audio_heap_outputs + ((faust.buffer_size * this.sample_size) * i);
                    this.HEAP32[(this.mixing >> 2) + i] = this.audio_heap_mixing + ((faust.buffer_size * this.sample_size) * i);
                }
                
                // Prepare Out buffer tables
                var dspOutChans = this.HEAP32.subarray(this.outs >> 2, (this.outs + this.numOut * this.ptr_size) >> 2);
                for (i = 0; i < this.numOut; i++) {
                    this.dspOutChannnels[i] = this.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + faust.buffer_size * this.sample_size) >> 2);
                }
            }
            
            // Parse UI
            faust.parse_ui(this.json_object.ui,
                           function (item) {
                               if (item.type === "vgroup"
                                   || item.type === "hgroup"
                                   || item.type === "tgroup") {
                                    faust.parse_items(item.items);
                               } else if (item.type === "hbargraph"
                                          || item.type === "vbargraph") {
                                    // Keep bargraph adresses
                                    this.outputs_items.push(item.address);
                               } else if (item.type === "vslider"
                                          || item.type === "hslider"
                                          || item.type === "button"
                                          || item.type === "checkbox"
                                          || item.type === "nentry") {
                                    // Keep inputs adresses
                                    this.inputs_items.push(item.address);
                               }
                           });
            
            // keep 'keyOn/keyOff' labels
            for (i = 0; i < this.inputs_items.length; i++) {
                if (this.inputs_items[i].endsWith("/gate")) {
                    this.fGateLabel = this.pathTable[this.inputs_items[i]];
                    console.log(this.fGateLabel);
                } else if (this.inputs_items[i].endsWith("/freq")) {
                    this.fFreqLabel = this.pathTable[this.inputs_items[i]];
                    console.log(this.fFreqLabel);
                } else if (this.inputs_items[i].endsWith("/gain")) {
                    this.fGainLabel = this.pathTable[this.inputs_items[i]];
                    console.log(this.fGainLabel);
                }
            }
            
            // Init DSP voices
            for (i = 0; i < polyphony; i++) {
                this.factory.init(this.dsp_voices[i], context.sampleRate);
            }
        }
        
        /**
         * Instantiates a new polyphonic voice.
         *
         * @param channel - the MIDI channel (0..15, not used for now)
         * @param pitch - the MIDI pitch (0..127)
         * @param velocity - the MIDI velocity (0..127)
         */
        this.keyOn = function (channel, pitch, velocity)
        {
            var voice = this.getFreeVoice();
            //console.log("keyOn voice %d", voice);
            this.factory.setParamValue(this.dsp_voices[voice], this.fFreqLabel, this.midiToFreq(pitch));
            this.factory.setParamValue(this.dsp_voices[voice], this.fGainLabel, velocity/127.);
            this.dsp_voices_state[voice] = pitch;
        }
        
        /**
         * De-instantiates a polyphonic voice.
         *
         * @param channel - the MIDI channel (0..15, not used for now)
         * @param pitch - the MIDI pitch (0..127)
         * @param velocity - the MIDI velocity (0..127)
         */
        this.keyOff = function (channel, pitch, velocity)
        {
            var voice = this.getPlayingVoice(pitch);
            if (voice !== this.kNoVoice) {
                //console.log("keyOff voice %d", voice);
                // No use of velocity for now...
                this.factory.setParamValue(this.dsp_voices[voice], this.fGateLabel, 0.0);
                // Release voice
                this.dsp_voices_state[voice] = this.kReleaseVoice;
            } else {
                console.log("Playing voice not found...\n");
            }
        }
        
        /**
         * Gently terminates all the active voices.
         */
        this.allNotesOff = function ()
        {
            for (var i = 0; i < polyphony; i++) {
                this.factory.setParamValue(this.dsp_voices[i], this.fGateLabel, 0.0);
                this.dsp_voices_state[i] = this.kReleaseVoice;
            }
        }
        
        /**
         * Controller 123 allNoteOff only is handled.
         *
         * @param channel - the MIDI channel (0..15, not used for now)
         * @param ctrl - the MIDI controller number (0..127)
         * @param value - the MIDI controller value (0..127)
         */
        this.ctrlChange = function (channel, ctrl, value)
        {
            if (ctrl === 123 || ctrl === 120) {
                this.allNotesOff();
            }
        }
        
        /**
         * PitchWeel: empty for now.
         *
         */
        this.pitchWheel = function (channel, wheel)
        {}
        
        // Init resulting DSP
        this.initAux();
    }
        
    process(inputs, outputs, parameters) {
        
        // Copy inputs
        for (var channel = 0; channel < input.length; ++channel) {
            var dspInput = this.dspInChannnels[i];
            for (var frame = 0; frame < input[channel].length; ++frame) {
                dspInput[j] = input[channel][frame];
            }
        }
        
        //var myParam = parameters.myParam;
       
        /*
         // Update control state
         for (i = 0; i < this.inputs_items.length; i++) {
         var path = this.inputs_items[i];
         var values = this.value_table[path];
         this.factory.setParamValue(this.dsp, this.pathTable[path], values[0]);
         values[0] = values[1];
         }
         */
        
        // Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
        if (this.compute_handler) {
            this.compute_handler(faust.buffer_size);
        }
        
        // First clear the outputs
        this.mixer.clearOutput(faust.buffer_size, this.numOut, this.outs);
        
        // Compute all running voices
        for (i = 0; i < polyphony; i++) {
            if (this.dsp_voices_state[i] != this.kFreeVoice) {
                if (this.dsp_voices_trigger[i]) {
                    // FIXME : properly cut the buffer in 2 slices...
                    this.factory.setParamValue(this.dsp_voices[i], this.fGateLabel, 0.0);
                    this.factory.compute(this.dsp_voices[i], 1, this.ins, this.mixing);
                    this.factory.setParamValue(this.dsp_voices[i], this.fGateLabel, 1.0);
                    this.factory.compute(this.dsp_voices[i], faust.buffer_size, this.ins, this.mixing);
                    this.dsp_voices_trigger[i] = false;
                } else {
                    // Compute regular voice
                    this.factory.compute(this.dsp_voices[i], faust.buffer_size, this.ins, this.mixing);
                }
                // Mix it in result
                this.dsp_voices_level[i] = this.mixer.mixVoice(faust.buffer_size, this.numOut, this.mixing, this.outs);
                // Check the level to possibly set the voice in kFreeVoice again
                if ((this.dsp_voices_level[i] < 0.001) && (this.dsp_voices_state[i] === this.kReleaseVoice)) {
                    this.dsp_voices_state[i] = this.kFreeVoice;
                }
            }
        }
        
        // Update bargraph
        this.update_outputs();
        
        // Copy outputs
        for (var channel = 0; channel < input.length; ++channel) {
            var dspOutput = this.dspOutChannnels[i];
            for (var frame = 0; frame < output[channel].length; ++frame) {
                output[channel][frame] = dspOutput[frame];
            }
        }
    }
}

// Compile the WebAssembly file, then register the processor class
fetch('mixer32.wasm')
.then(mix_res => mix_res.arrayBuffer())
.then(mix_bytes => WebAssembly.instantiate(mix_bytes, mixObject))
.then(mix_module =>
      fetch('mydsp.wasm')
      .then(dsp_file => dsp_file.arrayBuffer())
      .then(dsp_bytes => WebAssembly.instantiate(dsp_bytes, importObject))
      .then(dsp_module => { faust.mixer_instance = mix_module.instance;
                            faust.mydsp_instance = dsp_module.instance;
                            registerProcessor('mydsp_poly', mydsp_polyProcessor); })
.catch(function() { faust.error_msg = "Faust mydsp cannot be loaded or compiled"; });



