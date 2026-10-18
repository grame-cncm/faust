======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("pow")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", fmydspWave0[4], kStaticStruct|kConst, FloatArrayNumInst{0.1f,0.56f,1.3f,8.9f})
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
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

DeclareStructTypeInst(StructType<"mydsp",("int", fmydspWave0_idx)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(14))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Compute control begin ==========

Instructions complexity : Load = 14 Store = 0 Binop = 0 Mathop = 0 Numbers = 14 Declare = 14 Cast = 0 Select = 0 Loop = 0

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
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 37 Store = 16 Binop = 11 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } { Real(*) = 7 } ] Mathop = 9 [ { mydsp_faustpower2_f = 3 } { mydsp_faustpower2_i = 1 } { powf = 3 } { sqrtf = 2 } ] Numbers = 16 Declare = 7 Cast = 16 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, LoadVarInst(Address(fmydspWave0, kStaticStruct)[LoadVarInst(Address(fmydspWave0_idx, kStruct))]))
		DeclareVarInst("float", fTemp1, kStack, FunCallInst("sqrtf", BinopInst("*", Float(3.0f), LoadVarInst(Address(fTemp0, kStack)))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp1, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("sqrtf", LoadVarInst(Address(fTemp1, kStack)))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("*", Float(4.0f), LoadVarInst(Address(fTemp0, kStack))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", LoadVarInst(Address(fTemp2, kStack)), Float(0.125f))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", LoadVarInst(Address(fTemp2, kStack)), Float(0.0625f))))
		DeclareVarInst("float", fTemp3, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(5.0f), LoadVarInst(Address(fTemp0, kStack)))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
		DeclareVarInst("int", iTemp4, kStack, CastInst("int", BinopInst("*", Float(6.0f), LoadVarInst(Address(fTemp0, kStack)))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower2_i", LoadVarInst(Address(iTemp4, kStack)))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(iTemp4, kStack))))))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("*", Float(7.0f), LoadVarInst(Address(fTemp0, kStack))))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", LoadVarInst(Address(fTemp5, kStack)), Float(2.0001f))))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(1.0f)))
		StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(8.0f), LoadVarInst(Address(fTemp0, kStack)))))
		StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(1.0f)))
		StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(9.0f), LoadVarInst(Address(fTemp0, kStack)))))
		StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(4)))
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
	DeclareVarInst("float", fmydspWave0[4], kStaticStruct|kConst, FloatArrayNumInst{0.1f,0.56f,1.3f,8.9f})
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
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
	DeclareVarInst("int", fmydspWave0_idx, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
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
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, LoadVarInst(Address(fmydspWave0, kStaticStruct)[LoadVarInst(Address(fmydspWave0_idx, kStruct))]))
			DeclareVarInst("float", fTemp1, kStack, FunCallInst("sqrtf", BinopInst("*", Float(3.0f), LoadVarInst(Address(fTemp0, kStack)))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp1, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("sqrtf", LoadVarInst(Address(fTemp1, kStack)))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("*", Float(4.0f), LoadVarInst(Address(fTemp0, kStack))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", LoadVarInst(Address(fTemp2, kStack)), Float(0.125f))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", LoadVarInst(Address(fTemp2, kStack)), Float(0.0625f))))
			DeclareVarInst("float", fTemp3, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(5.0f), LoadVarInst(Address(fTemp0, kStack)))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp3, kStack))))
			DeclareVarInst("int", iTemp4, kStack, CastInst("int", BinopInst("*", Float(6.0f), LoadVarInst(Address(fTemp0, kStack)))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower2_i", LoadVarInst(Address(iTemp4, kStack)))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(iTemp4, kStack))))))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("*", Float(7.0f), LoadVarInst(Address(fTemp0, kStack))))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", LoadVarInst(Address(fTemp5, kStack)), Float(2.0001f))))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(1.0f)))
			StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(8.0f), LoadVarInst(Address(fTemp0, kStack)))))
			StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(1.0f)))
			StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(9.0f), LoadVarInst(Address(fTemp0, kStack)))))
			StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(4)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 0 bytes
Total heap size = 8 bytes
Stack size in compute = 112 bytes

======= Variable access in Control ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            107
  eval() cache hits:       34 (31.7757%)
  eval() cache misses:     73
  Loop detector calls:     73
  Stack detector calls:    73

--- Phase 3: Propagation ---
  propagate() calls:       117
  propagate() cache hits:  15 (12.8205%)
  propagate() cache misses:102

--- Box Type Computation ---
  getBoxType() calls:      277
  getBoxType() cache hits: 194 (70.0361%)
  getBoxType() computed:   83

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       1

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           561
  Trees reused (hash):     1263 (69.2434% reuse rate)
  Property set ops:        376
  Property get ops:        939

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
