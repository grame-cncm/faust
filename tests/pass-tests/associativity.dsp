// check associativity rules

first((x,xs)) = x;
first((x:xs)) = x;

process = first(par(i,8,*(i+1))) : first(seq(i,10,+(i+1)));
