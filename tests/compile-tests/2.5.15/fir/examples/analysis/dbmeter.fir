======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenHorizontalBox("8 channels dB meter")
	OpenVerticalBox("0")
	AddMetaDeclareInst(fVbargraph0, "unit", "dB")
	AddVerticalBargraph("0x7fdcc1f64f80", fVbargraph0, -70.0f, 10.0f)
	CloseboxInst
	OpenVerticalBox("1")
	AddMetaDeclareInst(fVbargraph1, "unit", "dB")
	AddVerticalBargraph("0x7fdcc1f69660", fVbargraph1, -70.0f, 10.0f)
	CloseboxInst
	OpenVerticalBox("2")
	AddMetaDeclareInst(fVbargraph2, "unit", "dB")
	AddVerticalBargraph("0x7fdcc1f6dd40", fVbargraph2, -70.0f, 10.0f)
	CloseboxInst
	OpenVerticalBox("3")
	AddMetaDeclareInst(fVbargraph3, "unit", "dB")
	AddVerticalBargraph("0x7fdcc1f724d0", fVbargraph3, -70.0f, 10.0f)
	CloseboxInst
	OpenVerticalBox("4")
	AddMetaDeclareInst(fVbargraph4, "unit", "dB")
	AddVerticalBargraph("0x7fdcc1f76d10", fVbargraph4, -70.0f, 10.0f)
	CloseboxInst
	OpenVerticalBox("5")
	AddMetaDeclareInst(fVbargraph5, "unit", "dB")
	AddVerticalBargraph("0x7fdcc1f7b600", fVbargraph5, -70.0f, 10.0f)
	CloseboxInst
	OpenVerticalBox("6")
	AddMetaDeclareInst(fVbargraph6, "unit", "dB")
	AddVerticalBargraph("0x7fdcc1f7ffa0", fVbargraph6, -70.0f, 10.0f)
	CloseboxInst
	OpenVerticalBox("7")
	AddMetaDeclareInst(fVbargraph7, "unit", "dB")
	AddVerticalBargraph("0x7fdcc1f849f0", fVbargraph7, -70.0f, 10.0f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, "int", iConst1)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, "int", iConst2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, "int", iConst3)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, "int", iConst4)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph4)
	DeclareVarInst(struct, "int", iConst5)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph5)
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph6)
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph7)
	DeclareVarInst(struct, "int", iConst8)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(8))
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
	StoreVarInst(struct, fConst0, BinopInst("/", Float(80.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, iConst1, Int32(0))
	StoreVarInst(struct, iConst2, Int32(0))
	StoreVarInst(struct, iConst3, Int32(0))
	StoreVarInst(struct, iConst4, Int32(0))
	StoreVarInst(struct, iConst5, Int32(0))
	StoreVarInst(struct, iConst6, Int32(0))
	StoreVarInst(struct, iConst7, Int32(0))
	StoreVarInst(struct, iConst8, Int32(0))
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
Load = 16
Store = 0
Binop = 0
Numbers = 0
Declare = 16
Cast = 0
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input6, LoadVarInst(kFunArgs, inputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input7, LoadVarInst(kFunArgs, inputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 67
Store = 33
Binop = 18
Numbers = 42
Declare = 9
Cast = 24
Select = 0
Loop = 1
Funcall = 40

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp0))))))))
		StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[Int32(0)])))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst1)))
		DeclareVarInst(stack, "float", fTemp1, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec1[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp1))))))))
		StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[Int32(0)])))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst2)))
		DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec2[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp2))))))))
		StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec2[Int32(0)])))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst3)))
		DeclareVarInst(stack, "float", fTemp3, CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec3[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp3))))))))
		StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec3[Int32(0)])))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst4)))
		DeclareVarInst(stack, "float", fTemp4, CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec4[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp4))))))))
		StoreVarInst(struct, fVbargraph4, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec4[Int32(0)])))
		StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst5)))
		DeclareVarInst(stack, "float", fTemp5, CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec5[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp5))))))))
		StoreVarInst(struct, fVbargraph5, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec5[Int32(0)])))
		StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst6)))
		DeclareVarInst(stack, "float", fTemp6, CastInst("float", LoadVarInst(stack, input6[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec6[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp6))))))))
		StoreVarInst(struct, fVbargraph6, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec6[Int32(0)])))
		StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst7)))
		DeclareVarInst(stack, "float", fTemp7, CastInst("float", LoadVarInst(stack, input7[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec7[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp7))))))))
		StoreVarInst(struct, fVbargraph7, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec7[Int32(0)])))
		StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst8)))
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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, "int", iConst1)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, "int", iConst2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, "int", iConst3)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, "int", iConst4)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph4)
	DeclareVarInst(struct, "int", iConst5)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph5)
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph6)
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph7)
	DeclareVarInst(struct, "int", iConst8)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(80.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, iConst1, Int32(0))
	StoreVarInst(struct, iConst2, Int32(0))
	StoreVarInst(struct, iConst3, Int32(0))
	StoreVarInst(struct, iConst4, Int32(0))
	StoreVarInst(struct, iConst5, Int32(0))
	StoreVarInst(struct, iConst6, Int32(0))
	StoreVarInst(struct, iConst7, Int32(0))
	StoreVarInst(struct, iConst8, Int32(0))
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
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input6, LoadVarInst(kFunArgs, inputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input7, LoadVarInst(kFunArgs, inputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp0))))))))
			StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[Int32(0)])))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst1)))
			DeclareVarInst(stack, "float", fTemp1, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec1[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp1))))))))
			StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[Int32(0)])))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst2)))
			DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec2[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp2))))))))
			StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec2[Int32(0)])))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst3)))
			DeclareVarInst(stack, "float", fTemp3, CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec3[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp3))))))))
			StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec3[Int32(0)])))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst4)))
			DeclareVarInst(stack, "float", fTemp4, CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec4[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp4))))))))
			StoreVarInst(struct, fVbargraph4, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec4[Int32(0)])))
			StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst5)))
			DeclareVarInst(stack, "float", fTemp5, CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec5[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp5))))))))
			StoreVarInst(struct, fVbargraph5, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec5[Int32(0)])))
			StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst6)))
			DeclareVarInst(stack, "float", fTemp6, CastInst("float", LoadVarInst(stack, input6[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec6[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp6))))))))
			StoreVarInst(struct, fVbargraph6, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec6[Int32(0)])))
			StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst7)))
			DeclareVarInst(stack, "float", fTemp7, CastInst("float", LoadVarInst(stack, input7[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec7[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("min_f", Float(10.0f), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), FunCallInst("fabsf", LoadVarInst(stack, fTemp7))))))))
			StoreVarInst(struct, fVbargraph7, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec7[Int32(0)])))
			StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, iConst8)))
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

Heap size int = 36 bytes
Heap size int* = 0 bytes
Heap size real = 100 bytes
Heap size = 136 bytes
Stack size in compute = 128 bytes

