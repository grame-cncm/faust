// OK: faust -svg tests/ondemand/tod1.dsp
// test rewriting of ondemand code
process = 1,1 : ondemand(+~_);

