======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", fmydspSIG0Wave0[8], kStaticStruct|kConst, FloatArrayNumInst{0.0f,0.5f,1.0f,0.5f,0.0f,-0.5f,-1.0f,-0.5f})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int", fmydspSIG0Wave0_idx)>)

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
	StoreVarInst(Address(fmydspSIG0Wave0_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 3 Binop = 4 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } ] Mathop = 0 Numbers = 4 Declare = 1 Cast = 0 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], LoadVarInst(Address(fmydspSIG0Wave0, kStaticStruct)[LoadVarInst(Address(fmydspSIG0Wave0_idx, kStruct))]))
		StoreVarInst(Address(fmydspSIG0Wave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspSIG0Wave0_idx, kStruct))), Int32(8)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("table1")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", ftbl0mydspSIG0[8], kStaticStruct)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", fmydspWave0[8], kStaticStruct|kConst, FloatArrayNumInst{1e+01f,10.5f,11.0f,10.5f,1e+01f,-10.5f,-11.0f,-10.5f})
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int[2]", iIIR0)("float[8]", ftbl1)("int", fmydspWave0_idx)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(8), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(8), LoadVarInst(Address(ftbl1, kStruct|kReference|kMutable))))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
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
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 2 Store = 0 Binop = 0 Mathop = 0 Numbers = 2 Declare = 2 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 17 Store = 7 Binop = 6 [ { Int(%) = 2 } { Int(+) = 3 } { Int(<) = 1 } ] Mathop = 2 [ { max_i = 1 } { min_i = 1 } ] Numbers = 12 Declare = 3 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		DeclareVarInst("int", iTemp1, kStack, FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", LoadVarInst(Address(iTemp0, kStack)), Int32(8)), Int32(7))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[LoadVarInst(Address(iTemp1, kStack))])))
		StoreVarInst(Address(ftbl1, kStruct)[LoadVarInst(Address(iTemp1, kStack))], LoadVarInst(Address(fmydspWave0, kStaticStruct)[LoadVarInst(Address(fmydspWave0_idx, kStruct))]))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl1, kStruct)[LoadVarInst(Address(iTemp1, kStack))])))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(8)))
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
	DeclareVarInst("float", ftbl0mydspSIG0[8], kStaticStruct)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", fmydspWave0[8], kStaticStruct|kConst, FloatArrayNumInst{1e+01f,10.5f,11.0f,10.5f,1e+01f,-10.5f,-11.0f,-10.5f})
	DeclareVarInst("int", iIIR0[2], kStruct)
	DeclareVarInst("float", ftbl1[8], kStruct)
	DeclareVarInst("int", fmydspWave0_idx, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(8), LoadVarInst(Address(ftbl1, kStruct|kReference|kMutable))))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(8), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("float", fmydspSIG0Wave0[8], kStaticStruct|kConst, FloatArrayNumInst{0.0f,0.5f,1.0f,0.5f,0.0f,-0.5f,-1.0f,-0.5f})
	DeclareVarInst("int", fmydspSIG0Wave0_idx, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fmydspSIG0Wave0_idx, kStruct), Int32(0))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], LoadVarInst(Address(fmydspSIG0Wave0, kStaticStruct)[LoadVarInst(Address(fmydspSIG0Wave0_idx, kStruct))]))
			StoreVarInst(Address(fmydspSIG0Wave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspSIG0Wave0_idx, kStruct))), Int32(8)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			DeclareVarInst("int", iTemp1, kStack, FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("%", LoadVarInst(Address(iTemp0, kStack)), Int32(8)), Int32(7))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[LoadVarInst(Address(iTemp1, kStack))])))
			StoreVarInst(Address(ftbl1, kStruct)[LoadVarInst(Address(iTemp1, kStack))], LoadVarInst(Address(fmydspWave0, kStaticStruct)[LoadVarInst(Address(fmydspWave0_idx, kStruct))]))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl1, kStruct)[LoadVarInst(Address(iTemp1, kStack))])))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(8)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 32 bytes
Total heap size = 52 bytes
Stack size in compute = 16 bytes

======= Variable access in Control ==========

Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = ftbl1 size = 8 size_bytes = 32 read = 0 write = 0 ratio = 0
Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = ftbl1 size = 8 size_bytes = 32 read = 0 write = 0 ratio = 0
Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = iIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = ftbl1 size = 8 size_bytes = 32 read = 1 write = 1 ratio = 0.25
Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            45
  eval() cache hits:       7 (15.5556%)
  eval() cache misses:     38
  Loop detector calls:     38
  Stack detector calls:    38

--- Phase 3: Propagation ---
  propagate() calls:       33
  propagate() cache hits:  5 (15.1515%)
  propagate() cache misses:28

--- Box Type Computation ---
  getBoxType() calls:      67
  getBoxType() cache hits: 42 (62.6866%)
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
  Trees created:           385
  Trees reused (hash):     688 (64.1193% reuse rate)
  Property set ops:        226
  Property get ops:        465

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
