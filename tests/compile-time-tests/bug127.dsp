// regression test for #127 by @magnetophon, fixed in 2.5.21 (rev. cc8253f7)

group(x) = vgroup("foo", x);
//this compiles:
// group(x) = vgroup("foo", (_,_));

test(1,group) = (group(_,_));
//this compiles:
// test(1,group) = (vgroup("foo",(_,_)));

process =
  test(1,group);
  //this compiles:
  // (group(_,_));
