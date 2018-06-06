//-----------------------------------------------
// MIDI controlled 16 channel volume control in db
//-----------------------------------------------

import("stdfaust.lib");
import("layout.dsp"); 

channel01		=  v01(vslider("Volume-01 [midi:ctrl 1] [tooltip CC-1]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel02		=  v02(vslider("Volume-02 [midi:ctrl 2] [tooltip CC-2]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel03		=  v03(vslider("Volume-03 [midi:ctrl 3] [tooltip CC-3]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel04		=  v04(vslider("Volume-04 [midi:ctrl 4] [tooltip CC-4]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel05		=  v05(vslider("Volume-05 [midi:ctrl 5] [tooltip CC-5]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel06		=  v06(vslider("Volume-06 [midi:ctrl 6] [tooltip CC-6]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel07		=  v07(vslider("Volume-07 [midi:ctrl 7] [tooltip CC-7]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel08		=  v08(vslider("Volume-08 [midi:ctrl 8] [tooltip CC-8]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel09		=  v09(vslider("Volume-09 [midi:ctrl 9] [tooltip CC-9]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel10		=  v10(vslider("Volume-10 [midi:ctrl 10] [tooltip CC-10]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel11		=  v11(vslider("Volume-11 [midi:ctrl 11] [tooltip CC-11]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel12		=  v12(vslider("Volume-12 [midi:ctrl 12] [tooltip CC-12]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel13		=  v13(vslider("Volume-13 [midi:ctrl 13] [tooltip CC-13]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel14		=  v14(vslider("Volume-14 [midi:ctrl 14] [tooltip CC-14]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel15		=  v15(vslider("Volume-15 [midi:ctrl 15] [tooltip CC-15]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);
channel16		=  v16(vslider("Volume-16 [midi:ctrl 16] [tooltip CC-16]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo);



process		= *(channel01), *(channel02), *(channel03), *(channel04), *(channel05), *(channel06), *(channel07), *(channel08), *(channel09), *(channel10), *(channel11), *(channel12), *(channel13), *(channel14), *(channel15), *(channel16);
