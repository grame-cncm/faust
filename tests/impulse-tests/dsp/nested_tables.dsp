declare name "nested_tables";
// Tables whose content generator reads a table itself (issue #737) : every
// level has to be generated and filled before the level above reads it.
// Before the fix the nested tables were never filled (cpp), not defined
// (ocpp, link error), or the code was not generated (wasm, c, -it).
//
// Every table is read where it was written, so each output is the signal of
// its generator : the reference is the output of
// process = wave, wave, t % 10 + 10, wave;
// from 2.88.0 (171b603ac), with no table read by a generator. Each run is
// 15000 frames, below N - 1. Every value is a multiple of 1/64, exact in
// single and double.

N = 1 << 14;
time = (+(1) ~ _) - 1;
t = time;

// 64 values in [-0.5, 0.5), read at a pace that does not depend on SR
wave = rdtable(64, float(time % 64) / 64.0 - 0.5, (time * 37) % 64);

// a constant table filled by a generator that reads a table
s1 = rdtable(N, wave, t);
// two levels
s2 = rdtable(N, rdtable(N, wave, time), t);
// integer tables, the last example of the issue
f1 = rdtable(10, time + 10);
f2 = rdtable(10, time : f1);
s3 = t % 10 : f2;
// a read-write table filled by a generator that reads a table; cell N - 1,
// written at every sample, is never read
s4 = rwtable(N, wave, N - 1, float(t), t);

process = s1, s2, s3, s4;
