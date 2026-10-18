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

Instructions complexity : Load = 8 Store = 4 Binop = 5 [ { Int(+) = 3 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 9 Declare = 2 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp2, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp2, kStack)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", Int32(-1), LoadVarInst(Address(iTemp2, kStack)))))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fmydspWave0_idx)("int", fSampleRate)("float", fConst0)("float", fTempPerm0)("float[2]", fRec0)("float", fTempPerm1)("float", fTempPerm2)("float", fTempPerm3)>)

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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(4e+02f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(fTempPerm0, kStruct), Float(0.0f))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(fTempPerm1, kStruct), Float(0.0f))
	StoreVarInst(Address(fTempPerm2, kStruct), Float(0.0f))
	StoreVarInst(Address(fTempPerm3, kStruct), Float(0.0f))
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 9 Store = 0 Binop = 0 Mathop = 0 Numbers = 5 Declare = 9 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("float", fTemp3, kStack, LoadVarInst(Address(fTempPerm0, kStruct)))
	DeclareVarInst("float", fTemp4, kStack, LoadVarInst(Address(fTempPerm1, kStruct)))
	DeclareVarInst("float", fTemp5, kStack, LoadVarInst(Address(fTempPerm2, kStruct)))
	DeclareVarInst("float", fTemp6, kStack, LoadVarInst(Address(fTempPerm3, kStruct)))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 31 Store = 13 Binop = 9 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } { Real(!=) = 1 } ] Mathop = 4 [ ] Numbers = 13 Declare = 3 Cast = 6 Select = 4 Loop = 1

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
				StoreVarInst(Address(fTemp3, kStack), BinopInst("+", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
				StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp3, kStack)))))
				StoreVarInst(Address(fTemp4, kStack), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), Int32(65535)))]))
			EndBlockInst
		EndIfInst
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp4, kStack))))
		IfInst 
			LoadVarInst(Address(iTemp1, kStack))
			BlockInst 
				StoreVarInst(Address(fTemp5, kStack), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp4, kStack))))
			EndBlockInst
		EndIfInst
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp5, kStack))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0, kStack))))
		IfInst 
			LoadVarInst(Address(iTemp1, kStack))
			BlockInst 
				StoreVarInst(Address(fTemp6, kStack), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp0, kStack))))
			EndBlockInst
		EndIfInst
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp6, kStack))))
		StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(13)))
		IfInst 
			LoadVarInst(Address(iTemp1, kStack))
			BlockInst 
				StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			EndBlockInst
		EndIfInst
	EndBlockInst
EndForLoopInst
BlockInst 
	StoreVarInst(Address(fTempPerm0, kStruct), LoadVarInst(Address(fTemp3, kStack)))
	StoreVarInst(Address(fTempPerm1, kStruct), LoadVarInst(Address(fTemp4, kStack)))
	StoreVarInst(Address(fTempPerm2, kStruct), LoadVarInst(Address(fTemp5, kStack)))
	StoreVarInst(Address(fTempPerm3, kStruct), LoadVarInst(Address(fTemp6, kStack)))
EndBlockInst

======= Compute DSP end ==========

======= Post compute DSP begin ==========

BlockInst 
	StoreVarInst(Address(fTempPerm0, kStruct), LoadVarInst(Address(fTemp3, kStack)))
	StoreVarInst(Address(fTempPerm1, kStruct), LoadVarInst(Address(fTemp4, kStack)))
	StoreVarInst(Address(fTempPerm2, kStruct), LoadVarInst(Address(fTemp5, kStack)))
	StoreVarInst(Address(fTempPerm3, kStruct), LoadVarInst(Address(fTemp6, kStack)))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("int", fmydspWave0_idx, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fTempPerm0, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fTempPerm1, kStruct)
	DeclareVarInst("float", fTempPerm2, kStruct)
	DeclareVarInst("float", fTempPerm3, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(4e+02f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fTempPerm0, kStruct), Float(0.0f))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(fTempPerm1, kStruct), Float(0.0f))
	StoreVarInst(Address(fTempPerm2, kStruct), Float(0.0f))
	StoreVarInst(Address(fTempPerm3, kStruct), Float(0.0f))
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("float", "sinf", "float", dummy0)
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
			DeclareVarInst("int", iTemp2, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp2, kStack)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", Int32(-1), LoadVarInst(Address(iTemp2, kStack)))))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
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
	DeclareVarInst("float", fTemp3, kStack, LoadVarInst(Address(fTempPerm0, kStruct)))
	DeclareVarInst("float", fTemp4, kStack, LoadVarInst(Address(fTempPerm1, kStruct)))
	DeclareVarInst("float", fTemp5, kStack, LoadVarInst(Address(fTempPerm2, kStruct)))
	DeclareVarInst("float", fTemp6, kStack, LoadVarInst(Address(fTempPerm3, kStruct)))
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
					StoreVarInst(Address(fTemp3, kStack), BinopInst("+", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
					StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp3, kStack)))))
					StoreVarInst(Address(fTemp4, kStack), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), Int32(65535)))]))
				EndBlockInst
			EndIfInst
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp4, kStack))))
			IfInst 
				LoadVarInst(Address(iTemp1, kStack))
				BlockInst 
					StoreVarInst(Address(fTemp5, kStack), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp4, kStack))))
				EndBlockInst
			EndIfInst
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp5, kStack))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0, kStack))))
			IfInst 
				LoadVarInst(Address(iTemp1, kStack))
				BlockInst 
					StoreVarInst(Address(fTemp6, kStack), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp0, kStack))))
				EndBlockInst
			EndIfInst
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp6, kStack))))
			StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(13)))
			IfInst 
				LoadVarInst(Address(iTemp1, kStack))
				BlockInst 
					StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
				EndBlockInst
			EndIfInst
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	StoreVarInst(Address(fTempPerm0, kStruct), LoadVarInst(Address(fTemp3, kStack)))
	StoreVarInst(Address(fTempPerm1, kStruct), LoadVarInst(Address(fTemp4, kStack)))
	StoreVarInst(Address(fTempPerm2, kStruct), LoadVarInst(Address(fTemp5, kStack)))
	StoreVarInst(Address(fTempPerm3, kStruct), LoadVarInst(Address(fTemp6, kStack)))
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 28 bytes
Total heap size = 44 bytes
Stack size in compute = 56 bytes

======= Variable access in Control ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fTempPerm1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fTempPerm1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fTempPerm2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fTempPerm3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1

======= Variable access in compute DSP ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fTempPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fTempPerm1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fTempPerm3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            126
  eval() cache hits:       21 (16.6667%)
  eval() cache misses:     105
  Loop detector calls:     105
  Stack detector calls:    105

--- Phase 3: Propagation ---
  propagate() calls:       92
  propagate() cache hits:  11 (11.9565%)
  propagate() cache misses:81

--- Box Type Computation ---
  getBoxType() calls:      224
  getBoxType() cache hits: 147 (65.625%)
  getBoxType() computed:   77

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       4

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           4735
  Trees reused (hash):     9986 (67.8351% reuse rate)
  Property set ops:        2460
  Property get ops:        1551

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
