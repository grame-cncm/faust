
'use strict';

var faust = faust || {};

// Standard Faust DSP
faust.mydsp = function (context, instance, buffer_size, sample_rate) {

    var output_handler = null;
    var ins, outs;
    
    var dspInChannnels = [];
    var dspOutChannnels = [];
   
    // Keep JSON parsed object
    var json_object = JSON.parse(getJSONmydsp());
    
    var numIn = parseInt(json_object.inputs);
    var numOut = parseInt(json_object.outputs);
     
    // Memory allocator
    var ptr_size = 4;
    var sample_size = 4;  // float
    
    function pow2limit (x)
    {
        var n = 65536; // Minimum = 64 kB
        while (n < x) { n = 2 * n; }
        return n;
    }
     
    var memory_size = pow2limit(parseInt(json_object.size) + (numIn + numOut) * (ptr_size + (buffer_size * sample_size)));
   
    var factory = instance.exports;
    
    var HEAP = instance.exports.memory.buffer;
    var HEAP32 = new Int32Array(HEAP);
    var HEAPF = new Float32Array(HEAP);
  
    // bargraph
    var outputs_timer = 5;
    var outputs_items = [];
     
    // input items
    var inputs_items = [];
    
    // buttons items
    var buttons_items = [];
    
    // default values
    var default_values = [];
    
    // DSP is placed first with index 0. Audio buffer start at the end of DSP.
    var audio_heap_ptr = parseInt(json_object.size);
  
    // Setup pointers offset
    var audio_heap_ptr_inputs = audio_heap_ptr; 
    var audio_heap_ptr_outputs = audio_heap_ptr_inputs + (numIn * ptr_size);
     
    // Setup buffer offset
    var audio_heap_inputs = audio_heap_ptr_outputs + (numOut * ptr_size);
    var audio_heap_outputs = audio_heap_inputs + (numIn * buffer_size * sample_size);
    
    // Start of DSP memory : DSP is placed first with index 0
    var dsp = 0;
    
    var pathTable = [];
    
    function update_outputs () 
    {
        if (outputs_items.length > 0 && output_handler && outputs_timer-- === 0) {
            outputs_timer = 5;
            for (var i = 0; i < outputs_items.length; i++) {
                output_handler(outputs_items[i], factory.getParamValue(dsp, pathTable[outputs_items[i]]));
            }
        }
    }
    
    function computeAux (inputs, outputs)
    {
        var i, j;
        
        // Read inputs
        for (i = 0; i < numIn; i++) {
            var input = inputs[i];
            var dspInput = dspInChannnels[i];
            dspInput.set(input);
        }
        
        // Compute
        factory.compute(dsp, buffer_size, ins, outs);
       
        // Update bargraph
        update_outputs();
        
        // Write outputs
        for (i = 0; i < numOut; i++) {
            var output = outputs[i];
            var dspOutput = dspOutChannnels[i];
            output.set(dspOutput);
        }
    };
         
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
        var i;
        for (i = 0; i < items.length; i++) {
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
            outputs_items.push(item.address);
            pathTable[item.address] = parseInt(item.index);
        } else if (item.type === "vslider" 
        	|| item.type === "hslider" 
        	|| item.type === "button" 
        	|| item.type === "checkbox" 
        	|| item.type === "nentry") {
            // Keep inputs adresses
            inputs_items.push(item.address);
            pathTable[item.address] = parseInt(item.index);
            if (item.type === "button") {
                buttons_items.push(item.address);
                default_values.push(0);
            } else if (item.type === "checkbox") {
            	default_values.push(0);
            } else {
                default_values.push(parseFloat(item.init));
            }
        }
    }
      
    function init ()
    {
        var i;
        
        if (numIn > 0) {
            ins = audio_heap_ptr_inputs; 
            for (i = 0; i < numIn; i++) { 
                HEAP32[(ins >> 2) + i] = audio_heap_inputs + ((buffer_size * sample_size) * i);
           }
     
            // Prepare Ins buffer tables
            var dspInChans = HEAP32.subarray(ins >> 2, (ins + numIn * ptr_size) >> 2);
            for (i = 0; i < numIn; i++) {
                dspInChannnels[i] = HEAPF.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sample_size) >> 2);
            }
        }
        
        if (numOut > 0) {
            outs = audio_heap_ptr_outputs; 
            for (i = 0; i < numOut; i++) { 
                HEAP32[(outs >> 2) + i] = audio_heap_outputs + ((buffer_size * sample_size) * i);
            }
          
            // Prepare Out buffer tables
            var dspOutChans = HEAP32.subarray(outs >> 2, (outs + numOut * ptr_size) >> 2);
            for (i = 0; i < numOut; i++) {
                dspOutChannnels[i] = HEAPF.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sample_size) >> 2);
            }
        }
                                
        // bargraph
        parse_ui(json_object.ui);
        
        // Init DSP
        factory.init(dsp, sample_rate);
    }
     
    init();
    
    // External API
    return {
     	
        getSampleRate : function () 
        {
            return factory.getSampleRate(dsp);
        },
        
        getNumInputs : function () 
        {
            return numIn;
        },
        
        getNumOutputs : function () 
        {
            return numOut;
        },
               
        init : function (sample_rate) 
        {
            factory.init(dsp, sample_rate);
        },
        
        instanceInit : function (sample_rate) 
        {
            factory.instanceInit(dsp, sample_rate);
        },
        
        instanceConstants : function (sample_rate) 
        {
            factory.instanceConstants(dsp, sample_rate);
        },
        
        instanceResetUserInterface : function () 
        {
            factory.instanceResetUserInterface(dsp);
        },
        
        instanceClear : function () 
        {
            factory.instanceClear(dsp);
        },
        
        setOutputParamHandler : function (handler)
        {
            output_handler = handler;
        },
        
        getOutputParamHandler : function ()
        {
            return output_handler;
        },
        
        setParamValue : function (path, val)
        {
            factory.setParamValue(dsp, pathTable[path], val);
        },

        getParamValue : function (path) 
        {
            return factory.getParamValue(dsp, pathTable[path]);
        },
        
        getParams : function()
        {
            return inputs_items;
        },
        
        getJSON : function ()
        {
            return getJSONmydsp();
        },
        
        compute : function (inputs, outputs)
        {
            computeAux(inputs, outputs);
        }
        
    };
};

// Helper functions

var create = function(ins, outs, buffer_size) 
{
    for (var i = 0; i < ins; i++) {
        inputs.push(new Float32Array(buffer_size));
    }
    for (var i = 0; i < outs; i++) {
        outputs.push(new Float32Array(buffer_size));
    }
}

function toUint8Array(buf)
{
    var res = new Uint8Array(buf.length);
    for (var i = 0; i < buf.length; ++i) {
        res[i] = buf[i];
    }
    return res;
}

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
        _acosh: Math.acosh,
        _asinh: Math.asinh,
        _atanh: Math.atanh,
        _cosh: Math.cosh,
        _sinh: Math.sinh,
        _tanh: Math.tanh,
           
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
        _acosh: Math.acosh,
        _asinh: Math.asinh,
        _atanh: Math.atanh,
        _cosh: Math.cosh,
        _sinh: Math.sinh,
        _tanh: Math.tanh,
        
        table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
    }
};

/* 
Testing code : 

	faust -lang wasm foo.dsp -o foo.wasm
	node /usr/local/share/faust/webaudio/wasm-standalone-node-wrapper.js foo.js foo.wasm 
	
*/

var fs = require('fs');

var buffer_size = 64;
var sample_rate = 44100;
var inputs = [];
var outputs = [];
var nbsamples = 4096;

function testDSP(instance, buffer_size)
{
	// Creates DSP and buffers
    var DSP = faust.mydsp(null, instance, buffer_size, sample_rate);
    create(DSP.getNumInputs(), DSP.getNumOutputs(), buffer_size);

    console.log("number_of_inputs : ", DSP.getNumInputs());
    console.log("number_of_outputs : ", DSP.getNumOutputs());
    console.log("JSON : ", DSP.getJSON());
 
    // Init DSP
    DSP.init(sample_rate);

    // Compute some samples
    while (nbsamples > 0) {
       	DSP.compute(inputs, outputs);
        nbsamples -= buffer_size;
    }
}

// Read .js file and dynamically eval 'getJSONmydsp' function
var response1 = fs.readFileSync(process.argv[2], 'utf8');
var getJSONmydsp = eval('(' + response1 + ')');

// Read .wasm file
var response2 = toUint8Array(fs.readFileSync(process.argv[3]));
var bytes = response2.buffer;

var res = WebAssembly.compile(bytes)
        .then(m => { WebAssembly.instantiate(m, importObject)
        .then(instance => { testDSP(instance, buffer_size); })});

