declare name        "Faust Midi Tester";
declare version     "1.0";
declare author      "Vincent Rateau, GRAME";
declare license     "GPL v3";
declare reference   "www.sonejo.net";


// FAUST MIDI TESTER


process = _*0, (vgroup("FAUST MIDI TESTER", hgroup("[1]", controltester, noteontester, noteofftester, midiclocktester), hgroup("[2]", kattester, pctester, chattester, pitchwheeltester) :> _)) : attach;


///////////////////////////

//Ctrl tester (ctrl ): tester(midi in, midi out)
controltester = vgroup("CTRL IN/OUT", valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("Ctrl Value IN (Ctrl %i) [midi:ctrl %i]", 60, 0, 127, 1) : hbargraph("Ctrl Value OUT (Ctrl %o) [midi:ctrl %o]", 0, 127);
booltest(i,o) = checkbox("Ctrl Bool IN (Ctrl %i) [midi:ctrl %i]") : hbargraph("Ctrl Bool OUT (Ctrl %o) [midi:ctrl %o]", 0, 1);
};


//Note tester (keyon) : tester(midi in, midi out)
noteontester = vgroup("NOTE ON IN/OUT", valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("NoteOn Value IN (Note %i) [midi:keyon %i]", 60, 0, 127, 1) : hbargraph("NoteOn Value OUT (Note %o) [midi:keyon %o]", 0, 127);
booltest(i,o) = checkbox("NoteOn Bool IN (Note %i) [midi:keyon %i]") : hbargraph("NoteOn Bool OUT (Note %o) [midi:keyon %o]", 0, 1);
};

//Note tester (keyoff) : tester(midi in, midi out)
noteofftester = vgroup("NOTE OFF IN/OUT", valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("NoteOff Value IN (Note %i) [midi:keyoff %i]", 60, 0, 127, 1) : hbargraph("NoteOff Value OUT (Note %o) [midi:keyoff %o]", 0, 127);
booltest(i,o) = checkbox("NoteOff Bool IN (Note %i) [midi:keyoff %i]") : hbargraph("NoteOff Bool OUT (Note %o) [midi:keyoff %o]", 0, 1);
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


//ProgramChange tester (pgm) : tester(midi in, midi out)
pctester = vgroup("PROGRAM CHANGE (PC) IN/OUT",valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("ProgramChange Value IN (PC %i) [midi:pgm %i]", 60, 0, 127, 1) : hbargraph("ProgramChange Value OUT (PC %o) [midi:pgm %o]", 0, 127);
booltest(i,o) = checkbox("ProgramChange Bool IN (PC %i) [midi:pgm %i]") : hbargraph("ProgramChange Bool OUT (PC %o) [midi:pgm %o]", 0, 1);
};


//Channel Aftertourch tester (chanpress) : tester(midi in, midi out)
chattester = vgroup("CHANNEL AFTERTOUCH (CHAT) IN/OUT",valuetest(50,51), booltest(100,101))
with{
valuetest(i,o) = hslider("Note CHAT Value IN (Note %i) [midi:chanpress %i]", 60, 0, 127, 1) : hbargraph("Note CHAT Value OUT (Note %o) [midi:chanpress %o]", 0, 127);
booltest(i,o) = checkbox("Note CHAT Bool IN (Note %i) [midi:chanpress %i]") : hbargraph("Note CHAT Bool OUT (Note %o) [midi:chanpress %o]", 0, 1);
};


//Pitchwheel tester (pitchwheel) : tester(midi in, midi out)
pitchwheeltester = vgroup("PITCHWHEEL IN/OUT",valuetest, booltest)
with{
valuetest = hslider("Pitchwheel Value IN  [midi:pitchwheel]", 0, -8192, 8191, 1) : hbargraph("Pitchwheel Value OUT[midi:pitchwheel]", -8192, 8191);
booltest = checkbox("Pitchwheel Bool IN [midi:pitchwheel]") : hbargraph("Pitchwheel Bool OUT [midi:pitchwheel]", 0, 1);
};


