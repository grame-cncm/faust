======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("bargraph")
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
		RetInst(Int32(10))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= Compute control begin ==========

Instructions complexity : Load = 10 Store = 0 Binop = 0 Mathop = 0 Numbers = 10 Declare = 10 Cast = 0 Select = 0 Loop = 0

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
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 13 Store = 11 Binop = 2 [ { Int(+) = 1 } { Int(<) = 1 } ] Mathop = 0 Numbers = 12 Declare = 1 Cast = 10 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(0.0f)))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(1e+01f)))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(2e+01f)))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(3e+01f)))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(4e+01f)))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(0.0f)))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(10.5f)))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(21.0f)))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(31.5f)))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(42.0f)))
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
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(0.0f)))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(1e+01f)))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(2e+01f)))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(3e+01f)))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(4e+01f)))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(0.0f)))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(10.5f)))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(21.0f)))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(31.5f)))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(42.0f)))
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
Stack size in compute = 80 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
