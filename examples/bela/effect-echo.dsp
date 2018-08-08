// Enter Faust code here
import("music.lib");
import("filter.lib");


myEcho = _ <: *(dry), (+~(fdelay(65536,delLength)*feedback*-1) : *(1-dry)) :> _
with{
	delLength = 6000;
	feedback = 0.8;
	dry = 0.3;
};

process = myEcho;