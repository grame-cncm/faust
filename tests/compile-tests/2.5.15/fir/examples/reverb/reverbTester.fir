======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("reverbTester")
	AddMetaDeclareInst(0, "1", "")
	OpenVerticalBox("Input Config")
	AddMetaDeclareInst(fCheckbox0, "1", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the stereo external audio inputs are   disabled (good for hearing the impulse response or pink-noise response alone)")
	AddCheckButtonInst("Mute Ext Inputs"fCheckbox0)
	AddMetaDeclareInst(fCheckbox1, "2", "")
	AddMetaDeclareInst(fCheckbox1, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting   the EQ sections)")
	AddCheckButtonInst("Pink Noise"fCheckbox1)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("Impulse Selection")
	AddMetaDeclareInst(fButton1, "1", "")
	AddMetaDeclareInst(fButton1, "tooltip", "Send impulse into LEFT channel")
	AddButtonInst("Left"fButton1)
	AddMetaDeclareInst(fButton0, "2", "")
	AddMetaDeclareInst(fButton0, "tooltip", "Send impulse into LEFT and RIGHT channels")
	AddButtonInst("Center"fButton0)
	AddMetaDeclareInst(fButton2, "3", "")
	AddMetaDeclareInst(fButton2, "tooltip", "Send impulse into RIGHT channel")
	AddButtonInst("Right"fButton2)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton1)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, int, iRec1[2])
	DeclareVarInst(struct, float, fRec0[4])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton2)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(5))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getInputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(0))
					EndBlock
				EndCase
			Case 1
				BlockInst 
					StoreVarInst(stack, rate, Int32(0))
					EndBlock
				EndCase
			Case 2
				BlockInst 
					StoreVarInst(stack, rate, Int32(0))
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
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton2, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec1[LoadVarInst(loop, l2)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(4))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 12
Store = 0
Binop = 2
Numbers = 2
Declare = 12
Cast = 5
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fButton1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.100000001f), CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fButton2)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 40
Store = 14
Binop = 35
Numbers = 27
Declare = 4
Cast = 9
Select = 0
Loop = 2
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow0))
		DeclareVarInst(stack, "int", iTemp0, BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec0[Int32(1)])), Float(0.0f)))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow2))
		StoreVarInst(struct, iRec1[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec1[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(0.522189379f), LoadVarInst(struct, fRec0[Int32(3)])), BinopInst("+", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec1[Int32(0)]))), BinopInst("*", Float(2.49495602f), LoadVarInst(struct, fRec0[Int32(1)])))), BinopInst("*", Float(2.0172658f), LoadVarInst(struct, fRec0[Int32(2)]))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0499220341f), LoadVarInst(struct, fRec0[Int32(0)])), BinopInst("*", Float(0.0506126992f), LoadVarInst(struct, fRec0[Int32(2)]))), BinopInst("+", BinopInst("*", Float(0.0959935337f), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", Float(0.00440878607f), LoadVarInst(struct, fRec0[Int32(3)]))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp0)), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)]))), CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f))))), LoadVarInst(stack, fTemp1))))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fSlow4))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fVec2[Int32(1)])), Float(0.0f))), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)]))), BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(stack, fTemp1))))))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, iRec1[Int32(1)], LoadVarInst(struct, iRec1[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j0, Int32(3))
			BinopInst(">", LoadVarInst(loop, j0), Int32(0))
			StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec0[LoadVarInst(loop, j0)], LoadVarInst(struct, fRec0[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton1)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, int, iRec1[2])
	DeclareVarInst(struct, float, fRec0[4])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton2)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton2, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec1[LoadVarInst(loop, l2)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(4))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l4)], Float(0.0f))
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
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fButton1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.100000001f), CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fButton2)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow0))
			DeclareVarInst(stack, "int", iTemp0, BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec0[Int32(1)])), Float(0.0f)))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow2))
			StoreVarInst(struct, iRec1[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec1[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(0.522189379f), LoadVarInst(struct, fRec0[Int32(3)])), BinopInst("+", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec1[Int32(0)]))), BinopInst("*", Float(2.49495602f), LoadVarInst(struct, fRec0[Int32(1)])))), BinopInst("*", Float(2.0172658f), LoadVarInst(struct, fRec0[Int32(2)]))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0499220341f), LoadVarInst(struct, fRec0[Int32(0)])), BinopInst("*", Float(0.0506126992f), LoadVarInst(struct, fRec0[Int32(2)]))), BinopInst("+", BinopInst("*", Float(0.0959935337f), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", Float(0.00440878607f), LoadVarInst(struct, fRec0[Int32(3)]))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp0)), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)]))), CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f))))), LoadVarInst(stack, fTemp1))))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fSlow4))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fVec2[Int32(1)])), Float(0.0f))), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)]))), BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(stack, fTemp1))))))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, iRec1[Int32(1)], LoadVarInst(struct, iRec1[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j0, Int32(3))
				BinopInst(">", LoadVarInst(loop, j0), Int32(0))
				StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec0[LoadVarInst(loop, j0)], LoadVarInst(struct, fRec0[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 60 bytes
Heap size = 72 bytes
Stack size in compute = 76 bytes

