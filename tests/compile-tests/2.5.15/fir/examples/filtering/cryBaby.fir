======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/vegf.html")
	OpenHorizontalBox("CRYBABY")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the wah   pedal has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	AddMetaDeclareInst(fHslider0, "1", "")
	AddMetaDeclareInst(fHslider0, "tooltip", "wah pedal angle between   0 (rocked back) and 1 (rocked forward)")
	AddHorizontalSlider("Wah parameter", fHslider0, 0.800000012f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec3[2])
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
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1413.71667f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(2827.43335f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.80000000000000004f)))
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
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 13
Store = 0
Binop = 14
Numbers = 13
Declare = 9
Cast = 3
Select = 0
Loop = 0
Funcall = 5

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(9.99999975e-05f), FunCallInst("powf", Float(4.0f), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(2.29999995f), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("/", LoadVarInst(stack, fSlow3), FunCallInst("powf", Float(2.0f), BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1))), Float(1.0f)))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00100000005f), BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow3))))))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(0.00100000005f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow4))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 27
Store = 11
Binop = 14
Numbers = 15
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
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec1[Int32(1)]))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec2[Int32(1)]))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)), LoadVarInst(struct, fRec1[Int32(0)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fRec0[Int32(2)])))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("-", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec0[Int32(1)])))))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec0[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1413.71667f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(2827.43335f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.80000000000000004f)))
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
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
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
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(9.99999975e-05f), FunCallInst("powf", Float(4.0f), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(2.29999995f), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("/", LoadVarInst(stack, fSlow3), FunCallInst("powf", Float(2.0f), BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1))), Float(1.0f)))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00100000005f), BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fSlow4), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow3))))))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(0.00100000005f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow4))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec1[Int32(1)]))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec2[Int32(1)]))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)), LoadVarInst(struct, fRec1[Int32(0)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fRec0[Int32(2)])))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("-", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec0[Int32(1)])))))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 56 bytes
Heap size = 60 bytes
Stack size in compute = 44 bytes

