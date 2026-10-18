======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("NoiseMD")
	AddMetaDeclareInst(fVslider0, "style", "knob")
	AddVerticalSlider("Volume", fVslider0, 0.0697f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fVslider0)("int[2]", iIIR0)("int", fSampleRate)>)

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

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0697f)))
EndBlockInst

======= ResetUI end ==========

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

Instructions complexity : Load = 3 Store = 0 Binop = 1 [ { Real(*) = 1 } ] Mathop = 2 [ { max_f = 1 } { min_f = 1 } ] Numbers = 4 Declare = 3 Cast = 1 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow0, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 9 Store = 4 Binop = 5 [ { Int(*) = 1 } { Int(+) = 2 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 0 Numbers = 8 Declare = 2 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), CastInst("float", LoadVarInst(Address(iTemp0, kStack))))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
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
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("int", iIIR0[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0697f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow0, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), CastInst("float", LoadVarInst(Address(iTemp0, kStack))))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 4 bytes
Total heap size = 16 bytes
Stack size in compute = 16 bytes

======= Variable access in Control ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            25
  eval() cache hits:       1 (4%)
  eval() cache misses:     24
  Loop detector calls:     24
  Stack detector calls:    24

--- Phase 3: Propagation ---
  propagate() calls:       23
  propagate() cache hits:  0 (0%)
  propagate() cache misses:23

--- Box Type Computation ---
  getBoxType() calls:      45
  getBoxType() cache hits: 24 (53.3333%)
  getBoxType() computed:   21

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       1

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           403
  Trees reused (hash):     608 (60.1385% reuse rate)
  Property set ops:        149
  Property get ops:        296

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
