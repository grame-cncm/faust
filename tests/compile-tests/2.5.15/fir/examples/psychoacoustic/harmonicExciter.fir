======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("harmonicExciter")
	AddMetaDeclareInst(0, "tooltip", "Reference:    http://en.wikipedia.org/wiki/Dynamic_range_compression")
	OpenVerticalBox("COMPRESSOR")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked,   the compressor has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	AddMetaDeclareInst(fHbargraph0, "1", "")
	AddMetaDeclareInst(fHbargraph0, "tooltip", "Current gain   of the compressor in dB")
	AddMetaDeclareInst(fHbargraph0, "unit", "dB")
	AddHorizontalBargraph("Compressor Gain", fHbargraph0, -50.0f, 10.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(0, "3", "")
	OpenHorizontalBox("Compression Control")
	AddMetaDeclareInst(fHslider3, "0", "")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddMetaDeclareInst(fHslider3, "tooltip", "A compression Ratio  of N means that for each N dB increase in input signal level above Threshold, the  output level goes up 1 dB")
	AddHorizontalSlider("Ratio", fHslider3, 5.0f, 1.0f, 20.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider6, "1", "")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddMetaDeclareInst(fHslider6, "tooltip", "When the signal level exceeds the Threshold (in dB), its level is compressed  according to the Ratio")
	AddMetaDeclareInst(fHslider6, "unit", "dB")
	AddHorizontalSlider("Threshold", fHslider6, -30.0f, -100.0f, 10.0f, 0.100000001f)
	CloseboxInst
	AddMetaDeclareInst(0, "4", "")
	OpenHorizontalBox("Compression Response")
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddMetaDeclareInst(fHslider2, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new lower target level (the compression `kicking in')")
	AddMetaDeclareInst(fHslider2, "unit", "ms")
	AddHorizontalSlider("Attack", fHslider2, 50.0f, 0.0f, 500.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider5, "2", "")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddMetaDeclareInst(fHslider5, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new higher target level (the compression 'releasing')")
	AddMetaDeclareInst(fHslider5, "unit", "ms")
	AddHorizontalSlider("Release", fHslider5, 500.0f, 0.0f, 1000.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(0, "tooltip", "Reference: Patent US4150253 A")
	OpenHorizontalBox("EXCITER")
	AddMetaDeclareInst(fHslider4, "0", "")
	AddMetaDeclareInst(fHslider4, "scale", "log")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddMetaDeclareInst(fHslider4, "tooltip", "Cutoff frequency for highpassed components to be excited")
	AddMetaDeclareInst(fHslider4, "unit", "Hz")
	AddHorizontalSlider("Cutoff Frequency", fHslider4, 5000.0f, 1000.0f, 10000.0f, 100.0f)
	AddMetaDeclareInst(fHslider1, "1", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "tooltip", "Percentage of harmonics generated")
	AddMetaDeclareInst(fHslider1, "unit", "percent")
	AddHorizontalSlider("Harmonics", fHslider1, 20.0f, 0.0f, 200.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "tooltip", "Dry/Wet mix of original signal   to excited signal")
	AddHorizontalSlider("Mix", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
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
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(2.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(20.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(5000.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(500.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(-30.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(3))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l3)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 31
Store = 0
Binop = 30
Numbers = 22
Declare = 21
Cast = 9
Select = 0
Loop = 0
Funcall = 7

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(100.0f), BinopInst("/", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00999999978f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "int", iSlow4, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow5)))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", BinopInst("+", BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider3))), Float(-1.0f)), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow8, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst3), CastInst("float", LoadVarInst(struct, fHslider4)))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow9), Float(1.41421354f)), LoadVarInst(stack, fSlow8)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow8))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow11))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow9), Float(-1.41421354f)), LoadVarInst(stack, fSlow8)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow11))))
	DeclareVarInst(stack, "float", fSlow15, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow5)))))
	DeclareVarInst(stack, "float", fSlow16, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider5))))))))
	DeclareVarInst(stack, "float", fSlow17, CastInst("float", LoadVarInst(struct, fHslider6)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow0)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 77
Store = 18
Binop = 54
Numbers = 35
Declare = 11
Cast = 6
Select = 0
Loop = 1
Funcall = 11

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp0), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec3[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec3[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec3[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec3[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp2, Select2Inst(LoadVarInst(stack, iSlow4) Float(0.0f) LoadVarInst(stack, fTemp1)))
		DeclareVarInst(stack, "float", fTemp3, FunCallInst("fabsf", LoadVarInst(stack, fTemp2)))
		DeclareVarInst(stack, "float", fTemp4, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(stack, fTemp3)) LoadVarInst(stack, fSlow16) LoadVarInst(stack, fSlow15)))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(stack, fTemp4)), BinopInst("*", LoadVarInst(stack, fTemp3), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp4)))))
		StoreVarInst(struct, fRec5[Int32(0)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec4[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow7), FunCallInst("max_f", BinopInst("-", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec5[Int32(0)]))), LoadVarInst(stack, fSlow17)), Float(0.0f)))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fTemp2), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec4[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp6, FunCallInst("fabsf", FunCallInst("fabsf", LoadVarInst(stack, fTemp5))))
		DeclareVarInst(stack, "float", fTemp7, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp6)) LoadVarInst(stack, fSlow16) LoadVarInst(stack, fSlow15)))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp7)), BinopInst("*", LoadVarInst(stack, fTemp6), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp7)))))
		StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow7), FunCallInst("max_f", BinopInst("-", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec1[Int32(0)]))), LoadVarInst(stack, fSlow17)), Float(0.0f)))))
		StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec0[Int32(0)])))))))
		DeclareVarInst(stack, "float", fTemp8, Select2Inst(LoadVarInst(stack, iSlow4) LoadVarInst(stack, fTemp1) LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fTemp8)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(stack, fTemp8), CastInst("float", BinopInst("<", LoadVarInst(stack, fTemp9), Float(0.0f))))), BinopInst("*", CastInst("float", BinopInst("*", BinopInst(">=", LoadVarInst(stack, fTemp9), Float(0.0f)), BinopInst("<=", LoadVarInst(stack, fTemp9), Float(1.0f)))), BinopInst("-", LoadVarInst(stack, fTemp9), BinopInst("*", Float(0.333333343f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp9)))))), BinopInst("*", Float(0.666666687f), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp9), Float(1.0f)))))), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fTemp0)))))
		StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(2.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(20.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(5000.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(500.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(-30.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(3))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l3)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(100.0f), BinopInst("/", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00999999978f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "int", iSlow4, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow5)))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", BinopInst("+", BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider3))), Float(-1.0f)), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow8, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst3), CastInst("float", LoadVarInst(struct, fHslider4)))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow9), Float(1.41421354f)), LoadVarInst(stack, fSlow8)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow8))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow11))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow9), Float(-1.41421354f)), LoadVarInst(stack, fSlow8)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow11))))
	DeclareVarInst(stack, "float", fSlow15, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow5)))))
	DeclareVarInst(stack, "float", fSlow16, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider5))))))))
	DeclareVarInst(stack, "float", fSlow17, CastInst("float", LoadVarInst(struct, fHslider6)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow0)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp0), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec3[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec3[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec3[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec3[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp2, Select2Inst(LoadVarInst(stack, iSlow4) Float(0.0f) LoadVarInst(stack, fTemp1)))
			DeclareVarInst(stack, "float", fTemp3, FunCallInst("fabsf", LoadVarInst(stack, fTemp2)))
			DeclareVarInst(stack, "float", fTemp4, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(stack, fTemp3)) LoadVarInst(stack, fSlow16) LoadVarInst(stack, fSlow15)))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(stack, fTemp4)), BinopInst("*", LoadVarInst(stack, fTemp3), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp4)))))
			StoreVarInst(struct, fRec5[Int32(0)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec4[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow7), FunCallInst("max_f", BinopInst("-", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec5[Int32(0)]))), LoadVarInst(stack, fSlow17)), Float(0.0f)))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fTemp2), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec4[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp6, FunCallInst("fabsf", FunCallInst("fabsf", LoadVarInst(stack, fTemp5))))
			DeclareVarInst(stack, "float", fTemp7, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp6)) LoadVarInst(stack, fSlow16) LoadVarInst(stack, fSlow15)))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp7)), BinopInst("*", LoadVarInst(stack, fTemp6), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp7)))))
			StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow7), FunCallInst("max_f", BinopInst("-", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec1[Int32(0)]))), LoadVarInst(stack, fSlow17)), Float(0.0f)))))
			StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec0[Int32(0)])))))))
			DeclareVarInst(stack, "float", fTemp8, Select2Inst(LoadVarInst(stack, iSlow4) LoadVarInst(stack, fTemp1) LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fTemp8)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(stack, fTemp8), CastInst("float", BinopInst("<", LoadVarInst(stack, fTemp9), Float(0.0f))))), BinopInst("*", CastInst("float", BinopInst("*", BinopInst(">=", LoadVarInst(stack, fTemp9), Float(0.0f)), BinopInst("<=", LoadVarInst(stack, fTemp9), Float(1.0f)))), BinopInst("-", LoadVarInst(stack, fTemp9), BinopInst("*", Float(0.333333343f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp9)))))), BinopInst("*", Float(0.666666687f), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp9), Float(1.0f)))))), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fTemp0)))))
			StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 112 bytes
Heap size = 116 bytes
Stack size in compute = 92 bytes

