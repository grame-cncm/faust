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
 
 Additional code : GRAME 2014-2015
 
*/

'use strict';

var faust = faust || {};

<<includeIntrinsic>>
<<includeclass>>

// asm.js mixer
function mydspMixer(global, foreign, buffer) {
	
	'use asm';
	
    var HEAP32 = new global.Int32Array(buffer);
    var HEAPF32 = new global.Float32Array(buffer);

    var max = global.Math.max;
    var abs = global.Math.abs;
 
    function clearOutput(count, channels, outputs) {
        count = count | 0;
        channels = channels | 0;
        outputs = outputs | 0;
        var i = 0;
        var j = 0;
        for (i = 0; ((i | 0) < (channels | 0) | 0); i = ((i | 0) + 1 | 0)) {
            for (j = 0; ((j | 0) < (count | 0) | 0); j = ((j | 0) + 1 | 0)) {
               HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2] = 0.;
            }
        }
    }

    function mixVoice(count, channels, inputs, outputs) {
        count = count | 0;
        channels = channels | 0;
        inputs = inputs | 0;
        outputs = outputs | 0;
        var i = 0;
        var j = 0;
        var level = 0.;
        for (i = 0; ((i | 0) < (channels | 0) | 0); i = ((i | 0) + 1 | 0)) {
            for (j = 0; ((j | 0) < (count | 0) | 0); j = ((j | 0) + 1 | 0)) {
                level = max(+level, +(abs(+(HEAPF32[(HEAP32[inputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]))));
                HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2] 
                    = +(HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]) + 
                      +(HEAPF32[(HEAP32[inputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]);
            }
        }
        return +level;
    }

    return { mixVoice: mixVoice, clearOutput: clearOutput};
}

// Polyphonic Faust DSP
faust.mydsp_poly = function (context, buffer_size, max_polyphony, callback) {

    var handler = null;
    var ins, outs;
    var mixing;
    var compute_callback = callback;
    
    var scriptProcessor;
    
    var dspInChannnels = [];
    var dspOutChannnels = [];
    
    var fFreqLabel;
    var fGateLabel;
    var fGainLabel;
    var fDate = 0;
    
    // Keep JSON parsed object
    var json_object = JSON.parse(getJSONmydsp());
    
    function getNumInputsAux () 
    {
        return (json_object.inputs !== undefined) ? parseInt(json_object.inputs) : 0;
    }
    
    function getNumOutputsAux () 
    {
        return (json_object.outputs !== undefined) ? parseInt(json_object.outputs) : 0;
    }
      
    var numIn = getNumInputsAux();
    var numOut = getNumOutputsAux();
 
    // Memory allocator
    var ptr_size = 4; 
    var sample_size = 4;
    
    function pow2limit (x)
    {
        var n = 65536; // Minimum = 64 kB
        while (n < x) { n = 2 * n; }
        return n;
    }
    
    // Output * 2 to handle mixing channels
    var memory_size = pow2limit(getSizemydsp() * max_polyphony + ((getNumInputsAux() + getNumOutputsAux() * 2) * (ptr_size + (buffer_size * sample_size))));
  
    console.log(getNumInputsAux());
    console.log(getNumOutputsAux());
    console.log(memory_size);
    
    var HEAP = new ArrayBuffer(memory_size);
    var HEAP32 = new Int32Array(HEAP);
    var HEAPF32 = new Float32Array(HEAP);
     
    console.log(HEAP);
    console.log(HEAP32);
    console.log(HEAPF32);
 
    // bargraph
    var ouputs_timer = 5;
    var ouputs_items = [];
     
    // input items
    var inputs_items = [];
     
    // Start of HEAP index
    var audio_heap_ptr = 0;
     
    // Setup pointers offset
    var audio_heap_ptr_inputs = audio_heap_ptr; 
    var audio_heap_ptr_outputs = audio_heap_ptr_inputs + (getNumInputsAux() * ptr_size);
    var audio_heap_ptr_mixing = audio_heap_ptr_outputs + (getNumOutputsAux() * ptr_size);
     
    // Setup buffer offset
    var audio_heap_inputs = audio_heap_ptr_mixing + (getNumOutputsAux() * ptr_size);
    var audio_heap_outputs = audio_heap_inputs + (getNumInputsAux() * buffer_size * sample_size);
    var audio_heap_mixing = audio_heap_outputs + (getNumOutputsAux() * buffer_size * sample_size);
    
    // Setup DSP voices offset
    var dsp_start = audio_heap_mixing + (getNumOutputsAux() * buffer_size * sample_size);
    
    // ASM module
    var factory = mydspModule(window, window.Math, HEAP);
    var mixer = mydspMixer(window, null, HEAP);
    console.log(factory);
    
    // Start of DSP memory ('polyphony' DSP voices)
    var dsp_voices = [];
    var dsp_voices_state = [];
    var dsp_voices_level = [];
    var dsp_voices_date = [];
    var dsp_voices_trigger = [];
    
    var kActiveVoice = 0;
    var kFreeVoice = -1;
    var kReleaseVoice = -2;
    var kNoVoice = -3;

    for (var i = 0; i < max_polyphony; i++) {
        dsp_voices[i] = dsp_start + i * getSizemydsp();
        dsp_voices_state[i] = kFreeVoice;
        dsp_voices_level[i] = 0;
        dsp_voices_date[i] = 0;
        dsp_voices_trigger[i] = false;
    }
    
    // Always returns a voice
    function newVoiceAux()
    {
        var voice = getVoice(kFreeVoice, true);
        dsp_voices_state[voice] = kActiveVoice;
        return voice;
    }
    
    function getVoice (note, steal)
    {
        for (var i = 0; i < max_polyphony; i++) {
            if (dsp_voices_state[i] === note) {
                if (steal) { dsp_voices_date[i] = fDate++; }
                return i;
            }
        }
        
        if (steal) {
            var voice_release = kNoVoice;
            var voice_playing = kNoVoice;
            var oldest_date_release = Number.MAX_VALUE;
            var oldest_date_playing = Number.MAX_VALUE;

            // Scan all voices
            for (var i = 0; i < max_polyphony; i++) {
                // Try to steal a voice in kReleaseVoice mode...
                if (dsp_voices_state[i] === kReleaseVoice) {
                    // Keeps oldest release voice
                    if (dsp_voices_date[i] < oldest_date_release) {
                        oldest_date_release = dsp_voices_date[i];
                        voice_release = i;
                    }
            } else {
                if (dsp_voices_date[i] < oldest_date_playing) {
                    oldest_date_playing = dsp_voices_date[i];
                    voice_playing = i;
                }
            }
        }

        // Then decide which one to steal
        if (oldest_date_release != Number.MAX_VALUE) {
            console.log("Steal release voice : voice_date = %d cur_date = %d voice = %d", dsp_voices_date[voice_release], fDate, voice_release);
            dsp_voices_date[voice_release] = fDate++;
            dsp_voices_trigger[voice_release] = true;
            return voice_release;
        } else {
            console.log("Steal playing voice : voice_date = %d cur_date = %d voice = %d", dsp_voices_date[voice_playing], fDate, voice_playing);
            dsp_voices_date[voice_playing] = fDate++;
            dsp_voices_trigger[voice_playing] = true;
            return voice_playing;
        }

        } else {
            return kNoVoice;
        }
    }
   
    var pathTable = getPathTablemydsp();
     
    function update_outputs () 
    {
        if (ouputs_items.length > 0 && handler && ouputs_timer-- === 0) {
            ouputs_timer = 5;
            for (var i = 0; i < ouputs_items.length; i++) {
                handler(ouputs_items[i], factory.getParamValue(dsp_voices[0], pathTable[ouputs_items[i]]));
            }
        }
    }
    
    function compute (e) 
    {
        var i, j;
        
        // Read inputs
        for (i = 0; i < numIn; i++) {
            var input = e.inputBuffer.getChannelData(i);
            var dspInput = dspInChannnels[i];
            for (j = 0; j < input.length; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // Possibly call an externally given callback (for instance to play a MIDIFile...)
        if (compute_callback) {
            compute_callback(buffer_size);
        }
        
        // First clear the outputs
        mixer.clearOutput(buffer_size, numOut, outs);
        
        // Compute all running voices
        var level;
        for (i = 0; i < max_polyphony; i++) {
            if (dsp_voices_state[i] != kFreeVoice) {
                if (dsp_voices_trigger[i]) {
                    // FIXME : properly cut the buffer in 2 slices...
                    factory.setParamValue(dsp_voices[i], fGateLabel, 0.0);
                    factory.compute(dsp_voices[i], 1, ins, mixing);
                    factory.setParamValue(dsp_voices[i], fGateLabel, 1.0);
                    factory.compute(dsp_voices[i], buffer_size, ins, mixing);
                    dsp_voices_trigger[i] = false;
                } else {
                    // Compute regular voice
                    factory.compute(dsp_voices[i], buffer_size, ins, mixing);
                }
                // Mix it in result
                dsp_voices_level[i] = mixer.mixVoice(buffer_size, numOut, mixing, outs);
                // Check the level to possibly set the voice in kFreeVoice again
                if ((dsp_voices_level[i] < 0.001) && (dsp_voices_state[i] == kReleaseVoice)) {
                    dsp_voices_state[i] = kFreeVoice;
                }
            }
        }
        
        // Update bargraph
        update_outputs();
        
        // Write outputs
        for (i = 0; i < numOut; i++) {
            var output = e.outputBuffer.getChannelData(i);
            var dspOutput = dspOutChannnels[i];
            for (j = 0; j < output.length; j++) {
                output[j] = dspOutput[j];
            }
        }
    }
    
    function midiToFreq (note) 
    {
        return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
    }
     
    // JSON parsing
    function parse_ui (ui) 
    {
        for (var i = 0; i < ui.length; i++) {
            parse_group(ui[i]);
        }
    }
    
   function parse_group (group) 
    {
        if (group.items) {
            parse_items(group.items);
        }
    }
    
    function parse_items (items) 
    {
        for (var i = 0; i < items.length; i++) {
            parse_item(items[i]);
        }
    }
    
    function parse_item (item) 
    {
        if (item.type === "vgroup" 
        	|| item.type === "hgroup" 
        	|| item.type === "tgroup") {
            parse_items(item.items);
        } else if (item.type === "hbargraph" 
        	|| item.type === "vbargraph") {
            // Keep bargraph adresses
            ouputs_items.push(item.address);
        } else if (item.type === "vslider"
        	 || item.type === "hslider" 
        	 || item.type === "button" 
        	 || item.type === "checkbox" 
        	 || item.type === "nentry") {
            // Keep inputs adresses
            inputs_items.push(item.address);
        }
    }
      
    function init ()
    {
        var i;
        
        // Setup web audio context
        console.log("buffer_size = %d", buffer_size);
        scriptProcessor = context.createScriptProcessor(buffer_size, numIn, numOut);
        scriptProcessor.onaudioprocess = compute;
        
        if (numIn > 0) {
            // allocate memory for input arrays
            ins = audio_heap_ptr_inputs; 
            for (i = 0; i < numIn; i++) { 
                HEAP32[(ins >> 2) + i] = audio_heap_inputs + ((buffer_size * sample_size) * i);
            }
     
            var dspInChans = HEAP32.subarray(ins >> 2, (ins + numIn * ptr_size) >> 2);
            for (i = 0; i < numIn; i++) {
                dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sample_size) >> 2);
            }
        }
        
        if (numOut > 0) {
            // allocate memory for output and mixing arrays
            outs = audio_heap_ptr_outputs; 
            mixing = audio_heap_ptr_mixing; 
            for (i = 0; i < numOut; i++) { 
                HEAP32[(outs >> 2) + i] = audio_heap_outputs + ((buffer_size * sample_size) * i);
                HEAP32[(mixing >> 2) + i] = audio_heap_mixing + ((buffer_size * sample_size) * i);
            }
            
            var dspOutChans = HEAP32.subarray(outs >> 2, (outs + numOut * ptr_size) >> 2);
            for (i = 0; i < numOut; i++) {
                dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sample_size) >> 2);
            }
        }
        
        // bargraph
        parse_ui(json_object.ui);
        
        // keep 'keyOn/keyOff' labels
        for (i = 0; i < inputs_items.length; i++) {
            if (inputs_items[i].endsWith("/gate")) {
                fGateLabel = pathTable[inputs_items[i]];
                console.log(fGateLabel);
            } else if (inputs_items[i].endsWith("/freq")) {
                fFreqLabel = pathTable[inputs_items[i]];
                console.log(fFreqLabel);
            } else if (inputs_items[i].endsWith("/gain")) {
                fGainLabel = pathTable[inputs_items[i]];
                console.log(fGainLabel);
            }
        }
        
        // Init DSP voices
        for (i = 0; i < max_polyphony; i++) {
            factory.init(dsp_voices[i], context.sampleRate);
        }
    }
    
    init();
    
    // External API
    return {
    
        destroy : function  ()
        {
            // Nothing to do
        },
        
        getNumInputs : function () 
        {
            return getNumInputsAux();
        },
        
        getNumOutputs : function() 
        {
            return getNumOutputsAux();
        },
       
        init : function (sample_rate)
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.init(dsp_voices[i], sample_rate);
            }
        },

        instanceInit : function (sample_rate) 
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.instanceInit(dsp_voices[i], sample_rate);
            }
        },

        instanceConstants : function (sample_rate) 
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.instanceConstants(dsp_voices[i], sample_rate);
            }
        },
        
        instanceResetUserInterface : function () 
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.instanceResetUserInterface(dsp_voices[i]);
            }
        },

        instanceClear : function () 
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.instanceClear(dsp_voices[i]);
            }
        },
    
        // Connect/disconnect to another node
        connect : function (node) 
        {
            if (node.getProcessor !== undefined) {
                scriptProcessor.connect(node.getProcessor());
            } else {
                scriptProcessor.connect(node);
            }
        },

        disconnect : function (node) 
        {
            if (node.getProcessor !== undefined) {
                scriptProcessor.disconnect(node.getProcessor());
            } else {
                scriptProcessor.disconnect(node);
            }
        },
        
        setHandler : function (hd)
        {
            handler = hd;
        },
        
        keyOn : function (channel, pitch, velocity)
        {
            var voice = newVoiceAux();
            //console.log("keyOn voice %d", voice);
            factory.setParamValue(dsp_voices[voice], fFreqLabel, midiToFreq(pitch));
            factory.setParamValue(dsp_voices[voice], fGainLabel, velocity/127.);
            dsp_voices_state[voice] = pitch;
            dsp_voices_trigger[voice] = true; // so that envelop is always re-initialized
        },
        
        keyOff : function (channel, pitch, velocity)
        {
            var voice = getVoice(pitch, false);
            if (voice !== kNoVoice) {
                //console.log("keyOff voice %d", voice);
                // No use of velocity for now...
                factory.setParamValue(dsp_voices[voice], fGateLabel, 0.0);
                // Release voice
                dsp_voices_state[voice] = kReleaseVoice;
            } else {
                console.log("Playing voice not found...");
            }
        },
   
        allNotesOff : function ()
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.setParamValue(dsp_voices[i], fGateLabel, 0.0);
                dsp_voices_state[i] = kReleaseVoice;
            }
        },

        ctrlChange : function (channel, ctrl, value)
        {
            if (ctrl === 123 || ctrl === 120) {
                for (var i = 0; i < max_polyphony; i++) {
                    factory.setParamValue(dsp_voices[i], fGateLabel, 0.0);
                    dsp_voices_state[i] = kReleaseVoice;
                }
            }
        },
        
        pitchWheel : function (channel, wheel)
        {},

        start : function () 
        {
            scriptProcessor.connect(context.destination);
        },

        stop : function () 
        {
            scriptProcessor.disconnect(context.destination);
        },

        setParamValue : function (path, val) 
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.setParamValue(dsp_voices[i], pathTable[path], val);
            }
        },

        getParamValue : function (path) 
        {
            return factory.getParamValue(dsp_voices[0], pathTable[path]);
        },

        controls : function()
        {
            return inputs_items;
        },
   
        json : function ()
        {
            return getJSONmydsp();
        },
        
        getSampleRate : function ()
        {
            return context.sampleRate;
        },
        
        setComputeCallback : function (callback) 
        {
            compute_callback = callback;
        },
        
        getComputeCallback : function () 
        {
            return compute_callback;
        },
        
        getProcessor : function ()
        {
            return scriptProcessor;
        }
    };
};

