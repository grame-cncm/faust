/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2024 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#![allow(unused_parens)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]
#![allow(unused_variables)]
#![allow(unused_mut)]
#![allow(non_upper_case_globals)]

//! PortAudio architecture file
extern crate portaudio;
use portaudio as pa;
use std::io;
extern crate libm;

type F32 = f32;
type F64 = f64;

#[derive(Copy, Clone)]
pub struct ParamIndex(pub i32);

pub struct Soundfile<'a,T> {
    fBuffers: &'a&'a T,
    fLength: &'a i32,
    fSR: &'a i32,
    fOffset: &'a i32,
    fChannels: i32
}

pub trait FaustDsp {
    type T;

    fn new() -> Self where Self: Sized;
    fn metadata(&self, m: &mut dyn Meta);
    fn get_sample_rate(&self) -> i32;
    fn get_num_inputs(&self) -> i32;
    fn get_num_outputs(&self) -> i32;
    fn class_init(sample_rate: i32) where Self: Sized;
    fn instance_reset_params(&mut self);
    fn instance_clear(&mut self);
    fn instance_constants(&mut self, sample_rate: i32);
    fn instance_init(&mut self, sample_rate: i32);
    fn init(&mut self, sample_rate: i32);
    fn build_user_interface(&self, ui_interface: &mut dyn UI<Self::T>);
    fn build_user_interface_static(ui_interface: &mut dyn UI<Self::T>) where Self: Sized;
    fn get_param(&self, param: ParamIndex) -> Option<Self::T>;
    fn set_param(&mut self, param: ParamIndex, value: Self::T);
    fn compute(&mut self, count: i32, inputs: &[&[Self::T]], outputs: &mut[&mut[Self::T]]);
}

pub trait Meta {
    // -- metadata declarations
    fn declare(&mut self, key: &str, value: &str);
}

pub trait UI<T> {
    // -- widget's layouts
    fn open_tab_box(&mut self, label: &str);
    fn open_horizontal_box(&mut self, label: &str);
    fn open_vertical_box(&mut self, label: &str);
    fn close_box(&mut self);

    // -- active widgets
    fn add_button(&mut self, label: &str, param: ParamIndex);
    fn add_check_button(&mut self, label: &str, param: ParamIndex);
    fn add_vertical_slider(&mut self, label: &str, param: ParamIndex, init: T, min: T, max: T, step: T);
    fn add_horizontal_slider(&mut self, label: &str, param: ParamIndex, init: T, min: T, max: T, step: T);
    fn add_num_entry(&mut self, label: &str, param: ParamIndex, init: T, min: T, max: T, step: T);

    // -- passive widgets
    fn add_horizontal_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T);
    fn add_vertical_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T);

    // -- metadata declarations
    fn declare(&mut self, param: Option<ParamIndex>, key: &str, value: &str);
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

    let pa = pa::PortAudio::new()?;

    // Allocation DSP on the heap
    let mut dsp;
    #[cfg(feature = "default-boxed")]
    {
        use default_boxed::DefaultBoxed;
        dsp = mydsp::default_boxed();
    }

    #[cfg(not(feature = "default-boxed"))]
    {
        dsp = Box::new(mydsp::new());
    }

    println!("Faust Rust code running with Portaudio: sample-rate = {} buffer-size = {}", SAMPLE_RATE, FRAMES_PER_BUFFER);

    //Create a input/output stream with the same number of input and output channels
    const INTERLEAVED: bool = false;// We want NON interleaved streams
    let input_device = pa.default_input_device()?;
    let output_device = pa.default_output_device()?;
    let input_latency = pa.device_info(input_device)?.default_low_input_latency;
    let output_latency = pa.device_info(output_device)?.default_low_input_latency;

    let in_params = pa::StreamParameters::new(input_device, CHANNELS, INTERLEAVED, input_latency);
    let out_params = pa::StreamParameters::new(output_device, CHANNELS, INTERLEAVED, output_latency);
    let settings = pa::DuplexStreamSettings::new(in_params, out_params, SAMPLE_RATE, FRAMES_PER_BUFFER);
    
    // This would have been interleaved:
    // let mut settings = try!(pa.default_duplex_stream_settings(CHANNELS, CHANNELS, SAMPLE_RATE, FRAMES_PER_BUFFER));

    println!("get_num_inputs: {}", dsp.get_num_inputs());
    println!("get_num_outputs: {}", dsp.get_num_outputs());

    // Init DSP with a given SR
    dsp.init(SAMPLE_RATE as i32);

    //settings.flags = pa::stream_flags::CLIP_OFF;

    // This routine will be called by the PortAudio engine when audio is needed. It may called at
    // interrupt level on some machines so don't do anything that could mess up the system like
    // dynamic resource allocation or IO.
    let callback = move |pa::DuplexStreamCallbackArgs { in_buffer, out_buffer, frames, time, .. } : pa::DuplexStreamCallbackArgs<f32, f32>| {
        let out_buffr: &mut [*mut f32];
        let in_buffr: & [*const f32];
        // rust-portaudio does not support non-interleaved audio out of the box (but portaudio does)
        unsafe {

            let in_buffer: *const *const f32 = ::std::mem::transmute(in_buffer.get_unchecked(0));
            in_buffr = ::std::slice::from_raw_parts(in_buffer, CHANNELS as usize);
            let input0 = ::std::slice::from_raw_parts(in_buffr[0], frames);
            let input1 = ::std::slice::from_raw_parts(in_buffr[1], frames);

            let input0_f64: Vec<f64> = input0.iter().map(|&sample| sample as f64).collect();
            let input1_f64: Vec<f64> = input1.iter().map(|&sample| sample as f64).collect();    
         
            let inputs_f64: [&[f64]; 2] = [&input0_f64[..], &input1_f64[..]];
            let inputs_ref: &[&[f64]] = &inputs_f64;

            // Prepare f64 outputs
            let mut output0_f64: Vec<f64> = vec![0.0; frames];
            let mut output1_f64: Vec<f64> = vec![0.0; frames];
    
            let mut outputs_f64: [&mut [f64]; 2] = [&mut output0_f64[..], &mut output1_f64[..]];
            let outputs_ref: &mut [&mut [f64]] = &mut outputs_f64;
    
            // Compute using f64 inputs and outputs
            dsp.compute(frames as usize, inputs_ref, outputs_ref);
    
            let out_buffer: *mut *mut f32 = ::std::mem::transmute(out_buffer.get_unchecked_mut(0));
            out_buffr = ::std::slice::from_raw_parts_mut(out_buffer, CHANNELS as usize);
            let output0 = ::std::slice::from_raw_parts_mut(out_buffr[0], frames);
            let output1 = ::std::slice::from_raw_parts_mut(out_buffr[1], frames);
  
            // Copy and convert outputs_ref[0] (f64) to output0 (f32)
            for (dest, &src) in output0.iter_mut().zip(outputs_ref[0].iter()) {
                *dest = src as f32;
            }
             for (dest, &src) in output1.iter_mut().zip(outputs_ref[1].iter()) {
                *dest = src as f32;
            }
        }
        pa::Continue
    };

    let mut stream = pa.open_non_blocking_stream(settings, callback)?;

    stream.start()?;

    // Wait for user input to quit
    println!("Press enter/return to quit...");
    let mut user_input = String::new();
    io::stdin().read_line(&mut user_input).ok();

    stream.stop()?;
    stream.close()?;

    Ok(())
}
