
'use strict';

var faust = faust || {};

// Standard Faust DSP
faust.mydsp = function (instance, buffer_size, sample_rate) {

    var output_handler = null;
    var ins, outs;
    
    var dspInChannnels = [];
    var dspOutChannnels = [];
   
    // Keep JSON parsed object
    var json_object = JSON.parse(getJSONmydsp());
    
    console.log("Compiled with wasm backend, libfaust version : %s, options : %s", json_object.version, json_object.options);
      
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
     
    var factory = instance.exports;
    
    // JS side allocated wasm memory
    var HEAP = module_memory.buffer;
    
    var HEAP32 = new Int32Array(HEAP);
    var HEAPF32 = new Float32Array(HEAP);
  
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
            for (j = 0; j < buffer_size; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // Compute
        factory.compute(dsp, buffer_size, ins, outs);
       
        // Update bargraph
        update_outputs();
        
        // Write outputs
        for (i = 0; i < numOut; i++) {
            var output = outputs[i];
            var dspOutput = dspOutChannnels[i];
            for (j = 0; j < buffer_size; j++) {
                output[j] = dspOutput[j];
            }
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
                dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sample_size) >> 2);
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
                dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sample_size) >> 2);
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
            return parseInt(json_object.inputs);
        },
        
        getNumOutputs : function () 
        {
            return parseInt(json_object.outputs);
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
        
        getButtonsParams : function()
        {
            return buttons_items;
        },
        
        getJSON : function ()
        {
            return getJSONmydsp();
        },
        
        compute : function (inputs, outputs)
        {
            computeAux(inputs, outputs);
        },
        
        checkDefaults : function ()
		{
			for (var i = 0; i < default_values.length; i++) {
				if (default_values[i] !== factory.getParamValue(dsp, pathTable[inputs_items[i]])) return false;
			}
			return true;
		},
	
		initRandom : function ()
		{
			for (var i = 0; i < default_values.length; i++) {
                factory.setParamValue(dsp, pathTable[inputs_items[i]], 0.123456789);
			}
		}
    };
};

// Bench code
var buffer_size = 1024;
var sample_rate = 44100;
var inputs = [];
var outputs = [];
var run = -1;
var bench_num = 3;

var NV = 4096;
var input_index = 0;
var output_index = 0;

// JS side allocated wasm memory
var module_memory = new WebAssembly.Memory({ initial: 512 });

var createBuffers = function(ins, outs)
{
    console.log("Allocate ins/outs buffers");
	for (var i = 0; i < ins; i++) {
		var input = new Float32Array(buffer_size * NV);
		// Init input with noise
		for (var j = 0; j < buffer_size * NV; j++) {
			input[j] = (Math.random() * 2) - 1.0;
		}
		inputs.push(input);
	}
	for (var i = 0; i < outs; i++) {
		outputs.push(new Float32Array(buffer_size * NV));
	}
}

function benchOne(dsp, run)
{
   var time1 = new Date().getTime();

    // Bench DSP
    while (run-- > 0) {
		var ins_slice = [];
		var outs_slice = [];
		for (var i = 0; i < dsp.getNumInputs(); i++) {
			ins_slice.push(inputs[i].subarray(input_index * buffer_size, (input_index + 1) * buffer_size));
			input_index = (1 + input_index) % NV;
		}
		for (var i = 0; i < dsp.getNumOutputs(); i++) {
			outs_slice.push(outputs[i].subarray(output_index * buffer_size, (output_index + 1) * buffer_size));
			output_index = (1 + output_index) % NV;
		}
		dsp.compute(ins_slice, outs_slice);
    }

    var time2 = new Date().getTime();
    return (time2 - time1);
}

function megapersec(frames, chans, dur)
{
	// Use 4 bytes for samples
	return (frames * chans * 4) / (1024 * 1024 * dur);
}

function bench(instance, display_handler)
{
    // Creates DSP
    var DSP = faust.mydsp(instance, buffer_size, sample_rate);
 
    // First call : create buffers and estimate a proper 'run' value
    if (run === -1) {
        // Setup buffers
        createBuffers(DSP.getNumInputs(), DSP.getNumOutputs(), buffer_size);
        // Setup a good value for 'run'
        var delta = benchOne(DSP, 1000);
        console.log("Delta : " + delta);
        run = (1000 / delta) * 5000;
    }
    
    var mega_results = [];
    var cpu_results = [];

	for (var i = 0; i < bench_num; i++) {
	
 		// Do the bench and keep result
		var duration = benchOne(DSP, run);
		var cpu = (duration * sample_rate) / (run * buffer_size * 10);
		var mega = megapersec(buffer_size, (DSP.getNumInputs() + DSP.getNumOutputs()), duration/run/1000);
		
		mega_results.push(mega);
		cpu_results.push(cpu);
    	
		console.log("MBytes/sec : " + mega.toFixed(2));
		console.log("DSP CPU % : " + cpu.toFixed(2));
    }
    
    // Compute mean 
    var mega_sum = 0.;
    var cpu_sum = 0.;
    for (var i = 0; i < bench_num; i++) {
    	mega_sum += mega_results[i];
    	cpu_sum += cpu_results[i];
    }
    
    var mega_mean = mega_sum/bench_num;
    var cpu_mean = cpu_sum/bench_num;
    
	console.log("MBytes/sec mean: " + mega_mean.toFixed(2));
	console.log("DSP CPU mean % : " + cpu_mean.toFixed(2));

    if (display_handler) {
    	display_handler(mega_mean, cpu_mean);
    }
}

faust.createmydsp = function(display_handler)
{
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
            
            memory: module_memory,
            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };
    
    if (typeof window !== "undefined") {
        fetch('mydsp.wasm')
        .then(dsp_file => dsp_file.arrayBuffer())
        .then(dsp_bytes => WebAssembly.instantiate(dsp_bytes, importObject))
        .then(dsp_module => bench(dsp_module.instance, display_handler))
        .catch(function(error) { console.log(error); faust.error_msg = "Faust mydsp cannot be loaded or compiled"; });
    } else {
        var dsp_bytes = os.file.readFile('mydsp.wasm', 'binary');
        WebAssembly.instantiate(dsp_bytes, importObject)
        .then(dsp_module => bench(dsp_module.instance, display_handler))
        .catch(function(error) { console.log(error); faust.error_msg = "Faust karplus cannot be loaded or compiled"; });
    }
}

// Startup
if (typeof window !== "undefined") {
    startBenchmark = function() {
        faust.createmydsp(function(v1, v2) {
            document.getElementById("megapersec").value = v1.toFixed(2);
            document.getElementById("cpu").value = v2.toFixed(2);
        });
    }
} else {
    startBenchmark = function() {
        faust.createmydsp(function(v1, v2) {
            console.log('MBits/s', v1.toFixed(2));
            console.log('CPU', v2.toFixed(2));
        });
    }();
}

