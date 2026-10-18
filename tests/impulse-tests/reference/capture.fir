======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Audio Capture")
	AddButtonInst("Capture"fButton0)
	AddHorizontalSlider("level (db)", fHslider0, 0.0f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fButton0)("int[2]", iVec0)("int", IOTA0)("float[524288]", fVec1)("int[2]", iRec1)("float[2]", fRec0)("FAUSTFLOAT", fHslider0)("float[2]", fIIR0)("int", fSampleRate)>)

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
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(524288))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 4 Store = 0 Binop = 2 [ { Real(*) = 1 } { Real(>) = 1 } ] Mathop = 3 [ { max_f = 1 } { min_f = 1 } { powf = 1 } ] Numbers = 7 Declare = 4 Cast = 4 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("int", iSlow0, kStack, CastInst("int", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton0, kStruct))), Float(0.0f)))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-96.0f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 27 Store = 12 Binop = 16 [ { Int(&) = 3 } { Int(*) = 1 } { Int(+) = 4 } { Int(-) = 2 } { Int(<) = 1 } { Int(<=) = 1 } { Real(*) = 3 } { Real(+) = 1 } ] Mathop = 0 Numbers = 28 Declare = 2 Cast = 2 Select = 1 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], LoadVarInst(Address(iSlow0, kStack)))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], Select2Inst(LoadVarInst(Address(iSlow0, kStack)) CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])) LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(iRec1, kStruct)[Int32(0)], BinopInst("*", BinopInst("+", LoadVarInst(Address(iSlow0, kStack)), LoadVarInst(Address(iRec1, kStruct)[Int32(1)])), BinopInst("<=", BinopInst("-", LoadVarInst(Address(iSlow0, kStack)), LoadVarInst(Address(iVec0, kStruct)[Int32(1)])), Int32(0))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(-1), LoadVarInst(Address(iRec1, kStruct)[Int32(0)])), Int32(524287))), Int32(524287))]))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp0, kStack))))))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(iRec1, kStruct)[Int32(1)], LoadVarInst(Address(iRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec1[524288], kStruct)
	DeclareVarInst("int", iRec1[2], kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("float", fIIR0[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(524288))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("int", iSlow0, kStack, CastInst("int", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton0, kStruct))), Float(0.0f)))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-96.0f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], LoadVarInst(Address(iSlow0, kStack)))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], Select2Inst(LoadVarInst(Address(iSlow0, kStack)) CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])) LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(iRec1, kStruct)[Int32(0)], BinopInst("*", BinopInst("+", LoadVarInst(Address(iSlow0, kStack)), LoadVarInst(Address(iRec1, kStruct)[Int32(1)])), BinopInst("<=", BinopInst("-", LoadVarInst(Address(iSlow0, kStack)), LoadVarInst(Address(iVec0, kStruct)[Int32(1)])), Int32(0))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(-1), LoadVarInst(Address(iRec1, kStruct)[Int32(0)])), Int32(524287))), Int32(524287))]))
			DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp0, kStack))))))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(iRec1, kStruct)[Int32(1)], LoadVarInst(Address(iRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 16 bytes
Heap size real = 2097176 bytes
Total heap size = 2097200 bytes
Stack size in compute = 24 bytes

======= Variable access in Control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = iRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = iRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = IOTA0 size = 1 size_bytes = 4 read = 3 write = 1 ratio = 4
Field = fVec1 size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = iRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            180
  eval() cache hits:       25 (13.8889%)
  eval() cache misses:     155
  Loop detector calls:     155
  Stack detector calls:    155

--- Phase 3: Propagation ---
  propagate() calls:       126
  propagate() cache hits:  9 (7.14286%)
  propagate() cache misses:117

--- Box Type Computation ---
  getBoxType() calls:      245
  getBoxType() cache hits: 164 (66.9388%)
  getBoxType() computed:   81

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       6

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           4925
  Trees reused (hash):     10841 (68.7619% reuse rate)
  Property set ops:        2530
  Property get ops:        2065

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
