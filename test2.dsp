import ("stdfaust.lib");

//process = button("play") <: @(100), @(10), @(1); // OK

//process = 440/ma.SR : (+,1:fmod) ~  _; // OK

//process = 440/ma.SR : (+,1:fmod) ~  (+~*(0.9)); // OK

// process = + ~ (+ ~ *(0.8)); // OK

// process = 1-1'; // OK

// process = fi.lowpass(3,1000);  // WRONG

// process = fi.lowpass(5,1000);  // OK

// process = (+:abs)~(*(0)); // OK

// process = (+:abs)~(*(0)) : @(10); // OK

// process = abs : ^(0.5) <: *(3), *(4);

process = os.osc(440);


