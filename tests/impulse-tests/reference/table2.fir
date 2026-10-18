======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int[2]", iIIR0)>)

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
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 8 Store = 4 Binop = 3 [ { Int(+) = 2 } { Int(<) = 1 } ] Mathop = 0 Numbers = 7 Declare = 2 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], LoadVarInst(Address(iTemp0, kStack)))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container "mydspSIG1" ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG1",("float[2]", fIIR2)>)

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
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 8 Store = 4 Binop = 3 [ { Int(+) = 1 } { Int(<) = 1 } { Real(+) = 1 } ] Mathop = 0 Numbers = 7 Declare = 2 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i2, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i2, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i2, kLoop), BinopInst("+", LoadVarInst(Address(i2, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", Float(0.1f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)])))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i2, kLoop))], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container "mydspSIG2" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("int", imydspSIG2Wave0[7], kStaticStruct|kConst, Int32ArrayNumInst{1,2,3,7,4,8,1})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG2",("int", imydspSIG2Wave0_idx)>)

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
	StoreVarInst(Address(imydspSIG2Wave0_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 3 Binop = 4 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } ] Mathop = 0 Numbers = 4 Declare = 1 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i3, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i3, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i3, kLoop), BinopInst("+", LoadVarInst(Address(i3, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i3, kLoop))], LoadVarInst(Address(imydspSIG2Wave0, kStaticStruct)[LoadVarInst(Address(imydspSIG2Wave0_idx, kStruct))]))
		StoreVarInst(Address(imydspSIG2Wave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspSIG2Wave0_idx, kStruct))), Int32(7)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container "mydspSIG3" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", fmydspSIG3Wave0[7], kStaticStruct|kConst, FloatArrayNumInst{1.4f,2.1f,3.8f,7.12f,4.9f,8.9f,1.2f})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG3",("int", fmydspSIG3Wave0_idx)>)

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
	StoreVarInst(Address(fmydspSIG3Wave0_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 3 Binop = 4 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } ] Mathop = 0 Numbers = 4 Declare = 1 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i4, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i4, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i4, kLoop), BinopInst("+", LoadVarInst(Address(i4, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i4, kLoop))], LoadVarInst(Address(fmydspSIG3Wave0, kStaticStruct)[LoadVarInst(Address(fmydspSIG3Wave0_idx, kStruct))]))
		StoreVarInst(Address(fmydspSIG3Wave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspSIG3Wave0_idx, kStruct))), Int32(7)))
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
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", imydspWave0[7], kStaticStruct|kConst, Int32ArrayNumInst{1,2,3,7,4,8,1})
	DeclareVarInst("float", fmydspWave1[7], kStaticStruct|kConst, FloatArrayNumInst{1.4f,2.1f,3.8f,7.12f,4.9f,8.9f,1.2f})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int[10]", itbl0)("int[2]", iIIR1)("float[7]", ftbl1)("float[2]", fIIR3)("int[10]", itbl2)("int", imydspWave0_idx)("float[7]", ftbl3)("int", fmydspWave1_idx)("int", fSampleRate)>)

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
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(10), LoadVarInst(Address(itbl0, kStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG1", sig1, kStack, FunCallInst("newmydspSIG1"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG1", LoadVarInst(Address(sig1, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG1", LoadVarInst(Address(sig1, kStack)), Int32(7), LoadVarInst(Address(ftbl1, kStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG2", sig2, kStack, FunCallInst("newmydspSIG2"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG2", LoadVarInst(Address(sig2, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG2", LoadVarInst(Address(sig2, kStack)), Int32(10), LoadVarInst(Address(itbl2, kStruct|kReference|kMutable))))
	StoreVarInst(Address(imydspWave0_idx, kStruct), Int32(0))
	DeclareVarInst("mydspSIG3", sig3, kStack, FunCallInst("newmydspSIG3"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG3", LoadVarInst(Address(sig3, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG3", LoadVarInst(Address(sig3, kStack)), Int32(7), LoadVarInst(Address(ftbl3, kStruct|kReference|kMutable))))
	StoreVarInst(Address(fmydspWave1_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 35 Store = 15 Binop = 24 [ { Int(%) = 6 } { Int(*) = 1 } { Int(+) = 8 } { Int(<) = 1 } { Real(*) = 3 } { Real(+) = 5 } ] Mathop = 20 [ { fmodf = 4 } { max_i = 8 } { min_i = 8 } ] Numbers = 52 Declare = 5 Cast = 10 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp1, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp1, kStack)))
		StoreVarInst(Address(itbl0, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp1, kStack))), Int32(10)), Int32(9)))], BinopInst("*", Int32(2), LoadVarInst(Address(iTemp1, kStack))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(itbl0, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", BinopInst("+", Int32(2), LoadVarInst(Address(iTemp1, kStack))), Int32(10)), Int32(9)))])))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("+", Float(0.1f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)])))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
		StoreVarInst(Address(ftbl1, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", FunCallInst("fmodf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp3, kStack))), Float(7.0f))), Int32(6)))], BinopInst("*", Float(1.24f), LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl1, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", FunCallInst("fmodf", BinopInst("+", Float(2.0f), LoadVarInst(Address(fTemp3, kStack))), Float(7.0f))), Int32(6)))])))
		DeclareVarInst("int", iTemp4, kStack, LoadVarInst(Address(imydspWave0, kStaticStruct)[LoadVarInst(Address(imydspWave0_idx, kStruct))]))
		StoreVarInst(Address(itbl2, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp4, kStack))), Int32(10)), Int32(9)))], CastInst("int", BinopInst("*", Float(1.24f), CastInst("float", LoadVarInst(Address(iTemp4, kStack))))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(itbl2, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", BinopInst("+", Int32(2), LoadVarInst(Address(iTemp4, kStack))), Int32(10)), Int32(9)))])))
		DeclareVarInst("float", fTemp5, kStack, LoadVarInst(Address(fmydspWave1, kStaticStruct)[LoadVarInst(Address(fmydspWave1_idx, kStruct))]))
		StoreVarInst(Address(ftbl3, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", FunCallInst("fmodf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp5, kStack))), Float(7.0f))), Int32(6)))], BinopInst("*", Float(1.24f), LoadVarInst(Address(fTemp5, kStack))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl3, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", FunCallInst("fmodf", BinopInst("+", Float(2.0f), LoadVarInst(Address(fTemp5, kStack))), Float(7.0f))), Int32(6)))])))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(imydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspWave0_idx, kStruct))), Int32(7)))
		StoreVarInst(Address(fmydspWave1_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave1_idx, kStruct))), Int32(7)))
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
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", imydspWave0[7], kStaticStruct|kConst, Int32ArrayNumInst{1,2,3,7,4,8,1})
	DeclareVarInst("float", fmydspWave1[7], kStaticStruct|kConst, FloatArrayNumInst{1.4f,2.1f,3.8f,7.12f,4.9f,8.9f,1.2f})
	DeclareVarInst("int", itbl0[10], kStruct)
	DeclareVarInst("int", iIIR1[2], kStruct)
	DeclareVarInst("float", ftbl1[7], kStruct)
	DeclareVarInst("float", fIIR3[2], kStruct)
	DeclareVarInst("int", itbl2[10], kStruct)
	DeclareVarInst("int", imydspWave0_idx, kStruct)
	DeclareVarInst("float", ftbl3[7], kStruct)
	DeclareVarInst("int", fmydspWave1_idx, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(10), LoadVarInst(Address(itbl0, kStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG1", sig1, kStack, FunCallInst("newmydspSIG1"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG1", LoadVarInst(Address(sig1, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG1", LoadVarInst(Address(sig1, kStack)), Int32(7), LoadVarInst(Address(ftbl1, kStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG2", sig2, kStack, FunCallInst("newmydspSIG2"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG2", LoadVarInst(Address(sig2, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG2", LoadVarInst(Address(sig2, kStack)), Int32(10), LoadVarInst(Address(itbl2, kStruct|kReference|kMutable))))
	StoreVarInst(Address(imydspWave0_idx, kStruct), Int32(0))
	DeclareVarInst("mydspSIG3", sig3, kStack, FunCallInst("newmydspSIG3"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG3", LoadVarInst(Address(sig3, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG3", LoadVarInst(Address(sig3, kStack)), Int32(7), LoadVarInst(Address(ftbl3, kStruct|kReference|kMutable))))
	StoreVarInst(Address(fmydspWave1_idx, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	DropInst(FunCallInst("deletemydspSIG1", LoadVarInst(Address(sig1, kStack))))
	DropInst(FunCallInst("deletemydspSIG2", LoadVarInst(Address(sig2, kStack))))
	DropInst(FunCallInst("deletemydspSIG3", LoadVarInst(Address(sig3, kStack))))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", iIIR0[2], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
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
			DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], LoadVarInst(Address(iTemp0, kStack)))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Declaration part ==========
	DeclareVarInst("float", fIIR2[2], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
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
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", Float(0.1f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)])))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i2, kLoop))], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Declaration part ==========
	DeclareVarInst("int", imydspSIG2Wave0[7], kStaticStruct|kConst, Int32ArrayNumInst{1,2,3,7,4,8,1})
	DeclareVarInst("int", imydspSIG2Wave0_idx, kStruct)
	========== Init method ==========
	StoreVarInst(Address(imydspSIG2Wave0_idx, kStruct), Int32(0))
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
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i3, kLoop))], LoadVarInst(Address(imydspSIG2Wave0, kStaticStruct)[LoadVarInst(Address(imydspSIG2Wave0_idx, kStruct))]))
			StoreVarInst(Address(imydspSIG2Wave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspSIG2Wave0_idx, kStruct))), Int32(7)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Declaration part ==========
	DeclareVarInst("float", fmydspSIG3Wave0[7], kStaticStruct|kConst, FloatArrayNumInst{1.4f,2.1f,3.8f,7.12f,4.9f,8.9f,1.2f})
	DeclareVarInst("int", fmydspSIG3Wave0_idx, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fmydspSIG3Wave0_idx, kStruct), Int32(0))
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
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i4, kLoop))], LoadVarInst(Address(fmydspSIG3Wave0, kStaticStruct)[LoadVarInst(Address(fmydspSIG3Wave0_idx, kStruct))]))
			StoreVarInst(Address(fmydspSIG3Wave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspSIG3Wave0_idx, kStruct))), Int32(7)))
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
			DeclareVarInst("int", iTemp1, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp1, kStack)))
			StoreVarInst(Address(itbl0, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp1, kStack))), Int32(10)), Int32(9)))], BinopInst("*", Int32(2), LoadVarInst(Address(iTemp1, kStack))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(itbl0, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", BinopInst("+", Int32(2), LoadVarInst(Address(iTemp1, kStack))), Int32(10)), Int32(9)))])))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("+", Float(0.1f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)])))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
			StoreVarInst(Address(ftbl1, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", FunCallInst("fmodf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp3, kStack))), Float(7.0f))), Int32(6)))], BinopInst("*", Float(1.24f), LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl1, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", FunCallInst("fmodf", BinopInst("+", Float(2.0f), LoadVarInst(Address(fTemp3, kStack))), Float(7.0f))), Int32(6)))])))
			DeclareVarInst("int", iTemp4, kStack, LoadVarInst(Address(imydspWave0, kStaticStruct)[LoadVarInst(Address(imydspWave0_idx, kStruct))]))
			StoreVarInst(Address(itbl2, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp4, kStack))), Int32(10)), Int32(9)))], CastInst("int", BinopInst("*", Float(1.24f), CastInst("float", LoadVarInst(Address(iTemp4, kStack))))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(itbl2, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", BinopInst("+", Int32(2), LoadVarInst(Address(iTemp4, kStack))), Int32(10)), Int32(9)))])))
			DeclareVarInst("float", fTemp5, kStack, LoadVarInst(Address(fmydspWave1, kStaticStruct)[LoadVarInst(Address(fmydspWave1_idx, kStruct))]))
			StoreVarInst(Address(ftbl3, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", FunCallInst("fmodf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp5, kStack))), Float(7.0f))), Int32(6)))], BinopInst("*", Float(1.24f), LoadVarInst(Address(fTemp5, kStack))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl3, kStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", FunCallInst("fmodf", BinopInst("+", Float(2.0f), LoadVarInst(Address(fTemp5, kStack))), Float(7.0f))), Int32(6)))])))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(imydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspWave0_idx, kStruct))), Int32(7)))
			StoreVarInst(Address(fmydspWave1_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave1_idx, kStruct))), Int32(7)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 12 bytes
Heap size int* = 88 bytes
Heap size real = 64 bytes
Total heap size = 188 bytes
Stack size in compute = 32 bytes

======= Variable access in Control ==========

Field = itbl0 size = 10 size_bytes = 40 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = ftbl1 size = 7 size_bytes = 28 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = itbl2 size = 10 size_bytes = 40 read = 0 write = 0 ratio = 0
Field = imydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = ftbl3 size = 7 size_bytes = 28 read = 0 write = 0 ratio = 0
Field = fmydspWave1_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = itbl0 size = 10 size_bytes = 40 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = ftbl1 size = 7 size_bytes = 28 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = itbl2 size = 10 size_bytes = 40 read = 0 write = 0 ratio = 0
Field = imydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = ftbl3 size = 7 size_bytes = 28 read = 0 write = 0 ratio = 0
Field = fmydspWave1_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = itbl0 size = 10 size_bytes = 40 read = 1 write = 1 ratio = 0.2
Field = iIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = ftbl1 size = 7 size_bytes = 28 read = 1 write = 1 ratio = 0.285714
Field = fIIR3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = itbl2 size = 10 size_bytes = 40 read = 1 write = 1 ratio = 0.2
Field = imydspWave0_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = ftbl3 size = 7 size_bytes = 28 read = 1 write = 1 ratio = 0.285714
Field = fmydspWave1_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            181
  eval() cache hits:       32 (17.6796%)
  eval() cache misses:     149
  Loop detector calls:     149
  Stack detector calls:    149

--- Phase 3: Propagation ---
  propagate() calls:       147
  propagate() cache hits:  36 (24.4898%)
  propagate() cache misses:111

--- Box Type Computation ---
  getBoxType() calls:      319
  getBoxType() cache hits: 233 (73.0408%)
  getBoxType() computed:   86

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       5

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           1259
  Trees reused (hash):     2750 (68.5957% reuse rate)
  Property set ops:        825
  Property get ops:        1914

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
