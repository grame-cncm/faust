======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int[2]", iIIR1)("float[4]", fIIR0)("float[4]", fVec0)>)

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
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(4))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 27 Store = 10 Binop = 24 [ { Int(*) = 1 } { Int(+) = 2 } { Int(-) = 4 } { Int(<) = 1 } { Int(>) = 2 } { Real(*) = 8 } { Real(+) = 6 } ] Mathop = 0 Numbers = 33 Declare = 5 Cast = 1 Select = 0 Loop = 3

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(Address(iTemp0, kStack))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", Float(-2.0172658f), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))), BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fIIR0, kStruct)[Int32(3)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fTemp1, kStack))))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fVec0, kStruct)[Int32(0)])), BinopInst("*", Float(-0.095993534f), LoadVarInst(Address(fVec0, kStruct)[Int32(1)]))), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fVec0, kStruct)[Int32(2)]))), BinopInst("*", Float(-0.004408786f), LoadVarInst(Address(fVec0, kStruct)[Int32(3)]))))
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
				StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(j1, kLoop))], LoadVarInst(Address(fVec0, kStruct)[BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("table")
	AddHorizontalSlider("freq", fHslider0, 4.4e+02f, 5e+01f, 2e+03f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fHslider0)("float[2]", fRec0)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(4.4e+02f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 4 Store = 0 Binop = 1 [ { Real(*) = 1 } ] Mathop = 2 [ { max_f = 1 } { min_f = 1 } ] Numbers = 4 Declare = 3 Cast = 1 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(5e+01f), FunCallInst("min_f", Float(2e+03f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 14 Store = 5 Binop = 5 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 1 } { Real(+) = 1 } { Real(-) = 1 } ] Mathop = 3 [ { floorf = 1 } { max_i = 1 } { min_i = 1 } ] Numbers = 10 Declare = 3 Cast = 3 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp2, kStack)))))
		DeclareVarInst("float", fTemp3, kStack, LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), Int32(65535)))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
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
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(4.4e+02f)))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", iIIR1[2], kStruct)
	DeclareVarInst("float", fIIR0[4], kStruct)
	DeclareVarInst("float", fVec0[4], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(4))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
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
			DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(Address(iTemp0, kStack))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", Float(-2.0172658f), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))), BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fIIR0, kStruct)[Int32(3)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fTemp1, kStack))))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fVec0, kStruct)[Int32(0)])), BinopInst("*", Float(-0.095993534f), LoadVarInst(Address(fVec0, kStruct)[Int32(1)]))), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fVec0, kStruct)[Int32(2)]))), BinopInst("*", Float(-0.004408786f), LoadVarInst(Address(fVec0, kStruct)[Int32(3)]))))
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
					StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(j1, kLoop))], LoadVarInst(Address(fVec0, kStruct)[BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(5e+01f), FunCallInst("min_f", Float(2e+03f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp2, kStack)))))
			DeclareVarInst("float", fTemp3, kStack, LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), Int32(65535)))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 16 bytes
Total heap size = 60 bytes
Stack size in compute = 20 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            159
  eval() cache hits:       39 (24.5283%)
  eval() cache misses:     120
  Loop detector calls:     120
  Stack detector calls:    120

--- Phase 3: Propagation ---
  propagate() calls:       157
  propagate() cache hits:  14 (8.9172%)
  propagate() cache misses:143

--- Box Type Computation ---
  getBoxType() calls:      303
  getBoxType() cache hits: 188 (62.0462%)
  getBoxType() computed:   115

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       4

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           1139
  Trees reused (hash):     2738 (70.6216% reuse rate)
  Property set ops:        540
  Property get ops:        1554

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
