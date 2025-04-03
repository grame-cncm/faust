declare name      "wfs";
declare version   "1.0";
declare author    "Grame";
declare license   "BSD";
declare copyright "(c)GRAME 2025";

import("stdfaust.lib");

// Distance between speakers in meters
speakersDist = 0.0783;  

// Reference listening point (central position for WFS)
xref = 0;
yref = 1;
zref = 0;

// Spatialize 2 sound sources on 8 speakers
process = sp.wfs_ui(xref,yref,zref,speakersDist,2,8);


