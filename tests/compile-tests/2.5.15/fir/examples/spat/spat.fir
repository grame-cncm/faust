======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("Spatializer 1x8")
	AddHorizontalSlider("angle", fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddHorizontalSlider("distance", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(8))
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
			Case 1
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 2
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 3
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 4
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 5
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 6
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 7
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
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
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
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 36
Store = 0
Binop = 57
Numbers = 57
Declare = 20
Cast = 2
Select = 0
Loop = 0
Funcall = 32

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("+", LoadVarInst(stack, fSlow0), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.5f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.375f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.25f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.125f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.0f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(0.875f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(0.75f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(0.625f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 52
Store = 25
Binop = 26
Numbers = 26
Declare = 2
Cast = 9
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec0[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec1[Int32(1)]))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec2[Int32(1)]))))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec3[Int32(1)]))))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec4[Int32(1)]))))
		StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec5[Int32(1)]))))
		StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow9), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec6[Int32(1)]))))
		StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec7[Int32(1)]))))
		StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
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
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("+", LoadVarInst(stack, fSlow0), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.5f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.375f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.25f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.125f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.0f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(0.875f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(0.75f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(4.99999987e-05f), BinopInst("*", LoadVarInst(stack, fSlow1), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow2), Float(0.625f)), Float(1.0f)), Float(-0.5f))), LoadVarInst(stack, fSlow0)))))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec0[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec1[Int32(1)]))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec2[Int32(1)]))))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec3[Int32(1)]))))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec4[Int32(1)]))))
			StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec5[Int32(1)]))))
			StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow9), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec6[Int32(1)]))))
			StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", Float(0.999899983f), LoadVarInst(struct, fRec7[Int32(1)]))))
			StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 72 bytes
Heap size = 76 bytes
Stack size in compute = 116 bytes

