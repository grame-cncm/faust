======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("lowboost")
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddMetaDeclareInst(fEntry0, "unit", "Hz")
	AddNumEntry"freq", fEntry0, 1e+02f, 2e+01f, 1.5e+02f, 1.0f)
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("gain", fVslider0, 0.0f, -2e+01f, 2e+01f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fEntry0)("float[3]", fIIR0)("FAUSTFLOAT", fVslider0)>)

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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(1e+02f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(3))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 28 Store = 0 Binop = 21 [ { Real(*) = 8 } { Real(+) = 6 } { Real(-) = 2 } { Real(/) = 5 } ] Mathop = 8 [ { max_f = 2 } { min_f = 2 } { mydsp_faustpower2_f = 1 } { powf = 1 } { sqrtf = 1 } { tanf = 1 } ] Numbers = 16 Declare = 16 Cast = 2 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(1.5e+02f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f)))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow1, kStack))), LoadVarInst(Address(fSlow4, kStack)))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fSlow2, kStack))), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-2e+01f), FunCallInst("min_f", Float(2e+01f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow7, kStack)))), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow9, kStack))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fSlow10, kStack))), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow9, kStack))), LoadVarInst(Address(fSlow4, kStack)))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow8, kStack))), LoadVarInst(Address(fSlow4, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 19 Store = 5 Binop = 11 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 5 } { Real(+) = 2 } { Real(-) = 2 } ] Mathop = 0 Numbers = 12 Declare = 2 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("-", BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("float", fIIR0[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(1e+02f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(3))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(1.5e+02f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f)))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow1, kStack))), LoadVarInst(Address(fSlow4, kStack)))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fSlow2, kStack))), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-2e+01f), FunCallInst("min_f", Float(2e+01f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow7, kStack)))), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow9, kStack))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fSlow10, kStack))), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow9, kStack))), LoadVarInst(Address(fSlow4, kStack)))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow8, kStack))), LoadVarInst(Address(fSlow4, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("-", BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
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
Stack size in compute = 72 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            1012
  eval() cache hits:       263 (25.9881%)
  eval() cache misses:     749
  Loop detector calls:     749
  Stack detector calls:    749

--- Phase 3: Propagation ---
  propagate() calls:       416
  propagate() cache hits:  126 (30.2885%)
  propagate() cache misses:290

--- Box Type Computation ---
  getBoxType() calls:      595
  getBoxType() cache hits: 472 (79.3277%)
  getBoxType() computed:   123

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       20

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           5734
  Trees reused (hash):     13152 (69.6389% reuse rate)
  Property set ops:        2728
  Property get ops:        2666

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
