======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenHorizontalBox("Stereo Reverb Tester")
	AddMetaDeclareInst(0, "1", "")
	OpenVerticalBox("Input Config")
	AddMetaDeclareInst(fCheckbox0, "2", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting the EQ sections)")
	AddCheckButtonInst("Pink Noise"fCheckbox0)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("Impulse Selection")
	AddMetaDeclareInst(fButton0, "1", "")
	AddMetaDeclareInst(fButton0, "tooltip", "Send impulse into LEFT channel")
	AddButtonInst("Left"fButton0)
	AddMetaDeclareInst(fButton1, "2", "")
	AddMetaDeclareInst(fButton1, "tooltip", "Send impulse into LEFT and RIGHT channels")
	AddButtonInst("Center"fButton1)
	AddMetaDeclareInst(fButton2, "3", "")
	AddMetaDeclareInst(fButton2, "tooltip", "Send impulse into RIGHT channel")
	AddButtonInst("Right"fButton2)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fButton0)("float[2]", fVec0)("FAUSTFLOAT", fButton1)("float[2]", fVec1)("FAUSTFLOAT", fCheckbox0)("int[2]", iIIR1)("float[4]", fIIR0)("float[4]", fVec2)("FAUSTFLOAT", fButton2)("float[2]", fVec3)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fButton1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fButton2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(4))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(4))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 9 Store = 0 Binop = 5 [ { Real(*) = 1 } { Real(>) = 4 } ] Mathop = 0 Numbers = 9 Declare = 9 Cast = 8 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton1, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(0.1f), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton2, kStruct))), Float(0.0f))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 45 Store = 17 Binop = 35 [ { Int(*) = 1 } { Int(+) = 4 } { Int(-) = 4 } { Int(<) = 1 } { Int(>) = 2 } { Real(*) = 9 } { Real(+) = 8 } { Real(-) = 3 } { Real(>) = 3 } ] Mathop = 0 Numbers = 48 Declare = 7 Cast = 5 Select = 0 Loop = 3

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow0, kStack)))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fSlow1, kStack)))
		DeclareVarInst("int", iTemp0, kStack, BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])), Float(0.0f)))
		DeclareVarInst("int", iTemp1, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp1, kStack)))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(Address(iTemp1, kStack))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", Float(-2.0172658f), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))), BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fIIR0, kStruct)[Int32(3)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fTemp2, kStack))))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fVec2, kStruct)[Int32(0)])), BinopInst("*", Float(-0.095993534f), LoadVarInst(Address(fVec2, kStruct)[Int32(1)]))), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fVec2, kStruct)[Int32(2)]))), BinopInst("*", Float(-0.004408786f), LoadVarInst(Address(fVec2, kStruct)[Int32(3)])))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", CastInst("float", BinopInst("+", BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])), Float(0.0f)), LoadVarInst(Address(iTemp0, kStack)))), LoadVarInst(Address(fTemp3, kStack)))))
		StoreVarInst(Address(fVec3, kStruct)[Int32(0)], LoadVarInst(Address(fSlow4, kStack)))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp0, kStack)), BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)])), Float(0.0f)))), LoadVarInst(Address(fTemp3, kStack)))))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
		ForLoopInst 
			DeclareVarInst("int", j0, kLoop, Int32(3))
			BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
			StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(fIIR0, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
		ForLoopInst 
			DeclareVarInst("int", j1, kLoop, Int32(3))
			BinopInst(">", LoadVarInst(Address(j1, kLoop)), Int32(0))
			StoreVarInst(Address(j1, kLoop), BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(j1, kLoop))], LoadVarInst(Address(fVec2, kStruct)[BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
		StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Post compute DSP begin ==========

BlockInst 
EndBlockInst

======= Post compute DSP end ==========

======= Flatten FIR begin ==========

BlockInst 
	========== Declaration part ==========
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("float", fVec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton1, kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("int", iIIR1[2], kStruct)
	DeclareVarInst("float", fIIR0[4], kStruct)
	DeclareVarInst("float", fVec2[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton2, kStruct)
	DeclareVarInst("float", fVec3[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fButton1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fButton2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(4))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(4))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton1, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(0.1f), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton2, kStruct))), Float(0.0f))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow0, kStack)))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fSlow1, kStack)))
			DeclareVarInst("int", iTemp0, kStack, BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])), Float(0.0f)))
			DeclareVarInst("int", iTemp1, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp1, kStack)))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(Address(iTemp1, kStack))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", Float(-2.0172658f), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))), BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fIIR0, kStruct)[Int32(3)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fTemp2, kStack))))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fVec2, kStruct)[Int32(0)])), BinopInst("*", Float(-0.095993534f), LoadVarInst(Address(fVec2, kStruct)[Int32(1)]))), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fVec2, kStruct)[Int32(2)]))), BinopInst("*", Float(-0.004408786f), LoadVarInst(Address(fVec2, kStruct)[Int32(3)])))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", CastInst("float", BinopInst("+", BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])), Float(0.0f)), LoadVarInst(Address(iTemp0, kStack)))), LoadVarInst(Address(fTemp3, kStack)))))
			StoreVarInst(Address(fVec3, kStruct)[Int32(0)], LoadVarInst(Address(fSlow4, kStack)))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp0, kStack)), BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)])), Float(0.0f)))), LoadVarInst(Address(fTemp3, kStack)))))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
			ForLoopInst 
				DeclareVarInst("int", j0, kLoop, Int32(3))
				BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
				StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(fIIR0, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
			ForLoopInst 
				DeclareVarInst("int", j1, kLoop, Int32(3))
				BinopInst(">", LoadVarInst(Address(j1, kLoop)), Int32(0))
				StoreVarInst(Address(j1, kLoop), BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(j1, kLoop))], LoadVarInst(Address(fVec2, kStruct)[BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
			StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 72 bytes
Total heap size = 84 bytes
Stack size in compute = 52 bytes

======= Variable access in Control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec2 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fButton2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec2 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fButton2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fButton1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR0 size = 4 size_bytes = 16 read = 4 write = 2 ratio = 1.5
Field = fVec2 size = 4 size_bytes = 16 read = 5 write = 2 ratio = 1.75
Field = fButton2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            382
  eval() cache hits:       58 (15.1832%)
  eval() cache misses:     324
  Loop detector calls:     324
  Stack detector calls:    324

--- Phase 3: Propagation ---
  propagate() calls:       214
  propagate() cache hits:  20 (9.34579%)
  propagate() cache misses:194

--- Box Type Computation ---
  getBoxType() calls:      426
  getBoxType() cache hits: 292 (68.5446%)
  getBoxType() computed:   134

--- Environment Operations ---
  Environment lookups:     47
  Average lookup depth:    0.574468
  Env layers pushed:       72

--- Pattern Matching ---
  build automaton calls:        3
  build total time (ms):        0.022333
  build avg time (ms):          0.00744433
  apply calls:                  22
  apply total time (ms):        0.022251
  apply avg time (ms):          0.00101141

--- Tree Operations ---
  Trees created:           24344
  Trees reused (hash):     69628 (74.0944% reuse rate)
  Property set ops:        16300
  Property get ops:        2842

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
