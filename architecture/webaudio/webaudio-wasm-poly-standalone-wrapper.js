/*
 faust2webaudio

 Primarily written by Myles Borins
 During the Spring 2013 offering of Music 420b with Julius Smith
 A bit during the Summer of 2013 with the help of Joshua Kit Clayton
 And finally a sprint during the late fall of 2013 to get everything working
 A Special thanks to Yann Orlarey and Stéphane Letz

 faust2webaudio is distributed under the terms the MIT or GPL2 Licenses.
 Choose the license that best suits your project. The text of the MIT and GPL
 licenses are at the root directory.

 Additional code: GRAME 2014-2017
*/

'use strict';

var faust = faust || {};

faust.error_msg = null;
faust.getErrorMessage = function() { return faust.error_msg; };

faust.remap = function(v, mn0, mx0, mn1, mx1)
{
    return (1.0 * (v - mn0) / (mx0 - mn0)) * (mx1 - mn1) + mn1;
}

faust.debug = false;

// Polyphonic Faust DSP

/**
 * Constructor
 *
 * @param mixer_instance - the wasm mixer instance
 * @param dsp_instance - the wasm DSP instance
 * @param memory - the wasm memory
 * @param context - the Web Audio context
 * @param buffer_size - the buffer_size in frames
 * @param polyphony - the number of polyphonic voices
 *
 * @return a valid WebAudio ScriptProcessorNode object or null
 */
faust.mydsp_poly = function (mixer_instance, dsp_instance, memory, context, buffer_size, polyphony) {

    // Keep JSON parsed object
    var json_object = null;
    try {
        json_object = JSON.parse(getJSONmydsp());
    } catch (e) {
        faust.error_msg = "Error in JSON.parse: " + e;
        return null;
    }

    var sp;
    try {
        sp = context.createScriptProcessor(buffer_size, parseInt(json_object.inputs), parseInt(json_object.outputs));
    } catch (e) {
        faust.error_msg = "Error in createScriptProcessor: " + e;
        return null;
    }

    sp.json_object = json_object;

    sp.output_handler = null;
    sp.ins = null;
    sp.outs = null;
    sp.mixing = null;
    sp.compute_handler = null;

    sp.dspInChannnels = [];
    sp.dspOutChannnels = [];

    sp.fFreqLabel = "";
    sp.fGateLabel = "";
    sp.fGainLabel = "";
    sp.fDate = 0;

    sp.fPitchwheelLabel = [];
    sp.fCtrlLabel = new Array(128);
    for (var i = 0; i < sp.fCtrlLabel.length; i++) { sp.fCtrlLabel[i] = []; }

    sp.numIn = parseInt(sp.json_object.inputs);
    sp.numOut = parseInt(sp.json_object.outputs);

    // Memory allocator
    sp.ptr_size = 4;
    sp.sample_size = 4;

    console.log(sp.numIn);
    console.log(sp.numOut);

    sp.factory = dsp_instance.exports;
    sp.HEAP = memory.buffer;
    sp.HEAP32 = new Int32Array(sp.HEAP);
    sp.HEAPF32 = new Float32Array(sp.HEAP);

    console.log(sp.HEAP);
    console.log(sp.HEAP32);
    console.log(sp.HEAPF32);

    // bargraph
    sp.outputs_timer = 5;
    sp.outputs_items = [];

    // input items
    sp.inputs_items = [];

    // Start of HEAP index
    sp.audio_heap_ptr = 0;

    // Setup pointers offset
    sp.audio_heap_ptr_inputs = sp.audio_heap_ptr;
    sp.audio_heap_ptr_outputs = sp.audio_heap_ptr_inputs + (sp.numIn * sp.ptr_size);
    sp.audio_heap_ptr_mixing = sp.audio_heap_ptr_outputs + (sp.numOut * sp.ptr_size);

    // Setup buffer offset
    sp.audio_heap_inputs = sp.audio_heap_ptr_mixing + (sp.numOut * sp.ptr_size);
    sp.audio_heap_outputs = sp.audio_heap_inputs + (sp.numIn * buffer_size * sp.sample_size);
    sp.audio_heap_mixing = sp.audio_heap_outputs + (sp.numOut * buffer_size * sp.sample_size);

    // Setup DSP voices offset
    sp.dsp_start = sp.audio_heap_mixing + (sp.numOut * buffer_size * sp.sample_size);

    // wasm mixer
    sp.mixer = mixer_instance.exports;

    console.log(sp.mixer);
    console.log(sp.factory);

    // Start of DSP memory ('polyphony' DSP voices)
    sp.dsp_voices = [];
    sp.dsp_voices_state = [];
    sp.dsp_voices_level = [];
    sp.dsp_voices_date = [];
    sp.dsp_voices_trigger = [];

    sp.kActiveVoice = 0;
    sp.kFreeVoice = -1;
    sp.kReleaseVoice = -2;
    sp.kNoVoice = -3;

    sp.pathTable = [];

    for (var i = 0; i < polyphony; i++) {
        sp.dsp_voices[i] = sp.dsp_start + i * parseInt(json_object.size);
        sp.dsp_voices_state[i] = sp.kFreeVoice;
        sp.dsp_voices_level[i] = 0;
        sp.dsp_voices_date[i] = 0;
        sp.dsp_voices_trigger[i] = false;
    }

    sp.getPlayingVoice = function(pitch)
    {
        var voice_playing = sp.kNoVoice;
        var oldest_date_playing = Number.MAX_VALUE;

        for (var i = 0; i < polyphony; i++) {
            if (sp.dsp_voices_state[i] === pitch) {
                // Keeps oldest playing voice
                if (sp.dsp_voices_date[i] < oldest_date_playing) {
                    oldest_date_playing = sp.dsp_voices_date[i];
                    voice_playing = i;
                }
            }
        }

        return voice_playing;
    }

    // Always returns a voice
    sp.allocVoice = function(voice)
    {
        sp.dsp_voices_date[voice] = sp.fDate++;
        sp.dsp_voices_trigger[voice] = true;    //so that envelop is always re-initialized
        sp.dsp_voices_state[voice] = sp.kActiveVoice;
        return voice;
    }

    sp.getFreeVoice = function()
    {
        for (var i = 0; i < polyphony; i++) {
            if (sp.dsp_voices_state[i] === sp.kFreeVoice) {
                return sp.allocVoice(i);
            }
        }

        var voice_release = sp.kNoVoice;
        var voice_playing = sp.kNoVoice;
        var oldest_date_release = Number.MAX_VALUE;
        var oldest_date_playing = Number.MAX_VALUE;

        // Scan all voices
        for (var i = 0; i < polyphony; i++) {
            // Try to steal a voice in kReleaseVoice mode...
            if (sp.dsp_voices_state[i] === sp.kReleaseVoice) {
                // Keeps oldest release voice
                if (sp.dsp_voices_date[i] < oldest_date_release) {
                    oldest_date_release = sp.dsp_voices_date[i];
                    voice_release = i;
                }
            } else {
                if (sp.dsp_voices_date[i] < oldest_date_playing) {
                    oldest_date_playing = sp.dsp_voices_date[i];
                    voice_playing = i;
                }
            }
        }

        // Then decide which one to steal
        if (oldest_date_release != Number.MAX_VALUE) {
            if (faust.debug)
                console.log("Steal release voice : voice_date = %d cur_date = %d voice = %d", sp.dsp_voices_date[voice_release], sp.fDate, voice_release);
            return sp.allocVoice(voice_release);
        } else if (oldest_date_playing != Number.MAX_VALUE) {
            if (faust.debug)
                console.log("Steal playing voice : voice_date = %d cur_date = %d voice = %d", sp.dsp_voices_date[voice_playing], sp.fDate, voice_playing);
            return sp.allocVoice(voice_playing);
        } else {
            return sp.kNoVoice;
        }
    }

    sp.update_outputs = function ()
    {
        if (sp.outputs_items.length > 0 && sp.output_handler && sp.outputs_timer-- === 0) {
            sp.outputs_timer = 5;
            for (var i = 0; i < sp.outputs_items.length; i++) {
                sp.output_handler(sp.outputs_items[i], sp.factory.getParamValue(sp.dsp_voices[0], sp.pathTable[sp.outputs_items[i]]));
            }
        }
    }

    sp.compute = function (e)
    {
        var i, j;

        // Read inputs
        for (i = 0; i < sp.numIn; i++) {
            var input = e.inputBuffer.getChannelData(i);
            var dspInput = sp.dspInChannnels[i];
            dspInput.set(input);
        }

        // Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
        if (sp.compute_handler) {
            sp.compute_handler(buffer_size);
        }

        // First clear the outputs
        sp.mixer.clearOutput(buffer_size, sp.numOut, sp.outs);

        // Compute all running voices
        for (i = 0; i < polyphony; i++) {
            if (sp.dsp_voices_state[i] != sp.kFreeVoice) {
                if (sp.dsp_voices_trigger[i]) {
                    // FIXME : properly cut the buffer in 2 slices...
                    sp.factory.setParamValue(sp.dsp_voices[i], sp.fGateLabel, 0.0);
                    sp.factory.compute(sp.dsp_voices[i], 1, sp.ins, sp.mixing);
                    sp.factory.setParamValue(sp.dsp_voices[i], sp.fGateLabel, 1.0);
                    sp.factory.compute(sp.dsp_voices[i], buffer_size, sp.ins, sp.mixing);
                    sp.dsp_voices_trigger[i] = false;
                } else {
                    // Compute regular voice
                    sp.factory.compute(sp.dsp_voices[i], buffer_size, sp.ins, sp.mixing);
                }
                // Mix it in result
                sp.dsp_voices_level[i] = sp.mixer.mixVoice(buffer_size, sp.numOut, sp.mixing, sp.outs);
                // Check the level to possibly set the voice in kFreeVoice again
                if ((sp.dsp_voices_level[i] < 0.001) && (sp.dsp_voices_state[i] === sp.kReleaseVoice)) {
                    sp.dsp_voices_state[i] = sp.kFreeVoice;
                }
            }
        }

        // Update bargraph
        sp.update_outputs();

        // Write outputs
        for (i = 0; i < sp.numOut; i++) {
            var output = e.outputBuffer.getChannelData(i);
            var dspOutput = sp.dspOutChannnels[i];
            output.set(dspOutput);
        }
    }

    sp.midiToFreq = function (note)
    {
        return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
    }

    // JSON parsing
    sp.parse_ui = function (ui)
    {
        for (var i = 0; i < ui.length; i++) {
            sp.parse_group(ui[i]);
        }
    }

    sp.parse_group = function (group)
    {
        if (group.items) {
            sp.parse_items(group.items);
        }
    }

    sp.parse_items = function (items)
    {
        for (var i = 0; i < items.length; i++) {
            sp.parse_item(items[i]);
        }
    }

    sp.parse_item = function (item)
    {
        if (item.type === "vgroup"
        	|| item.type === "hgroup"
        	|| item.type === "tgroup") {
            sp.parse_items(item.items);
        } else if (item.type === "hbargraph"
        	|| item.type === "vbargraph") {
            // Keep bargraph adresses
            sp.outputs_items.push(item.address);
            sp.pathTable[item.address] = parseInt(item.index);
        } else if (item.type === "vslider"
        	|| item.type === "hslider"
        	|| item.type === "button"
        	|| item.type === "checkbox"
        	|| item.type === "nentry") {
            // Keep inputs adresses
            sp.inputs_items.push(item.address);
            sp.pathTable[item.address] = parseInt(item.index);
            if (item.meta !== undefined) {
                for (var i = 0; i < item.meta.length; i++) {
                    if (item.meta[i].midi !== undefined) {
                        if (item.meta[i].midi.trim() === "pitchwheel") {
                            sp.fPitchwheelLabel.push(item.address);
                        } else if (item.meta[i].midi.trim().split(" ")[0] === "ctrl") {
                            sp.fCtrlLabel[parseInt(item.meta[i].midi.trim().split(" ")[1])]
                                .push({ path:item.address,
                                        min:parseFloat(item.min),
                                        max:parseFloat(item.max) });
                        }
                    }
                }
            }
        }
    }

    sp.initAux = function ()
    {
        var i;

        console.log("buffer_size %d", buffer_size);
        sp.onaudioprocess = sp.compute;

        if (sp.numIn > 0) {
            sp.ins = sp.audio_heap_ptr_inputs;
            for (i = 0; i < sp.numIn; i++) {
                sp.HEAP32[(sp.ins >> 2) + i] = sp.audio_heap_inputs + ((buffer_size * sp.sample_size) * i);
            }

            // Prepare Ins buffer tables
            var dspInChans = sp.HEAP32.subarray(sp.ins >> 2, (sp.ins + sp.numIn * sp.ptr_size) >> 2);
            for (i = 0; i < sp.numIn; i++) {
                sp.dspInChannnels[i] = sp.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sp.sample_size) >> 2);
            }
        }

        if (sp.numOut > 0) {
            // allocate memory for output and mixing arrays
            sp.outs = sp.audio_heap_ptr_outputs;
            sp.mixing = sp.audio_heap_ptr_mixing;

            for (i = 0; i < sp.numOut; i++) {
                sp.HEAP32[(sp.outs >> 2) + i] = sp.audio_heap_outputs + ((buffer_size * sp.sample_size) * i);
                sp.HEAP32[(sp.mixing >> 2) + i] = sp.audio_heap_mixing + ((buffer_size * sp.sample_size) * i);
            }

            // Prepare Out buffer tables
            var dspOutChans = sp.HEAP32.subarray(sp.outs >> 2, (sp.outs + sp.numOut * sp.ptr_size) >> 2);
            for (i = 0; i < sp.numOut; i++) {
                sp.dspOutChannnels[i] = sp.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sp.sample_size) >> 2);
            }
        }

        // Parse JSON UI part
        sp.parse_ui(sp.json_object.ui);

        // keep 'keyOn/keyOff' labels
        for (i = 0; i < sp.inputs_items.length; i++) {
            if (sp.inputs_items[i].endsWith("/gate")) {
                sp.fGateLabel = sp.pathTable[sp.inputs_items[i]];
                console.log(sp.fGateLabel);
            } else if (sp.inputs_items[i].endsWith("/freq")) {
                sp.fFreqLabel = sp.pathTable[sp.inputs_items[i]];
                console.log(sp.fFreqLabel);
            } else if (sp.inputs_items[i].endsWith("/gain")) {
                sp.fGainLabel = sp.pathTable[sp.inputs_items[i]];
                console.log(sp.fGainLabel);
            }
        }

        // Init DSP voices
        for (i = 0; i < polyphony; i++) {
            sp.factory.init(sp.dsp_voices[i], context.sampleRate);
        }
    }

    /*
    	Public API to be used to control the WebAudio node.
    */

    /* Return current sample rate. */
    sp.getSampleRate = function ()
    {
        return context.sampleRate;
    }

    /* Return instance number of audio inputs. */
    sp.getNumInputs = function ()
    {
        return sp.numIn;
    }

    /* Return instance number of audio outputs. */
    sp.getNumOutputs = function ()
    {
        return sp.numOut;
    }

    /**
     * Global init, doing the following initialization:
     * - static tables initialization
     * - call 'instanceInit': constants and instance state initialisation
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    sp.init = function (sample_rate)
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.init(sp.dsp_voices[i], sample_rate);
        }
    }

    /**
     * Init instance state.
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    sp.instanceInit = function (sample_rate)
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.instanceInit(sp.dsp_voices[i], sample_rate);
        }
    }

    /**
     * Init instance constant state.
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    sp.instanceConstants = function (sample_rate)
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.instanceConstants(sp.dsp_voices[i], sample_rate);
        }
    }

    /* Init default control parameters values. */
    sp.instanceResetUserInterface = function ()
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.instanceResetUserInterface(sp.dsp_voices[i]);
        }
    }

	/* Init instance state (delay lines...). */
    sp.instanceClear = function ()
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.instanceClear(sp.dsp_voices[i]);
        }
    }

    /**
     * Trigger the Meta handler with instance specific calls to 'declare' (key, value) metadata.
     *
     * @param handler - the Meta handler as a 'declare' function of type (key, value)
     */
    sp.metadata = function (handler)
    {
       if (json_object.meta) {
    		json_object.meta.forEach(function(meta) {
    			handler.declare(Object.keys(meta)[0], Object.values(meta)[0]);
    		});
       }
    }

    /**
     * Setup a control output handler with a function of type (path, value)
     * to be used on each generated output value. This handler will be called
     * each audio cycle at the end of the 'compute' method.
     *
     * @param handler - a function of type function(path, value)
     */
    sp.setOutputParamHandler = function (handler)
    {
        sp.output_handler = handler;
    }

    /**
     * Get the current output handler.
     */
    sp.getOutputParamHandler = function ()
    {
        return sp.output_handler;
    }

    /**
     * Instantiates a new polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    sp.keyOn = function (channel, pitch, velocity)
    {
        var voice = sp.getFreeVoice();
        if (faust.debug)
            console.log("keyOn voice %d", voice);
        sp.factory.setParamValue(sp.dsp_voices[voice], sp.fFreqLabel, sp.midiToFreq(pitch));
        sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGainLabel, velocity/127.);
        sp.dsp_voices_state[voice] = pitch;
    }

    /**
     * De-instantiates a polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    sp.keyOff = function (channel, pitch, velocity)
    {
        var voice = sp.getPlayingVoice(pitch);
        if (voice !== sp.kNoVoice) {
            if (faust.debug)
                console.log("keyOff voice %d", voice);
            // No use of velocity for now...
            sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGateLabel, 0.0);
            // Release voice
            sp.dsp_voices_state[voice] = sp.kReleaseVoice;
        } else {
            if (faust.debug)
                console.log("Playing voice not found...");
        }
    }

    /**
     * Gently terminates all the active voices.
     */
    sp.allNotesOff = function ()
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.setParamValue(sp.dsp_voices[i], sp.fGateLabel, 0.0);
            sp.dsp_voices_state[i] = sp.kReleaseVoice;
        }
    }

    /**
     * Controller
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param ctrl - the MIDI controller number (0..127)
     * @param value - the MIDI controller value (0..127)
     */
    sp.ctrlChange = function (channel, ctrl, value)
    {
        if (ctrl === 123 || ctrl === 120) {
            sp.allNotesOff();
        }
        if (sp.fCtrlLabel[ctrl] !== []) {
            for (var i = 0; i < sp.fCtrlLabel[ctrl].length; i++) {
            	var path = sp.fCtrlLabel[ctrl][i].path;
            	sp.setParamValue(path, faust.remap(value, 0, 127, sp.fCtrlLabel[ctrl][i].min, sp.fCtrlLabel[ctrl][i].max));
                if (sp.output_handler) {
                    sp.output_handler(path, sp.getParamValue(path));
                }
            }
        }
    }

    /**
     * PitchWeel
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param value - the MIDI controller value (-1..1)
     */
    sp.pitchWheel = function (channel, wheel)
    {
        for (var i = 0; i < sp.fPitchwheelLabel.length; i++) {
        	var path = sp.fPitchwheelLabel[i];
        	sp.setParamValue(path, Math.pow(2.0, wheel/12.0));
            if (sp.output_handler) {
                sp.output_handler(path, sp.getParamValue(path));
            }
        }
    }

    /**
     * Set parameter value.
     *
     * @param path - the path to the wanted parameter (retrieved using 'getParams' method)
     * @param val - the float value for the wanted parameter
     */
    sp.setParamValue = function (path, val)
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.setParamValue(sp.dsp_voices[i], sp.pathTable[path], val);
        }
    }

    /**
     * Get parameter value.
     *
     * @param path - the path to the wanted parameter (retrieved using 'getParams' method)
     *
     * @return the float value
     */
    sp.getParamValue = function (path)
    {
        return sp.factory.getParamValue(sp.dsp_voices[0], sp.pathTable[path]);
    }

    /**
     * Get the table of all input parameter paths.
     *
     * @returnthe table of all input parameter paths
     */
    sp.getParams = function()
    {
        return sp.inputs_items;
    }

    /**
     * Get DSP JSON description with its UI and metadata.
     *
     * @return DSP JSON description
     */
    sp.getJSON = function ()
    {
        return getJSONmydsp();
    }

    /**
     * Set a compute handler to be called each audio cycle
     * (for instance to synchronize playing a MIDIFile...).
     *
     * @param handler - a function of type function(buffer_size)
     */
    sp.setComputeHandler = function (handler)
    {
        sp.compute_handler = handler;
    }

    /**
     * Get the current compute handler.
     */
    sp.getComputeHandler = function ()
    {
        return sp.compute_handler;
    }

    // Init resulting DSP
    sp.initAux();

    return sp;
};

faust.createMemory = function (buffer_size, polyphony) {

    // Memory allocator
    var ptr_size = 4;
    var sample_size = 4;

    function pow2limit(x)
    {
    	var n = 65536; // Minimum = 64 kB
		while (n < x) { n = 2 * n; }
		return n;
    }

    // Keep JSON parsed object
    var json_object = null;
    try {
        json_object = JSON.parse(getJSONmydsp());
    } catch (e) {
        faust.error_msg = "Error in JSON.parse: " + e;
        return null;
    }

    var memory_size = pow2limit(parseInt(json_object.size) * polyphony + ((parseInt(json_object.inputs) + parseInt(json_object.outputs) * 2) * (ptr_size + (buffer_size * sample_size)))) / 65536;
    memory_size = Math.max(2, memory_size); // As least 2
    return new WebAssembly.Memory({ initial: memory_size, maximum: memory_size });
}

/**
 * Create a 'polyphonic' ScriptProcessorNode Web Audio object
 * by loading and compiling the Faust wasm file
 * to be use for the voice, and allocating the number of needed voices
 *
 * @param context - the Web Audio context
 * @param buffer_size - the buffer_size in frames
 * @param polyphony - the number of polyphonic voices
 * @param callback - a callback taking the created ScriptProcessorNode as parameter, or null in case of error
 */
faust.createmydsp_poly = function(context, buffer_size, polyphony, callback)
{
    var memory = faust.createMemory(buffer_size, polyphony);
   
    var mixObject = { imports: { print: arg => console.log(arg) } }
    mixObject["memory"] = { "memory": memory };
    
    var importObject = {
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
            
            memory: memory,
                
            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };

    fetch('mixer32.wasm')
    .then(mix_res => mix_res.arrayBuffer())
    .then(mix_bytes => WebAssembly.instantiate(mix_bytes, mixObject))
    .then(mix_module =>
          fetch('mydsp.wasm')
          .then(dsp_file => dsp_file.arrayBuffer())
          .then(dsp_bytes => WebAssembly.instantiate(dsp_bytes, importObject))
          .then(dsp_module => callback(faust.mydsp_poly(mix_module.instance, dsp_module.instance, memory, context, buffer_size, polyphony)))
          .catch(function(error) { console.log(error); faust.error_msg = "Faust mydsp_poly cannot be loaded or compiled"; callback(null); }))
    .catch(function(error) { console.log(error); faust.error_msg = "Faust mydsp_poly cannot be loaded or compiled"; callback(null); });
}

