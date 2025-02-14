======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("sound")
	AddSoundfile("son", "{'sound1';'sound2'}", &fSoundfile0)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("Soundfile*", fSoundfile0)("int", IOTA0)("int[2]", iVec0SI)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(4))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	IfInst 
		BinopInst("==", CastInst("uintptr_t", LoadVarInst(Address(fSoundfile0, kStruct))), Int64(0))
		BlockInst 
			StoreVarInst(Address(fSoundfile0, kStruct), LoadVarInst(Address(defaultsound, kGlobal)))
		EndBlockInst
	EndIfInst
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SI, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Allocate begin ==========

BlockInst 
	StoreVarInst(Address(fSoundfile0, kStruct), Int64(0))
EndBlockInst

======= Allocate end ==========

======= Compute control begin ==========

Instructions complexity : Load = 19 Store = 0 Binop = 1 [ { Int(+) = 1 } ] Mathop = 0 Numbers = 19 Declare = 19 Cast = 4 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("Soundfile*", fSoundfile0ca, kStack, LoadVarInst(Address(fSoundfile0, kStruct)))
	DeclareVarInst("int*", fSoundfile0ca_le0, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fLength))
	DeclareVarInst("int", iSlow0BI, kStack, BinopInst("+", LoadVarInst(Address(fSoundfile0ca_le0, kStack)[Int32(0)]), Int32(-1)))
	DeclareVarInst("int*", fSoundfile0ca_of0, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fOffset))
	DeclareVarInst("float**", fSoundfile0ca_bu0, kStack, CastInst("float**", LoadVarInst(Address(fSoundfile0ca, kStack)->fBuffers)))
	DeclareVarInst("float*", fSoundfile0ca_bu_ch0, kStack, LoadVarInst(Address(fSoundfile0ca_bu0, kStack)[Int32(0)]))
	DeclareVarInst("int*", fSoundfile0ca_of1, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fOffset))
	DeclareVarInst("float**", fSoundfile0ca_bu1, kStack, CastInst("float**", LoadVarInst(Address(fSoundfile0ca, kStack)->fBuffers)))
	DeclareVarInst("float*", fSoundfile0ca_bu_ch1, kStack, LoadVarInst(Address(fSoundfile0ca_bu1, kStack)[Int32(1)]))
	DeclareVarInst("int*", fSoundfile0ca_of2, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fOffset))
	DeclareVarInst("float**", fSoundfile0ca_bu2, kStack, CastInst("float**", LoadVarInst(Address(fSoundfile0ca, kStack)->fBuffers)))
	DeclareVarInst("float*", fSoundfile0ca_bu_ch2, kStack, LoadVarInst(Address(fSoundfile0ca_bu2, kStack)[Int32(2)]))
	DeclareVarInst("int*", fSoundfile0ca_of3, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fOffset))
	DeclareVarInst("float**", fSoundfile0ca_bu3, kStack, CastInst("float**", LoadVarInst(Address(fSoundfile0ca, kStack)->fBuffers)))
	DeclareVarInst("float*", fSoundfile0ca_bu_ch3, kStack, LoadVarInst(Address(fSoundfile0ca_bu3, kStack)[Int32(3)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 26 Store = 7 Binop = 12 [ { Int(&) = 3 } { Int(+) = 7 } { Int(-) = 1 } { Int(<) = 1 } ] Mathop = 2 [ { max_i = 1 } { min_i = 1 } ] Numbers = 13 Declare = 2 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
		DeclareVarInst("int", iTemp0SI, kStack, FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(iSlow0BI, kStack)))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSoundfile0ca_bu_ch0, kStack)[BinopInst("+", LoadVarInst(Address(fSoundfile0ca_of0, kStack)[Int32(0)]), LoadVarInst(Address(iTemp0SI, kStack)))])))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSoundfile0ca_bu_ch1, kStack)[BinopInst("+", LoadVarInst(Address(fSoundfile0ca_of1, kStack)[Int32(0)]), LoadVarInst(Address(iTemp0SI, kStack)))])))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSoundfile0ca_bu_ch2, kStack)[BinopInst("+", LoadVarInst(Address(fSoundfile0ca_of2, kStack)[Int32(0)]), LoadVarInst(Address(iTemp0SI, kStack)))])))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSoundfile0ca_bu_ch3, kStack)[BinopInst("+", LoadVarInst(Address(fSoundfile0ca_of3, kStack)[Int32(0)]), LoadVarInst(Address(iTemp0SI, kStack)))])))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst
BlockInst 
	StoreVarInst(Address(fSoundfile0, kStruct), LoadVarInst(Address(fSoundfile0ca, kStack)))
EndBlockInst

======= Compute DSP end ==========

======= Post compute DSP begin ==========

BlockInst 
	StoreVarInst(Address(fSoundfile0, kStruct), LoadVarInst(Address(fSoundfile0ca, kStack)))
EndBlockInst

======= Post compute DSP end ==========

======= Flatten FIR begin ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("Soundfile*", fSoundfile0, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay iVec0SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec0SI[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	IfInst 
		BinopInst("==", CastInst("uintptr_t", LoadVarInst(Address(fSoundfile0, kStruct))), Int64(0))
		BlockInst 
			StoreVarInst(Address(fSoundfile0, kStruct), LoadVarInst(Address(defaultsound, kGlobal)))
		EndBlockInst
	EndIfInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SI, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("Soundfile*", fSoundfile0ca, kStack, LoadVarInst(Address(fSoundfile0, kStruct)))
	DeclareVarInst("int*", fSoundfile0ca_le0, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fLength))
	DeclareVarInst("int", iSlow0BI, kStack, BinopInst("+", LoadVarInst(Address(fSoundfile0ca_le0, kStack)[Int32(0)]), Int32(-1)))
	DeclareVarInst("int*", fSoundfile0ca_of0, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fOffset))
	DeclareVarInst("float**", fSoundfile0ca_bu0, kStack, CastInst("float**", LoadVarInst(Address(fSoundfile0ca, kStack)->fBuffers)))
	DeclareVarInst("float*", fSoundfile0ca_bu_ch0, kStack, LoadVarInst(Address(fSoundfile0ca_bu0, kStack)[Int32(0)]))
	DeclareVarInst("int*", fSoundfile0ca_of1, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fOffset))
	DeclareVarInst("float**", fSoundfile0ca_bu1, kStack, CastInst("float**", LoadVarInst(Address(fSoundfile0ca, kStack)->fBuffers)))
	DeclareVarInst("float*", fSoundfile0ca_bu_ch1, kStack, LoadVarInst(Address(fSoundfile0ca_bu1, kStack)[Int32(1)]))
	DeclareVarInst("int*", fSoundfile0ca_of2, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fOffset))
	DeclareVarInst("float**", fSoundfile0ca_bu2, kStack, CastInst("float**", LoadVarInst(Address(fSoundfile0ca, kStack)->fBuffers)))
	DeclareVarInst("float*", fSoundfile0ca_bu_ch2, kStack, LoadVarInst(Address(fSoundfile0ca_bu2, kStack)[Int32(2)]))
	DeclareVarInst("int*", fSoundfile0ca_of3, kStack, LoadVarInst(Address(fSoundfile0ca, kStack)->fOffset))
	DeclareVarInst("float**", fSoundfile0ca_bu3, kStack, CastInst("float**", LoadVarInst(Address(fSoundfile0ca, kStack)->fBuffers)))
	DeclareVarInst("float*", fSoundfile0ca_bu_ch3, kStack, LoadVarInst(Address(fSoundfile0ca_bu3, kStack)[Int32(3)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
			DeclareVarInst("int", iTemp0SI, kStack, FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(iSlow0BI, kStack)))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSoundfile0ca_bu_ch0, kStack)[BinopInst("+", LoadVarInst(Address(fSoundfile0ca_of0, kStack)[Int32(0)]), LoadVarInst(Address(iTemp0SI, kStack)))])))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSoundfile0ca_bu_ch1, kStack)[BinopInst("+", LoadVarInst(Address(fSoundfile0ca_of1, kStack)[Int32(0)]), LoadVarInst(Address(iTemp0SI, kStack)))])))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSoundfile0ca_bu_ch2, kStack)[BinopInst("+", LoadVarInst(Address(fSoundfile0ca_of2, kStack)[Int32(0)]), LoadVarInst(Address(iTemp0SI, kStack)))])))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSoundfile0ca_bu_ch3, kStack)[BinopInst("+", LoadVarInst(Address(fSoundfile0ca_of3, kStack)[Int32(0)]), LoadVarInst(Address(iTemp0SI, kStack)))])))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	StoreVarInst(Address(fSoundfile0, kStruct), LoadVarInst(Address(fSoundfile0ca, kStack)))
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 8 bytes
Total heap size = 24 bytes
Stack size in compute = 148 bytes

======= Variable access in Control ==========

Field = fSoundfile0 size = 1 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSoundfile0 size = 1 size_bytes = 8 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSoundfile0 size = 1 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 4 write = 1 ratio = 5
Field = iVec0SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
