======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("stereo echo")
	OpenVerticalBox("echo  1000")
	AddHorizontalSlider("feedback", fHslider0, 0.0f, 0.0f, 100.0f, 0.100000001f)
	AddHorizontalSlider("millisecond", fHslider1, 0.0f, 0.0f, 1000.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec0[131072])
	DeclareVarInst(struct, float, fRec1[131072])
	DeclareVarInst(struct, float, fRec2[131072])
	DeclareVarInst(struct, float, fRec3[131072])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(4))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(4))
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
	StoreVarInst(struct, fConst0, BinopInst("*", Float(0.00100000005f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(131072))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(131072))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(131072))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(131072))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 11
Store = 0
Binop = 4
Numbers = 5
Declare = 10
Cast = 3
Select = 0
Loop = 0
Funcall = 2

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "int", iSlow1, BinopInst("+", FunCallInst("min_i", Int32(65536), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider1)))), Int32(-1)))), Int32(1)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 28
Store = 10
Binop = 15
Numbers = 7
Declare = 1
Cast = 8
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow1)), Int32(131071))]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(0)), Int32(131071))])))
		StoreVarInst(struct, fRec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow1)), Int32(131071))]))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(0)), Int32(131071))])))
		StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow1)), Int32(131071))]))))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(0)), Int32(131071))])))
		StoreVarInst(struct, fRec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow1)), Int32(131071))]))))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(0)), Int32(131071))])))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec0[131072])
	DeclareVarInst(struct, float, fRec1[131072])
	DeclareVarInst(struct, float, fRec2[131072])
	DeclareVarInst(struct, float, fRec3[131072])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("*", Float(0.00100000005f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(131072))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(131072))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(131072))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(131072))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "int", iSlow1, BinopInst("+", FunCallInst("min_i", Int32(65536), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider1)))), Int32(-1)))), Int32(1)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow1)), Int32(131071))]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(0)), Int32(131071))])))
			StoreVarInst(struct, fRec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow1)), Int32(131071))]))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(0)), Int32(131071))])))
			StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow1)), Int32(131071))]))))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(0)), Int32(131071))])))
			StoreVarInst(struct, fRec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow1)), Int32(131071))]))))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(0)), Int32(131071))])))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 2097164 bytes
Heap size = 2097172 bytes
Stack size in compute = 72 bytes

