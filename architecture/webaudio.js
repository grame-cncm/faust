
<<includeIntrinsic>>
<<includeclass>>

<!-- WebAudio API -->

var isWebKitAudio = (typeof (webkitAudioContext) !== "undefined");

process_mydsp = function(obj) 
{
    function process_aux_mydsp(event) 
    {
        var count;
        
        /*
        if (event.inputBuffer.numberOfChannels < dsp.getNumInputs()) {
            console.log("Incorrect number of input %d instead of %d", event.inputBuffer.numberOfChannels, dsp.getNumInputs());
            return;
        }
        */
        
        if (event.outputBuffer.numberOfChannels < obj.dsp.getNumOutputs()) {
            console.log("Incorrect number of output %d instead of %d", event.outputBuffer.numberOfChannels, obj.dsp.getNumOutputs());
            return;
        }
         
        for (var i = 0; i < obj.dsp.getNumInputs(); i++) {
            obj.inputs[i] = event.inputBuffer.getChannelData(i);
            if (obj.inputs[i] != null) {
                count = obj.inputs[i].length;
            }
        }
        
        for (var i = 0; i < obj.dsp.getNumOutputs(); i++) {
            obj.outputs[i] = event.outputBuffer.getChannelData(i);
            if (obj.outputs[i] != null) {
                count = obj.outputs[i].length;
            }
        }
        
        obj.dsp.compute(count, obj.inputs, obj.outputs);

    }
    return process_aux_mydsp;
}

function create_mydsp(audio_context, user_interface, meta_interface, buffer_size)
{
    this.dsp = new mydsp();
    
    this.dsp.init(audio_context.sampleRate);
    this.dsp.buildUserInterface(user_interface);
    this.dsp.metadata(meta_interface);
    
    this.inputs = new Array(this.dsp.getNumInputs());
    this.outputs = new Array(this.dsp.getNumOutputs());
    
    console.log(audio_context.sampleRate);
    console.log(this.dsp.getNumInputs());
    console.log(this.dsp.getNumOutputs());
    
    this.processor = (isWebKitAudio) 
        ? audio_context.createJavaScriptNode(buffer_size, this.dsp.getNumInputs(), this.dsp.getNumOutputs())
        : audio_context.createScriptProcessor(buffer_size, this.dsp.getNumInputs(), this.dsp.getNumOutputs());
    this.processor.onaudioprocess = process_mydsp(this);
    
    return this.processor;
}


