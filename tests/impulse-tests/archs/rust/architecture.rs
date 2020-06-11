#![allow(unused_parens)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]
#![allow(unused_variables)]
#![allow(unused_mut)]
#![allow(non_upper_case_globals)]
#![allow(bare_trait_objects)]

extern crate libm;
extern crate num_traits;

use std::fs::File;
use std::io::Write;
use std::env;

use num_traits::{cast::FromPrimitive, float::Float};

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

pub struct ButtonUI<T>
{
    fState: T
}

impl<T: Float + FromPrimitive> UI<T> for ButtonUI<T>
{
    // -- widget's layouts
    fn openTabBox(&mut self, label: &str) -> ()
    {}
    fn openHorizontalBox(&mut self, label: &str) -> ()
    {}
    fn openVerticalBox(&mut self, label: &str) -> ()
    {}
    fn closeBox(&mut self) -> ()
    {}

    // -- active widgets
    fn addButton(&mut self, label: &str, zone: &mut T) -> ()
    {
        //println!("addButton: {}", label);
        *zone = self.fState;
    }
    fn addCheckButton(&mut self, label: &str, zone: &mut T) -> ()
    {}
    fn addVerticalSlider(&mut self, label: &str, zone: &mut T, init: T, min: T, max: T, step: T) -> ()
    {}
    fn addHorizontalSlider(&mut self, label: &str, zone: &mut T , init: T, min: T, max: T, step: T) -> ()
    {}
    fn addNumEntry(&mut self, label: &str, zone: &mut T, init: T, min: T, max: T, step: T) -> ()
    {}

    // -- passive widgets
    fn addHorizontalBargraph(&mut self, label: &str, zone: &mut T, min: T, max: T) -> ()
    {}
    fn addVerticalBargraph(&mut self, label: &str, zone: &mut T, min: T, max: T) -> ()
    {}

    // -- metadata declarations
    fn declare(&mut self, zone: &mut T, key: &str, value: &str) -> ()
    {}
}

// Generated intrinsics:
<<includeIntrinsic>>

// Generated class:
<<includeclass>>

const SAMPLE_RATE: i32 = 44100;

type FloatType = f64;

fn print_header(output_file: &mut File, num_total_samples: usize) {
    let mut dsp = Box::new(mydsp::new());
    dsp.init(SAMPLE_RATE);
    writeln!(output_file, "number_of_inputs  : {}", dsp.getNumInputs()).unwrap();
    writeln!(output_file, "number_of_outputs : {}", dsp.getNumOutputs()).unwrap();
    writeln!(output_file, "number_of_frames  : {}", num_total_samples).unwrap();
}

fn run_dsp(output_file: &mut File, num_samples: usize, line_num_offset: usize) {

    // Generation constants
    let buffer_size = 64usize;
    let num_buffers_to_generate = 100;

    // Init dsp
    let mut dsp = Box::new(mydsp::new());
    dsp.init(SAMPLE_RATE);

    let num_inputs = dsp.getNumInputs() as usize;
    let num_outputs = dsp.getNumOutputs() as usize;

    // Prepare buffers
    let mut in_buffer = vec![vec![0 as FloatType; buffer_size]; num_inputs];
    let mut out_buffer = vec![vec![0 as FloatType; buffer_size]; num_outputs];

    // Compute
    let mut cycle = 0;
    let mut num_samples_written = 0;
    while num_samples_written < num_samples {

        let buffer_size = buffer_size.min(num_samples - num_samples_written);

        // handle inputs
        for c in 0..num_inputs {
            for j in 0..buffer_size {
                let first_frame = num_samples_written == 0 && j == 0;
                in_buffer[c][j] = if first_frame { 1.0 } else { 0.0 };
            }
        }

        // Set button state
        if cycle == 0 {
            let mut buttonOn = ButtonUI::<f64>{ fState: 1.0 };
            dsp.buildUserInterface(&mut buttonOn);
        } else {
            let mut buttonOff = ButtonUI::<f64>{ fState: 0.0 };
            dsp.buildUserInterface(&mut buttonOff);
        }

        dsp.compute(
            buffer_size as i32,
            in_buffer.iter().map(|buffer| buffer.as_slice()).collect::<Vec<&[FloatType]>>().as_slice(),
            out_buffer.iter_mut().map(|buffer| buffer.as_mut_slice()).collect::<Vec<&mut [FloatType]>>().as_mut_slice(),
        );

        // handle outputs
        for j in 0..buffer_size {
            write!(output_file, "{:6} :", num_samples_written + line_num_offset).unwrap();
            for c in 0..num_outputs {
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
    let output_file_name = env::args().nth(1).expect("ERROR: Output file name expected.");
    let mut output_file = File::create(output_file_name).expect("Cannot create output file");

    print_header(&mut output_file, num_total_samples);

    // Only test mono DSP for now
    run_dsp(&mut output_file, block_size, 0);

    //run_dsp(&mut output_file, block_size, 1 * block_size);
    //run_dsp(&mut output_file, block_size, 2 * block_size);
    //run_dsp(&mut output_file, block_size, 3 * block_size);
}
