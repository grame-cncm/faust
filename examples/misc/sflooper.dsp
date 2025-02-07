//--------------------------sflooper----------------------------
//
// # sflooper
//
// A simple looper that allows playback, reversing, and looping with speed control within a sound file. 
// It automatically adapts to the number of channels in the input sound file and wraps around 
// when the end of the sound file is reached. 
// The loop start and end positions, as well as the playback direction can be controlled.
// A horizontal bar graph displays the current playback position within the loop.
//
// #### Usage
//
// ```
// sflooper(sound) : si.bus(outputs(sound)-2);
// ```
// Where:
//
// * `sound`: the input sound file.
//
// Example:
//
// ```
// sound = soundfile("sound[url:{'loop.wav'}]",2);
// sflooper(sound);
// ```
//------------------------------------------------------------

import("stdfaust.lib");

declare name      "looper";
declare version   "1.0";
declare author    "Grame";
declare license   "BSD";
declare copyright "(c)GRAME 2025";

// Play button state is used to control loop_reader index increment and actual output signal generation.

sflooper(sf) = (0, play * loop_index) : sf : !, !, attach(_,pos), si.bus(outputs(sf)-3)
with {
   
    // User controls
    speed = hslider("h:Controls/[3]Speed", 1, 0.2, 5, 0.01); // Slider to control playback speed
    play = checkbox("h:Controls/[4]Play/Stop");              // Checkbox to start/stop playback
    reverse = checkbox("h:Controls/[5]Reverse");             // Checkbox to play in reverse
   
    // Loop start and end positions with smoothing (scaled to the sound file length) 
    loop_start = length * hslider("[1]Loop_start", 0, 0, 1, 0.01) : si.smoo;
    loop_end = length * hslider("[2]Loop_end", 1, 0, 1, 0.01) : si.smoo;

    // Sound file length
    length = (0, 0) : sf : (_, si.block(outputs(sf) - 1));  
    
    // Current playback position within the loop
    loop_index = min_loop_pos + (index % max(ma.EPSILON, loop_length))
    with {
       
        // Minimum loop position
        min_loop_pos = min(loop_start, loop_end);
      
        // Loop duration
        loop_length = abs(loop_end - loop_start);

        // Playback speed with direction
        read_speed = speed * ba.if(reverse, -1, 1);

        // Index counter that tracks playback position
        index = windex
        letrec {
            'windex = ba.if(windex < 0, windex + length,  // Wrap around if index goes negative
                      ba.if(windex > length, 0,           // Wrap around if index exceeds length
                      windex + play * read_speed));       // Update index based on play state and direction
        };

    };
  
    // Display playback position as a horizontal bar graph
    pos = (loop_index / length) : hbargraph("[6]Position", 0, 1);
    
};

declare soundfiles "https://raw.githubusercontent.com/sletz/faust-sampler/main";
sound = soundfile("sound[url:{'violon.wav'}]", 2);

process = sflooper(sound);

