======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("smoothDelay")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "unit", "ms")
	AddHorizontalSlider("delay", fHslider0, 0.0f, 0.0f, 5000.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("feedback", fHslider2, 0.0f, 0.0f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "unit", "ms")
	AddHorizontalSlider("interpolation", fHslider1, 10.0f, 1.0f, 100.0f, 0.100000001f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[1048576])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fVec1[1048576])
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
	StoreVarInst(struct, fConst1, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l2)], Float(0.0f))
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
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(1048576))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(1048576))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 10
Store = 0
Binop = 4
Numbers = 2
Declare = 8
Cast = 3
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("/", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fHslider2))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 60
Store = 18
Binop = 33
Numbers = 33
Declare = 7
Cast = 6
Select = 0
Loop = 1
Funcall = 6

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, Select2Inst(BinopInst("!=", LoadVarInst(struct, fRec1[Int32(1)]), Float(0.0f)) Select2Inst(BinopInst("&", BinopInst(">", LoadVarInst(struct, fRec2[Int32(1)]), Float(0.0f)), BinopInst("<", LoadVarInst(struct, fRec2[Int32(1)]), Float(1.0f))) LoadVarInst(struct, fRec1[Int32(1)]) Float(0.0f)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(struct, fRec2[Int32(1)]), Float(0.0f)), BinopInst("!=", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec3[Int32(1)]))) LoadVarInst(stack, fSlow1) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(struct, fRec2[Int32(1)]), Float(1.0f)), BinopInst("!=", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec4[Int32(1)]))) LoadVarInst(stack, fSlow2) Float(0.0f)))))
		StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fTemp0))
		StoreVarInst(struct, fRec2[Int32(0)], FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp0)))))
		StoreVarInst(struct, fRec3[Int32(0)], Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(struct, fRec2[Int32(1)]), Float(1.0f)), BinopInst("!=", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fSlow0))) LoadVarInst(stack, fSlow0) LoadVarInst(struct, fRec3[Int32(1)])))
		StoreVarInst(struct, fRec4[Int32(0)], Select2Inst(BinopInst("&", BinopInst("<=", LoadVarInst(struct, fRec2[Int32(1)]), Float(0.0f)), BinopInst("!=", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(stack, fSlow0))) LoadVarInst(stack, fSlow0) LoadVarInst(struct, fRec4[Int32(1)])))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec2[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec0[Int32(1)]))))
		StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(1048575))], LoadVarInst(stack, fTemp2))
		DeclareVarInst(stack, "int", iTemp3, CastInst("int", FunCallInst("min_f", Float(524288.0f), FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec3[Int32(0)])))))
		DeclareVarInst(stack, "int", iTemp4, CastInst("int", FunCallInst("min_f", Float(524288.0f), FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec4[Int32(0)])))))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp3)), Int32(1048575))])), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp4)), Int32(1048575))]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec5[Int32(1)]))))
		StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(1048575))], LoadVarInst(stack, fTemp5))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp3)), Int32(1048575))])), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp4)), Int32(1048575))]))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec5[Int32(0)])))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[1048576])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fVec1[1048576])
	DeclareVarInst(struct, float, fRec5[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l2)], Float(0.0f))
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
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(1048576))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(1048576))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("/", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fHslider2))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, Select2Inst(BinopInst("!=", LoadVarInst(struct, fRec1[Int32(1)]), Float(0.0f)) Select2Inst(BinopInst("&", BinopInst(">", LoadVarInst(struct, fRec2[Int32(1)]), Float(0.0f)), BinopInst("<", LoadVarInst(struct, fRec2[Int32(1)]), Float(1.0f))) LoadVarInst(struct, fRec1[Int32(1)]) Float(0.0f)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(struct, fRec2[Int32(1)]), Float(0.0f)), BinopInst("!=", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec3[Int32(1)]))) LoadVarInst(stack, fSlow1) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(struct, fRec2[Int32(1)]), Float(1.0f)), BinopInst("!=", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec4[Int32(1)]))) LoadVarInst(stack, fSlow2) Float(0.0f)))))
			StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fTemp0))
			StoreVarInst(struct, fRec2[Int32(0)], FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp0)))))
			StoreVarInst(struct, fRec3[Int32(0)], Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(struct, fRec2[Int32(1)]), Float(1.0f)), BinopInst("!=", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fSlow0))) LoadVarInst(stack, fSlow0) LoadVarInst(struct, fRec3[Int32(1)])))
			StoreVarInst(struct, fRec4[Int32(0)], Select2Inst(BinopInst("&", BinopInst("<=", LoadVarInst(struct, fRec2[Int32(1)]), Float(0.0f)), BinopInst("!=", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(stack, fSlow0))) LoadVarInst(stack, fSlow0) LoadVarInst(struct, fRec4[Int32(1)])))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec2[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec0[Int32(1)]))))
			StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(1048575))], LoadVarInst(stack, fTemp2))
			DeclareVarInst(stack, "int", iTemp3, CastInst("int", FunCallInst("min_f", Float(524288.0f), FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec3[Int32(0)])))))
			DeclareVarInst(stack, "int", iTemp4, CastInst("int", FunCallInst("min_f", Float(524288.0f), FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec4[Int32(0)])))))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp3)), Int32(1048575))])), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp4)), Int32(1048575))]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec5[Int32(1)]))))
			StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(1048575))], LoadVarInst(stack, fTemp5))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp3)), Int32(1048575))])), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp4)), Int32(1048575))]))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec5[Int32(0)])))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 8388680 bytes
Heap size = 8388688 bytes
Stack size in compute = 48 bytes

