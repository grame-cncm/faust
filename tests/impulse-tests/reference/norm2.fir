======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("norm2")
	AddHorizontalSlider("c_add_2", fHslider0, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("c_add_3", fHslider1, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("c_adv_1", fHslider4, 1.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("c_adv_2", fHslider5, 1.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("c_adv_4", fHslider6, 1.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("c_adv_5", fHslider7, 1.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("c_adv_6", fHslider8, 1.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("c_cmpd_2", fHslider3, 1.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("c_mul_2", fHslider2, 1.0f, -1e+01f, 1e+01f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fHslider2)("FAUSTFLOAT", fHslider3)("FAUSTFLOAT", fHslider4)("FAUSTFLOAT", fHslider5)("FAUSTFLOAT", fHslider6)("FAUSTFLOAT", fHslider7)("FAUSTFLOAT", fHslider8)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(10))
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

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider7, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider8, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
EndBlockInst

======= ResetUI end ==========

======= Compute control begin ==========

Instructions complexity : Load = 29 Store = 0 Binop = 4 [ { Real(*) = 2 } { Real(+) = 2 } ] Mathop = 1 [ { mydsp_faustpower2_f = 1 } ] Numbers = 22 Declare = 27 Cast = 9 Select = 0 Loop = 0

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
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider4, kStruct))), CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider6, kStruct))), CastInst("float", LoadVarInst(Address(fHslider7, kStruct)))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fHslider8, kStruct))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 38 Store = 11 Binop = 9 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 5 } { Real(+) = 2 } ] Mathop = 1 [ { mydsp_faustpower2_f = 1 } ] Numbers = 3 Declare = 1 Cast = 19 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])))))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider8, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider7, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider8, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
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
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider4, kStruct))), CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider6, kStruct))), CastInst("float", LoadVarInst(Address(fHslider7, kStruct)))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fHslider8, kStruct))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])))))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 36 bytes
Total heap size = 40 bytes
Stack size in compute = 188 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
