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

// Standard Faust DSP

faust.mydsp = function (context, buffer_size) {

    var that = {};
    
    faust.context = context;
 
    that.buffer_size = buffer_size;
    that.handler = null;
   
    // JSON parsing
    that.json = function ()
    {
        return getJSONmydsp();
    }
    
    // Keep JSON parsed object
    that.jon_object = JSON.parse(that.json());
    
    that.getNumInputs = function () 
    {
        return (that.jon_object.inputs != undefined) ? that.jon_object.inputs : 0;
    };
    
    that.getNumOutputs = function () 
    {
        return (that.jon_object.outputs != undefined) ? that.jon_object.outputs : 0;
    };
     
    // Memory allocator
    that.ptr_size = 4; 
    that.sample_size = 4;
    that.maxBufferSize = 8192;
    
    that.pow2limit = function(x)
    {
        var n = 2;
        while (n < x) { n = 2 * n; }
        return (n < 4096) ? 4096 : n;
    }
     
    var memory_size = that.pow2limit(getSizemydsp() + (that.getNumInputs() + that.getNumOutputs()) * (that.ptr_size + that.maxBufferSize * that.sample_size));
  
    that.HEAP = new ArrayBuffer(memory_size);
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
    that.audio_heap_ptr_outputs = that.audio_heap_ptr_inputs + (that.getNumInputs() * that.ptr_size);
     
    // Setup buffer offset
    that.audio_heap_inputs = that.audio_heap_ptr_outputs + (that.getNumOutputs() * that.ptr_size);
    that.audio_heap_outputs = that.audio_heap_inputs + (that.getNumInputs() * that.buffer_size * that.sample_size);
    
    // Setup DSP offset
    that.dsp_start = that.audio_heap_outputs + (that.getNumOutputs() * that.buffer_size * that.sample_size);
     
    // Start of DSP memory
    that.dsp = that.dsp_start;
 
    // ASM module
    that.factory = mydspFactory(window, null, that.HEAP);
    console.log(that.factory);
 
    that.pathTable = getPathTablemydsp();
       
    that.update_outputs = function () 
    {
        if (that.ouputs_items.length > 0 && that.handler && that.ouputs_timer-- === 0) {
            that.ouputs_timer = 5;
            var i;
            for (i = 0; i < that.ouputs_items.length; i++) {
                that.handler(that.ouputs_items[i], that.factory.getValue(that.dsp, that.pathTable[that.ouputs_items[i]]));
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
        
        // Compute
        that.factory.compute(that.dsp, that.buffer_size, that.ins, that.outs);
       
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
        that.factory.setValue(that.dsp, that.pathTable[path], val);
    };
    
    that.getValue = function (path) 
    {
        that.factory.getValue(that.dsp, that.pathTable[path]);
    };
    
    that.controls = function()
    {
        return that.inputs_items;
    }
    
    // JSON parsing
    that.parse_ui = function(ui) 
    {
        var i;
        for (i = 0; i < ui.length; i++) {
            console.log(ui[i]);
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
            for (i = 0; i < that.numIn; i++) { 
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
            for (i = 0; i < that.numOut; i++) { 
                that.HEAP32[(that.outs >> 2) + i] = that.audio_heap_outputs + ((that.buffer_size * that.sample_size) * i);
            }
          
            that.dspOutChannnels = [];
            var dspOutChans = that.HEAP32.subarray(that.outs >> 2, (that.outs + that.numOut * that.ptr_size) >> 2);
            for (i = 0; i < that.numOut; i++) {
                that.dspOutChannnels[i] = that.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + that.buffer_size * that.ptr_size) >> 2);
            }
        }
                                
        // bargraph
        that.parse_ui(that.jon_object.ui);
        
        // Init DSP
        that.factory.init(that.dsp, faust.context.sampleRate);
    };
    
    that.init();
    return that;
}

