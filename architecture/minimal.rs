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
#![allow(dead_code)]
#![allow(unused_variables)]
#![allow(unused_mut)]
#![allow(non_upper_case_globals)]

extern crate libm;
extern crate num_traits;

use std::fs::File;
use std::io::Write;
use std::env;

use num_traits::{cast::FromPrimitive, float::Float};

pub trait FaustDsp {
    type Sample;

    fn new() -> Self where Self: Sized;
    fn metadata(&mut self, m: &mut dyn Meta);
    fn get_sample_rate(&mut self) -> i32;
    fn get_num_inputs(&mut self) -> i32;
    fn get_num_outputs(&mut self) -> i32;
    fn get_input_rate(&mut self, channel: i32) -> i32;
    fn get_output_rate(&mut self, channel: i32) -> i32;
    fn class_init(sample_rate: i32) where Self: Sized;
    fn instance_reset_user_interface(&mut self);
    fn instance_clear(&mut self);
    fn instance_constants(&mut self, sample_rate: i32);
    fn instance_init(&mut self, sample_rate: i32);
    fn init(&mut self, sample_rate: i32);
    fn build_user_interface(&mut self, ui_interface: &mut dyn UI<Self::Sample>);
    fn compute(&mut self, count: i32, inputs: &[&[Self::Sample]], outputs: &mut[&mut[Self::Sample]]);
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
    fn add_button(&mut self, label: &str, zone: &mut T);
    fn add_check_button(&mut self, label: &str, zone: &mut T);
    fn add_vertical_slider(&mut self, label: &str, zone: &mut T, init: T, min: T, max: T, step: T);
    fn add_horizontal_slider(&mut self, label: &str, zone: &mut T , init: T, min: T, max: T, step: T);
    fn add_num_entry(&mut self, label: &str, zone: &mut T, init: T, min: T, max: T, step: T);

    // -- passive widgets
    fn add_horizontal_bargraph(&mut self, label: &str, zone: &mut T, min: T, max: T);
    fn add_vertical_bargraph(&mut self, label: &str, zone: &mut T, min: T, max: T);

    // -- metadata declarations
    fn declare(&mut self, zone: &mut T, key: &str, value: &str);
}

pub struct PrintMeta {}

impl Meta for PrintMeta {

    fn declare(&mut self, key: &str, value: &str) -> ()
    {
        println!("declare: {} {}", key, value);
    }

}

pub struct PrintUI<T>
{
    phantom: PhantomData<T>
}

impl<T> UI<T> for PrintUI<T> {

    // -- widget's layouts

    fn openTabBox(&mut self, label: &str) -> ()
    {
        println!("openTabBox: {}", label);
    }
    fn openHorizontalBox(&mut self, label: &str) -> ()
    {
        println!("openHorizontalBox: {}", label);
    }
    fn openVerticalBox(&mut self, label: &str) -> ()
    {
        println!("openVerticalBox: {}", label);
    }
    fn closeBox(&mut self) -> ()
    {
        println!("closeBox:");
    }

    // -- active widgets

    fn addButton(&mut self, label: &str, zone: &mut T) -> ()
    {
        println!("addButton: {}", label);
    }
    fn addCheckButton(&mut self, label: &str, zone: &mut T) -> ()
    {
        println!("addCheckButton: {}", label);
    }
    fn addVerticalSlider(&mut self, label: &str, zone: &mut T, init: T, min: T, max: T, step: T) -> ()
    {
        println!("addVerticalSlider: {}", label);
    }
    fn addHorizontalSlider(&mut self, label: &str, zone: &mut T , init: T, min: T, max: T, step: T) -> ()
    {
        println!("addHorizontalSlider: {}", label);
    }
    fn addNumEntry(&mut self, label: &str, zone: &mut T, init: T, min: T, max: T, step: T) -> ()
    {
        println!("addNumEntry: {}", label);
    }

    // -- passive widgets

    fn addHorizontalBargraph(&mut self, label: &str, zone: &mut T, min: T, max: T) -> ()
    {
        println!("addHorizontalBargraph: {}", label);
    }
    fn addVerticalBargraph(&mut self, label: &str, zone: &mut T, min: T, max: T) -> ()
    {
        println!("addVerticalBargraph: {}", label);
    }

    // -- metadata declarations

    fn declare(&mut self, zone: &mut T, key: &str, value: &str) -> ()
    {
        println!("declare: {} {}", key, value);
    }
}

<<includeIntrinsic>>
<<includeclass>>

fn main() {

    println!("Faust Rust DSP");

    let mut dsp = Box::new(mydsp::new());

    println!("get_num_inputs: {}", dsp.get_num_inputs());
    println!("get_num_outputs: {}", dsp.get_num_outputs());

    // Init DSP with a given SR
    dsp.init(44100);

    // Print UI
    let mut printer = PrintUI::<f32>{ phantom: PhantomData };
    dsp.buildUserInterface(&mut printer);

    // Print Meta
    let mut meta = PrintMeta{};
    dsp.metadata(&mut meta);

    println!("get_sample_rate: {}", dsp.get_sample_rate());

    // Has to be done in the audio thread taking adapted "native" (JACK/PortAudio allocated...) audio buffers
    // dsp.compute(512, inputs, outputs);
}
