import("music.lib");

smooth(c) = *(1-c) : +~*(c);

process = (@(nentry("d1", 200, 0, 1000, 1)) : smooth(0.999)),
	 	(@(nentry("d2", 200, 0, 2000, 1)) : smooth(0.999)), 
		(@(nentry("d3", 400, 200, 3000, 1)) : smooth(0.999));
