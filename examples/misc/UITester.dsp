declare name "UITester";
declare version "1.0";
declare author "O. Guillerminet";
declare license "BSD";
declare copyright "(c) O. Guillerminet 2012";

vbox =			vgroup("vbox", 
					checkbox("check1"),
					checkbox("check2"),
					nentry("knob0[style:knob]", 60, 0, 127, 0.1));

sliders = 		hgroup("sliders",
					vslider("vslider1", 60, 0, 127, 0.1),
					vslider("vslider2", 60, 0, 127, 0.1),
					vslider("vslider3", 60, 0, 127, 0.1));

knobs = 		hgroup("knobs",
					vslider("knob1[style:knob]", 60, 0, 127, 0.1),
					vslider("knob2[style:knob]", 60, 0, 127, 0.1), 
					vslider("knob3[style:knob]", 60, 0, 127, 0.1));

smallhbox1 =		hgroup("small box 1",
					vslider("vslider5 [unit:Hz]", 60, 0, 127, 0.1),
					vslider("vslider6 [unit:Hz]", 60, 0, 127, 0.1),
					vslider("knob4[style:knob]", 60, 0, 127, 0.1),
					nentry("num1 [unit:f]", 60, 0, 127, 0.1),
					vbargraph("vbar1", 0, 127));

smallhbox2 =		hgroup("small box 2",
					vslider("vslider7 [unit:Hz]", 60, 0, 127, 0.1),
					vslider("vslider8 [unit:Hz]", 60, 0, 127, 0.1),
					vslider("knob5[style:knob]", 60, 0, 127, 0.1),
					nentry("num2 [unit:f]", 60, 0, 127, 0.1),
					vbargraph("vbar2", 0, 127));

smallhbox3 =		hgroup("small box 3",
					vslider("vslider9 [unit:Hz]", 60, 0, 127, 0.1),
					vslider("vslider10 [unit:m]", 60, 0, 127, 0.1),
					vslider("knob6[style:knob]", 60, 0, 127, 0.1),
					nentry("num3 [unit:f]", 60, 0, 127, 0.1),
					vbargraph("vbar3", 0, 127));

subhbox1 =		hgroup("sub box 1",
					smallhbox2,
					smallhbox3);

vmisc = 		vgroup("vmisc",
					vslider("vslider4 [unit:Hz]", 60, 0, 127, 0.1),
					button("button"),
					hslider("hslider [unit:Hz]", 60, 0, 127, 0.1),
					smallhbox1,
					subhbox1,
					hbargraph("hbar", 0, 127));

hmisc = 		hgroup("hmisc",
					vslider("vslider4 [unit:f]", 60, 0, 127, 0.1),
					button("button"),
					hslider("hslider", 60, 0, 127, 0.1),
					nentry("num [unit:f]", 60, 0, 127, 0.1),
					vbargraph("vbar", 0, 127),
					hbargraph("hbar", 0, 127));

//------------------------- Process --------------------------------

process = 		tgroup("grp 1",
					vbox,
					sliders,
					knobs,
					vmisc,
					hmisc);

