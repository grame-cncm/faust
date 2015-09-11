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
    var sqrt = global.Math.sqrt;

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

    function mixVoice(count, channels, inputs, outputs, polyphony) {
        count = count | 0;
        channels = channels | 0;
        inputs = inputs | 0;
        outputs = outputs | 0;
        polyphony = +polyphony;
        var i = 0;
        var j = 0;
        var level = 0.;
        var gain_level = 0.;
        gain_level = 1. / +sqrt(polyphony);
        for (i = 0; ((i | 0) < (channels | 0) | 0); i = ((i | 0) + 1 | 0)) {
            for (j = 0; ((j | 0) < (count | 0) | 0); j = ((j | 0) + 1 | 0)) {
                level = max(+level, +(abs(+(HEAPF32[(HEAP32[inputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]))));
                HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2] 
                    = +(HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]) + 
                      +(HEAPF32[(HEAP32[inputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]) * +gain_level;
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
    var numIn, numOut, mixing;
    var compute_callback = callback;
    
    var scriptProcessor;
    
    var dspInChannnels = [];
    var dspOutChannnels = [];
    
    var fFreqLabel;
    var fGateLabel;
    var fGainLabel;
    
    // Keep JSON parsed object
    var jon_object = JSON.parse(getJSONmydsp());
    
    function getNumInputsAux () 
    {
        return (jon_object.inputs !== undefined) ? parseInt(jon_object.inputs) : 0;
    }
    
    function getNumOutputsAux () 
    {
        return (jon_object.outputs !== undefined) ? parseInt(jon_object.outputs) : 0;
    }

    // Memory allocator
    var ptr_size = 4; 
    var sample_size = 4;
    
    function pow2limit(x)
    {
        var n = 2;
        while (n < x) { n = 2 * n; }
        return (n < 65536) ? 65536 : n; // Minimum = 64 kB
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
    var factory = mydspModule(window, null, HEAP);
    var mixer = mydspMixer(window, null, HEAP);
    console.log(factory);
    
    // Start of DSP memory ('polyphony' DSP voices)
    var dsp_voices = [];
    var dsp_voices_state = [];
    
    var kFreeVoice = -2;
    var kReleaseVoice = -1;

    for (var i = 0; i < max_polyphony; i++) {
        dsp_voices[i] = dsp_start + i * getSizemydsp();
        dsp_voices_state[i] = kFreeVoice;
    }
    
    function getVoice (note)
    {
        for (var i = 0; i < max_polyphony; i++) {
            if (dsp_voices_state[i] === note) return i;
        }
        return kReleaseVoice;
    }
   
    var pathTable = getPathTablemydsp();
     
    function update_outputs () 
    {
        if (ouputs_items.length > 0 && handler && ouputs_timer-- === 0) {
            ouputs_timer = 5;
            for (var i = 0; i < ouputs_items.length; i++) {
                handler(ouputs_items[i], factory.getValue(dsp_voices[0], pathTable[ouputs_items[i]]));
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
                factory.compute(dsp_voices[i], buffer_size, ins, mixing);
                level = mixer.mixVoice(buffer_size, numOut, mixing, outs, max_polyphony);
                if ((level < 0.001) && (dsp_voices_state[i] == kReleaseVoice)) {
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
        if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
            parse_items(item.items);
        } else if (item.type === "hbargraph" || item.type === "vbargraph") {
            // Keep bargraph adresses
            ouputs_items.push(item.address);
        } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
            // Keep inputs adresses
            inputs_items.push(item.address);
        }
    }
      
    function init ()
    {
        var i;
        
        // Get input / output counts
        numIn = getNumInputsAux();
        numOut = getNumOutputsAux();
        
        // Setup web audio context
        console.log("buffer_size = %d", buffer_size);
        scriptProcessor = context.createScriptProcessor(buffer_size, numIn, numOut);
        scriptProcessor.onaudioprocess = compute;
        
        if (numIn > 0) {
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
        parse_ui(jon_object.ui);
        
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
    
        getNumInputs : function () 
        {
            return getNumInputsAux();
        },
        
        getNumOutputs : function() 
        {
            return getNumOutputsAux();
        },
    
        destroy : function  ()
        {
            // Nothing to do
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
            var voice = getVoice(kFreeVoice);
            if (voice == kReleaseVoice) voice = getVoice(kReleaseVoice);  // Gets a free voice
           
            if (voice >= 0) {
                //console.log("keyOn voice %d", voice);
                factory.setValue(dsp_voices[voice], fFreqLabel, midiToFreq(pitch));
                factory.setValue(dsp_voices[voice], fGainLabel, velocity/127.);
                factory.setValue(dsp_voices[voice], fGateLabel, 1.0);
                dsp_voices_state[voice] = pitch;
            } else {
                console.log("No more free voice...\n");
            }
        },

        keyOff : function (channel, pitch, velocity)
        {
            var voice = getVoice(pitch);
            if (voice >= 0) {
                //console.log("keyOff voice %d", voice);
                factory.setValue(dsp_voices[voice], fGainLabel, velocity/127.);
                factory.setValue(dsp_voices[voice], fGateLabel, 0.0);
                dsp_voices_state[voice] = kReleaseVoice;
            } else {
                console.log("Playing voice not found...\n");
            }
        },

        allNotesOff : function ()
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.setValue(dsp_voices[i], fGateLabel, 0.0);
                dsp_voices_state[i] = kReleaseVoice;
            }
        },

        ctrlChange : function (channel, ctrl, value)
        {},

        pitchBend : function (channel, refPitch, pitch)
        {
            var voice = getVoice(refPitch);
            if (voice >= 0) {
                factory.setValue(dsp_voices[voice], fFreqLabel, midiToFreq(pitch));
            } else {
                console.log("Playing voice not found...\n");
            }
        },

        start : function () 
        {
            scriptProcessor.connect(context.destination);
        },

        stop : function () 
        {
            scriptProcessor.disconnect(context.destination);
        },

        setValue : function (path, val) 
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.setValue(dsp_voices[i], pathTable[path], val);
            }
        },

        getValue : function (path) 
        {
            return factory.getValue(dsp_voices[0], pathTable[path]);
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
        
        setComputeCallback : function (callback) {
            compute_callback = callback;
        },
        
        getComputeCallback : function () {
            return compute_callback;
        },
        
        getProcessor : function ()
        {
            return scriptProcessor;
        }
    };
};

