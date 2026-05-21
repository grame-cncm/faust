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

//! Faust JACK architecture file
extern crate jack;
use jack::prelude as j;
use std::io;
extern crate libm;

type F32 = f32;
type F64 = f64;
type FaustFloat = F32;

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

#[cfg_attr(feature = "default-boxed", derive(default_boxed::DefaultBoxed))]
<<includeIntrinsic>>
<<includeclass>>

fn main() {

    // Create JACK client
    let (client, _status) = j::Client::new("faust_rust", j::client_options::NO_START_SERVER).unwrap();

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

    println!("Faust Rust code running with JACK: sample-rate = {} buffer-size = {}", client.sample_rate(), client.buffer_size());

    let num_inputs = dsp.get_num_inputs() as usize;
    let num_outputs = dsp.get_num_outputs() as usize;
    println!("get_num_inputs: {}", num_inputs);
    println!("get_num_outputs: {}", num_outputs);

    // Init DSP with a given SR
    dsp.init(client.sample_rate() as i32);

    // Register N input and M output ports based on the DSP's declared
    // channel counts. The previous version of this arch file hard-coded
    // 2x2, which made any other channel layout panic with "wrong number
    // of input/output buffers" inside dsp.compute().
    let in_ports: Vec<j::Port<j::AudioInSpec>> = (0..num_inputs)
        .map(|i| client.register_port(&format!("in{}", i + 1), j::AudioInSpec::default()).unwrap())
        .collect();

    let mut out_ports: Vec<j::Port<j::AudioOutSpec>> = (0..num_outputs)
        .map(|i| client.register_port(&format!("out{}", i + 1), j::AudioOutSpec::default()).unwrap())
        .collect();

    let process_callback = move |_: &j::Client, ps: &j::ProcessScope| -> j::JackControl {
        // Build the AudioIn/OutPort views into this ProcessScope.
        let in_views: Vec<j::AudioInPort> =
            in_ports.iter().map(|p| j::AudioInPort::new(p, ps)).collect();
        let mut out_views: Vec<j::AudioOutPort> =
            out_ports.iter_mut().map(|p| j::AudioOutPort::new(p, ps)).collect();

        // Collect the &[f32] / &mut[f32] handles dsp.compute wants.
        let inputs: Vec<&[f32]> = in_views.iter().map(|v| &**v).collect();
        let mut outputs: Vec<&mut [f32]> =
            out_views.iter_mut().map(|v| &mut **v).collect();

        // Determine the frame count: outputs first (always present if M>0),
        // then inputs, then fall back to the scope's reported buffer size
        // (covers the 0-in 0-out generator-style edge case). Faust-generated
        // mydsp.compute takes a `usize`, not the `i32` the FaustDsp trait
        // declares above — the trait is essentially documentation.
        let n_frames: usize = if let Some(o) = outputs.first() {
            o.len()
        } else if let Some(i) = inputs.first() {
            i.len()
        } else {
            ps.n_frames() as usize
        };

        dsp.compute(n_frames, &inputs, &mut outputs);

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
