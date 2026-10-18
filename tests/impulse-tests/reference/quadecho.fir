======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("stereo echo")
	OpenVerticalBox("echo 1000")
	AddHorizontalSlider("feedback", fHslider0, 1e+02f, 0.0f, 1e+02f, 0.1f)
	AddHorizontalSlider("millisecond", fHslider1, 108.7f, 0.0f, 1e+03f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("int", IOTA0)("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fHslider1)("float[131072]", fRec0)("float[131072]", fRec1)("float[131072]", fRec2)("float[131072]", fRec3)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(4))
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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(108.7f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(131072))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(131072))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(131072))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(131072))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 15 Store = 0 Binop = 8 [ { Int(&) = 1 } { Int(+) = 2 } { Real(*) = 5 } ] Mathop = 4 [ { max_f = 2 } { min_f = 2 } ] Numbers = 19 Declare = 14 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("int", iSlow2, kStack, BinopInst("+", Int32(1), BinopInst("&", BinopInst("+", Int32(-1), CastInst("int", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+03f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))), Int32(65535))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 44 Store = 10 Binop = 27 [ { Int(&) = 12 } { Int(+) = 2 } { Int(-) = 4 } { Int(<) = 1 } { Real(*) = 4 } { Real(+) = 4 } ] Mathop = 0 Numbers = 15 Declare = 1 Cast = 8 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(131071))]))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))])))
		StoreVarInst(Address(fRec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(131071))]))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))])))
		StoreVarInst(Address(fRec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fRec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(131071))]))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))])))
		StoreVarInst(Address(fRec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(131071))]))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))])))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fRec0[131072], kStruct)
	DeclareVarInst("float", fRec1[131072], kStruct)
	DeclareVarInst("float", fRec2[131072], kStruct)
	DeclareVarInst("float", fRec3[131072], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(108.7f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(131072))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(131072))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(131072))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(131072))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
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
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("int", iSlow2, kStack, BinopInst("+", Int32(1), BinopInst("&", BinopInst("+", Int32(-1), CastInst("int", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+03f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))), Int32(65535))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(131071))]))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))])))
			StoreVarInst(Address(fRec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(131071))]))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))])))
			StoreVarInst(Address(fRec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fRec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(131071))]))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))])))
			StoreVarInst(Address(fRec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))], BinopInst("+", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(131071))]))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(131071))])))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 2097168 bytes
Total heap size = 2097176 bytes
Stack size in compute = 88 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 131072 size_bytes = 524288 read = 0 write = 0 ratio = 0
Field = fRec1 size = 131072 size_bytes = 524288 read = 0 write = 0 ratio = 0
Field = fRec2 size = 131072 size_bytes = 524288 read = 0 write = 0 ratio = 0
Field = fRec3 size = 131072 size_bytes = 524288 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 131072 size_bytes = 524288 read = 0 write = 0 ratio = 0
Field = fRec1 size = 131072 size_bytes = 524288 read = 0 write = 0 ratio = 0
Field = fRec2 size = 131072 size_bytes = 524288 read = 0 write = 0 ratio = 0
Field = fRec3 size = 131072 size_bytes = 524288 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 13 write = 1 ratio = 14
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 131072 size_bytes = 524288 read = 2 write = 1 ratio = 2.28882e-05
Field = fRec1 size = 131072 size_bytes = 524288 read = 2 write = 1 ratio = 2.28882e-05
Field = fRec2 size = 131072 size_bytes = 524288 read = 2 write = 1 ratio = 2.28882e-05
Field = fRec3 size = 131072 size_bytes = 524288 read = 2 write = 1 ratio = 2.28882e-05

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            268
  eval() cache hits:       35 (13.0597%)
  eval() cache misses:     233
  Loop detector calls:     233
  Stack detector calls:    233

--- Phase 3: Propagation ---
  propagate() calls:       222
  propagate() cache hits:  22 (9.90991%)
  propagate() cache misses:200

--- Box Type Computation ---
  getBoxType() calls:      330
  getBoxType() cache hits: 240 (72.7273%)
  getBoxType() computed:   90

--- Environment Operations ---
  Environment lookups:     18
  Average lookup depth:    0.333333
  Env layers pushed:       26

--- Pattern Matching ---
  build automaton calls:        1
  build total time (ms):        0.008667
  build avg time (ms):          0.008667
  apply calls:                  12
  apply total time (ms):        0.010001
  apply avg time (ms):          0.000833417

--- Tree Operations ---
  Trees created:           5312
  Trees reused (hash):     11540 (68.4785% reuse rate)
  Property set ops:        2638
  Property get ops:        3196

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
