import("stdfaust.lib");

// int(exp) are not simplified in route expressions, why ?

ok = route(4, 4, par(i, 4, (i*5)/4));
xbug = route(4, 4, par(i, 4, int((i*5)/4)));
bug = route(4, 4, 1, int(7/2));
process = bug;