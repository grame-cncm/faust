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

import("all.lib");

process = _,_,(pathClock : compteurUpReset2(nbRepet) : rampePlayer, _) : routageIO : rec_play_table, rec_play_table;

///////////////////////////////////////////////////////////////////////////////////////////////////

// General loop duration
MasterTaille = hslider("MasterTaille[BELA: ANALOG_0]", 500, 200, 2000,0.01);
MasterClocSize = int(MasterTaille*ma.SR/ 1000);

// Depth of repeat fragments
taille = hslider("taille[BELA: ANALOG_1]", 50, 2, 200,0.01);
clocSize = int(taille*ma.SR/ 1000);

// Number of repeat fragments
nbRepet = int(hslider("nbRepet[BELA: ANALOG_2]",4,1,16,1) );

trig = _<:_,mem: >;

routageIO(a, b, c, d) = a, c, d, b, c, d;

rec_play_table(input, inReadIndex, reset) = (rwtable(wf, rindex):fi.dcblockerat(20))
    with {
        SR = 44100;
        buffer_sec = 2;
        size = int(SR * buffer_sec);
        init = 0.;

        windex = (%(_,size))~(+(1):*(1-reset));	
        rindex = (%(int(inReadIndex),size));

        wf = size, init, int(windex), input;
	};

MasterClock = (%(_,MasterClocSize))~(+(1)) : detect
    with {
        detect(x) = select2 (x < 100, 0, 1);
    };

SlaveClock(reset) = (%(_,clocSize))~(+(1):*(1-reset));
detect1(x) = select2 (x < clocSize/2, 0, 1);

pathClock = MasterClock <: trig, _ : SlaveClock, _ : detect1, _;

compteurUpReset2(nb, in, reset) = ((in:trig), reset : (routage : memo2)~_), reset
    with {
        memo2(a, b)		= (ba.if(b>0.5, 0, _) )~(+(a));
        compare(value)	= ba.if(value>nb, 1, 0); // :trig;
        routage(d,e,f)	= e, (f, compare(d) : RSLatch <: +(f));
    };

RSLatch(R, S) = latch(S,R)
    with {
        trig = _<:_,mem: >;
        latch(S,R) = _ ~ (ba.if(R>0.5, 0, _) : ba.if(S>0.5,1,_));
    };

rampePlayer(reset) = rampe
    with {
        rst = reset : trig;
        rampe = _ ~ (+(1):*(1-rst));
    };
