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

'use strict';

// Build global context
var window = {};
window.Math = {};

window.Int32Array = Int32Array;
window.Float64Array = Float64Array;

window.Math.imul = Math.imul;
window.Math.log = Math.log;
window.Math.abs = global.Math.abs;
window.Math.fabs = global.Math.abs;
window.Math.acos = global.Math.acos;
window.Math.asin = global.Math.asin;
window.Math.atan = global.Math.atan;
window.Math.atan2 = global.Math.atan2;
window.Math.ceil = global.Math.ceil;
window.Math.cos = global.Math.cos;
window.Math.exp = global.Math.exp;
window.Math.floor = global.Math.floor;
window.Math.log = global.Math.log;
window.Math.max = global.Math.max;
window.Math.min = global.Math.min;
window.Math.pow = global.Math.pow;
window.Math.round = global.Math.round;
window.Math.sin = global.Math.sin;
window.Math.sqrt = global.Math.sqrt;
window.Math.tan = global.Math.tan;

//console.log("libfaust");

var libfaust = require('/usr/local/share/faust/webaudio/libfaust.js');

//console.log(libfaust);
//console.log(libfaust.Module);
//console.log("libfaust OK");

var faust = faust || {};

faust.createAsmCDSPFactoryFromString = libfaust.cwrap('createAsmCDSPFactoryFromString', 'number', ['number', 'number', 'number', 'number', 'number']);
faust.expandCDSPFromString = libfaust.cwrap('expandCDSPFromString', 'number', ['number', 'number', 'number', 'number', 'number', 'number']);
faust.getCLibFaustVersion = libfaust.cwrap('getCLibFaustVersion', 'number', []);
faust.freeCMemory = libfaust.cwrap('freeCMemory', null, ['number']);

faust.error_msg = null;
faust.factory_number = 0;
faust.factory_table = [];

faust.getErrorMessage = function() { return faust.error_msg; };

faust.createDSPFactory = function (code, argv) {
    
    var sha_key = Sha1.hash(code, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        // Existing factory, do not create it...
        return factory;
    }
    
    //console.log("libfaust.js version : " + libfaust.Pointer_stringify(faust.getCLibFaustVersion()));
    
    // Allocate strings on the HEAP
    var factory_name = "mydsp" + faust.factory_number++;
    var code_ptr = libfaust._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = libfaust._malloc(name.length + 1);
    var error_msg_ptr = libfaust._malloc(4096);
    
    libfaust.stringToUTF8(name, name_ptr, libfaust.lengthBytesUTF8(name) + 1);
    libfaust.stringToUTF8(code, code_ptr, libfaust.lengthBytesUTF8(code) + 1);
    
    // Add 'cn' option with the factory name
    argv = (argv === undefined) ? new Array() : argv;
    argv.push("-cn", factory_name);
    
    // Prepare 'argv' array for C side
    var ptr_size = 8;
    var argv_ptr = libfaust._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(libfaust.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = libfaust._malloc(argv[i].length + 1);
        libfaust.stringToUTF8(argv[i], arg_ptr, libfaust.lengthBytesUTF8(argv[i]) + 1);
        argv_ptr_buffer[i] = arg_ptr;
    }
    
    try {
        var factory_code_ptr = faust.createAsmCDSPFactoryFromString(name_ptr, code_ptr, argv.length, argv_ptr, error_msg_ptr);
        var factory_code = libfaust.Pointer_stringify(factory_code_ptr);
        faust.error_msg = libfaust.Pointer_stringify(error_msg_ptr);
    } catch(e) {
        console.log(e);
    }
    
    // Free strings
    libfaust._free(code_ptr);
    libfaust._free(name_ptr);
    libfaust._free(error_msg_ptr);
    
    // Free C allocated asm.js module
    faust.freeCMemory(factory_code_ptr);
    
    // Free 'argv' C side array
    for (var i = 0; i < argv.length; i++) {
        libfaust._free(argv_ptr_buffer[i]);
    }
    libfaust._free(argv_ptr);
    
    if (factory_code === "") {
        return null;
    } else {
        return faust.readDSPFactoryFromMachineAux(factory_name, factory_code, sha_key);
    }
};

faust.expandDSP = function (code, argv) {
    
    // Force "ajs" compilation
    argv.push("-lang");
    argv.push("ajs");
    
    // Allocate strings on the HEAP
    var code_ptr = libfaust._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = libfaust._malloc(name.length + 1);
    var sha_key_ptr = libfaust._malloc(64);
    var error_msg_ptr = libfaust._malloc(4096);
    
    libfaust.stringToUTF8(name, name_ptr, libfaust.lengthBytesUTF8(name) + 1);
    libfaust.stringToUTF8(code, code_ptr, libfaust.lengthBytesUTF8(code) + 1);
    
    // Add 'cn' option with the factory name
    argv = (argv === undefined) ? new Array() : argv;
    
    // Prepare 'argv' array for C side
    var ptr_size = 8;
    var argv_ptr = libfaust._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(libfaust.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = libfaust._malloc(argv[i].length + 1);
        libfaust.stringToUTF8(argv[i], arg_ptr, libfaust.lengthBytesUTF8(argv[i]) + 1);
        argv_ptr_buffer[i] = arg_ptr;
    }
    
    var expand_dsp_ptr = faust.expandCDSPFromString(name_ptr, code_ptr, argv.length, argv_ptr, sha_key_ptr, error_msg_ptr);
    var expand_dsp = libfaust.Pointer_stringify(expand_dsp_ptr);
    var sha_key = libfaust.Pointer_stringify(sha_key_ptr);
    faust.error_msg = libfaust.Pointer_stringify(error_msg_ptr);
    
    // Free strings
    libfaust._free(code_ptr);
    libfaust._free(name_ptr);
    libfaust._free(sha_key_ptr);
    libfaust._free(error_msg_ptr);
    
    // Free C allocated asm.js module
    faust.freeCMemory(expand_dsp_ptr);
    
    // Free 'argv' C side array
    for (var i = 0; i < argv.length; i++) {
        libfaust._free(argv_ptr_buffer[i]);
    }
    libfaust._free(argv_ptr);
    
    return expand_dsp;
};

faust.writeDSPFactoryToMachine = function (factory)
{
    return { name : factory.name, code : factory.code };
}

faust.readDSPFactoryFromMachine = function (machine)
{
    var sha_key = Sha1.hash(machine.code, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        // Existing factory, do not create it...
        return factory;
    } else {
        return faust.readDSPFactoryFromMachineAux(machine.name, machine.code, sha_key);
    }
}

faust.readDSPFactoryFromMachineAux = function (factory_name, factory_code, sha_key)
{
    //console.log(factory_code);
    
    // 'libfaust.js' asm.js backend generates the ASM module + UI method, then we compile the code
    eval(factory_code);
    
    // Compile the ASM module itself : 'buffer' is the emscripten global memory context
    factory = eval(factory_name + "Module(window, window.Math, libfaust.buffer)");
    
    var path_table_function = eval("getPathTable" + factory_name);
    factory.pathTable = path_table_function();
    
    factory.getJSON = eval("getJSON" + factory_name);
    factory.metadata = eval("metadata" + factory_name);
    factory.getSize = eval("getSize" + factory_name);
    
    factory.name = factory_name;
    factory.sha_key = sha_key;
    factory.code = factory_code;
    
    faust.factory_table[sha_key] = factory;
    
    return factory;
}

faust.deleteDSPFactory = function (factory) { faust.factory_table[factory.sha_key] = null; };

// 'mono' DSP
faust.createDSPInstance = function (factory, buffer_size, sample_rate) {
    
    var dsp = libfaust._malloc(factory.getSize());
    var handler = null;
    var ins, outs;
    var numIn, numOut;
    
    var dspInChannnels = [];
    var dspOutChannnels = [];
    
    // bargraph
    var ouputs_timer = 5;
    var ouputs_items = [];
    
    // input items
    var inputs_items = [];
    
    // buttons items
    var buttons_items = [];
    
    // default values
    var default_values = [];
    
    // Allocate table for 'setParamValue'
    var value_table = [];
    
    function update_outputs ()
    {
        if (ouputs_items.length > 0 && handler && ouputs_timer-- === 0) {
            ouputs_timer = 5;
            for (var i = 0; i < ouputs_items.length; i++) {
                handler(ouputs_items[i], factory.getParamValue(dsp, factory.pathTable[ouputs_items[i]]));
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
            for (j = 0; j < input.length; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // Update control state
        for (i = 0; i < inputs_items.length; i++) {
            var path = inputs_items[i];
            var values = value_table[path];
            factory.setParamValue(dsp, factory.pathTable[path], values[0]);
            values[0] = values[1];
        }
        
        // Compute
        factory.compute(dsp, buffer_size, ins, outs);
        
        // Update bargraph
        update_outputs();
        
        // Write outputs
        for (i = 0; i < numOut; i++) {
            var output = outputs[i];
            var dspOutput = dspOutChannnels[i];
            for (j = 0; j < output.length; j++) {
                output[j] = dspOutput[j];
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
        // Setup web audio context
        var i;
        var ptr_size = 8;
        var sample_size = 8;    // double
        
        // Get input / output counts
        numIn = factory.getNumInputs(dsp);
        numOut = factory.getNumOutputs(dsp);
        
        // Setup web audio context
        //console.log("buffer_size %d", buffer_size);
        
        if (numIn > 0) {
            ins = libfaust._malloc(ptr_size * numIn);
            for (i = 0; i < numIn; i++) {
                libfaust.HEAP32[(ins >> 2) + i] = libfaust._malloc(buffer_size * sample_size);
            }
            
            // Prepare Ins buffer tables
            var dspInChans = libfaust.HEAP32.subarray(ins >> 2, (ins + numIn * ptr_size) >> 2);
            for (i = 0; i < numIn; i++) {
                dspInChannnels[i] = libfaust.HEAPF64.subarray(dspInChans[i] >> 3, (dspInChans[i] + buffer_size * sample_size) >> 3);
            }
        }
        
        if (numOut > 0) {
            outs = libfaust._malloc(ptr_size * numOut);
            for (i = 0; i < numOut; i++) {
                libfaust.HEAP32[(outs >> 2) + i] = libfaust._malloc(buffer_size * sample_size);
            }
            
            // Prepare Out buffer tables
            var dspOutChans = libfaust.HEAP32.subarray(outs >> 2, (outs + numOut * ptr_size) >> 2);
            for (i = 0; i < numOut; i++) {
                dspOutChannnels[i] = libfaust.HEAPF64.subarray(dspOutChans[i] >> 3, (dspOutChans[i] + buffer_size * sample_size) >> 3);
            }
        }
        
        // bargraph
        parse_ui(JSON.parse(factory.getJSON()).ui);
        
        // Init DSP
        factory.init(dsp, sample_rate);
        
        // Init 'value' table
        for (var i = 0; i < inputs_items.length; i++) {
            var path = inputs_items[i];
            var values = new Float32Array(2);
            values[0] = values[1] = factory.getParamValue(dsp, factory.pathTable[path]);
            value_table[path] = values;
        }
    }
    
    function setParamValueAux(path, val)
    {
        var values = value_table[path];
        if (values) {
        	// relaxing the test
        	//if (factory.getParamValue(dsp, factory.pathTable[path]) == values[0]) {
                values[0] = val;
            //}
            values[1] = val;
        }
    }
    
    init();
    
    // External API
    return {
        
        getNumInputs : function ()
        {
            return factory.getNumInputs(dsp);
        },
        
        getNumOutputs : function ()
        {
            return factory.getNumOutputs(dsp);
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
        
        setHandler : function (hd)
        {
            handler = hd;
        },
        
        setParamValue : function (path, val)
        {
            setParamValueAux(path, val);
        },
        
        setParamValue1 : function (path, val)
        {
            factory.setParamValue(dsp, factory.pathTable[path], val);
        },
        
        getParamValue : function (path)
        {
            return factory.getParamValue(dsp, factory.pathTable[path]);
        },
        
        controls : function()
        {
            return inputs_items;
        },
        
        buttons : function()
        {
            return buttons_items;
        },
        
        json : function ()
        {
            return factory.getJSON();
        },
        
        compute : function (inputs, outputs)
        {
            computeAux(inputs, outputs);
        },
        
        checkDefaults : function ()
        {
            for (var i = 0; i < default_values.length; i++) {
                if (default_values[i] !== factory.getParamValue(dsp, factory.pathTable[inputs_items[i]])) return false;
            }
            return true;
        },
        
        initRandom : function ()
        {
            for (var i = 0; i < default_values.length; i++) {
                factory.setParamValue(dsp, factory.pathTable[inputs_items[i]], 0.123456789);
            }
        }
        
    }
}

faust.deleteDSPInstance = function (dsp) {
    dsp.stop();
    
    if (dsp.numIn > 0) {
        for (var i = 0; i < dsp.numIn; i++) {
            libfaust._free(libfaust.HEAP32[(dsp.ins >> 2) + i]);
        }
        libfaust._free(dsp.ins);
    }
    
    if (dsp.numOut > 0) {
        for (var i = 0; i < dsp.numOut; i++) {
            libfaust._free(libfaust.HEAP32[(dsp.outs >> 2) + i]);
        }
        libfaust._free(dsp.outs);
    }
    
    libfaust._free(dsp.dsp);
}

// Helper functions

var create = function(ins, outs, buffer_size) {
    
    for (var i = 0; i < ins; i++) {
        inputs.push(new Float64Array(buffer_size));
    }
    for (var i = 0; i < outs; i++) {
        outputs.push(new Float64Array(buffer_size));
    }
}

var impulse = function(ins, buffer_size) {
    for (var i = 0; i < ins; i++) {
        inputs[i][0] = 1.0;
        for (var f = 1; f < buffer_size; f++) {
            inputs[i][f] = 0.0;
        }
    }
}

var zero = function(ins, buffer_size) {
    for (var i = 0; i < ins; i++) {
        for (var f = 0; f < buffer_size; f++) {
            inputs[i][f] = 0.0;
        }
    }
}

var normalize = function(f)
{
    return (Math.abs(f) < 0.000001) ? 0.0 : f;
}

var setButtons = function(dsp, value)
{
    var buttons = DSP.buttons();
    for (var i = 0; i < buttons.length; i++) {
        dsp.setParamValue(buttons[i], value);
    }
}

var fs = require('fs');

var buffer_size = 64;
var sample_rate = 44100;
var inputs = [];
var outputs = [];
var nbsamples = 60000;
var linenum = 0;
var run = 0;
var control_data;
var factory;
var dsp_code;

try {
    dsp_code = fs.readFileSync('SOURCE_FILE.dsp', 'utf8');
    factory = faust.createDSPFactory(dsp_code, ["-double"]);
} catch (e) {
    console.error("Cannot allocate factory " + faust.getErrorMessage());
    process.exit(1);
}

// Creates DSP and buffers
var DSP = faust.createDSPInstance(factory, buffer_size, sample_rate);
create(DSP.getNumInputs(), DSP.getNumOutputs(), buffer_size);

//console.log(DSP);
//console.log(DSP.getNumInputs());
//console.log(DSP.getNumOutputs());
//console.log(DSP.json());
//console.log(DSP.buttons());
//console.log(control_data);
//console.log(DSP.controls());

// Write output file header
console.log("number_of_inputs  : ", DSP.getNumInputs());
console.log("number_of_outputs : ", DSP.getNumOutputs());
console.log("number_of_frames  : ", nbsamples);

/*
 // Check getSampleRate
 if (DSP.getSampleRate() !== sample_rate) {
 console.error("ERROR in getSampleRate");
	process.exit(1);
 }
 */

// Check setParamValue/getParamValue
var path_table = DSP.controls();
for (var i = 0; i < path_table.length; i++) {
    DSP.setParamValue1(path_table[i], 0.1234);
    if (DSP.getParamValue(path_table[i]) !== 0.1234) {
        console.error("ERROR in setParamValue/getParamValue for " + path_table[i] + " " + DSP.getParamValue(path_table[i]));
        process.exit(1);
    }
}

// Check default after 'instanceResetUserInterface'
DSP.initRandom();
DSP.instanceResetUserInterface();
if (!DSP.checkDefaults()) {
    console.error("ERROR in checkDefaults after 'instanceResetUserInterface'");
    process.exit(1);
}

// Check default after 'instanceInit'
DSP.initRandom();
DSP.instanceInit();
if (!DSP.checkDefaults()) {
    console.error("ERROR in checkDefaults after 'instanceInit'");
    process.exit(1);
}

// Check default after 'init'
DSP.initRandom();
DSP.init(sample_rate);
if (!DSP.checkDefaults()) {
    console.error("ERROR in checkDefaults after 'init'");
    process.exit(1);
}

DSP.init(sample_rate);

// Read control parameters
try {
    control_data = fs.readFileSync('DSP_NAMErc', 'utf8');
    var lines = control_data.split('\n');
    for (var line = 0; line < lines.length; line++) {
        var param = lines[line].split(' ');
        DSP.setParamValue('/'+ param[1], parseFloat(param[0]));
    }
} catch (e) {}

// Compute samples and write output file
while (nbsamples > 0) {
    if (run === 0) {
        impulse(DSP.getNumInputs(), buffer_size);
        setButtons(DSP, 1.0);
    }
    if (run === 1) {
        zero(DSP.getNumInputs(), buffer_size);
        setButtons(DSP, 0.0);
    }
    var nFrames = Math.min(buffer_size, nbsamples);
    DSP.compute(inputs, outputs);
    run++;
    for (var i = 0; i < nFrames; i++) {
        var line = (linenum++) + " : ";
        for (var c = 0; c < DSP.getNumOutputs(); c++) {
            var f = normalize(outputs[c][i]);
            line = line + f + " ";
        }
        console.log(line);
    }
    nbsamples -= nFrames;
}
