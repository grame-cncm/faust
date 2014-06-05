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

/*global webkitAudioContext, Module, HEAPF32, HEAP32, Pointer_stringify, ALLOC_STACK, intArrayFromString, allocate*/

var faust = faust || {};

// Shim AudioContext on webkit
window.AudioContext = window.AudioContext || window.webkitAudioContext || undefined;

/*
function mydsp() {
	
	this.iRec0 = new Int32Array(2);
	this.fVslider0;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2009");
		m.declare("license", "BSD");
		m.declare("name", "Noise");
		m.declare("version", "1.1");
	}
    
	this.getNumInputs = function() {
		return 0;
		
	}
	this.getNumOutputs = function() {
		return 1;
		
	}
	this.getInputRate = function(channel) {
		var rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
                
		}
		return rate;
		
	}
	this.getOutputRate = function(channel) {
		var rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
                
		}
		return rate;
		
	}
	
	this.classInit = function(samplingFreq) {
		
	}
	
	this.instanceInit = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fVslider0 = 0;
		for (var i = 0; (i < 2); i = (i + 1)) {
			this.iRec0[i] = 0;
			
		}
		
	}
	
	this.init = function(samplingFreq) {
		this.classInit(samplingFreq);
		this.instanceInit(samplingFreq);
	}
	
	this.buildUserInterface = function(ui_interface) {
		ui_interface.openVerticalBox("noise");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.addVerticalSlider("Volume", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var fSlow0 = (4.65661e-10 * this.fVslider0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec0[0] = (12345 + (1103515245 * this.iRec0[1]));
			output0[i] = (fSlow0 * this.iRec0[0]);
			this.iRec0[1] = this.iRec0[0];
			
		}
		
	}
	
}
*/

(function () {
 
    var asmjs_dsp_factory = Module.cwrap('asmjs_dsp_factory', null, ['number']);
 
    // Standard Faust DSP

    faust.DSP = function (context, buffer_size, handler) {
        var that = {};
        
        faust.context = context;
        that.buffer_size = buffer_size;
        that.handler = handler;
        
        // bargraph
        that.ouputs_timer = 5;
        that.ouputs_items = [];
        
        // input items
        that.inputs_items = [];
 
        //var factoryPtr = allocate(intArrayFromString(''), 'i8', ALLOC_STACK);
        //asmjs_dsp_factory(factoryPtr);
        //that.factory = Pointer_stringify(factoryPtr);
 
        that.factory = Pointer_stringify(asmjs_dsp_factory("process = +;"));
 
        console.log(that.factory);
    
        that.ptr = eval(that.factory);
         
        // Bind to C++ Member Functions
        
        that.getNumInputs = function () 
        {
            return that.ptr.getNumInputs();
        };
        
        that.getNumOutputs = function () 
        {
            return that.ptr.getNumOutputs();
        };
        
        
        that.update_outputs = function () 
        {
            /*
            if (that.ouputs_items.length > 0 && that.handler && that.ouputs_timer-- === 0) {
                that.ouputs_timer = 5;
                var i;
                for (i = 0; i < that.ouputs_items.length; i++) {
                    var pathPtr = allocate(intArrayFromString(that.ouputs_items[i]), 'i8', ALLOC_STACK);
                    that.handler(that.ouputs_items[i], DSP_getValue(that.ptr, pathPtr));
                }
            }
            */
        };
        
 
        that.compute = function (e) 
        {
            var i;
 
            var inputs = [];
            for (i = 0; i < that.getNumInputs(); i++) {
                inputs[i] = e.inputBuffer.getChannelData(i);
            }
 
             var outputs = [];
             for (i = 0; i < that.getNumOutputs(); i++) {
                outputs[i] = e.outputBuffer.getChannelData(i);
             }
 
            // Compute
            that.ptr.compute(that.buffer_size, inputs, outputs);
           
            // Update bargraph
            that.update_outputs();
        };
        
        that.destroy = function ()
        {
            //DSP_destructor(that.ptr);
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
        
        // Bind to Web Audio, external API
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
            //DSP_setValue(that.ptr, allocate(intArrayFromString(path), 'i8', ALLOC_STACK), val);
        };
        
        that.json = function ()
        {
            /*
            var jsonPtr = allocate(intArrayFromString(''), 'i8', ALLOC_STACK);
            DSP_getJSON(that.ptr, jsonPtr);
            return Pointer_stringify(jsonPtr);
            */
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
            // Setup web audio context
            console.log("that.buffer_size %d", that.buffer_size);
            that.scriptProcessor = faust.context.createScriptProcessor(that.buffer_size, that.getNumInputs(), that.getNumOutputs());
            that.scriptProcessor.onaudioprocess = that.compute;
                                    
            // bargraph
            //that.parse_ui(JSON.parse(that.json()).ui);
 
            that.ptr.init(faust.context.sampleRate);
        };
        
        that.init();
        
        return that;
    };

}());
