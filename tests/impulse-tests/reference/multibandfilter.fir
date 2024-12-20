======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenHorizontalBox("Multi Band Filter")
	OpenVerticalBox("peak 0")
	AddMetaDeclareInst(fEntry19, "style", "knob")
	AddNumEntry"Q factor", fEntry19, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry18, "style", "knob")
	AddMetaDeclareInst(fEntry18, "unit", "Hz")
	AddNumEntry"freq", fEntry18, 1e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider9, "unit", "dB")
	AddVerticalSlider("gain", fVslider9, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 1")
	AddMetaDeclareInst(fEntry17, "style", "knob")
	AddNumEntry"Q factor", fEntry17, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry16, "style", "knob")
	AddMetaDeclareInst(fEntry16, "unit", "Hz")
	AddNumEntry"freq", fEntry16, 2e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider8, "unit", "dB")
	AddVerticalSlider("gain", fVslider8, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 2")
	AddMetaDeclareInst(fEntry15, "style", "knob")
	AddNumEntry"Q factor", fEntry15, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry14, "style", "knob")
	AddMetaDeclareInst(fEntry14, "unit", "Hz")
	AddNumEntry"freq", fEntry14, 3e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider7, "unit", "dB")
	AddVerticalSlider("gain", fVslider7, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 3")
	AddMetaDeclareInst(fEntry13, "style", "knob")
	AddNumEntry"Q factor", fEntry13, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry12, "style", "knob")
	AddMetaDeclareInst(fEntry12, "unit", "Hz")
	AddNumEntry"freq", fEntry12, 4e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider6, "unit", "dB")
	AddVerticalSlider("gain", fVslider6, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 4")
	AddMetaDeclareInst(fEntry11, "style", "knob")
	AddNumEntry"Q factor", fEntry11, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry10, "style", "knob")
	AddMetaDeclareInst(fEntry10, "unit", "Hz")
	AddNumEntry"freq", fEntry10, 5e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider5, "unit", "dB")
	AddVerticalSlider("gain", fVslider5, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 5")
	AddMetaDeclareInst(fEntry9, "style", "knob")
	AddNumEntry"Q factor", fEntry9, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry8, "style", "knob")
	AddMetaDeclareInst(fEntry8, "unit", "Hz")
	AddNumEntry"freq", fEntry8, 6e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider4, "unit", "dB")
	AddVerticalSlider("gain", fVslider4, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 6")
	AddMetaDeclareInst(fEntry7, "style", "knob")
	AddNumEntry"Q factor", fEntry7, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry6, "style", "knob")
	AddMetaDeclareInst(fEntry6, "unit", "Hz")
	AddNumEntry"freq", fEntry6, 7e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider3, "unit", "dB")
	AddVerticalSlider("gain", fVslider3, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 7")
	AddMetaDeclareInst(fEntry5, "style", "knob")
	AddNumEntry"Q factor", fEntry5, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry4, "style", "knob")
	AddMetaDeclareInst(fEntry4, "unit", "Hz")
	AddNumEntry"freq", fEntry4, 8e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider2, "unit", "dB")
	AddVerticalSlider("gain", fVslider2, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 8")
	AddMetaDeclareInst(fEntry3, "style", "knob")
	AddNumEntry"Q factor", fEntry3, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry2, "style", "knob")
	AddMetaDeclareInst(fEntry2, "unit", "Hz")
	AddNumEntry"freq", fEntry2, 9e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider1, "unit", "dB")
	AddVerticalSlider("gain", fVslider1, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
	OpenVerticalBox("peak 9")
	AddMetaDeclareInst(fEntry1, "style", "knob")
	AddNumEntry"Q factor", fEntry1, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddMetaDeclareInst(fEntry0, "unit", "Hz")
	AddNumEntry"freq", fEntry0, 1e+04f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("gain", fVslider0, 0.0f, -5e+01f, 5e+01f, 0.1f)
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

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fEntry0)("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fEntry1)("FAUSTFLOAT", fEntry2)("FAUSTFLOAT", fVslider1)("FAUSTFLOAT", fEntry3)("FAUSTFLOAT", fEntry4)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fEntry5)("FAUSTFLOAT", fEntry6)("FAUSTFLOAT", fVslider3)("FAUSTFLOAT", fEntry7)("FAUSTFLOAT", fEntry8)("FAUSTFLOAT", fVslider4)("FAUSTFLOAT", fEntry9)("FAUSTFLOAT", fEntry10)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fEntry11)("FAUSTFLOAT", fEntry12)("FAUSTFLOAT", fVslider6)("FAUSTFLOAT", fEntry13)("FAUSTFLOAT", fEntry14)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fEntry15)("FAUSTFLOAT", fEntry16)("FAUSTFLOAT", fVslider8)("FAUSTFLOAT", fEntry17)("FAUSTFLOAT", fEntry18)("FAUSTFLOAT", fVslider9)("FAUSTFLOAT", fEntry19)("float[3]", fRec9)("float[3]", fRec8)("float[3]", fRec7)("float[3]", fRec6)("float[3]", fRec5)("float[3]", fRec4)("float[3]", fRec3)("float[3]", fRec2)("float[3]", fRec1)("float[3]", fRec0)>)

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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(1e+04f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Double(9e+03f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Double(8e+03f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Double(7e+03f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry8, kStruct), CastInst("FAUSTFLOAT", Double(6e+03f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry9, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry10, kStruct), CastInst("FAUSTFLOAT", Double(5e+03f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry11, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry12, kStruct), CastInst("FAUSTFLOAT", Double(4e+03f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry13, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry14, kStruct), CastInst("FAUSTFLOAT", Double(3e+03f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry15, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry16, kStruct), CastInst("FAUSTFLOAT", Double(2e+03f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry17, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry18, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry19, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(3))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(3))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(3))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(3))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(3))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(3))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(3))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(3))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 192 Store = 0 Binop = 190 [ { Real(*) = 70 } { Real(+) = 60 } { Real(-) = 30 } { Real(/) = 30 } ] Mathop = 30 [ { mydsp_faustpower2_f = 10 } { powf = 10 } { tanf = 10 } ] Numbers = 102 Declare = 92 Cast = 30 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))), LoadVarInst(Address(fSlow6, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fSlow7, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow5, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(fEntry5, kStruct))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct)))))), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow12, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow10, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow15, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry6, kStruct))))))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", LoadVarInst(Address(fEntry7, kStruct))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("+", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow17, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow15, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow20, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry8, kStruct))))))
	DeclareVarInst("float", fSlow21, kStack, CastInst("float", LoadVarInst(Address(fEntry9, kStruct))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct)))))), LoadVarInst(Address(fSlow21, kStack))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("+", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fSlow22, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow20, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow25, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry10, kStruct))))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", LoadVarInst(Address(fEntry11, kStruct))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct)))))), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow27, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow25, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow30, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry12, kStruct))))))
	DeclareVarInst("float", fSlow31, kStack, CastInst("float", LoadVarInst(Address(fEntry13, kStruct))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct)))))), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("+", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow32, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow30, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry14, kStruct))))))
	DeclareVarInst("float", fSlow36, kStack, CastInst("float", LoadVarInst(Address(fEntry15, kStruct))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct)))))), LoadVarInst(Address(fSlow36, kStack))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("+", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fSlow37, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow35, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry16, kStruct))))))
	DeclareVarInst("float", fSlow41, kStack, CastInst("float", LoadVarInst(Address(fEntry17, kStruct))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct)))))), LoadVarInst(Address(fSlow41, kStack))))
	DeclareVarInst("float", fSlow43, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fSlow42, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow44, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow40, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry18, kStruct))))))
	DeclareVarInst("float", fSlow46, kStack, CastInst("float", LoadVarInst(Address(fEntry19, kStruct))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct)))))), LoadVarInst(Address(fSlow46, kStack))))
	DeclareVarInst("float", fSlow48, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), BinopInst("+", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fSlow47, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow49, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow45, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), BinopInst("-", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fSlow47, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow46, kStack))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), BinopInst("+", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fSlow51, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow53, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), BinopInst("-", LoadVarInst(Address(fSlow51, kStack)), LoadVarInst(Address(fSlow45, kStack))))))
	DeclareVarInst("float", fSlow54, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), BinopInst("-", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fSlow42, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow55, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow41, kStack))))
	DeclareVarInst("float", fSlow56, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fSlow55, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow57, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), BinopInst("-", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fSlow40, kStack))))))
	DeclareVarInst("float", fSlow58, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("-", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fSlow37, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow59, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow36, kStack))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("+", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fSlow59, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("-", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fSlow35, kStack))))))
	DeclareVarInst("float", fSlow62, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("-", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow32, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow63, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("+", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow63, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("-", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fSlow30, kStack))))))
	DeclareVarInst("float", fSlow66, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("-", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow27, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow67, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow68, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow67, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow69, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("-", LoadVarInst(Address(fSlow67, kStack)), LoadVarInst(Address(fSlow25, kStack))))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("-", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fSlow22, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow71, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow21, kStack))))
	DeclareVarInst("float", fSlow72, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("+", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fSlow71, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow73, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("-", LoadVarInst(Address(fSlow71, kStack)), LoadVarInst(Address(fSlow20, kStack))))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("-", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow17, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow75, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow76, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("+", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow75, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow77, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("-", LoadVarInst(Address(fSlow75, kStack)), LoadVarInst(Address(fSlow15, kStack))))))
	DeclareVarInst("float", fSlow78, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("-", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow12, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow79, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow80, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow79, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow81, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("-", LoadVarInst(Address(fSlow79, kStack)), LoadVarInst(Address(fSlow10, kStack))))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("-", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fSlow7, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow83, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow6, kStack))))
	DeclareVarInst("float", fSlow84, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fSlow83, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow85, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("-", LoadVarInst(Address(fSlow83, kStack)), LoadVarInst(Address(fSlow5, kStack))))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow88, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow87, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow89, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow87, kStack)), LoadVarInst(Address(fSlow0, kStack))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 146 Store = 32 Binop = 102 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 60 } { Real(+) = 30 } { Real(-) = 10 } ] Mathop = 0 Numbers = 92 Declare = 11 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fSlow49, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp0, kStack))))))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp1, kStack))))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp1, kStack)), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp2, kStack))))))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp3, kStack))))))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp3, kStack)), BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow65, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp4, kStack))))))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow69, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp5, kStack))))))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp5, kStack)), BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow73, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp6, kStack))))))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6, kStack)), BinopInst("*", LoadVarInst(Address(fSlow76, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow78, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp7, kStack))))))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp7, kStack)), BinopInst("*", LoadVarInst(Address(fSlow80, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow82, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp8, kStack))))))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), BinopInst("*", LoadVarInst(Address(fSlow84, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow85, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow86, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp9, kStack))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp9, kStack)), BinopInst("*", LoadVarInst(Address(fSlow88, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(2)], LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(2)], LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(2)], LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(2)], LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(2)], LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
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
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry11, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry13, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry15, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry16, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry17, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry18, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry19, kStruct)
	DeclareVarInst("float", fRec9[3], kStruct)
	DeclareVarInst("float", fRec8[3], kStruct)
	DeclareVarInst("float", fRec7[3], kStruct)
	DeclareVarInst("float", fRec6[3], kStruct)
	DeclareVarInst("float", fRec5[3], kStruct)
	DeclareVarInst("float", fRec4[3], kStruct)
	DeclareVarInst("float", fRec3[3], kStruct)
	DeclareVarInst("float", fRec2[3], kStruct)
	DeclareVarInst("float", fRec1[3], kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(1e+04f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Double(9e+03f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Double(8e+03f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Double(7e+03f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry8, kStruct), CastInst("FAUSTFLOAT", Double(6e+03f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry9, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry10, kStruct), CastInst("FAUSTFLOAT", Double(5e+03f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry11, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry12, kStruct), CastInst("FAUSTFLOAT", Double(4e+03f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry13, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry14, kStruct), CastInst("FAUSTFLOAT", Double(3e+03f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry15, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry16, kStruct), CastInst("FAUSTFLOAT", Double(2e+03f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry17, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fEntry18, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry19, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(3))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(3))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(3))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(3))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(3))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(3))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(3))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(3))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))), LoadVarInst(Address(fSlow6, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fSlow7, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow5, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(fEntry5, kStruct))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct)))))), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow12, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow10, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow15, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry6, kStruct))))))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", LoadVarInst(Address(fEntry7, kStruct))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("+", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow17, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow15, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow20, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry8, kStruct))))))
	DeclareVarInst("float", fSlow21, kStack, CastInst("float", LoadVarInst(Address(fEntry9, kStruct))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct)))))), LoadVarInst(Address(fSlow21, kStack))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("+", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fSlow22, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow20, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow25, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry10, kStruct))))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", LoadVarInst(Address(fEntry11, kStruct))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct)))))), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow27, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow25, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow30, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry12, kStruct))))))
	DeclareVarInst("float", fSlow31, kStack, CastInst("float", LoadVarInst(Address(fEntry13, kStruct))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct)))))), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("+", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow32, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow30, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry14, kStruct))))))
	DeclareVarInst("float", fSlow36, kStack, CastInst("float", LoadVarInst(Address(fEntry15, kStruct))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct)))))), LoadVarInst(Address(fSlow36, kStack))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("+", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fSlow37, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow35, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry16, kStruct))))))
	DeclareVarInst("float", fSlow41, kStack, CastInst("float", LoadVarInst(Address(fEntry17, kStruct))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct)))))), LoadVarInst(Address(fSlow41, kStack))))
	DeclareVarInst("float", fSlow43, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fSlow42, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow44, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow40, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry18, kStruct))))))
	DeclareVarInst("float", fSlow46, kStack, CastInst("float", LoadVarInst(Address(fEntry19, kStruct))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct)))))), LoadVarInst(Address(fSlow46, kStack))))
	DeclareVarInst("float", fSlow48, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), BinopInst("+", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fSlow47, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow49, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow45, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), BinopInst("-", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fSlow47, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow46, kStack))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), BinopInst("+", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fSlow51, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow53, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), BinopInst("-", LoadVarInst(Address(fSlow51, kStack)), LoadVarInst(Address(fSlow45, kStack))))))
	DeclareVarInst("float", fSlow54, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), BinopInst("-", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fSlow42, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow55, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow41, kStack))))
	DeclareVarInst("float", fSlow56, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fSlow55, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow57, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), BinopInst("-", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fSlow40, kStack))))))
	DeclareVarInst("float", fSlow58, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("-", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fSlow37, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow59, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow36, kStack))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("+", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fSlow59, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("-", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fSlow35, kStack))))))
	DeclareVarInst("float", fSlow62, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("-", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow32, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow63, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("+", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow63, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("-", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fSlow30, kStack))))))
	DeclareVarInst("float", fSlow66, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("-", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow27, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow67, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow68, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow67, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow69, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("-", LoadVarInst(Address(fSlow67, kStack)), LoadVarInst(Address(fSlow25, kStack))))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("-", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fSlow22, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow71, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow21, kStack))))
	DeclareVarInst("float", fSlow72, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("+", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fSlow71, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow73, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("-", LoadVarInst(Address(fSlow71, kStack)), LoadVarInst(Address(fSlow20, kStack))))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("-", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow17, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow75, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow76, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("+", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow75, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow77, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("-", LoadVarInst(Address(fSlow75, kStack)), LoadVarInst(Address(fSlow15, kStack))))))
	DeclareVarInst("float", fSlow78, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("-", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow12, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow79, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow80, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow79, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow81, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("-", LoadVarInst(Address(fSlow79, kStack)), LoadVarInst(Address(fSlow10, kStack))))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("-", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fSlow7, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow83, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow6, kStack))))
	DeclareVarInst("float", fSlow84, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fSlow83, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow85, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("-", LoadVarInst(Address(fSlow83, kStack)), LoadVarInst(Address(fSlow5, kStack))))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow88, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow87, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow89, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow87, kStack)), LoadVarInst(Address(fSlow0, kStack))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fSlow49, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp0, kStack))))))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp1, kStack))))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp1, kStack)), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp2, kStack))))))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp3, kStack))))))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp3, kStack)), BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow65, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp4, kStack))))))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow69, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp5, kStack))))))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp5, kStack)), BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow73, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp6, kStack))))))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6, kStack)), BinopInst("*", LoadVarInst(Address(fSlow76, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow78, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp7, kStack))))))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp7, kStack)), BinopInst("*", LoadVarInst(Address(fSlow80, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow82, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp8, kStack))))))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), BinopInst("*", LoadVarInst(Address(fSlow84, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow85, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow86, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp9, kStack))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp9, kStack)), BinopInst("*", LoadVarInst(Address(fSlow88, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(2)], LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(2)], LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(2)], LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(2)], LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(2)], LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 244 bytes
Total heap size = 248 bytes
Stack size in compute = 376 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 10 write = 0 ratio = 10
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry15 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry16 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec8 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec7 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec6 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec5 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec4 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec3 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec2 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec1 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fRec0 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
