======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenTabBox("grp 1")
	OpenHorizontalBox("hmisc")
	AddButtonInst("button"fButton1)
	AddHorizontalBargraph("hbar", fHbargraph1, 0.0f, 127.0f)
	AddHorizontalSlider("hslider", fHslider1, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry4, "unit", "f")
	AddNumEntry"num", fEntry4, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddVerticalBargraph("vbar", fVbargraph3, 0.0f, 127.0f)
	AddMetaDeclareInst(fVslider16, "unit", "f")
	AddVerticalSlider("vslider4", fVslider16, 60.0f, 0.0f, 127.0f, 0.100000001f)
	CloseboxInst
	OpenHorizontalBox("knobs")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddVerticalSlider("knob1", fVslider3, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddVerticalSlider("knob2", fVslider4, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider5, "style", "knob")
	AddVerticalSlider("knob3", fVslider5, 60.0f, 0.0f, 127.0f, 0.100000001f)
	CloseboxInst
	OpenHorizontalBox("sliders")
	AddVerticalSlider("vslider1", fVslider0, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddVerticalSlider("vslider2", fVslider1, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddVerticalSlider("vslider3", fVslider2, 60.0f, 0.0f, 127.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("vbox")
	AddCheckButtonInst("check1"fCheckbox0)
	AddCheckButtonInst("check2"fCheckbox1)
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddNumEntry"knob0", fEntry0, 60.0f, 0.0f, 127.0f, 0.100000001f)
	CloseboxInst
	OpenVerticalBox("vmisc")
	AddButtonInst("button"fButton0)
	AddHorizontalBargraph("hbar", fHbargraph0, 0.0f, 127.0f)
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("hslider", fHslider0, 60.0f, 0.0f, 127.0f, 0.100000001f)
	OpenHorizontalBox("small box 1")
	AddMetaDeclareInst(fVslider9, "style", "knob")
	AddVerticalSlider("knob4", fVslider9, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry1, "unit", "f")
	AddNumEntry"num1", fEntry1, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddVerticalBargraph("vbar1", fVbargraph0, 0.0f, 127.0f)
	AddMetaDeclareInst(fVslider7, "unit", "Hz")
	AddVerticalSlider("vslider5", fVslider7, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider8, "unit", "Hz")
	AddVerticalSlider("vslider6", fVslider8, 60.0f, 0.0f, 127.0f, 0.100000001f)
	CloseboxInst
	OpenHorizontalBox("sub box 1")
	OpenHorizontalBox("small box 2")
	AddMetaDeclareInst(fVslider12, "style", "knob")
	AddVerticalSlider("knob5", fVslider12, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry2, "unit", "f")
	AddNumEntry"num2", fEntry2, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddVerticalBargraph("vbar2", fVbargraph1, 0.0f, 127.0f)
	AddMetaDeclareInst(fVslider10, "unit", "Hz")
	AddVerticalSlider("vslider7", fVslider10, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider11, "unit", "Hz")
	AddVerticalSlider("vslider8", fVslider11, 60.0f, 0.0f, 127.0f, 0.100000001f)
	CloseboxInst
	OpenHorizontalBox("small box 3")
	AddMetaDeclareInst(fVslider15, "style", "knob")
	AddVerticalSlider("knob6", fVslider15, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fEntry3, "unit", "f")
	AddNumEntry"num3", fEntry3, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddVerticalBargraph("vbar3", fVbargraph2, 0.0f, 127.0f)
	AddMetaDeclareInst(fVslider14, "unit", "m")
	AddVerticalSlider("vslider10", fVslider14, 60.0f, 0.0f, 127.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider13, "unit", "Hz")
	AddVerticalSlider("vslider9", fVslider13, 60.0f, 0.0f, 127.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(fVslider6, "unit", "Hz")
	AddVerticalSlider("vslider4", fVslider6, 60.0f, 0.0f, 127.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider10)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider11)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider12)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider13)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider14)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider15)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider16)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(6))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(34))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getInputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 1
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 2
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 3
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 4
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 5
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getOutputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 1
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 2
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 3
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 4
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 5
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 6
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 7
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 8
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 9
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 10
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 11
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 12
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 13
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 14
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 15
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 16
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 17
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 18
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 19
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 20
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 21
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 22
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 23
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 24
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 25
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 26
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 27
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 28
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 29
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 30
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 31
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 32
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 33
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fEntry1, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider10, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider11, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider12, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fEntry2, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider13, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider14, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider15, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fEntry3, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider16, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fButton1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fEntry4, CastInst("FAUSTFLOAT", Double(60.0f)))
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 68
Store = 0
Binop = 0
Numbers = 0
Declare = 68
Cast = 28
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output8, LoadVarInst(kFunArgs, outputs[Int32(8)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output9, LoadVarInst(kFunArgs, outputs[Int32(9)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output10, LoadVarInst(kFunArgs, outputs[Int32(10)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output11, LoadVarInst(kFunArgs, outputs[Int32(11)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output12, LoadVarInst(kFunArgs, outputs[Int32(12)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output13, LoadVarInst(kFunArgs, outputs[Int32(13)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output14, LoadVarInst(kFunArgs, outputs[Int32(14)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output15, LoadVarInst(kFunArgs, outputs[Int32(15)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output16, LoadVarInst(kFunArgs, outputs[Int32(16)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output17, LoadVarInst(kFunArgs, outputs[Int32(17)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output18, LoadVarInst(kFunArgs, outputs[Int32(18)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output19, LoadVarInst(kFunArgs, outputs[Int32(19)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output20, LoadVarInst(kFunArgs, outputs[Int32(20)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output21, LoadVarInst(kFunArgs, outputs[Int32(21)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output22, LoadVarInst(kFunArgs, outputs[Int32(22)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output23, LoadVarInst(kFunArgs, outputs[Int32(23)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output24, LoadVarInst(kFunArgs, outputs[Int32(24)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output25, LoadVarInst(kFunArgs, outputs[Int32(25)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output26, LoadVarInst(kFunArgs, outputs[Int32(26)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output27, LoadVarInst(kFunArgs, outputs[Int32(27)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output28, LoadVarInst(kFunArgs, outputs[Int32(28)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output29, LoadVarInst(kFunArgs, outputs[Int32(29)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output30, LoadVarInst(kFunArgs, outputs[Int32(30)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output31, LoadVarInst(kFunArgs, outputs[Int32(31)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output32, LoadVarInst(kFunArgs, outputs[Int32(32)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output33, LoadVarInst(kFunArgs, outputs[Int32(33)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fCheckbox0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fCheckbox1)))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fEntry0)))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fVslider0)))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fVslider1)))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fVslider2)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fVslider3)))
	DeclareVarInst(stack, "float", fSlow7, CastInst("float", LoadVarInst(struct, fVslider4)))
	DeclareVarInst(stack, "float", fSlow8, CastInst("float", LoadVarInst(struct, fVslider5)))
	DeclareVarInst(stack, "float", fSlow9, CastInst("float", LoadVarInst(struct, fVslider6)))
	DeclareVarInst(stack, "float", fSlow10, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow11, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow12, CastInst("float", LoadVarInst(struct, fVslider7)))
	DeclareVarInst(stack, "float", fSlow13, CastInst("float", LoadVarInst(struct, fVslider8)))
	DeclareVarInst(stack, "float", fSlow14, CastInst("float", LoadVarInst(struct, fVslider9)))
	DeclareVarInst(stack, "float", fSlow15, CastInst("float", LoadVarInst(struct, fEntry1)))
	DeclareVarInst(stack, "float", fSlow16, CastInst("float", LoadVarInst(struct, fVslider10)))
	DeclareVarInst(stack, "float", fSlow17, CastInst("float", LoadVarInst(struct, fVslider11)))
	DeclareVarInst(stack, "float", fSlow18, CastInst("float", LoadVarInst(struct, fVslider12)))
	DeclareVarInst(stack, "float", fSlow19, CastInst("float", LoadVarInst(struct, fEntry2)))
	DeclareVarInst(stack, "float", fSlow20, CastInst("float", LoadVarInst(struct, fVslider13)))
	DeclareVarInst(stack, "float", fSlow21, CastInst("float", LoadVarInst(struct, fVslider14)))
	DeclareVarInst(stack, "float", fSlow22, CastInst("float", LoadVarInst(struct, fVslider15)))
	DeclareVarInst(stack, "float", fSlow23, CastInst("float", LoadVarInst(struct, fEntry3)))
	DeclareVarInst(stack, "float", fSlow24, CastInst("float", LoadVarInst(struct, fVslider16)))
	DeclareVarInst(stack, "float", fSlow25, CastInst("float", LoadVarInst(struct, fButton1)))
	DeclareVarInst(stack, "float", fSlow26, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow27, CastInst("float", LoadVarInst(struct, fEntry4)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 77
Store = 41
Binop = 2
Numbers = 2
Declare = 1
Cast = 46
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow0)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow1)))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow2)))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow3)))
		StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow4)))
		StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow5)))
		StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow6)))
		StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow7)))
		StoreVarInst(stack, output8[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow8)))
		StoreVarInst(stack, output9[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow9)))
		StoreVarInst(stack, output10[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow10)))
		StoreVarInst(stack, output11[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow11)))
		StoreVarInst(stack, output12[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow12)))
		StoreVarInst(stack, output13[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow13)))
		StoreVarInst(stack, output14[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow14)))
		StoreVarInst(stack, output15[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow15)))
		StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)]))))
		StoreVarInst(stack, output16[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph0)))
		StoreVarInst(stack, output17[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow16)))
		StoreVarInst(stack, output18[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow17)))
		StoreVarInst(stack, output19[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow18)))
		StoreVarInst(stack, output20[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow19)))
		StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)]))))
		StoreVarInst(stack, output21[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph1)))
		StoreVarInst(stack, output22[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow20)))
		StoreVarInst(stack, output23[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow21)))
		StoreVarInst(stack, output24[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow22)))
		StoreVarInst(stack, output25[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow23)))
		StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)]))))
		StoreVarInst(stack, output26[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph2)))
		StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)]))))
		StoreVarInst(stack, output27[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fHbargraph0)))
		StoreVarInst(stack, output28[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow24)))
		StoreVarInst(stack, output29[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow25)))
		StoreVarInst(stack, output30[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow26)))
		StoreVarInst(stack, output31[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow27)))
		StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)]))))
		StoreVarInst(stack, output32[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph3)))
		StoreVarInst(struct, fHbargraph1, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)]))))
		StoreVarInst(stack, output33[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fHbargraph1)))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider10)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider11)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider12)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider13)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider14)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider15)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider16)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHbargraph1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fEntry1, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider10, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider11, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider12, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fEntry2, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider13, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider14, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider15, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fEntry3, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider16, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fButton1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fEntry4, CastInst("FAUSTFLOAT", Double(60.0f)))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output8, LoadVarInst(kFunArgs, outputs[Int32(8)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output9, LoadVarInst(kFunArgs, outputs[Int32(9)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output10, LoadVarInst(kFunArgs, outputs[Int32(10)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output11, LoadVarInst(kFunArgs, outputs[Int32(11)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output12, LoadVarInst(kFunArgs, outputs[Int32(12)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output13, LoadVarInst(kFunArgs, outputs[Int32(13)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output14, LoadVarInst(kFunArgs, outputs[Int32(14)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output15, LoadVarInst(kFunArgs, outputs[Int32(15)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output16, LoadVarInst(kFunArgs, outputs[Int32(16)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output17, LoadVarInst(kFunArgs, outputs[Int32(17)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output18, LoadVarInst(kFunArgs, outputs[Int32(18)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output19, LoadVarInst(kFunArgs, outputs[Int32(19)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output20, LoadVarInst(kFunArgs, outputs[Int32(20)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output21, LoadVarInst(kFunArgs, outputs[Int32(21)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output22, LoadVarInst(kFunArgs, outputs[Int32(22)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output23, LoadVarInst(kFunArgs, outputs[Int32(23)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output24, LoadVarInst(kFunArgs, outputs[Int32(24)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output25, LoadVarInst(kFunArgs, outputs[Int32(25)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output26, LoadVarInst(kFunArgs, outputs[Int32(26)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output27, LoadVarInst(kFunArgs, outputs[Int32(27)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output28, LoadVarInst(kFunArgs, outputs[Int32(28)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output29, LoadVarInst(kFunArgs, outputs[Int32(29)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output30, LoadVarInst(kFunArgs, outputs[Int32(30)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output31, LoadVarInst(kFunArgs, outputs[Int32(31)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output32, LoadVarInst(kFunArgs, outputs[Int32(32)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output33, LoadVarInst(kFunArgs, outputs[Int32(33)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fCheckbox0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fCheckbox1)))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fEntry0)))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fVslider0)))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fVslider1)))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fVslider2)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fVslider3)))
	DeclareVarInst(stack, "float", fSlow7, CastInst("float", LoadVarInst(struct, fVslider4)))
	DeclareVarInst(stack, "float", fSlow8, CastInst("float", LoadVarInst(struct, fVslider5)))
	DeclareVarInst(stack, "float", fSlow9, CastInst("float", LoadVarInst(struct, fVslider6)))
	DeclareVarInst(stack, "float", fSlow10, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow11, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow12, CastInst("float", LoadVarInst(struct, fVslider7)))
	DeclareVarInst(stack, "float", fSlow13, CastInst("float", LoadVarInst(struct, fVslider8)))
	DeclareVarInst(stack, "float", fSlow14, CastInst("float", LoadVarInst(struct, fVslider9)))
	DeclareVarInst(stack, "float", fSlow15, CastInst("float", LoadVarInst(struct, fEntry1)))
	DeclareVarInst(stack, "float", fSlow16, CastInst("float", LoadVarInst(struct, fVslider10)))
	DeclareVarInst(stack, "float", fSlow17, CastInst("float", LoadVarInst(struct, fVslider11)))
	DeclareVarInst(stack, "float", fSlow18, CastInst("float", LoadVarInst(struct, fVslider12)))
	DeclareVarInst(stack, "float", fSlow19, CastInst("float", LoadVarInst(struct, fEntry2)))
	DeclareVarInst(stack, "float", fSlow20, CastInst("float", LoadVarInst(struct, fVslider13)))
	DeclareVarInst(stack, "float", fSlow21, CastInst("float", LoadVarInst(struct, fVslider14)))
	DeclareVarInst(stack, "float", fSlow22, CastInst("float", LoadVarInst(struct, fVslider15)))
	DeclareVarInst(stack, "float", fSlow23, CastInst("float", LoadVarInst(struct, fEntry3)))
	DeclareVarInst(stack, "float", fSlow24, CastInst("float", LoadVarInst(struct, fVslider16)))
	DeclareVarInst(stack, "float", fSlow25, CastInst("float", LoadVarInst(struct, fButton1)))
	DeclareVarInst(stack, "float", fSlow26, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow27, CastInst("float", LoadVarInst(struct, fEntry4)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow0)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow1)))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow2)))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow3)))
			StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow4)))
			StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow5)))
			StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow6)))
			StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow7)))
			StoreVarInst(stack, output8[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow8)))
			StoreVarInst(stack, output9[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow9)))
			StoreVarInst(stack, output10[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow10)))
			StoreVarInst(stack, output11[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow11)))
			StoreVarInst(stack, output12[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow12)))
			StoreVarInst(stack, output13[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow13)))
			StoreVarInst(stack, output14[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow14)))
			StoreVarInst(stack, output15[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow15)))
			StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)]))))
			StoreVarInst(stack, output16[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph0)))
			StoreVarInst(stack, output17[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow16)))
			StoreVarInst(stack, output18[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow17)))
			StoreVarInst(stack, output19[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow18)))
			StoreVarInst(stack, output20[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow19)))
			StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)]))))
			StoreVarInst(stack, output21[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph1)))
			StoreVarInst(stack, output22[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow20)))
			StoreVarInst(stack, output23[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow21)))
			StoreVarInst(stack, output24[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow22)))
			StoreVarInst(stack, output25[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow23)))
			StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)]))))
			StoreVarInst(stack, output26[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph2)))
			StoreVarInst(struct, fHbargraph0, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)]))))
			StoreVarInst(stack, output27[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fHbargraph0)))
			StoreVarInst(stack, output28[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow24)))
			StoreVarInst(stack, output29[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow25)))
			StoreVarInst(stack, output30[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow26)))
			StoreVarInst(stack, output31[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fSlow27)))
			StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)]))))
			StoreVarInst(stack, output32[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph3)))
			StoreVarInst(struct, fHbargraph1, CastInst("FAUSTFLOAT", CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)]))))
			StoreVarInst(stack, output33[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fHbargraph1)))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 136 bytes
Heap size = 140 bytes
Stack size in compute = 432 bytes

