// a stereo distortion effect connected to a stereo reverb

import("stdfaust.lib");

distDrive = 0.8;
distOffset = 0;

process = par(i,2,ef.cubicnl(distDrive,distOffset)) : dm.zita_rev1;