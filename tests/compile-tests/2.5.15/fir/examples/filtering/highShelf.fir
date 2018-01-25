======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("highShelf")
	AddHorizontalSlider("Freq", fHslider1, 1000.0f, 100.0f, 10000.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Gain", fHslider0, 0.0f, -10.0f, 10.0f, 0.100000001f)
	AddHorizontalSlider("Q", fHslider2, 1.0f, 0.00999999978f, 100.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
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
	StoreVarInst(struct, fConst0, BinopInst("/", Float(6.28318548f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
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
Load = 32
Store = 0
Binop = 30
Numbers = 16
Declare = 15
Cast = 3
Select = 0
Loop = 0
Funcall = 6

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0250000004f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst0), FunCallInst("max_f", Float(0.0f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", BinopInst("*", FunCallInst("sqrtf", LoadVarInst(stack, fSlow0)), FunCallInst("sinf", LoadVarInst(stack, fSlow1))), FunCallInst("max_f", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("cosf", LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow0), Float(-1.0f)), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2)), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow4)))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("+", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow6)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fSlow4), LoadVarInst(stack, fSlow2)))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow0), Float(1.0f)), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fSlow9)))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow0))), BinopInst("+", BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow9)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)))))
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
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec0[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec0[Int32(1)]))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec0[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec0[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec0[Int32(2)]))))))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec0[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(6.28318548f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
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
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0250000004f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst0), FunCallInst("max_f", Float(0.0f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", BinopInst("*", FunCallInst("sqrtf", LoadVarInst(stack, fSlow0)), FunCallInst("sinf", LoadVarInst(stack, fSlow1))), FunCallInst("max_f", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("cosf", LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow0), Float(-1.0f)), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2)), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow4)))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("+", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow6)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fSlow4), LoadVarInst(stack, fSlow2)))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow0), Float(1.0f)), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fSlow9)))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow0))), BinopInst("+", BinopInst("+", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow9)), Float(-1.0f))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec0[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec0[Int32(1)]))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec0[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec0[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec0[Int32(2)]))))))
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
Stack size in compute = 68 bytes

