======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("parseint")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(16))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= Compute control begin ==========

Instructions complexity : Load = 16 Store = 0 Binop = 0 Mathop = 0 Numbers = 16 Declare = 16 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output8, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", output9, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", output10, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", output11, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(11)]))
	DeclareVarInst("FAUSTFLOAT*", output12, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(12)]))
	DeclareVarInst("FAUSTFLOAT*", output13, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(13)]))
	DeclareVarInst("FAUSTFLOAT*", output14, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", output15, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(15)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 19 Store = 17 Binop = 2 [ { Int(+) = 1 } { Int(<) = 1 } ] Mathop = 0 Numbers = 18 Declare = 1 Cast = 16 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(10)))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-10)))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(2147483647)))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2147483647)))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2147483648)))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2147483648)))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2147483647)))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(2147483647)))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-1)))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(1)))
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(0)))
		StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(0)))
		StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(1)))
		StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-1)))
		StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(2)))
		StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2)))
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
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output8, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", output9, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", output10, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", output11, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(11)]))
	DeclareVarInst("FAUSTFLOAT*", output12, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(12)]))
	DeclareVarInst("FAUSTFLOAT*", output13, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(13)]))
	DeclareVarInst("FAUSTFLOAT*", output14, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", output15, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(15)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(10)))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-10)))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(2147483647)))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2147483647)))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2147483648)))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2147483648)))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2147483647)))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(2147483647)))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-1)))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(1)))
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(0)))
			StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(0)))
			StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(1)))
			StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-1)))
			StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(2)))
			StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(-2)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 0 bytes
Total heap size = 4 bytes
Stack size in compute = 128 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            33
  eval() cache hits:       6 (18.1818%)
  eval() cache misses:     27
  Loop detector calls:     27
  Stack detector calls:    27

--- Phase 3: Propagation ---
  propagate() calls:       31
  propagate() cache hits:  6 (19.3548%)
  propagate() cache misses:25

--- Box Type Computation ---
  getBoxType() calls:      61
  getBoxType() cache hits: 36 (59.0164%)
  getBoxType() computed:   25

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       1

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           145
  Trees reused (hash):     261 (64.2857% reuse rate)
  Property set ops:        119
  Property get ops:        254

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
