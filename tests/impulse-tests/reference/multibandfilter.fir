======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenHorizontalBox("Multi Band Filter")
	OpenVerticalBox("peak 0")
	AddMetaDeclareInst(fEntry1, "style", "knob")
	AddNumEntry"Q factor", fEntry1, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddMetaDeclareInst(fEntry0, "unit", "Hz")
	AddNumEntry"freq", fEntry0, 1e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("gain", fVslider0, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 1")
	AddMetaDeclareInst(fEntry3, "style", "knob")
	AddNumEntry"Q factor", fEntry3, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry2, "style", "knob")
	AddMetaDeclareInst(fEntry2, "unit", "Hz")
	AddNumEntry"freq", fEntry2, 2e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider1, "unit", "dB")
	AddVerticalSlider("gain", fVslider1, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 2")
	AddMetaDeclareInst(fEntry5, "style", "knob")
	AddNumEntry"Q factor", fEntry5, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry4, "style", "knob")
	AddMetaDeclareInst(fEntry4, "unit", "Hz")
	AddNumEntry"freq", fEntry4, 3e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider2, "unit", "dB")
	AddVerticalSlider("gain", fVslider2, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 3")
	AddMetaDeclareInst(fEntry7, "style", "knob")
	AddNumEntry"Q factor", fEntry7, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry6, "style", "knob")
	AddMetaDeclareInst(fEntry6, "unit", "Hz")
	AddNumEntry"freq", fEntry6, 4e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider3, "unit", "dB")
	AddVerticalSlider("gain", fVslider3, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 4")
	AddMetaDeclareInst(fEntry9, "style", "knob")
	AddNumEntry"Q factor", fEntry9, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry8, "style", "knob")
	AddMetaDeclareInst(fEntry8, "unit", "Hz")
	AddNumEntry"freq", fEntry8, 5e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider4, "unit", "dB")
	AddVerticalSlider("gain", fVslider4, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 5")
	AddMetaDeclareInst(fEntry11, "style", "knob")
	AddNumEntry"Q factor", fEntry11, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry10, "style", "knob")
	AddMetaDeclareInst(fEntry10, "unit", "Hz")
	AddNumEntry"freq", fEntry10, 6e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider5, "unit", "dB")
	AddVerticalSlider("gain", fVslider5, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 6")
	AddMetaDeclareInst(fEntry13, "style", "knob")
	AddNumEntry"Q factor", fEntry13, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry12, "style", "knob")
	AddMetaDeclareInst(fEntry12, "unit", "Hz")
	AddNumEntry"freq", fEntry12, 7e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider6, "unit", "dB")
	AddVerticalSlider("gain", fVslider6, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 7")
	AddMetaDeclareInst(fEntry15, "style", "knob")
	AddNumEntry"Q factor", fEntry15, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry14, "style", "knob")
	AddMetaDeclareInst(fEntry14, "unit", "Hz")
	AddNumEntry"freq", fEntry14, 8e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider7, "unit", "dB")
	AddVerticalSlider("gain", fVslider7, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 8")
	AddMetaDeclareInst(fEntry17, "style", "knob")
	AddNumEntry"Q factor", fEntry17, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry16, "style", "knob")
	AddMetaDeclareInst(fEntry16, "unit", "Hz")
	AddNumEntry"freq", fEntry16, 9e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider8, "unit", "dB")
	AddVerticalSlider("gain", fVslider8, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 9")
	AddMetaDeclareInst(fEntry19, "style", "knob")
	AddNumEntry"Q factor", fEntry19, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry18, "style", "knob")
	AddMetaDeclareInst(fEntry18, "unit", "Hz")
	AddNumEntry"freq", fEntry18, 1e+04f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider9, "unit", "dB")
	AddVerticalSlider("gain", fVslider9, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fEntry0)("int", fSampleRate)("float", fConst0KI)("FAUSTFLOAT", fEntry1)("FAUSTFLOAT", fVslider0)("int", IOTA0)("float[2]", fVec0SE)("float[4]", fVec1SE)("FAUSTFLOAT", fEntry2)("FAUSTFLOAT", fEntry3)("FAUSTFLOAT", fVslider1)("float[2]", fVec5SE)("float[4]", fVec6SE)("FAUSTFLOAT", fEntry4)("FAUSTFLOAT", fEntry5)("FAUSTFLOAT", fVslider2)("float[2]", fVec10SE)("float[4]", fVec11SE)("FAUSTFLOAT", fEntry6)("FAUSTFLOAT", fEntry7)("FAUSTFLOAT", fVslider3)("float[2]", fVec15SE)("float[4]", fVec16SE)("FAUSTFLOAT", fEntry8)("FAUSTFLOAT", fEntry9)("FAUSTFLOAT", fVslider4)("float[2]", fVec20SE)("float[4]", fVec21SE)("FAUSTFLOAT", fEntry10)("FAUSTFLOAT", fEntry11)("FAUSTFLOAT", fVslider5)("float[2]", fVec25SE)("float[4]", fVec26SE)("FAUSTFLOAT", fEntry12)("FAUSTFLOAT", fEntry13)("FAUSTFLOAT", fVslider6)("float[2]", fVec30SE)("float[4]", fVec31SE)("FAUSTFLOAT", fEntry14)("FAUSTFLOAT", fEntry15)("FAUSTFLOAT", fVslider7)("float[2]", fVec35SE)("float[4]", fVec36SE)("FAUSTFLOAT", fEntry16)("FAUSTFLOAT", fEntry17)("FAUSTFLOAT", fVslider8)("float[2]", fVec40SE)("float[4]", fVec41SE)("FAUSTFLOAT", fEntry18)("FAUSTFLOAT", fEntry19)("FAUSTFLOAT", fVslider9)("float[2]", fVec45SE)("float[4]", fVec46SE)>)

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
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Double(2e+03f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Double(3e+03f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Double(4e+03f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry8, kStruct), CastInst("FAUSTFLOAT", Double(5e+03f)))
	StoreVarInst(Address(fEntry9, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry10, kStruct), CastInst("FAUSTFLOAT", Double(6e+03f)))
	StoreVarInst(Address(fEntry11, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry12, kStruct), CastInst("FAUSTFLOAT", Double(7e+03f)))
	StoreVarInst(Address(fEntry13, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry14, kStruct), CastInst("FAUSTFLOAT", Double(8e+03f)))
	StoreVarInst(Address(fEntry15, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry16, kStruct), CastInst("FAUSTFLOAT", Double(9e+03f)))
	StoreVarInst(Address(fEntry17, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry18, kStruct), CastInst("FAUSTFLOAT", Double(1e+04f)))
	StoreVarInst(Address(fEntry19, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(4))
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
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(4))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(4))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(4))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec35SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(4))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec40SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(4))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec41SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec45SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(4))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 252 Store = 0 Binop = 260 [ { Real(*) = 90 } { Real(+) = 110 } { Real(/) = 60 } ] Mathop = 50 [ { mydsp_faustpower2_f = 10 } { powf = 30 } { tanf = 10 } ] Numbers = 152 Declare = 112 Cast = 30 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow2BE, kStack)))), LoadVarInst(Address(fSlow1BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))), LoadVarInst(Address(fSlow1BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))), LoadVarInst(Address(fSlow1BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow1BE, kStack))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fSlow8BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow10BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), MinusInst(LoadVarInst(Address(fSlow0BE, kStack))))))))
	DeclareVarInst("float", fSlow11BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))))
	DeclareVarInst("float", fSlow12BE, kStack, CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))
	DeclareVarInst("float", fSlow13BE, kStack, CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))
	DeclareVarInst("float", fSlow14BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow13BE, kStack)))), LoadVarInst(Address(fSlow12BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow15BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow11BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow16BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow13BE, kStack))))
	DeclareVarInst("float", fSlow17BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow16BE, kStack)))), LoadVarInst(Address(fSlow12BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow18BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow16BE, kStack)))), LoadVarInst(Address(fSlow12BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow19BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow12BE, kStack))))
	DeclareVarInst("float", fSlow20BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fSlow19BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow21BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow19BE, kStack)), MinusInst(LoadVarInst(Address(fSlow11BE, kStack))))))))
	DeclareVarInst("float", fSlow22BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))))
	DeclareVarInst("float", fSlow23BE, kStack, CastInst("float", LoadVarInst(Address(fEntry5, kStruct))))
	DeclareVarInst("float", fSlow24BE, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow25BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow24BE, kStack)))), LoadVarInst(Address(fSlow23BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow26BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow22BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow24BE, kStack))))
	DeclareVarInst("float", fSlow28BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow22BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow27BE, kStack)))), LoadVarInst(Address(fSlow23BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow29BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow27BE, kStack)))), LoadVarInst(Address(fSlow23BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow30BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow23BE, kStack))))
	DeclareVarInst("float", fSlow31BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fSlow30BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow32BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow30BE, kStack)), MinusInst(LoadVarInst(Address(fSlow22BE, kStack))))))))
	DeclareVarInst("float", fSlow33BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry6, kStruct))))))
	DeclareVarInst("float", fSlow34BE, kStack, CastInst("float", LoadVarInst(Address(fEntry7, kStruct))))
	DeclareVarInst("float", fSlow35BE, kStack, CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))
	DeclareVarInst("float", fSlow36BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow35BE, kStack)))), LoadVarInst(Address(fSlow34BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow37BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow33BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow38BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow35BE, kStack))))
	DeclareVarInst("float", fSlow39BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow38BE, kStack)))), LoadVarInst(Address(fSlow34BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow40BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow38BE, kStack)))), LoadVarInst(Address(fSlow34BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow41BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow34BE, kStack))))
	DeclareVarInst("float", fSlow42BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), LoadVarInst(Address(fSlow41BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow43BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow41BE, kStack)), MinusInst(LoadVarInst(Address(fSlow33BE, kStack))))))))
	DeclareVarInst("float", fSlow44BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry8, kStruct))))))
	DeclareVarInst("float", fSlow45BE, kStack, CastInst("float", LoadVarInst(Address(fEntry9, kStruct))))
	DeclareVarInst("float", fSlow46BE, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow47BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow46BE, kStack)))), LoadVarInst(Address(fSlow45BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow48BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow44BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow49BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow46BE, kStack))))
	DeclareVarInst("float", fSlow50BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow49BE, kStack)))), LoadVarInst(Address(fSlow45BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow51BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow49BE, kStack)))), LoadVarInst(Address(fSlow45BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow52BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow45BE, kStack))))
	DeclareVarInst("float", fSlow53BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44BE, kStack)), LoadVarInst(Address(fSlow52BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow54BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow52BE, kStack)), MinusInst(LoadVarInst(Address(fSlow44BE, kStack))))))))
	DeclareVarInst("float", fSlow55BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry10, kStruct))))))
	DeclareVarInst("float", fSlow56BE, kStack, CastInst("float", LoadVarInst(Address(fEntry11, kStruct))))
	DeclareVarInst("float", fSlow57BE, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow58BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow57BE, kStack)))), LoadVarInst(Address(fSlow56BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow59BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow55BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow60BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow57BE, kStack))))
	DeclareVarInst("float", fSlow61BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow55BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow60BE, kStack)))), LoadVarInst(Address(fSlow56BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow62BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow60BE, kStack)))), LoadVarInst(Address(fSlow56BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow63BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow56BE, kStack))))
	DeclareVarInst("float", fSlow64BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow55BE, kStack)), LoadVarInst(Address(fSlow63BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow65BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow63BE, kStack)), MinusInst(LoadVarInst(Address(fSlow55BE, kStack))))))))
	DeclareVarInst("float", fSlow66BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry12, kStruct))))))
	DeclareVarInst("float", fSlow67BE, kStack, CastInst("float", LoadVarInst(Address(fEntry13, kStruct))))
	DeclareVarInst("float", fSlow68BE, kStack, CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))
	DeclareVarInst("float", fSlow69BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow68BE, kStack)))), LoadVarInst(Address(fSlow67BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow70BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow66BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow71BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow68BE, kStack))))
	DeclareVarInst("float", fSlow72BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow66BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow71BE, kStack)))), LoadVarInst(Address(fSlow67BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow73BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow71BE, kStack)))), LoadVarInst(Address(fSlow67BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow74BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow67BE, kStack))))
	DeclareVarInst("float", fSlow75BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow66BE, kStack)), LoadVarInst(Address(fSlow74BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow76BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow74BE, kStack)), MinusInst(LoadVarInst(Address(fSlow66BE, kStack))))))))
	DeclareVarInst("float", fSlow77BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry14, kStruct))))))
	DeclareVarInst("float", fSlow78BE, kStack, CastInst("float", LoadVarInst(Address(fEntry15, kStruct))))
	DeclareVarInst("float", fSlow79BE, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow80BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow79BE, kStack)))), LoadVarInst(Address(fSlow78BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow81BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow77BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow82BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow79BE, kStack))))
	DeclareVarInst("float", fSlow83BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow82BE, kStack)))), LoadVarInst(Address(fSlow78BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow84BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow82BE, kStack)))), LoadVarInst(Address(fSlow78BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow85BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow78BE, kStack))))
	DeclareVarInst("float", fSlow86BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), LoadVarInst(Address(fSlow85BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow87BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow85BE, kStack)), MinusInst(LoadVarInst(Address(fSlow77BE, kStack))))))))
	DeclareVarInst("float", fSlow88BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry16, kStruct))))))
	DeclareVarInst("float", fSlow89BE, kStack, CastInst("float", LoadVarInst(Address(fEntry17, kStruct))))
	DeclareVarInst("float", fSlow90BE, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow91BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow90BE, kStack)))), LoadVarInst(Address(fSlow89BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow92BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow88BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow93BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow90BE, kStack))))
	DeclareVarInst("float", fSlow94BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow88BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow93BE, kStack)))), LoadVarInst(Address(fSlow89BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow95BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow93BE, kStack)))), LoadVarInst(Address(fSlow89BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow96BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow89BE, kStack))))
	DeclareVarInst("float", fSlow97BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow88BE, kStack)), LoadVarInst(Address(fSlow96BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow98BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow96BE, kStack)), MinusInst(LoadVarInst(Address(fSlow88BE, kStack))))))))
	DeclareVarInst("float", fSlow99BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry18, kStruct))))))
	DeclareVarInst("float", fSlow100BE, kStack, CastInst("float", LoadVarInst(Address(fEntry19, kStruct))))
	DeclareVarInst("float", fSlow101BE, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow102BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow101BE, kStack)))), LoadVarInst(Address(fSlow100BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow103BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow99BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow104BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow101BE, kStack))))
	DeclareVarInst("float", fSlow105BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow104BE, kStack)))), LoadVarInst(Address(fSlow100BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow106BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow104BE, kStack)))), LoadVarInst(Address(fSlow100BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow107BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow100BE, kStack))))
	DeclareVarInst("float", fSlow108BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), LoadVarInst(Address(fSlow107BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow109BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow107BE, kStack)), MinusInst(LoadVarInst(Address(fSlow99BE, kStack))))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 227 Store = 23 Binop = 213 [ { Int(&) = 70 } { Int(+) = 2 } { Int(-) = 30 } { Int(<) = 1 } { Real(*) = 70 } { Real(+) = 40 } ] Mathop = 0 Numbers = 103 Declare = 21 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp1SE, kStack)))
		DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow14BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow17BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow15BE, kStack)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp3SE, kStack)))
		DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow18BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20BE, kStack)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow15BE, kStack)), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow21BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow25BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow28BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp5SE, kStack)))
		DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow29BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow32BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow39BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp7SE, kStack, LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp7SE, kStack)))
		DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow42BE, kStack)), LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow43BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow47BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow50BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow48BE, kStack)), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp9SE, kStack)))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow51BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow53BE, kStack)), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow48BE, kStack)), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow54BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow58BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow61BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow59BE, kStack)), LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp11SE, kStack)))
		DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow62BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow64BE, kStack)), LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow59BE, kStack)), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow65BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow69BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow72BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp13SE, kStack)))
		DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec35SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow73BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow75BE, kStack)), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow76BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow80BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow83BE, kStack)), LoadVarInst(Address(fTemp14SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow81BE, kStack)), LoadVarInst(Address(fVec35SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp15SE, kStack, LoadVarInst(Address(fVec35SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp15SE, kStack)))
		DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fVec35SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow81BE, kStack)), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fTemp14SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow94BE, kStack)), LoadVarInst(Address(fTemp16SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp17SE, kStack, LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp17SE, kStack)))
		DeclareVarInst("float", fTemp18SE, kStack, LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow95BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow97BE, kStack)), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow98BE, kStack)), LoadVarInst(Address(fTemp16SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow102BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow105BE, kStack)), LoadVarInst(Address(fTemp18SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow103BE, kStack)), LoadVarInst(Address(fVec45SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp19SE, kStack, LoadVarInst(Address(fVec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp19SE, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow106BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow108BE, kStack)), LoadVarInst(Address(fVec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow103BE, kStack)), LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow109BE, kStack)), LoadVarInst(Address(fTemp18SE, kStack)))))))
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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay fVec0SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec1SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	// Recursion delay fVec5SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec5SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec6SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	// Recursion delay fVec10SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec10SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec11SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	// Recursion delay fVec15SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec15SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec16SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	// Recursion delay fVec20SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec20SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec21SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry11, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	// Recursion delay fVec25SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec25SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec26SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry13, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	// Recursion delay fVec30SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec30SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec31SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry15, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	// Recursion delay fVec35SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec35SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec36SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry16, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry17, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	// Recursion delay fVec40SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec40SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec41SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry18, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry19, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	// Recursion delay fVec45SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec45SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec46SE[4], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Double(2e+03f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Double(3e+03f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Double(4e+03f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry8, kStruct), CastInst("FAUSTFLOAT", Double(5e+03f)))
	StoreVarInst(Address(fEntry9, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry10, kStruct), CastInst("FAUSTFLOAT", Double(6e+03f)))
	StoreVarInst(Address(fEntry11, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry12, kStruct), CastInst("FAUSTFLOAT", Double(7e+03f)))
	StoreVarInst(Address(fEntry13, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry14, kStruct), CastInst("FAUSTFLOAT", Double(8e+03f)))
	StoreVarInst(Address(fEntry15, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry16, kStruct), CastInst("FAUSTFLOAT", Double(9e+03f)))
	StoreVarInst(Address(fEntry17, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry18, kStruct), CastInst("FAUSTFLOAT", Double(1e+04f)))
	StoreVarInst(Address(fEntry19, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(4))
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
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(4))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(4))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(4))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec35SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(4))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec40SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(4))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec41SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec45SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(4))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow2BE, kStack)))), LoadVarInst(Address(fSlow1BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))), LoadVarInst(Address(fSlow1BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))), LoadVarInst(Address(fSlow1BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow1BE, kStack))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fSlow8BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow10BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), MinusInst(LoadVarInst(Address(fSlow0BE, kStack))))))))
	DeclareVarInst("float", fSlow11BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))))
	DeclareVarInst("float", fSlow12BE, kStack, CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))
	DeclareVarInst("float", fSlow13BE, kStack, CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))
	DeclareVarInst("float", fSlow14BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow13BE, kStack)))), LoadVarInst(Address(fSlow12BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow15BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow11BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow16BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow13BE, kStack))))
	DeclareVarInst("float", fSlow17BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow16BE, kStack)))), LoadVarInst(Address(fSlow12BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow18BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow16BE, kStack)))), LoadVarInst(Address(fSlow12BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow19BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow12BE, kStack))))
	DeclareVarInst("float", fSlow20BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fSlow19BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow21BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow19BE, kStack)), MinusInst(LoadVarInst(Address(fSlow11BE, kStack))))))))
	DeclareVarInst("float", fSlow22BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))))
	DeclareVarInst("float", fSlow23BE, kStack, CastInst("float", LoadVarInst(Address(fEntry5, kStruct))))
	DeclareVarInst("float", fSlow24BE, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow25BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow24BE, kStack)))), LoadVarInst(Address(fSlow23BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow26BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow22BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow24BE, kStack))))
	DeclareVarInst("float", fSlow28BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow22BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow27BE, kStack)))), LoadVarInst(Address(fSlow23BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow29BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow27BE, kStack)))), LoadVarInst(Address(fSlow23BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow30BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow23BE, kStack))))
	DeclareVarInst("float", fSlow31BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fSlow30BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow32BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow30BE, kStack)), MinusInst(LoadVarInst(Address(fSlow22BE, kStack))))))))
	DeclareVarInst("float", fSlow33BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry6, kStruct))))))
	DeclareVarInst("float", fSlow34BE, kStack, CastInst("float", LoadVarInst(Address(fEntry7, kStruct))))
	DeclareVarInst("float", fSlow35BE, kStack, CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))
	DeclareVarInst("float", fSlow36BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow35BE, kStack)))), LoadVarInst(Address(fSlow34BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow37BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow33BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow38BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow35BE, kStack))))
	DeclareVarInst("float", fSlow39BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow38BE, kStack)))), LoadVarInst(Address(fSlow34BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow40BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow38BE, kStack)))), LoadVarInst(Address(fSlow34BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow41BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow34BE, kStack))))
	DeclareVarInst("float", fSlow42BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), LoadVarInst(Address(fSlow41BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow43BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow41BE, kStack)), MinusInst(LoadVarInst(Address(fSlow33BE, kStack))))))))
	DeclareVarInst("float", fSlow44BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry8, kStruct))))))
	DeclareVarInst("float", fSlow45BE, kStack, CastInst("float", LoadVarInst(Address(fEntry9, kStruct))))
	DeclareVarInst("float", fSlow46BE, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow47BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow46BE, kStack)))), LoadVarInst(Address(fSlow45BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow48BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow44BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow49BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow46BE, kStack))))
	DeclareVarInst("float", fSlow50BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow49BE, kStack)))), LoadVarInst(Address(fSlow45BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow51BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow49BE, kStack)))), LoadVarInst(Address(fSlow45BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow52BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow45BE, kStack))))
	DeclareVarInst("float", fSlow53BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44BE, kStack)), LoadVarInst(Address(fSlow52BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow54BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow52BE, kStack)), MinusInst(LoadVarInst(Address(fSlow44BE, kStack))))))))
	DeclareVarInst("float", fSlow55BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry10, kStruct))))))
	DeclareVarInst("float", fSlow56BE, kStack, CastInst("float", LoadVarInst(Address(fEntry11, kStruct))))
	DeclareVarInst("float", fSlow57BE, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow58BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow57BE, kStack)))), LoadVarInst(Address(fSlow56BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow59BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow55BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow60BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow57BE, kStack))))
	DeclareVarInst("float", fSlow61BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow55BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow60BE, kStack)))), LoadVarInst(Address(fSlow56BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow62BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow60BE, kStack)))), LoadVarInst(Address(fSlow56BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow63BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow56BE, kStack))))
	DeclareVarInst("float", fSlow64BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow55BE, kStack)), LoadVarInst(Address(fSlow63BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow65BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow63BE, kStack)), MinusInst(LoadVarInst(Address(fSlow55BE, kStack))))))))
	DeclareVarInst("float", fSlow66BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry12, kStruct))))))
	DeclareVarInst("float", fSlow67BE, kStack, CastInst("float", LoadVarInst(Address(fEntry13, kStruct))))
	DeclareVarInst("float", fSlow68BE, kStack, CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))
	DeclareVarInst("float", fSlow69BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow68BE, kStack)))), LoadVarInst(Address(fSlow67BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow70BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow66BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow71BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow68BE, kStack))))
	DeclareVarInst("float", fSlow72BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow66BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow71BE, kStack)))), LoadVarInst(Address(fSlow67BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow73BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow71BE, kStack)))), LoadVarInst(Address(fSlow67BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow74BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow67BE, kStack))))
	DeclareVarInst("float", fSlow75BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow66BE, kStack)), LoadVarInst(Address(fSlow74BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow76BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow74BE, kStack)), MinusInst(LoadVarInst(Address(fSlow66BE, kStack))))))))
	DeclareVarInst("float", fSlow77BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry14, kStruct))))))
	DeclareVarInst("float", fSlow78BE, kStack, CastInst("float", LoadVarInst(Address(fEntry15, kStruct))))
	DeclareVarInst("float", fSlow79BE, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow80BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow79BE, kStack)))), LoadVarInst(Address(fSlow78BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow81BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow77BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow82BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow79BE, kStack))))
	DeclareVarInst("float", fSlow83BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow82BE, kStack)))), LoadVarInst(Address(fSlow78BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow84BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow82BE, kStack)))), LoadVarInst(Address(fSlow78BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow85BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow78BE, kStack))))
	DeclareVarInst("float", fSlow86BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), LoadVarInst(Address(fSlow85BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow87BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow85BE, kStack)), MinusInst(LoadVarInst(Address(fSlow77BE, kStack))))))))
	DeclareVarInst("float", fSlow88BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry16, kStruct))))))
	DeclareVarInst("float", fSlow89BE, kStack, CastInst("float", LoadVarInst(Address(fEntry17, kStruct))))
	DeclareVarInst("float", fSlow90BE, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow91BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow90BE, kStack)))), LoadVarInst(Address(fSlow89BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow92BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow88BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow93BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow90BE, kStack))))
	DeclareVarInst("float", fSlow94BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow88BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow93BE, kStack)))), LoadVarInst(Address(fSlow89BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow95BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow93BE, kStack)))), LoadVarInst(Address(fSlow89BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow96BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow89BE, kStack))))
	DeclareVarInst("float", fSlow97BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow88BE, kStack)), LoadVarInst(Address(fSlow96BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow98BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow88BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow96BE, kStack)), MinusInst(LoadVarInst(Address(fSlow88BE, kStack))))))))
	DeclareVarInst("float", fSlow99BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry18, kStruct))))))
	DeclareVarInst("float", fSlow100BE, kStack, CastInst("float", LoadVarInst(Address(fEntry19, kStruct))))
	DeclareVarInst("float", fSlow101BE, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow102BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow101BE, kStack)))), LoadVarInst(Address(fSlow100BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow103BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow99BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow104BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow101BE, kStack))))
	DeclareVarInst("float", fSlow105BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), MinusInst(BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow104BE, kStack)))), LoadVarInst(Address(fSlow100BE, kStack)))))), Float(1.0f)))
	DeclareVarInst("float", fSlow106BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow104BE, kStack)))), LoadVarInst(Address(fSlow100BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow107BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow100BE, kStack))))
	DeclareVarInst("float", fSlow108BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), LoadVarInst(Address(fSlow107BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow109BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow99BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow107BE, kStack)), MinusInst(LoadVarInst(Address(fSlow99BE, kStack))))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp1SE, kStack)))
			DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow14BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow17BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow15BE, kStack)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp3SE, kStack)))
			DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow18BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20BE, kStack)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow15BE, kStack)), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow21BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow25BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow28BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp5SE, kStack)))
			DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow29BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow32BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow39BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp7SE, kStack, LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp7SE, kStack)))
			DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow42BE, kStack)), LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow43BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow47BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow50BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow48BE, kStack)), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp9SE, kStack)))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow51BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow53BE, kStack)), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow48BE, kStack)), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow54BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow58BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow61BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow59BE, kStack)), LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp11SE, kStack)))
			DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow62BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow64BE, kStack)), LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow59BE, kStack)), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow65BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow69BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow72BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp13SE, kStack)))
			DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec35SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow73BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow75BE, kStack)), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow76BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow80BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow83BE, kStack)), LoadVarInst(Address(fTemp14SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow81BE, kStack)), LoadVarInst(Address(fVec35SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp15SE, kStack, LoadVarInst(Address(fVec35SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp15SE, kStack)))
			DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fVec35SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow81BE, kStack)), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fTemp14SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow94BE, kStack)), LoadVarInst(Address(fTemp16SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp17SE, kStack, LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp17SE, kStack)))
			DeclareVarInst("float", fTemp18SE, kStack, LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow95BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow97BE, kStack)), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow98BE, kStack)), LoadVarInst(Address(fTemp16SE, kStack))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow102BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow105BE, kStack)), LoadVarInst(Address(fTemp18SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow103BE, kStack)), LoadVarInst(Address(fVec45SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp19SE, kStack, LoadVarInst(Address(fVec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp19SE, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow106BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow108BE, kStack)), LoadVarInst(Address(fVec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow103BE, kStack)), LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow109BE, kStack)), LoadVarInst(Address(fTemp18SE, kStack)))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 364 bytes
Total heap size = 372 bytes
Stack size in compute = 456 bytes

======= Variable access in Control ==========

Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec15SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec25SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec30SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec31SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec35SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec40SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec41SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec45SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 10 write = 0 ratio = 10
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec15SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec25SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec30SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec31SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry15 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec35SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry16 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec40SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec41SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fEntry18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec45SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 71 write = 1 ratio = 72
Field = fVec0SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec1SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec6SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec11SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec15SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec16SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec21SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec25SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec26SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec30SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec31SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec35SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec36SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec40SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec41SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fEntry18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec45SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec46SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
