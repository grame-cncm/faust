
async function getnode(audioCtx, module, code, voices) {
    let sp = typeof (window.AudioWorkletNode) == "undefined";
    let compiler = Faust.createCompiler(Faust.createLibFaust(module));
    if (voices > 1)
        return Faust.createAudioNodeFactory().compilePolyNode(audioCtx, "Faust", compiler, code, null, "-I libraries", voices, sp, 1024);
    else
        return Faust.createAudioNodeFactory().compileMonoNode(audioCtx, "Faust", compiler, code, null, "-I libraries", sp, 1024);
}
