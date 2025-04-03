======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Bandfilter")
	AddMetaDeclareInst(fEntry1, "style", "knob")
	AddNumEntry"Q factor", fEntry1, 5e+01f, 0.1f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddMetaDeclareInst(fEntry0, "unit", "Hz")
	AddNumEntry"freq", fEntry0, 1e+03f, 2e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("gain", fVslider0, 0.0f, -5e+01f, 5e+01f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fEntry0)("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fEntry1)("float[3]", fRec0)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(3))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 21 Store = 0 Binop = 19 [ { Real(*) = 7 } { Real(+) = 6 } { Real(-) = 3 } { Real(/) = 3 } ] Mathop = 3 [ { mydsp_faustpower2_f = 1 } { powf = 1 } { tanf = 1 } ] Numbers = 12 Declare = 11 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow6, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fSlow0, kStack))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 20 Store = 5 Binop = 12 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 6 } { Real(+) = 3 } { Real(-) = 1 } ] Mathop = 0 Numbers = 11 Declare = 2 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp0, kStack))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(3))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(2.0f), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow6, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fSlow0, kStack))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp0, kStack))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 28 bytes
Total heap size = 32 bytes
Stack size in compute = 52 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
