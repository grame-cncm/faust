======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("FAUST MIDI TESTER")
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	OpenVerticalBox("CTRL IN/OUT")
	AddMetaDeclareInst(fCheckbox0, "midi", "ctrl 100")
	AddCheckButtonInst("Ctrl Bool IN (Ctrl 100)"fCheckbox0)
	AddMetaDeclareInst(fHbargraph1, "midi", "ctrl 101")
	AddHorizontalBargraph("Ctrl Bool OUT (Ctrl 101)", fHbargraph1, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "midi", "ctrl 50")
	AddHorizontalSlider("Ctrl Value IN (Ctrl 50)", fHslider0, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph0, "midi", "ctrl 51")
	AddHorizontalBargraph("Ctrl Value OUT (Ctrl 51)", fHbargraph0, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("MIDI SYNC (IN)")
	AddMetaDeclareInst(fCheckbox4, "midi", "start")
	AddMetaDeclareInst(fCheckbox4, "midi", "stop")
	AddCheckButtonInst("MIDI START/STOP"fCheckbox4)
	AddMetaDeclareInst(fCheckbox3, "midi", "clock")
	AddCheckButtonInst("MIDI clock signal"fCheckbox3)
	CloseboxInst
	OpenVerticalBox("NOTE OFF IN/OUT")
	AddMetaDeclareInst(fCheckbox2, "midi", "keyoff 100")
	AddCheckButtonInst("NoteOff Bool IN (Note 100)"fCheckbox2)
	AddMetaDeclareInst(fHbargraph5, "midi", "keyoff 101")
	AddHorizontalBargraph("NoteOff Bool OUT (Note 101)", fHbargraph5, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider2, "midi", "keyoff 50")
	AddHorizontalSlider("NoteOff Value IN (Note 50)", fHslider2, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph4, "midi", "keyoff 51")
	AddHorizontalBargraph("NoteOff Value OUT (Note 51)", fHbargraph4, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("NOTE ON IN/OUT")
	AddMetaDeclareInst(fCheckbox1, "midi", "keyon 100")
	AddCheckButtonInst("NoteOn Bool IN (Note 100)"fCheckbox1)
	AddMetaDeclareInst(fHbargraph3, "midi", "keyon 101")
	AddHorizontalBargraph("NoteOn Bool OUT (Note 101)", fHbargraph3, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "midi", "keyon 50")
	AddHorizontalSlider("NoteOn Value IN (Note 50)", fHslider1, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph2, "midi", "keyon 51")
	AddHorizontalBargraph("NoteOn Value OUT (Note 51)", fHbargraph2, 0.0f, 127.0f)
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	OpenVerticalBox("CHANNEL AFTERTOUCH (CHAT) IN/OUT")
	AddMetaDeclareInst(fCheckbox7, "midi", "chanpress 100")
	AddCheckButtonInst("Note CHAT Bool IN (Note 100)"fCheckbox7)
	AddMetaDeclareInst(fHbargraph11, "midi", "chanpress 101")
	AddHorizontalBargraph("Note CHAT Bool OUT (Note 101)", fHbargraph11, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider5, "midi", "chanpress 50")
	AddHorizontalSlider("Note CHAT Value IN (Note 50)", fHslider5, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph10, "midi", "chanpress 51")
	AddHorizontalBargraph("Note CHAT Value OUT (Note 51)", fHbargraph10, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT")
	AddMetaDeclareInst(fCheckbox5, "midi", "keypress 100")
	AddCheckButtonInst("Note KAT Bool IN (Note 100)"fCheckbox5)
	AddMetaDeclareInst(fHbargraph7, "midi", "keypress 101")
	AddHorizontalBargraph("Note KAT Bool OUT (Note 101)", fHbargraph7, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider3, "midi", "keypress 50")
	AddHorizontalSlider("Note KAT Value IN (Note 50)", fHslider3, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph6, "midi", "keypress 51")
	AddHorizontalBargraph("Note KAT Value OUT (Note 51)", fHbargraph6, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("PITCHWHEEL IN/OUT")
	AddMetaDeclareInst(fCheckbox8, "midi", "pitchwheel")
	AddCheckButtonInst("Pitchwheel Bool IN"fCheckbox8)
	AddMetaDeclareInst(fHbargraph13, "midi", "pitchwheel")
	AddHorizontalBargraph("Pitchwheel Bool OUT", fHbargraph13, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider6, "midi", "pitchwheel")
	AddHorizontalSlider("Pitchwheel Value IN", fHslider6, 0.0f, -8192.0f, 8191.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph12, "midi", "pitchwheel")
	AddHorizontalBargraph("Pitchwheel Value OUT", fHbargraph12, -8192.0f, 8191.0f)
	CloseboxInst
	OpenVerticalBox("PROGRAM CHANGE (PC) IN/OUT")
	AddMetaDeclareInst(fCheckbox6, "midi", "pgm 100")
	AddCheckButtonInst("ProgramChange Bool IN (PC 100)"fCheckbox6)
	AddMetaDeclareInst(fHbargraph9, "midi", "pgm 101")
	AddHorizontalBargraph("ProgramChange Bool OUT (PC 101)", fHbargraph9, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider4, "midi", "pgm 50")
	AddHorizontalSlider("ProgramChange Value IN (PC 50)", fHslider4, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph8, "midi", "pgm 51")
	AddHorizontalBargraph("ProgramChange Value OUT (PC 51)", fHbargraph8, 0.0f, 127.0f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHbargraph0)("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fHbargraph1)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fHbargraph2)("FAUSTFLOAT", fCheckbox1)("FAUSTFLOAT", fHbargraph3)("FAUSTFLOAT", fHslider2)("FAUSTFLOAT", fHbargraph4)("FAUSTFLOAT", fCheckbox2)("FAUSTFLOAT", fHbargraph5)("FAUSTFLOAT", fCheckbox3)("FAUSTFLOAT", fCheckbox4)("FAUSTFLOAT", fHslider3)("FAUSTFLOAT", fHbargraph6)("FAUSTFLOAT", fCheckbox5)("FAUSTFLOAT", fHbargraph7)("FAUSTFLOAT", fHslider4)("FAUSTFLOAT", fHbargraph8)("FAUSTFLOAT", fCheckbox6)("FAUSTFLOAT", fHbargraph9)("FAUSTFLOAT", fHslider5)("FAUSTFLOAT", fHbargraph10)("FAUSTFLOAT", fCheckbox7)("FAUSTFLOAT", fHbargraph11)("FAUSTFLOAT", fHslider6)("FAUSTFLOAT", fHbargraph12)("FAUSTFLOAT", fCheckbox8)("FAUSTFLOAT", fHbargraph13)("float", fConst0)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), Float(0.0f))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox8, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Compute control begin ==========

Instructions complexity : Load = 16 Store = 14 Binop = 7 [ { Real(>) = 7 } ] Mathop = 14 [ { max_f = 7 } { min_f = 7 } ] Numbers = 23 Declare = 2 Cast = 35 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	StoreVarInst(Address(fHbargraph0, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
	StoreVarInst(Address(fHbargraph1, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph2, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	StoreVarInst(Address(fHbargraph3, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph4, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	StoreVarInst(Address(fHbargraph5, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph6, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))))
	StoreVarInst(Address(fHbargraph7, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox5, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph8, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))))
	StoreVarInst(Address(fHbargraph9, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph10, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))))
	StoreVarInst(Address(fHbargraph11, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph12, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(-8192.0f), FunCallInst("min_f", Float(8191.0f), CastInst("float", LoadVarInst(Address(fHslider6, kStruct)))))))
	StoreVarInst(Address(fHbargraph13, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox8, kStruct))), Float(0.0f)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 5 Store = 2 Binop = 2 [ { Int(+) = 1 } { Int(<) = 1 } ] Mathop = 0 Numbers = 2 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fConst0, kStruct))))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Post compute DSP begin ==========

BlockInst 
EndBlockInst

======= Post compute DSP end ==========

======= Flatten FIR begin ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph11, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph13, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), Float(0.0f))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fCheckbox7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox8, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	StoreVarInst(Address(fHbargraph0, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
	StoreVarInst(Address(fHbargraph1, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph2, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	StoreVarInst(Address(fHbargraph3, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph4, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	StoreVarInst(Address(fHbargraph5, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph6, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))))
	StoreVarInst(Address(fHbargraph7, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox5, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph8, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))))
	StoreVarInst(Address(fHbargraph9, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph10, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))))
	StoreVarInst(Address(fHbargraph11, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct))), Float(0.0f)))))
	StoreVarInst(Address(fHbargraph12, kStruct), CastInst("FAUSTFLOAT", FunCallInst("max_f", Float(-8192.0f), FunCallInst("min_f", Float(8191.0f), CastInst("float", LoadVarInst(Address(fHslider6, kStruct)))))))
	StoreVarInst(Address(fHbargraph13, kStruct), CastInst("FAUSTFLOAT", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox8, kStruct))), Float(0.0f)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fConst0, kStruct))))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 124 bytes
Total heap size = 128 bytes
Stack size in compute = 16 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph0 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph1 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph2 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph3 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph4 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph5 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph6 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph7 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph8 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph9 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph10 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph11 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph12 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph13 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            338
  eval() cache hits:       73 (21.5976%)
  eval() cache misses:     265
  Loop detector calls:     265
  Stack detector calls:    265

--- Phase 3: Propagation ---
  propagate() calls:       184
  propagate() cache hits:  95 (51.6304%)
  propagate() cache misses:89

--- Box Type Computation ---
  getBoxType() calls:      252
  getBoxType() cache hits: 164 (65.0794%)
  getBoxType() computed:   88

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       33

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           2087
  Trees reused (hash):     6047 (74.3423% reuse rate)
  Property set ops:        802
  Property get ops:        1800

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
