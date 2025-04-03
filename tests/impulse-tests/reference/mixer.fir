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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fVslider0)("float[2]", fRec1)("FAUSTFLOAT", fEntry0)("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fVslider1)("float[2]", fRec3)("float[2]", fRec2)("FAUSTFLOAT", fVbargraph0)("FAUSTFLOAT", fEntry1)("FAUSTFLOAT", fCheckbox1)("FAUSTFLOAT", fVslider2)("float[2]", fRec5)("float[2]", fRec4)("FAUSTFLOAT", fVbargraph1)("FAUSTFLOAT", fEntry2)("FAUSTFLOAT", fCheckbox2)("FAUSTFLOAT", fVslider3)("float[2]", fRec7)("float[2]", fRec6)("FAUSTFLOAT", fVbargraph2)("FAUSTFLOAT", fEntry3)("FAUSTFLOAT", fCheckbox3)("FAUSTFLOAT", fVslider4)("float[2]", fRec9)("float[2]", fRec8)("FAUSTFLOAT", fVbargraph3)("FAUSTFLOAT", fEntry4)("FAUSTFLOAT", fCheckbox4)("FAUSTFLOAT", fVslider5)("float[2]", fRec11)("float[2]", fRec10)("FAUSTFLOAT", fVbargraph4)("FAUSTFLOAT", fEntry5)("FAUSTFLOAT", fCheckbox5)("FAUSTFLOAT", fVslider6)("float[2]", fRec13)("float[2]", fRec12)("FAUSTFLOAT", fVbargraph5)("FAUSTFLOAT", fEntry6)("FAUSTFLOAT", fCheckbox6)("FAUSTFLOAT", fVslider7)("float[2]", fRec15)("float[2]", fRec14)("FAUSTFLOAT", fVbargraph6)("FAUSTFLOAT", fEntry7)("FAUSTFLOAT", fCheckbox7)("FAUSTFLOAT", fVslider8)("float[2]", fRec17)("float[2]", fRec16)("FAUSTFLOAT", fVbargraph7)("float[2]", fRec0)("FAUSTFLOAT", fVbargraph8)("float[2]", fRec18)("FAUSTFLOAT", fVbargraph9)>)

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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
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
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 51 Store = 0 Binop = 50 [ { Real(*) = 26 } { Real(+) = 16 } { Real(-) = 8 } ] Mathop = 25 [ { powf = 9 } { sqrtf = 16 } ] Numbers = 69 Declare = 51 Cast = 25 Select = 0 Loop = 0

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
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry0, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow1, kStack)))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry1, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct)))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry2, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow9, kStack)))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct)))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry3, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow13, kStack)))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct)))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct)))))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry4, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow18, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow17, kStack)))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox4, kStruct)))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct)))))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry5, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow22, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow21, kStack)))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox5, kStruct)))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct)))))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry6, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow26, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow25, kStack)))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct)))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct)))))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry7, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow30, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow29, kStack)))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct)))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct)))))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow34, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow13, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow37, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow17, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow38, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow21, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow29, kStack)), Float(1.0f))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 158 Store = 51 Binop = 88 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 53 } { Real(+) = 23 } { Real(-) = 10 } ] Mathop = 40 [ { fabsf = 10 } { log10f = 10 } { max_f = 20 } ] Numbers = 127 Declare = 19 Cast = 20 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp0, kStack)))))
		StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp1, kStack, LoadVarInst(Address(fTemp0, kStack)))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp3, kStack, LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow12, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp4, kStack)))))
		StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp5, kStack, LoadVarInst(Address(fTemp4, kStack)))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow16, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp6, kStack)))))
		StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp7, kStack, LoadVarInst(Address(fTemp6, kStack)))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp8, kStack)))))
		StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp9, kStack, LoadVarInst(Address(fTemp8, kStack)))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec13, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp10, kStack)))))
		StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp11, kStack, LoadVarInst(Address(fTemp10, kStack)))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow28, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec15, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp12, kStack)))))
		StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp13, kStack, LoadVarInst(Address(fTemp12, kStack)))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow32, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec17, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp14, kStack)))))
		StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp15, kStack, LoadVarInst(Address(fTemp14, kStack)))
		DeclareVarInst("float", fTemp16, kStack, BinopInst("*", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fTemp7, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fTemp9, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fTemp11, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fTemp13, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fTemp15, kStack))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp16, kStack)))))
		StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp16, kStack))))
		DeclareVarInst("float", fTemp17, kStack, BinopInst("*", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fTemp7, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fTemp9, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp11, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp13, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fTemp15, kStack))))))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp17, kStack)))))
		StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp17, kStack))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("float", fRec11[2], kStruct)
	DeclareVarInst("float", fRec10[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("float", fRec13[2], kStruct)
	DeclareVarInst("float", fRec12[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("float", fRec15[2], kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("float", fRec17[2], kStruct)
	DeclareVarInst("float", fRec16[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph7, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph8, kStruct)
	DeclareVarInst("float", fRec18[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph9, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
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
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry0, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow1, kStack)))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry1, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct)))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry2, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow9, kStack)))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct)))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry3, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow13, kStack)))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct)))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct)))))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry4, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow18, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow17, kStack)))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox4, kStruct)))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct)))))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry5, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow22, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow21, kStack)))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox5, kStruct)))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct)))))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry6, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow26, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow25, kStack)))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox6, kStruct)))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct)))))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("*", Float(0.0055555557f), BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry7, kStruct))), Float(-9e+01f))))
	DeclareVarInst("float", fSlow30, kStack, FunCallInst("sqrtf", MinusInst(LoadVarInst(Address(fSlow29, kStack)))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fCheckbox7, kStruct)))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct)))))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow34, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow13, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow37, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow17, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow38, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow21, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(Address(fSlow29, kStack)), Float(1.0f))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp0, kStack)))))
			StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp1, kStack, LoadVarInst(Address(fTemp0, kStack)))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp3, kStack, LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow12, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp4, kStack)))))
			StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp5, kStack, LoadVarInst(Address(fTemp4, kStack)))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow16, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp6, kStack)))))
			StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp7, kStack, LoadVarInst(Address(fTemp6, kStack)))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp8, kStack)))))
			StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp9, kStack, LoadVarInst(Address(fTemp8, kStack)))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec13, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp10, kStack)))))
			StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp11, kStack, LoadVarInst(Address(fTemp10, kStack)))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow28, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec15, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp12, kStack)))))
			StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp13, kStack, LoadVarInst(Address(fTemp12, kStack)))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow32, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec17, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp14, kStack)))))
			StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp15, kStack, LoadVarInst(Address(fTemp14, kStack)))
			DeclareVarInst("float", fTemp16, kStack, BinopInst("*", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fTemp7, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fTemp9, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fTemp11, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fTemp13, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fTemp15, kStack))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp16, kStack)))))
			StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp16, kStack))))
			DeclareVarInst("float", fTemp17, kStack, BinopInst("*", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fTemp7, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fTemp9, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp11, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp13, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fTemp15, kStack))))))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("fabsf", LoadVarInst(Address(fTemp17, kStack)))))
			StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp17, kStack))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
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
Stack size in compute = 244 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 10 write = 0 ratio = 10
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec10 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec12 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec14 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec16 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fRec18 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
