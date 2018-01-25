======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "tooltip", "Reference:   http://en.wikipedia.org/wiki/Dynamic_range_compression")
	OpenVerticalBox("COMPRESSOR")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the compressor   has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	AddMetaDeclareInst(fHbargraph0, "1", "")
	AddMetaDeclareInst(fHbargraph0, "tooltip", "Current gain of  the compressor in dB")
	AddMetaDeclareInst(fHbargraph0, "unit", "dB")
	AddHorizontalBargraph("Compressor Gain", fHbargraph0, -50.0f, 10.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(0, "3", "")
	OpenHorizontalBox("Compression Control")
	AddMetaDeclareInst(fHslider2, "0", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddMetaDeclareInst(fHslider2, "tooltip", "A compression Ratio of N means that for each N dB increase in input  signal level above Threshold, the output level goes up 1 dB")
	AddHorizontalSlider("Ratio", fHslider2, 5.0f, 1.0f, 20.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider4, "1", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddMetaDeclareInst(fHslider4, "tooltip", "When the signal level exceeds the Threshold (in dB), its level  is compressed according to the Ratio")
	AddMetaDeclareInst(fHslider4, "unit", "dB")
	AddHorizontalSlider("Threshold", fHslider4, -30.0f, -100.0f, 10.0f, 0.100000001f)
	CloseboxInst
	AddMetaDeclareInst(0, "4", "")
	OpenHorizontalBox("Compression Response")
	AddMetaDeclareInst(fHslider1, "1", "")
	AddMetaDeclareInst(fHslider1, "scale", "log")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "unit", "ms")
	AddHorizontalSlider("Attack     tooltip: Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new lower target level (the compression  `kicking in')]", fHslider1, 50.0f, 1.0f, 1000.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider3, "2", "")
	AddMetaDeclareInst(fHslider3, "scale", "log")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddMetaDeclareInst(fHslider3, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new higher target level (the compression  'releasing')")
	AddMetaDeclareInst(fHslider3, "unit", "ms")
	AddHorizontalSlider("Release", fHslider3, 500.0f, 1.0f, 1000.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(fHslider0, "5", "")
	AddMetaDeclareInst(fHslider0, "tooltip", "The compressed-signal output level is increased by this amount  (in dB) to make up for the level lost due to compression")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Makeup Gain", fHslider0, 40.0f, -96.0f, 96.0f, 0.100000001f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(2.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(40.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(500.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(-30.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 18
Store = 0
Binop = 13
Numbers = 10
Declare = 12
Cast = 7
Select = 0
Loop = 0
Funcall = 6

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow2)))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", BinopInst("+", BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2))), Float(-1.0f)), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow2)))))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))))))
	DeclareVarInst(stack, "float", fSlow7, CastInst("float", LoadVarInst(struct, fHslider4)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 63
Store = 16
Binop = 31
Numbers = 27
Declare = 12
Cast = 5
Select = 0
Loop = 1
Funcall = 13

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
		DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp3, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp2)))
		DeclareVarInst(stack, "float", fTemp4, FunCallInst("fabsf", BinopInst("+", FunCallInst("fabsf", LoadVarInst(stack, fTemp1)), FunCallInst("fabsf", LoadVarInst(stack, fTemp3)))))
		DeclareVarInst(stack, "float", fTemp5, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp4)) LoadVarInst(stack, fSlow6) LoadVarInst(stack, fSlow5)))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp5)), BinopInst("*", LoadVarInst(stack, fTemp4), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp5)))))
		StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("max_f", BinopInst("-", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec1[Int32(0)]))), LoadVarInst(stack, fSlow7)), Float(0.0f)))))
		DeclareVarInst(stack, "float", fTemp6, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec0[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp6)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp7)))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp6)))
		DeclareVarInst(stack, "float", fTemp9, FunCallInst("fabsf", BinopInst("+", FunCallInst("fabsf", LoadVarInst(stack, fTemp7)), FunCallInst("fabsf", LoadVarInst(stack, fTemp8)))))
		DeclareVarInst(stack, "float", fTemp10, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp9)) LoadVarInst(stack, fSlow6) LoadVarInst(stack, fSlow5)))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(stack, fTemp9), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp10)))))
		StoreVarInst(struct, fRec4[Int32(0)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("max_f", BinopInst("-", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec4[Int32(0)]))), LoadVarInst(stack, fSlow7)), Float(0.0f)))))
		StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec3[Int32(0)])))))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp2) BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp8)))))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(2.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(40.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(500.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(-30.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l5)], Float(0.0f))
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
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow2)))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", BinopInst("+", BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2))), Float(-1.0f)), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow2)))))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))))))
	DeclareVarInst(stack, "float", fSlow7, CastInst("float", LoadVarInst(struct, fHslider4)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
			DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp3, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp2)))
			DeclareVarInst(stack, "float", fTemp4, FunCallInst("fabsf", BinopInst("+", FunCallInst("fabsf", LoadVarInst(stack, fTemp1)), FunCallInst("fabsf", LoadVarInst(stack, fTemp3)))))
			DeclareVarInst(stack, "float", fTemp5, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp4)) LoadVarInst(stack, fSlow6) LoadVarInst(stack, fSlow5)))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp5)), BinopInst("*", LoadVarInst(stack, fTemp4), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp5)))))
			StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("max_f", BinopInst("-", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec1[Int32(0)]))), LoadVarInst(stack, fSlow7)), Float(0.0f)))))
			DeclareVarInst(stack, "float", fTemp6, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec0[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp6)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp7)))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp6)))
			DeclareVarInst(stack, "float", fTemp9, FunCallInst("fabsf", BinopInst("+", FunCallInst("fabsf", LoadVarInst(stack, fTemp7)), FunCallInst("fabsf", LoadVarInst(stack, fTemp8)))))
			DeclareVarInst(stack, "float", fTemp10, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp9)) LoadVarInst(stack, fSlow6) LoadVarInst(stack, fSlow5)))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(stack, fTemp9), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp10)))))
			StoreVarInst(struct, fRec4[Int32(0)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("max_f", BinopInst("-", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec4[Int32(0)]))), LoadVarInst(stack, fSlow7)), Float(0.0f)))))
			StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec3[Int32(0)])))))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp2) BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp8)))))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 88 bytes
Heap size = 92 bytes
Stack size in compute = 64 bytes

