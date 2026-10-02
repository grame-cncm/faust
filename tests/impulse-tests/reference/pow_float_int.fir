======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("pow_float_int")
	AddHorizontalSlider("n", fHslider1, 5e+04f, 0.0f, 5e+04f, 1.0f)
	AddHorizontalSlider("x", fHslider0, 0.6f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("int", "mydsp_faustpower2_i", "int", value_i)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_i, kFunArgs)), LoadVarInst(Address(value_i, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int", fSampleRate)>)

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

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.6f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(5e+04f)))
EndBlockInst

======= ResetUI end ==========

======= Compute control begin ==========

Instructions complexity : Load = 4 Store = 0 Binop = 0 Mathop = 2 [ { mydsp_faustpower2_f = 1 } { mydsp_faustpower2_i = 1 } ] Numbers = 2 Declare = 4 Cast = 4 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", FunCallInst("mydsp_faustpower2_i", CastInst("int", CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 3 Binop = 2 [ { Int(+) = 1 } { Int(<) = 1 } ] Mathop = 0 Numbers = 2 Declare = 1 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow0, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow1, kStack))))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("int", "mydsp_faustpower2_i", "int", value_i)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_i, kFunArgs)), LoadVarInst(Address(value_i, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.6f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(5e+04f)))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", FunCallInst("mydsp_faustpower2_i", CastInst("int", CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow0, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow1, kStack))))
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
Stack size in compute = 24 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            29
  eval() cache hits:       6 (20.6897%)
  eval() cache misses:     23
  Loop detector calls:     23
  Stack detector calls:    23

--- Phase 3: Propagation ---
  propagate() calls:       23
  propagate() cache hits:  2 (8.69565%)
  propagate() cache misses:21

--- Box Type Computation ---
  getBoxType() calls:      41
  getBoxType() cache hits: 24 (58.5366%)
  getBoxType() computed:   17

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       1

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           221
  Trees reused (hash):     1034 (82.3904% reuse rate)
  Property set ops:        125
  Property get ops:        291

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
