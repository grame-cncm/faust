// check short delay are correctly compiled
// and shared (/(x):@(y) ==> @(y):/(x) when x is constant)

process = _ <: sum(i,4, /(i+1) : @(i+4));
