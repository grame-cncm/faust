/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

extern crate libm;
extern crate num_traits;

use std::fs::File;
use std::io::Write;
use std::env;
use std::marker::PhantomData;

use num_traits::{cast::FromPrimitive, float::Float};

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
    fn add_horizontal_slider(&mut self, label: &str, param: ParamIndex , init: T, min: T, max: T, step: T);
    fn add_num_entry(&mut self, label: &str, param: ParamIndex, init: T, min: T, max: T, step: T);

    // -- passive widgets
    fn add_horizontal_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T);
    fn add_vertical_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T);

    // -- metadata declarations
    fn declare(&mut self, param: Option<ParamIndex>, key: &str, value: &str);
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

    fn open_tab_box(&mut self, label: &str) -> ()
    {
        println!("openTabBox: {}", label);
    }
    fn open_horizontal_box(&mut self, label: &str) -> ()
    {
        println!("openHorizontalBox: {}", label);
    }
    fn open_vertical_box(&mut self, label: &str) -> ()
    {
        println!("openVerticalBox: {}", label);
    }
    fn close_box(&mut self) -> ()
    {
        println!("closeBox:");
    }

    // -- active widgets

    fn add_button(&mut self, label: &str, param: ParamIndex) -> ()
    {
        println!("addButton: {}", label);
    }
    fn add_check_button(&mut self, label: &str, param: ParamIndex) -> ()
    {
        println!("addCheckButton: {}", label);
    }
    fn add_vertical_slider(&mut self, label: &str, param: ParamIndex, init: T, min: T, max: T, step: T) -> ()
    {
        println!("addVerticalSlider: {}", label);
    }
    fn add_horizontal_slider(&mut self, label: &str, param: ParamIndex , init: T, min: T, max: T, step: T) -> ()
    {
        println!("addHorizontalSlider: {}", label);
    }
    fn add_num_entry(&mut self, label: &str, param: ParamIndex, init: T, min: T, max: T, step: T) -> ()
    {
        println!("addNumEntry: {}", label);
    }

    // -- passive widgets

    fn add_horizontal_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T) -> ()
    {
        println!("addHorizontalBargraph: {}", label);
    }
    fn add_vertical_bargraph(&mut self, label: &str, param: ParamIndex, min: T, max: T) -> ()
    {
        println!("addVerticalBargraph: {}", label);
    }

    // -- metadata declarations

    fn declare(&mut self, param: Option<ParamIndex>, key: &str, value: &str) -> ()
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
    dsp.build_user_interface(&mut printer);

    // Print Meta
    let mut meta = PrintMeta{};
    dsp.metadata(&mut meta);

    println!("get_sample_rate: {}", dsp.get_sample_rate());

    // Has to be done in the audio thread taking adapted "native" (JACK/PortAudio allocated...) audio buffers
    // dsp.compute(512, inputs, outputs);
}
