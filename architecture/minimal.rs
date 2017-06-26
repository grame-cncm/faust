
<<includeIntrinsic>>

<<includeclass>>

fn main() {

    println!("Faust Rust DSP");

    let mut dsp = mydsp::new();

    println!("getNumInputs {}", dsp.getNumInputs());
    println!("getNumOutputs {}", dsp.getNumOutputs());

}
