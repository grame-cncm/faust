//-------------------------------------------------
// Check that min and max are able to bound
// infinite intervals
//--------------------------------------------------

import("music.lib");

clip(lo,hi) =  max(lo) : min(hi);
smooth(c) = *(1-c) : +~*(c);
d = hslider("delay",0,0,100,1) : smooth(0.999) : clip(0,100);

process = @(d);
