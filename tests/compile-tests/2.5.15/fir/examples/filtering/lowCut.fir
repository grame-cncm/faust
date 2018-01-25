======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("low-freq shelving cut")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "unit", "dB")
	AddHorizontalSlider("attenuation", fHslider1, 0.0f, -96.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider0, 100.0f, 20.0f, 5000.0f, 1.0f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
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
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
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
Load = 22
Store = 0
Binop = 23
Numbers = 15
Declare = 13
Cast = 2
Select = 0
Loop = 0
Funcall = 4

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider1))))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow3))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow0)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(stack, fSlow5), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow3)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow1)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), Float(1.41421354f))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), Float(-1.41421354f))), Float(1.0f)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 19
Store = 5
Binop = 13
Numbers = 5
Declare = 1
Cast = 2
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec0[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec0[Int32(1)]))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec0[Int32(2)]))))))
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
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec0[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(3.14159274f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
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
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider1))))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow3))), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow0)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(stack, fSlow5), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow3)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow1)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), Float(1.41421354f))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow0), Float(-1.41421354f))), Float(1.0f)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec0[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec0[Int32(1)]))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec0[Int32(2)]))))))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 24 bytes
Heap size = 28 bytes
Stack size in compute = 60 bytes

