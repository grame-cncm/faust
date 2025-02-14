======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int", IOTA1)("int[2]", iVec2SI)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 10 Store = 4 Binop = 8 [ { Int(&) = 3 } { Int(+) = 3 } { Int(-) = 1 } { Int(<) = 1 } ] Mathop = 0 Numbers = 8 Declare = 1 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]))
		StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container "mydspSIG1" ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG1",("int", IOTA2)("float[2]", fVec6SI)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA2, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 10 Store = 4 Binop = 8 [ { Int(&) = 3 } { Int(+) = 2 } { Int(-) = 1 } { Int(<) = 1 } { Real(+) = 1 } ] Mathop = 0 Numbers = 8 Declare = 1 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i2, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i2, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i2, kLoop), BinopInst("+", LoadVarInst(Address(i2, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA2, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA2, kStruct)), Int32(1)), Int32(1))]), Float(0.1f)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i2, kLoop))], LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA2, kStruct)), Int32(1))]))
		StoreVarInst(Address(IOTA2, kStruct), BinopInst("+", LoadVarInst(Address(IOTA2, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container "mydspSIG2" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("int", imydspSIG2Wave0SC[7], kStaticStruct|kConst, Int32ArrayNumInst{1,2,3,7,4,8,1})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG2",("int", iConst1KC)("int", imydspSIG2Wave0SC_idx)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(iConst1KC, kStruct), Int32(1))
	StoreVarInst(Address(imydspSIG2Wave0SC_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 3 Binop = 4 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } ] Mathop = 0 Numbers = 4 Declare = 1 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i3, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i3, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i3, kLoop), BinopInst("+", LoadVarInst(Address(i3, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i3, kLoop))], LoadVarInst(Address(imydspSIG2Wave0SC, kStaticStruct)[LoadVarInst(Address(imydspSIG2Wave0SC_idx, kStruct))]))
		StoreVarInst(Address(imydspSIG2Wave0SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspSIG2Wave0SC_idx, kStruct))), Int32(7)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container "mydspSIG3" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", fmydspSIG3Wave0SC[7], kStaticStruct|kConst, FloatArrayNumInst{1.4f,2.1f,3.8f,7.12f,4.9f,8.9f,1.2f})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG3",("float", fConst3KC)("int", fmydspSIG3Wave0SC_idx)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fConst3KC, kStruct), Float(1.4f))
	StoreVarInst(Address(fmydspSIG3Wave0SC_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 3 Binop = 4 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } ] Mathop = 0 Numbers = 4 Declare = 1 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i4, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i4, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i4, kLoop), BinopInst("+", LoadVarInst(Address(i4, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i4, kLoop))], LoadVarInst(Address(fmydspSIG3Wave0SC, kStaticStruct)[LoadVarInst(Address(fmydspSIG3Wave0SC_idx, kStruct))]))
		StoreVarInst(Address(fmydspSIG3Wave0SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspSIG3Wave0SC_idx, kStruct))), Int32(7)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("table2")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", imydspWave0SC[7], kStaticStruct|kConst, Int32ArrayNumInst{1,2,3,7,4,8,1})
	DeclareVarInst("float", fmydspWave1SC[7], kStaticStruct|kConst, FloatArrayNumInst{1.4f,2.1f,3.8f,7.12f,4.9f,8.9f,1.2f})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("int[2]", iVec0SI)("int[10]", itbl0SI)("float[2]", fVec4SI)("float[7]", ftbl1SI)("int", iConst0KC)("int", imydspWave0SC_idx)("int[10]", itbl2SC)("float", fConst2KC)("int", fmydspWave1SC_idx)("float[7]", ftbl3SC)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(4))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(10), LoadVarInst(Address(itbl0SI, kStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG1", sig1, kStack, FunCallInst("newmydspSIG1"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG1", LoadVarInst(Address(sig1, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG1", LoadVarInst(Address(sig1, kStack)), Int32(7), LoadVarInst(Address(ftbl1SI, kStruct|kReference|kMutable))))
	StoreVarInst(Address(iConst0KC, kStruct), Int32(1))
	StoreVarInst(Address(imydspWave0SC_idx, kStruct), Int32(0))
	DeclareVarInst("mydspSIG2", sig2, kStack, FunCallInst("newmydspSIG2"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG2", LoadVarInst(Address(sig2, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG2", LoadVarInst(Address(sig2, kStack)), Int32(10), LoadVarInst(Address(itbl2SC, kStruct|kReference|kMutable))))
	StoreVarInst(Address(fConst2KC, kStruct), Float(1.4f))
	StoreVarInst(Address(fmydspWave1SC_idx, kStruct), Int32(0))
	DeclareVarInst("mydspSIG3", sig3, kStack, FunCallInst("newmydspSIG3"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG3", LoadVarInst(Address(sig3, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG3", LoadVarInst(Address(sig3, kStack)), Int32(7), LoadVarInst(Address(ftbl3SC, kStruct|kReference|kMutable))))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SI, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 4 Store = 0 Binop = 0 Mathop = 0 Numbers = 4 Declare = 4 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 40 Store = 14 Binop = 33 [ { Int(%) = 6 } { Int(&) = 6 } { Int(*) = 1 } { Int(+) = 9 } { Int(-) = 2 } { Int(<) = 1 } { Real(*) = 3 } { Real(+) = 5 } ] Mathop = 4 [ { fmodf = 4 } ] Numbers = 37 Declare = 5 Cast = 10 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
		DeclareVarInst("int", iTemp0SI, kStack, LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(itbl0SI, kStruct)[BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp0SI, kStack)), Int32(1)), Int32(10))], BinopInst("*", Int32(2), LoadVarInst(Address(iTemp0SI, kStack))))
		StoreVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(0.1f)))
		DeclareVarInst("float", fTemp1SI, kStack, LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(ftbl1SI, kStruct)[CastInst("int", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp1SI, kStack)), Float(1.0f)), Float(7.0f)))], BinopInst("*", Float(1.24f), LoadVarInst(Address(fTemp1SI, kStack))))
		DeclareVarInst("int", iTemp2SC, kStack, LoadVarInst(Address(imydspWave0SC, kStaticStruct)[LoadVarInst(Address(imydspWave0SC_idx, kStruct))]))
		StoreVarInst(Address(itbl2SC, kStruct)[BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp2SC, kStack)), Int32(1)), Int32(10))], CastInst("int", BinopInst("*", Float(1.24f), CastInst("float", LoadVarInst(Address(iTemp2SC, kStack))))))
		DeclareVarInst("float", fTemp3SC, kStack, LoadVarInst(Address(fmydspWave1SC, kStaticStruct)[LoadVarInst(Address(fmydspWave1SC_idx, kStruct))]))
		StoreVarInst(Address(ftbl3SC, kStruct)[CastInst("int", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp3SC, kStack)), Float(1.0f)), Float(7.0f)))], BinopInst("*", Float(1.24f), LoadVarInst(Address(fTemp3SC, kStack))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(itbl0SI, kStruct)[BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp0SI, kStack)), Int32(2)), Int32(10))])))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl1SI, kStruct)[CastInst("int", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp1SI, kStack)), Float(2.0f)), Float(7.0f)))])))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(itbl2SC, kStruct)[BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp2SC, kStack)), Int32(2)), Int32(10))])))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl3SC, kStruct)[CastInst("int", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp3SC, kStack)), Float(2.0f)), Float(7.0f)))])))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(imydspWave0SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspWave0SC_idx, kStruct))), Int32(7)))
		StoreVarInst(Address(fmydspWave1SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave1SC_idx, kStruct))), Int32(7)))
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
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", imydspWave0SC[7], kStaticStruct|kConst, Int32ArrayNumInst{1,2,3,7,4,8,1})
	DeclareVarInst("float", fmydspWave1SC[7], kStaticStruct|kConst, FloatArrayNumInst{1.4f,2.1f,3.8f,7.12f,4.9f,8.9f,1.2f})
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay iVec0SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec0SI[2], kStruct)
	DeclareVarInst("int", itbl0SI[10], kStruct)
	// Recursion delay fVec4SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec4SI[2], kStruct)
	DeclareVarInst("float", ftbl1SI[7], kStruct)
	DeclareVarInst("int", iConst0KC, kStruct)
	DeclareVarInst("int", imydspWave0SC_idx, kStruct)
	DeclareVarInst("int", itbl2SC[10], kStruct)
	DeclareVarInst("float", fConst2KC, kStruct)
	DeclareVarInst("int", fmydspWave1SC_idx, kStruct)
	DeclareVarInst("float", ftbl3SC[7], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(10), LoadVarInst(Address(itbl0SI, kStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG1", sig1, kStack, FunCallInst("newmydspSIG1"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG1", LoadVarInst(Address(sig1, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG1", LoadVarInst(Address(sig1, kStack)), Int32(7), LoadVarInst(Address(ftbl1SI, kStruct|kReference|kMutable))))
	StoreVarInst(Address(iConst0KC, kStruct), Int32(1))
	StoreVarInst(Address(imydspWave0SC_idx, kStruct), Int32(0))
	DeclareVarInst("mydspSIG2", sig2, kStack, FunCallInst("newmydspSIG2"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG2", LoadVarInst(Address(sig2, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG2", LoadVarInst(Address(sig2, kStack)), Int32(10), LoadVarInst(Address(itbl2SC, kStruct|kReference|kMutable))))
	StoreVarInst(Address(fConst2KC, kStruct), Float(1.4f))
	StoreVarInst(Address(fmydspWave1SC_idx, kStruct), Int32(0))
	DeclareVarInst("mydspSIG3", sig3, kStack, FunCallInst("newmydspSIG3"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG3", LoadVarInst(Address(sig3, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG3", LoadVarInst(Address(sig3, kStack)), Int32(7), LoadVarInst(Address(ftbl3SC, kStruct|kReference|kMutable))))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SI, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	DropInst(FunCallInst("deletemydspSIG1", LoadVarInst(Address(sig1, kStack))))
	DropInst(FunCallInst("deletemydspSIG2", LoadVarInst(Address(sig2, kStack))))
	DropInst(FunCallInst("deletemydspSIG3", LoadVarInst(Address(sig3, kStack))))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", IOTA1, kStruct)
	// Recursion delay iVec2SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec2SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]))
			StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Declaration part ==========
	DeclareVarInst("int", IOTA2, kStruct)
	// Recursion delay fVec6SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec6SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(IOTA2, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i2, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i2, kLoop), BinopInst("+", LoadVarInst(Address(i2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA2, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA2, kStruct)), Int32(1)), Int32(1))]), Float(0.1f)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i2, kLoop))], LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA2, kStruct)), Int32(1))]))
			StoreVarInst(Address(IOTA2, kStruct), BinopInst("+", LoadVarInst(Address(IOTA2, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Declaration part ==========
	DeclareVarInst("int", imydspSIG2Wave0SC[7], kStaticStruct|kConst, Int32ArrayNumInst{1,2,3,7,4,8,1})
	DeclareVarInst("int", iConst1KC, kStruct)
	DeclareVarInst("int", imydspSIG2Wave0SC_idx, kStruct)
	========== Init method ==========
	StoreVarInst(Address(iConst1KC, kStruct), Int32(1))
	StoreVarInst(Address(imydspSIG2Wave0SC_idx, kStruct), Int32(0))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i3, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i3, kLoop), BinopInst("+", LoadVarInst(Address(i3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i3, kLoop))], LoadVarInst(Address(imydspSIG2Wave0SC, kStaticStruct)[LoadVarInst(Address(imydspSIG2Wave0SC_idx, kStruct))]))
			StoreVarInst(Address(imydspSIG2Wave0SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspSIG2Wave0SC_idx, kStruct))), Int32(7)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Declaration part ==========
	DeclareVarInst("float", fmydspSIG3Wave0SC[7], kStaticStruct|kConst, FloatArrayNumInst{1.4f,2.1f,3.8f,7.12f,4.9f,8.9f,1.2f})
	DeclareVarInst("float", fConst3KC, kStruct)
	DeclareVarInst("int", fmydspSIG3Wave0SC_idx, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fConst3KC, kStruct), Float(1.4f))
	StoreVarInst(Address(fmydspSIG3Wave0SC_idx, kStruct), Int32(0))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i4, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i4, kLoop), BinopInst("+", LoadVarInst(Address(i4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i4, kLoop))], LoadVarInst(Address(fmydspSIG3Wave0SC, kStaticStruct)[LoadVarInst(Address(fmydspSIG3Wave0SC_idx, kStruct))]))
			StoreVarInst(Address(fmydspSIG3Wave0SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspSIG3Wave0SC_idx, kStruct))), Int32(7)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
			DeclareVarInst("int", iTemp0SI, kStack, LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(itbl0SI, kStruct)[BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp0SI, kStack)), Int32(1)), Int32(10))], BinopInst("*", Int32(2), LoadVarInst(Address(iTemp0SI, kStack))))
			StoreVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(0.1f)))
			DeclareVarInst("float", fTemp1SI, kStack, LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(ftbl1SI, kStruct)[CastInst("int", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp1SI, kStack)), Float(1.0f)), Float(7.0f)))], BinopInst("*", Float(1.24f), LoadVarInst(Address(fTemp1SI, kStack))))
			DeclareVarInst("int", iTemp2SC, kStack, LoadVarInst(Address(imydspWave0SC, kStaticStruct)[LoadVarInst(Address(imydspWave0SC_idx, kStruct))]))
			StoreVarInst(Address(itbl2SC, kStruct)[BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp2SC, kStack)), Int32(1)), Int32(10))], CastInst("int", BinopInst("*", Float(1.24f), CastInst("float", LoadVarInst(Address(iTemp2SC, kStack))))))
			DeclareVarInst("float", fTemp3SC, kStack, LoadVarInst(Address(fmydspWave1SC, kStaticStruct)[LoadVarInst(Address(fmydspWave1SC_idx, kStruct))]))
			StoreVarInst(Address(ftbl3SC, kStruct)[CastInst("int", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp3SC, kStack)), Float(1.0f)), Float(7.0f)))], BinopInst("*", Float(1.24f), LoadVarInst(Address(fTemp3SC, kStack))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(itbl0SI, kStruct)[BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp0SI, kStack)), Int32(2)), Int32(10))])))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl1SI, kStruct)[CastInst("int", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp1SI, kStack)), Float(2.0f)), Float(7.0f)))])))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(itbl2SC, kStruct)[BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp2SC, kStack)), Int32(2)), Int32(10))])))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl3SC, kStruct)[CastInst("int", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp3SC, kStack)), Float(2.0f)), Float(7.0f)))])))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(imydspWave0SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspWave0SC_idx, kStruct))), Int32(7)))
			StoreVarInst(Address(fmydspWave1SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave1SC_idx, kStruct))), Int32(7)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 20 bytes
Heap size int* = 88 bytes
Heap size real = 68 bytes
Total heap size = 216 bytes
Stack size in compute = 32 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = itbl0SI size = 10 size_bytes = 40 read = 0 write = 0 ratio = 0
Field = fVec4SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = ftbl1SI size = 7 size_bytes = 28 read = 0 write = 0 ratio = 0
Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = imydspWave0SC_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = itbl2SC size = 10 size_bytes = 40 read = 0 write = 0 ratio = 0
Field = fConst2KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave1SC_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = ftbl3SC size = 7 size_bytes = 28 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = itbl0SI size = 10 size_bytes = 40 read = 0 write = 0 ratio = 0
Field = fVec4SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = ftbl1SI size = 7 size_bytes = 28 read = 0 write = 0 ratio = 0
Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = imydspWave0SC_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = itbl2SC size = 10 size_bytes = 40 read = 0 write = 0 ratio = 0
Field = fConst2KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave1SC_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = ftbl3SC size = 7 size_bytes = 28 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 7 write = 1 ratio = 8
Field = iVec0SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = itbl0SI size = 10 size_bytes = 40 read = 1 write = 1 ratio = 0.2
Field = fVec4SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = ftbl1SI size = 7 size_bytes = 28 read = 1 write = 1 ratio = 0.285714
Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = imydspWave0SC_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = itbl2SC size = 10 size_bytes = 40 read = 1 write = 1 ratio = 0.2
Field = fConst2KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave1SC_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = ftbl3SC size = 7 size_bytes = 28 read = 1 write = 1 ratio = 0.285714
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
