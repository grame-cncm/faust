/*
 faust2webaudio
 
 Additional code: GRAME 2017
*/
 
'use strict';

var faust = faust || {};

faust.error_msg = null;
faust.getErrorMessage = function() { return faust.error_msg; };

faust.asm2wasm = { // special asm2wasm imports
    "fmod": function(x, y) {
        return x % y;
    },
    "log10": function(x) {
        return window.Math.log(x) / window.Math.log(10);
    },
    "remainder": function(x, y) {
        return x - window.Math.round(x/y) * y;
    }
}

faust.importObject = { imports: { print: arg => console.log(arg) } }
faust.importObject["global.Math"] = window.Math;
faust.importObject["asm2wasm"] = faust.asm2wasm;

// WebAssembly instance
faust.mydsp_instance = null;

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
    var i;
    for (i = 0; i < items.length; i++) {
        callback(items[i]);
    }
}

// Monophonic Faust DSP

class mydsp_processor extends AudioWorkletProcessor {
    
    static get parameterDescriptors () {
        
        // Analyse JSON to generate AudioParam parameters
        var json_object = JSON.parse(getJSONmydsp());
        var params = [];
        
        faust.parse_ui(json_object.ui,
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
        
        this.json_object = json_object;
        
        this.output_handler = null;
        this.ins = null;
        this.outs = null;
        
        this.dspInChannnels = [];
        this.dspOutChannnels = [];
        
        this.numIn = getNumInputsAux();
        this.numOut = getNumOutputsAux();
        
        // Memory allocator
        this.ptr_size = 4;
        this.sample_size = 4;
        
        this.factory = faust.mydsp_instance.exports;
        this.HEAP = faust.mydsp_instance.exports.memory.buffer;
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
        
        // DSP is placed first with index 0. Audio buffer start at the end of DSP.
        this.audio_heap_ptr = getSizemydsp();
        
        // Setup pointers offset
        this.audio_heap_ptr_inputs = this.audio_heap_ptr;
        this.audio_heap_ptr_outputs = this.audio_heap_ptr_inputs + (this.numIn * this.ptr_size);
        
        // Setup buffer offset
        this.audio_heap_inputs = this.audio_heap_ptr_outputs + (this.numOut * this.ptr_size);
        this.audio_heap_outputs = this.audio_heap_inputs + (this.numIn * 128 * this.sample_size);
        
        // Start of DSP memory : DSP is placed first with index 0
        this.dsp = 0;
        
        this.pathTable = getPathTablemydsp();
        
        // Allocate table for 'setParamValue'
        this.value_table = [];
        
        this.update_outputs = function ()
        {
            if (this.outputs_items.length > 0 && this.output_handler && this.outputs_timer-- === 0) {
                this.outputs_timer = 5;
                for (var i = 0; i < this.outputs_items.length; i++) {
                    this.output_handler(this.outputs_items[i], this.factory.getParamValue(this.dsp, this.pathTable[this.outputs_items[i]]));
                }
            }
        }
        
        this.initAux = function ()
        {
            var i;
            
            // Setup web audio context
            //console.log("buffer_size %d", buffer_size);
            this.onaudioprocess = this.compute;
            
            if (this.numIn > 0) {
                this.ins = this.audio_heap_ptr_inputs;
                for (i = 0; i < this.numIn; i++) {
                    this.HEAP32[(this.ins >> 2) + i] = this.audio_heap_inputs + ((128 * this.sample_size) * i);
                }
                
                // Prepare Ins buffer tables
                var dspInChans = this.HEAP32.subarray(this.ins >> 2, (this.ins + this.numIn * this.ptr_size) >> 2);
                for (i = 0; i < this.numIn; i++) {
                    this.dspInChannnels[i] = this.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + 128 * this.sample_size) >> 2);
                }
            }
            
            if (this.numOut > 0) {
                this.outs = this.audio_heap_ptr_outputs;
                for (i = 0; i < this.numOut; i++) {
                    this.HEAP32[(this.outs >> 2) + i] = this.audio_heap_outputs + ((128 * this.sample_size) * i);
                }
                
                // Prepare Out buffer tables
                var dspOutChans = this.HEAP32.subarray(this.outs >> 2, (this.outs + this.numOut * this.ptr_size) >> 2);
                for (i = 0; i < this.numOut; i++) {
                    this.dspOutChannnels[i] = this.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + 128 * this.sample_size) >> 2);
                }
            }
            
            // bargraph
            faust.parse_ui(this.json_object.ui,
                           function (item){
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
            
            // Init DSP
            this.factory.init(this.dsp, context.sampleRate);
            
            // Init 'value' table
            for (i = 0; i < this.inputs_items.length; i++) {
                var path = this.inputs_items[i];
                var values = new Float32Array(2);
                values[0] = values[1] = this.factory.getParamValue(this.dsp, this.pathTable[path]);
                this.value_table[path] = values;
            }
        }
   
        
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
        
        // Compute
        this.factory.compute(this.dsp, 128, this.ins, this.outs);
        
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
fetch('mydsp.wasm')
.then(dsp_file => dsp_file.arrayBuffer())
.then(dsp_bytes => WebAssembly.instantiate(dsp_bytes, faust.importObject))
.then(dsp_module => faust.mydsp_instance = dsp_module.instance; registerProcessor('mydsp', mydsp_processor);)
.catch(function() { faust.error_msg = "Faust DSP cannot be loaded or compiled"; callback(null); });



