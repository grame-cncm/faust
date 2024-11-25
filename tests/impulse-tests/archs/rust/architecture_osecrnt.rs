/************************************************************************
************************************************************************
FAUST Architecture File
Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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
#![allow(dead_code)]
#![allow(unused_variables)]
#![allow(unused_mut)]
#![allow(non_upper_case_globals)]
#![recursion_limit = "256"]

extern crate libm;
extern crate num_traits;
/* extern crate fastfloat; */

use default_boxed::DefaultBoxed;
use num_traits::cast::FromPrimitive;
use num_traits::float::Float;
use std::convert::TryInto;
use std::env;
use std::fs::File;
use std::io::Write;

type F32 = f32;
type F64 = f64;

/*
type F32 = Fast<f32>;
type F64 = Fast<f64>;
*/

#[derive(Copy, Clone)]
pub struct ParamIndex(i32);

pub struct Soundfile<'a> {
    fBuffers: &'a &'a F32,
    fLength: &'a i32,
    fSR: &'a i32,
    fOffset: &'a i32,
    fChannels: i32,
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
    fn add_vertical_slider(
        &mut self,
        label: &str,
        param: ParamIndex,
        init: T,
        min: T,
        max: T,
        step: T,
    );
    fn add_horizontal_slider(
        &mut self,
        label: &str,
        param: ParamIndex,
        init: T,
        min: T,
        max: T,
        step: T,
    );
    fn add_num_entry(&mut self, label: &str, param: ParamIndex, init: T, min: T, max: T, step: T);

    // -- passive widgets
    fn add_horizontal_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T);
    fn add_vertical_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T);

    // -- metadata declarations
    fn declare(&mut self, param: Option<ParamIndex>, key: &str, value: &str);
}

pub struct ButtonUI {
    all_button_params: Vec<ParamIndex>,
}

impl ButtonUI {
    fn set_button_parameters_to(&self, dsp: &mut Box<mydsp>, value: f64) {
        for button_param in &self.all_button_params {
            dsp.set_param(*button_param, value);
        }
    }
}

impl<T: Float + FromPrimitive> UI<T> for ButtonUI {
    // -- widget's layouts
    fn open_tab_box(&mut self, label: &str) {}
    fn open_horizontal_box(&mut self, label: &str) {}
    fn open_vertical_box(&mut self, label: &str) {}
    fn close_box(&mut self) {}

    // -- active widgets
    fn add_button(&mut self, label: &str, param: ParamIndex) {
        self.all_button_params.push(param);
    }
    fn add_check_button(&mut self, label: &str, param: ParamIndex) {}
    fn add_vertical_slider(
        &mut self,
        label: &str,
        param: ParamIndex,
        init: T,
        min: T,
        max: T,
        step: T,
    ) {
    }
    fn add_horizontal_slider(
        &mut self,
        label: &str,
        param: ParamIndex,
        init: T,
        min: T,
        max: T,
        step: T,
    ) {
    }
    fn add_num_entry(&mut self, label: &str, param: ParamIndex, init: T, min: T, max: T, step: T) {}

    // -- passive widgets
    fn add_horizontal_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T) {}
    fn add_vertical_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T) {}

    // -- metadata declarations
    fn declare(&mut self, param: Option<ParamIndex>, key: &str, value: &str) {}
}

// Generated intrinsics:
<<includeIntrinsic>>

// Generated class:
<<includeclass>>

const SAMPLE_RATE: i32 = 44100;

fn print_header(mut dsp: Box<mydsp>, num_total_samples: usize, output_file: &mut File) {
    dsp.init(SAMPLE_RATE);
    writeln!(output_file, "number_of_inputs  : {}", FAUST_INPUTS).unwrap();
    writeln!(output_file, "number_of_outputs : {}", FAUST_OUTPUTS).unwrap();
    writeln!(output_file, "number_of_frames  : {}", num_total_samples).unwrap();
}

fn run_dsp(
    mut dsp: Box<mydsp>,
    num_samples: usize,
    line_num_offset: usize,
    output_file: &mut File,
) {
    // Generation constants
    let buffer_size = 64usize;

    // Init dsp
    dsp.init(SAMPLE_RATE);

    // Prepare buffers
    let mut in_buffer = vec![vec![0 as FaustFloat; buffer_size]; FAUST_INPUTS];
    let mut out_buffer = vec![vec![0 as FaustFloat; buffer_size]; FAUST_OUTPUTS];

    // Prepare UI
    let mut ui = ButtonUI {
        all_button_params: Vec::new(),
    };
    dsp.build_user_interface(&mut ui);

    // Compute
    let mut cycle = 0;
    let mut num_samples_written = 0;
    while num_samples_written < num_samples {
        let buffer_size = buffer_size.min(num_samples - num_samples_written);

        // handle inputs
        for c in 0..FAUST_INPUTS {
            for j in 0..buffer_size {
                let first_frame = num_samples_written == 0 && j == 0;
                in_buffer[c][j] = if first_frame { 1.0 } else { 0.0 };
            }
        }

        // Set button state
        if cycle == 0 {
            ui.set_button_parameters_to(&mut dsp, 1.0);
        } else {
            ui.set_button_parameters_to(&mut dsp, 0.0);
        }

        dsp.control();
        for i in 0..buffer_size {
            dsp.frame(
                in_buffer
                    .iter()
                    .map(|buffer| &buffer[i])
                    .collect::<Vec<&FaustFloat>>()
                    .split_at(FAUST_INPUTS)
                    .0
                    .try_into()
                    .expect("too few input buffers"),
                out_buffer
                    .iter_mut()
                    .map(|buffer| &mut buffer[i])
                    .collect::<Vec<&mut FaustFloat>>()
                    .split_at_mut(FAUST_OUTPUTS)
                    .0
                    .try_into()
                    .expect("too few output buffers"),
            );
        }
        // handle outputs
        for j in 0..buffer_size {
            write!(output_file, "{:6} :", num_samples_written + line_num_offset).unwrap();
            for c in 0..FAUST_OUTPUTS {
                write!(output_file, " {:8.6}", out_buffer[c][j]).unwrap();
            }
            writeln!(output_file).unwrap();
            num_samples_written += 1;
        }

        cycle = cycle + 1;
    }
}

fn main() {
    let num_total_samples = 60000;

    let block_size = num_total_samples / 4;

    // Open output file
    let output_file_name = env::args()
        .nth(1)
        .expect("ERROR: Output file name expected.");
    let mut output_file = File::create(output_file_name).expect("Cannot create output file");

    print_header(mydsp::default_boxed(), num_total_samples, &mut output_file);

    run_dsp(mydsp::default_boxed(), block_size, 0, &mut output_file);
}
