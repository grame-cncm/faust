======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("Bandfilter")
	AddMetaDeclareInst(fEntry1, "style", "knob")
	AddNumEntry"Q factor", fEntry1, 50.0f, 0.100000001f, 100.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddMetaDeclareInst(fEntry0, "unit", "Hz")
	AddNumEntry"freq", fEntry0, 1000.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("gain", fVslider0, 0.0f, -50.0f, 50.0f, 0.100000001f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
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
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry1)
	DeclareVarInst(struct, float, fRec0[3])
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
	StoreVarInst(struct, fConst0, BinopInst("/", Float(3.14159274f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry1, CastInst("FAUSTFLOAT", Double(50.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(3))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 21
Store = 0
Binop = 20
Numbers = 11
Declare = 11
Cast = 3
Select = 0
Loop = 0
Funcall = 3

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry0)))))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fEntry1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider0))))), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow0)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow6))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fSlow0)))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 19
Store = 5
Binop = 12
Numbers = 5
Declare = 2
Cast = 2
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)])))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec0[Int32(2)])), LoadVarInst(stack, fTemp0)))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp0), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec0[Int32(2)]))))))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry1)
	DeclareVarInst(struct, float, fRec0[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(3.14159274f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry1, CastInst("FAUSTFLOAT", Double(50.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(3))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fEntry0)))))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fEntry1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), BinopInst("-", Float(0.0f), CastInst("float", LoadVarInst(struct, fVslider0))))), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow0)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow6))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fSlow0)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)])))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec0[Int32(2)])), LoadVarInst(stack, fTemp0)))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp0), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec0[Int32(2)]))))))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 28 bytes
Heap size = 32 bytes
Stack size in compute = 52 bytes

