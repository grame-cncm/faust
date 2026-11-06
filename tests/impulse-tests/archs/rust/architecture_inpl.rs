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
#![allow(unused_imports)]
#![recursion_limit = "256"]

use default_boxed::DefaultBoxed;
use num_traits::cast::FromPrimitive;
use num_traits::float::Float;
use std::env;
use std::fs::File;
use std::io::Write;
use libm::remainderf;
use libm::rintf;
use libm::remainder;
use libm::rint;

type F32 = f32;
type F64 = f64;
type FaustFloat = f64;

#[derive(Copy, Clone)]
pub struct ParamIndex(i32);

pub const MAX_SOUNDFILE_PARTS: usize = 256;
const SOUNDFILE_BUFFER_SIZE: usize = 1024;
const SOUNDFILE_SAMPLE_RATE: i32 = 44100;

/// The soundfile read by the 'soundfile' primitive: MAX_SOUNDFILE_PARTS parts, the loaded files
/// followed by empty parts, stored one after the other in each channel buffer.
/// The generated code reads channel 'chan % fChannels' at 'fOffset[part] + index', with the index
/// kept in [0, fLength[part] - 1]. Contract: fChannels >= 1, fBuffers holds fChannels buffers, and
/// fLength, fSR and fOffset have MAX_SOUNDFILE_PARTS entries (otherwise the DSP code panics).
pub struct Soundfile<T> {
    pub fBuffers: Vec<Vec<T>>,
    pub fLength: Vec<i32>,
    pub fSR: Vec<i32>,
    pub fOffset: Vec<i32>,
    pub fChannels: i32,
}

impl<T: Copy + Default> Default for Soundfile<T> {
    /// The default sound, used until the host installs one: a silent channel, every part
    /// SOUNDFILE_BUFFER_SIZE frames long, all parts sharing the same buffer
    fn default() -> Self {
        Soundfile {
            fBuffers: vec![vec![T::default(); SOUNDFILE_BUFFER_SIZE]],
            fLength: vec![SOUNDFILE_BUFFER_SIZE as i32; MAX_SOUNDFILE_PARTS],
            fSR: vec![SOUNDFILE_SAMPLE_RATE; MAX_SOUNDFILE_PARTS],
            fOffset: vec![0; MAX_SOUNDFILE_PARTS],
            fChannels: 1,
        }
    }
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

    // -- soundfiles: the host loads the files of 'url', then gives them to 'set_soundfile(param, ...)'
    fn add_soundfile(&mut self, label: &str, url: &str, param: ParamIndex) {}

    // -- metadata declarations
    fn declare(&mut self, param: Option<ParamIndex>, key: &str, value: &str);
}

pub struct ButtonUI {
    all_button_params: Vec<ParamIndex>,
    soundfiles: Vec<(String, ParamIndex)>,
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

    // -- soundfiles
    fn add_soundfile(&mut self, label: &str, url: &str, param: ParamIndex) {
        self.soundfiles.push((url.to_string(), param));
    }

    // -- metadata declarations
    fn declare(&mut self, param: Option<ParamIndex>, key: &str, value: &str) {}
}

#[cfg_attr(feature = "default-boxed", derive(default_boxed::DefaultBoxed))]
// Generated intrinsics:
<<includeIntrinsic>>

// Generated class:
<<includeclass>>

// Soundfiles of the test: the fixture of the C++ harness (TestMemoryReader in controlTools.h).
// Each channel has its own phase, so that reading a soundfile with more channels than it has
// shows the 'chan % fChannels' wrap.
const SOUND_CHAN: usize = 2;
const SOUND_LENGTH: usize = 4096;
const SOUND_SR: i32 = 44100;

// Number of files of a soundfile url: "{'a.wav';'b.wav'}" has two
fn soundfile_part_count(url: &str) -> usize {
    url.trim()
        .trim_start_matches('{')
        .trim_end_matches('}')
        .split(';')
        .filter(|part| !part.trim().is_empty())
        .count()
        .max(1)
}

// Every file of the url is a SOUND_LENGTH part, the remaining parts are empty, as SoundUI does
fn test_soundfile(url: &str) -> Soundfile<FaustFloat> {
    let real_parts = soundfile_part_count(url).min(MAX_SOUNDFILE_PARTS);
    let total_length =
        real_parts * SOUND_LENGTH + (MAX_SOUNDFILE_PARTS - real_parts) * SOUNDFILE_BUFFER_SIZE;
    let mut soundfile = Soundfile {
        fBuffers: vec![vec![0.0 as FaustFloat; total_length]; SOUND_CHAN],
        fLength: Vec::with_capacity(MAX_SOUNDFILE_PARTS),
        fSR: Vec::with_capacity(MAX_SOUNDFILE_PARTS),
        fOffset: Vec::with_capacity(MAX_SOUNDFILE_PARTS),
        fChannels: SOUND_CHAN as i32,
    };
    let mut offset = 0;
    for part in 0..MAX_SOUNDFILE_PARTS {
        let real = part < real_parts;
        let length = if real { SOUND_LENGTH } else { SOUNDFILE_BUFFER_SIZE };
        soundfile.fLength.push(length as i32);
        soundfile.fSR.push(if real { SOUND_SR } else { SOUNDFILE_SAMPLE_RATE });
        soundfile.fOffset.push(offset as i32);
        if real {
            for chan in 0..SOUND_CHAN {
                for sample in 0..SOUND_LENGTH {
                    let phase = (2.0 * std::f64::consts::PI * sample as f64) / SOUND_LENGTH as f64;
                    soundfile.fBuffers[chan][offset + sample] =
                        (part as f64 + chan as f64 + phase).sin() as FaustFloat;
                }
            }
        }
        offset += length;
    }
    soundfile
}

// A DSP without soundfile has no 'set_soundfile': this default keeps the call below valid,
// the inherent method of a DSP with soundfiles being chosen first
trait TestSoundfileDsp {
    fn set_soundfile(
        &mut self,
        param: ParamIndex,
        soundfile: Soundfile<FaustFloat>,
    ) -> Result<Soundfile<FaustFloat>, Soundfile<FaustFloat>> {
        Err(soundfile)
    }
}

impl TestSoundfileDsp for mydsp {}

fn load_test_soundfiles(dsp: &mut mydsp) {
    let mut ui = ButtonUI {
        all_button_params: Vec::new(),
        soundfiles: Vec::new(),
    };
    mydsp::build_user_interface_static(&mut ui);
    for (url, param) in ui.soundfiles {
        if dsp.set_soundfile(param, test_soundfile(&url)).is_err() {
            panic!("soundfile '{}' cannot be installed", url);
        }
    }
}

const SAMPLE_RATE: i32 = 44100;

fn print_header(dsp: &Box<mydsp>, num_total_samples: usize, output_file: &mut File) {
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
    //let mut in_buffer = vec![vec![0 as FaustFloat; buffer_size]; FAUST_INPUTS];
    let mut buffers =
        vec![vec![0 as FaustFloat; buffer_size]; std::cmp::max(FAUST_INPUTS, FAUST_OUTPUTS)];

    // Prepare UI
    let mut ui = ButtonUI {
        all_button_params: Vec::new(),
        soundfiles: Vec::new(),
    };
    dsp.build_user_interface(&mut ui);

    // Compute
    let mut cycle = 0;
    let mut num_samples_written = 0;
    while num_samples_written < num_samples {
        let buffer_size = buffer_size.min(num_samples - num_samples_written);

        // handle inputs
        for buffer in buffers.iter_mut() {
            for (i, sample) in buffer.iter_mut().enumerate() {
                let first_frame = num_samples_written == 0 && i == 0;
                *sample = if first_frame { 1.0 } else { 0.0 };
            }
        }

        // Set button state
        if cycle == 0 {
            ui.set_button_parameters_to(&mut dsp, 1.0);
        } else {
            ui.set_button_parameters_to(&mut dsp, 0.0);
        }

        dsp.compute(buffer_size, &mut buffers);

        // handle outputs
        (0..buffer_size).for_each(|j| {
            write!(output_file, "{:6} :", num_samples_written + line_num_offset).unwrap();
            (0..FAUST_OUTPUTS).for_each(|c| {
                write!(output_file, " {:8.6}", buffers[c][j]).unwrap();
            });
            writeln!(output_file).unwrap();
            num_samples_written += 1;
        });

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

    let mut dsp = mydsp::default_boxed();
    load_test_soundfiles(&mut dsp);
    dsp.init(SAMPLE_RATE);

    print_header(&dsp, num_total_samples, &mut output_file);

    run_dsp(dsp, block_size, 0, &mut output_file);
}
