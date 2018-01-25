======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("trumpet")
	AddMetaDeclareInst(fHslider4, "midi", "pitchwheel")
	AddHorizontalSlider("bend", fHslider4, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("freq", fHslider3, 300.0f, 50.0f, 2000.0f, 0.00999999978f)
	AddHorizontalSlider("gain", fHslider2, 1.0f, 0.0f, 1.0f, 0.00999999978f)
	AddButtonInst("gate"fButton0)
	AddMetaDeclareInst(fHslider1, "midi", "ctrl 64")
	AddHorizontalSlider("sustain", fHslider1, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "midi", "ctrl 1")
	AddHorizontalSlider("y", fHslider0, 1.0f, 0.0f, 1.0f, 0.00100000005f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
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
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[3])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(300.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(1.0f)))
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
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l1)], Float(0.0f))
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
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 10
Store = 0
Binop = 5
Numbers = 4
Declare = 8
Cast = 6
Select = 0
Loop = 0
Funcall = 1

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, fSlow1), Float(0.0f)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 70
Store = 20
Binop = 56
Numbers = 44
Declare = 13
Cast = 4
Select = 0
Loop = 1
Funcall = 4

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec2[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("*", Float(4000.0f), LoadVarInst(struct, fRec2[Int32(0)])), Float(50.0f)))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp0)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(stack, fTemp1), Float(1.0f)))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow1))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp3, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fVec0[Int32(1)])), LoadVarInst(stack, iSlow5)))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp3))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp3)), LoadVarInst(struct, fRec6[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp4, FunCallInst("max_f", Float(1.00000001e-07f), FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec6[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp4))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(stack, fTemp5), Float(-1.0f)))
		DeclareVarInst(stack, "int", iTemp7, BinopInst("<", LoadVarInst(stack, fTemp6), Float(0.0f)))
		StoreVarInst(struct, fRec4[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp7) LoadVarInst(stack, fTemp5) LoadVarInst(stack, fTemp6)))
		DeclareVarInst(stack, "float", fRec5, Select2Inst(LoadVarInst(stack, iTemp7) LoadVarInst(stack, fTemp5) BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("*", BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp4))), LoadVarInst(stack, fTemp6)))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fRec5)), Float(-1.0f))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp8))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp1)), LoadVarInst(stack, fTemp2)))), BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp1), Float(1.0f)), LoadVarInst(stack, fTemp0)), Float(1.0f)))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp1), Float(-1.0f)), LoadVarInst(stack, fTemp0)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp0))))))), LoadVarInst(stack, fTemp9))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("/", BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec0[Int32(1)])))), LoadVarInst(stack, fTemp9)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp10)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp10)))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
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
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(300.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(1.0f)))
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
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l1)], Float(0.0f))
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
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, fSlow1), Float(0.0f)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec2[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("*", Float(4000.0f), LoadVarInst(struct, fRec2[Int32(0)])), Float(50.0f)))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp0)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(stack, fTemp1), Float(1.0f)))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow1))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp3, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fVec0[Int32(1)])), LoadVarInst(stack, iSlow5)))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp3))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp3)), LoadVarInst(struct, fRec6[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp4, FunCallInst("max_f", Float(1.00000001e-07f), FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec6[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp4))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(stack, fTemp5), Float(-1.0f)))
			DeclareVarInst(stack, "int", iTemp7, BinopInst("<", LoadVarInst(stack, fTemp6), Float(0.0f)))
			StoreVarInst(struct, fRec4[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp7) LoadVarInst(stack, fTemp5) LoadVarInst(stack, fTemp6)))
			DeclareVarInst(stack, "float", fRec5, Select2Inst(LoadVarInst(stack, iTemp7) LoadVarInst(stack, fTemp5) BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("*", BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp4))), LoadVarInst(stack, fTemp6)))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fRec5)), Float(-1.0f))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp8))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp1)), LoadVarInst(stack, fTemp2)))), BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp1), Float(1.0f)), LoadVarInst(stack, fTemp0)), Float(1.0f)))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp1), Float(-1.0f)), LoadVarInst(stack, fTemp0)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp0))))))), LoadVarInst(stack, fTemp9))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("/", BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec0[Int32(1)])))), LoadVarInst(stack, fTemp9)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp10)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp10)))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 104 bytes
Heap size = 108 bytes
Stack size in compute = 40 bytes

