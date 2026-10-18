======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("notch")
	AddHorizontalSlider("Freq", fHslider0, 1e+03f, 1e+02f, 1e+04f, 1.0f)
	AddHorizontalSlider("Q", fHslider1, 1.0f, 0.01f, 1e+02f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("float[3]", fIIR0)>)

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
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(6.2831855f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(1e+03f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(1.0f)))
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

Instructions complexity : Load = 12 Store = 0 Binop = 9 [ { Real(*) = 3 } { Real(+) = 1 } { Real(-) = 1 } { Real(/) = 4 } ] Mathop = 8 [ { cosf = 1 } { max_f = 4 } { min_f = 2 } { sinf = 1 } ] Numbers = 13 Declare = 8 Cast = 2 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(0.0f), FunCallInst("max_f", Float(1e+02f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.5f), BinopInst("/", FunCallInst("sinf", LoadVarInst(Address(fSlow0, kStack))), FunCallInst("max_f", Float(0.001f), FunCallInst("max_f", Float(0.01f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(2.0f), BinopInst("/", FunCallInst("cosf", LoadVarInst(Address(fSlow0, kStack))), LoadVarInst(Address(fSlow2, kStack)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 19 Store = 5 Binop = 11 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 5 } { Real(+) = 2 } { Real(-) = 2 } ] Mathop = 0 Numbers = 12 Declare = 2 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("-", BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
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
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fIIR0[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(6.2831855f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(1e+03f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(1.0f)))
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
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(0.0f), FunCallInst("max_f", Float(1e+02f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.5f), BinopInst("/", FunCallInst("sinf", LoadVarInst(Address(fSlow0, kStack))), FunCallInst("max_f", Float(0.001f), FunCallInst("max_f", Float(0.01f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(2.0f), BinopInst("/", FunCallInst("cosf", LoadVarInst(Address(fSlow0, kStack))), LoadVarInst(Address(fSlow2, kStack)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("-", BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
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
Stack size in compute = 40 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            509
  eval() cache hits:       79 (15.5206%)
  eval() cache misses:     430
  Loop detector calls:     430
  Stack detector calls:    430

--- Phase 3: Propagation ---
  propagate() calls:       263
  propagate() cache hits:  76 (28.8973%)
  propagate() cache misses:187

--- Box Type Computation ---
  getBoxType() calls:      401
  getBoxType() cache hits: 285 (71.0723%)
  getBoxType() computed:   116

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       31

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           6251
  Trees reused (hash):     15276 (70.962% reuse rate)
  Property set ops:        3549
  Property get ops:        2062

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
