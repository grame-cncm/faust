======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("spectralTilt")
	AddMetaDeclareInst(fHslider2, "1", "")
	AddHorizontalSlider("Slope of Spectral Tilt across Band", fHslider2, -0.5f, -1.0f, 1.0f, 0.00100000005f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("Band Start Frequency", fHslider0, 100.0f, 20.0f, 10000.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "3", "")
	AddMetaDeclareInst(fHslider1, "unit", "Hz")
	AddHorizontalSlider("Band Width", fHslider1, 5000.0f, 100.0f, 10000.0f, 1.0f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec0[2])
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
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(0.5f), LoadVarInst(struct, fConst0)))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(5000.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(-0.5f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 56
Store = 0
Binop = 39
Numbers = 11
Declare = 25
Cast = 3
Select = 0
Loop = 0
Funcall = 7

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow0), CastInst("float", LoadVarInst(struct, fHslider1))), LoadVarInst(stack, fSlow0)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), FunCallInst("powf", LoadVarInst(stack, fSlow1), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow3)))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(6.28318548f), BinopInst("/", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2)), LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fConst2)), LoadVarInst(stack, fSlow8))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", Float(6.28318548f), BinopInst("/", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow4)), LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fConst2)))
	DeclareVarInst(stack, "float", fSlow13, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), FunCallInst("powf", LoadVarInst(stack, fSlow1), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))))))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("/", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(6.28318548f), LoadVarInst(stack, fSlow0)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("+", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow15)))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fConst2)), LoadVarInst(stack, fSlow16))))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", Float(6.28318548f), BinopInst("/", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow13)), LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("+", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow19)))
	DeclareVarInst(stack, "float", fSlow21, BinopInst("-", LoadVarInst(stack, fSlow19), LoadVarInst(struct, fConst2)))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("/", BinopInst("*", LoadVarInst(stack, fSlow6), BinopInst("+", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow11))), LoadVarInst(stack, fSlow13)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 28
Store = 10
Binop = 16
Numbers = 10
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
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fTemp0))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow18), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fTemp0)), BinopInst("*", LoadVarInst(stack, fSlow21), LoadVarInst(struct, fVec0[Int32(1)]))))))
		StoreVarInst(struct, fVec1[Int32(0)], BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec1[Int32(0)])))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fVec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec1[Int32(0)]))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec0[Int32(0)]))))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(0.5f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(5000.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(-0.5f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow0), CastInst("float", LoadVarInst(struct, fHslider1))), LoadVarInst(stack, fSlow0)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), FunCallInst("powf", LoadVarInst(stack, fSlow1), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow3)))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(6.28318548f), BinopInst("/", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow2)), LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fConst2)), LoadVarInst(stack, fSlow8))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", Float(6.28318548f), BinopInst("/", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow4)), LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fConst2)))
	DeclareVarInst(stack, "float", fSlow13, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), FunCallInst("powf", LoadVarInst(stack, fSlow1), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))))))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("/", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(6.28318548f), LoadVarInst(stack, fSlow0)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("+", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow15)))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fConst2)), LoadVarInst(stack, fSlow16))))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", Float(6.28318548f), BinopInst("/", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fSlow13)), LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("+", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow19)))
	DeclareVarInst(stack, "float", fSlow21, BinopInst("-", LoadVarInst(stack, fSlow19), LoadVarInst(struct, fConst2)))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("/", BinopInst("*", LoadVarInst(stack, fSlow6), BinopInst("+", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow11))), LoadVarInst(stack, fSlow13)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fTemp0))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow18), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fTemp0)), BinopInst("*", LoadVarInst(stack, fSlow21), LoadVarInst(struct, fVec0[Int32(1)]))))))
			StoreVarInst(struct, fVec1[Int32(0)], BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec1[Int32(0)])))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fVec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec1[Int32(0)]))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec0[Int32(0)]))))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 56 bytes
Heap size = 60 bytes
Stack size in compute = 108 bytes

