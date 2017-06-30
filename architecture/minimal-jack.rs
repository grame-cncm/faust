
#![allow(unused_parens)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]

//! Faust Jack architecture file
extern crate jack;
use jack::prelude as j;
use std::io;

<<includeIntrinsic>>
<<includeclass>>

fn main() {

    // Create JACK client
    let (client, _status) = j::Client::new("faust_rust", j::client_options::NO_START_SERVER).unwrap();

    // Allocation DSP on the heap
    let mut dsp = Box::new(mydsp::new());

    println!("Faust Rust code running with JACK: sample-rate = {} buffer-size = {}", client.sample_rate(), client.buffer_size());

    println!("getNumInputs: {}", dsp.getNumInputs());
    println!("getNumOutputs: {}", dsp.getNumOutputs());

    // Init DSP with a given SR
    dsp.init(client.sample_rate() as i32);

    // Register ports. They will be used in a callback that will be
    // called when new data is available.

    let in_a = client.register_port("in1", j::AudioInSpec::default()).unwrap();
    let in_b = client.register_port("in2", j::AudioInSpec::default()).unwrap();

    let mut out_a = client.register_port("out1", j::AudioOutSpec::default()).unwrap();
    let mut out_b = client.register_port("out2", j::AudioOutSpec::default()).unwrap();

    let process_callback = move |_: &j::Client, ps: &j::ProcessScope| -> j::JackControl {
        let mut out_a_p = j::AudioOutPort::new(&mut out_a, ps);
        let mut out_b_p = j::AudioOutPort::new(&mut out_b, ps);

        let in_a_p = j::AudioInPort::new(&in_a, ps);
        let in_b_p = j::AudioInPort::new(&in_b, ps);

        let input0: &[f32] = &in_a_p;
        let input1: &[f32] = &in_b_p;

        let output0: &mut[f32] = &mut out_a_p;
        let output1: &mut[f32] = &mut out_b_p;

        let inputs = &[input0, input1];
        let outputs = &mut[output0, output1];

        dsp.compute(in_a_p.len() as i32, inputs, outputs);

        j::JackControl::Continue
    };
    let process = j::ClosureProcessHandler::new(process_callback);

    // Activate the client, which starts the processing.
    let active_client = j::AsyncClient::new(client, (), process).unwrap();

    // Wait for user input to quit
    println!("Press enter/return to quit...");
    let mut user_input = String::new();
    io::stdin().read_line(&mut user_input).ok();

    active_client.deactivate().unwrap();
}
