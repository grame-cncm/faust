// A DSP with every kind of control the remote control protocol treats apart:
// the same as test/remote-native/remote_test.dsp in faustwasm, which its
// conformance test compiles with remote_host.cpp
declare name "remote_test";
freq = hslider("freq", 440, 20, 2000, 1);
gate = button("gate");
locked = hslider("locked [remote:off]", 0.5, 0, 1, 0.01);
tilt = hslider("tilt [acc: 0 0 -10 0 10]", 0.5, 0, 1, 0.01);
mode = checkbox("mode");
count = nentry("count", 3, 0, 10, 1);
// Every control is used: Faust drops the others from the interface
process = (freq / 2000, gate, tilt, locked) :> _ : hbargraph("level", 0, 4) * mode * count;
