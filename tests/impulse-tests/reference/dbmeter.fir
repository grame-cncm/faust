======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenHorizontalBox("8 channels dB meter")
	OpenVerticalBox("0")
	AddMetaDeclareInst(fVbargraph0, "unit", "dB")
	AddVerticalBargraph("vbargraph0", fVbargraph0, -7e+01f, 1e+01f)
	CloseboxInst
	OpenVerticalBox("1")
	AddMetaDeclareInst(fVbargraph1, "unit", "dB")
	AddVerticalBargraph("vbargraph1", fVbargraph1, -7e+01f, 1e+01f)
	CloseboxInst
	OpenVerticalBox("2")
	AddMetaDeclareInst(fVbargraph2, "unit", "dB")
	AddVerticalBargraph("vbargraph2", fVbargraph2, -7e+01f, 1e+01f)
	CloseboxInst
	OpenVerticalBox("3")
	AddMetaDeclareInst(fVbargraph3, "unit", "dB")
	AddVerticalBargraph("vbargraph3", fVbargraph3, -7e+01f, 1e+01f)
	CloseboxInst
	OpenVerticalBox("4")
	AddMetaDeclareInst(fVbargraph4, "unit", "dB")
	AddVerticalBargraph("vbargraph4", fVbargraph4, -7e+01f, 1e+01f)
	CloseboxInst
	OpenVerticalBox("5")
	AddMetaDeclareInst(fVbargraph5, "unit", "dB")
	AddVerticalBargraph("vbargraph5", fVbargraph5, -7e+01f, 1e+01f)
	CloseboxInst
	OpenVerticalBox("6")
	AddMetaDeclareInst(fVbargraph6, "unit", "dB")
	AddVerticalBargraph("vbargraph6", fVbargraph6, -7e+01f, 1e+01f)
	CloseboxInst
	OpenVerticalBox("7")
	AddMetaDeclareInst(fVbargraph7, "unit", "dB")
	AddVerticalBargraph("vbargraph7", fVbargraph7, -7e+01f, 1e+01f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("float[2]", fRec0)("FAUSTFLOAT", fVbargraph0)("int", iConst1)("float[2]", fRec1)("FAUSTFLOAT", fVbargraph1)("int", iConst2)("float[2]", fRec2)("FAUSTFLOAT", fVbargraph2)("int", iConst3)("float[2]", fRec3)("FAUSTFLOAT", fVbargraph3)("int", iConst4)("float[2]", fRec4)("FAUSTFLOAT", fVbargraph4)("int", iConst5)("float[2]", fRec5)("FAUSTFLOAT", fVbargraph5)("int", iConst6)("float[2]", fRec6)("FAUSTFLOAT", fVbargraph6)("int", iConst7)("float[2]", fRec7)("FAUSTFLOAT", fVbargraph7)("int", iConst8)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(8))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(8))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(8e+01f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(iConst1, kStruct), Int32(0))
	StoreVarInst(Address(iConst2, kStruct), Int32(0))
	StoreVarInst(Address(iConst3, kStruct), Int32(0))
	StoreVarInst(Address(iConst4, kStruct), Int32(0))
	StoreVarInst(Address(iConst5, kStruct), Int32(0))
	StoreVarInst(Address(iConst6, kStruct), Int32(0))
	StoreVarInst(Address(iConst7, kStruct), Int32(0))
	StoreVarInst(Address(iConst8, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 16 Store = 0 Binop = 0 Mathop = 0 Numbers = 16 Declare = 16 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 75 Store = 33 Binop = 18 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 8 } { Real(-) = 8 } ] Mathop = 40 [ { fabsf = 8 } { log10f = 8 } { max_f = 16 } { min_f = 8 } ] Numbers = 66 Declare = 9 Cast = 24 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp0, kStack)))))))))
		StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst1, kStruct))))
		DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp1, kStack)))))))))
		StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst2, kStruct))))
		DeclareVarInst("float", fTemp2, kStack, CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp2, kStack)))))))))
		StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst3, kStruct))))
		DeclareVarInst("float", fTemp3, kStack, CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp3, kStack)))))))))
		StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst4, kStruct))))
		DeclareVarInst("float", fTemp4, kStack, CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp4, kStack)))))))))
		StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec4, kStruct)[Int32(0)])))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst5, kStruct))))
		DeclareVarInst("float", fTemp5, kStack, CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp5, kStack)))))))))
		StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec5, kStruct)[Int32(0)])))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst6, kStruct))))
		DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp6, kStack)))))))))
		StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec6, kStruct)[Int32(0)])))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst7, kStruct))))
		DeclareVarInst("float", fTemp7, kStack, CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp7, kStack)))))))))
		StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec7, kStruct)[Int32(0)])))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst8, kStruct))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph0, kStruct)
	DeclareVarInst("int", iConst1, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph1, kStruct)
	DeclareVarInst("int", iConst2, kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph2, kStruct)
	DeclareVarInst("int", iConst3, kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph3, kStruct)
	DeclareVarInst("int", iConst4, kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph4, kStruct)
	DeclareVarInst("int", iConst5, kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph5, kStruct)
	DeclareVarInst("int", iConst6, kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph6, kStruct)
	DeclareVarInst("int", iConst7, kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph7, kStruct)
	DeclareVarInst("int", iConst8, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(8e+01f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(iConst1, kStruct), Int32(0))
	StoreVarInst(Address(iConst2, kStruct), Int32(0))
	StoreVarInst(Address(iConst3, kStruct), Int32(0))
	StoreVarInst(Address(iConst4, kStruct), Int32(0))
	StoreVarInst(Address(iConst5, kStruct), Int32(0))
	StoreVarInst(Address(iConst6, kStruct), Int32(0))
	StoreVarInst(Address(iConst7, kStruct), Int32(0))
	StoreVarInst(Address(iConst8, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp0, kStack)))))))))
			StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst1, kStruct))))
			DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp1, kStack)))))))))
			StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst2, kStruct))))
			DeclareVarInst("float", fTemp2, kStack, CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp2, kStack)))))))))
			StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst3, kStruct))))
			DeclareVarInst("float", fTemp3, kStack, CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp3, kStack)))))))))
			StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst4, kStruct))))
			DeclareVarInst("float", fTemp4, kStack, CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp4, kStack)))))))))
			StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec4, kStruct)[Int32(0)])))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst5, kStruct))))
			DeclareVarInst("float", fTemp5, kStack, CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp5, kStack)))))))))
			StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec5, kStruct)[Int32(0)])))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst6, kStruct))))
			DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp6, kStack)))))))))
			StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec6, kStruct)[Int32(0)])))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst7, kStruct))))
			DeclareVarInst("float", fTemp7, kStack, CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fConst0, kStruct))), FunCallInst("min_f", Float(1e+01f), BinopInst("*", Float(2e+01f), FunCallInst("log10f", FunCallInst("max_f", Float(0.00031622776f), FunCallInst("fabsf", LoadVarInst(Address(fTemp7, kStack)))))))))
			StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec7, kStruct)[Int32(0)])))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(iConst8, kStruct))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 36 bytes
Heap size int* = 0 bytes
Heap size real = 100 bytes
Total heap size = 136 bytes
Stack size in compute = 128 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = iConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = iConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = iConst3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec3 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = iConst4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = iConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = iConst6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = iConst7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = iConst8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
