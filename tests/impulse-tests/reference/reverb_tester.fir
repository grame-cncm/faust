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

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fButton0)("int", IOTA0)("float[2]", fVec0BE)("FAUSTFLOAT", fButton1)("float[2]", fVec1BE)("FAUSTFLOAT", fButton2)("float[2]", fVec2BE)("int[2]", iVec4SI)("float[2]", fVec6SI)("float[4]", fVec3SI)("FAUSTFLOAT", fCheckbox0)("int", fSampleRate)>)

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
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fButton1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fButton2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0BE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1BE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2BE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec4SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SI, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 11 Store = 0 Binop = 1 [ { Real(*) = 1 } ] Mathop = 0 Numbers = 5 Declare = 11 Cast = 4 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, LoadVarInst(Address(fSlow0BE, kStack)))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fButton1, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, LoadVarInst(Address(fSlow2BE, kStack)))
	DeclareVarInst("float", fSlow4BE, kStack, CastInst("float", LoadVarInst(Address(fButton2, kStruct))))
	DeclareVarInst("float", fSlow5BE, kStack, LoadVarInst(Address(fSlow4BE, kStack)))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("*", Float(0.1f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 50 Store = 10 Binop = 55 [ { Int(&) = 17 } { Int(*) = 1 } { Int(+) = 5 } { Int(-) = 8 } { Int(<) = 1 } { Real(*) = 9 } { Real(+) = 11 } { Real(>) = 3 } ] Mathop = 0 Numbers = 41 Declare = 6 Cast = 5 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow1BE, kStack)))
		StoreVarInst(Address(fVec1BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow3BE, kStack)))
		StoreVarInst(Address(fVec2BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow5BE, kStack)))
		DeclareVarInst("float", fTemp0SI, kStack, LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(3)), Int32(3))]))
		StoreVarInst(Address(iVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec4SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
		DeclareVarInst("float", fTemp1SI, kStack, LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fTemp0SI, kStack))), BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(iVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), BinopInst("*", Float(-2.0172658f), LoadVarInst(Address(fTemp1SI, kStack)))))
		DeclareVarInst("float", fTemp2SI, kStack, LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp2SI, kStack)))
		DeclareVarInst("int", iTemp3SE, kStack, BinopInst(">", BinopInst("+", LoadVarInst(Address(fSlow2BE, kStack)), MinusInst(LoadVarInst(Address(fVec1BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Float(0.0f)))
		DeclareVarInst("float", fTemp4SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fTemp1SI, kStack)))), BinopInst("*", Float(-0.095993534f), LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", Float(-0.004408786f), LoadVarInst(Address(fTemp0SI, kStack))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", CastInst("float", BinopInst("+", BinopInst(">", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), MinusInst(LoadVarInst(Address(fVec0BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Float(0.0f)), LoadVarInst(Address(iTemp3SE, kStack)))), LoadVarInst(Address(fTemp4SE, kStack)))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp4SE, kStack)), CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp3SE, kStack)), BinopInst(">", BinopInst("+", LoadVarInst(Address(fSlow4BE, kStack)), MinusInst(LoadVarInst(Address(fVec2BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Float(0.0f)))))))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0BE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton1, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec1BE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton2, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2BE[2], kStruct)
	// Recursion delay iVec4SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec4SI[2], kStruct)
	// Recursion delay fVec6SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec6SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec3SI[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fButton1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fButton2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0BE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1BE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2BE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec4SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SI, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, LoadVarInst(Address(fSlow0BE, kStack)))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fButton1, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, LoadVarInst(Address(fSlow2BE, kStack)))
	DeclareVarInst("float", fSlow4BE, kStack, CastInst("float", LoadVarInst(Address(fButton2, kStruct))))
	DeclareVarInst("float", fSlow5BE, kStack, LoadVarInst(Address(fSlow4BE, kStack)))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("*", Float(0.1f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow1BE, kStack)))
			StoreVarInst(Address(fVec1BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow3BE, kStack)))
			StoreVarInst(Address(fVec2BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow5BE, kStack)))
			DeclareVarInst("float", fTemp0SI, kStack, LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(3)), Int32(3))]))
			StoreVarInst(Address(iVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec4SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
			DeclareVarInst("float", fTemp1SI, kStack, LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fTemp0SI, kStack))), BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(iVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), BinopInst("*", Float(-2.0172658f), LoadVarInst(Address(fTemp1SI, kStack)))))
			DeclareVarInst("float", fTemp2SI, kStack, LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp2SI, kStack)))
			DeclareVarInst("int", iTemp3SE, kStack, BinopInst(">", BinopInst("+", LoadVarInst(Address(fSlow2BE, kStack)), MinusInst(LoadVarInst(Address(fVec1BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Float(0.0f)))
			DeclareVarInst("float", fTemp4SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fTemp1SI, kStack)))), BinopInst("*", Float(-0.095993534f), LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", Float(-0.004408786f), LoadVarInst(Address(fTemp0SI, kStack))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", CastInst("float", BinopInst("+", BinopInst(">", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), MinusInst(LoadVarInst(Address(fVec0BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Float(0.0f)), LoadVarInst(Address(iTemp3SE, kStack)))), LoadVarInst(Address(fTemp4SE, kStack)))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp4SE, kStack)), CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp3SE, kStack)), BinopInst(">", BinopInst("+", LoadVarInst(Address(fSlow4BE, kStack)), MinusInst(LoadVarInst(Address(fVec2BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Float(0.0f)))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 64 bytes
Total heap size = 80 bytes
Stack size in compute = 60 bytes

======= Variable access in Control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec4SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec4SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 18 write = 1 ratio = 19
Field = fVec0BE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fButton1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1BE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fButton2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2BE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = iVec4SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec6SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec3SI size = 4 size_bytes = 16 read = 3 write = 1 ratio = 1
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
