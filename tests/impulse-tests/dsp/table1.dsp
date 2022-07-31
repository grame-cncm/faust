wf1 = waveform{0,0.5,1,0.5,0,-0.5,-1,-.5};
wf2 = waveform{10,10.5,11,10.5,10,-10.5,-11,-10.5};

size = wf1 : _,!;
index = (+(1)~_) % size;
table1 = wf1,index : rdtable;
table2 = wf1,index,(wf2:!,_),index : rwtable;

process = table1,table2;