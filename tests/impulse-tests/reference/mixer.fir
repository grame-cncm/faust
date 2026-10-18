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
	AddMetaDeclareInst(fVslider0, "1", "")
	AddVerticalSlider("0x00", fVslider0, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph0, "2", "")
	AddMetaDeclareInst(fVbargraph0, "unit", "dB")
	AddVerticalBargraph("vbargraph0", fVbargraph0, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox0)
	CloseboxInst
	OpenVerticalBox("Ch 1")
	AddMetaDeclareInst(fEntry2, "1", "")
	AddMetaDeclareInst(fEntry2, "style", "knob")
	AddNumEntry"pan", fEntry2, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider2, "1", "")
	AddVerticalSlider("0x00", fVslider2, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph2, "2", "")
	AddMetaDeclareInst(fVbargraph2, "unit", "dB")
	AddVerticalBargraph("vbargraph1", fVbargraph2, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox2)
	CloseboxInst
	OpenVerticalBox("Ch 2")
	AddMetaDeclareInst(fEntry4, "1", "")
	AddMetaDeclareInst(fEntry4, "style", "knob")
	AddNumEntry"pan", fEntry4, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider4, "1", "")
	AddVerticalSlider("0x00", fVslider4, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph4, "2", "")
	AddMetaDeclareInst(fVbargraph4, "unit", "dB")
	AddVerticalBargraph("vbargraph2", fVbargraph4, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox4)
	CloseboxInst
	OpenVerticalBox("Ch 3")
	AddMetaDeclareInst(fEntry6, "1", "")
	AddMetaDeclareInst(fEntry6, "style", "knob")
	AddNumEntry"pan", fEntry6, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider6, "1", "")
	AddVerticalSlider("0x00", fVslider6, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph6, "2", "")
	AddMetaDeclareInst(fVbargraph6, "unit", "dB")
	AddVerticalBargraph("vbargraph3", fVbargraph6, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox6)
	CloseboxInst
	OpenVerticalBox("Ch 4")
	AddMetaDeclareInst(fEntry1, "1", "")
	AddMetaDeclareInst(fEntry1, "style", "knob")
	AddNumEntry"pan", fEntry1, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider1, "1", "")
	AddVerticalSlider("0x00", fVslider1, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph1, "2", "")
	AddMetaDeclareInst(fVbargraph1, "unit", "dB")
	AddVerticalBargraph("vbargraph4", fVbargraph1, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox1)
	CloseboxInst
	OpenVerticalBox("Ch 5")
	AddMetaDeclareInst(fEntry3, "1", "")
	AddMetaDeclareInst(fEntry3, "style", "knob")
	AddNumEntry"pan", fEntry3, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider3, "1", "")
	AddVerticalSlider("0x00", fVslider3, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph3, "2", "")
	AddMetaDeclareInst(fVbargraph3, "unit", "dB")
	AddVerticalBargraph("vbargraph5", fVbargraph3, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox3)
	CloseboxInst
	OpenVerticalBox("Ch 6")
	AddMetaDeclareInst(fEntry5, "1", "")
	AddMetaDeclareInst(fEntry5, "style", "knob")
	AddNumEntry"pan", fEntry5, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider5, "1", "")
	AddVerticalSlider("0x00", fVslider5, 0.0f, -7e+01f, 4.0f, 0.1f)
	AddMetaDeclareInst(fVbargraph5, "2", "")
	AddMetaDeclareInst(fVbargraph5, "unit", "dB")
	AddVerticalBargraph("vbargraph6", fVbargraph5, -7e+01f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox5)
	CloseboxInst
	OpenVerticalBox("Ch 7")
	AddMetaDeclareInst(fEntry7, "1", "")
	AddMetaDeclareInst(fEntry7, "style", "knob")
	AddNumEntry"pan", fEntry7, 0.0f, -9e+01f, 9e+01f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider7, "1", "")
	AddVerticalSlider("0x00", fVslider7, 0.0f, -7e+01f, 4.0f, 0.1f)
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
	AddMetaDeclareInst(fVslider8, "1", "")
	AddVerticalSlider("0x00", fVslider8, 0.0f, -7e+01f, 4.0f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fEntry0)("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fVslider0)("float[2]", fIIR0)("float[2]", fRec1)("FAUSTFLOAT", fVbargraph0)("FAUSTFLOAT", fEntry1)("FAUSTFLOAT", fCheckbox1)("FAUSTFLOAT", fVslider1)("float[2]", fIIR1)("float[2]", fRec2)("FAUSTFLOAT", fVbargraph1)("FAUSTFLOAT", fEntry2)("FAUSTFLOAT", fCheckbox2)("FAUSTFLOAT", fVslider2)("float[2]", fIIR2)("float[2]", fRec3)("FAUSTFLOAT", fVbargraph2)("FAUSTFLOAT", fEntry3)("FAUSTFLOAT", fCheckbox3)("FAUSTFLOAT", fVslider3)("float[2]", fIIR3)("float[2]", fRec4)("FAUSTFLOAT", fVbargraph3)("FAUSTFLOAT", fEntry4)("FAUSTFLOAT", fCheckbox4)("FAUSTFLOAT", fVslider4)("float[2]", fIIR4)("float[2]", fRec5)("FAUSTFLOAT", fVbargraph4)("FAUSTFLOAT", fEntry5)("FAUSTFLOAT", fCheckbox5)("FAUSTFLOAT", fVslider5)("float[2]", fIIR5)("float[2]", fRec6)("FAUSTFLOAT", fVbargraph5)("FAUSTFLOAT", fEntry6)("FAUSTFLOAT", fCheckbox6)("FAUSTFLOAT", fVslider6)("float[2]", fIIR6)("float[2]", fRec7)("FAUSTFLOAT", fVbargraph6)("FAUSTFLOAT", fEntry7)("FAUSTFLOAT", fCheckbox7)("FAUSTFLOAT", fVslider7)("float[2]", fIIR7)("float[2]", fRec8)("FAUSTFLOAT", fVbargraph7)("FAUSTFLOAT", fVslider8)("float[2]", fIIR8)("float[2]", fRec0)("FAUSTFLOAT", fVbargraph8)("float[2]", fRec9)("FAUSTFLOAT", fVbargraph9)>)

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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR8, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 59 Store = 0 Binop = 49 [ { Real(*) = 17 } { Real(+) = 16 } { Real(-) = 8 } { Real(>) = 8 } ] Mathop = 59 [ { max_f = 17 } { min_f = 17 } { powf = 9 } { sqrtf = 16 } ] Numbers = 102 Declare = 59 Cast = 33 Select = 0 Loop = 0

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
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow0, kStack)))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow9, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))))))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow10, kStack)))))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow12, kStack))))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))))))
	DeclareVarInst("float", fSlow16, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow15, kStack)))))
	DeclareVarInst("float", fSlow17, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow17, kStack))))
	DeclareVarInst("float", fSlow19, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))))))
	DeclareVarInst("float", fSlow21, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow20, kStack)))))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox4, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("float", fSlow24, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry5, kStruct))))))))
	DeclareVarInst("float", fSlow26, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow25, kStack)))))
	DeclareVarInst("float", fSlow27, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox5, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow29, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry6, kStruct))))))))
	DeclareVarInst("float", fSlow31, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow30, kStack)))))
	DeclareVarInst("float", fSlow32, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow32, kStack))))
	DeclareVarInst("float", fSlow34, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))))
	DeclareVarInst("float", fSlow35, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry7, kStruct))))))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow35, kStack)))))
	DeclareVarInst("float", fSlow37, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow37, kStack))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))))
	DeclareVarInst("float", fSlow41, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow0, kStack)))))
	DeclareVarInst("float", fSlow42, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow43, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow10, kStack)))))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow15, kStack)))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow20, kStack)))))
	DeclareVarInst("float", fSlow46, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow25, kStack)))))
	DeclareVarInst("float", fSlow47, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow30, kStack)))))
	DeclareVarInst("float", fSlow48, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow35, kStack)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 168 Store = 51 Binop = 97 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 62 } { Real(+) = 23 } { Real(-) = 10 } ] Mathop = 40 [ { fabsf = 10 } { log10f = 10 } { max_f = 20 } ] Numbers = 126 Declare = 29 Cast = 20 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp0, kStack))))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp1, kStack)))))
		StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp2, kStack, LoadVarInst(Address(fTemp1, kStack)))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp3, kStack))))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp4, kStack)))))
		StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp5, kStack, LoadVarInst(Address(fTemp4, kStack)))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("+", LoadVarInst(Address(fSlow14, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp6, kStack))))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp7, kStack)))))
		StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp8, kStack, LoadVarInst(Address(fTemp7, kStack)))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("+", LoadVarInst(Address(fSlow19, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp9, kStack)))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp9, kStack))))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp10, kStack)))))
		StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp11, kStack, LoadVarInst(Address(fTemp10, kStack)))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("+", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp12, kStack))))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp13, kStack)))))
		StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp14, kStack, LoadVarInst(Address(fTemp13, kStack)))
		DeclareVarInst("float", fTemp15, kStack, BinopInst("+", LoadVarInst(Address(fSlow29, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp15, kStack)))
		DeclareVarInst("float", fTemp16, kStack, BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp15, kStack))))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp16, kStack)))))
		StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp17, kStack, LoadVarInst(Address(fTemp16, kStack)))
		DeclareVarInst("float", fTemp18, kStack, BinopInst("+", LoadVarInst(Address(fSlow34, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp18, kStack)))
		DeclareVarInst("float", fTemp19, kStack, BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp18, kStack))))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp19, kStack)))))
		StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp20, kStack, LoadVarInst(Address(fTemp19, kStack)))
		DeclareVarInst("float", fTemp21, kStack, BinopInst("+", LoadVarInst(Address(fSlow39, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp21, kStack)))
		DeclareVarInst("float", fTemp22, kStack, BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp21, kStack))))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp22, kStack)))))
		StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp23, kStack, LoadVarInst(Address(fTemp22, kStack)))
		DeclareVarInst("float", fTemp24, kStack, BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp24, kStack)))
		DeclareVarInst("float", fTemp25, kStack, BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp24, kStack))))
		DeclareVarInst("float", fTemp26, kStack, BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fTemp2, kStack))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), LoadVarInst(Address(fTemp8, kStack))), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fTemp11, kStack))))), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fTemp14, kStack))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fTemp17, kStack)))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fTemp20, kStack))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fTemp23, kStack)))))), LoadVarInst(Address(fTemp25, kStack))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp26, kStack)))))
		StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp26, kStack))))
		DeclareVarInst("float", fTemp27, kStack, BinopInst("*", LoadVarInst(Address(fTemp25, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fTemp2, kStack))), BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fTemp8, kStack))), BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fTemp11, kStack))))), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fTemp14, kStack))), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fTemp17, kStack)))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fTemp20, kStack))), BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fTemp23, kStack))))))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp27, kStack)))))
		StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp27, kStack))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(1)], LoadVarInst(Address(fIIR8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("float", fIIR0[2], kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("float", fIIR1[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("float", fIIR2[2], kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("float", fIIR3[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("float", fIIR4[2], kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("float", fIIR5[2], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("float", fIIR6[2], kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("float", fIIR7[2], kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("float", fIIR8[2], kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph8, kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph9, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR8, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow0, kStack)))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow9, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))))))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow10, kStack)))))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow12, kStack))))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))))))
	DeclareVarInst("float", fSlow16, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow15, kStack)))))
	DeclareVarInst("float", fSlow17, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow17, kStack))))
	DeclareVarInst("float", fSlow19, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))))))
	DeclareVarInst("float", fSlow21, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow20, kStack)))))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox4, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("float", fSlow24, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry5, kStruct))))))))
	DeclareVarInst("float", fSlow26, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow25, kStack)))))
	DeclareVarInst("float", fSlow27, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox5, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow29, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry6, kStruct))))))))
	DeclareVarInst("float", fSlow31, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow30, kStack)))))
	DeclareVarInst("float", fSlow32, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow32, kStack))))
	DeclareVarInst("float", fSlow34, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))))
	DeclareVarInst("float", fSlow35, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", Float(-9e+01f), FunCallInst("max_f", Float(-9e+01f), FunCallInst("min_f", Float(9e+01f), CastInst("float", LoadVarInst(Address(fEntry7, kStruct))))))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("sqrtf", NegInst(LoadVarInst(Address(fSlow35, kStack)))))
	DeclareVarInst("float", fSlow37, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow37, kStack))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))))
	DeclareVarInst("float", fSlow41, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow0, kStack)))))
	DeclareVarInst("float", fSlow42, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow43, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow10, kStack)))))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow15, kStack)))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow20, kStack)))))
	DeclareVarInst("float", fSlow46, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow25, kStack)))))
	DeclareVarInst("float", fSlow47, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow30, kStack)))))
	DeclareVarInst("float", fSlow48, kStack, FunCallInst("sqrtf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow35, kStack)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp0, kStack))))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp1, kStack)))))
			StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp2, kStack, LoadVarInst(Address(fTemp1, kStack)))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp3, kStack))))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp4, kStack)))))
			StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp5, kStack, LoadVarInst(Address(fTemp4, kStack)))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("+", LoadVarInst(Address(fSlow14, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp6, kStack))))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp7, kStack)))))
			StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp8, kStack, LoadVarInst(Address(fTemp7, kStack)))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("+", LoadVarInst(Address(fSlow19, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp9, kStack)))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp9, kStack))))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp10, kStack)))))
			StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp11, kStack, LoadVarInst(Address(fTemp10, kStack)))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("+", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp12, kStack))))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp13, kStack)))))
			StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp14, kStack, LoadVarInst(Address(fTemp13, kStack)))
			DeclareVarInst("float", fTemp15, kStack, BinopInst("+", LoadVarInst(Address(fSlow29, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp15, kStack)))
			DeclareVarInst("float", fTemp16, kStack, BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp15, kStack))))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp16, kStack)))))
			StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp17, kStack, LoadVarInst(Address(fTemp16, kStack)))
			DeclareVarInst("float", fTemp18, kStack, BinopInst("+", LoadVarInst(Address(fSlow34, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp18, kStack)))
			DeclareVarInst("float", fTemp19, kStack, BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp18, kStack))))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp19, kStack)))))
			StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp20, kStack, LoadVarInst(Address(fTemp19, kStack)))
			DeclareVarInst("float", fTemp21, kStack, BinopInst("+", LoadVarInst(Address(fSlow39, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp21, kStack)))
			DeclareVarInst("float", fTemp22, kStack, BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp21, kStack))))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp22, kStack)))))
			StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp23, kStack, LoadVarInst(Address(fTemp22, kStack)))
			DeclareVarInst("float", fTemp24, kStack, BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp24, kStack)))
			DeclareVarInst("float", fTemp25, kStack, BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp24, kStack))))
			DeclareVarInst("float", fTemp26, kStack, BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fTemp2, kStack))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), LoadVarInst(Address(fTemp8, kStack))), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fTemp11, kStack))))), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fTemp14, kStack))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fTemp17, kStack)))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fTemp20, kStack))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fTemp23, kStack)))))), LoadVarInst(Address(fTemp25, kStack))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp26, kStack)))))
			StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp26, kStack))))
			DeclareVarInst("float", fTemp27, kStack, BinopInst("*", LoadVarInst(Address(fTemp25, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fTemp2, kStack))), BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fTemp8, kStack))), BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fTemp11, kStack))))), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fTemp14, kStack))), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fTemp17, kStack)))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fTemp20, kStack))), BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fTemp23, kStack))))))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp27, kStack)))))
			StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp27, kStack))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(1)], LoadVarInst(Address(fIIR8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 296 bytes
Total heap size = 300 bytes
Stack size in compute = 276 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 10 write = 0 ratio = 10
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec3 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR8 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fRec9 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            343
  eval() cache hits:       61 (17.7843%)
  eval() cache misses:     282
  Loop detector calls:     282
  Stack detector calls:    282

--- Phase 3: Propagation ---
  propagate() calls:       1137
  propagate() cache hits:  33 (2.90237%)
  propagate() cache misses:1104

--- Box Type Computation ---
  getBoxType() calls:      1276
  getBoxType() cache hits: 1142 (89.4984%)
  getBoxType() computed:   134

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       27

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           10418
  Trees reused (hash):     25306 (70.8375% reuse rate)
  Property set ops:        4791
  Property get ops:        11658

--- Iteration Constructs ---
  par() iterations:        8
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
