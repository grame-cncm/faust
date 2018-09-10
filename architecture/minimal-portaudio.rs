/************************************************************************
************************************************************************
    FAUST Architecture File
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------

    This is sample code. This file is provided as an example of minimal
    FAUST architecture file. Redistribution and use in source and binary
    forms, with or without modification, in part or in full are permitted.
    In particular you can create a derived work of this FAUST architecture
    and distribute that work under terms of your choice.

    This sample code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
************************************************************************
************************************************************************/

#![allow(unused_parens)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]

//! Portaudio architecture file
extern crate portaudio;
use portaudio as pa;
use std::io;

pub trait Meta {

    // -- metadata declarations

    fn declare(&mut self, key: &str, value: &str) -> ();

}

pub trait UI<T> {

    // -- widget's layouts

    fn openTabBox(&mut self, label: &str) -> ();
    fn openHorizontalBox(&mut self, label: &str) -> ();
    fn openVerticalBox(&mut self, label: &str) -> ();
    fn closeBox(&mut self) -> ();

    // -- active widgets

    fn addButton(&mut self, label: &str, zone: &mut T) -> ();
    fn addCheckButton(&mut self, label: &str, zone: &mut T) -> ();
    fn addVerticalSlider(&mut self, label: &str, zone: &mut T, init: T, min: T, max: T, step: T) -> ();
    fn addHorizontalSlider(&mut self, label: &str, zone: &mut T , init: T, min: T, max: T, step: T) -> ();
    fn addNumEntry(&mut self, label: &str, zone: &mut T, init: T, min: T, max: T, step: T) -> ();

    // -- passive widgets

    fn addHorizontalBargraph(&mut self, label: &str, zone: &mut T, min: T, max: T) -> ();
    fn addVerticalBargraph(&mut self, label: &str, zone: &mut T, min: T, max: T) -> ();

    // -- metadata declarations

    fn declare(&mut self, zone: &mut T, key: &str, value: &str) -> ();

}

<<includeIntrinsic>>
<<includeclass>>

const CHANNELS: i32 = 2;
const SAMPLE_RATE: f64 = 44_100.0;
const FRAMES_PER_BUFFER: u32 = 64;


fn main() {
    run().unwrap()
}

fn run() -> Result<(), pa::Error> {


    let pa = try!(pa::PortAudio::new());

    // Allocation DSP on the heap
    let mut dsp = Box::new(mydsp::new());

    println!("Faust Rust code running with Portaudio: sample-rate = {} buffer-size = {}", SAMPLE_RATE, FRAMES_PER_BUFFER);

    //Create a input/output stream with the same number of input and output channels
    const INTERLEAVED: bool = false;// We want NON interleaved streams
    let input_device = try!(pa.default_input_device());
    let output_device = try!(pa.default_output_device());
    let input_latency = try!(pa.device_info(input_device)).default_low_input_latency;
    let output_latency = try!(pa.device_info(output_device)).default_low_input_latency;

    let in_params = pa::StreamParameters::new(input_device, CHANNELS, INTERLEAVED, input_latency);
    let out_params = pa::StreamParameters::new(output_device, CHANNELS, INTERLEAVED, output_latency);
    let settings = pa::DuplexStreamSettings::new(in_params, out_params, SAMPLE_RATE, FRAMES_PER_BUFFER);
    //This would have been interleaved:
    //let mut settings = try!(pa.default_duplex_stream_settings(CHANNELS, CHANNELS, SAMPLE_RATE, FRAMES_PER_BUFFER));

    println!("getNumInputs: {}", dsp.getNumInputs());
    println!("getNumOutputs: {}", dsp.getNumOutputs());

    // Init DSP with a given SR
    dsp.init(SAMPLE_RATE as i32);


    //settings.flags = pa::stream_flags::CLIP_OFF;

    // This routine will be called by the PortAudio engine when audio is needed. It may called at
    // interrupt level on some machines so don't do anything that could mess up the system like
    // dynamic resource allocation or IO.
    let callback = move |pa::DuplexStreamCallbackArgs { in_buffer, out_buffer, frames, time, .. } : pa::DuplexStreamCallbackArgs<f32, f32>| {
        let out_buffr: &mut [*mut f32];
        let in_buffr: & [*const f32];
        //rust-portaudio does not support non-interleaved audio out of the box (but portaudio does)
        unsafe {
            let out_buffer: *mut *mut f32 = ::std::mem::transmute(out_buffer.get_unchecked_mut(0));
            out_buffr = ::std::slice::from_raw_parts_mut(out_buffer, CHANNELS as usize);
            let output0 = ::std::slice::from_raw_parts_mut(out_buffr[0], frames);
            let output1 = ::std::slice::from_raw_parts_mut(out_buffr[1], frames);

            let in_buffer: *const *const f32 = ::std::mem::transmute(in_buffer.get_unchecked(0));
            in_buffr = ::std::slice::from_raw_parts(in_buffer, CHANNELS as usize);
            let input0 = ::std::slice::from_raw_parts(in_buffr[0], frames);
            let input1 = ::std::slice::from_raw_parts(in_buffr[1], frames);

            let inputs = &[input0, input1];
            let outputs = &mut [output0, output1];

            dsp.compute(frames as i32, inputs, outputs);
        }
        pa::Continue
    };

    let mut stream = try!(pa.open_non_blocking_stream(settings, callback));

    try!(stream.start());

    // Wait for user input to quit
    println!("Press enter/return to quit...");
    let mut user_input = String::new();
    io::stdin().read_line(&mut user_input).ok();

    try!(stream.stop());
    try!(stream.close());

    Ok(())
}
