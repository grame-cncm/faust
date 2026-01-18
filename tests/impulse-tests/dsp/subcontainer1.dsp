// Test case for fSampleRate initialization in SubContainers

/*
import("stdfaust.lib");
process = rdtable(100, ma.SR, ba.time % 100);
*/

ID_0 = fconstant(int fSamplingFreq, <math.h>);
ID_1 = 1.0f, ID_0;
ID_2 = (ID_1 : max);
ID_3 = 1.92e+05f, ID_2;
ID_4 = (ID_3 : min);
ID_5 = _, 1;
ID_6 = (ID_5 : +);
ID_7 = ID_6 ~ _;
ID_8 = (ID_7 : mem);
ID_9 = ID_8, 100;
ID_10 = (ID_9 : %);
ID_11 = ID_4, ID_10;
ID_12 = 100, ID_11;
ID_13 = ID_12 : rdtable;
process = ID_13;
