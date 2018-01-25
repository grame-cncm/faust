======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html")
	OpenVerticalBox("FLANGER")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the flanger   has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	AddMetaDeclareInst(fCheckbox1, "1", "")
	AddCheckButtonInst("Invert Flange Sum"fCheckbox1)
	AddMetaDeclareInst(fHbargraph0, "2", "")
	AddMetaDeclareInst(fHbargraph0, "style", "led")
	AddMetaDeclareInst(fHbargraph0, "tooltip", "Display sum of flange delays")
	AddHorizontalBargraph("Flange LFO", fHbargraph0, -1.5f, 1.5f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fHslider1, "1", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "unit", "Hz")
	AddHorizontalSlider("Speed", fHslider1, 0.5f, 0.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider2, "2", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("Depth", fHslider2, 1.0f, 0.0f, 1.0f, 0.00100000005f)
	AddMetaDeclareInst(fHslider3, "3", "")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("Feedback", fHslider3, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("Delay Controls")
	AddMetaDeclareInst(fHslider5, "1", "")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddMetaDeclareInst(fHslider5, "unit", "ms")
	AddHorizontalSlider("Flange Delay", fHslider5, 10.0f, 0.0f, 20.0f, 0.00100000005f)
	AddMetaDeclareInst(fHslider4, "2", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddMetaDeclareInst(fHslider4, "unit", "ms")
	AddHorizontalSlider("Delay Offset", fHslider4, 1.0f, 0.0f, 20.0f, 0.00100000005f)
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Flanger Output Level", fHslider0, 0.0f, -60.0f, 10.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec1[4096])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fVec2[4096])
	DeclareVarInst(struct, float, fRec3[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(2))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
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
			Case 1
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
			Case 1
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
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(10.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(4096))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(4096))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 18
Store = 0
Binop = 6
Numbers = 6
Declare = 15
Cast = 10
Select = 0
Loop = 0
Funcall = 3

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("sinf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("cosf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow7, Select2Inst(CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox1))) BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow6)) LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow8, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(0.000500000024f), CastInst("float", LoadVarInst(struct, fHslider5))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 74
Store = 17
Binop = 46
Numbers = 25
Declare = 13
Cast = 8
Select = 0
Loop = 1
Funcall = 2

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)]))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec0[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
		StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(struct, fRec1[Int32(0)]), LoadVarInst(struct, fRec0[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow1), Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec2[Int32(1)])), LoadVarInst(stack, fTemp1)))
		StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp2))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("+", LoadVarInst(stack, fSlow9), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f))))))
		DeclareVarInst(stack, "int", iTemp4, CastInst("int", LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp5, FunCallInst("floorf", LoadVarInst(stack, fTemp3)))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(2049), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp4)))), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp3)))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp5)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(2049), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1))))), Int32(4095))]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec2[Int32(0)])))))))
		DeclareVarInst(stack, "float", fTemp6, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fSlow1), Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp6))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec3[Int32(1)])), LoadVarInst(stack, fTemp7)))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp8))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("+", LoadVarInst(stack, fSlow9), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(struct, fRec1[Int32(0)]), Float(1.0f))))))
		DeclareVarInst(stack, "int", iTemp10, CastInst("int", LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "float", fTemp11, FunCallInst("floorf", LoadVarInst(stack, fTemp9)))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(2049), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp10)))), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp11), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp9)))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(2049), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp10), Int32(1))))), Int32(4095))]))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp6) BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(stack, fTemp7), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec3[Int32(0)])))))))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec1[4096])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fVec2[4096])
	DeclareVarInst(struct, float, fRec3[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(10.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(4096))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(4096))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("sinf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("cosf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow7, Select2Inst(CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox1))) BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow6)) LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow8, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(0.000500000024f), CastInst("float", LoadVarInst(struct, fHslider5))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)]))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec0[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
			StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(struct, fRec1[Int32(0)]), LoadVarInst(struct, fRec0[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow1), Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec2[Int32(1)])), LoadVarInst(stack, fTemp1)))
			StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp2))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("+", LoadVarInst(stack, fSlow9), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f))))))
			DeclareVarInst(stack, "int", iTemp4, CastInst("int", LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp5, FunCallInst("floorf", LoadVarInst(stack, fTemp3)))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(2049), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp4)))), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp3)))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp5)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(2049), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1))))), Int32(4095))]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec2[Int32(0)])))))))
			DeclareVarInst(stack, "float", fTemp6, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fSlow1), Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp6))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec3[Int32(1)])), LoadVarInst(stack, fTemp7)))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp8))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("+", LoadVarInst(stack, fSlow9), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(struct, fRec1[Int32(0)]), Float(1.0f))))))
			DeclareVarInst(stack, "int", iTemp10, CastInst("int", LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "float", fTemp11, FunCallInst("floorf", LoadVarInst(stack, fTemp9)))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(2049), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp10)))), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp11), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp9)))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(2049), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp10), Int32(1))))), Int32(4095))]))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp6) BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(stack, fTemp7), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec3[Int32(0)])))))))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 32844 bytes
Heap size = 32860 bytes
Stack size in compute = 76 bytes

