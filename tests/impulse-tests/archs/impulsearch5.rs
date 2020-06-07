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

use std::marker::PhantomData;
use std::env;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;

pub trait Meta {

    // -- metadata declarations

    fn declare(&mut self, key: &str, value: &str) -> ();

}

pub trait UI<'a, T: 'a> {

    // -- widget's layouts

    fn openTabBox(&mut self, label: &str) -> ();
    fn openHorizontalBox(&mut self, label: &str) -> ();
    fn openVerticalBox(&mut self, label: &str) -> ();
    fn closeBox(&mut self) -> ();

    // -- active widgets

    fn addButton(&mut self, label: &str, zone: &'a mut T) -> ();
    fn addCheckButton(&mut self, label: &str, zone: &'a mut T) -> ();
    fn addVerticalSlider(&mut self, label: &str, zone: &'a mut T, init: T, min: T, max: T, step: T) -> ();
    fn addHorizontalSlider(&mut self, label: &str, zone: &'a mut T , init: T, min: T, max: T, step: T) -> ();
    fn addNumEntry(&mut self, label: &str, zone: &'a mut T, init: T, min: T, max: T, step: T) -> ();

    // -- passive widgets

    fn addHorizontalBargraph(&mut self, label: &str, zone: &'a mut T, min: T, max: T) -> ();
    fn addVerticalBargraph(&mut self, label: &str, zone: &'a mut T, min: T, max: T) -> ();

    // -- metadata declarations

    fn declare(&mut self, zone: &'a mut T, key: &str, value: &str) -> ();

}

pub struct PrintMeta {}

impl Meta for PrintMeta {

    fn declare(&mut self, key: &str, value: &str) -> ()
    {
        println!("declare: {} {}", key, value);
    }

}

/*******************************************************************************
* FUI : used to save and recall the state of the user interface
* This class provides essentially two new methods saveState() and recallState()
* used to save on file and recall from file the state of the user interface.
* The file is human readable and editable
******************************************************************************/

pub trait FUIHelper {

    fn pushGroupLabel(label: &str)  -> ();

}

pub struct FUI<'a, T: 'a>
{
    phantom: PhantomData<T>,
    fGroupStack: Vec<String>,
    fNameList: Vec<String>,
    fName2Zone: HashMap<String, &'a mut T>,
    fButtons: Vec<&'a mut T>
}

// Helpers functions

impl<'a, T> FUI<'a, T> {

    fn pushGroupLabel(&mut self, label: &str) -> ()
    {
        // TODO
        self.fGroupStack.push(label.to_string());
        self.fNameList.push(label.to_string());
    }

    fn addElement(&mut self, label: &str, zone: &'a mut T, button: bool) -> ()
    {
        // TODO
        self.fGroupStack.push(label.to_string());
        self.fNameList.push(label.to_string());
        self.fButtons.push(zone);
    }

}

impl<'a, T> UI<'a, T> for FUI<'a, T> {


    // -- widget's layouts

    fn openTabBox(&mut self, label: &str) -> ()
    {
        self.pushGroupLabel(label);
    }
    fn openHorizontalBox(&mut self, label: &str) -> ()
    {

    }
    fn openVerticalBox(&mut self, label: &str) -> ()
    {

    }
    fn closeBox(&mut self) -> ()
    {

    }

    // -- active widgets

    fn addButton(&mut self, label: &str, zone: &'a mut T) -> ()
    {

    }
    fn addCheckButton(&mut self, label: &str, zone: &'a mut T) -> ()
    {

    }
    fn addVerticalSlider(&mut self, label: &str, zone: &'a mut T, init: T, min: T, max: T, step: T) -> ()
    {

    }
    fn addHorizontalSlider(&mut self, label: &str, zone: &'a mut T , init: T, min: T, max: T, step: T) -> ()
    {

    }
    fn addNumEntry(&mut self, label: &str, zone: &'a mut T, init: T, min: T, max: T, step: T) -> ()
    {

    }

    // -- passive widgets

    fn addHorizontalBargraph(&mut self, label: &str, zone: &'a mut T, min: T, max: T) -> ()
    {

    }
    fn addVerticalBargraph(&mut self, label: &str, zone: &'a mut T, min: T, max: T) -> ()
    {

    }

    // -- metadata declarations

    fn declare(&mut self, zone: &'a mut T, key: &str, value: &str) -> ()
    {

    }
}

pub trait dsp<T> {

    //fn new() -> dsp<T>;

    fn getSampleRate(&mut self) -> i32;

    fn getNumInputs(&mut self) -> i32;

    fn getNumOutputs(&mut self) -> i32;

    fn getInputRate(&mut self, channel: i32) -> i32;

    fn getOutputRate(&mut self, channel: i32) -> i32;

    fn buildUserInterface(&mut self, ui_interface: &mut UI<T>) -> ();

    fn classInit(samplingFreq: i32) -> ();

    fn instanceResetUserInterface(&mut self) -> ();

    fn instanceClear(&mut self) -> ();

    fn instanceConstants(&mut self, samplingFreq: i32) -> ();

    fn instanceInit(&mut self, samplingFreq: i32) -> ();

    fn init(&mut self, samplingFreq: i32) -> ();

    fn compute(&mut self, count: i32, inputs: &[&[T]], outputs: &mut[&mut[T]]) -> ();

}

<<includeIntrinsic>>
<<includeclass>>

fn main() {

    println!("Faust Rust DSP");

    let mut dsp = Box::new(mydsp::new());

    println!("getNumInputs: {}", dsp.getNumInputs());
    println!("getNumOutputs: {}", dsp.getNumOutputs());

    // Init DSP with a given SR
    dsp.init(44100);

    // Print UI
    let mut fui = FUI::<f32> {
        phantom: PhantomData,
        fGroupStack: Vec::new(),
        fNameList: Vec::new(),
        fName2Zone: HashMap::new(),
        fButtons: Vec::new()
    };

    dsp.buildUserInterface(&mut fui);

    // Print Meta
    let mut meta = PrintMeta{};
    dsp.metadata(&mut meta);

    println!("getSampleRate: {}", dsp.getSampleRate());
}
