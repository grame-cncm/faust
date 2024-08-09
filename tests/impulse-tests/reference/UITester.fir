======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenTabBox("grp 1")
	OpenHorizontalBox("hmisc")
	AddButtonInst("button"fButton1)
	AddHorizontalBargraph("hbar", fHbargraph1, 0.0f, 127.0f)
	AddHorizontalSlider("hslider", fHslider1, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fEntry4, "unit", "f")
	AddNumEntry"num", fEntry4, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddVerticalBargraph("vbar", fVbargraph3, 0.0f, 127.0f)
	AddMetaDeclareInst(fVslider16, "unit", "f")
	AddVerticalSlider("vslider4", fVslider16, 6e+01f, 0.0f, 127.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("knobs")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddVerticalSlider("knob1", fVslider3, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddVerticalSlider("knob2", fVslider4, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fVslider5, "style", "knob")
	AddVerticalSlider("knob3", fVslider5, 6e+01f, 0.0f, 127.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("sliders")
	AddVerticalSlider("vslider1", fVslider0, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddVerticalSlider("vslider2", fVslider1, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddVerticalSlider("vslider3", fVslider2, 6e+01f, 0.0f, 127.0f, 0.1f)
	CloseboxInst
	OpenVerticalBox("vbox")
	AddCheckButtonInst("check1"fCheckbox0)
	AddCheckButtonInst("check2"fCheckbox1)
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddNumEntry"knob0", fEntry0, 6e+01f, 0.0f, 127.0f, 0.1f)
	CloseboxInst
	OpenVerticalBox("vmisc")
	AddButtonInst("button"fButton0)
	AddHorizontalBargraph("hbar", fHbargraph0, 0.0f, 127.0f)
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("hslider", fHslider0, 6e+01f, 0.0f, 127.0f, 0.1f)
	OpenHorizontalBox("small box 1")
	AddMetaDeclareInst(fVslider9, "style", "knob")
	AddVerticalSlider("knob4", fVslider9, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fEntry1, "unit", "f")
	AddNumEntry"num1", fEntry1, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddVerticalBargraph("vbar1", fVbargraph0, 0.0f, 127.0f)
	AddMetaDeclareInst(fVslider7, "unit", "Hz")
	AddVerticalSlider("vslider5", fVslider7, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fVslider8, "unit", "Hz")
	AddVerticalSlider("vslider6", fVslider8, 6e+01f, 0.0f, 127.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("sub box 1")
	OpenHorizontalBox("small box 2")
	AddMetaDeclareInst(fVslider12, "style", "knob")
	AddVerticalSlider("knob5", fVslider12, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fEntry2, "unit", "f")
	AddNumEntry"num2", fEntry2, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddVerticalBargraph("vbar2", fVbargraph1, 0.0f, 127.0f)
	AddMetaDeclareInst(fVslider10, "unit", "Hz")
	AddVerticalSlider("vslider7", fVslider10, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fVslider11, "unit", "Hz")
	AddVerticalSlider("vslider8", fVslider11, 6e+01f, 0.0f, 127.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("small box 3")
	AddMetaDeclareInst(fVslider15, "style", "knob")
	AddVerticalSlider("knob6", fVslider15, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fEntry3, "unit", "f")
	AddNumEntry"num3", fEntry3, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddVerticalBargraph("vbar3", fVbargraph2, 0.0f, 127.0f)
	AddMetaDeclareInst(fVslider14, "unit", "m")
	AddVerticalSlider("vslider10", fVslider14, 6e+01f, 0.0f, 127.0f, 0.1f)
	AddMetaDeclareInst(fVslider13, "unit", "Hz")
	AddVerticalSlider("vslider9", fVslider13, 6e+01f, 0.0f, 127.0f, 0.1f)
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(fVslider6, "unit", "Hz")
	AddVerticalSlider("vslider4", fVslider6, 6e+01f, 0.0f, 127.0f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fCheckbox1)("FAUSTFLOAT", fEntry0)("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fVslider1)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fVslider3)("FAUSTFLOAT", fVslider4)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fVslider6)("FAUSTFLOAT", fButton0)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fVslider8)("FAUSTFLOAT", fVslider9)("FAUSTFLOAT", fEntry1)("FAUSTFLOAT", fVbargraph0)("FAUSTFLOAT", fVslider10)("FAUSTFLOAT", fVslider11)("FAUSTFLOAT", fVslider12)("FAUSTFLOAT", fEntry2)("FAUSTFLOAT", fVbargraph1)("FAUSTFLOAT", fVslider13)("FAUSTFLOAT", fVslider14)("FAUSTFLOAT", fVslider15)("FAUSTFLOAT", fEntry3)("FAUSTFLOAT", fVbargraph2)("FAUSTFLOAT", fHbargraph0)("FAUSTFLOAT", fVslider16)("FAUSTFLOAT", fButton1)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fEntry4)("FAUSTFLOAT", fVbargraph3)("FAUSTFLOAT", fHbargraph1)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(6))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(34))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider11, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider12, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider13, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider14, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider15, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider16, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fButton1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
EndBlockInst

======= ResetUI end ==========

======= Compute control begin ==========

Instructions complexity : Load = 68 Store = 0 Binop = 0 Mathop = 0 Numbers = 40 Declare = 68 Cast = 28 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
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
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))
	DeclareVarInst("float", fSlow3, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow4, kStack, CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow8, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow9, kStack, CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))
	DeclareVarInst("float", fSlow10, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow13, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow14, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow15, kStack, CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))
	DeclareVarInst("float", fSlow17, kStack, CastInst("float", LoadVarInst(Address(fVslider11, kStruct))))
	DeclareVarInst("float", fSlow18, kStack, CastInst("float", LoadVarInst(Address(fVslider12, kStruct))))
	DeclareVarInst("float", fSlow19, kStack, CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))
	DeclareVarInst("float", fSlow20, kStack, CastInst("float", LoadVarInst(Address(fVslider13, kStruct))))
	DeclareVarInst("float", fSlow21, kStack, CastInst("float", LoadVarInst(Address(fVslider14, kStruct))))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(fVslider15, kStruct))))
	DeclareVarInst("float", fSlow23, kStack, CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))
	DeclareVarInst("float", fSlow24, kStack, CastInst("float", LoadVarInst(Address(fVslider16, kStruct))))
	DeclareVarInst("float", fSlow25, kStack, CastInst("float", LoadVarInst(Address(fButton1, kStruct))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow27, kStack, CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 83 Store = 41 Binop = 2 [ { Int(+) = 1 } { Int(<) = 1 } ] Mathop = 0 Numbers = 2 Declare = 1 Cast = 46 Select = 0 Loop = 1

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
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow10, kStack))))
		StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow11, kStack))))
		StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow12, kStack))))
		StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow13, kStack))))
		StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow14, kStack))))
		StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow15, kStack))))
		StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVbargraph0, kStruct))))
		StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow16, kStack))))
		StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow17, kStack))))
		StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow18, kStack))))
		StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow19, kStack))))
		StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVbargraph1, kStruct))))
		StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow20, kStack))))
		StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow21, kStack))))
		StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow22, kStack))))
		StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow23, kStack))))
		StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVbargraph2, kStruct))))
		StoreVarInst(Address(fHbargraph0, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fHbargraph0, kStruct))))
		StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow24, kStack))))
		StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow25, kStack))))
		StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow26, kStack))))
		StoreVarInst(Address(output31, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow27, kStack))))
		StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output32, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVbargraph3, kStruct))))
		StoreVarInst(Address(fHbargraph1, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))))
		StoreVarInst(Address(output33, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fHbargraph1, kStruct))))
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
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider11, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider13, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider15, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider16, kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHbargraph1, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider11, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider12, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider13, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider14, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider15, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fEntry3, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider16, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fButton1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fEntry4, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
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
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))
	DeclareVarInst("float", fSlow3, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow4, kStack, CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow8, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow9, kStack, CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))
	DeclareVarInst("float", fSlow10, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow13, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow14, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow15, kStack, CastInst("float", LoadVarInst(Address(fEntry1, kStruct))))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))
	DeclareVarInst("float", fSlow17, kStack, CastInst("float", LoadVarInst(Address(fVslider11, kStruct))))
	DeclareVarInst("float", fSlow18, kStack, CastInst("float", LoadVarInst(Address(fVslider12, kStruct))))
	DeclareVarInst("float", fSlow19, kStack, CastInst("float", LoadVarInst(Address(fEntry2, kStruct))))
	DeclareVarInst("float", fSlow20, kStack, CastInst("float", LoadVarInst(Address(fVslider13, kStruct))))
	DeclareVarInst("float", fSlow21, kStack, CastInst("float", LoadVarInst(Address(fVslider14, kStruct))))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(fVslider15, kStruct))))
	DeclareVarInst("float", fSlow23, kStack, CastInst("float", LoadVarInst(Address(fEntry3, kStruct))))
	DeclareVarInst("float", fSlow24, kStack, CastInst("float", LoadVarInst(Address(fVslider16, kStruct))))
	DeclareVarInst("float", fSlow25, kStack, CastInst("float", LoadVarInst(Address(fButton1, kStruct))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow27, kStack, CastInst("float", LoadVarInst(Address(fEntry4, kStruct))))
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
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow10, kStack))))
			StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow11, kStack))))
			StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow12, kStack))))
			StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow13, kStack))))
			StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow14, kStack))))
			StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow15, kStack))))
			StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVbargraph0, kStruct))))
			StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow16, kStack))))
			StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow17, kStack))))
			StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow18, kStack))))
			StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow19, kStack))))
			StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVbargraph1, kStruct))))
			StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow20, kStack))))
			StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow21, kStack))))
			StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow22, kStack))))
			StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow23, kStack))))
			StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVbargraph2, kStruct))))
			StoreVarInst(Address(fHbargraph0, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fHbargraph0, kStruct))))
			StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow24, kStack))))
			StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow25, kStack))))
			StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow26, kStack))))
			StoreVarInst(Address(output31, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow27, kStack))))
			StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output32, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVbargraph3, kStruct))))
			StoreVarInst(Address(fHbargraph1, kStruct), CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))))
			StoreVarInst(Address(output33, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fHbargraph1, kStruct))))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 136 bytes
Total heap size = 140 bytes
Stack size in compute = 432 bytes

======= Variable access in Control ==========

Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fButton1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider15 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider16 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fButton1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fHbargraph0 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVslider16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fButton1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fHbargraph1 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
