======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenHorizontalBox("Multi Band Filter")
	OpenVerticalBox("peak 0")
	AddMetaDeclareInst(fEntry19, "style", "knob")
	AddNumEntry"Q factor", fEntry19, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry18, "style", "knob")
	AddMetaDeclareInst(fEntry18, "unit", "Hz")
	AddNumEntry"freq", fEntry18, 1000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider9, "unit", "dB")
	AddVerticalSlider("gain", fVslider9, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 1")
	AddMetaDeclareInst(fEntry17, "style", "knob")
	AddNumEntry"Q factor", fEntry17, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry16, "style", "knob")
	AddMetaDeclareInst(fEntry16, "unit", "Hz")
	AddNumEntry"freq", fEntry16, 2000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider8, "unit", "dB")
	AddVerticalSlider("gain", fVslider8, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 2")
	AddMetaDeclareInst(fEntry15, "style", "knob")
	AddNumEntry"Q factor", fEntry15, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry14, "style", "knob")
	AddMetaDeclareInst(fEntry14, "unit", "Hz")
	AddNumEntry"freq", fEntry14, 3000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider7, "unit", "dB")
	AddVerticalSlider("gain", fVslider7, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 3")
	AddMetaDeclareInst(fEntry13, "style", "knob")
	AddNumEntry"Q factor", fEntry13, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry12, "style", "knob")
	AddMetaDeclareInst(fEntry12, "unit", "Hz")
	AddNumEntry"freq", fEntry12, 4000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider6, "unit", "dB")
	AddVerticalSlider("gain", fVslider6, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 4")
	AddMetaDeclareInst(fEntry11, "style", "knob")
	AddNumEntry"Q factor", fEntry11, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry10, "style", "knob")
	AddMetaDeclareInst(fEntry10, "unit", "Hz")
	AddNumEntry"freq", fEntry10, 5000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider5, "unit", "dB")
	AddVerticalSlider("gain", fVslider5, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 5")
	AddMetaDeclareInst(fEntry9, "style", "knob")
	AddNumEntry"Q factor", fEntry9, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry8, "style", "knob")
	AddMetaDeclareInst(fEntry8, "unit", "Hz")
	AddNumEntry"freq", fEntry8, 6000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider4, "unit", "dB")
	AddVerticalSlider("gain", fVslider4, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 6")
	AddMetaDeclareInst(fEntry7, "style", "knob")
	AddNumEntry"Q factor", fEntry7, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry6, "style", "knob")
	AddMetaDeclareInst(fEntry6, "unit", "Hz")
	AddNumEntry"freq", fEntry6, 7000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider3, "unit", "dB")
	AddVerticalSlider("gain", fVslider3, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 7")
	AddMetaDeclareInst(fEntry5, "style", "knob")
	AddNumEntry"Q factor", fEntry5, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry4, "style", "knob")
	AddMetaDeclareInst(fEntry4, "unit", "Hz")
	AddNumEntry"freq", fEntry4, 8000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider2, "unit", "dB")
	AddVerticalSlider("gain", fVslider2, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 8")
	AddMetaDeclareInst(fEntry3, "style", "knob")
	AddNumEntry"Q factor", fEntry3, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry2, "style", "knob")
	AddMetaDeclareInst(fEntry2, "unit", "Hz")
	AddNumEntry"freq", fEntry2, 9000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider1, "unit", "dB")
	AddVerticalSlider("gain", fVslider1, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("peak 9")
	AddMetaDeclareInst(fEntry1, "style", "knob")
	AddNumEntry"Q factor", fEntry1, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddMetaDeclareInst(fEntry0, "unit", "Hz")
	AddNumEntry"freq", fEntry0, 10000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("gain", fVslider0, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry3)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry5)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry6)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry7)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry8)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry9)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry10)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry11)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry12)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry13)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry14)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry15)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry16)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry17)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry18)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry19)
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, float, fRec0[3])
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
	StoreVarInst(struct, fConst0, BinopInst("/", Float(3.14159274f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(10000.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry1, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry2, CastInst("FAUSTFLOAT", Double(9000.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry3, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry4, CastInst("FAUSTFLOAT", Double(8000.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry5, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry6, CastInst("FAUSTFLOAT", Double(7000.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry7, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry8, CastInst("FAUSTFLOAT", Double(6000.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry9, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry10, CastInst("FAUSTFLOAT", Double(5000.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry11, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry12, CastInst("FAUSTFLOAT", Double(4000.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry13, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry14, CastInst("FAUSTFLOAT", Double(3000.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry15, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry16, CastInst("FAUSTFLOAT", Double(2000.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry17, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry18, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry19, CastInst("FAUSTFLOAT", Double(50.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(3))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(3))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(3))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 192
Store = 0
Binop = 200
Numbers = 110
Declare = 92
Cast = 30
Select = 0
Loop = 0
Funcall = 30

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry0)))))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fEntry1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider0))))), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow0)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry2)))))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fEntry3)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider1))))), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow7))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow5)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry4)))))
	DeclareVarInst(stack, "float", fSlow11, CastInst("float", LoadVarInst(struct, fEntry5)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider2))))), LoadVarInst(stack, fSlow11)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fSlow12))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow10)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow15, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry6)))))
	DeclareVarInst(stack, "float", fSlow16, CastInst("float", LoadVarInst(struct, fEntry7)))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider3))))), LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(stack, fSlow15), LoadVarInst(stack, fSlow17))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow15)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow20, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry8)))))
	DeclareVarInst(stack, "float", fSlow21, CastInst("float", LoadVarInst(struct, fEntry9)))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider4))))), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fSlow22))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow20)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow25, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry10)))))
	DeclareVarInst(stack, "float", fSlow26, CastInst("float", LoadVarInst(struct, fEntry11)))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider5))))), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), BinopInst("+", LoadVarInst(stack, fSlow25), LoadVarInst(stack, fSlow27))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow25)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow30, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry12)))))
	DeclareVarInst(stack, "float", fSlow31, CastInst("float", LoadVarInst(struct, fEntry13)))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider6))))), LoadVarInst(stack, fSlow31)))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("+", LoadVarInst(stack, fSlow30), LoadVarInst(stack, fSlow32))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow34, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow30)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow35, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry14)))))
	DeclareVarInst(stack, "float", fSlow36, CastInst("float", LoadVarInst(struct, fEntry15)))
	DeclareVarInst(stack, "float", fSlow37, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider7))))), LoadVarInst(stack, fSlow36)))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("+", LoadVarInst(stack, fSlow35), LoadVarInst(stack, fSlow37))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow39, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow35)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow40, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry16)))))
	DeclareVarInst(stack, "float", fSlow41, CastInst("float", LoadVarInst(struct, fEntry17)))
	DeclareVarInst(stack, "float", fSlow42, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider8))))), LoadVarInst(stack, fSlow41)))
	DeclareVarInst(stack, "float", fSlow43, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), BinopInst("+", LoadVarInst(stack, fSlow40), LoadVarInst(stack, fSlow42))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow44, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow40)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow45, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry18)))))
	DeclareVarInst(stack, "float", fSlow46, CastInst("float", LoadVarInst(struct, fEntry19)))
	DeclareVarInst(stack, "float", fSlow47, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider9))))), LoadVarInst(stack, fSlow46)))
	DeclareVarInst(stack, "float", fSlow48, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("+", LoadVarInst(stack, fSlow45), LoadVarInst(stack, fSlow47))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow49, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow45)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow50, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("-", LoadVarInst(stack, fSlow45), LoadVarInst(stack, fSlow47))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow51, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow46)))
	DeclareVarInst(stack, "float", fSlow52, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("+", LoadVarInst(stack, fSlow45), LoadVarInst(stack, fSlow51))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow53, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("-", LoadVarInst(stack, fSlow51), LoadVarInst(stack, fSlow45)))))
	DeclareVarInst(stack, "float", fSlow54, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), BinopInst("-", LoadVarInst(stack, fSlow40), LoadVarInst(stack, fSlow42))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow55, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow41)))
	DeclareVarInst(stack, "float", fSlow56, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), BinopInst("+", LoadVarInst(stack, fSlow40), LoadVarInst(stack, fSlow55))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow57, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow40), BinopInst("-", LoadVarInst(stack, fSlow55), LoadVarInst(stack, fSlow40)))))
	DeclareVarInst(stack, "float", fSlow58, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("-", LoadVarInst(stack, fSlow35), LoadVarInst(stack, fSlow37))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow59, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow36)))
	DeclareVarInst(stack, "float", fSlow60, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("+", LoadVarInst(stack, fSlow35), LoadVarInst(stack, fSlow59))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow61, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("-", LoadVarInst(stack, fSlow59), LoadVarInst(stack, fSlow35)))))
	DeclareVarInst(stack, "float", fSlow62, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("-", LoadVarInst(stack, fSlow30), LoadVarInst(stack, fSlow32))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow63, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow31)))
	DeclareVarInst(stack, "float", fSlow64, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("+", LoadVarInst(stack, fSlow30), LoadVarInst(stack, fSlow63))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow65, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("-", LoadVarInst(stack, fSlow63), LoadVarInst(stack, fSlow30)))))
	DeclareVarInst(stack, "float", fSlow66, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), BinopInst("-", LoadVarInst(stack, fSlow25), LoadVarInst(stack, fSlow27))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow67, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow68, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), BinopInst("+", LoadVarInst(stack, fSlow25), LoadVarInst(stack, fSlow67))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow69, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow25), BinopInst("-", LoadVarInst(stack, fSlow67), LoadVarInst(stack, fSlow25)))))
	DeclareVarInst(stack, "float", fSlow70, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("-", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fSlow22))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow71, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow72, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fSlow71))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow73, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("-", LoadVarInst(stack, fSlow71), LoadVarInst(stack, fSlow20)))))
	DeclareVarInst(stack, "float", fSlow74, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("-", LoadVarInst(stack, fSlow15), LoadVarInst(stack, fSlow17))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow75, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow76, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(stack, fSlow15), LoadVarInst(stack, fSlow75))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow77, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("-", LoadVarInst(stack, fSlow75), LoadVarInst(stack, fSlow15)))))
	DeclareVarInst(stack, "float", fSlow78, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("-", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fSlow12))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow79, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow11)))
	DeclareVarInst(stack, "float", fSlow80, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fSlow79))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow81, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("-", LoadVarInst(stack, fSlow79), LoadVarInst(stack, fSlow10)))))
	DeclareVarInst(stack, "float", fSlow82, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow7))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow83, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow84, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow83))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow85, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(stack, fSlow83), LoadVarInst(stack, fSlow5)))))
	DeclareVarInst(stack, "float", fSlow86, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow87, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow88, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow87))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow89, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow87), LoadVarInst(stack, fSlow0)))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 145
Store = 32
Binop = 102
Numbers = 32
Declare = 11
Cast = 2
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow49), LoadVarInst(struct, fRec9[Int32(1)])))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow48), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow50), LoadVarInst(struct, fRec9[Int32(2)])), LoadVarInst(stack, fTemp0)))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow44), LoadVarInst(struct, fRec8[Int32(1)])))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow48), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp0), BinopInst("*", LoadVarInst(stack, fSlow52), LoadVarInst(struct, fRec9[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow53), LoadVarInst(struct, fRec9[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow43), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow54), LoadVarInst(struct, fRec8[Int32(2)])), LoadVarInst(stack, fTemp1)))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow39), LoadVarInst(struct, fRec7[Int32(1)])))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow43), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", LoadVarInst(stack, fSlow56), LoadVarInst(struct, fRec8[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow57), LoadVarInst(struct, fRec8[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow38), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow58), LoadVarInst(struct, fRec7[Int32(2)])), LoadVarInst(stack, fTemp2)))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(stack, fSlow34), LoadVarInst(struct, fRec6[Int32(1)])))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow38), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow60), LoadVarInst(struct, fRec7[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow61), LoadVarInst(struct, fRec7[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow33), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow62), LoadVarInst(struct, fRec6[Int32(2)])), LoadVarInst(stack, fTemp3)))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec5[Int32(1)])))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow33), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("*", LoadVarInst(stack, fSlow64), LoadVarInst(struct, fRec6[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow65), LoadVarInst(struct, fRec6[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow28), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow66), LoadVarInst(struct, fRec5[Int32(2)])), LoadVarInst(stack, fTemp4)))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec4[Int32(1)])))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow28), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow68), LoadVarInst(struct, fRec5[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow69), LoadVarInst(struct, fRec5[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow70), LoadVarInst(struct, fRec4[Int32(2)])), LoadVarInst(stack, fTemp5)))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fSlow19), LoadVarInst(struct, fRec3[Int32(1)])))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("*", LoadVarInst(stack, fSlow72), LoadVarInst(struct, fRec4[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow73), LoadVarInst(struct, fRec4[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow18), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow74), LoadVarInst(struct, fRec3[Int32(2)])), LoadVarInst(stack, fTemp6)))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec2[Int32(1)])))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow18), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp6), BinopInst("*", LoadVarInst(stack, fSlow76), LoadVarInst(struct, fRec3[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow77), LoadVarInst(struct, fRec3[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow78), LoadVarInst(struct, fRec2[Int32(2)])), LoadVarInst(stack, fTemp7)))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec1[Int32(1)])))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp7), BinopInst("*", LoadVarInst(stack, fSlow80), LoadVarInst(struct, fRec2[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow81), LoadVarInst(struct, fRec2[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow82), LoadVarInst(struct, fRec1[Int32(2)])), LoadVarInst(stack, fTemp8)))))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)])))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), BinopInst("*", LoadVarInst(stack, fSlow84), LoadVarInst(struct, fRec1[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow85), LoadVarInst(struct, fRec1[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow86), LoadVarInst(struct, fRec0[Int32(2)])), LoadVarInst(stack, fTemp9)))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp9), BinopInst("*", LoadVarInst(stack, fSlow88), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow89), LoadVarInst(struct, fRec0[Int32(2)]))))))
		StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry3)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry5)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry6)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry7)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry8)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry9)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry10)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry11)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry12)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry13)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry14)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry15)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry16)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry17)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry18)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry19)
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, float, fRec0[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(3.14159274f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(10000.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry1, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry2, CastInst("FAUSTFLOAT", Double(9000.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry3, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry4, CastInst("FAUSTFLOAT", Double(8000.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry5, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry6, CastInst("FAUSTFLOAT", Double(7000.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry7, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry8, CastInst("FAUSTFLOAT", Double(6000.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry9, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry10, CastInst("FAUSTFLOAT", Double(5000.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry11, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry12, CastInst("FAUSTFLOAT", Double(4000.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry13, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry14, CastInst("FAUSTFLOAT", Double(3000.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry15, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry16, CastInst("FAUSTFLOAT", Double(2000.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry17, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fEntry18, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry19, CastInst("FAUSTFLOAT", Double(50.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(3))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(3))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(3))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry0)))))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fEntry1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider0))))), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow0)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry2)))))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fEntry3)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider1))))), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow7))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow5)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry4)))))
	DeclareVarInst(stack, "float", fSlow11, CastInst("float", LoadVarInst(struct, fEntry5)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider2))))), LoadVarInst(stack, fSlow11)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fSlow12))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow10)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow15, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry6)))))
	DeclareVarInst(stack, "float", fSlow16, CastInst("float", LoadVarInst(struct, fEntry7)))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider3))))), LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(stack, fSlow15), LoadVarInst(stack, fSlow17))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow15)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow20, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry8)))))
	DeclareVarInst(stack, "float", fSlow21, CastInst("float", LoadVarInst(struct, fEntry9)))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider4))))), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fSlow22))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow20)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow25, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry10)))))
	DeclareVarInst(stack, "float", fSlow26, CastInst("float", LoadVarInst(struct, fEntry11)))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider5))))), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), BinopInst("+", LoadVarInst(stack, fSlow25), LoadVarInst(stack, fSlow27))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow25)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow30, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry12)))))
	DeclareVarInst(stack, "float", fSlow31, CastInst("float", LoadVarInst(struct, fEntry13)))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider6))))), LoadVarInst(stack, fSlow31)))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("+", LoadVarInst(stack, fSlow30), LoadVarInst(stack, fSlow32))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow34, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow30)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow35, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry14)))))
	DeclareVarInst(stack, "float", fSlow36, CastInst("float", LoadVarInst(struct, fEntry15)))
	DeclareVarInst(stack, "float", fSlow37, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider7))))), LoadVarInst(stack, fSlow36)))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("+", LoadVarInst(stack, fSlow35), LoadVarInst(stack, fSlow37))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow39, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow35)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow40, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry16)))))
	DeclareVarInst(stack, "float", fSlow41, CastInst("float", LoadVarInst(struct, fEntry17)))
	DeclareVarInst(stack, "float", fSlow42, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider8))))), LoadVarInst(stack, fSlow41)))
	DeclareVarInst(stack, "float", fSlow43, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), BinopInst("+", LoadVarInst(stack, fSlow40), LoadVarInst(stack, fSlow42))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow44, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow40)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow45, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry18)))))
	DeclareVarInst(stack, "float", fSlow46, CastInst("float", LoadVarInst(struct, fEntry19)))
	DeclareVarInst(stack, "float", fSlow47, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider9))))), LoadVarInst(stack, fSlow46)))
	DeclareVarInst(stack, "float", fSlow48, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("+", LoadVarInst(stack, fSlow45), LoadVarInst(stack, fSlow47))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow49, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow45)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow50, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("-", LoadVarInst(stack, fSlow45), LoadVarInst(stack, fSlow47))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow51, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow46)))
	DeclareVarInst(stack, "float", fSlow52, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("+", LoadVarInst(stack, fSlow45), LoadVarInst(stack, fSlow51))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow53, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("-", LoadVarInst(stack, fSlow51), LoadVarInst(stack, fSlow45)))))
	DeclareVarInst(stack, "float", fSlow54, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), BinopInst("-", LoadVarInst(stack, fSlow40), LoadVarInst(stack, fSlow42))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow55, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow41)))
	DeclareVarInst(stack, "float", fSlow56, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), BinopInst("+", LoadVarInst(stack, fSlow40), LoadVarInst(stack, fSlow55))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow57, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow40), BinopInst("-", LoadVarInst(stack, fSlow55), LoadVarInst(stack, fSlow40)))))
	DeclareVarInst(stack, "float", fSlow58, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("-", LoadVarInst(stack, fSlow35), LoadVarInst(stack, fSlow37))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow59, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow36)))
	DeclareVarInst(stack, "float", fSlow60, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("+", LoadVarInst(stack, fSlow35), LoadVarInst(stack, fSlow59))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow61, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("-", LoadVarInst(stack, fSlow59), LoadVarInst(stack, fSlow35)))))
	DeclareVarInst(stack, "float", fSlow62, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("-", LoadVarInst(stack, fSlow30), LoadVarInst(stack, fSlow32))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow63, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow31)))
	DeclareVarInst(stack, "float", fSlow64, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("+", LoadVarInst(stack, fSlow30), LoadVarInst(stack, fSlow63))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow65, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("-", LoadVarInst(stack, fSlow63), LoadVarInst(stack, fSlow30)))))
	DeclareVarInst(stack, "float", fSlow66, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), BinopInst("-", LoadVarInst(stack, fSlow25), LoadVarInst(stack, fSlow27))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow67, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow68, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), BinopInst("+", LoadVarInst(stack, fSlow25), LoadVarInst(stack, fSlow67))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow69, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow25), BinopInst("-", LoadVarInst(stack, fSlow67), LoadVarInst(stack, fSlow25)))))
	DeclareVarInst(stack, "float", fSlow70, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("-", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fSlow22))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow71, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow72, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fSlow71))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow73, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("-", LoadVarInst(stack, fSlow71), LoadVarInst(stack, fSlow20)))))
	DeclareVarInst(stack, "float", fSlow74, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("-", LoadVarInst(stack, fSlow15), LoadVarInst(stack, fSlow17))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow75, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow76, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(stack, fSlow15), LoadVarInst(stack, fSlow75))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow77, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("-", LoadVarInst(stack, fSlow75), LoadVarInst(stack, fSlow15)))))
	DeclareVarInst(stack, "float", fSlow78, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("-", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fSlow12))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow79, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow11)))
	DeclareVarInst(stack, "float", fSlow80, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fSlow79))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow81, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("-", LoadVarInst(stack, fSlow79), LoadVarInst(stack, fSlow10)))))
	DeclareVarInst(stack, "float", fSlow82, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow7))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow83, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow84, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow83))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow85, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(stack, fSlow83), LoadVarInst(stack, fSlow5)))))
	DeclareVarInst(stack, "float", fSlow86, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow87, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow88, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow87))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow89, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow87), LoadVarInst(stack, fSlow0)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow49), LoadVarInst(struct, fRec9[Int32(1)])))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow48), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow50), LoadVarInst(struct, fRec9[Int32(2)])), LoadVarInst(stack, fTemp0)))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow44), LoadVarInst(struct, fRec8[Int32(1)])))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow48), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp0), BinopInst("*", LoadVarInst(stack, fSlow52), LoadVarInst(struct, fRec9[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow53), LoadVarInst(struct, fRec9[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow43), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow54), LoadVarInst(struct, fRec8[Int32(2)])), LoadVarInst(stack, fTemp1)))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow39), LoadVarInst(struct, fRec7[Int32(1)])))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow43), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", LoadVarInst(stack, fSlow56), LoadVarInst(struct, fRec8[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow57), LoadVarInst(struct, fRec8[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow38), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow58), LoadVarInst(struct, fRec7[Int32(2)])), LoadVarInst(stack, fTemp2)))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(stack, fSlow34), LoadVarInst(struct, fRec6[Int32(1)])))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow38), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow60), LoadVarInst(struct, fRec7[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow61), LoadVarInst(struct, fRec7[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow33), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow62), LoadVarInst(struct, fRec6[Int32(2)])), LoadVarInst(stack, fTemp3)))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec5[Int32(1)])))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow33), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("*", LoadVarInst(stack, fSlow64), LoadVarInst(struct, fRec6[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow65), LoadVarInst(struct, fRec6[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow28), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow66), LoadVarInst(struct, fRec5[Int32(2)])), LoadVarInst(stack, fTemp4)))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec4[Int32(1)])))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow28), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow68), LoadVarInst(struct, fRec5[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow69), LoadVarInst(struct, fRec5[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow70), LoadVarInst(struct, fRec4[Int32(2)])), LoadVarInst(stack, fTemp5)))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fSlow19), LoadVarInst(struct, fRec3[Int32(1)])))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("*", LoadVarInst(stack, fSlow72), LoadVarInst(struct, fRec4[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow73), LoadVarInst(struct, fRec4[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow18), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow74), LoadVarInst(struct, fRec3[Int32(2)])), LoadVarInst(stack, fTemp6)))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec2[Int32(1)])))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow18), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp6), BinopInst("*", LoadVarInst(stack, fSlow76), LoadVarInst(struct, fRec3[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow77), LoadVarInst(struct, fRec3[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow78), LoadVarInst(struct, fRec2[Int32(2)])), LoadVarInst(stack, fTemp7)))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec1[Int32(1)])))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp7), BinopInst("*", LoadVarInst(stack, fSlow80), LoadVarInst(struct, fRec2[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow81), LoadVarInst(struct, fRec2[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow82), LoadVarInst(struct, fRec1[Int32(2)])), LoadVarInst(stack, fTemp8)))))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)])))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), BinopInst("*", LoadVarInst(stack, fSlow84), LoadVarInst(struct, fRec1[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow85), LoadVarInst(struct, fRec1[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow86), LoadVarInst(struct, fRec0[Int32(2)])), LoadVarInst(stack, fTemp9)))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp9), BinopInst("*", LoadVarInst(stack, fSlow88), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow89), LoadVarInst(struct, fRec0[Int32(2)]))))))
			StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 244 bytes
Heap size = 248 bytes
Stack size in compute = 376 bytes

