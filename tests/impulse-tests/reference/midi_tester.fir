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
	AddMetaDeclareInst(fCheckbox8, "midi", "ctrl 100")
	AddCheckButtonInst("Ctrl Bool IN (Ctrl 100)"fCheckbox8)
	AddMetaDeclareInst(fHbargraph13, "midi", "ctrl 101")
	AddHorizontalBargraph("Ctrl Bool OUT (Ctrl 101)", fHbargraph13, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider6, "midi", "ctrl 50")
	AddHorizontalSlider("Ctrl Value IN (Ctrl 50)", fHslider6, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph12, "midi", "ctrl 51")
	AddHorizontalBargraph("Ctrl Value OUT (Ctrl 51)", fHbargraph12, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("MIDI SYNC (IN)")
	AddMetaDeclareInst(fCheckbox4, "midi", "start")
	AddMetaDeclareInst(fCheckbox4, "midi", "stop")
	AddCheckButtonInst("MIDI START/STOP"fCheckbox4)
	AddMetaDeclareInst(fCheckbox5, "midi", "clock")
	AddCheckButtonInst("MIDI clock signal"fCheckbox5)
	CloseboxInst
	OpenVerticalBox("NOTE OFF IN/OUT")
	AddMetaDeclareInst(fCheckbox6, "midi", "keyoff 100")
	AddCheckButtonInst("NoteOff Bool IN (Note 100)"fCheckbox6)
	AddMetaDeclareInst(fHbargraph8, "midi", "keyoff 101")
	AddHorizontalBargraph("NoteOff Bool OUT (Note 101)", fHbargraph8, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider4, "midi", "keyoff 50")
	AddHorizontalSlider("NoteOff Value IN (Note 50)", fHslider4, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph9, "midi", "keyoff 51")
	AddHorizontalBargraph("NoteOff Value OUT (Note 51)", fHbargraph9, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("NOTE ON IN/OUT")
	AddMetaDeclareInst(fCheckbox7, "midi", "keyon 100")
	AddCheckButtonInst("NoteOn Bool IN (Note 100)"fCheckbox7)
	AddMetaDeclareInst(fHbargraph10, "midi", "keyon 101")
	AddHorizontalBargraph("NoteOn Bool OUT (Note 101)", fHbargraph10, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider5, "midi", "keyon 50")
	AddHorizontalSlider("NoteOn Value IN (Note 50)", fHslider5, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph11, "midi", "keyon 51")
	AddHorizontalBargraph("NoteOn Value OUT (Note 51)", fHbargraph11, 0.0f, 127.0f)
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	OpenVerticalBox("CHANNEL AFTERTOUCH (CHAT) IN/OUT")
	AddMetaDeclareInst(fCheckbox1, "midi", "chanpress 100")
	AddCheckButtonInst("Note CHAT Bool IN (Note 100)"fCheckbox1)
	AddMetaDeclareInst(fHbargraph2, "midi", "chanpress 101")
	AddHorizontalBargraph("Note CHAT Bool OUT (Note 101)", fHbargraph2, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "midi", "chanpress 50")
	AddHorizontalSlider("Note CHAT Value IN (Note 50)", fHslider1, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph3, "midi", "chanpress 51")
	AddHorizontalBargraph("Note CHAT Value OUT (Note 51)", fHbargraph3, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT")
	AddMetaDeclareInst(fCheckbox3, "midi", "keypress 100")
	AddCheckButtonInst("Note KAT Bool IN (Note 100)"fCheckbox3)
	AddMetaDeclareInst(fHbargraph6, "midi", "keypress 101")
	AddHorizontalBargraph("Note KAT Bool OUT (Note 101)", fHbargraph6, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider3, "midi", "keypress 50")
	AddHorizontalSlider("Note KAT Value IN (Note 50)", fHslider3, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph7, "midi", "keypress 51")
	AddHorizontalBargraph("Note KAT Value OUT (Note 51)", fHbargraph7, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("PITCHWHEEL IN/OUT")
	AddMetaDeclareInst(fCheckbox0, "midi", "pitchwheel")
	AddCheckButtonInst("Pitchwheel Bool IN"fCheckbox0)
	AddMetaDeclareInst(fHbargraph0, "midi", "pitchwheel")
	AddHorizontalBargraph("Pitchwheel Bool OUT", fHbargraph0, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "midi", "pitchwheel")
	AddHorizontalSlider("Pitchwheel Value IN", fHslider0, 0.0f, -8192.0f, 8191.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph1, "midi", "pitchwheel")
	AddHorizontalBargraph("Pitchwheel Value OUT", fHbargraph1, -8192.0f, 8191.0f)
	CloseboxInst
	OpenVerticalBox("PROGRAM CHANGE (PC) IN/OUT")
	AddMetaDeclareInst(fCheckbox2, "midi", "pgm 100")
	AddCheckButtonInst("ProgramChange Bool IN (PC 100)"fCheckbox2)
	AddMetaDeclareInst(fHbargraph4, "midi", "pgm 101")
	AddHorizontalBargraph("ProgramChange Bool OUT (PC 101)", fHbargraph4, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider2, "midi", "pgm 50")
	AddHorizontalSlider("ProgramChange Value IN (PC 50)", fHslider2, 6e+01f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph5, "midi", "pgm 51")
	AddHorizontalBargraph("ProgramChange Value OUT (PC 51)", fHbargraph5, 0.0f, 127.0f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fHbargraph0)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHbargraph1)("FAUSTFLOAT", fCheckbox1)("FAUSTFLOAT", fHbargraph2)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fHbargraph3)("FAUSTFLOAT", fCheckbox2)("FAUSTFLOAT", fHbargraph4)("FAUSTFLOAT", fHslider2)("FAUSTFLOAT", fHbargraph5)("FAUSTFLOAT", fCheckbox3)("FAUSTFLOAT", fHbargraph6)("FAUSTFLOAT", fHslider3)("FAUSTFLOAT", fHbargraph7)("FAUSTFLOAT", fCheckbox4)("FAUSTFLOAT", fCheckbox5)("FAUSTFLOAT", fCheckbox6)("FAUSTFLOAT", fHbargraph8)("FAUSTFLOAT", fHslider4)("FAUSTFLOAT", fHbargraph9)("FAUSTFLOAT", fCheckbox7)("FAUSTFLOAT", fHbargraph10)("FAUSTFLOAT", fHslider5)("FAUSTFLOAT", fHbargraph11)("FAUSTFLOAT", fHslider6)("FAUSTFLOAT", fHbargraph12)("FAUSTFLOAT", fCheckbox8)("FAUSTFLOAT", fHbargraph13)("float", fConst0)("int", fSampleRate)>)

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
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Compute control begin ==========

Instructions complexity : Load = 16 Store = 14 Binop = 0 Mathop = 0 Numbers = 2 Declare = 2 Cast = 28 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	StoreVarInst(Address(fHbargraph0, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	StoreVarInst(Address(fHbargraph1, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	StoreVarInst(Address(fHbargraph2, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct)))))
	StoreVarInst(Address(fHbargraph3, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	StoreVarInst(Address(fHbargraph4, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct)))))
	StoreVarInst(Address(fHbargraph5, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	StoreVarInst(Address(fHbargraph6, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct)))))
	StoreVarInst(Address(fHbargraph7, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	StoreVarInst(Address(fHbargraph8, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct)))))
	StoreVarInst(Address(fHbargraph9, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	StoreVarInst(Address(fHbargraph10, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct)))))
	StoreVarInst(Address(fHbargraph11, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))
	StoreVarInst(Address(fHbargraph12, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider6, kStruct)))))
	StoreVarInst(Address(fHbargraph13, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox8, kStruct)))))
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
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
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
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fCheckbox8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	StoreVarInst(Address(fHbargraph0, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	StoreVarInst(Address(fHbargraph1, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	StoreVarInst(Address(fHbargraph2, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct)))))
	StoreVarInst(Address(fHbargraph3, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	StoreVarInst(Address(fHbargraph4, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct)))))
	StoreVarInst(Address(fHbargraph5, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	StoreVarInst(Address(fHbargraph6, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct)))))
	StoreVarInst(Address(fHbargraph7, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	StoreVarInst(Address(fHbargraph8, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct)))))
	StoreVarInst(Address(fHbargraph9, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	StoreVarInst(Address(fHbargraph10, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct)))))
	StoreVarInst(Address(fHbargraph11, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))
	StoreVarInst(Address(fHbargraph12, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fHslider6, kStruct)))))
	StoreVarInst(Address(fHbargraph13, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(fCheckbox8, kStruct)))))
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

Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph0 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph1 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph2 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph3 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph4 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph5 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph6 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph7 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph8 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph9 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph10 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph11 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph12 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fCheckbox8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHbargraph13 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
