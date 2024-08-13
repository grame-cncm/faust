======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "sinf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int[2]", iRec0)>)

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
			StoreVarInst(Address(iRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 4 Binop = 5 [ { Int(+) = 3 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec0, kStruct)[Int32(1)]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec0, kStruct)[Int32(0)]), Int32(-1))))))
		StoreVarInst(Address(iRec0, kStruct)[Int32(1)], LoadVarInst(Address(iRec0, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("osc_enable")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", fmydspWave0[13], kStaticStruct|kConst, FloatArrayNumInst{1.0f,0.5f,0.0f,0.0f,0.0f,0.0f,-0.5f,-1.0f,-0.5f,0.0f,0.0f,0.0f,0.0f})
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fmydspWave0_idx)("int", fSampleRate)("float", fConst0)("float[2]", fRec1)("float", fTempPerm0)("float", fTempPerm1)("float", fTempPerm2)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(5))
	EndBlockInst
EndDeclare

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(4e+02f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(fTempPerm0, kStruct), Float(0.0f))
	StoreVarInst(Address(fTempPerm1, kStruct), Float(0.0f))
	StoreVarInst(Address(fTempPerm2, kStruct), Float(0.0f))
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 8 Store = 0 Binop = 0 Mathop = 0 Numbers = 5 Declare = 8 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("float", fTemp2, kStack, LoadVarInst(Address(fTempPerm0, kStruct)))
	DeclareVarInst("float", fTemp3, kStack, LoadVarInst(Address(fTempPerm1, kStruct)))
	DeclareVarInst("float", fTemp4, kStack, LoadVarInst(Address(fTempPerm2, kStruct)))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 31 Store = 12 Binop = 10 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } { Real(!=) = 1 } ] Mathop = 4 [ ] Numbers = 14 Declare = 3 Cast = 6 Select = 4 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, LoadVarInst(Address(fmydspWave0, kStaticStruct)[LoadVarInst(Address(fmydspWave0_idx, kStruct))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0, kStack))))
		DeclareVarInst("int", iTemp1, kStack, BinopInst("!=", LoadVarInst(Address(fTemp0, kStack)), Float(0.0f)))
		IfInst 
			LoadVarInst(Address(iTemp1, kStack))
			BlockInst 
				StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fConst0, kStruct)), BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))))
				StoreVarInst(Address(fTemp2, kStack), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), Int32(65535)))]))
			EndBlockInst
		EndIfInst
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp2, kStack))))
		IfInst 
			LoadVarInst(Address(iTemp1, kStack))
			BlockInst 
				StoreVarInst(Address(fTemp3, kStack), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp2, kStack))))
			EndBlockInst
		EndIfInst
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0, kStack))))
		IfInst 
			LoadVarInst(Address(iTemp1, kStack))
			BlockInst 
				StoreVarInst(Address(fTemp4, kStack), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp0, kStack))))
			EndBlockInst
		EndIfInst
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp4, kStack))))
		StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(13)))
		IfInst 
			LoadVarInst(Address(iTemp1, kStack))
			BlockInst 
				StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			EndBlockInst
		EndIfInst
	EndBlockInst
EndForLoopInst
BlockInst 
	StoreVarInst(Address(fTempPerm0, kStruct), LoadVarInst(Address(fTemp2, kStack)))
	StoreVarInst(Address(fTempPerm1, kStruct), LoadVarInst(Address(fTemp3, kStack)))
	StoreVarInst(Address(fTempPerm2, kStruct), LoadVarInst(Address(fTemp4, kStack)))
EndBlockInst

======= Compute DSP end ==========

======= Post compute DSP begin ==========

BlockInst 
	StoreVarInst(Address(fTempPerm0, kStruct), LoadVarInst(Address(fTemp2, kStack)))
	StoreVarInst(Address(fTempPerm1, kStruct), LoadVarInst(Address(fTemp3, kStack)))
	StoreVarInst(Address(fTempPerm2, kStruct), LoadVarInst(Address(fTemp4, kStack)))
EndBlockInst

======= Post compute DSP end ==========

======= Flatten FIR begin ==========

BlockInst 
	========== Declaration part ==========
	DeclareVarInst("float", fmydspWave0[13], kStaticStruct|kConst, FloatArrayNumInst{1.0f,0.5f,0.0f,0.0f,0.0f,0.0f,-0.5f,-1.0f,-0.5f,0.0f,0.0f,0.0f,0.0f})
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("int", fmydspWave0_idx, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("float", fTempPerm0, kStruct)
	DeclareVarInst("float", fTempPerm1, kStruct)
	DeclareVarInst("float", fTempPerm2, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(4e+02f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(fTempPerm0, kStruct), Float(0.0f))
	StoreVarInst(Address(fTempPerm1, kStruct), Float(0.0f))
	StoreVarInst(Address(fTempPerm2, kStruct), Float(0.0f))
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("int", iRec0[2], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
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
			StoreVarInst(Address(iRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec0, kStruct)[Int32(1)]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec0, kStruct)[Int32(0)]), Int32(-1))))))
			StoreVarInst(Address(iRec0, kStruct)[Int32(1)], LoadVarInst(Address(iRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("float", fTemp2, kStack, LoadVarInst(Address(fTempPerm0, kStruct)))
	DeclareVarInst("float", fTemp3, kStack, LoadVarInst(Address(fTempPerm1, kStruct)))
	DeclareVarInst("float", fTemp4, kStack, LoadVarInst(Address(fTempPerm2, kStruct)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, LoadVarInst(Address(fmydspWave0, kStaticStruct)[LoadVarInst(Address(fmydspWave0_idx, kStruct))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0, kStack))))
			DeclareVarInst("int", iTemp1, kStack, BinopInst("!=", LoadVarInst(Address(fTemp0, kStack)), Float(0.0f)))
			IfInst 
				LoadVarInst(Address(iTemp1, kStack))
				BlockInst 
					StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fConst0, kStruct)), BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))))
					StoreVarInst(Address(fTemp2, kStack), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), Int32(65535)))]))
				EndBlockInst
			EndIfInst
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp2, kStack))))
			IfInst 
				LoadVarInst(Address(iTemp1, kStack))
				BlockInst 
					StoreVarInst(Address(fTemp3, kStack), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp2, kStack))))
				EndBlockInst
			EndIfInst
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0, kStack))))
			IfInst 
				LoadVarInst(Address(iTemp1, kStack))
				BlockInst 
					StoreVarInst(Address(fTemp4, kStack), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp0, kStack))))
				EndBlockInst
			EndIfInst
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp4, kStack))))
			StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(13)))
			IfInst 
				LoadVarInst(Address(iTemp1, kStack))
				BlockInst 
					StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
				EndBlockInst
			EndIfInst
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	StoreVarInst(Address(fTempPerm0, kStruct), LoadVarInst(Address(fTemp2, kStack)))
	StoreVarInst(Address(fTempPerm1, kStruct), LoadVarInst(Address(fTemp3, kStack)))
	StoreVarInst(Address(fTempPerm2, kStruct), LoadVarInst(Address(fTemp4, kStack)))
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 24 bytes
Total heap size = 40 bytes
Stack size in compute = 52 bytes

======= Variable access in Control ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fTempPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fTempPerm0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fTempPerm1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fTempPerm2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1

======= Variable access in compute DSP ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec1 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fTempPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
