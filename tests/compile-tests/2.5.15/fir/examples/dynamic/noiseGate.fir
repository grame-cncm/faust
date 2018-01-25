======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "tooltip", "Reference:   http://en.wikipedia.org/wiki/Noise_gate")
	OpenVerticalBox("GATE")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked,   the gate has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	AddMetaDeclareInst(fHbargraph0, "1", "")
	AddMetaDeclareInst(fHbargraph0, "tooltip", "Current gain of the  gate in dB")
	AddMetaDeclareInst(fHbargraph0, "unit", "dB")
	AddHorizontalBargraph("Gate Gain", fHbargraph0, -50.0f, 10.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddMetaDeclareInst(fHslider2, "tooltip", "When   the signal level falls below the Threshold (expressed in dB), the signal is   muted")
	AddMetaDeclareInst(fHslider2, "unit", "dB")
	AddHorizontalSlider("Threshold", fHslider2, -30.0f, -120.0f, 0.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddMetaDeclareInst(fHslider0, "scale", "log")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "tooltip", "Time constant in MICROseconds (1/e smoothing time) for the gate  gain to go (exponentially) from 0 (muted) to 1 (unmuted)")
	AddMetaDeclareInst(fHslider0, "unit", "us")
	AddHorizontalSlider("Attack", fHslider0, 10.0f, 10.0f, 10000.0f, 1.0f)
	AddMetaDeclareInst(fHslider3, "3", "")
	AddMetaDeclareInst(fHslider3, "scale", "log")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddMetaDeclareInst(fHslider3, "tooltip", "Time in ms to keep the gate open (no muting) after the signal  level falls below the Threshold")
	AddMetaDeclareInst(fHslider3, "unit", "ms")
	AddHorizontalSlider("Hold", fHslider3, 200.0f, 1.0f, 1000.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "4", "")
	AddMetaDeclareInst(fHslider1, "scale", "log")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "tooltip", "Time constant in ms (1/e smoothing time) for the gain to go  (exponentially) from 1 (unmuted) to 0 (muted)")
	AddMetaDeclareInst(fHslider1, "unit", "ms")
	AddHorizontalSlider("Release", fHslider1, 100.0f, 1.0f, 1000.0f, 1.0f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "log10f", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, int, iRec4[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, int, iVec1[2])
	DeclareVarInst(struct, int, iRec9[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[2])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(-30.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(200.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
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
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec4[LoadVarInst(loop, l2)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec1[LoadVarInst(loop, l6)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec9[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 21
Store = 0
Binop = 12
Numbers = 9
Declare = 13
Cast = 7
Select = 0
Loop = 0
Funcall = 8

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(9.99999997e-07f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), FunCallInst("min_f", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fSlow2))))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", BinopInst("*", LoadVarInst(struct, fConst0), FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3)))))))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow8, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow2)))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 79
Store = 24
Binop = 33
Numbers = 31
Declare = 14
Cast = 13
Select = 0
Loop = 1
Funcall = 12

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
		DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp3, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp2)))
		DeclareVarInst(stack, "float", fTemp4, FunCallInst("fabsf", LoadVarInst(stack, fTemp3)))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("fabsf", BinopInst("+", FunCallInst("fabsf", LoadVarInst(stack, fTemp1)), LoadVarInst(stack, fTemp4))))))
		DeclareVarInst(stack, "float", fRec2, LoadVarInst(struct, fRec3[Int32(0)]))
		DeclareVarInst(stack, "int", iTemp5, BinopInst(">", LoadVarInst(stack, fRec2), LoadVarInst(stack, fSlow5)))
		StoreVarInst(struct, iVec0[Int32(0)], LoadVarInst(stack, iTemp5))
		StoreVarInst(struct, iRec4[Int32(0)], FunCallInst("max_i", CastInst("int", BinopInst("*", LoadVarInst(stack, iSlow6), BinopInst("<", LoadVarInst(stack, iTemp5), LoadVarInst(struct, iVec0[Int32(1)])))), CastInst("int", BinopInst("+", LoadVarInst(struct, iRec4[Int32(1)]), Int32(-1)))))
		DeclareVarInst(stack, "float", fTemp6, FunCallInst("fabsf", FunCallInst("max_f", CastInst("float", LoadVarInst(stack, iTemp5)), CastInst("float", BinopInst(">", LoadVarInst(struct, iRec4[Int32(0)]), Int32(0))))))
		DeclareVarInst(stack, "float", fTemp7, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp6)) LoadVarInst(stack, fSlow8) LoadVarInst(stack, fSlow7)))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp7)), BinopInst("*", LoadVarInst(stack, fTemp6), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp7)))))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec0[Int32(0)])))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("fabsf", BinopInst("+", LoadVarInst(stack, fTemp4), FunCallInst("fabsf", LoadVarInst(stack, fTemp1)))))))
		DeclareVarInst(stack, "float", fRec7, LoadVarInst(struct, fRec8[Int32(0)]))
		DeclareVarInst(stack, "int", iTemp8, BinopInst(">", LoadVarInst(stack, fRec7), LoadVarInst(stack, fSlow5)))
		StoreVarInst(struct, iVec1[Int32(0)], LoadVarInst(stack, iTemp8))
		StoreVarInst(struct, iRec9[Int32(0)], FunCallInst("max_i", CastInst("int", BinopInst("*", LoadVarInst(stack, iSlow6), BinopInst("<", LoadVarInst(stack, iTemp8), LoadVarInst(struct, iVec1[Int32(1)])))), CastInst("int", BinopInst("+", LoadVarInst(struct, iRec9[Int32(1)]), Int32(-1)))))
		DeclareVarInst(stack, "float", fTemp9, FunCallInst("fabsf", FunCallInst("max_f", CastInst("float", LoadVarInst(stack, iTemp8)), CastInst("float", BinopInst(">", LoadVarInst(struct, iRec9[Int32(0)]), Int32(0))))))
		DeclareVarInst(stack, "float", fTemp10, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(stack, fTemp9)) LoadVarInst(stack, fSlow8) LoadVarInst(stack, fSlow7)))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(stack, fTemp9), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp10)))))
		StoreVarInst(struct, fRec5[Int32(0)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(struct, fRec5[Int32(0)])))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp2) BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(struct, fRec5[Int32(0)])))))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, iRec4[Int32(1)], LoadVarInst(struct, iRec4[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, iVec1[Int32(1)], LoadVarInst(struct, iVec1[Int32(0)]))
		StoreVarInst(struct, iRec9[Int32(1)], LoadVarInst(struct, iRec9[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, int, iRec4[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, int, iVec1[2])
	DeclareVarInst(struct, int, iRec9[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(-30.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(200.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
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
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec4[LoadVarInst(loop, l2)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec1[LoadVarInst(loop, l6)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec9[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l9)], Float(0.0f))
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
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(9.99999997e-07f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), FunCallInst("min_f", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fSlow2))))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", BinopInst("*", LoadVarInst(struct, fConst0), FunCallInst("max_f", LoadVarInst(struct, fConst2), BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3)))))))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow8, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow2)))))
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
			DeclareVarInst(stack, "float", fTemp4, FunCallInst("fabsf", LoadVarInst(stack, fTemp3)))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("fabsf", BinopInst("+", FunCallInst("fabsf", LoadVarInst(stack, fTemp1)), LoadVarInst(stack, fTemp4))))))
			DeclareVarInst(stack, "float", fRec2, LoadVarInst(struct, fRec3[Int32(0)]))
			DeclareVarInst(stack, "int", iTemp5, BinopInst(">", LoadVarInst(stack, fRec2), LoadVarInst(stack, fSlow5)))
			StoreVarInst(struct, iVec0[Int32(0)], LoadVarInst(stack, iTemp5))
			StoreVarInst(struct, iRec4[Int32(0)], FunCallInst("max_i", CastInst("int", BinopInst("*", LoadVarInst(stack, iSlow6), BinopInst("<", LoadVarInst(stack, iTemp5), LoadVarInst(struct, iVec0[Int32(1)])))), CastInst("int", BinopInst("+", LoadVarInst(struct, iRec4[Int32(1)]), Int32(-1)))))
			DeclareVarInst(stack, "float", fTemp6, FunCallInst("fabsf", FunCallInst("max_f", CastInst("float", LoadVarInst(stack, iTemp5)), CastInst("float", BinopInst(">", LoadVarInst(struct, iRec4[Int32(0)]), Int32(0))))))
			DeclareVarInst(stack, "float", fTemp7, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp6)) LoadVarInst(stack, fSlow8) LoadVarInst(stack, fSlow7)))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp7)), BinopInst("*", LoadVarInst(stack, fTemp6), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp7)))))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", LoadVarInst(struct, fRec0[Int32(0)])))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("fabsf", BinopInst("+", LoadVarInst(stack, fTemp4), FunCallInst("fabsf", LoadVarInst(stack, fTemp1)))))))
			DeclareVarInst(stack, "float", fRec7, LoadVarInst(struct, fRec8[Int32(0)]))
			DeclareVarInst(stack, "int", iTemp8, BinopInst(">", LoadVarInst(stack, fRec7), LoadVarInst(stack, fSlow5)))
			StoreVarInst(struct, iVec1[Int32(0)], LoadVarInst(stack, iTemp8))
			StoreVarInst(struct, iRec9[Int32(0)], FunCallInst("max_i", CastInst("int", BinopInst("*", LoadVarInst(stack, iSlow6), BinopInst("<", LoadVarInst(stack, iTemp8), LoadVarInst(struct, iVec1[Int32(1)])))), CastInst("int", BinopInst("+", LoadVarInst(struct, iRec9[Int32(1)]), Int32(-1)))))
			DeclareVarInst(stack, "float", fTemp9, FunCallInst("fabsf", FunCallInst("max_f", CastInst("float", LoadVarInst(stack, iTemp8)), CastInst("float", BinopInst(">", LoadVarInst(struct, iRec9[Int32(0)]), Int32(0))))))
			DeclareVarInst(stack, "float", fTemp10, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(stack, fTemp9)) LoadVarInst(stack, fSlow8) LoadVarInst(stack, fSlow7)))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(stack, fTemp9), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp10)))))
			StoreVarInst(struct, fRec5[Int32(0)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(struct, fRec5[Int32(0)])))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp2) BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(struct, fRec5[Int32(0)])))))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, iRec4[Int32(1)], LoadVarInst(struct, iRec4[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, iVec1[Int32(1)], LoadVarInst(struct, iVec1[Int32(0)]))
			StoreVarInst(struct, iRec9[Int32(1)], LoadVarInst(struct, iRec9[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 32 bytes
Heap size real = 84 bytes
Heap size = 120 bytes
Stack size in compute = 68 bytes

