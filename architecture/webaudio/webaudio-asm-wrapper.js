/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/*  SHA-1 implementation in JavaScript | (c) Chris Veness 2002-2013 | www.movable-type.co.uk      */
/*   - see http://csrc.nist.gov/groups/ST/toolkit/secure_hashing.html                             */
/*         http://csrc.nist.gov/groups/ST/toolkit/examples.html                                   */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

var Sha1 = {};  // Sha1 namespace

/**
 * Generates SHA-1 hash of string
 *
 * @param {String} msg                String to be hashed
 * @param {Boolean} [utf8encode=true] Encode msg as UTF-8 before generating hash
 * @returns {String}                  Hash of msg as hex character string
 */
Sha1.hash = function(msg, utf8encode) {
    utf8encode =  (typeof utf8encode == 'undefined') ? true : utf8encode;
    
    // convert string to UTF-8, as SHA only deals with byte-streams
    if (utf8encode) msg = Utf8.encode(msg);
    
    // constants [§4.2.1]
    var K = [0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6];
    
    // PREPROCESSING 
    
    msg += String.fromCharCode(0x80);  // add trailing '1' bit (+ 0's padding) to string [§5.1.1]
    
    // convert string msg into 512-bit/16-integer blocks arrays of ints [§5.2.1]
    var l = msg.length/4 + 2;  // length (in 32-bit integers) of msg + ‘1’ + appended length
    var N = Math.ceil(l/16);   // number of 16-integer-blocks required to hold 'l' ints
    var M = new Array(N);
    
    for (var i=0; i<N; i++) {
        M[i] = new Array(16);
        for (var j=0; j<16; j++) {  // encode 4 chars per integer, big-endian encoding
            M[i][j] = (msg.charCodeAt(i*64+j*4)<<24) | (msg.charCodeAt(i*64+j*4+1)<<16) | 
            (msg.charCodeAt(i*64+j*4+2)<<8) | (msg.charCodeAt(i*64+j*4+3));
        } // note running off the end of msg is ok 'cos bitwise ops on NaN return 0
    }
    // add length (in bits) into final pair of 32-bit integers (big-endian) [§5.1.1]
    // note: most significant word would be (len-1)*8 >>> 32, but since JS converts
    // bitwise-op args to 32 bits, we need to simulate this by arithmetic operators
    M[N-1][14] = ((msg.length-1)*8) / Math.pow(2, 32); M[N-1][14] = Math.floor(M[N-1][14])
    M[N-1][15] = ((msg.length-1)*8) & 0xffffffff;
    
    // set initial hash value [§5.3.1]
    var H0 = 0x67452301;
    var H1 = 0xefcdab89;
    var H2 = 0x98badcfe;
    var H3 = 0x10325476;
    var H4 = 0xc3d2e1f0;
    
    // HASH COMPUTATION [§6.1.2]
    
    var W = new Array(80); var a, b, c, d, e;
    for (var i=0; i<N; i++) {
        
        // 1 - prepare message schedule 'W'
        for (var t=0;  t<16; t++) W[t] = M[i][t];
        for (var t=16; t<80; t++) W[t] = Sha1.ROTL(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);
        
        // 2 - initialise five working variables a, b, c, d, e with previous hash value
        a = H0; b = H1; c = H2; d = H3; e = H4;
        
        // 3 - main loop
        for (var t=0; t<80; t++) {
            var s = Math.floor(t/20); // seq for blocks of 'f' functions and 'K' constants
            var T = (Sha1.ROTL(a,5) + Sha1.f(s,b,c,d) + e + K[s] + W[t]) & 0xffffffff;
            e = d;
            d = c;
            c = Sha1.ROTL(b, 30);
            b = a;
            a = T;
        }
        
        // 4 - compute the new intermediate hash value
        H0 = (H0+a) & 0xffffffff;  // note 'addition modulo 2^32'
        H1 = (H1+b) & 0xffffffff; 
        H2 = (H2+c) & 0xffffffff; 
        H3 = (H3+d) & 0xffffffff; 
        H4 = (H4+e) & 0xffffffff;
    }
    
    return Sha1.toHexStr(H0) + Sha1.toHexStr(H1) + 
    Sha1.toHexStr(H2) + Sha1.toHexStr(H3) + Sha1.toHexStr(H4);
}

//
// function 'f' [§4.1.1]
//
Sha1.f = function(s, x, y, z)  {
    switch (s) {
        case 0: return (x & y) ^ (~x & z);           // Ch()
        case 1: return x ^ y ^ z;                    // Parity()
        case 2: return (x & y) ^ (x & z) ^ (y & z);  // Maj()
        case 3: return x ^ y ^ z;                    // Parity()
    }
}

//
// rotate left (circular left shift) value x by n positions [§3.2.5]
//
Sha1.ROTL = function(x, n) {
    return (x<<n) | (x>>>(32-n));
}

//
// hexadecimal representation of a number 
//   (note toString(16) is implementation-dependant, and  
//   in IE returns signed numbers when used on full words)
//
Sha1.toHexStr = function(n) {
    var s="", v;
    for (var i=7; i>=0; i--) { v = (n>>>(i*4)) & 0xf; s += v.toString(16); }
    return s;
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/*  Utf8 class: encode / decode between multi-byte Unicode characters and UTF-8 multiple          */
/*              single-byte character encoding (c) Chris Veness 2002-2013                         */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

var Utf8 = {};  // Utf8 namespace

/**
 * Encode multi-byte Unicode string into utf-8 multiple single-byte characters 
 * (BMP / basic multilingual plane only)
 *
 * Chars in range U+0080 - U+07FF are encoded in 2 chars, U+0800 - U+FFFF in 3 chars
 *
 * @param {String} strUni Unicode string to be encoded as UTF-8
 * @returns {String} encoded string
 */
Utf8.encode = function(strUni) {
    // use regular expressions & String.replace callback function for better efficiency 
    // than procedural approaches
    var strUtf = strUni.replace(
                                /[\u0080-\u07ff]/g,  // U+0080 - U+07FF => 2 bytes 110yyyyy, 10zzzzzz
                                function(c) { 
                                var cc = c.charCodeAt(0);
                                return String.fromCharCode(0xc0 | cc>>6, 0x80 | cc&0x3f); }
                                );
    strUtf = strUtf.replace(
                            /[\u0800-\uffff]/g,  // U+0800 - U+FFFF => 3 bytes 1110xxxx, 10yyyyyy, 10zzzzzz
                            function(c) { 
                            var cc = c.charCodeAt(0); 
                            return String.fromCharCode(0xe0 | cc>>12, 0x80 | cc>>6&0x3F, 0x80 | cc&0x3f); }
                            );
    return strUtf;
}

/**
 * Decode utf-8 encoded string back into multi-byte Unicode characters
 *
 * @param {String} strUtf UTF-8 string to be decoded back to Unicode
 * @returns {String} decoded string
 */
Utf8.decode = function(strUtf) {
    // note: decode 3-byte chars first as decoded 2-byte strings could appear to be 3-byte char!
    var strUni = strUtf.replace(
                                /[\u00e0-\u00ef][\u0080-\u00bf][\u0080-\u00bf]/g,  // 3-byte chars
                                function(c) {  // (note parentheses for precence)
                                var cc = ((c.charCodeAt(0)&0x0f)<<12) | ((c.charCodeAt(1)&0x3f)<<6) | ( c.charCodeAt(2)&0x3f); 
                                return String.fromCharCode(cc); }
                                );
    strUni = strUni.replace(
                            /[\u00c0-\u00df][\u0080-\u00bf]/g,                 // 2-byte chars
                            function(c) {  // (note parentheses for precence)
                            var cc = (c.charCodeAt(0)&0x1f)<<6 | c.charCodeAt(1)&0x3f;
                            return String.fromCharCode(cc); }
                            );
    return strUni;
}

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

// asm.js mixer
function mydspMixer(global, foreign, buffer) {
	
	'use asm';
	
    var HEAP32 = new global.Int32Array(buffer);
	var HEAPF32 = new global.Float32Array(buffer);
    
    var max = global.Math.max;
    var abs = global.Math.abs;
    
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
        var level = 0.;
        for (i = 0; ((i | 0) < (channels | 0) | 0); i = ((i | 0) + 1 | 0)) {
            for (j = 0; ((j | 0) < (count | 0) | 0); j = ((j | 0) + 1 | 0)) {
                level = max(+level, +(abs(+(HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]))));
                HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2] 
                    = +(HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]) + 
                      +(HEAPF32[(HEAP32[inputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]);
            }
        }
        return +level;
    }
	
	return { mixVoice: mixVoice, clearOutput: clearOutput};
}

var faust = faust || {};

// Shim AudioContext on webkit
window.AudioContext = window.AudioContext || window.webkitAudioContext || undefined;

faust.createAsmCDSPFactoryFromString = Module.cwrap('createAsmCDSPFactoryFromString', 'number', ['number', 'number', 'number', 'number']);
faust.freeCDSP = Module.cwrap('freeCDSP', null, ['number']);

faust.error_msg = null;
faust.factory_number = 0;
faust.factory_table = [];

faust.getErrorMessage = function() { return faust.error_msg; }

faust.createDSPFactory = function (code) {

    var sha_key = Sha1.hash(code, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        // Existing factory, do not create it...
        return factory;
    }
    
    // Allocate strings on the HEAP
    var factory_name = "mydsp" + faust.factory_number++;
    var code_ptr = Module._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = Module._malloc(name.length + 1);
    var error_msg_ptr = Module._malloc(256);
    var factory_name_ptr = Module._malloc(factory_name.length + 1);
    
    Module.writeStringToMemory(name, name_ptr);
    Module.writeStringToMemory(code, code_ptr);
    Module.writeStringToMemory(factory_name, factory_name_ptr);
    
    var factory_code_ptr = faust.createAsmCDSPFactoryFromString(name_ptr, code_ptr, factory_name_ptr, error_msg_ptr);
    var factory_code = Pointer_stringify(factory_code_ptr);
    faust.error_msg = Pointer_stringify(error_msg_ptr);
    if (factory_code === "") {
        return null;
    }

    console.log(factory_code);

    // 'libfaust.js' asm.js backend generates the ASM module + UI method, then we compile the code
    eval(factory_code);

    // Compile the ASM module itself : 'buffer' is the emscripten global memory context
    var factory = eval(factory_name + "Factory(window, null, buffer)");        
    console.log(factory);

    var path_table_function = eval("getPathTable" + factory_name); 
    factory.pathTable = path_table_function();

    var json_function = eval("getJSON" + factory_name);
    factory.getJSON = function() { return json_function(); }

    var metadata_function = eval("metadata" + factory_name);
    factory.metadata = function(m) { return metadata_function(m); }

    var getdspsize_function = eval("getSize" + factory_name);
    factory.getSize = function(m) { return getdspsize_function(m); }

    factory.factory_name = factory_name;
    factory.sha_key = sha_key;
    faust.factory_table[sha_key] = factory;
    console.log(sha_key);
    
    /// Free strings
    Module._free(code_ptr);
    Module._free(name_ptr);
    Module._free(error_msg_ptr);
    Module._free(factory_name_ptr);
    
    // Free C allocated asm.js module
    faust.freeCDSP(factory_code_ptr);
    
    return factory;
};

faust.deleteDSPFactory = function (factory) { faust.factory_table[factory.sha_key] = null; }

// 'mono' DSP
faust.createDSPInstance = function (factory, context, buffer_size) {
    
    var that = {};

    that.factory = factory;
    that.dsp = Module._malloc(that.factory.getSize());
    faust.context = context;
    that.buffer_size = buffer_size;
    that.handler = null;

    // bargraph
    that.ouputs_timer = 5;
    that.ouputs_items = [];
     
    // input items
    that.inputs_items = [];
           
    that.getNumInputs = function () 
    {
        return that.factory.getNumInputs(that.dsp);
    };
    
    that.getNumOutputs = function () 
    {
        return that.factory.getNumOutputs(that.dsp);
    };
    
    that.update_outputs = function () 
    {
        if (that.ouputs_items.length > 0 && that.handler && that.ouputs_timer-- === 0) {
            that.ouputs_timer = 5;
            var i;
            for (i = 0; i < that.ouputs_items.length; i++) {
                that.handler(that.ouputs_items[i], that.factory.getValue(that.dsp, that.factory.pathTable[that.ouputs_items[i]]));
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

    that.setHandler = function(handler)
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
        that.factory.setValue(that.dsp, that.factory.pathTable[path], val);
    };
    
    that.getValue = function (path) 
    {
        return that.factory.getValue(that.dsp, that.factory.pathTable[path]);
    };
    
    that.json = function ()
    {
        return that.factory.getJSON();
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
        var i;
        that.ptrsize = 4; //assuming pointer in emscripten are 32bits
        that.samplesize = 4;
         
        // Get input / output counts
        that.numIn = that.getNumInputs();
        that.numOut = that.getNumOutputs();
         
        // Setup web audio context
        console.log("that.buffer_size %d", that.buffer_size);
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
         
            // Prepare Out buffer tables
            that.dspOutChannnels = [];
            var dspOutChans = HEAP32.subarray(that.outs >> 2, (that.outs + that.numOut * that.ptrsize) >> 2);
            for (i = 0; i < that.numOut; i++) {
                that.dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + that.buffer_size * that.ptrsize) >> 2);
            }
        }
                                
        // bargraph
        that.parse_ui(JSON.parse(that.json()).ui);

        // Init DSP
        that.factory.init(that.dsp, faust.context.sampleRate);
    };
    
    that.init();
    return that;
};

faust.deleteDSPInstance = function (that) {
    that.stop();
    var i;
     
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
  
    Module._free(that.dsp);
};

// 'poly' DSP
faust.createPolyDSPInstance = function (factory, context, buffer_size, max_polyphony) {
    
    var that = {};

    that.factory = factory;
    faust.context = context;
    that.polyphony = max_polyphony;
    that.buffer_size = buffer_size;
    that.handler = null;

    // bargraph
    that.ouputs_timer = 5;
    that.ouputs_items = [];
     
    // input items
    that.inputs_items = [];
    
    // asm.js mixer
    that.mixer = mydspMixer(window, null, buffer);
    
    // Start of DSP memory ('polyphony' DSP voices)
    that.dsp_voices = [];
    that.dsp_voices_state = [];
    
    that.kFreeVoice = -2;
    that.kReleaseVoice = -1;
    
    var i;
    for (i = 0; i < that.polyphony; i++) {
        that.dsp_voices[i] = Module._malloc(that.factory.getSize());
        that.dsp_voices_state[i] = that.kFreeVoice;
    }
    
    that.getVoice = function (note)
    {
        var i;
        for (i = 0; i < that.polyphony; i++) {
            if (that.dsp_voices_state[i] === note) return i;
        }
        return that.kReleaseVoice;
    }
           
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
                that.handler(that.ouputs_items[i], that.factory.getValue(that.dsp_voices[0], that.factory.pathTable[that.ouputs_items[i]]));
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
        
        // Compute all running voices
        var level;
        for (i = 0; i < that.polyphony; i++) {
            if (that.dsp_voices_state[i] != that.kFreeVoice) {
                that.factory.compute(that.dsp_voices[i], that.buffer_size, that.ins, that.mixing);
                level = that.mixer.mixVoice(that.buffer_size, that.numOut, that.mixing, that.outs);
                if ((level < 0.001) && (that.dsp_voices_state[i] == that.kReleaseVoice)) {
                    that.dsp_voices_state[i] = that.kFreeVoice;
                }
            }
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

    that.setHandler = function(handler)
    {
        that.handler = handler;
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
        var voice = that.getVoice(that.kFreeVoice);
        if (voice == that.kReleaseVoice) voice = that.getVoice(that.kReleaseVoice);  // Gets a free voice
       
        if (voice >= 0) {
            //console.log("keyOn voice %d", voice);
            that.factory.setValue(that.dsp_voices[voice], that.fFreqLabel, that.midiToFreq(pitch));
            that.factory.setValue(that.dsp_voices[voice], that.fGainLabel, velocity/127.);
            that.factory.setValue(that.dsp_voices[voice], that.fGateLabel, 1.0);
            that.dsp_voices_state[voice] = pitch;
        } else {
            console.log("No more free voice...\n");
        }
    }
    
    that.keyOff = function (channel, pitch)
    {
        var voice = that.getVoice(pitch);
        if (voice >= 0) {
            //console.log("keyOff voice %d", voice);
            that.factory.setValue(that.dsp_voices[voice], that.fGateLabel, 0.0);
            that.dsp_voices_state[voice] = that.kReleaseVoice;
        } else {
            console.log("Playing voice not found...\n");
        }
    }
    
    that.ctrlChange = function (channel, ctrl, value)
    {}
    
    that.pitchBend = function (channel, refPitch, pitch)
    {
        var voice = that.getVoice(refPitch);
        if (voice >= 0) {
            that.factory.setValue(that.dsp_voices[voice], that.fGateLabel, that.midiToFreq(pitch))
        } else {
        	console.log("Playing voice not found...\n");
        }
    }
  
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
            that.factory.setValue(that.dsp_voices[i], that.factory.pathTable[path], val);
        }
    };
    
    that.getValue = function (path) 
    {
        that.factory.getValue(that.dsp_voices[0], that.factory.pathTable[path]);
    };
    
    that.json = function ()
    {
        return that.factory.getJSON();
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
        var i;
        that.ptrsize = 4; //assuming pointer in emscripten are 32bits
        that.samplesize = 4;
         
        // Get input / output counts
        that.numIn = that.getNumInputs();
        that.numOut = that.getNumOutputs();
         
        // Setup web audio context
        console.log("that.buffer_size %d", that.buffer_size);
        that.scriptProcessor = faust.context.createScriptProcessor(that.buffer_size, that.numIn, that.numOut);
        that.scriptProcessor.onaudioprocess = that.compute;
    
        if (that.numIn > 0) {
            // allocate memory for input arrays
            that.ins = Module._malloc(that.ptrsize * that.numIn);
             
            for (i = 0; i < that.numIn; i++) { 
                  HEAP32[(that.ins >> 2) + i] = Module._malloc(that.buffer_size * that.samplesize); 
            }

            // Prepare ins/out buffer tables
            that.dspInChannnels = [];
            var dspInChans = HEAP32.subarray(that.ins >> 2, (that.ins + that.numIn * that.ptrsize) >> 2);
            for (i = 0; i < that.numIn; i++) {
                that.dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + that.buffer_size * that.ptrsize) >> 2);
            }
        }
            
        if (that.numOut > 0) {
        
            // allocate memory for output and mixing arrays
            that.outs = Module._malloc(that.ptrsize * that.numOut);
            that.mixing = Module._malloc(that.ptrsize * that.numOut);
             
            for (i = 0; i < that.numOut; i++) { 
                HEAP32[(that.outs >> 2) + i] = Module._malloc(that.buffer_size * that.samplesize);
                HEAP32[(that.mixing >> 2) + i] = Module._malloc(that.buffer_size * that.samplesize);
            }
         
            that.dspOutChannnels = [];
            
            var dspOutChans = HEAP32.subarray(that.outs >> 2, (that.outs + that.numOut * that.ptrsize) >> 2);
            var mixingChans = HEAP32.subarray(that.outs >> 2, (that.mixing + that.numOut * that.ptr_size) >> 2);
            
            for (i = 0; i < that.numOut; i++) {
                that.dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + that.buffer_size * that.ptrsize) >> 2);
            }
        }
                                
        // bargraph
        that.parse_ui(JSON.parse(that.json()).ui);
        
        // keep 'keyOn/keyOff' labels
        for (i = 0; i < that.inputs_items.length; i++) {
            if (that.inputs_items[i].endsWith("/gate")) {
                that.fGateLabel = that.factory.pathTable[that.inputs_items[i]];
                console.log(that.fGateLabel);
            } else if (that.inputs_items[i].endsWith("/freq")) {
                that.fFreqLabel = that.factory.pathTable[that.inputs_items[i]];
                console.log(that.fFreqLabel);
            } else if (that.inputs_items[i].endsWith("/gain")) {
                that.fGainLabel = that.factory.pathTable[that.inputs_items[i]];
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
};

faust.deletePolyDSPInstance = function (that) {
    that.stop();
    var i;
    
    if (that.numIn > 0) {
        for (i = 0; i < that.numIn; i++) { 
            Module._free(HEAP32[(that.ins >> 2) + i]); 
        }
        Module._free(that.ins);
    }
     
    if (that.numOut > 0) {
        for (i = 0; i < that.numOut; i++) { 
            Module._free(HEAP32[(that.outs >> 2) + i]);
            Module._free(HEAP32[(that.mixing >> 2) + i])
        }
        Module._free(that.outs);
        Module._free(that.mixing);
    }
    
    for (i = 0; i < that.polyphony; i++) {
        Module._free(that.dsp_voices[i]);
    }
};