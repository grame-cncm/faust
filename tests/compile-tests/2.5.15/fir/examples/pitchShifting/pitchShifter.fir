======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("Pitch Shifter")
	AddHorizontalSlider("shift (semitones)", fHslider1, 0.0f, -12.0f, 12.0f, 0.100000001f)
	AddHorizontalSlider("window (samples)", fHslider0, 1000.0f, 50.0f, 10000.0f, 1.0f)
	AddHorizontalSlider("xfade (samples)", fHslider2, 10.0f, 1.0f, 10000.0f, 1.0f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[131072])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", fSamplingFreq)
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
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(10.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(131072))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
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
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 5
Store = 0
Binop = 2
Numbers = 3
Declare = 5
Cast = 3
Select = 0
Loop = 0
Funcall = 1

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 38
Store = 6
Binop = 26
Numbers = 10
Declare = 9
Cast = 4
Select = 0
Loop = 1
Funcall = 4

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], LoadVarInst(stack, fTemp0))
		StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), Float(1.0f)), LoadVarInst(stack, fSlow1))), LoadVarInst(stack, fSlow0)))
		DeclareVarInst(stack, "int", iTemp1, CastInst("int", LoadVarInst(struct, fRec0[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp2, FunCallInst("floorf", LoadVarInst(struct, fRec0[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec0[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp4, FunCallInst("min_f", BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec0[Int32(0)])), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec0[Int32(0)])))
		DeclareVarInst(stack, "int", iTemp6, CastInst("int", LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "float", fTemp7, FunCallInst("floorf", LoadVarInst(stack, fTemp5)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(65537), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp1)))), Int32(131071))]), BinopInst("+", LoadVarInst(stack, fTemp2), LoadVarInst(stack, fTemp3))), BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fTemp2)), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(65537), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp1), Int32(1))))), Int32(131071))]))), LoadVarInst(stack, fTemp4)), BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(65537), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp6)))), Int32(131071))]), BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp3)), LoadVarInst(stack, fSlow0))), BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fTemp7))), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(65537), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp6), Int32(1))))), Int32(131071))]))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp4))))))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[131072])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(131072))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
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
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(131071))], LoadVarInst(stack, fTemp0))
			StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("fmodf", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), Float(1.0f)), LoadVarInst(stack, fSlow1))), LoadVarInst(stack, fSlow0)))
			DeclareVarInst(stack, "int", iTemp1, CastInst("int", LoadVarInst(struct, fRec0[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp2, FunCallInst("floorf", LoadVarInst(struct, fRec0[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec0[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp4, FunCallInst("min_f", BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec0[Int32(0)])), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec0[Int32(0)])))
			DeclareVarInst(stack, "int", iTemp6, CastInst("int", LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "float", fTemp7, FunCallInst("floorf", LoadVarInst(stack, fTemp5)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(65537), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp1)))), Int32(131071))]), BinopInst("+", LoadVarInst(stack, fTemp2), LoadVarInst(stack, fTemp3))), BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fTemp2)), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(65537), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp1), Int32(1))))), Int32(131071))]))), LoadVarInst(stack, fTemp4)), BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(65537), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp6)))), Int32(131071))]), BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp3)), LoadVarInst(stack, fSlow0))), BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fTemp7))), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), FunCallInst("min_i", Int32(65537), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp6), Int32(1))))), Int32(131071))]))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp4))))))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 524308 bytes
Heap size = 524316 bytes
Stack size in compute = 28 bytes

