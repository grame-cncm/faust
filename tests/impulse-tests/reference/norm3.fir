======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("norm3")
	AddHorizontalSlider("1.1_c", fHslider0, 2.0f, 1.0f, 1e+01f, 1.0f)
	AddHorizontalSlider("1.2_c", fHslider1, 2.0f, 1.0f, 1e+01f, 1.0f)
	AddHorizontalSlider("1.4_c1", fHslider2, 1e+01f, 1.0f, 1e+02f, 1.0f)
	AddHorizontalSlider("1.4_c2", fHslider3, 2e+01f, 1.0f, 1e+02f, 1.0f)
	AddHorizontalSlider("1.5_c", fHslider4, 2e+01f, 1.0f, 1e+02f, 1.0f)
	AddHorizontalSlider("3.1_x", fHslider5, 0.0f, -1.0f, 1.0f, 1.0f)
	AddHorizontalSlider("3.2_y", fHslider6, 0.0f, -1.0f, 1.0f, 1.0f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "fabsf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("float[2]", fVec0)("FAUSTFLOAT", fHslider1)("float[2]", fVec1)("int", IOTA0)("float[32]", fVec2)("float[128]", fVec3)("FAUSTFLOAT", fHslider2)("float[128]", fVec4)("FAUSTFLOAT", fHslider3)("float[11]", fVec5)("float[128]", fVec6)("FAUSTFLOAT", fHslider4)("FAUSTFLOAT", fHslider5)("FAUSTFLOAT", fHslider6)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(11))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(11))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+01f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(2e+01f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(2e+01f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(32))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(128))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(128))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(11))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(128))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 29 Store = 0 Binop = 1 [ { Real(/) = 1 } ] Mathop = 0 Numbers = 23 Declare = 29 Cast = 10 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", input8, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", input9, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", input10, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output8, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", output9, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", output10, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("int", iSlow2, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("int", iSlow3, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("int", iSlow4, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 60 Store = 24 Binop = 21 [ { Int(&) = 8 } { Int(+) = 2 } { Int(-) = 6 } { Int(<) = 1 } { Int(>) = 1 } { Real(*) = 3 } ] Mathop = 1 [ { fabsf = 1 } ] Numbers = 28 Declare = 2 Cast = 20 Select = 0 Loop = 2

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))
		StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(30)), Int32(31))])))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(127))]))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow3, kStack))), Int32(127))])))
		StoreVarInst(Address(fVec5, kStruct)[Int32(0)], CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], LoadVarInst(Address(fVec5, kStruct)[CastInst("int", BinopInst("*", Float(1e+01f), FunCallInst("fabsf", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])))))]))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow4, kStack))), Int32(127))])))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(3)))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(5.0f)))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow6, kStack))))
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		ForLoopInst 
			DeclareVarInst("int", j0, kLoop, Int32(10))
			BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
			StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(fVec5, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
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
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("float", fVec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec2[32], kStruct)
	DeclareVarInst("float", fVec3[128], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fVec4[128], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fVec5[11], kStruct)
	DeclareVarInst("float", fVec6[128], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+01f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(2e+01f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(2e+01f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(32))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(128))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(128))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(11))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(128))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
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
	DeclareVarInst("FAUSTFLOAT*", input8, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", input9, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", input10, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output8, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", output9, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", output10, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("int", iSlow2, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("int", iSlow3, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("int", iSlow4, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))
			StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(30)), Int32(31))])))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(127))]))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow3, kStack))), Int32(127))])))
			StoreVarInst(Address(fVec5, kStruct)[Int32(0)], CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], LoadVarInst(Address(fVec5, kStruct)[CastInst("int", BinopInst("*", Float(1e+01f), FunCallInst("fabsf", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])))))]))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow4, kStack))), Int32(127))])))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(3)))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(5.0f)))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow6, kStack))))
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			ForLoopInst 
				DeclareVarInst("int", j0, kLoop, Int32(10))
				BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
				StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(fVec5, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 1752 bytes
Total heap size = 1760 bytes
Stack size in compute = 204 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fVec3 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5 size = 11 size_bytes = 44 read = 0 write = 0 ratio = 0
Field = fVec6 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fVec3 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec4 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec5 size = 11 size_bytes = 44 read = 0 write = 0 ratio = 0
Field = fVec6 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = IOTA0 size = 1 size_bytes = 4 read = 9 write = 1 ratio = 10
Field = fVec2 size = 32 size_bytes = 128 read = 1 write = 1 ratio = 0.0625
Field = fVec3 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5 size = 11 size_bytes = 44 read = 2 write = 2 ratio = 0.363636
Field = fVec6 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
