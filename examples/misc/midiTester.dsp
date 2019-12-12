declare name        "midiTester";
declare version     "1.0";
declare author      "Vincent Rateau, GRAME";
declare license     "GPL v3";
declare reference   "www.sonejo.net";

// FAUST MIDI TESTER

process = _*0, (vgroup("FAUST MIDI TESTER", hgroup("[1]", controltester, controlchantester, noteontester, noteonchantester, noteofftester, noteoffchantester, keypresschantester, midiclocktester), hgroup("[2]", kattester, katchantester, pctester, pcchantester, chattester, chatchantester, pitchwheeltester, pitchwheelchantester) :> _)) : attach;

///////////////////////////

//Ctrl tester (ctrl ): tester(midi in, midi out)
controltester = vgroup("CTRL IN/OUT", valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("Ctrl Value IN (Ctrl %i) [midi:ctrl %i]", 60, 0, 127, 1) : hbargraph("Ctrl Value OUT (Ctrl %o) [midi:ctrl %o]", 0, 127);
booltest(i,o) = checkbox("Ctrl Bool IN (Ctrl %i) [midi:ctrl %i]") : hbargraph("Ctrl Bool OUT (Ctrl %o) [midi:ctrl %o]", 0, 1);
};

//Ctrl Chan tester (ctrl chan): tester(midi in, midi out)
controlchantester = vgroup("CTRL CHAN IN/OUT", valuetest(50,2,74,3))
with{
valuetest(i,ic,o,oc) = hslider("Ctrl Value IN (Ctrl %i Channel %ic) [midi:ctrl %i %ic]", 60, 0, 127, 1) : hbargraph("Ctrl Value OUT (Ctrl %o) Channel OUT(Chan %oc) [midi:ctrl %o %oc]", 0, 127);
};

//Note tester (keyon) : tester(midi in, midi out)
noteontester = vgroup("NOTE ON IN/OUT", valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("NoteOn Value IN (Note %i) [midi:keyon %i]", 60, 0, 127, 1) : hbargraph("NoteOn Value OUT (Note %o) [midi:keyon %o]", 0, 127);
booltest(i,o) = checkbox("NoteOn Bool IN (Note %i) [midi:keyon %i]") : hbargraph("NoteOn Bool OUT (Note %o) [midi:keyon %o]", 0, 1);
};

//Note Chan tester (keyon) : tester(midi in, midi out)
noteonchantester = vgroup("NOTE ON CHAN IN/OUT", valuetest(50, 2, 51, 3), booltest(50, 2, 101, 3))
with{
valuetest(i, ic, o, oc) = hslider("NoteOn Value IN (Note %i Channel %ic) [midi:keyon %i %ic]", 60, 0, 127, 1) : hbargraph("NoteOn Value OUT (Note %o Chan %oc) [midi:keyon %o %oc]", 0, 127);
booltest(i, ic, o, oc) = checkbox("NoteOn Chan Bool IN (Note %i Channel %ic) [midi:keyon %i %ic]") : hbargraph("NoteOn Chan Bool OUT (Note %o Channel %oc) [midi:keyon %o %oc]", 0, 1);
};

//Note tester (keyoff) : tester(midi in, midi out)
noteofftester = vgroup("NOTE OFF IN/OUT", valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("NoteOff Value IN (Note %i) [midi:keyoff %i]", 60, 0, 127, 1) : hbargraph("NoteOff Value OUT (Note %o) [midi:keyoff %o]", 0, 127);
booltest(i,o) = checkbox("NoteOff Bool IN (Note %i) [midi:keyoff %i]") : hbargraph("NoteOff Bool OUT (Note %o) [midi:keyoff %o]", 0, 1);
};

//Note Chan tester (keyoff) : tester(midi in, midi out)
noteoffchantester = vgroup("NOTE OFF CHAN IN/OUT", valuetest(50, 2, 51, 3), booltest(50, 2, 101, 3))
with{
valuetest(i, ic, o, oc) = hslider("NoteOff Value IN (Note %i Channel %ic) [midi:keyoff %i %ic]", 60, 0, 127, 1) : hbargraph("NoteOff Value OUT (Note %o Channel %oc) [midi:keyoff %o %oc]", 0, 127);
booltest(i, ic, o, oc) = checkbox("NoteOff Bool IN (Note %i Channel %ic) [midi:keyoff %i %ic]") : hbargraph("NoteOff Bool OUT (Note %o Channel %oc) [midi:keyoff %o %oc]", 0, 1);
};

//KeyPress Chan tester (keypress) : tester(midi in, midi out)
keypresschantester = vgroup("KEY PRESS CHAN IN/OUT", valuetest(50, 2, 51, 3), booltest(50, 2, 101, 3))
with{
valuetest(i, ic, o, oc) = hslider("Pressure Value IN (Note %i Channel %ic) [midi:keypress %i %ic]", 60, 0, 127, 1) : hbargraph("Note Value OUT (Note %o Channel %oc) [midi:keypress %o %oc]", 0, 127);
booltest(i, ic, o, oc) = checkbox("Pressure Bool IN (Note %i Channel %ic) [midi:keypress %i %ic]") : hbargraph("Pressure Bool OUT (Note %o Channel %oc) [midi:keypress %o %oc]", 0, 1);
};

//Midisync tester
midiclocktester = vgroup("MIDI SYNC (IN)", clock, startstop)
with{
clock = checkbox("MIDI clock signal [midi:clock]");
startstop = checkbox("MIDI START/STOP [midi:start] [midi:stop]");
};

//Key Aftertouch tester (keypress) : tester(midi in, midi out)
kattester = vgroup("KEY AFTERTOUCH (KAT) IN/OUT",valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("Note KAT Value IN (Note %i) [midi:keypress %i]", 60, 0, 127, 1) : hbargraph("Note KAT Value OUT (Note %o) [midi:keypress %o]", 0, 127);
booltest(i,o) = checkbox("Note KAT Bool IN (Note %i) [midi:keypress %i]") : hbargraph("Note KAT Bool OUT (Note %o) [midi:keypress %o]", 0, 1);
};

//Key Aftertouch tester (keypress) : tester(midi in, midi out)
katchantester = vgroup("KEY AFTERTOUCH CHAN (KAT) IN/OUT",valuetest(50,2,51,3), booltest(100,2,101,3))
with{
valuetest(i,ic,o,oc) = hslider("Note KAT Value IN (Note %i) (Chan %ic) [midi:keypress %i %ic]", 60, 0, 127, 1) : hbargraph("Note KAT Value OUT (Note %o) (Chan %oc) [midi:keypress %o %oc]", 0, 127);
booltest(i,ic,o,oc) = checkbox("Note KAT Bool IN (Note %i) (Chan %ic) [midi:keypress %i %ic]") : hbargraph("Note KAT Bool OUT (Note %o) (Chan %oc)[midi:keypress %o %oc]", 0, 1);
};

//ProgramChange tester (pgm) : tester(midi in, midi out)
pctester = vgroup("PROGRAM CHANGE (PC) IN/OUT",valuetest(1,2), booltest(1,2))
with{
valuetest(i,o) = hslider("ProgramChange Value IN (PC %i) [midi:pgm %i]", 60, 0, 127, 1) : hbargraph("ProgramChange Value OUT (PC %o) [midi:pgm %o]", 0, 127);
booltest(i,o) = checkbox("ProgramChange Bool IN (PC %i) [midi:pgm %i]") : hbargraph("ProgramChange Bool OUT (PC %o) [midi:pgm %o]", 0, 1);
};

//ProgramChange Chan tester (pgm) : tester(midi in, midi out)
pcchantester = vgroup("PROGRAM CHANGE CHAN (PC) IN/OUT",valuetest(1, 2, 2, 3), booltest(1, 2, 2, 3))
with{
valuetest(i,ic,o,oc) = hslider("ProgramChange Value IN (PC %i) (CHAN %ic) [midi:pgm %i %ic]", 60, 0, 127, 1) : hbargraph("ProgramChange Value OUT (PC %o) (CHAN %oc) [midi:pgm %o %oc]", 0, 127);
booltest(i,ic,o,oc) = checkbox("ProgramChange Bool IN (PC %i) (CHAN %ic) [midi:pgm %i %ic]") : hbargraph("ProgramChange Bool OUT (PC %o) (CHAN %oc) [midi:pgm %o %oc]", 0, 1);
};

//Channel Aftertourch tester (chanpress) : tester(midi in, midi out)
chattester = vgroup("CHANNEL AFTERTOUCH (CHAT) IN/OUT",valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("Note CHAT Value IN (Note %i) [midi:chanpress %i]", 60, 0, 127, 1) : hbargraph("Note CHAT Value OUT (Note %o) [midi:chanpress %o]", 0, 127);
booltest(i,o) = checkbox("Note CHAT Bool IN (Note %i) [midi:chanpress %i]") : hbargraph("Note CHAT Bool OUT (Note %o) [midi:chanpress %o]", 0, 1);
};

//Channel Aftertourch tester (chanpress) : tester(midi in, midi out)
chatchantester = vgroup("CHANNEL AFTERTOUCH CHAN (CHAT) IN/OUT",valuetest(50,2,51,3), booltest(100,2,101,3))
with{
valuetest(i,ic,o,oc) = hslider("Note CHAT Chan Value IN (Note %i) (Chan %ic) [midi:chanpress %i %ic]", 60, 0, 127, 1) : hbargraph("Note CHAT Value OUT (Note %o) (Chan %oc) [midi:chanpress %o %oc]", 0, 127);
booltest(i,ic,o,oc) = checkbox("Note CHAT Bool IN (Note %i) (Chan %ic) [midi:chanpress %i %ic]") : hbargraph("Note CHAT Bool OUT (Note %o) (Chan %oc) [midi:chanpress %o %oc]", 0, 1);
};

//Pitchwheel tester (pitchwheel) : tester(midi in, midi out)
pitchwheeltester = vgroup("PITCHWHEEL IN/OUT",valuetest, booltest)
with{
valuetest = hslider("Pitchwheel Value IN  [midi:pitchwheel]", 0, -8192, 8191, 1) : hbargraph("Pitchwheel Value OUT[midi:pitchwheel]", -8192, 8191);
booltest = checkbox("Pitchwheel Bool IN [midi:pitchwheel]") : hbargraph("Pitchwheel Bool OUT [midi:pitchwheel]", 0, 1);
};

//Pitchwheel Chan tester (pitchwheel) : tester(midi in, midi out)
pitchwheelchantester = vgroup("PITCHWHEEL CHAN IN/OUT",valuetest(2, 15), booltest(2, 15))
with{
valuetest(ic, oc) = hslider("Pitchwheel Value IN (Chan %ic) [midi:pitchwheel %ic]", 0, -8192, 8191, 1) : hbargraph("Pitchwheel Value OUT (Chan %oc)[midi:pitchwheel %oc]", -8192, 8191);
booltest(ic, oc) = checkbox("Pitchwheel Bool IN (Chan %ic) [midi:pitchwheel %ic]") : hbargraph("Pitchwheel Bool OUT (Chan %oc) [midi:pitchwheel %oc]", 0, 1);
};
