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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fEntry0)("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fEntry1)("float[3]", fIIR0)>)

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
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(1e+03f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
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

Instructions complexity : Load = 25 Store = 0 Binop = 16 [ { Real(*) = 4 } { Real(+) = 4 } { Real(-) = 2 } { Real(/) = 6 } ] Mathop = 9 [ { max_f = 3 } { min_f = 3 } { mydsp_faustpower2_f = 1 } { powf = 1 } { tanf = 1 } ] Numbers = 13 Declare = 13 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))))), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f)))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow1, kStack))), LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow3, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("/", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fSlow4, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow8, kStack))), LoadVarInst(Address(fSlow5, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 19 Store = 5 Binop = 11 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 5 } { Real(+) = 2 } { Real(-) = 2 } ] Mathop = 0 Numbers = 12 Declare = 2 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("-", BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
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
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("float", fIIR0[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(1e+03f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
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
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("max_f", Float(0.1f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("powf", Float(1e+01f), NegInst(BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-5e+01f), FunCallInst("min_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))))), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f)))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fSlow1, kStack))), LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow3, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("/", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fSlow4, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow8, kStack))), LoadVarInst(Address(fSlow5, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("-", BinopInst("-", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
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
Heap size real = 28 bytes
Total heap size = 32 bytes
Stack size in compute = 60 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            1062
  eval() cache hits:       272 (25.6121%)
  eval() cache misses:     790
  Loop detector calls:     790
  Stack detector calls:    790

--- Phase 3: Propagation ---
  propagate() calls:       464
  propagate() cache hits:  174 (37.5%)
  propagate() cache misses:290

--- Box Type Computation ---
  getBoxType() calls:      619
  getBoxType() cache hits: 504 (81.4216%)
  getBoxType() computed:   115

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       22

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           5774
  Trees reused (hash):     13259 (69.6632% reuse rate)
  Property set ops:        2730
  Property get ops:        2759

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
