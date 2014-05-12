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

var DSP_constructor = Module.cwrap('DSP_constructor', 'number', 'number');
var DSP_destructor = Module.cwrap('DSP_destructor', null, ['number']);
var DSP_compute = Module.cwrap('DSP_compute', ['number'], ['number', 'number', 'number', 'number']);
var DSP_getNumInputs = Module.cwrap('DSP_getNumInputs', 'number', 'number');
var DSP_getNumOutputs = Module.cwrap('DSP_getNumOutputs', 'number', 'number');
var DSP_getJSON = Module.cwrap('DSP_getJSON', null, ['number','number']);
var DSP_setValue = Module.cwrap('DSP_setValue', null, ['number', 'number', 'number']);
var DSP_getValue = Module.cwrap('DSP_getValue', 'number', ['number', 'number']);

faust.DSP = function (context, vectorsize, handler) {
    var that = {};
    
    faust.context = context;
    that.vectorsize = vectorsize;
    that.handler = handler;
    
    // bargraph
    that.bargraph_timer = 5;
    that.bargraph_table = [];
    
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
    
    that.update_bargraph = function () 
    {
        if (that.bargraph_table.length > 0 && that.handler && that.bargraph_timer-- === 0) {
            that.bargraph_timer = 5;
            var i;
            for (i = 0; i < that.bargraph_table.length; i++) {
                var pathPtr = allocate(intArrayFromString(that.bargraph_table[i]), 'i8', ALLOC_STACK);
                that.handler(that.bargraph_table[i], DSP_getValue(that.ptr, pathPtr));
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
        DSP_compute(that.ptr, that.vectorsize, that.ins, that.outs);
       
        // Update bargraph
        that.update_bargraph();
        
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
    };
    
    // Connect to another node
    that.connect = function (node) 
    {
        if (node.scriptProcessor) {
            that.scriptProcessor.connect(node.scriptProcessor);
        } else {
            that.scriptProcessor.connect(node);
        }
    };
    
    // Bind to Web Audio
    that.start = function () 
    {
        that.scriptProcessor.connect(faust.context.destination);
    };
    
    that.stop = function () 
    {
        that.scriptProcessor.disconnect(faust.context.destination);
    };
    
    that.update = function (path, val) 
    {
        DSP_setValue(that.ptr, allocate(intArrayFromString(path), 'i8', ALLOC_STACK), val);
    };
    
    that.json = function ()
    {
        var jsonPtr = allocate(intArrayFromString(''), 'i8', ALLOC_STACK);
        DSP_getJSON(that.ptr, jsonPtr);
        return Pointer_stringify(jsonPtr);
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
            that.bargraph_table.push(item.address);
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
        that.scriptProcessor = faust.context.createScriptProcessor(that.vectorsize, that.numIn, that.numOut);
        that.scriptProcessor.onaudioprocess = that.compute;
        
        // TODO the below calls to malloc are not yet being freed, potential memory leak
        // allocate memory for input / output arrays
        that.ins = Module._malloc(that.ptrsize * that.numIn);
        
        // Assign to our array of pointer elements an array of 32bit floats, one for each channel. currently we assume pointers are 32bits
        for (i = 0; i < that.numIn; i++) { 
            // assign memory at that.ins[i] to a new ptr value. Maybe there's an easier way, but this is clearer to me than any typedarray magic beyond the presumably TypedArray HEAP32
            HEAP32[(that.ins >> 2) + i] = Module._malloc(that.vectorsize * that.samplesize); 
        }
        
        //ptrsize, change to eight or use Runtime.QUANTUM? or what?
        that.outs = Module._malloc(that.ptrsize * that.numOut); 
        
        // Assign to our array of pointer elements an array of 64bit floats, one for each channel. Currently we assume pointers are 32bits
        for (i = 0; i < that.numOut; i++) { 
            // Assign memory at that.outs[i] to a new ptr value. Maybe there's an easier way, but this is clearer to me than any typedarray magic beyond the presumably TypedArray HEAP32
            HEAP32[(that.outs >> 2) + i] = Module._malloc(that.vectorsize * that.samplesize);
        }
    
        // Prepare Ins/out buffer tables
        that.dspInChannnels = [];
        var dspInChans = HEAP32.subarray(that.ins >> 2, (that.ins + that.ins * that.ptrsize) >> 2);
        for (i = 0; i < that.numIn; i++) {
            that.dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + that.vectorsize * that.ptrsize) >> 2);
        }
       
        that.dspOutChannnels = [];
        var dspOutChans = HEAP32.subarray(that.outs >> 2, (that.outs + that.numOut * that.ptrsize) >> 2);
        for (i = 0; i < that.numOut; i++) {
            that.dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + that.vectorsize * that.ptrsize) >> 2);
        }
                                
        // bargraph
        that.parse_ui(JSON.parse(that.json()).ui);
    };
    
    that.init();
    return that;
};

}());