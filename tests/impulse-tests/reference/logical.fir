======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("logical")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(12))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(6))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= Compute control begin ==========

Instructions complexity : Load = 18 Store = 0 Binop = 0 Mathop = 0 Numbers = 18 Declare = 18 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", input8, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", input9, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", input10, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", input11, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(11)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 33 Store = 7 Binop = 20 [ { Int(&) = 2 } { Int(+) = 1 } { Int(<) = 1 } { Int(^) = 2 } { Int(|) = 2 } { Real(*) = 12 } ] Mathop = 24 [ { max_f = 12 } { min_f = 12 } ] Numbers = 44 Declare = 1 Cast = 30 Select = 3 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("|", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("^", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Select2Inst(BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))) Int32(200) Int32(100))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Select2Inst(BinopInst("|", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))) Int32(20) Int32(10))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Select2Inst(BinopInst("^", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))) Int32(2) Int32(1))))
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
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", input8, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", input9, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", input10, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", input11, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(11)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("|", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("^", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Select2Inst(BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))) Int32(200) Int32(100))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Select2Inst(BinopInst("|", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))) Int32(20) Int32(10))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Select2Inst(BinopInst("^", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(12345.0f), CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(67895.0f), CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))) Int32(2) Int32(1))))
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
Stack size in compute = 144 bytes

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
  eval() calls:            51
  eval() cache hits:       10 (19.6078%)
  eval() cache misses:     41
  Loop detector calls:     41
  Stack detector calls:    41

--- Phase 3: Propagation ---
  propagate() calls:       125
  propagate() cache hits:  10 (8%)
  propagate() cache misses:115

--- Box Type Computation ---
  getBoxType() calls:      189
  getBoxType() cache hits: 150 (79.3651%)
  getBoxType() computed:   39

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       1

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           562
  Trees reused (hash):     1684 (74.9777% reuse rate)
  Property set ops:        472
  Property get ops:        1298

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
