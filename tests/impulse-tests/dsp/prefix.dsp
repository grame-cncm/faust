/*
process = prefix(0.5, 0.8), 
    prefix(0.31), 
    (prefix(0.32):prefix(0.7)), 
    (prefix(0.33):mem), 
    (prefix(0.34):mem:mem), 
    (prefix(0.35,0.9) <: _,_);
*/

process = prefix(0.5, 0.8), 
    prefix(0.31), 
    (prefix(0.32):prefix(0.7)), 
    (prefix(0.35,0.9) <: _,_);