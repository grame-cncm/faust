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
 
 Additional code : GRAME 2014-2016
*/

'use strict';

var faust = faust || {};

Module.lengthBytesUTF8 = function(str) 
{
	var len=0;for(var i=0;i<str.length;++i){var u=str.charCodeAt(i);if(u>=55296&&u<=57343)u=65536+((u&1023)<<10)|str.charCodeAt(++i)&1023;if(u<=127){++len}else if(u<=2047){len+=2}else if(u<=65535){len+=3}else if(u<=2097151){len+=4}else if(u<=67108863){len+=5}else{len+=6}}return len;
}

// Polyphonic DSP : has to have 'freq', 'gate', 'gain' parameters to be possibly triggered with keyOn, keyOff events.

var DSP_poly_constructor = Module.cwrap('DSP_poly_constructor', 'number', ['number']);
var DSP_poly_destructor = Module.cwrap('DSP_poly_destructor', null, ['number']);
var DSP_poly_getSampleRate = Module.cwrap('DSP_poly_getSampleRate', 'number', ['number']);
var DSP_poly_init = Module.cwrap('DSP_poly_init', null, ['number','number']);
var DSP_poly_instanceInit = Module.cwrap('DSP_poly_instanceInit', null, ['number','number']);
var DSP_poly_instanceConstants = Module.cwrap('DSP_poly_instanceConstants', null, ['number','number']);
var DSP_poly_instanceResetUserInterface = Module.cwrap('DSP_poly_instanceResetUserInterface', null, ['number']);
var DSP_poly_instanceClear = Module.cwrap('DSP_poly_instanceClear', null, ['number']);
var DSP_poly_compute = Module.cwrap('DSP_poly_compute', null, ['number', 'number', 'number', 'number']);
var DSP_poly_getNumInputs = Module.cwrap('DSP_poly_getNumInputs', 'number', ['number']);
var DSP_poly_getNumOutputs = Module.cwrap('DSP_poly_getNumOutputs', 'number', ['number']);
var DSP_poly_getJSON = Module.cwrap('DSP_poly_getJSON', 'number', ['number']);
var DSP_poly_setParamValue = Module.cwrap('DSP_poly_setParamValue', null, ['number', 'number', 'number']);
var DSP_poly_getParamValue = Module.cwrap('DSP_poly_getParamValue', 'number', ['number', 'number']);
var DSP_poly_keyOn = Module.cwrap('DSP_poly_keyOn', null, ['number', 'number', 'number', 'number']);
var DSP_poly_keyOff = Module.cwrap('DSP_poly_keyOff', null, ['number', 'number', 'number', 'number']);
var DSP_poly_allNotesOff = Module.cwrap('DSP_poly_allNotesOff', null, ['number']);
var DSP_poly_ctrlChange = Module.cwrap('DSP_poly_ctrlChange', null, ['number', 'number', 'number', 'number']);
var DSP_poly_pitchWheel = Module.cwrap('DSP_poly_pitchWheel', null, ['number', 'number', 'number']);

faust.DSP_poly = function (context, buffer_size, max_polyphony, callback) {
  
    var handler = null;
    var ins, outs;
    var numIn, numOut;
    var compute_callback = callback;
    
    var scriptProcessor;
    
    var dspInChannnels = [];
    var dspOutChannnels = [];
    
    // Path string
    var path_ptr = Module._malloc(512);
    
    // bargraph
    var ouputs_timer = 5;
    var ouputs_items = [];
    
    // input items
    var inputs_items = [];
    
    var ptr = DSP_poly_constructor(max_polyphony);
    DSPP_poly_init(ptr, context.sampleRate);
     
    function update_outputs () 
    {
        if (ouputs_items.length > 0 && handler && ouputs_timer-- === 0) {
            ouputs_timer = 5;
            for (var i = 0; i < ouputs_items.length; i++) {
                Module.stringToUTF8(ouputs_items[i], path_ptr, Module.lengthBytesUTF8(ouputs_items[i]) + 1);
                handler(ouputs_items[i], DSP_poly_getParamValue(ptr, path_ptr));
            }
        }
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
    
    function compute (e) 
    {
        // Read inputs
        for (var i = 0; i < numIn; i++) {
            var input = e.inputBuffer.getChannelData(i);
            var dspInput = dspInChannnels[i];
            for (var j = 0; j < input.length; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // Possibly call an externally given callback (for instance to play a MIDIFile...)
        if (compute_callback) {
            compute_callback(buffer_size);
        }
        
        // Compute
        DSP_poly_compute(ptr, buffer_size, ins, outs);
        
        // Update bargraph
        update_outputs();
        
        // Write outputs
        for (var i = 0; i < numOut; i++) {
            var output = e.outputBuffer.getChannelData(i);
            var dspOutput = dspOutChannnels[i];
            for (var j = 0; j < output.length; j++) {
                output[j] = dspOutput[j];
            }
        }
    }
    
    function init ()
    {
        var i;
        var ptr_size = 4; //assuming pointer in emscripten are 32bits
        var sample_size = 4;
        
        // Get input / output counts
        numIn = DSP_poly_getNumInputs(ptr);
        numOut = DSP_poly_getNumOutputs(ptr);
        
        // Setup web audio context
        scriptProcessor = context.createScriptProcessor(buffer_size, numIn, numOut);
        scriptProcessor.onaudioprocess = compute;
        
        if (numIn > 0) {
            ins = Module._malloc(ptr_size * numIn);
            for (i = 0; i < numIn; i++) { 
                HEAP32[(ins >> 2) + i] = Module._malloc(buffer_size * sample_size); 
            }
            
            // Prepare Ins buffer tables
            var dspInChans = HEAP32.subarray(ins >> 2, (ins + numIn * ptr_size) >> 2);
            for (i = 0; i < numIn; i++) {
                dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sample_size) >> 2);
            }
        }
        
        if (numOut > 0) {
            outs = Module._malloc(ptr_size * numOut); 
            for (i = 0; i < numOut; i++) { 
                HEAP32[(outs >> 2) + i] = Module._malloc(buffer_size * sample_size);
            }
           
            // Prepare Outs buffer tables
            var dspOutChans = HEAP32.subarray(outs >> 2, (outs + numOut * ptr_size) >> 2);
            for (i = 0; i < numOut; i++) {
                dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sample_size) >> 2);
            }
        }
        
        // bargraph
        parse_ui(JSON.parse(Pointer_stringify(DSP_poly_getJSON(ptr))).ui);
    }
    
    init();
    
    // External API
    return {
    
        getNumInputs : function () 
        {
            return DSP_poly_getNumInputs(ptr);
        },
        
        getNumOutputs : function() 
        {
            return DSP_poly_getNumOutputs(ptr);
        },
        
        getSampleRate : function () 
        {
            return DSP_poly_getSampleRate(ptr);
        },
        
        init : function (sample_rate) 
        {
            DSP_init(ptr, sample_rate);
        },
        
        instanceInit : function (sample_rate) 
        {
            DSP_poly_instanceInit(ptr, sample_rate);
        },
        
        instanceConstants : function (sample_rate) 
        {
            DSP_poly_instanceConstants(ptr, sample_rate);
        },
        
        instanceResetUserInterface : function () 
        {
            DSP_poly_instanceResetUserInterface(ptr);
        },
        
        instanceClear : function () 
        {
            DSP_poly_instanceClear(ptr);
        },
        
        keyOn : function (channel, pitch, velocity)
        {
            DSP_poly_keyOn(ptr, channel, pitch, velocity);
        },
        
        keyOff : function (channel, pitch, velocity)
        {
            DSP_poly_keyOff(ptr, channel, pitch, velocity);
        },
        
        allNotesOff : function ()
        {
            DSP_poly_allNotesOff(ptr);
        },
        
        ctrlChange : function (channel, ctrl, value)
        {
            DSP_poly_ctrlChange(ptr, channel, ctrl, value);
        },
        
        pitchWheel : function (channel, pitchWheel)
        {
            DSP_poly_pitchWheel(ptr, channel, pitchWheel);
        },
        
        destroy : function ()
        {
            DSP_poly_destructor(ptr);
            
            if (numIn > 0) {
                for (var i = 0; i < numIn; i++) { 
                    Module._free(HEAP32[(ins >> 2) + i]); 
                }
                Module._free(ins);
            }
             
            if (numOut > 0) {
                for (var i = 0; i < numOut; i++) { 
                    Module._free(HEAP32[(outs >> 2) + i]);
                }
                Module._free(outs);
            }
            
            Module._free(path_ptr);
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
    
        setHandler: function (hd)
        {
            handler = hd;
        },
       
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
            Module.stringToUTF8(path, path_ptr, Module.lengthBytesUTF8(path) + 1);
            DSP_poly_setParamValue(ptr, path_ptr, val);
        },
        
        getParamValue : function (path) 
        {
            Module.stringToUTF8(path, path_ptr, Module.lengthBytesUTF8(path) + 1);
            return DSP_poly_getParamValue(ptr, path_ptr);
        },
                
        controls : function ()
        {
            return inputs_items;
        },
        
        json : function ()
        {
            return Pointer_stringify(DSP_poly_getJSON(ptr));
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

