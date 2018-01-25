======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "Sine oscillator based   on 2D vector rotation")
	OpenVerticalBox("SINE WAVE OSCILLATOR oscrs")
	AddMetaDeclareInst(fHslider0, "1", "")
	AddMetaDeclareInst(fHslider0, "tooltip", "Sawtooth waveform   amplitude")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Amplitude", fHslider0, -20.0f, -120.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)")
	AddMetaDeclareInst(fHslider1, "unit", "PK")
	AddHorizontalSlider("Frequency", fHslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider2, "3", "")
	AddMetaDeclareInst(fHslider2, "scale", "log")
	AddMetaDeclareInst(fHslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds")
	AddMetaDeclareInst(fHslider2, "unit", "sec")
	AddHorizontalSlider("Portamento", fHslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec2[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(-20.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l0)], Int32(0))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 6
Store = 0
Binop = 9
Numbers = 9
Declare = 4
Cast = 3
Select = 0
Loop = 0
Funcall = 3

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider2))))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(440.0f), BinopInst("*", FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", CastInst("float", LoadVarInst(struct, fHslider1)), Float(-49.0f)))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 29
Store = 12
Binop = 17
Numbers = 16
Declare = 4
Cast = 2
Select = 0
Loop = 1
Funcall = 2

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec3[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec3[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp1, FunCallInst("sinf", LoadVarInst(stack, fTemp0)))
		DeclareVarInst(stack, "float", fTemp2, FunCallInst("cosf", LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp2))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp2)), BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp1)))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec1[Int32(0)]))))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec2[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(-20.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l0)], Int32(0))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider2))))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(440.0f), BinopInst("*", FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", CastInst("float", LoadVarInst(struct, fHslider1)), Float(-49.0f)))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec3[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec3[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp1, FunCallInst("sinf", LoadVarInst(stack, fTemp0)))
			DeclareVarInst(stack, "float", fTemp2, FunCallInst("cosf", LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp2))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp2)), BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp1)))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec1[Int32(0)]))))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 56 bytes
Heap size = 68 bytes
Stack size in compute = 20 bytes

