declare name "zitaRev";
declare version "0.0";
declare author "JOS, Revised by RM";
declare description "Example GUI for `zita_rev1_stereo` (mostly following the Linux `zita-rev1` GUI).";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.zita_rev1;	
