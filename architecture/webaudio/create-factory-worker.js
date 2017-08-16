
importScripts('libfaustworker.js');

onmessage = function(e) {
  
    try {
        var code = e.data.code;
        var argv = e.data.argv;
        var factory_name = e.data.factory_name;
        
        // Allocate strings on the HEAP
        var code_ptr = Module._malloc(code.length + 1);
        var name = "FaustDSP";
        var name_ptr = Module._malloc(name.length + 1);
        var error_msg_ptr = Module._malloc(4096);
        
        Module.stringToUTF8(name, name_ptr, Module.lengthBytesUTF8(name) + 1);
        Module.stringToUTF8(code, code_ptr, Module.lengthBytesUTF8(code) + 1);
        
        var createAsmCDSPFactoryFromString = Module.cwrap('createAsmCDSPFactoryFromString', 'number', ['number', 'number', 'number', 'number', 'number']);
        var getCLibFaustVersion = Module.cwrap('getCLibFaustVersion', 'number', []);
        var freeCMemory = Module.cwrap('freeCMemory', null, ['number']);
        
        console.log("libfaustworker.js version : " + Pointer_stringify(getCLibFaustVersion()));
        
        // Add 'cn' option with the factory name
        argv = (argv === null) ? new Array() : argv;
        argv.push("-cn", factory_name);
        
        // Prepare 'argv' array for C side
        var ptr_size = 4; 
        var argv_ptr = Module._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
        var argv_ptr_buffer = new Int32Array(Module.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
        for (var i = 0; i < argv.length; i++) {
            var arg_ptr = Module._malloc(argv[i].length + 1);
            Module.stringToUTF8(argv[i], arg_ptr, Module.lengthBytesUTF8(argv[i]) + 1);
            argv_ptr_buffer[i] = arg_ptr; 
        }
        
    	var factory_code_ptr = createAsmCDSPFactoryFromString(name_ptr, code_ptr, argv.length, argv_ptr, error_msg_ptr);
    	var factory_code = Pointer_stringify(factory_code_ptr);
    	var error_msg = Pointer_stringify(error_msg_ptr);
    
    	// Free strings
    	Module._free(code_ptr);
    	Module._free(name_ptr);
    	Module._free(error_msg_ptr);
        
        // Free C allocated asm.js module
        freeCMemory(factory_code_ptr);
        
        // Free 'argv' C side array
        for (var i = 0; i < argv.length; i++) {
            Module._free(argv_ptr_buffer[i]);
        }
        Module._free(argv_ptr);
        
        // Returns compiled factory
        postMessage({factory_code: factory_code, error_msg: error_msg});
   
    } catch (e) {
        console.log(e);
        postMessage({factory_code: "", error_msg: "createAsmCDSPFactoryFromString error"});
    }
   
}

