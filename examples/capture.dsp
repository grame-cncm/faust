//-------------------------------------------------
// 		Capture : record up to 8s of sound and 
//		playback the recorded sound in loop
//-------------------------------------------------



//----------------------
// signaux de capture
//----------------------

B = button("Capture");	// Capture button
R = (B-mem(B)) > 0;		// Reset signal
D = (+(B):*(1-R))~_;	// Capture duration : 0..NNNN0..MMM

smooth(c) = *(1-c): + ~ *(c);

C = B : smooth(0.99);	// A little bit of crossfade

capture = *(C): (+ : delay(8*65536, D-1)) ~ *(1-B) : *(hslider("Playback level", 0.5, 0, 1, 0.01));


process = _ <: par(i, 4, hgroup("Memory %i", capture) ) :> _ ;

