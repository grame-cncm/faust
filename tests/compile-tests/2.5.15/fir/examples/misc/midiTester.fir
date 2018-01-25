======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

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
	AddHorizontalSlider("Ctrl Value IN (Ctrl 50)", fHslider6, 60.0f, 0.0f, 127.0f, 1.0f)
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
	AddHorizontalSlider("NoteOff Value IN (Note 50)", fHslider4, 60.0f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph9, "midi", "keyoff 51")
	AddHorizontalBargraph("NoteOff Value OUT (Note 51)", fHbargraph9, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("NOTE ON IN/OUT")
	AddMetaDeclareInst(fCheckbox7, "midi", "keyon 100")
	AddCheckButtonInst("NoteOn Bool IN (Note 100)"fCheckbox7)
	AddMetaDeclareInst(fHbargraph10, "midi", "keyon 101")
	AddHorizontalBargraph("NoteOn Bool OUT (Note 101)", fHbargraph10, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider5, "midi", "keyon 50")
	AddHorizontalSlider("NoteOn Value IN (Note 50)", fHslider5, 60.0f, 0.0f, 127.0f, 1.0f)
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
	AddHorizontalSlider("Note CHAT Value IN (Note 50)", fHslider1, 60.0f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph3, "midi", "chanpress 51")
	AddHorizontalBargraph("Note CHAT Value OUT (Note 51)", fHbargraph3, 0.0f, 127.0f)
	CloseboxInst
	OpenVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT")
	AddMetaDeclareInst(fCheckbox3, "midi", "keypress 100")
	AddCheckButtonInst("Note KAT Bool IN (Note 100)"fCheckbox3)
	AddMetaDeclareInst(fHbargraph6, "midi", "keypress 101")
	AddHorizontalBargraph("Note KAT Bool OUT (Note 101)", fHbargraph6, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider3, "midi", "keypress 50")
	AddHorizontalSlider("Note KAT Value IN (Note 50)", fHslider3, 60.0f, 0.0f, 127.0f, 1.0f)
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
	AddHorizontalSlider("ProgramChange Value IN (PC 50)", fHslider2, 60.0f, 0.0f, 127.0f, 1.0f)
	AddMetaDeclareInst(fHbargraph5, "midi", "pgm 51")
	AddHorizontalBargraph("ProgramChange Value OUT (PC 51)", fHbargraph5, 0.0f, 127.0f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph1)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph3)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph5)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph7)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox4)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox5)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph8)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph9)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph10)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph11)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph12)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox8)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph13)
	DeclareVarInst(struct, "int", iConst0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getInputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(0))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getOutputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, iConst0, Int32(0))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox8, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 16
Store = 14
Binop = 0
Numbers = 0
Declare = 2
Cast = 28
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	StoreVarInst(struct, fHbargraph1, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider0))))
	StoreVarInst(struct, fHbargraph2, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox1))))
	StoreVarInst(struct, fHbargraph3, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider1))))
	StoreVarInst(struct, fHbargraph4, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox2))))
	StoreVarInst(struct, fHbargraph5, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider2))))
	StoreVarInst(struct, fHbargraph6, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox3))))
	StoreVarInst(struct, fHbargraph7, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider3))))
	StoreVarInst(struct, fHbargraph8, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox6))))
	StoreVarInst(struct, fHbargraph9, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider4))))
	StoreVarInst(struct, fHbargraph10, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox7))))
	StoreVarInst(struct, fHbargraph11, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider5))))
	StoreVarInst(struct, fHbargraph12, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider6))))
	StoreVarInst(struct, fHbargraph13, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox8))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 5
Store = 2
Binop = 2
Numbers = 2
Declare = 1
Cast = 1
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst0)))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph1)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph3)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph5)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph7)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox4)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox5)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph8)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph9)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph10)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph11)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph12)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox8)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph13)
	DeclareVarInst(struct, "int", iConst0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, iConst0, Int32(0))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fCheckbox8, CastInst("FAUSTFLOAT", Double(0.0f)))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	StoreVarInst(struct, fHbargraph1, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider0))))
	StoreVarInst(struct, fHbargraph2, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox1))))
	StoreVarInst(struct, fHbargraph3, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider1))))
	StoreVarInst(struct, fHbargraph4, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox2))))
	StoreVarInst(struct, fHbargraph5, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider2))))
	StoreVarInst(struct, fHbargraph6, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox3))))
	StoreVarInst(struct, fHbargraph7, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider3))))
	StoreVarInst(struct, fHbargraph8, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox6))))
	StoreVarInst(struct, fHbargraph9, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider4))))
	StoreVarInst(struct, fHbargraph10, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox7))))
	StoreVarInst(struct, fHbargraph11, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider5))))
	StoreVarInst(struct, fHbargraph12, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fHslider6))))
	StoreVarInst(struct, fHbargraph13, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(struct, fCheckbox8))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst0)))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 120 bytes
Heap size = 128 bytes
Stack size in compute = 16 bytes

