======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("bs")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("float[2]", fRec0)("int", fSampleRate)>)

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

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 2 Store = 0 Binop = 1 [ { Real(/) = 1 } ] Mathop = 0 Numbers = 2 Declare = 2 Cast = 1 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("/", Float(1e+01f), CastInst("float", LoadVarInst(Address(count, kFunArgs)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 14 Store = 4 Binop = 6 [ { Int(+) = 1 } { Int(<) = 1 } { Real(+) = 1 } { Real(-) = 1 } { Real(<) = 1 } { Real(>) = 1 } ] Mathop = 0 Numbers = 11 Declare = 3 Cast = 1 Select = 2 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow0, kStack))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp0, kStack)), Float(1e+01f)) LoadVarInst(Address(fTemp0, kStack)) Select2Inst(BinopInst(">", LoadVarInst(Address(fTemp1, kStack)), Float(1e+01f)) LoadVarInst(Address(fTemp1, kStack)) Float(1e+01f))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
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
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("/", Float(1e+01f), CastInst("float", LoadVarInst(Address(count, kFunArgs)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow0, kStack))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp0, kStack)), Float(1e+01f)) LoadVarInst(Address(fTemp0, kStack)) Select2Inst(BinopInst(">", LoadVarInst(Address(fTemp1, kStack)), Float(1e+01f)) LoadVarInst(Address(fTemp1, kStack)) Float(1e+01f))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 8 bytes
Total heap size = 12 bytes
Stack size in compute = 12 bytes

======= Variable access in Control ==========

Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fRec0 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            150
  eval() cache hits:       26 (17.3333%)
  eval() cache misses:     124
  Loop detector calls:     124
  Stack detector calls:    124

--- Phase 3: Propagation ---
  propagate() calls:       68
  propagate() cache hits:  16 (23.5294%)
  propagate() cache misses:52

--- Box Type Computation ---
  getBoxType() calls:      114
  getBoxType() cache hits: 83 (72.807%)
  getBoxType() computed:   31

--- Environment Operations ---
  Environment lookups:     3
  Average lookup depth:    0
  Env layers pushed:       13

--- Pattern Matching ---
  build automaton calls:        1
  build total time (ms):        0.007458
  build avg time (ms):          0.007458
  apply calls:                  3
  apply total time (ms):        0.013333
  apply avg time (ms):          0.00444433

--- Tree Operations ---
  Trees created:           660
  Trees reused (hash):     1311 (66.5145% reuse rate)
  Property set ops:        289
  Property get ops:        1030

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
