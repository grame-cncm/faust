======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenHorizontalBox("mixer")
	OpenVerticalBox("Ch 0")
	AddMetaDeclareInst(fEntry0, "1", "")
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddNumEntry"pan", fEntry0, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider1, "1", "")
	AddVerticalSlider("0x00", fVslider1, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph0, "2", "")
	AddMetaDeclareInst(fVbargraph0, "unit", "dB")
	AddVerticalBargraph("vbargraph0", fVbargraph0, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox0)
	CloseboxInst
	OpenVerticalBox("Ch 1")
	AddMetaDeclareInst(fEntry1, "1", "")
	AddMetaDeclareInst(fEntry1, "style", "knob")
	AddNumEntry"pan", fEntry1, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider2, "1", "")
	AddVerticalSlider("0x00", fVslider2, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph1, "2", "")
	AddMetaDeclareInst(fVbargraph1, "unit", "dB")
	AddVerticalBargraph("vbargraph1", fVbargraph1, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox1)
	CloseboxInst
	OpenVerticalBox("Ch 2")
	AddMetaDeclareInst(fEntry2, "1", "")
	AddMetaDeclareInst(fEntry2, "style", "knob")
	AddNumEntry"pan", fEntry2, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider3, "1", "")
	AddVerticalSlider("0x00", fVslider3, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph2, "2", "")
	AddMetaDeclareInst(fVbargraph2, "unit", "dB")
	AddVerticalBargraph("vbargraph2", fVbargraph2, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox2)
	CloseboxInst
	OpenVerticalBox("Ch 3")
	AddMetaDeclareInst(fEntry3, "1", "")
	AddMetaDeclareInst(fEntry3, "style", "knob")
	AddNumEntry"pan", fEntry3, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider4, "1", "")
	AddVerticalSlider("0x00", fVslider4, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph3, "2", "")
	AddMetaDeclareInst(fVbargraph3, "unit", "dB")
	AddVerticalBargraph("vbargraph3", fVbargraph3, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox3)
	CloseboxInst
	OpenVerticalBox("Ch 4")
	AddMetaDeclareInst(fEntry4, "1", "")
	AddMetaDeclareInst(fEntry4, "style", "knob")
	AddNumEntry"pan", fEntry4, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider5, "1", "")
	AddVerticalSlider("0x00", fVslider5, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph4, "2", "")
	AddMetaDeclareInst(fVbargraph4, "unit", "dB")
	AddVerticalBargraph("vbargraph4", fVbargraph4, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox4)
	CloseboxInst
	OpenVerticalBox("Ch 5")
	AddMetaDeclareInst(fEntry5, "1", "")
	AddMetaDeclareInst(fEntry5, "style", "knob")
	AddNumEntry"pan", fEntry5, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider6, "1", "")
	AddVerticalSlider("0x00", fVslider6, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph5, "2", "")
	AddMetaDeclareInst(fVbargraph5, "unit", "dB")
	AddVerticalBargraph("vbargraph5", fVbargraph5, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox5)
	CloseboxInst
	OpenVerticalBox("Ch 6")
	AddMetaDeclareInst(fEntry6, "1", "")
	AddMetaDeclareInst(fEntry6, "style", "knob")
	AddNumEntry"pan", fEntry6, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider7, "1", "")
	AddVerticalSlider("0x00", fVslider7, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph6, "2", "")
	AddMetaDeclareInst(fVbargraph6, "unit", "dB")
	AddVerticalBargraph("vbargraph6", fVbargraph6, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox6)
	CloseboxInst
	OpenVerticalBox("Ch 7")
	AddMetaDeclareInst(fEntry7, "1", "")
	AddMetaDeclareInst(fEntry7, "style", "knob")
	AddNumEntry"pan", fEntry7, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider8, "1", "")
	AddVerticalSlider("0x00", fVslider8, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph7, "2", "")
	AddMetaDeclareInst(fVbargraph7, "unit", "dB")
	AddVerticalBargraph("vbargraph7", fVbargraph7, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox7)
	CloseboxInst
	OpenHorizontalBox("stereo out")
	OpenVerticalBox("L")
	AddMetaDeclareInst(fVbargraph8, "2", "")
	AddMetaDeclareInst(fVbargraph8, "unit", "dB")
	AddVerticalBargraph("vbargraph8", fVbargraph8, -7e+01f, 5.0f)
	CloseboxInst
	OpenVerticalBox("R")
	AddMetaDeclareInst(fVbargraph9, "2", "")
	AddMetaDeclareInst(fVbargraph9, "unit", "dB")
	AddVerticalBargraph("vbargraph9", fVbargraph9, -7e+01f, 5.0f)
	CloseboxInst
	AddMetaDeclareInst(fVslider0, "1", "")
	AddVerticalSlider("0x00", fVslider0, 0.0f, -7e+01f, 4.0f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fVslider0)("int", IOTA0)("float[2]", fVec0SE)("FAUSTFLOAT", fEntry0)("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fVslider1)("float[2]", fVec2SE)("int", fSampleRate)("float", fConst0KI)("float[2]", fVec4SE)("FAUSTFLOAT", fVbargraph0)("FAUSTFLOAT", fEntry1)("FAUSTFLOAT", fCheckbox1)("FAUSTFLOAT", fVslider2)("float[2]", fVec6SE)("float[2]", fVec8SE)("FAUSTFLOAT", fVbargraph1)("FAUSTFLOAT", fEntry2)("FAUSTFLOAT", fCheckbox2)("FAUSTFLOAT", fVslider3)("float[2]", fVec10SE)("float[2]", fVec12SE)("FAUSTFLOAT", fVbargraph2)("FAUSTFLOAT", fEntry3)("FAUSTFLOAT", fCheckbox3)("FAUSTFLOAT", fVslider4)("float[2]", fVec14SE)("float[2]", fVec16SE)("FAUSTFLOAT", fVbargraph3)("FAUSTFLOAT", fEntry4)("FAUSTFLOAT", fCheckbox4)("FAUSTFLOAT", fVslider5)("float[2]", fVec18SE)("float[2]", fVec20SE)("FAUSTFLOAT", fVbargraph4)("FAUSTFLOAT", fEntry5)("FAUSTFLOAT", fCheckbox5)("FAUSTFLOAT", fVslider6)("float[2]", fVec22SE)("float[2]", fVec24SE)("FAUSTFLOAT", fVbargraph5)("FAUSTFLOAT", fEntry6)("FAUSTFLOAT", fCheckbox6)("FAUSTFLOAT", fVslider7)("float[2]", fVec26SE)("float[2]", fVec28SE)("FAUSTFLOAT", fVbargraph6)("FAUSTFLOAT", fEntry7)("FAUSTFLOAT", fCheckbox7)("FAUSTFLOAT", fVslider8)("float[2]", fVec30SE)("float[2]", fVec32SE)("FAUSTFLOAT", fVbargraph7)("float[2]", fVec34SE)("FAUSTFLOAT", fVbargraph8)("float[2]", fVec36SE)("FAUSTFLOAT", fVbargraph9)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(8))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 51 Store = 0 Binop = 50 [ { Real(*) = 26 } { Real(+) = 24 } ] Mathop = 25 [ { powf = 9 } { sqrtf = 16 } ] Numbers = 69 Declare = 51 Cast = 25 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry0, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow2BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow1BE, kStack)))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry1, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow6BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct)))))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry2, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow10BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow9BE, kStack)))))
	DeclareVarInst("float", fSlow11BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))))))
	DeclareVarInst("float", fSlow12BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry3, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow14BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow13BE, kStack)))))
	DeclareVarInst("float", fSlow15BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct))))))
	DeclareVarInst("float", fSlow16BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct)))))))
	DeclareVarInst("float", fSlow17BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry4, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow18BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow17BE, kStack)))))
	DeclareVarInst("float", fSlow19BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox4, kStruct))))))
	DeclareVarInst("float", fSlow20BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct)))))))
	DeclareVarInst("float", fSlow21BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry5, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow22BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow21BE, kStack)))))
	DeclareVarInst("float", fSlow23BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox5, kStruct))))))
	DeclareVarInst("float", fSlow24BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct)))))))
	DeclareVarInst("float", fSlow25BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry6, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow26BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow25BE, kStack)))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct))))))
	DeclareVarInst("float", fSlow28BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct)))))))
	DeclareVarInst("float", fSlow29BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry7, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow30BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow29BE, kStack)))))
	DeclareVarInst("float", fSlow31BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct))))))
	DeclareVarInst("float", fSlow32BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct)))))))
	DeclareVarInst("float", fSlow33BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow1BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow34BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow35BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow9BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow36BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow13BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow37BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow17BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow38BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow21BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow39BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow25BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow40BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow29BE, kStack)), Float(1.0f))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 198 Store = 33 Binop = 165 [ { Int(&) = 57 } { Int(+) = 2 } { Int(-) = 19 } { Int(<) = 1 } { Real(*) = 53 } { Real(+) = 33 } ] Mathop = 40 [ { fabsf = 10 } { log10f = 10 } { max_f = 20 } ] Numbers = 108 Declare = 20 Cast = 20 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow4BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp1SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp1SE, kStack)))))
		StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fTemp1SE, kStack)))
		StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp3SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fTemp3SE, kStack)))
		StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp5SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp5SE, kStack)))))
		StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fTemp5SE, kStack)))
		StoreVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow16BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp7SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow15BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp7SE, kStack)))))
		StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fTemp7SE, kStack)))
		StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow20BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp9SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow19BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp9SE, kStack)))))
		StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fTemp9SE, kStack)))
		StoreVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow24BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp11SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp11SE, kStack)))))
		StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fTemp11SE, kStack)))
		StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow28BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp13SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow27BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp13SE, kStack)))))
		StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fTemp13SE, kStack)))
		StoreVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow32BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp15SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp15SE, kStack)))))
		StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fTemp15SE, kStack)))
		DeclareVarInst("float", fTemp17SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp0SE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow14BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow18BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fTemp14SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30BE, kStack)), LoadVarInst(Address(fTemp16SE, kStack))))))
		StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp17SE, kStack)))))
		StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		DeclareVarInst("float", fTemp18SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp0SE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow34BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow35BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow38BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow39BE, kStack)), LoadVarInst(Address(fTemp14SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow40BE, kStack)), LoadVarInst(Address(fTemp16SE, kStack))))))
		StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp18SE, kStack)))))
		StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp17SE, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp18SE, kStack))))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay fVec0SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	// Recursion delay fVec2SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec2SE[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	// Recursion delay fVec4SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec4SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	// Recursion delay fVec6SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec6SE[2], kStruct)
	// Recursion delay fVec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec8SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	// Recursion delay fVec10SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec10SE[2], kStruct)
	// Recursion delay fVec12SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec12SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	// Recursion delay fVec14SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec14SE[2], kStruct)
	// Recursion delay fVec16SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec16SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	// Recursion delay fVec18SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec18SE[2], kStruct)
	// Recursion delay fVec20SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec20SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	// Recursion delay fVec22SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec22SE[2], kStruct)
	// Recursion delay fVec24SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec24SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	// Recursion delay fVec26SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec26SE[2], kStruct)
	// Recursion delay fVec28SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec28SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	// Recursion delay fVec30SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec30SE[2], kStruct)
	// Recursion delay fVec32SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec32SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph7, kStruct)
	// Recursion delay fVec34SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec34SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph8, kStruct)
	// Recursion delay fVec36SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec36SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph9, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry0, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow2BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow1BE, kStack)))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry1, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow6BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct)))))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry2, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow10BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow9BE, kStack)))))
	DeclareVarInst("float", fSlow11BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))))))
	DeclareVarInst("float", fSlow12BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry3, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow14BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow13BE, kStack)))))
	DeclareVarInst("float", fSlow15BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct))))))
	DeclareVarInst("float", fSlow16BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct)))))))
	DeclareVarInst("float", fSlow17BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry4, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow18BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow17BE, kStack)))))
	DeclareVarInst("float", fSlow19BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox4, kStruct))))))
	DeclareVarInst("float", fSlow20BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct)))))))
	DeclareVarInst("float", fSlow21BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry5, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow22BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow21BE, kStack)))))
	DeclareVarInst("float", fSlow23BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox5, kStruct))))))
	DeclareVarInst("float", fSlow24BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct)))))))
	DeclareVarInst("float", fSlow25BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry6, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow26BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow25BE, kStack)))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct))))))
	DeclareVarInst("float", fSlow28BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct)))))))
	DeclareVarInst("float", fSlow29BE, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry7, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow30BE, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow29BE, kStack)))))
	DeclareVarInst("float", fSlow31BE, kStack, BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct))))))
	DeclareVarInst("float", fSlow32BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct)))))))
	DeclareVarInst("float", fSlow33BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow1BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow34BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow35BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow9BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow36BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow13BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow37BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow17BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow38BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow21BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow39BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow25BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow40BE, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow29BE, kStack)), Float(1.0f))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow4BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp1SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp1SE, kStack)))))
			StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fTemp1SE, kStack)))
			StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp3SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fTemp3SE, kStack)))
			StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp5SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp5SE, kStack)))))
			StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fTemp5SE, kStack)))
			StoreVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow16BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp7SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow15BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp7SE, kStack)))))
			StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fTemp7SE, kStack)))
			StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow20BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp9SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow19BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp9SE, kStack)))))
			StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fTemp9SE, kStack)))
			StoreVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow24BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp11SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp11SE, kStack)))))
			StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fTemp11SE, kStack)))
			StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow28BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp13SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow27BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp13SE, kStack)))))
			StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fTemp13SE, kStack)))
			StoreVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow32BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp15SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp15SE, kStack)))))
			StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fTemp15SE, kStack)))
			DeclareVarInst("float", fTemp17SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp0SE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow14BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow18BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fTemp14SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30BE, kStack)), LoadVarInst(Address(fTemp16SE, kStack))))))
			StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp17SE, kStack)))))
			StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			DeclareVarInst("float", fTemp18SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp0SE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow34BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow35BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow38BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow39BE, kStack)), LoadVarInst(Address(fTemp14SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow40BE, kStack)), LoadVarInst(Address(fTemp16SE, kStack))))))
			StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), MinusInst(LoadVarInst(Address(fConst0KI, kStruct)))), FunCallInst("fabsf", LoadVarInst(Address(fTemp18SE, kStack)))))
			StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp17SE, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp18SE, kStack))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 296 bytes
Total heap size = 304 bytes
Stack size in compute = 244 bytes

======= Variable access in Control ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec14SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec18SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec22SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec30SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec14SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec18SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec22SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec30SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 58 write = 1 ratio = 59
Field = fVec0SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 10 write = 0 ratio = 10
Field = fVec4SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec8SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec12SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec14SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec16SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec18SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec20SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec22SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec24SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec28SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec30SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec32SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fVec34SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fVec36SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
