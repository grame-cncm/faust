======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("bargraph")
	AddVerticalBargraph("bar0", fVbargraph5, 0.0f, 1e+01f)
	AddVerticalBargraph("bar1", fVbargraph6, 0.0f, 1e+01f)
	AddVerticalBargraph("bar2", fVbargraph7, 0.0f, 1e+01f)
	AddVerticalBargraph("bar3", fVbargraph8, 0.0f, 1e+01f)
	AddVerticalBargraph("bar4", fVbargraph9, 0.0f, 1e+01f)
	AddVerticalBargraph("foo0", fVbargraph0, 0.0f, 1e+01f)
	AddVerticalBargraph("foo1", fVbargraph1, 0.0f, 1e+01f)
	AddVerticalBargraph("foo2", fVbargraph2, 0.0f, 1e+01f)
	AddVerticalBargraph("foo3", fVbargraph3, 0.0f, 1e+01f)
	AddVerticalBargraph("foo4", fVbargraph4, 0.0f, 1e+01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fVbargraph0)("FAUSTFLOAT", fVbargraph1)("FAUSTFLOAT", fVbargraph2)("FAUSTFLOAT", fVbargraph3)("FAUSTFLOAT", fVbargraph4)("FAUSTFLOAT", fVbargraph5)("FAUSTFLOAT", fVbargraph6)("FAUSTFLOAT", fVbargraph7)("FAUSTFLOAT", fVbargraph8)("FAUSTFLOAT", fVbargraph9)("int", fSampleRate)>)

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

Instructions complexity : Load = 20 Store = 10 Binop = 0 Mathop = 0 Numbers = 20 Declare = 20 Cast = 10 Select = 0 Loop = 0

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
	StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	DeclareVarInst("float", fSlow0, kStack, LoadVarInst(Address(fVbargraph0, kStruct)))
	StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", Float(1e+01f)))
	DeclareVarInst("float", fSlow1, kStack, LoadVarInst(Address(fVbargraph1, kStruct)))
	StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", Float(2e+01f)))
	DeclareVarInst("float", fSlow2, kStack, LoadVarInst(Address(fVbargraph2, kStruct)))
	StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", Float(3e+01f)))
	DeclareVarInst("float", fSlow3, kStack, LoadVarInst(Address(fVbargraph3, kStruct)))
	StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", Float(4e+01f)))
	DeclareVarInst("float", fSlow4, kStack, LoadVarInst(Address(fVbargraph4, kStruct)))
	StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	DeclareVarInst("float", fSlow5, kStack, LoadVarInst(Address(fVbargraph5, kStruct)))
	StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", Float(10.5f)))
	DeclareVarInst("float", fSlow6, kStack, LoadVarInst(Address(fVbargraph6, kStruct)))
	StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", Float(21.0f)))
	DeclareVarInst("float", fSlow7, kStack, LoadVarInst(Address(fVbargraph7, kStruct)))
	StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", Float(31.5f)))
	DeclareVarInst("float", fSlow8, kStack, LoadVarInst(Address(fVbargraph8, kStruct)))
	StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", Float(42.0f)))
	DeclareVarInst("float", fSlow9, kStack, LoadVarInst(Address(fVbargraph9, kStruct)))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 23 Store = 11 Binop = 2 [ { Int(+) = 1 } { Int(<) = 1 } ] Mathop = 0 Numbers = 2 Declare = 1 Cast = 10 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow0, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow1, kStack))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow2, kStack))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow3, kStack))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow4, kStack))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow6, kStack))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow7, kStack))))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow8, kStack))))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow9, kStack))))
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
	DeclareVarInst("FAUSTFLOAT", fVbargraph0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph9, kStruct)
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
	StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	DeclareVarInst("float", fSlow0, kStack, LoadVarInst(Address(fVbargraph0, kStruct)))
	StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", Float(1e+01f)))
	DeclareVarInst("float", fSlow1, kStack, LoadVarInst(Address(fVbargraph1, kStruct)))
	StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", Float(2e+01f)))
	DeclareVarInst("float", fSlow2, kStack, LoadVarInst(Address(fVbargraph2, kStruct)))
	StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", Float(3e+01f)))
	DeclareVarInst("float", fSlow3, kStack, LoadVarInst(Address(fVbargraph3, kStruct)))
	StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", Float(4e+01f)))
	DeclareVarInst("float", fSlow4, kStack, LoadVarInst(Address(fVbargraph4, kStruct)))
	StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	DeclareVarInst("float", fSlow5, kStack, LoadVarInst(Address(fVbargraph5, kStruct)))
	StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", Float(10.5f)))
	DeclareVarInst("float", fSlow6, kStack, LoadVarInst(Address(fVbargraph6, kStruct)))
	StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", Float(21.0f)))
	DeclareVarInst("float", fSlow7, kStack, LoadVarInst(Address(fVbargraph7, kStruct)))
	StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", Float(31.5f)))
	DeclareVarInst("float", fSlow8, kStack, LoadVarInst(Address(fVbargraph8, kStruct)))
	StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", Float(42.0f)))
	DeclareVarInst("float", fSlow9, kStack, LoadVarInst(Address(fVbargraph9, kStruct)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow0, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow1, kStack))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow2, kStack))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow3, kStack))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow4, kStack))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow6, kStack))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow7, kStack))))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow8, kStack))))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow9, kStack))))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 40 bytes
Total heap size = 44 bytes
Stack size in compute = 120 bytes

======= Variable access in Control ==========

Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fVbargraph0 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph1 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph2 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph3 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph4 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph5 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph6 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph7 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph8 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVbargraph9 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
