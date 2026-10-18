======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("karplus")
	OpenVerticalBox("excitator")
	AddMetaDeclareInst(fHslider2, "unit", "f")
	AddHorizontalSlider("excitation", fHslider2, 327.023f, 2.0f, 512.0f, 1.0f)
	AddButtonInst("play"fButton0)
	CloseboxInst
	AddHorizontalSlider("level", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f)
	OpenVerticalBox("resonator")
	AddHorizontalSlider("attenuation", fHslider0, 0.0f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fHslider3, "unit", "f")
	AddHorizontalSlider("duration", fHslider3, 271.994f, 2.0f, 512.0f, 1.0f)
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

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int[2]", iIIR0)("FAUSTFLOAT", fButton0)("float[2]", fVec0)("FAUSTFLOAT", fHslider2)("float[2]", fRec1)("int", IOTA0)("float[512]", fVec1)("FAUSTFLOAT", fHslider3)("float[3]", fRec0)("int", fSampleRate)>)

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
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(327.023f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(271.994f)))
EndBlockInst

======= ResetUI end ==========

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
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(512))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 9 Store = 0 Binop = 7 [ { Int(&) = 1 } { Real(*) = 2 } { Real(+) = 1 } { Real(-) = 1 } { Real(/) = 1 } { Real(>) = 1 } ] Mathop = 8 [ { max_f = 4 } { min_f = 4 } ] Numbers = 16 Declare = 9 Cast = 7 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(2.0f), FunCallInst("min_f", Float(512.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	DeclareVarInst("int", iSlow7, kStack, BinopInst("&", CastInst("int", BinopInst("+", Float(-1.5f), FunCallInst("max_f", Float(2.0f), FunCallInst("min_f", Float(512.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))))), Int32(4095)))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 29 Store = 13 Binop = 20 [ { Int(&) = 2 } { Int(*) = 1 } { Int(+) = 3 } { Int(-) = 1 } { Int(<) = 1 } { Real(*) = 4 } { Real(+) = 3 } { Real(-) = 2 } { Real(>) = 3 } ] Mathop = 0 Numbers = 32 Declare = 2 Cast = 5 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow5, kStack)))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])), Float(0.0f))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.0f))))), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(iTemp0, kStack))), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow7, kStack))), Int32(511))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", iIIR0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("float", fVec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec1[512], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(327.023f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(271.994f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(512))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(2.0f), FunCallInst("min_f", Float(512.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	DeclareVarInst("int", iSlow7, kStack, BinopInst("&", CastInst("int", BinopInst("+", Float(-1.5f), FunCallInst("max_f", Float(2.0f), FunCallInst("min_f", Float(512.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))))), Int32(4095)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow5, kStack)))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])), Float(0.0f))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.0f))))), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(iTemp0, kStack))), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow7, kStack))), Int32(511))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 2096 bytes
Total heap size = 2112 bytes
Stack size in compute = 40 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = IOTA0 size = 1 size_bytes = 4 read = 3 write = 1 ratio = 4
Field = fVec1 size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            209
  eval() cache hits:       30 (14.3541%)
  eval() cache misses:     179
  Loop detector calls:     179
  Stack detector calls:    179

--- Phase 3: Propagation ---
  propagate() calls:       160
  propagate() cache hits:  38 (23.75%)
  propagate() cache misses:122

--- Box Type Computation ---
  getBoxType() calls:      274
  getBoxType() cache hits: 180 (65.6934%)
  getBoxType() computed:   94

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       12

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           5253
  Trees reused (hash):     11556 (68.7489% reuse rate)
  Property set ops:        2699
  Property get ops:        2415

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
