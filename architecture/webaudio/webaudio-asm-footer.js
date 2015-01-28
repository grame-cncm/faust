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

var DSP_constructor = Module.cwrap('DSP_constructor', 'number', ['number']);
var DSP_destructor = Module.cwrap('DSP_destructor', null, ['number']);
var DSP_compute = Module.cwrap('DSP_compute', null, ['number', 'number', 'number', 'number']);
var DSP_getNumInputs = Module.cwrap('DSP_getNumInputs', 'number', ['number']);
var DSP_getNumOutputs = Module.cwrap('DSP_getNumOutputs', 'number', ['number']);
var DSP_getJSON = Module.cwrap('DSP_getJSON', 'number', ['number']);
var DSP_setValue = Module.cwrap('DSP_setValue', null, ['number', 'number', 'number']);
var DSP_getValue = Module.cwrap('DSP_getValue', 'number', ['number', 'number']);

// Standard Faust DSP

faust.DSP = function (context, buffer_size) {
    var that = {};
    
    faust.context = context;
    that.buffer_size = buffer_size;
    that.handler = null;
    
    // Path string
    that.pathPtr = Module._malloc(512);
    
    // bargraph
    that.ouputs_timer = 5;
    that.ouputs_items = [];
    
    // input items
    that.inputs_items = [];
    
    that.ptr = DSP_constructor(faust.context.sampleRate);
    
    // Bind to C++ Member Functions
    
    that.getNumInputs = function () 
    {
        return DSP_getNumInputs(that.ptr);
    };
    
    that.getNumOutputs = function () 
    {
        return DSP_getNumOutputs(that.ptr);
    };
    
    that.update_outputs = function () 
    {
        if (that.ouputs_items.length > 0 && that.handler && that.ouputs_timer-- === 0) {
            that.ouputs_timer = 5;
            var i;
            for (i = 0; i < that.ouputs_items.length; i++) {
                Module.writeStringToMemory(that.ouputs_items[i], that.pathPtr);
                that.handler(that.ouputs_items[i], DSP_getValue(that.ptr, that.pathPtr));
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
        DSP_compute(that.ptr, that.buffer_size, that.ins, that.outs);
       
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
        DSP_destructor(that.ptr);
        
        if (that.numIn > 0) {
            for (i = 0; i < that.numIn; i++) { 
                Module._free(HEAP32[(that.ins >> 2) + i]); 
            }
            Module._free(that.ins);
        }
         
        if (that.numOut > 0) {
            for (i = 0; i < that.numOut; i++) { 
                Module._free(HEAP32[(that.outs >> 2) + i]);
            }
            Module._free(that.outs);
        }
        
        Module._free(that.pathPtr);
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
        Module.writeStringToMemory(path, that.pathPtr);
        DSP_setValue(that.ptr, that.pathPtr, val);
    };
    
    that.getValue = function (path) 
    {
        Module.writeStringToMemory(path, that.pathPtr);
        return DSP_getValue(that.ptr, that.pathPtr);
    };
     
    that.json = function ()
    {
        return Pointer_stringify(DSP_getJSON(that.ptr));
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
        that.ptrsize = 4; //assuming pointer in emscripten are 32bits
        that.samplesize = 4;
        
        // Get input / output counts
        that.numIn = that.getNumInputs();
        that.numOut = that.getNumOutputs();
        
        // Setup web audio context
        that.scriptProcessor = faust.context.createScriptProcessor(that.buffer_size, that.numIn, that.numOut);
        that.scriptProcessor.onaudioprocess = that.compute;
        
        if (that.numIn > 0) {
            that.ins = Module._malloc(that.ptrsize * that.numIn);
            for (i = 0; i < that.numIn; i++) { 
                HEAP32[(that.ins >> 2) + i] = Module._malloc(that.buffer_size * that.samplesize); 
            }
            
            // Prepare Ins buffer tables
            that.dspInChannnels = [];
            var dspInChans = HEAP32.subarray(that.ins >> 2, (that.ins + that.numIn * that.ptrsize) >> 2);
            for (i = 0; i < that.numIn; i++) {
                that.dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + that.buffer_size * that.ptrsize) >> 2);
            }
        }
        
        if (that.numOut > 0) {
        
            that.outs = Module._malloc(that.ptrsize * that.numOut); 
            for (i = 0; i < that.numOut; i++) { 
                HEAP32[(that.outs >> 2) + i] = Module._malloc(that.buffer_size * that.samplesize);
            }
           
            // Prepare Outs buffer tables
            that.dspOutChannnels = [];
            var dspOutChans = HEAP32.subarray(that.outs >> 2, (that.outs + that.numOut * that.ptrsize) >> 2);
            for (i = 0; i < that.numOut; i++) {
                that.dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + that.buffer_size * that.ptrsize) >> 2);
            }
        }
                                
        // bargraph
        that.parse_ui(JSON.parse(that.json()).ui);
    };
    
    that.init();
    return that;
};

