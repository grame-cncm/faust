//--------------------------looper----------------------------
//
// # Looper
//
// A simple looper that allows playback, reversing, and looping within a sound file. 
// It automatically adapts to the number of channels in the input sound file and wraps around 
// when the end of the sound file is reached. 
// The loop start and end positions, as well as the playback direction can be controlled.
// A horizontal bar graph displays the current playback position within the loop.
//
// #### Usage
//
// ```
// looper(sound) : si.bus(2);
// ```
// Where:
//
// * `sound`: the input sound file.
//
// Example:
//
// ```
// sound = soundfile("sound[url:{'loop.wav'}]",2);
// looper(sound) : si.bus(outputs(sound));
// ```
//------------------------------------------------------------

import("stdfaust.lib");

declare name      "looper";
declare version   "1.0";
declare author    "Grame";
declare license   "BSD";
declare copyright "(c)GRAME 2025";

looper(sf) = (0, loop_reader) : sf : !, !, attach(_,pos), si.bus(outputs(sf)-3)
with {
   
    // User controls
    play = checkbox("h:Controls/[3]Play/Stop");    // Checkbox to start/stop playback
    reverse = checkbox("h:Controls/[4]Reverse");   // Checkbox to play in reverse
   
    // Loop start and end positions (scaled to the sound file length)
    loop_start = length * hslider("[1]Loop_start", 0, 0, 1, 0.01);
    loop_end = length * hslider("[2]Loop_end", 1, 0, 1, 0.01);

    // Sound file length
    length = (0, 0) : sf : (_, si.block(outputs(sf) - 1));  
    
    // Current playback position within the loop
    loop_reader = min_loop_pos + (index % max(ma.EPSILON, loop_length))
    with {
       
        // Minimum loop position
        min_loop_pos = min(loop_start, loop_end);
      
        // Loop duration
        loop_length = abs(loop_end - loop_start);

        // Index counter that tracks playback position
        index = windex
        letrec {
            'windex = ba.if(windex < 0, windex + length,         // Wrap around if index goes negative
                      ba.if(windex > length, 0,                  // Wrap around if index exceeds length
                      windex + play * ba.if(reverse, -1, 1)));   // Update index based on play state and direction
        };

    };
  
    // Display playback position as a horizontal bar graph
    pos = (loop_reader / length) : hbargraph("[5]Position", 0, 1);
    
};

declare soundfiles "https://raw.githubusercontent.com/sletz/faust-sampler/main";
sound = soundfile("sound[url:{'violon.wav'}]", 2);

process = looper(sound);

