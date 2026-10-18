======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("select2")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("int", imydspWave0[4], kStaticStruct|kConst, Int32ArrayNumInst{1,0,0,0})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", imydspWave0_idx)("int[2]", iIIR0)("int[2]", iIIR1)("int", fSampleRate)>)

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
	StoreVarInst(Address(imydspWave0_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

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
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 1 Store = 0 Binop = 0 Mathop = 0 Numbers = 1 Declare = 1 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 15 Store = 7 Binop = 6 [ { Int(%) = 1 } { Int(+) = 4 } { Int(<) = 1 } ] Mathop = 0 Numbers = 14 Declare = 3 Cast = 1 Select = 1 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		DeclareVarInst("int", iTemp1, kStack, BinopInst("+", Int32(2), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp1, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(Address(imydspWave0, kStaticStruct)[LoadVarInst(Address(imydspWave0_idx, kStruct))]) LoadVarInst(Address(iTemp1, kStack)) LoadVarInst(Address(iTemp0, kStack)))))
		StoreVarInst(Address(imydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspWave0_idx, kStruct))), Int32(4)))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
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
	DeclareVarInst("int", imydspWave0[4], kStaticStruct|kConst, Int32ArrayNumInst{1,0,0,0})
	DeclareVarInst("int", imydspWave0_idx, kStruct)
	DeclareVarInst("int", iIIR0[2], kStruct)
	DeclareVarInst("int", iIIR1[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(imydspWave0_idx, kStruct), Int32(0))
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
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			DeclareVarInst("int", iTemp1, kStack, BinopInst("+", Int32(2), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp1, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(Address(imydspWave0, kStaticStruct)[LoadVarInst(Address(imydspWave0_idx, kStruct))]) LoadVarInst(Address(iTemp1, kStack)) LoadVarInst(Address(iTemp0, kStack)))))
			StoreVarInst(Address(imydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(imydspWave0_idx, kStruct))), Int32(4)))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 16 bytes
Heap size real = 0 bytes
Total heap size = 24 bytes
Stack size in compute = 8 bytes

======= Variable access in Control ==========

Field = imydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = imydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = imydspWave0_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = iIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = iIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            26
  eval() cache hits:       3 (11.5385%)
  eval() cache misses:     23
  Loop detector calls:     23
  Stack detector calls:    23

--- Phase 3: Propagation ---
  propagate() calls:       23
  propagate() cache hits:  3 (13.0435%)
  propagate() cache misses:20

--- Box Type Computation ---
  getBoxType() calls:      53
  getBoxType() cache hits: 35 (66.0377%)
  getBoxType() computed:   18

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       2

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           279
  Trees reused (hash):     490 (63.7191% reuse rate)
  Property set ops:        116
  Property get ops:        331

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
