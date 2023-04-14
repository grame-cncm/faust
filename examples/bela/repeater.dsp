// REPEATER:
// Freeze and repeat a small part of input signal 'n' times
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// ANALOG IN:
// ANALOG 0	: Duration (ms) between 2 repeat series (500 to 2000 ms)
// ANALOG 1	: Duration of one repeat (2 to 200 ms)
// ANALOG 2	: Number of repeat
//
///////////////////////////////////////////////////////////////////////////////////////////////////

import("stdfaust.lib");

process = _, _ , (pathClock : compteurUpReset: rampePlayer, _) : routageIO : rec_play_table , rec_play_table;

///////////////////////////////////////////////////////////////////////////////////////////////////

// General loop duration
MasterTaille = hslider("MasterTaille[BELA: ANALOG_0]", 500, 200, 2000, 0.01);
MasterClocSize = int(MasterTaille*ma.SR/1000);

// Depth of repeat fragments
taille = hslider("taille[BELA: ANALOG_1]", 50, 2, 200, 0.01);
clocSize = int(taille*ma.SR/1000);

// Number of repeat fragments
nbRepet = int(hslider("nbRepet[BELA: ANALOG_2]", 3, 1, 16, 1));

trig(x) = (x - x') > 0;

// Counter between 0 and MasterClock, send 0 when it's between 0 and 200
MasterClock = (%(_,MasterClocSize))~(+(1)) : detect1
    with 
    {
        detect1(x) = select2(x < 200, 0, 1);
    };

// Counter between 0 and clocSize, send 0 when it's between 0 and 20
SlaveClock(reset) = (%(_,clocSize))~(+(1):*(1-reset)) : detect2
    with 
    {
        detect2(x) = select2(x < 20, 0, 1);
    };

pathClock = MasterClock <: trig, _ : SlaveClock, _;

// Detect if reset is triggered or if nbRepet is reached
compteurUpReset(in, reset) = ((reinitConditions : increment)~_), reset
    with 
    {
        increment(b) = (ba.if(b>0.5, 0, _))~(+(in:trig));
        reinitConditions(d) = (ba.if (d>nbRepet, 1, 0) : rSLatch + reset);
        rSLatch(S) = _~(ba.if(reset>0.5, 0, _) : ba.if(S>0.5, 1, _));
    };

// Will be used for the read index of the rwtable
rampePlayer(counterReset) = rampe 
    with 
    {
        rst = counterReset : trig;
        rampe = _~(+(1):*(1-rst));
    };

// a and b are audio signals, c will be the read index from the ramp player and d is the reset
routageIO(a, b, c, d) = a, c, d, b, c, d;

rec_play_table(input, inReadIndex, reset) = (rwtable(size, init, windex,input, inReadIndex))
    with 
    {
        SR = 44100;
        buffer_sec = 2;
        size = int(SR * buffer_sec);
        init = 0.;
        // the writing is looped over the whole length of the rwtable
        windex = (%(_,size))~(+(1)) : (*(1-reset)) : int;	
    };
    