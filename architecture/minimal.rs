
<<includeIntrinsic>>

<<includeclass>>

fn main() {

    println!("Faust Rust DSP");

    let mut dsp = mydsp::new();

    println!("getNumInputs: {}", dsp.getNumInputs());
    println!("getNumOutputs: {}", dsp.getNumOutputs());

    // Init DSP with a given SR
    dsp.init(44100);

    println!("getSampleRate: {}", dsp.getSampleRate());

    // Has to be done in the audio thread taking adapted "native" (JACK/PortAudio allocated...) audio buffers
    // dsp.compute(512, inputs, outputs);
}
