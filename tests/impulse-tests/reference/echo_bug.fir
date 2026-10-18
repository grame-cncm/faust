======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("echo_bug")
	AddMetaDeclareInst(fHslider0, "0", "")
	AddHorizontalSlider("EchoWarp", fHslider0, 0.0f, -1.0f, 1.0f, 0.001f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[256]", fRec0)("FAUSTFLOAT", fHslider0)("int", fSampleRate)>)

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
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(256))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 2 Store = 0 Binop = 0 Mathop = 0 Numbers = 2 Declare = 2 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 27 Store = 4 Binop = 23 [ { Int(&) = 5 } { Int(+) = 3 } { Int(-) = 4 } { Int(<) = 1 } { Real(*) = 4 } { Real(+) = 4 } { Real(-) = 2 } ] Mathop = 9 [ { floorf = 1 } { max_f = 1 } { max_i = 3 } { min_f = 1 } { min_i = 3 } ] Numbers = 22 Declare = 6 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", BinopInst("*", Float(0.005f), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", Float(0.995f), LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(255))]))))
		DeclareVarInst("float", fRec2, kStack, FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
		DeclareVarInst("float", fRec1, kStack, BinopInst("*", Float(1e+02f), BinopInst("+", Float(1.0f), LoadVarInst(Address(fRec2, kStack)))))
		DeclareVarInst("int", iTemp1, kStack, CastInst("int", LoadVarInst(Address(fRec1, kStack))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("-", LoadVarInst(Address(fRec1, kStack)), FunCallInst("floorf", LoadVarInst(Address(fRec1, kStack)))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp1, kStack))))), Int32(255))]), BinopInst("*", LoadVarInst(Address(fTemp2, kStack)), BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp1, kStack)))))), Int32(255))]), LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp1, kStack))))), Int32(255))])))))))
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
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fRec0[256], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(256))
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
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", BinopInst("*", Float(0.005f), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", Float(0.995f), LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(255))]))))
			DeclareVarInst("float", fRec2, kStack, FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
			DeclareVarInst("float", fRec1, kStack, BinopInst("*", Float(1e+02f), BinopInst("+", Float(1.0f), LoadVarInst(Address(fRec2, kStack)))))
			DeclareVarInst("int", iTemp1, kStack, CastInst("int", LoadVarInst(Address(fRec1, kStack))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("-", LoadVarInst(Address(fRec1, kStack)), FunCallInst("floorf", LoadVarInst(Address(fRec1, kStack)))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp1, kStack))))), Int32(255))]), BinopInst("*", LoadVarInst(Address(fTemp2, kStack)), BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp1, kStack)))))), Int32(255))]), LoadVarInst(Address(fRec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp1, kStack))))), Int32(255))])))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 1028 bytes
Total heap size = 1036 bytes
Stack size in compute = 16 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 6 write = 1 ratio = 7
Field = fRec0 size = 256 size_bytes = 1024 read = 4 write = 1 ratio = 0.0195312
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            187
  eval() cache hits:       54 (28.877%)
  eval() cache misses:     133
  Loop detector calls:     133
  Stack detector calls:    133

--- Phase 3: Propagation ---
  propagate() calls:       172
  propagate() cache hits:  23 (13.3721%)
  propagate() cache misses:149

--- Box Type Computation ---
  getBoxType() calls:      348
  getBoxType() cache hits: 233 (66.954%)
  getBoxType() computed:   115

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       3

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           1536
  Trees reused (hash):     3257 (67.9533% reuse rate)
  Property set ops:        592
  Property get ops:        2152

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
