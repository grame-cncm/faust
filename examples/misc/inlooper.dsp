//--------------------------inlooper----------------------------
//
// # inlooper
//
// A simple looper that allows capture, playback, reversing, and looping with speed control from a mono input. 
// It wraps around when the end of the capture section is reached. 
// The loop start and end positions, as well as the playback direction can be controlled.
// A horizontal bar graph displays the current playback position within the loop.
//
// #### Usage
//
// ```
// _ : inlooper(length) : _;
// ```
// Where:
//
// * `length`: the loop duration in samples (constant numerical expression). 
//
//------------------------------------------------------------

import("stdfaust.lib");

declare name      "inlooper";
declare version   "1.0";
declare author    "Grame";
declare license   "BSD";
declare copyright "(c)GRAME 2025";

inlooper(length) = attach(rwtable(length, 0.0, rec_index, _, loop_index), pos)
with {
   
    // User controls
    speed = hslider("h:Controls/[3]Speed", 1, 0.2, 5, 0.01); // Slider to control playback speed
    record = button("h:Controls/[4]Record");                 // Button to start/stop recording
    play = checkbox("h:Controls/[5]Play/Stop");              // Checkbox to start/stop playback
    reverse = checkbox("h:Controls/[6]Reverse");             // Checkbox to play in reverse
    
    // Loop start and end positions with smoothing (scaled to the captured input length) 
    loop_start = length * hslider("[1]Loop_start", 0, 0, 1, 0.01) : si.smoo;
    loop_end = length * hslider("[2]Loop_end", 1, 0, 1, 0.01) : si.smoo;

    // Index counter that tracks recording position
    rec_index = (+(1) : %(length)) ~ *(record);

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
    pos = (loop_index / length) : hbargraph("[7]Position", 0, 1);
    
};

process = inlooper(MAX_LENGTH)
with {
    MAX_LENGTH = 5 * 44100; // 5 seconds at 44100 Hz, has to be a constant
};

