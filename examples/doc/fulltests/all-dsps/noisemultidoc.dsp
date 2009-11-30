declare name 		"noisemultidoc";
declare version 	"0.1";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// 	Demo file for the Faust documentation.
//-----------------------------------------------


<doc>
This program describes a white noise generator with an interactive volume. The \texttt{random} function describes a random numbers generator, which equation follows: <equation>random</equation>

Notice hereby the use of an integer arithmetic on 32 bits. The white noise corresponds to : <equation>noise</equation>
</doc>

random  = +(12345)~*(1103515245);
noise   = random/2147483647;

<doc>
Moreover, its sound level is controlled by a user interface element, finally giving the following equation : <equation>process</equation>
</doc>

<doc>This process is illustrated with <diagram>process</diagram>.</doc>


process = noise * vslider("volume", 0, 0, 1, 0.1);
