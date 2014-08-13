declare name 		"echo";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";
//-----------------------------------------------
// 		Impulse response of a simpleeEcho
//-----------------------------------------------

xxprocess = vectorize(5) : echo : serialize
    with {
        echo = (+:@(1000))~*(0.9);
    };

toto = vectorize(5) : vectorize(3);
tutu = _~_ : vectorize(5);

yyprocess = tutu + toto : serialize;

zzprocess = toto : +~_ ;

wwprocess = down(8,_) : log : up(8,_);

qqprocess = up(8,_) : smooth(0.9) : down(8,_) with { smooth(c) = *(1-c) : +~*(c); };
process = up(2,_) : mem ;
xxxprocess = mem;