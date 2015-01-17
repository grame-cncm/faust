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
 
 Additional code : GRAME 2014
 
 */

var faust = faust || {};

// Shim AudioContext on webkit
window.AudioContext = window.AudioContext || window.webkitAudioContext || undefined;
<<includeIntrinsic>>
<<includeclass>>

// asm.js mixer
function mydspMixer(global, foreign, buffer) {
	
	'use asm';
	
    var HEAP32 = new global.Int32Array(buffer);
	var HEAPF32 = new global.Float32Array(buffer);
    
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
        for (i = 0; ((i | 0) < (channels | 0) | 0); i = ((i | 0) + 1 | 0)) {
            for (j = 0; ((j | 0) < (count | 0) | 0); j = ((j | 0) + 1 | 0)) {
                HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2] 
                    = +(HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]) + 
                      +(HEAPF32[(HEAP32[inputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]);
             }
        }
	}
	
	return { mixVoice: mixVoice, clearOutput: clearOutput};
}

// Polyphonic Faust DSP
faust.mydsp_poly = function (context, buffer_size, polyphony) {

    var that = {};
    
    faust.context = context;
 
    that.polyphony = polyphony;
    that.buffer_size = buffer_size;
    that.handler = null;
 
    that.ptr_size = 4; 
    that.sample_size = 4;
     
     // Memory allocator
    that.maxInputs = 128;
    that.maxOutputs = 128;
    that.maxBufferSize = 8192;
    console.log(getSizemydsp());
    
    /*
    var size = getSizemydsp() + (that.maxInputs + that.maxOutputs) * that.ptr_size + (that.maxInputs + that.maxOutputs) * that.maxBufferSize * that.sample_size;
    size = window.Math.floor(size/4096);
    size = (size + 1) * 4096;
    */
 
    // Next valid heap size for ASM code is 0x3000000 (given by Firefox), use twice of it for the DSP size itself....
    that.HEAP = new ArrayBuffer(0x3000000*2);
    var buffer = that.HEAP;
    
    that.HEAP32 = new window.Int32Array(that.HEAP);
    that.HEAPF32 = new window.Float32Array(that.HEAP);
     
    console.log(that.HEAP);
    console.log(that.HEAP32);
    console.log(that.HEAPF32);
 
    // bargraph
    that.ouputs_timer = 5;
    that.ouputs_items = [];
     
    // input items
    that.inputs_items = [];
     
    // Start of HEAP index
    that.audio_heap_ptr = 0;
     
    // Setup pointers offset
    that.audio_heap_ptr_inputs = that.audio_heap_ptr; 
    that.audio_heap_ptr_outputs = that.audio_heap_ptr_inputs + (that.maxInputs * that.ptr_size);
    that.audio_heap_ptr_mixing = that.audio_heap_ptr_outputs + (that.maxOutputs * that.ptr_size);
     
    // Setup buffer offset
    that.audio_heap_inputs = that.audio_heap_ptr_outputs + (that.maxOutputs * that.ptr_size);
    that.audio_heap_outputs = that.audio_heap_inputs + (that.maxInputs * that.buffer_size * that.sample_size);
    that.audio_heap_mixing = that.audio_heap_outputs + (that.maxOutputs * that.buffer_size * that.sample_size)
    
    // Setup DSP voices offset
    that.dsp_start = that.audio_heap_mixing + (that.maxOutputs * that.buffer_size * that.sample_size);
    
    // ASM module
    that.factory = mydspFactory(window, null, that.HEAP);
    that.mixer = mydspMixer(window, null, that.HEAP);
    console.log(that.factory);
    
    // Start of DSP memory ('polyphony' DSP voices)
    that.dsp_voices = [];
    var voice;
    for (voice = 0; voice < that.polyphony; voice++) {
        that.dsp_voices[voice] = that.dsp_start + voice * getSizemydsp();
    }
   
    that.pathTable = getPathTablemydsp();
    
    that.getNumInputs = function () 
    {
        return that.factory.getNumInputs(that.dsp_voices[0]);
    };
    
    that.getNumOutputs = function () 
    {
        return that.factory.getNumOutputs(that.dsp_voices[0]);
    };
    
    that.update_outputs = function () 
    {
        if (that.ouputs_items.length > 0 && that.handler && that.ouputs_timer-- === 0) {
            that.ouputs_timer = 5;
            var i;
            for (i = 0; i < that.ouputs_items.length; i++) {
                that.handler(that.ouputs_items[i], that.factory.getValue(that.dsp_voices[0], that.pathTable[that.ouputs_items[i]]));
            }
        }
    };
    
    that.compute = function (e) 
    {
        var i, j;
        
        // Read inputs
        for (i = 0; i < that.numIn; i++) {
            var input = e.inputBuffer.getChannelData(i);
            var dspInput = that.dspInChannnels[i];
            for (j = 0; j < input.length; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // First clear the outputs
        that.mixer.clearOutput(that.buffer_size, that.numOut, that.outs);
        
        // Compute
        for (i = 0; i < that.polyphony; i++) {
            that.factory.compute(that.dsp_voices[i], that.buffer_size, that.ins, that.mixing);
            that.mixer.mixVoice(that.buffer_size, that.numOut, that.mixing, that.outs);
        }
       
        // Update bargraph
        that.update_outputs();
        
        // Write outputs
        for (i = 0; i < that.numOut; i++) {
            var output = e.outputBuffer.getChannelData(i);
            var dspOutput = that.dspOutChannnels[i];
            for (j = 0; j < output.length; j++) {
                output[j] = dspOutput[j];
            }
        }
    };
 
    that.destroy = function ()
    {
        // Nothing to do
    };
    
    // Connect/disconnect to another node
    that.connect = function (node) 
    {
        if (node.scriptProcessor) {
            that.scriptProcessor.connect(node.scriptProcessor);
        } else {
            that.scriptProcessor.connect(node);
        }
    };

    that.disconnect = function (node) 
    {
        if (node.scriptProcessor) {
            that.scriptProcessor.disconnect(node.scriptProcessor);
        } else {
            that.scriptProcessor.disconnect(node);
        }
    };
 
    that.setHandler = function (handler)
    {
        that.handler = handler;
    };
    
    that.midiToFreq = function (note) 
    {
        return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
    }
    
    that.keyOn = function (channel, pitch, velocity)
    {
        //console.log("keyOn %d %d %d %f %f", channel, pitch, velocity, that.midiToFreq(pitch),  velocity/127.);
        var voice = pitch - 48;
        that.factory.setValue(that.dsp_voices[voice], that.fFreqLabel, that.midiToFreq(pitch));
        that.factory.setValue(that.dsp_voices[voice], that.fGainLabel, velocity/127.);
        that.factory.setValue(that.dsp_voices[voice], that.fGateLabel, 1.0);
    }
    
    that.keyOff = function (channel, pitch)
    {
        //console.log("keyOff %d %d", channel, pitch);
        var voice = pitch - 48;
        that.factory.setValue(that.dsp_voices[voice], that.fGateLabel, 0.0);
    }
    
    that.ctrlChange = function (channel, ctrl, value)
    {}
    
    that.pitchBend = function (channel, refPitch, pitch)
    {}
    
    // Bind to Web Audio, external API
    that.start = function () 
    {
        that.scriptProcessor.connect(faust.context.destination);
    };
    
    that.stop = function () 
    {
        that.scriptProcessor.disconnect(faust.context.destination);
    };
    
    that.setValue = function (path, val) 
    {
        var i;
        for (i = 0; i < that.polyphony; i++) {
            that.factory.setValue(that.dsp_voices[i], that.pathTable[path], val);
        }
    };
    
    that.getValue = function (path) 
    {
        that.factory.getValue(that.dsp_voices[0], that.pathTable[path]);
    };
     
    that.json = function ()
    {
        return getJSONmydsp();
    }
    
    that.controls = function()
    {
        return that.inputs_items;
    }
    
    // JSON parsing
    that.parse_ui = function(ui) 
    {
        var i;
        for (i = 0; i < ui.length; i++) {
            that.parse_group(ui[i]);
        }
    }
    
    that.parse_group = function(group) 
    {
        if (group.items) {
            that.parse_items(group.items);
        }
    }
    
    that.parse_items = function(items) 
    {
        var i;
        for (i = 0; i < items.length; i++) {
            that.parse_item(items[i]);
        }
    }
    
    that.parse_item = function(item) 
    {
        if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
            that.parse_items(item.items);
        } else if (item.type === "hbargraph" || item.type === "vbargraph") {
            // Keep bargraph adresses
            that.ouputs_items.push(item.address);
        } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
            // Keep inputs adresses
            that.inputs_items.push(item.address);
        }
    }
      
    that.init = function ()
    {
        var i;
        
        // Get input / output counts
        that.numIn = that.getNumInputs();
        that.numOut = that.getNumOutputs();
        
        // Setup web audio context
        console.log("that.buffer_size %d", that.buffer_size);
        that.scriptProcessor = faust.context.createScriptProcessor(that.buffer_size, that.numIn, that.numOut);
        that.scriptProcessor.onaudioprocess = that.compute;
        
        if (that.numIn > 0) {
 
            that.ins = that.audio_heap_ptr_inputs; 
            
            // Assign to our array of pointer elements an array of 32bit floats, one for each channel. currently we assume pointers are 32bits
            for (i = 0; i < that.numIn; i++) { 
                // Assign memory at that.ins[i] to a new ptr value. Maybe there's an easier way, but this is clearer to me than any typed array magic beyond the presumably TypedArray HEAP32
                that.HEAP32[(that.ins >> 2) + i] = that.audio_heap_inputs + ((that.buffer_size * that.sample_size) * i);
            }
     
            // Prepare Ins/out buffer tables
            that.dspInChannnels = [];
            var dspInChans = that.HEAP32.subarray(that.ins >> 2, (that.ins + that.numIn * that.ptr_size) >> 2);
            for (i = 0; i < that.numIn; i++) {
                that.dspInChannnels[i] = that.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + that.buffer_size * that.ptr_size) >> 2);
            }
        }
        
        if (that.numOut > 0) {
 
            that.outs = that.audio_heap_ptr_outputs; 
            that.mixing = that.audio_heap_ptr_mixing; 
            
            // Assign to our array of pointer elements an array of 64bit floats, one for each channel. Currently we assume pointers are 32bits
            for (i = 0; i < that.numOut; i++) { 
                // Assign memory at that.outs[i] to a new ptr value. Maybe there's an easier way, but this is clearer to me than any typed array magic beyond the presumably TypedArray HEAP32
                that.HEAP32[(that.outs >> 2) + i] = that.audio_heap_outputs + ((that.buffer_size * that.sample_size) * i);
                that.HEAP32[(that.mixing >> 2) + i] = that.audio_heap_mixing + ((that.buffer_size * that.sample_size) * i);
            }
          
            that.dspOutChannnels = [];
            that.mixingChannnels = [];
            
            var dspOutChans = that.HEAP32.subarray(that.outs >> 2, (that.outs + that.numOut * that.ptr_size) >> 2);
            var mixingChans = that.HEAP32.subarray(that.outs >> 2, (that.mixing + that.numOut * that.ptr_size) >> 2);
            
            for (i = 0; i < that.numOut; i++) {
                that.dspOutChannnels[i] = that.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + that.buffer_size * that.ptr_size) >> 2);
                that.mixingChannnels[i] = that.HEAPF32.subarray(mixingChans[i] >> 2, (mixingChans[i] + that.buffer_size * that.ptr_size) >> 2);
            }
        }
        
         // bargraph
        that.parse_ui(JSON.parse(that.json()).ui);
        
        // init labels
        for (i = 0; i < that.inputs_items.length; i++) {
            if (that.inputs_items[i].endsWith("/gate")) {
                that.fGateLabel = that.pathTable[that.inputs_items[i]];
                console.log(that.fGateLabel);
            } else if (that.inputs_items[i].endsWith("/freq")) {
                that.fFreqLabel = that.pathTable[that.inputs_items[i]];
                console.log(that.fFreqLabel);
            } else if (that.inputs_items[i].endsWith("/gain")) {
                that.fGainLabel = that.pathTable[that.inputs_items[i]];
                console.log(that.fGainLabel);
            }
        }
        
        // Init DSP voices
        for (i = 0; i < that.polyphony; i++) {
            that.factory.init(that.dsp_voices[i], faust.context.sampleRate);
        }
    };
    
    that.init();
    return that;
}

