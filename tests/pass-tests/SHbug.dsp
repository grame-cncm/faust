// Bug discovered June 30, 2009
// partial application of primitives should work
//

myselect2(t,a,b)=select2(t,a,b);
sampleAndHold(t) = select2(t,_) ~ _;

process = sampleAndHold(int(button("sample")));


