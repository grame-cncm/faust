======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Pitch Shifter")
	AddHorizontalSlider("shift (semitones)", fHslider1, 0.0f, -12.0f, 12.0f, 0.1f)
	AddHorizontalSlider("window (samples)", fHslider0, 1e+03f, 5e+01f, 1e+04f, 1.0f)
	AddHorizontalSlider("xfade (samples)", fHslider2, 1e+01f, 1.0f, 1e+04f, 1.0f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[32768]", fVec0)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("float[2]", fRec0)("FAUSTFLOAT", fHslider2)("int", fSampleRate)>)

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
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(1e+03f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(1e+01f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(32768))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 7 Store = 0 Binop = 4 [ { Real(*) = 1 } { Real(+) = 1 } { Real(-) = 1 } { Real(/) = 1 } ] Mathop = 7 [ { max_f = 3 } { min_f = 3 } { powf = 1 } ] Numbers = 12 Declare = 6 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(5e+01f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), FunCallInst("max_f", Float(-12.0f), FunCallInst("min_f", Float(12.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("-", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 46 Store = 6 Binop = 36 [ { Int(&) = 9 } { Int(+) = 4 } { Int(-) = 4 } { Int(<) = 1 } { Real(*) = 6 } { Real(+) = 7 } { Real(-) = 5 } ] Mathop = 2 [ { fmodf = 1 } { min_f = 1 } ] Numbers = 26 Declare = 10 Cast = 6 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], LoadVarInst(Address(fTemp0, kStack)))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), LoadVarInst(Address(fSlow0, kStack))))
		DeclareVarInst("int", iTemp1, kStack, CastInst("int", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("-", LoadVarInst(Address(fSlow0, kStack)), CastInst("float", LoadVarInst(Address(iTemp1, kStack)))))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp1, kStack)), Int32(65535))), Int32(32767))]), BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp3, kStack))), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp1, kStack))), Int32(65535))), Int32(32767))]))))
		DeclareVarInst("int", iTemp5, kStack, CastInst("int", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(iTemp5, kStack))))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp5, kStack)), Int32(65535))), Int32(32767))]), BinopInst("+", LoadVarInst(Address(fTemp6, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp6, kStack))), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp5, kStack))), Int32(65535))), Int32(32767))]))))
		DeclareVarInst("float", fTemp8, kStack, FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), Float(1.0f)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp7, kStack)), LoadVarInst(Address(fTemp4, kStack)))))))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[32768], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(1e+03f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(1e+01f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(32768))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(5e+01f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), FunCallInst("max_f", Float(-12.0f), FunCallInst("min_f", Float(12.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("-", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], LoadVarInst(Address(fTemp0, kStack)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), LoadVarInst(Address(fSlow0, kStack))))
			DeclareVarInst("int", iTemp1, kStack, CastInst("int", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("-", LoadVarInst(Address(fSlow0, kStack)), CastInst("float", LoadVarInst(Address(iTemp1, kStack)))))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp1, kStack)), Int32(65535))), Int32(32767))]), BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp3, kStack))), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp1, kStack))), Int32(65535))), Int32(32767))]))))
			DeclareVarInst("int", iTemp5, kStack, CastInst("int", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(iTemp5, kStack))))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp5, kStack)), Int32(65535))), Int32(32767))]), BinopInst("+", LoadVarInst(Address(fTemp6, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp6, kStack))), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp5, kStack))), Int32(65535))), Int32(32767))]))))
			DeclareVarInst("float", fTemp8, kStack, FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), Float(1.0f)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp7, kStack)), LoadVarInst(Address(fTemp4, kStack)))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 131092 bytes
Total heap size = 131100 bytes
Stack size in compute = 32 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 6 write = 1 ratio = 7
Field = fVec0 size = 32768 size_bytes = 131072 read = 4 write = 1 ratio = 0.000152588
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 8 write = 2 ratio = 5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            641
  eval() cache hits:       123 (19.1888%)
  eval() cache misses:     518
  Loop detector calls:     518
  Stack detector calls:    518

--- Phase 3: Propagation ---
  propagate() calls:       306
  propagate() cache hits:  121 (39.5425%)
  propagate() cache misses:185

--- Box Type Computation ---
  getBoxType() calls:      479
  getBoxType() cache hits: 367 (76.618%)
  getBoxType() computed:   112

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       28

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           5898
  Trees reused (hash):     12098 (67.2261% reuse rate)
  Property set ops:        2718
  Property get ops:        2813

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
