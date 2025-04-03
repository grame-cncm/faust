======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("highShelf")
	AddHorizontalSlider("Freq", fHslider1, 1e+03f, 1e+02f, 1e+04f, 1.0f)
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Gain", fHslider0, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("Q", fHslider2, 1.0f, 0.01f, 1e+02f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fHslider2)("float[3]", fRec0)>)

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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(6.2831855f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
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

Instructions complexity : Load = 32 Store = 0 Binop = 27 [ { Real(*) = 7 } { Real(+) = 13 } { Real(-) = 4 } { Real(/) = 3 } ] Mathop = 6 [ { cosf = 1 } { max_f = 2 } { powf = 1 } { sinf = 1 } { sqrtf = 1 } ] Numbers = 17 Declare = 17 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.025f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(0.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", BinopInst("*", FunCallInst("sqrtf", LoadVarInst(Address(fSlow0, kStack))), FunCallInst("sinf", LoadVarInst(Address(fSlow1, kStack)))), FunCallInst("max_f", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("cosf", LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(-1.0f)), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow4, kStack)))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow2, kStack))), Float(1.0f)))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow2, kStack))))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("*", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(1.0f)), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", Float(-1.0f), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow11, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 20 Store = 5 Binop = 13 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 7 } { Real(+) = 2 } { Real(-) = 2 } ] Mathop = 0 Numbers = 12 Declare = 1 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))))))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(6.2831855f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
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
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.025f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(0.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", BinopInst("*", FunCallInst("sqrtf", LoadVarInst(Address(fSlow0, kStack))), FunCallInst("sinf", LoadVarInst(Address(fSlow1, kStack)))), FunCallInst("max_f", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("cosf", LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(-1.0f)), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow4, kStack)))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow2, kStack))), Float(1.0f)))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow2, kStack))))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("*", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(1.0f)), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", Float(-1.0f), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow11, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))))))
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
Stack size in compute = 76 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
