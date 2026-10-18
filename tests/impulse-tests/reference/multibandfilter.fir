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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fEntry0)("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fEntry1)("float[3]", fIIR9)("FAUSTFLOAT", fEntry2)("FAUSTFLOAT", fVslider1)("FAUSTFLOAT", fEntry3)("float[3]", fIIR8)("FAUSTFLOAT", fEntry4)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fEntry5)("float[3]", fIIR7)("FAUSTFLOAT", fEntry6)("FAUSTFLOAT", fVslider3)("FAUSTFLOAT", fEntry7)("float[3]", fIIR6)("FAUSTFLOAT", fEntry8)("FAUSTFLOAT", fVslider4)("FAUSTFLOAT", fEntry9)("float[3]", fIIR5)("FAUSTFLOAT", fEntry10)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fEntry11)("float[3]", fIIR4)("FAUSTFLOAT", fEntry12)("FAUSTFLOAT", fVslider6)("FAUSTFLOAT", fEntry13)("float[3]", fIIR3)("FAUSTFLOAT", fEntry14)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fEntry15)("float[3]", fIIR2)("FAUSTFLOAT", fEntry16)("FAUSTFLOAT", fVslider8)("FAUSTFLOAT", fEntry17)("float[3]", fIIR1)("FAUSTFLOAT", fEntry18)("FAUSTFLOAT", fVslider9)("FAUSTFLOAT", fEntry19)("float[3]", fIIR0)>)

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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(1e+03f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Float(2e+03f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Float(3e+03f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Float(4e+03f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry8, kStruct), CastInst("FAUSTFLOAT", Float(5e+03f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry9, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry10, kStruct), CastInst("FAUSTFLOAT", Float(6e+03f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry11, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry12, kStruct), CastInst("FAUSTFLOAT", Float(7e+03f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry13, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry14, kStruct), CastInst("FAUSTFLOAT", Float(8e+03f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry15, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry16, kStruct), CastInst("FAUSTFLOAT", Float(9e+03f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry17, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry18, kStruct), CastInst("FAUSTFLOAT", Float(1e+04f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry19, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(3))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR9, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(3))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR8, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(3))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(3))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(3))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(3))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(3))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(3))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 232 Store = 0 Binop = 160 [ { Real(*) = 40 } { Real(+) = 40 } { Real(-) = 20 } { Real(/) = 60 } ] Mathop = 90 [ { max_f = 30 } { min_f = 30 } { mydsp_faustpower2_f = 10 } { powf = 10 } { tanf = 10 } ] Numbers = 112 Declare = 112 Cast = 30 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))))), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f)))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow1, kStack))), LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow3, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("/", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fSlow4, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow8, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))))))
	DeclareVarInst("float", fSlow12, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow13, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))))), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow12, kStack))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("+", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fSlow15, kStack))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow12, kStack))), LoadVarInst(Address(fSlow16, kStack)))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow14, kStack))), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("/", LoadVarInst(Address(fSlow11, kStack)), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fSlow15, kStack))), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow19, kStack))), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow22, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("float", fSlow24, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry5, kStruct))))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))))))), LoadVarInst(Address(fSlow24, kStack))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow23, kStack))), LoadVarInst(Address(fSlow27, kStack)))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fSlow25, kStack))), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("/", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fSlow24, kStack))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow26, kStack))), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fSlow30, kStack))), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry6, kStruct))))))))
	DeclareVarInst("float", fSlow34, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow33, kStack))))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry7, kStruct))))))
	DeclareVarInst("float", fSlow36, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))))), LoadVarInst(Address(fSlow35, kStack))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow34, kStack))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fSlow37, kStack))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow34, kStack))), LoadVarInst(Address(fSlow38, kStack)))))
	DeclareVarInst("float", fSlow40, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fSlow36, kStack))), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("/", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fSlow35, kStack))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fSlow37, kStack))), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow43, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fSlow41, kStack))), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry8, kStruct))))))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow44, kStack))))
	DeclareVarInst("float", fSlow46, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry9, kStruct))))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))))), LoadVarInst(Address(fSlow46, kStack))))
	DeclareVarInst("float", fSlow48, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow45, kStack))))
	DeclareVarInst("float", fSlow49, kStack, BinopInst("+", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fSlow48, kStack))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow45, kStack))), LoadVarInst(Address(fSlow49, kStack)))))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fSlow47, kStack))), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("/", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fSlow46, kStack))))
	DeclareVarInst("float", fSlow53, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fSlow48, kStack))), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow54, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fSlow52, kStack))), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow55, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry10, kStruct))))))))
	DeclareVarInst("float", fSlow56, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow55, kStack))))
	DeclareVarInst("float", fSlow57, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry11, kStruct))))))
	DeclareVarInst("float", fSlow58, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow55, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))))), LoadVarInst(Address(fSlow57, kStack))))
	DeclareVarInst("float", fSlow59, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow56, kStack))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("+", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fSlow59, kStack))))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow56, kStack))), LoadVarInst(Address(fSlow60, kStack)))))
	DeclareVarInst("float", fSlow62, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fSlow58, kStack))), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow63, kStack, BinopInst("/", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fSlow57, kStack))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fSlow59, kStack))), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fSlow63, kStack))), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow66, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry12, kStruct))))))))
	DeclareVarInst("float", fSlow67, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow66, kStack))))
	DeclareVarInst("float", fSlow68, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry13, kStruct))))))
	DeclareVarInst("float", fSlow69, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))))), LoadVarInst(Address(fSlow68, kStack))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow67, kStack))))
	DeclareVarInst("float", fSlow71, kStack, BinopInst("+", LoadVarInst(Address(fSlow69, kStack)), LoadVarInst(Address(fSlow70, kStack))))
	DeclareVarInst("float", fSlow72, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow67, kStack))), LoadVarInst(Address(fSlow71, kStack)))))
	DeclareVarInst("float", fSlow73, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fSlow69, kStack))), LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("/", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fSlow68, kStack))))
	DeclareVarInst("float", fSlow75, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fSlow70, kStack))), LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow76, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fSlow74, kStack))), LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow77, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry14, kStruct))))))))
	DeclareVarInst("float", fSlow78, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow77, kStack))))
	DeclareVarInst("float", fSlow79, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry15, kStruct))))))
	DeclareVarInst("float", fSlow80, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))))), LoadVarInst(Address(fSlow79, kStack))))
	DeclareVarInst("float", fSlow81, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow78, kStack))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("+", LoadVarInst(Address(fSlow80, kStack)), LoadVarInst(Address(fSlow81, kStack))))
	DeclareVarInst("float", fSlow83, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow78, kStack))), LoadVarInst(Address(fSlow82, kStack)))))
	DeclareVarInst("float", fSlow84, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fSlow80, kStack))), LoadVarInst(Address(fSlow82, kStack))))
	DeclareVarInst("float", fSlow85, kStack, BinopInst("/", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fSlow79, kStack))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow85, kStack)), LoadVarInst(Address(fSlow81, kStack))), LoadVarInst(Address(fSlow82, kStack))))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fSlow85, kStack))), LoadVarInst(Address(fSlow82, kStack))))
	DeclareVarInst("float", fSlow88, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry16, kStruct))))))))
	DeclareVarInst("float", fSlow89, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow88, kStack))))
	DeclareVarInst("float", fSlow90, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry17, kStruct))))))
	DeclareVarInst("float", fSlow91, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow88, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))))), LoadVarInst(Address(fSlow90, kStack))))
	DeclareVarInst("float", fSlow92, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow89, kStack))))
	DeclareVarInst("float", fSlow93, kStack, BinopInst("+", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fSlow92, kStack))))
	DeclareVarInst("float", fSlow94, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow89, kStack))), LoadVarInst(Address(fSlow93, kStack)))))
	DeclareVarInst("float", fSlow95, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fSlow91, kStack))), LoadVarInst(Address(fSlow93, kStack))))
	DeclareVarInst("float", fSlow96, kStack, BinopInst("/", LoadVarInst(Address(fSlow88, kStack)), LoadVarInst(Address(fSlow90, kStack))))
	DeclareVarInst("float", fSlow97, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fSlow92, kStack))), LoadVarInst(Address(fSlow93, kStack))))
	DeclareVarInst("float", fSlow98, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fSlow96, kStack))), LoadVarInst(Address(fSlow93, kStack))))
	DeclareVarInst("float", fSlow99, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry18, kStruct))))))))
	DeclareVarInst("float", fSlow100, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow99, kStack))))
	DeclareVarInst("float", fSlow101, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry19, kStruct))))))
	DeclareVarInst("float", fSlow102, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow99, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))))))), LoadVarInst(Address(fSlow101, kStack))))
	DeclareVarInst("float", fSlow103, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow100, kStack))))
	DeclareVarInst("float", fSlow104, kStack, BinopInst("+", LoadVarInst(Address(fSlow102, kStack)), LoadVarInst(Address(fSlow103, kStack))))
	DeclareVarInst("float", fSlow105, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow100, kStack))), LoadVarInst(Address(fSlow104, kStack)))))
	DeclareVarInst("float", fSlow106, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow103, kStack)), LoadVarInst(Address(fSlow102, kStack))), LoadVarInst(Address(fSlow104, kStack))))
	DeclareVarInst("float", fSlow107, kStack, BinopInst("/", LoadVarInst(Address(fSlow99, kStack)), LoadVarInst(Address(fSlow101, kStack))))
	DeclareVarInst("float", fSlow108, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow107, kStack)), LoadVarInst(Address(fSlow103, kStack))), LoadVarInst(Address(fSlow104, kStack))))
	DeclareVarInst("float", fSlow109, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow103, kStack)), LoadVarInst(Address(fSlow107, kStack))), LoadVarInst(Address(fSlow104, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 136 Store = 32 Binop = 92 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 50 } { Real(+) = 20 } { Real(-) = 20 } ] Mathop = 0 Numbers = 102 Declare = 11 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("-", BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow51, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp5, kStack)))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow65, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow73, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow75, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow76, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow83, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow84, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow86, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow83, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow87, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow94, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow95, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp8, kStack)))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow94, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow98, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow105, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow106, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp9, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow108, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow105, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow109, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fIIR9, kStruct)[Int32(2)], LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR9, kStruct)[Int32(1)], LoadVarInst(Address(fIIR9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(2)], LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(1)], LoadVarInst(Address(fIIR8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(2)], LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(2)], LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(2)], LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(2)], LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(2)], LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(2)], LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(2)], LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("float", fIIR9[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry3, kStruct)
	DeclareVarInst("float", fIIR8[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry5, kStruct)
	DeclareVarInst("float", fIIR7[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry7, kStruct)
	DeclareVarInst("float", fIIR6[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry9, kStruct)
	DeclareVarInst("float", fIIR5[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry11, kStruct)
	DeclareVarInst("float", fIIR4[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry13, kStruct)
	DeclareVarInst("float", fIIR3[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry15, kStruct)
	DeclareVarInst("float", fIIR2[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry16, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry17, kStruct)
	DeclareVarInst("float", fIIR1[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry18, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry19, kStruct)
	DeclareVarInst("float", fIIR0[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(1e+03f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Float(2e+03f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Float(3e+03f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry5, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry6, kStruct), CastInst("FAUSTFLOAT", Float(4e+03f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry7, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry8, kStruct), CastInst("FAUSTFLOAT", Float(5e+03f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry9, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry10, kStruct), CastInst("FAUSTFLOAT", Float(6e+03f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry11, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry12, kStruct), CastInst("FAUSTFLOAT", Float(7e+03f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry13, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry14, kStruct), CastInst("FAUSTFLOAT", Float(8e+03f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry15, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry16, kStruct), CastInst("FAUSTFLOAT", Float(9e+03f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry17, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fEntry18, kStruct), CastInst("FAUSTFLOAT", Float(1e+04f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry19, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(3))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR9, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(3))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR8, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(3))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(3))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(3))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(3))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(3))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(3))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))))), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f)))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow1, kStack))), LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow3, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("/", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fSlow4, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow8, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))))))
	DeclareVarInst("float", fSlow12, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow13, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))))), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow12, kStack))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("+", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fSlow15, kStack))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow12, kStack))), LoadVarInst(Address(fSlow16, kStack)))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow14, kStack))), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("/", LoadVarInst(Address(fSlow11, kStack)), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fSlow15, kStack))), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fSlow19, kStack))), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow22, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("float", fSlow24, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry5, kStruct))))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))))))), LoadVarInst(Address(fSlow24, kStack))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow23, kStack))), LoadVarInst(Address(fSlow27, kStack)))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fSlow25, kStack))), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("/", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fSlow24, kStack))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow26, kStack))), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fSlow30, kStack))), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry6, kStruct))))))))
	DeclareVarInst("float", fSlow34, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow33, kStack))))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry7, kStruct))))))
	DeclareVarInst("float", fSlow36, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))))), LoadVarInst(Address(fSlow35, kStack))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow34, kStack))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fSlow37, kStack))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow34, kStack))), LoadVarInst(Address(fSlow38, kStack)))))
	DeclareVarInst("float", fSlow40, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fSlow36, kStack))), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("/", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fSlow35, kStack))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fSlow37, kStack))), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow43, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fSlow41, kStack))), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry8, kStruct))))))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow44, kStack))))
	DeclareVarInst("float", fSlow46, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry9, kStruct))))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))))), LoadVarInst(Address(fSlow46, kStack))))
	DeclareVarInst("float", fSlow48, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow45, kStack))))
	DeclareVarInst("float", fSlow49, kStack, BinopInst("+", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fSlow48, kStack))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow45, kStack))), LoadVarInst(Address(fSlow49, kStack)))))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fSlow47, kStack))), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("/", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fSlow46, kStack))))
	DeclareVarInst("float", fSlow53, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fSlow48, kStack))), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow54, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fSlow52, kStack))), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow55, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry10, kStruct))))))))
	DeclareVarInst("float", fSlow56, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow55, kStack))))
	DeclareVarInst("float", fSlow57, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry11, kStruct))))))
	DeclareVarInst("float", fSlow58, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow55, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))))), LoadVarInst(Address(fSlow57, kStack))))
	DeclareVarInst("float", fSlow59, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow56, kStack))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("+", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fSlow59, kStack))))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow56, kStack))), LoadVarInst(Address(fSlow60, kStack)))))
	DeclareVarInst("float", fSlow62, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fSlow58, kStack))), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow63, kStack, BinopInst("/", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fSlow57, kStack))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fSlow59, kStack))), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fSlow63, kStack))), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow66, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry12, kStruct))))))))
	DeclareVarInst("float", fSlow67, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow66, kStack))))
	DeclareVarInst("float", fSlow68, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry13, kStruct))))))
	DeclareVarInst("float", fSlow69, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))))), LoadVarInst(Address(fSlow68, kStack))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow67, kStack))))
	DeclareVarInst("float", fSlow71, kStack, BinopInst("+", LoadVarInst(Address(fSlow69, kStack)), LoadVarInst(Address(fSlow70, kStack))))
	DeclareVarInst("float", fSlow72, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow67, kStack))), LoadVarInst(Address(fSlow71, kStack)))))
	DeclareVarInst("float", fSlow73, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fSlow69, kStack))), LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("/", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fSlow68, kStack))))
	DeclareVarInst("float", fSlow75, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fSlow70, kStack))), LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow76, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fSlow74, kStack))), LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow77, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry14, kStruct))))))))
	DeclareVarInst("float", fSlow78, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow77, kStack))))
	DeclareVarInst("float", fSlow79, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry15, kStruct))))))
	DeclareVarInst("float", fSlow80, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))))), LoadVarInst(Address(fSlow79, kStack))))
	DeclareVarInst("float", fSlow81, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow78, kStack))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("+", LoadVarInst(Address(fSlow80, kStack)), LoadVarInst(Address(fSlow81, kStack))))
	DeclareVarInst("float", fSlow83, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow78, kStack))), LoadVarInst(Address(fSlow82, kStack)))))
	DeclareVarInst("float", fSlow84, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fSlow80, kStack))), LoadVarInst(Address(fSlow82, kStack))))
	DeclareVarInst("float", fSlow85, kStack, BinopInst("/", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fSlow79, kStack))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow85, kStack)), LoadVarInst(Address(fSlow81, kStack))), LoadVarInst(Address(fSlow82, kStack))))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fSlow85, kStack))), LoadVarInst(Address(fSlow82, kStack))))
	DeclareVarInst("float", fSlow88, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry16, kStruct))))))))
	DeclareVarInst("float", fSlow89, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow88, kStack))))
	DeclareVarInst("float", fSlow90, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry17, kStruct))))))
	DeclareVarInst("float", fSlow91, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow88, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))))), LoadVarInst(Address(fSlow90, kStack))))
	DeclareVarInst("float", fSlow92, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow89, kStack))))
	DeclareVarInst("float", fSlow93, kStack, BinopInst("+", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fSlow92, kStack))))
	DeclareVarInst("float", fSlow94, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow89, kStack))), LoadVarInst(Address(fSlow93, kStack)))))
	DeclareVarInst("float", fSlow95, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fSlow91, kStack))), LoadVarInst(Address(fSlow93, kStack))))
	DeclareVarInst("float", fSlow96, kStack, BinopInst("/", LoadVarInst(Address(fSlow88, kStack)), LoadVarInst(Address(fSlow90, kStack))))
	DeclareVarInst("float", fSlow97, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fSlow92, kStack))), LoadVarInst(Address(fSlow93, kStack))))
	DeclareVarInst("float", fSlow98, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fSlow96, kStack))), LoadVarInst(Address(fSlow93, kStack))))
	DeclareVarInst("float", fSlow99, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry18, kStruct))))))))
	DeclareVarInst("float", fSlow100, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow99, kStack))))
	DeclareVarInst("float", fSlow101, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry19, kStruct))))))
	DeclareVarInst("float", fSlow102, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow99, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))))))), LoadVarInst(Address(fSlow101, kStack))))
	DeclareVarInst("float", fSlow103, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow100, kStack))))
	DeclareVarInst("float", fSlow104, kStack, BinopInst("+", LoadVarInst(Address(fSlow102, kStack)), LoadVarInst(Address(fSlow103, kStack))))
	DeclareVarInst("float", fSlow105, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow100, kStack))), LoadVarInst(Address(fSlow104, kStack)))))
	DeclareVarInst("float", fSlow106, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow103, kStack)), LoadVarInst(Address(fSlow102, kStack))), LoadVarInst(Address(fSlow104, kStack))))
	DeclareVarInst("float", fSlow107, kStack, BinopInst("/", LoadVarInst(Address(fSlow99, kStack)), LoadVarInst(Address(fSlow101, kStack))))
	DeclareVarInst("float", fSlow108, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow107, kStack)), LoadVarInst(Address(fSlow103, kStack))), LoadVarInst(Address(fSlow104, kStack))))
	DeclareVarInst("float", fSlow109, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow103, kStack)), LoadVarInst(Address(fSlow107, kStack))), LoadVarInst(Address(fSlow104, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("-", BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fIIR9, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fIIR8, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow51, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp5, kStack)))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow65, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow73, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow75, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow76, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow83, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow84, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow86, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow83, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow87, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow94, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow95, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp8, kStack)))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow94, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow98, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow105, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow106, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp9, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow108, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow105, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow109, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fIIR9, kStruct)[Int32(2)], LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR9, kStruct)[Int32(1)], LoadVarInst(Address(fIIR9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(2)], LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(1)], LoadVarInst(Address(fIIR8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(2)], LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(2)], LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(2)], LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(2)], LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(2)], LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(2)], LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(2)], LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
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
Stack size in compute = 456 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 10 write = 0 ratio = 10
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry15 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry16 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fEntry18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR9 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR8 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fEntry18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            10483
  eval() cache hits:       2786 (26.5764%)
  eval() cache misses:     7697
  Loop detector calls:     7697
  Stack detector calls:    7697

--- Phase 3: Propagation ---
  propagate() calls:       4429
  propagate() cache hits:  1825 (41.2057%)
  propagate() cache misses:2604

--- Box Type Computation ---
  getBoxType() calls:      5816
  getBoxType() cache hits: 4978 (85.5915%)
  getBoxType() computed:   838

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       231

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           21578
  Trees reused (hash):     53533 (71.2719% reuse rate)
  Property set ops:        9192
  Property get ops:        25168

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        10
  sum() iterations:        0
  prod() iterations:       0

==========================================
