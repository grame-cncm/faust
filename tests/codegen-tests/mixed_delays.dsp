// Mixed delay cases: copy delay (<= 9) and dense delay (> 9, high density)
// Ensures both implementations are exercised in one compile unit.

process = _ <: sum(i,4, @(i+1)), sum(i,64, @(i+1)) : +;
