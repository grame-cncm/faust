======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("math")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global external declarations begin ==========

BlockInst 
	DeclareFunInst("int", "isnanf", "float", dummy0)
	DeclareFunInst("int", "isinff", "float", dummy0)
	DeclareFunInst("float", "copysignf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "acoshf", "float", dummy0)
	DeclareFunInst("float", "asinhf", "float", dummy0)
	DeclareFunInst("float", "atanhf", "float", dummy0)
	DeclareFunInst("float", "coshf", "float", dummy0)
	DeclareFunInst("float", "sinhf", "float", dummy0)
	DeclareFunInst("float", "tanhf", "float", dummy0)
EndBlockInst

======= Global external declarations end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "abs", "int", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "acosf", "float", dummy0)
	DeclareFunInst("float", "asinf", "float", dummy0)
	DeclareFunInst("float", "atanf", "float", dummy0)
	DeclareFunInst("float", "atan2f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "ceilf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "logf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("int", "mydsp_faustpower3_i", "int", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "remainderf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "rintf", "float", dummy0)
	DeclareFunInst("float", "roundf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("float[2]", fVec0)("int[2]", iVec1)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(104))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(76))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 180 Store = 0 Binop = 0 Mathop = 0 Numbers = 180 Declare = 180 Cast = 0 Select = 0 Loop = 0

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
	DeclareVarInst("FAUSTFLOAT*", input12, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(12)]))
	DeclareVarInst("FAUSTFLOAT*", input13, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(13)]))
	DeclareVarInst("FAUSTFLOAT*", input14, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", input15, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(15)]))
	DeclareVarInst("FAUSTFLOAT*", input16, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(16)]))
	DeclareVarInst("FAUSTFLOAT*", input17, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(17)]))
	DeclareVarInst("FAUSTFLOAT*", input18, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(18)]))
	DeclareVarInst("FAUSTFLOAT*", input19, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(19)]))
	DeclareVarInst("FAUSTFLOAT*", input20, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(20)]))
	DeclareVarInst("FAUSTFLOAT*", input21, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(21)]))
	DeclareVarInst("FAUSTFLOAT*", input22, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(22)]))
	DeclareVarInst("FAUSTFLOAT*", input23, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(23)]))
	DeclareVarInst("FAUSTFLOAT*", input24, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(24)]))
	DeclareVarInst("FAUSTFLOAT*", input25, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(25)]))
	DeclareVarInst("FAUSTFLOAT*", input26, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(26)]))
	DeclareVarInst("FAUSTFLOAT*", input27, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(27)]))
	DeclareVarInst("FAUSTFLOAT*", input28, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(28)]))
	DeclareVarInst("FAUSTFLOAT*", input29, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(29)]))
	DeclareVarInst("FAUSTFLOAT*", input30, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(30)]))
	DeclareVarInst("FAUSTFLOAT*", input31, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(31)]))
	DeclareVarInst("FAUSTFLOAT*", input32, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(32)]))
	DeclareVarInst("FAUSTFLOAT*", input33, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(33)]))
	DeclareVarInst("FAUSTFLOAT*", input34, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(34)]))
	DeclareVarInst("FAUSTFLOAT*", input35, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(35)]))
	DeclareVarInst("FAUSTFLOAT*", input36, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(36)]))
	DeclareVarInst("FAUSTFLOAT*", input37, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(37)]))
	DeclareVarInst("FAUSTFLOAT*", input38, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(38)]))
	DeclareVarInst("FAUSTFLOAT*", input39, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(39)]))
	DeclareVarInst("FAUSTFLOAT*", input40, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(40)]))
	DeclareVarInst("FAUSTFLOAT*", input41, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(41)]))
	DeclareVarInst("FAUSTFLOAT*", input42, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(42)]))
	DeclareVarInst("FAUSTFLOAT*", input43, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(43)]))
	DeclareVarInst("FAUSTFLOAT*", input44, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(44)]))
	DeclareVarInst("FAUSTFLOAT*", input45, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(45)]))
	DeclareVarInst("FAUSTFLOAT*", input46, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(46)]))
	DeclareVarInst("FAUSTFLOAT*", input47, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(47)]))
	DeclareVarInst("FAUSTFLOAT*", input48, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(48)]))
	DeclareVarInst("FAUSTFLOAT*", input49, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(49)]))
	DeclareVarInst("FAUSTFLOAT*", input50, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(50)]))
	DeclareVarInst("FAUSTFLOAT*", input51, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(51)]))
	DeclareVarInst("FAUSTFLOAT*", input52, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(52)]))
	DeclareVarInst("FAUSTFLOAT*", input53, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(53)]))
	DeclareVarInst("FAUSTFLOAT*", input54, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(54)]))
	DeclareVarInst("FAUSTFLOAT*", input55, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(55)]))
	DeclareVarInst("FAUSTFLOAT*", input56, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(56)]))
	DeclareVarInst("FAUSTFLOAT*", input57, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(57)]))
	DeclareVarInst("FAUSTFLOAT*", input58, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(58)]))
	DeclareVarInst("FAUSTFLOAT*", input59, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(59)]))
	DeclareVarInst("FAUSTFLOAT*", input60, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(60)]))
	DeclareVarInst("FAUSTFLOAT*", input61, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(61)]))
	DeclareVarInst("FAUSTFLOAT*", input62, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(62)]))
	DeclareVarInst("FAUSTFLOAT*", input63, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(63)]))
	DeclareVarInst("FAUSTFLOAT*", input64, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(64)]))
	DeclareVarInst("FAUSTFLOAT*", input65, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(65)]))
	DeclareVarInst("FAUSTFLOAT*", input66, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(66)]))
	DeclareVarInst("FAUSTFLOAT*", input67, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(67)]))
	DeclareVarInst("FAUSTFLOAT*", input68, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(68)]))
	DeclareVarInst("FAUSTFLOAT*", input69, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(69)]))
	DeclareVarInst("FAUSTFLOAT*", input70, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(70)]))
	DeclareVarInst("FAUSTFLOAT*", input71, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(71)]))
	DeclareVarInst("FAUSTFLOAT*", input72, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(72)]))
	DeclareVarInst("FAUSTFLOAT*", input73, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(73)]))
	DeclareVarInst("FAUSTFLOAT*", input74, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(74)]))
	DeclareVarInst("FAUSTFLOAT*", input75, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(75)]))
	DeclareVarInst("FAUSTFLOAT*", input76, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(76)]))
	DeclareVarInst("FAUSTFLOAT*", input77, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(77)]))
	DeclareVarInst("FAUSTFLOAT*", input78, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(78)]))
	DeclareVarInst("FAUSTFLOAT*", input79, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(79)]))
	DeclareVarInst("FAUSTFLOAT*", input80, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(80)]))
	DeclareVarInst("FAUSTFLOAT*", input81, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(81)]))
	DeclareVarInst("FAUSTFLOAT*", input82, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(82)]))
	DeclareVarInst("FAUSTFLOAT*", input83, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(83)]))
	DeclareVarInst("FAUSTFLOAT*", input84, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(84)]))
	DeclareVarInst("FAUSTFLOAT*", input85, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(85)]))
	DeclareVarInst("FAUSTFLOAT*", input86, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(86)]))
	DeclareVarInst("FAUSTFLOAT*", input87, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(87)]))
	DeclareVarInst("FAUSTFLOAT*", input88, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(88)]))
	DeclareVarInst("FAUSTFLOAT*", input89, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(89)]))
	DeclareVarInst("FAUSTFLOAT*", input90, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(90)]))
	DeclareVarInst("FAUSTFLOAT*", input91, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(91)]))
	DeclareVarInst("FAUSTFLOAT*", input92, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(92)]))
	DeclareVarInst("FAUSTFLOAT*", input93, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(93)]))
	DeclareVarInst("FAUSTFLOAT*", input94, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(94)]))
	DeclareVarInst("FAUSTFLOAT*", input95, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(95)]))
	DeclareVarInst("FAUSTFLOAT*", input96, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(96)]))
	DeclareVarInst("FAUSTFLOAT*", input97, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(97)]))
	DeclareVarInst("FAUSTFLOAT*", input98, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(98)]))
	DeclareVarInst("FAUSTFLOAT*", input99, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(99)]))
	DeclareVarInst("FAUSTFLOAT*", input100, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(100)]))
	DeclareVarInst("FAUSTFLOAT*", input101, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(101)]))
	DeclareVarInst("FAUSTFLOAT*", input102, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(102)]))
	DeclareVarInst("FAUSTFLOAT*", input103, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(103)]))
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
	DeclareVarInst("FAUSTFLOAT*", output14, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", output15, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(15)]))
	DeclareVarInst("FAUSTFLOAT*", output16, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(16)]))
	DeclareVarInst("FAUSTFLOAT*", output17, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(17)]))
	DeclareVarInst("FAUSTFLOAT*", output18, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(18)]))
	DeclareVarInst("FAUSTFLOAT*", output19, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(19)]))
	DeclareVarInst("FAUSTFLOAT*", output20, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(20)]))
	DeclareVarInst("FAUSTFLOAT*", output21, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(21)]))
	DeclareVarInst("FAUSTFLOAT*", output22, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(22)]))
	DeclareVarInst("FAUSTFLOAT*", output23, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(23)]))
	DeclareVarInst("FAUSTFLOAT*", output24, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(24)]))
	DeclareVarInst("FAUSTFLOAT*", output25, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(25)]))
	DeclareVarInst("FAUSTFLOAT*", output26, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(26)]))
	DeclareVarInst("FAUSTFLOAT*", output27, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(27)]))
	DeclareVarInst("FAUSTFLOAT*", output28, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(28)]))
	DeclareVarInst("FAUSTFLOAT*", output29, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(29)]))
	DeclareVarInst("FAUSTFLOAT*", output30, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(30)]))
	DeclareVarInst("FAUSTFLOAT*", output31, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(31)]))
	DeclareVarInst("FAUSTFLOAT*", output32, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(32)]))
	DeclareVarInst("FAUSTFLOAT*", output33, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(33)]))
	DeclareVarInst("FAUSTFLOAT*", output34, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(34)]))
	DeclareVarInst("FAUSTFLOAT*", output35, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(35)]))
	DeclareVarInst("FAUSTFLOAT*", output36, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(36)]))
	DeclareVarInst("FAUSTFLOAT*", output37, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(37)]))
	DeclareVarInst("FAUSTFLOAT*", output38, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(38)]))
	DeclareVarInst("FAUSTFLOAT*", output39, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(39)]))
	DeclareVarInst("FAUSTFLOAT*", output40, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(40)]))
	DeclareVarInst("FAUSTFLOAT*", output41, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(41)]))
	DeclareVarInst("FAUSTFLOAT*", output42, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(42)]))
	DeclareVarInst("FAUSTFLOAT*", output43, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(43)]))
	DeclareVarInst("FAUSTFLOAT*", output44, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(44)]))
	DeclareVarInst("FAUSTFLOAT*", output45, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(45)]))
	DeclareVarInst("FAUSTFLOAT*", output46, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(46)]))
	DeclareVarInst("FAUSTFLOAT*", output47, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(47)]))
	DeclareVarInst("FAUSTFLOAT*", output48, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(48)]))
	DeclareVarInst("FAUSTFLOAT*", output49, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(49)]))
	DeclareVarInst("FAUSTFLOAT*", output50, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(50)]))
	DeclareVarInst("FAUSTFLOAT*", output51, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(51)]))
	DeclareVarInst("FAUSTFLOAT*", output52, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(52)]))
	DeclareVarInst("FAUSTFLOAT*", output53, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(53)]))
	DeclareVarInst("FAUSTFLOAT*", output54, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(54)]))
	DeclareVarInst("FAUSTFLOAT*", output55, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(55)]))
	DeclareVarInst("FAUSTFLOAT*", output56, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(56)]))
	DeclareVarInst("FAUSTFLOAT*", output57, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(57)]))
	DeclareVarInst("FAUSTFLOAT*", output58, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(58)]))
	DeclareVarInst("FAUSTFLOAT*", output59, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(59)]))
	DeclareVarInst("FAUSTFLOAT*", output60, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(60)]))
	DeclareVarInst("FAUSTFLOAT*", output61, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(61)]))
	DeclareVarInst("FAUSTFLOAT*", output62, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(62)]))
	DeclareVarInst("FAUSTFLOAT*", output63, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(63)]))
	DeclareVarInst("FAUSTFLOAT*", output64, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(64)]))
	DeclareVarInst("FAUSTFLOAT*", output65, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(65)]))
	DeclareVarInst("FAUSTFLOAT*", output66, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(66)]))
	DeclareVarInst("FAUSTFLOAT*", output67, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(67)]))
	DeclareVarInst("FAUSTFLOAT*", output68, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(68)]))
	DeclareVarInst("FAUSTFLOAT*", output69, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(69)]))
	DeclareVarInst("FAUSTFLOAT*", output70, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(70)]))
	DeclareVarInst("FAUSTFLOAT*", output71, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(71)]))
	DeclareVarInst("FAUSTFLOAT*", output72, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(72)]))
	DeclareVarInst("FAUSTFLOAT*", output73, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(73)]))
	DeclareVarInst("FAUSTFLOAT*", output74, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(74)]))
	DeclareVarInst("FAUSTFLOAT*", output75, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(75)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 291 Store = 81 Binop = 128 [ { Int(!=) = 1 } { Int(%) = 1 } { Int(&) = 4 } { Int(+) = 1 } { Int(<) = 2 } { Int(<<) = 1 } { Int(<=) = 1 } { Int(==) = 1 } { Int(>) = 1 } { Int(>=) = 1 } { Int(>>) = 1 } { Int(^) = 2 } { Int(|) = 2 } { Real(!=) = 1 } { Real(*) = 94 } { Real(+) = 8 } { Real(<) = 1 } { Real(<=) = 1 } { Real(==) = 1 } { Real(>) = 2 } { Real(>=) = 1 } ] Mathop = 50 [ { abs = 2 } { acosf = 2 } { acoshf = 1 } { asinf = 1 } { asinhf = 1 } { atan2f = 3 } { atanf = 1 } { atanhf = 1 } { ceilf = 1 } { copysignf = 1 } { cosf = 1 } { coshf = 1 } { expf = 1 } { fabsf = 2 } { floorf = 1 } { fmodf = 2 } { isinff = 1 } { isnanf = 1 } { log10f = 1 } { logf = 1 } { max_f = 2 } { max_i = 1 } { min_f = 2 } { min_i = 1 } { mydsp_faustpower3_f = 1 } { mydsp_faustpower3_i = 2 } { powf = 7 } { remainderf = 1 } { rintf = 1 } { roundf = 1 } { sinf = 1 } { sinhf = 1 } { sqrtf = 1 } { tanf = 1 } { tanhf = 1 } ] Numbers = 128 Declare = 1 Cast = 244 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], Float(2.0f))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", LoadVarInst(Address(fVec0, kStruct)[Int32(1)]), Float(3e+01f))))
		StoreVarInst(Address(iVec1, kStruct)[Int32(0)], Int32(2))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("int", FunCallInst("powf", CastInst("float", LoadVarInst(Address(iVec1, kStruct)[Int32(1)])), CastInst("float", Int32(30))))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(1.0737418e+09f)))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(1073741824)))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("isnanf", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("isinff", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("copysignf", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">>", CastInst("int", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<<", CastInst("int", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("%", CastInst("int", BinopInst("*", Float(10.5f), CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))])))), Int32(3))))
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("fmodf", BinopInst("*", Float(10.5f), CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(3.0f))))
		StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("&", CastInst("int", CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input12, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input13, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input14, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input15, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(2.4f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input16, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", CastInst("float", LoadVarInst(Address(input17, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
		StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("|", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input18, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input19, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("|", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input20, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input21, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("^", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input22, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input23, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("^", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input24, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input25, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("int", FunCallInst("powf", CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input26, kStack)[LoadVarInst(Address(i0, kLoop))]))))), CastInst("float", CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input27, kStack)[LoadVarInst(Address(i0, kLoop))])))))))))
		StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(2.4f), BinopInst("*", CastInst("float", LoadVarInst(Address(input28, kStack)[LoadVarInst(Address(i0, kLoop))])), FunCallInst("powf", Float(3.5f), CastInst("float", LoadVarInst(Address(input29, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input30, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input31, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input32, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("float", CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input33, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
		StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input34, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input35, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input36, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input37, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">=", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input38, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input39, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input40, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input41, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input42, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input43, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input44, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input45, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<=", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input46, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input47, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input48, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input49, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output31, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("==", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input50, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input51, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output32, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("!=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input52, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input53, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output33, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("!=", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input54, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input55, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output34, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("abs", CastInst("int", BinopInst("*", Float(4.4f), CastInst("float", LoadVarInst(Address(input56, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output35, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("abs", CastInst("int", MinusInst(BinopInst("*", Float(4.4f), CastInst("float", LoadVarInst(Address(input57, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
		StoreVarInst(Address(output36, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("fabsf", BinopInst("*", Float(4.4f), CastInst("float", LoadVarInst(Address(input58, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output37, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("fabsf", MinusInst(BinopInst("*", Float(4.4f), CastInst("float", LoadVarInst(Address(input59, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output38, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("acosf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input60, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output39, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("acosf", CastInst("float", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input61, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
		StoreVarInst(Address(output40, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("asinf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input62, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output41, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atanf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input63, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output42, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atan2f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input64, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(4.0f))))
		StoreVarInst(Address(output43, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atan2f", CastInst("float", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input65, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Float(4.0f))))
		StoreVarInst(Address(output44, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atan2f", CastInst("float", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input66, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Float(4.0f))))
		StoreVarInst(Address(output45, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("ceilf", BinopInst("*", Float(1.3f), CastInst("float", LoadVarInst(Address(input67, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output46, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("cosf", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input68, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output47, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("expf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input69, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output48, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("floorf", BinopInst("*", Float(6.5f), CastInst("float", LoadVarInst(Address(input70, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output49, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("fmodf", BinopInst("*", Float(9.2f), CastInst("float", LoadVarInst(Address(input71, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(2.0f))))
		StoreVarInst(Address(output50, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("logf", BinopInst("*", Float(0.5f), BinopInst("+", CastInst("float", LoadVarInst(Address(input72, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(1.0f))))))
		StoreVarInst(Address(output51, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("log10f", BinopInst("*", Float(0.5f), BinopInst("+", CastInst("float", LoadVarInst(Address(input73, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(1.0f))))))
		StoreVarInst(Address(output52, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("max_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input74, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(input75, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output53, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("min_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input76, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(input77, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output54, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("max_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input78, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("float", CastInst("int", BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(input79, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
		StoreVarInst(Address(output55, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("min_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input80, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("float", CastInst("int", BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(input81, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
		StoreVarInst(Address(output56, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("max_i", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input82, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input83, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output57, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("min_i", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input84, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input85, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output58, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input86, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(0.3f))))
		StoreVarInst(Address(output59, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", CastInst("float", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input87, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Float(0.3f))))
		StoreVarInst(Address(output60, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower3_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input88, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output61, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower3_i", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input89, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output62, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower3_i", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input90, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
		StoreVarInst(Address(output63, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(3.0f), CastInst("float", LoadVarInst(Address(input91, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output64, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("remainderf", BinopInst("*", Float(9.2f), CastInst("float", LoadVarInst(Address(input92, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(2.0f))))
		StoreVarInst(Address(output65, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("rintf", BinopInst("*", Float(1.5f), CastInst("float", LoadVarInst(Address(input93, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output66, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("roundf", BinopInst("*", Float(1.5f), CastInst("float", LoadVarInst(Address(input94, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output67, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("sinf", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input95, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output68, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("sqrtf", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input96, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output69, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("tanf", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input97, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
		StoreVarInst(Address(output70, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("acoshf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input98, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
		StoreVarInst(Address(output71, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("asinhf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input99, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
		StoreVarInst(Address(output72, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atanhf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input100, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(0.5f)))))
		StoreVarInst(Address(output73, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("coshf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input101, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
		StoreVarInst(Address(output74, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("sinhf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input102, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
		StoreVarInst(Address(output75, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("tanhf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input103, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec1, kStruct)[Int32(1)], LoadVarInst(Address(iVec1, kStruct)[Int32(0)]))
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
	DeclareFunInst("int", "isnanf", "float", dummy0)
	DeclareFunInst("int", "isinff", "float", dummy0)
	DeclareFunInst("float", "copysignf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "acoshf", "float", dummy0)
	DeclareFunInst("float", "asinhf", "float", dummy0)
	DeclareFunInst("float", "atanhf", "float", dummy0)
	DeclareFunInst("float", "coshf", "float", dummy0)
	DeclareFunInst("float", "sinhf", "float", dummy0)
	DeclareFunInst("float", "tanhf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "abs", "int", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "acosf", "float", dummy0)
	DeclareFunInst("float", "asinf", "float", dummy0)
	DeclareFunInst("float", "atanf", "float", dummy0)
	DeclareFunInst("float", "atan2f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "ceilf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "logf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("int", "mydsp_faustpower3_i", "int", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "remainderf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "rintf", "float", dummy0)
	DeclareFunInst("float", "roundf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareVarInst("float", fVec0[2], kStruct)
	DeclareVarInst("int", iVec1[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
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
	DeclareVarInst("FAUSTFLOAT*", input12, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(12)]))
	DeclareVarInst("FAUSTFLOAT*", input13, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(13)]))
	DeclareVarInst("FAUSTFLOAT*", input14, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", input15, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(15)]))
	DeclareVarInst("FAUSTFLOAT*", input16, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(16)]))
	DeclareVarInst("FAUSTFLOAT*", input17, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(17)]))
	DeclareVarInst("FAUSTFLOAT*", input18, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(18)]))
	DeclareVarInst("FAUSTFLOAT*", input19, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(19)]))
	DeclareVarInst("FAUSTFLOAT*", input20, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(20)]))
	DeclareVarInst("FAUSTFLOAT*", input21, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(21)]))
	DeclareVarInst("FAUSTFLOAT*", input22, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(22)]))
	DeclareVarInst("FAUSTFLOAT*", input23, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(23)]))
	DeclareVarInst("FAUSTFLOAT*", input24, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(24)]))
	DeclareVarInst("FAUSTFLOAT*", input25, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(25)]))
	DeclareVarInst("FAUSTFLOAT*", input26, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(26)]))
	DeclareVarInst("FAUSTFLOAT*", input27, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(27)]))
	DeclareVarInst("FAUSTFLOAT*", input28, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(28)]))
	DeclareVarInst("FAUSTFLOAT*", input29, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(29)]))
	DeclareVarInst("FAUSTFLOAT*", input30, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(30)]))
	DeclareVarInst("FAUSTFLOAT*", input31, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(31)]))
	DeclareVarInst("FAUSTFLOAT*", input32, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(32)]))
	DeclareVarInst("FAUSTFLOAT*", input33, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(33)]))
	DeclareVarInst("FAUSTFLOAT*", input34, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(34)]))
	DeclareVarInst("FAUSTFLOAT*", input35, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(35)]))
	DeclareVarInst("FAUSTFLOAT*", input36, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(36)]))
	DeclareVarInst("FAUSTFLOAT*", input37, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(37)]))
	DeclareVarInst("FAUSTFLOAT*", input38, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(38)]))
	DeclareVarInst("FAUSTFLOAT*", input39, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(39)]))
	DeclareVarInst("FAUSTFLOAT*", input40, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(40)]))
	DeclareVarInst("FAUSTFLOAT*", input41, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(41)]))
	DeclareVarInst("FAUSTFLOAT*", input42, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(42)]))
	DeclareVarInst("FAUSTFLOAT*", input43, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(43)]))
	DeclareVarInst("FAUSTFLOAT*", input44, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(44)]))
	DeclareVarInst("FAUSTFLOAT*", input45, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(45)]))
	DeclareVarInst("FAUSTFLOAT*", input46, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(46)]))
	DeclareVarInst("FAUSTFLOAT*", input47, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(47)]))
	DeclareVarInst("FAUSTFLOAT*", input48, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(48)]))
	DeclareVarInst("FAUSTFLOAT*", input49, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(49)]))
	DeclareVarInst("FAUSTFLOAT*", input50, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(50)]))
	DeclareVarInst("FAUSTFLOAT*", input51, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(51)]))
	DeclareVarInst("FAUSTFLOAT*", input52, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(52)]))
	DeclareVarInst("FAUSTFLOAT*", input53, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(53)]))
	DeclareVarInst("FAUSTFLOAT*", input54, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(54)]))
	DeclareVarInst("FAUSTFLOAT*", input55, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(55)]))
	DeclareVarInst("FAUSTFLOAT*", input56, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(56)]))
	DeclareVarInst("FAUSTFLOAT*", input57, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(57)]))
	DeclareVarInst("FAUSTFLOAT*", input58, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(58)]))
	DeclareVarInst("FAUSTFLOAT*", input59, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(59)]))
	DeclareVarInst("FAUSTFLOAT*", input60, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(60)]))
	DeclareVarInst("FAUSTFLOAT*", input61, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(61)]))
	DeclareVarInst("FAUSTFLOAT*", input62, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(62)]))
	DeclareVarInst("FAUSTFLOAT*", input63, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(63)]))
	DeclareVarInst("FAUSTFLOAT*", input64, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(64)]))
	DeclareVarInst("FAUSTFLOAT*", input65, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(65)]))
	DeclareVarInst("FAUSTFLOAT*", input66, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(66)]))
	DeclareVarInst("FAUSTFLOAT*", input67, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(67)]))
	DeclareVarInst("FAUSTFLOAT*", input68, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(68)]))
	DeclareVarInst("FAUSTFLOAT*", input69, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(69)]))
	DeclareVarInst("FAUSTFLOAT*", input70, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(70)]))
	DeclareVarInst("FAUSTFLOAT*", input71, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(71)]))
	DeclareVarInst("FAUSTFLOAT*", input72, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(72)]))
	DeclareVarInst("FAUSTFLOAT*", input73, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(73)]))
	DeclareVarInst("FAUSTFLOAT*", input74, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(74)]))
	DeclareVarInst("FAUSTFLOAT*", input75, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(75)]))
	DeclareVarInst("FAUSTFLOAT*", input76, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(76)]))
	DeclareVarInst("FAUSTFLOAT*", input77, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(77)]))
	DeclareVarInst("FAUSTFLOAT*", input78, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(78)]))
	DeclareVarInst("FAUSTFLOAT*", input79, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(79)]))
	DeclareVarInst("FAUSTFLOAT*", input80, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(80)]))
	DeclareVarInst("FAUSTFLOAT*", input81, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(81)]))
	DeclareVarInst("FAUSTFLOAT*", input82, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(82)]))
	DeclareVarInst("FAUSTFLOAT*", input83, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(83)]))
	DeclareVarInst("FAUSTFLOAT*", input84, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(84)]))
	DeclareVarInst("FAUSTFLOAT*", input85, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(85)]))
	DeclareVarInst("FAUSTFLOAT*", input86, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(86)]))
	DeclareVarInst("FAUSTFLOAT*", input87, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(87)]))
	DeclareVarInst("FAUSTFLOAT*", input88, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(88)]))
	DeclareVarInst("FAUSTFLOAT*", input89, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(89)]))
	DeclareVarInst("FAUSTFLOAT*", input90, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(90)]))
	DeclareVarInst("FAUSTFLOAT*", input91, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(91)]))
	DeclareVarInst("FAUSTFLOAT*", input92, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(92)]))
	DeclareVarInst("FAUSTFLOAT*", input93, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(93)]))
	DeclareVarInst("FAUSTFLOAT*", input94, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(94)]))
	DeclareVarInst("FAUSTFLOAT*", input95, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(95)]))
	DeclareVarInst("FAUSTFLOAT*", input96, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(96)]))
	DeclareVarInst("FAUSTFLOAT*", input97, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(97)]))
	DeclareVarInst("FAUSTFLOAT*", input98, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(98)]))
	DeclareVarInst("FAUSTFLOAT*", input99, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(99)]))
	DeclareVarInst("FAUSTFLOAT*", input100, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(100)]))
	DeclareVarInst("FAUSTFLOAT*", input101, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(101)]))
	DeclareVarInst("FAUSTFLOAT*", input102, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(102)]))
	DeclareVarInst("FAUSTFLOAT*", input103, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(103)]))
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
	DeclareVarInst("FAUSTFLOAT*", output14, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", output15, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(15)]))
	DeclareVarInst("FAUSTFLOAT*", output16, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(16)]))
	DeclareVarInst("FAUSTFLOAT*", output17, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(17)]))
	DeclareVarInst("FAUSTFLOAT*", output18, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(18)]))
	DeclareVarInst("FAUSTFLOAT*", output19, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(19)]))
	DeclareVarInst("FAUSTFLOAT*", output20, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(20)]))
	DeclareVarInst("FAUSTFLOAT*", output21, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(21)]))
	DeclareVarInst("FAUSTFLOAT*", output22, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(22)]))
	DeclareVarInst("FAUSTFLOAT*", output23, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(23)]))
	DeclareVarInst("FAUSTFLOAT*", output24, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(24)]))
	DeclareVarInst("FAUSTFLOAT*", output25, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(25)]))
	DeclareVarInst("FAUSTFLOAT*", output26, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(26)]))
	DeclareVarInst("FAUSTFLOAT*", output27, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(27)]))
	DeclareVarInst("FAUSTFLOAT*", output28, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(28)]))
	DeclareVarInst("FAUSTFLOAT*", output29, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(29)]))
	DeclareVarInst("FAUSTFLOAT*", output30, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(30)]))
	DeclareVarInst("FAUSTFLOAT*", output31, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(31)]))
	DeclareVarInst("FAUSTFLOAT*", output32, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(32)]))
	DeclareVarInst("FAUSTFLOAT*", output33, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(33)]))
	DeclareVarInst("FAUSTFLOAT*", output34, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(34)]))
	DeclareVarInst("FAUSTFLOAT*", output35, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(35)]))
	DeclareVarInst("FAUSTFLOAT*", output36, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(36)]))
	DeclareVarInst("FAUSTFLOAT*", output37, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(37)]))
	DeclareVarInst("FAUSTFLOAT*", output38, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(38)]))
	DeclareVarInst("FAUSTFLOAT*", output39, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(39)]))
	DeclareVarInst("FAUSTFLOAT*", output40, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(40)]))
	DeclareVarInst("FAUSTFLOAT*", output41, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(41)]))
	DeclareVarInst("FAUSTFLOAT*", output42, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(42)]))
	DeclareVarInst("FAUSTFLOAT*", output43, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(43)]))
	DeclareVarInst("FAUSTFLOAT*", output44, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(44)]))
	DeclareVarInst("FAUSTFLOAT*", output45, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(45)]))
	DeclareVarInst("FAUSTFLOAT*", output46, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(46)]))
	DeclareVarInst("FAUSTFLOAT*", output47, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(47)]))
	DeclareVarInst("FAUSTFLOAT*", output48, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(48)]))
	DeclareVarInst("FAUSTFLOAT*", output49, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(49)]))
	DeclareVarInst("FAUSTFLOAT*", output50, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(50)]))
	DeclareVarInst("FAUSTFLOAT*", output51, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(51)]))
	DeclareVarInst("FAUSTFLOAT*", output52, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(52)]))
	DeclareVarInst("FAUSTFLOAT*", output53, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(53)]))
	DeclareVarInst("FAUSTFLOAT*", output54, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(54)]))
	DeclareVarInst("FAUSTFLOAT*", output55, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(55)]))
	DeclareVarInst("FAUSTFLOAT*", output56, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(56)]))
	DeclareVarInst("FAUSTFLOAT*", output57, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(57)]))
	DeclareVarInst("FAUSTFLOAT*", output58, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(58)]))
	DeclareVarInst("FAUSTFLOAT*", output59, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(59)]))
	DeclareVarInst("FAUSTFLOAT*", output60, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(60)]))
	DeclareVarInst("FAUSTFLOAT*", output61, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(61)]))
	DeclareVarInst("FAUSTFLOAT*", output62, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(62)]))
	DeclareVarInst("FAUSTFLOAT*", output63, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(63)]))
	DeclareVarInst("FAUSTFLOAT*", output64, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(64)]))
	DeclareVarInst("FAUSTFLOAT*", output65, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(65)]))
	DeclareVarInst("FAUSTFLOAT*", output66, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(66)]))
	DeclareVarInst("FAUSTFLOAT*", output67, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(67)]))
	DeclareVarInst("FAUSTFLOAT*", output68, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(68)]))
	DeclareVarInst("FAUSTFLOAT*", output69, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(69)]))
	DeclareVarInst("FAUSTFLOAT*", output70, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(70)]))
	DeclareVarInst("FAUSTFLOAT*", output71, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(71)]))
	DeclareVarInst("FAUSTFLOAT*", output72, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(72)]))
	DeclareVarInst("FAUSTFLOAT*", output73, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(73)]))
	DeclareVarInst("FAUSTFLOAT*", output74, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(74)]))
	DeclareVarInst("FAUSTFLOAT*", output75, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(75)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], Float(2.0f))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", LoadVarInst(Address(fVec0, kStruct)[Int32(1)]), Float(3e+01f))))
			StoreVarInst(Address(iVec1, kStruct)[Int32(0)], Int32(2))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("int", FunCallInst("powf", CastInst("float", LoadVarInst(Address(iVec1, kStruct)[Int32(1)])), CastInst("float", Int32(30))))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(1.0737418e+09f)))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(1073741824)))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("isnanf", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("isinff", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("copysignf", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">>", CastInst("int", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<<", CastInst("int", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("%", CastInst("int", BinopInst("*", Float(10.5f), CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))])))), Int32(3))))
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("fmodf", BinopInst("*", Float(10.5f), CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(3.0f))))
			StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("&", CastInst("int", CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input12, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input13, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input14, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input15, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(2.4f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input16, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", CastInst("float", LoadVarInst(Address(input17, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
			StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("|", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input18, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input19, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("|", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input20, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input21, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("^", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input22, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input23, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("^", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input24, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input25, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", CastInst("int", FunCallInst("powf", CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input26, kStack)[LoadVarInst(Address(i0, kLoop))]))))), CastInst("float", CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input27, kStack)[LoadVarInst(Address(i0, kLoop))])))))))))
			StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(2.4f), BinopInst("*", CastInst("float", LoadVarInst(Address(input28, kStack)[LoadVarInst(Address(i0, kLoop))])), FunCallInst("powf", Float(3.5f), CastInst("float", LoadVarInst(Address(input29, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input30, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input31, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input32, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("float", CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input33, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
			StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input34, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input35, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input36, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input37, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst(">=", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input38, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input39, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input40, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input41, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input42, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input43, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input44, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input45, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("<=", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input46, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input47, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input48, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input49, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output31, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("==", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input50, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input51, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output32, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("!=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input52, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input53, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output33, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("!=", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input54, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input55, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output34, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("abs", CastInst("int", BinopInst("*", Float(4.4f), CastInst("float", LoadVarInst(Address(input56, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output35, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("abs", CastInst("int", MinusInst(BinopInst("*", Float(4.4f), CastInst("float", LoadVarInst(Address(input57, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
			StoreVarInst(Address(output36, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("fabsf", BinopInst("*", Float(4.4f), CastInst("float", LoadVarInst(Address(input58, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output37, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("fabsf", MinusInst(BinopInst("*", Float(4.4f), CastInst("float", LoadVarInst(Address(input59, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output38, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("acosf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input60, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output39, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("acosf", CastInst("float", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input61, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
			StoreVarInst(Address(output40, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("asinf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input62, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output41, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atanf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input63, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output42, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atan2f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input64, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(4.0f))))
			StoreVarInst(Address(output43, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atan2f", CastInst("float", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input65, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Float(4.0f))))
			StoreVarInst(Address(output44, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atan2f", CastInst("float", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input66, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Float(4.0f))))
			StoreVarInst(Address(output45, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("ceilf", BinopInst("*", Float(1.3f), CastInst("float", LoadVarInst(Address(input67, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output46, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("cosf", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input68, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output47, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("expf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input69, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output48, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("floorf", BinopInst("*", Float(6.5f), CastInst("float", LoadVarInst(Address(input70, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output49, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("fmodf", BinopInst("*", Float(9.2f), CastInst("float", LoadVarInst(Address(input71, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(2.0f))))
			StoreVarInst(Address(output50, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("logf", BinopInst("*", Float(0.5f), BinopInst("+", CastInst("float", LoadVarInst(Address(input72, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(1.0f))))))
			StoreVarInst(Address(output51, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("log10f", BinopInst("*", Float(0.5f), BinopInst("+", CastInst("float", LoadVarInst(Address(input73, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(1.0f))))))
			StoreVarInst(Address(output52, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("max_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input74, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(input75, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output53, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("min_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input76, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(input77, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output54, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("max_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input78, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("float", CastInst("int", BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(input79, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
			StoreVarInst(Address(output55, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("min_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input80, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("float", CastInst("int", BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(input81, kStack)[LoadVarInst(Address(i0, kLoop))]))))))))
			StoreVarInst(Address(output56, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("max_i", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input82, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input83, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output57, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("min_i", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input84, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(2.4f), CastInst("float", LoadVarInst(Address(input85, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output58, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input86, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(0.3f))))
			StoreVarInst(Address(output59, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", CastInst("float", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input87, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Float(0.3f))))
			StoreVarInst(Address(output60, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower3_f", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input88, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output61, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower3_i", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input89, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output62, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower3_i", CastInst("int", BinopInst("*", Float(0.5f), CastInst("float", LoadVarInst(Address(input90, kStack)[LoadVarInst(Address(i0, kLoop))])))))))
			StoreVarInst(Address(output63, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(3.0f), CastInst("float", LoadVarInst(Address(input91, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output64, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("remainderf", BinopInst("*", Float(9.2f), CastInst("float", LoadVarInst(Address(input92, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(2.0f))))
			StoreVarInst(Address(output65, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("rintf", BinopInst("*", Float(1.5f), CastInst("float", LoadVarInst(Address(input93, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output66, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("roundf", BinopInst("*", Float(1.5f), CastInst("float", LoadVarInst(Address(input94, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output67, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("sinf", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input95, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output68, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("sqrtf", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input96, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output69, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("tanf", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input97, kStack)[LoadVarInst(Address(i0, kLoop))]))))))
			StoreVarInst(Address(output70, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("acoshf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input98, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
			StoreVarInst(Address(output71, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("asinhf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input99, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
			StoreVarInst(Address(output72, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("atanhf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input100, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(0.5f)))))
			StoreVarInst(Address(output73, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("coshf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input101, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
			StoreVarInst(Address(output74, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("sinhf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input102, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
			StoreVarInst(Address(output75, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", FunCallInst("tanhf", BinopInst("+", BinopInst("*", Float(0.3f), CastInst("float", LoadVarInst(Address(input103, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(1e+01f)))))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec1, kStruct)[Int32(1)], LoadVarInst(Address(iVec1, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 8 bytes
Total heap size = 20 bytes
Stack size in compute = 1440 bytes

======= Variable access in Control ==========

Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = iVec1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
