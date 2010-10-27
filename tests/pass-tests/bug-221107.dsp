import("music.lib");

//--------------------------------
// bug du 22-nov-2007 (Christophe)
//--------------------------------

T1(index)	= rdtable(10000, sin(time/100), int(index*100));			//Low cpu cost sine calculation
T2(index)	= rdtable(1000, pow(2,(time/100)), int(index*100));


s1 = hslider("slider1",0, 0, 100, 1);
s2 = hslider("slider2",0, 0, 100, 1);

process = T1(s1), T2(s2);
