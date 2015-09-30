
importScripts('libfaustworker.js');

onmessage = function(e) {
  
    var code = e.data.code;
    var argv = e.data.argv;
    var factory_name = e.data.factory_name;
    
    // Allocate strings on the HEAP
    var code_ptr = Module._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = Module._malloc(name.length + 1);
    var error_msg_ptr = Module._malloc(256);
    
    Module.writeStringToMemory(name, name_ptr);
    Module.writeStringToMemory(code, code_ptr);
    
    var createAsmCDSPFactoryFromString = Module.cwrap('createAsmCDSPFactoryFromString', 'number', ['number', 'number', 'number', 'number', 'number']);
    var getCLibFaustVersion = Module.cwrap('getCLibFaustVersion', 'number', []);
    var freeCDSP = Module.cwrap('freeCDSP', null, ['number']);
    
    argv = (argv === null) ? new Array() : argv;
    argv.push("-cn", factory_name);
    
    // Prepare 'argv' array for C side
    var ptr_size = 4; 
    var argv_ptr = Module._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(Module.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = Module._malloc(argv[i].length + 1);
        Module.writeStringToMemory(argv[i], arg_ptr);
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
    freeCDSP(factory_code_ptr);
    
    // Free 'argv' C side array
    for (var i = 0; i < argv.length; i++) {
        Module._free(argv_ptr_buffer[i]);
    }
    Module._free(argv_ptr);
   
	postMessage({factory_code: factory_code, error_msg: error_msg});
}

