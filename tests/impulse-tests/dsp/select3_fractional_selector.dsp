// select3 converts its selector to int before choosing a branch.
// Both selectors stay in the documented [0, 2] range for any input.
process(x) = select3(min(1.0, abs(x))*0.25, 0.25, 0.5, 0.75),
             select3(1.0 + min(1.0, abs(x))*0.25, 0.25, 0.5, 0.75);
