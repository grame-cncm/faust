
#![allow(unused_parens)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]

use std::marker::PhantomData;

pub trait Meta {

    // -- metadata declarations

    fn declare(&self, key: &'static str, value: &'static str) -> ();

}

pub trait UI<T> {

    // -- widget's layouts

    fn openTabBox(&self, label: &'static str) -> ();
    fn openHorizontalBox(&self, label: &'static str) -> ();
    fn openVerticalBox(&self, label: &'static str) -> ();
    fn closeBox(&self) -> ();

    // -- active widgets

    fn addButton(&self, label: &'static str, zone: &T) -> ();
    fn addCheckButton(&self, label: &'static str, zone: &T) -> ();
    fn addVerticalSlider(&self, label: &'static str, zone: &T, init: T, min: T, max: T, step: T) -> ();
    fn addHorizontalSlider(&self, label: &'static str, zone: &T , init: T, min: T, max: T, step: T) -> ();
    fn addNumEntry(&self, label: &'static str, zone: &T, init: T, min: T, max: T, step: T) -> ();

    // -- passive widgets

    fn addHorizontalBargraph(&self, label: &'static str, zone: &T, min: T, max: T) -> ();
    fn addVerticalBargraph(&self, label: &'static str, zone: &T, min: T, max: T) -> ();

    // -- metadata declarations

    fn declare(&self, zone: &T, key: &'static str, value: &'static str) -> ();

}

pub struct PrintMeta {}

impl Meta for PrintMeta {

    fn declare(&self, key: &'static str, value: &'static str) -> ()
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

    fn openTabBox(&self, label: &'static str) -> ()
    {
        println!("openTabBox: {}", label);
    }
    fn openHorizontalBox(&self, label: &'static str) -> ()
    {
        println!("openHorizontalBox: {}", label);
    }
    fn openVerticalBox(&self, label: &'static str) -> ()
    {
        println!("openVerticalBox: {}", label);
    }
    fn closeBox(&self) -> ()
    {
        println!("closeBox:");
    }

    // -- active widgets

    fn addButton(&self, label: &'static str, zone: &T) -> ()
    {
        println!("addButton: {}", label);
    }
    fn addCheckButton(&self, label: &'static str, zone: &T) -> ()
    {
        println!("addCheckButton: {}", label);
    }
    fn addVerticalSlider(&self, label: &'static str, zone: &T, init: T, min: T, max: T, step: T) -> ()
    {
        println!("addVerticalSlider: {}", label);
    }
    fn addHorizontalSlider(&self, label: &'static str, zone: &T , init: T, min: T, max: T, step: T) -> ()
    {
        println!("addHorizontalSlider: {}", label);
    }
    fn addNumEntry(&self, label: &'static str, zone: &T, init: T, min: T, max: T, step: T) -> ()
    {
        println!("addNumEntry: {}", label);
    }

    // -- passive widgets

    fn addHorizontalBargraph(&self, label: &'static str, zone: &T, min: T, max: T) -> ()
    {
        println!("addHorizontalBargraph: {}", label);
    }
    fn addVerticalBargraph(&self, label: &'static str, zone: &T, min: T, max: T) -> ()
    {
        println!("addVerticalBargraph: {}", label);
    }

    // -- metadata declarations

    fn declare(&self, zone: &T, key: &'static str, value: &'static str) -> ()
    {
        println!("declare: {} {}", key, value);
    }
}

pub trait dsp<T> {

    //fn new() -> dsp<T>;

    fn getSampleRate(&mut self) -> i32;

    fn getNumInputs(&mut self) -> i32;

    fn getNumOutputs(&mut self) -> i32;

    fn getInputRate(&mut self, channel: i32) -> i32;

    fn getOutputRate(&mut self, channel: i32) -> i32;

    fn buildUserInterface(&mut self, ui_interface: &UI<T>) -> ();

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

    let mut dsp = mydsp::new();

    println!("getNumInputs: {}", dsp.getNumInputs());
    println!("getNumOutputs: {}", dsp.getNumOutputs());

    // Init DSP with a given SR
    dsp.init(44100);

    // Print UI
    let printer = PrintUI::<f32>{ phantom: PhantomData };
    dsp.buildUserInterface(&printer);

    // Print Meta
    let meta = PrintMeta{};
    dsp.metadata(&meta);

    println!("getSampleRate: {}", dsp.getSampleRate());

    // Has to be done in the audio thread taking adapted "native" (JACK/PortAudio allocated...) audio buffers
    // dsp.compute(512, inputs, outputs);
}
