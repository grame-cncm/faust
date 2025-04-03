======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("low-freq shelving cut")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "unit", "dB")
	AddHorizontalSlider("attenuation", fHslider1, 0.0f, -96.0f, 1e+01f, 0.1f)
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider0, 1e+02f, 2e+01f, 5e+03f, 1.0f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("float[3]", fRec0)>)

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
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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

Instructions complexity : Load = 22 Store = 0 Binop = 22 [ { Real(*) = 11 } { Real(+) = 8 } { Real(-) = 2 } { Real(/) = 1 } ] Mathop = 4 [ { mydsp_faustpower2_f = 1 } { powf = 1 } { sqrtf = 1 } { tanf = 1 } ] Numbers = 16 Declare = 13 Cast = 2 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow1, kStack)))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow3, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(1.4142135f))), Float(1.0f)))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow3, kStack))))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow1, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), Float(-1.0f))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(-1.4142135f))), Float(1.0f)))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 20 Store = 5 Binop = 13 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 7 } { Real(+) = 3 } { Real(-) = 1 } ] Mathop = 0 Numbers = 12 Declare = 1 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))))))
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
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("powf", Float(1e+01f), MinusInst(BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow1, kStack)))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow3, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(1.4142135f))), Float(1.0f)))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow3, kStack))))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow1, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), Float(-1.0f))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(-1.4142135f))), Float(1.0f)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))))))
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
Heap size real = 24 bytes
Total heap size = 28 bytes
Stack size in compute = 60 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
