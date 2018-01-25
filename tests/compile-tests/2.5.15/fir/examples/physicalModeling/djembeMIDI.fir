======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("djembe")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("midi")
	AddMetaDeclareInst(fHslider4, "0", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("freq", fHslider4, 60.0f, 50.0f, 100.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddHorizontalSlider("gain", fHslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("otherParams")
	AddMetaDeclareInst(fHslider2, "0", "")
	AddMetaDeclareInst(fHslider2, "midi", "ctrl 1")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("strikePosition", fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider3, "1", "")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("strikeSharpness", fHslider3, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddHorizontalSlider("outGain", fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(fButton0, "3", "")
	AddButtonInst("gate"fButton0)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "cosf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, int, iRec3[2])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, float, fRec10[3])
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, float, fRec11[3])
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, float, fRec13[3])
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, float, fRec15[3])
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, "float", fConst43)
	DeclareVarInst(struct, "float", fConst44)
	DeclareVarInst(struct, float, fRec16[3])
	DeclareVarInst(struct, "float", fConst45)
	DeclareVarInst(struct, "float", fConst46)
	DeclareVarInst(struct, "float", fConst47)
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, "float", fConst48)
	DeclareVarInst(struct, "float", fConst49)
	DeclareVarInst(struct, "float", fConst50)
	DeclareVarInst(struct, float, fRec18[3])
	DeclareVarInst(struct, "float", fConst51)
	DeclareVarInst(struct, "float", fConst52)
	DeclareVarInst(struct, "float", fConst53)
	DeclareVarInst(struct, float, fRec19[3])
	DeclareVarInst(struct, "float", fConst54)
	DeclareVarInst(struct, "float", fConst55)
	DeclareVarInst(struct, "float", fConst56)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, "float", fConst57)
	DeclareVarInst(struct, "float", fConst58)
	DeclareVarInst(struct, "float", fConst59)
	DeclareVarInst(struct, float, fRec21[3])
	DeclareVarInst(struct, "float", fConst60)
	DeclareVarInst(struct, "float", fConst61)
	DeclareVarInst(struct, "float", fConst62)
	DeclareVarInst(struct, float, fRec22[3])
	DeclareVarInst(struct, "float", fConst63)
	DeclareVarInst(struct, "float", fConst64)
	DeclareVarInst(struct, "float", fConst65)
	DeclareVarInst(struct, float, fRec23[3])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getInputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
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
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00400000019f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(500.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst6, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst5))))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst8, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst9, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.569999993f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst10, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst9))))
	StoreVarInst(struct, fConst11, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst9)))
	StoreVarInst(struct, fConst12, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.540000021f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst13, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst12))))
	StoreVarInst(struct, fConst14, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst12)))
	StoreVarInst(struct, fConst15, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.50999999f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst16, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst15))))
	StoreVarInst(struct, fConst17, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst15)))
	StoreVarInst(struct, fConst18, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.479999989f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst19, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst18))))
	StoreVarInst(struct, fConst20, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst18)))
	StoreVarInst(struct, fConst21, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.449999988f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst22, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst21))))
	StoreVarInst(struct, fConst23, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst21)))
	StoreVarInst(struct, fConst24, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.419999987f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst25, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst24))))
	StoreVarInst(struct, fConst26, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst24)))
	StoreVarInst(struct, fConst27, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.389999986f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst28, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst29, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst27)))
	StoreVarInst(struct, fConst30, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.360000014f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst31, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst30))))
	StoreVarInst(struct, fConst32, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst30)))
	StoreVarInst(struct, fConst33, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.330000013f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst34, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst33))))
	StoreVarInst(struct, fConst35, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst33)))
	StoreVarInst(struct, fConst36, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.300000012f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst37, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst36))))
	StoreVarInst(struct, fConst38, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst36)))
	StoreVarInst(struct, fConst39, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.270000011f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst40, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst39))))
	StoreVarInst(struct, fConst41, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst39)))
	StoreVarInst(struct, fConst42, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.239999995f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst43, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst42))))
	StoreVarInst(struct, fConst44, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst42)))
	StoreVarInst(struct, fConst45, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.209999993f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst46, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst45))))
	StoreVarInst(struct, fConst47, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst45)))
	StoreVarInst(struct, fConst48, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.180000007f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst49, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst48))))
	StoreVarInst(struct, fConst50, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst48)))
	StoreVarInst(struct, fConst51, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.150000006f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst52, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst51))))
	StoreVarInst(struct, fConst53, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst51)))
	StoreVarInst(struct, fConst54, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.119999997f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst55, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst54))))
	StoreVarInst(struct, fConst56, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst54)))
	StoreVarInst(struct, fConst57, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0900000036f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst58, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst57))))
	StoreVarInst(struct, fConst59, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst57)))
	StoreVarInst(struct, fConst60, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0599999987f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst61, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst60))))
	StoreVarInst(struct, fConst62, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst60)))
	StoreVarInst(struct, fConst63, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0299999993f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst64, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst63))))
	StoreVarInst(struct, fConst65, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst63)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(60.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec3[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(3))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(3))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(3))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(3))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(3))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(3))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(3))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(3))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(3))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(3))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(3))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(3))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(3))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(3))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(3))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 94
Store = 0
Binop = 94
Numbers = 44
Declare = 44
Cast = 6
Select = 0
Loop = 0
Funcall = 24

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("*", Float(15000.0f), LoadVarInst(stack, fSlow1)), Float(500.0f)))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow3), Float(1.41421354f)), LoadVarInst(stack, fSlow2)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", CastInst("float", LoadVarInst(struct, fHslider1)), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("*", Float(500.0f), LoadVarInst(stack, fSlow1)), Float(40.0f)))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow7), Float(1.41421354f)), LoadVarInst(stack, fSlow6)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow7), Float(-1.41421354f)), LoadVarInst(stack, fSlow6)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow2))))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow3), Float(-1.41421354f)), LoadVarInst(stack, fSlow2)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow16, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow17, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("/", LoadVarInst(struct, fConst4), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow21, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("*", LoadVarInst(struct, fConst6), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(stack, fSlow21)))))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("*", LoadVarInst(struct, fConst10), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(200.0f))))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", LoadVarInst(struct, fConst13), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(400.0f))))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("*", LoadVarInst(struct, fConst16), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(600.0f))))))
	DeclareVarInst(stack, "float", fSlow26, BinopInst("*", LoadVarInst(struct, fConst19), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(800.0f))))))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("*", LoadVarInst(struct, fConst22), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1000.0f))))))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("*", LoadVarInst(struct, fConst25), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1200.0f))))))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", LoadVarInst(struct, fConst28), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1400.0f))))))
	DeclareVarInst(stack, "float", fSlow30, BinopInst("*", LoadVarInst(struct, fConst31), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1600.0f))))))
	DeclareVarInst(stack, "float", fSlow31, BinopInst("*", LoadVarInst(struct, fConst34), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1800.0f))))))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("*", LoadVarInst(struct, fConst37), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2000.0f))))))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("*", LoadVarInst(struct, fConst40), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2200.0f))))))
	DeclareVarInst(stack, "float", fSlow34, BinopInst("*", LoadVarInst(struct, fConst43), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2400.0f))))))
	DeclareVarInst(stack, "float", fSlow35, BinopInst("*", LoadVarInst(struct, fConst46), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2600.0f))))))
	DeclareVarInst(stack, "float", fSlow36, BinopInst("*", LoadVarInst(struct, fConst49), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2800.0f))))))
	DeclareVarInst(stack, "float", fSlow37, BinopInst("*", LoadVarInst(struct, fConst52), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3000.0f))))))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("*", LoadVarInst(struct, fConst55), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3200.0f))))))
	DeclareVarInst(stack, "float", fSlow39, BinopInst("*", LoadVarInst(struct, fConst58), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3400.0f))))))
	DeclareVarInst(stack, "float", fSlow40, BinopInst("*", LoadVarInst(struct, fConst61), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3600.0f))))))
	DeclareVarInst(stack, "float", fSlow41, BinopInst("*", LoadVarInst(struct, fConst64), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3800.0f))))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 240
Store = 77
Binop = 180
Numbers = 109
Declare = 4
Cast = 3
Select = 0
Loop = 1
Funcall = 1

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec3[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec3[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec3[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec2[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec2[Int32(1)]))))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec2[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec2[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec2[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec1[Int32(2)]))))))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow16))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow17))
		StoreVarInst(struct, fRec4[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow16), LoadVarInst(struct, fVec0[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fSlow18), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("-", LoadVarInst(stack, fSlow17), LoadVarInst(struct, fVec1[Int32(1)])))), Float(1.0f)))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("<", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fSlow19)))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec1[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec1[Int32(1)])))), Select2Inst(LoadVarInst(stack, iTemp0) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec4[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp0) BinopInst("*", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fRec4[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fSlow18)) BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fSlow19)))), Float(1.0f)) Float(0.0f))))))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec0[Int32(2)])))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow23), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst11), LoadVarInst(struct, fRec5[Int32(2)])))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst14), LoadVarInst(struct, fRec6[Int32(2)])))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), LoadVarInst(struct, fRec7[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst17), LoadVarInst(struct, fRec7[Int32(2)])))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec8[Int32(2)])))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow27), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst23), LoadVarInst(struct, fRec9[Int32(2)])))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow28), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec10[Int32(2)])))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst29), LoadVarInst(struct, fRec11[Int32(2)])))))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow30), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec12[Int32(2)])))))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow31), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst35), LoadVarInst(struct, fRec13[Int32(2)])))))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow32), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec14[Int32(2)])))))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow33), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst41), LoadVarInst(struct, fRec15[Int32(2)])))))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow34), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec16[Int32(2)])))))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst47), LoadVarInst(struct, fRec17[Int32(2)])))))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow36), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec18[Int32(2)])))))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow37), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst53), LoadVarInst(struct, fRec19[Int32(2)])))))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow38), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec20[Int32(2)])))))
		StoreVarInst(struct, fRec21[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow39), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst59), LoadVarInst(struct, fRec21[Int32(2)])))))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec22[Int32(2)])))))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow41), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(struct, fRec23[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("*", Float(0.25f), BinopInst("-", LoadVarInst(struct, fRec5[Int32(0)]), LoadVarInst(struct, fRec5[Int32(2)])))), BinopInst("*", Float(0.111111112f), BinopInst("-", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(struct, fRec6[Int32(2)])))), BinopInst("*", Float(0.0625f), BinopInst("-", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(struct, fRec7[Int32(2)])))), BinopInst("*", Float(0.0399999991f), BinopInst("-", LoadVarInst(struct, fRec8[Int32(0)]), LoadVarInst(struct, fRec8[Int32(2)])))), BinopInst("*", Float(0.027777778f), BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fRec9[Int32(2)])))), BinopInst("*", Float(0.0204081628f), BinopInst("-", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(struct, fRec10[Int32(2)])))), BinopInst("*", Float(0.015625f), BinopInst("-", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(struct, fRec11[Int32(2)])))), BinopInst("*", Float(0.0123456791f), BinopInst("-", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fRec12[Int32(2)])))), BinopInst("*", Float(0.00999999978f), BinopInst("-", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(struct, fRec13[Int32(2)])))), BinopInst("*", Float(0.00826446246f), BinopInst("-", LoadVarInst(struct, fRec14[Int32(0)]), LoadVarInst(struct, fRec14[Int32(2)])))), BinopInst("*", Float(0.0069444445f), BinopInst("-", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(struct, fRec15[Int32(2)])))), BinopInst("*", Float(0.00591715984f), BinopInst("-", LoadVarInst(struct, fRec16[Int32(0)]), LoadVarInst(struct, fRec16[Int32(2)])))), BinopInst("*", Float(0.00510204071f), BinopInst("-", LoadVarInst(struct, fRec17[Int32(0)]), LoadVarInst(struct, fRec17[Int32(2)])))), BinopInst("*", Float(0.00444444455f), BinopInst("-", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fRec18[Int32(2)])))), BinopInst("*", Float(0.00390625f), BinopInst("-", LoadVarInst(struct, fRec19[Int32(0)]), LoadVarInst(struct, fRec19[Int32(2)])))), BinopInst("*", Float(0.00346020772f), BinopInst("-", LoadVarInst(struct, fRec20[Int32(0)]), LoadVarInst(struct, fRec20[Int32(2)])))), BinopInst("*", Float(0.00308641978f), BinopInst("-", LoadVarInst(struct, fRec21[Int32(0)]), LoadVarInst(struct, fRec21[Int32(2)])))), BinopInst("*", Float(0.00277008303f), BinopInst("-", LoadVarInst(struct, fRec22[Int32(0)]), LoadVarInst(struct, fRec22[Int32(2)])))), BinopInst("*", Float(0.00249999994f), BinopInst("-", LoadVarInst(struct, fRec23[Int32(0)]), LoadVarInst(struct, fRec23[Int32(2)])))), LoadVarInst(struct, fRec0[Int32(2)]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp2)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp2)))
		StoreVarInst(struct, iRec3[Int32(1)], LoadVarInst(struct, iRec3[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(2)], LoadVarInst(struct, fRec10[Int32(1)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(2)], LoadVarInst(struct, fRec11[Int32(1)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(2)], LoadVarInst(struct, fRec13[Int32(1)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(2)], LoadVarInst(struct, fRec15[Int32(1)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(2)], LoadVarInst(struct, fRec16[Int32(1)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(2)], LoadVarInst(struct, fRec17[Int32(1)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(2)], LoadVarInst(struct, fRec18[Int32(1)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(2)], LoadVarInst(struct, fRec19[Int32(1)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(2)], LoadVarInst(struct, fRec20[Int32(1)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(2)], LoadVarInst(struct, fRec21[Int32(1)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(2)], LoadVarInst(struct, fRec22[Int32(1)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(2)], LoadVarInst(struct, fRec23[Int32(1)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, int, iRec3[2])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, float, fRec10[3])
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, float, fRec11[3])
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, float, fRec13[3])
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, float, fRec15[3])
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, "float", fConst43)
	DeclareVarInst(struct, "float", fConst44)
	DeclareVarInst(struct, float, fRec16[3])
	DeclareVarInst(struct, "float", fConst45)
	DeclareVarInst(struct, "float", fConst46)
	DeclareVarInst(struct, "float", fConst47)
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, "float", fConst48)
	DeclareVarInst(struct, "float", fConst49)
	DeclareVarInst(struct, "float", fConst50)
	DeclareVarInst(struct, float, fRec18[3])
	DeclareVarInst(struct, "float", fConst51)
	DeclareVarInst(struct, "float", fConst52)
	DeclareVarInst(struct, "float", fConst53)
	DeclareVarInst(struct, float, fRec19[3])
	DeclareVarInst(struct, "float", fConst54)
	DeclareVarInst(struct, "float", fConst55)
	DeclareVarInst(struct, "float", fConst56)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, "float", fConst57)
	DeclareVarInst(struct, "float", fConst58)
	DeclareVarInst(struct, "float", fConst59)
	DeclareVarInst(struct, float, fRec21[3])
	DeclareVarInst(struct, "float", fConst60)
	DeclareVarInst(struct, "float", fConst61)
	DeclareVarInst(struct, "float", fConst62)
	DeclareVarInst(struct, float, fRec22[3])
	DeclareVarInst(struct, "float", fConst63)
	DeclareVarInst(struct, "float", fConst64)
	DeclareVarInst(struct, "float", fConst65)
	DeclareVarInst(struct, float, fRec23[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00400000019f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(500.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst6, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst5))))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst8, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst9, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.569999993f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst10, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst9))))
	StoreVarInst(struct, fConst11, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst9)))
	StoreVarInst(struct, fConst12, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.540000021f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst13, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst12))))
	StoreVarInst(struct, fConst14, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst12)))
	StoreVarInst(struct, fConst15, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.50999999f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst16, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst15))))
	StoreVarInst(struct, fConst17, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst15)))
	StoreVarInst(struct, fConst18, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.479999989f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst19, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst18))))
	StoreVarInst(struct, fConst20, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst18)))
	StoreVarInst(struct, fConst21, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.449999988f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst22, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst21))))
	StoreVarInst(struct, fConst23, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst21)))
	StoreVarInst(struct, fConst24, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.419999987f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst25, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst24))))
	StoreVarInst(struct, fConst26, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst24)))
	StoreVarInst(struct, fConst27, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.389999986f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst28, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst29, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst27)))
	StoreVarInst(struct, fConst30, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.360000014f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst31, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst30))))
	StoreVarInst(struct, fConst32, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst30)))
	StoreVarInst(struct, fConst33, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.330000013f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst34, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst33))))
	StoreVarInst(struct, fConst35, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst33)))
	StoreVarInst(struct, fConst36, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.300000012f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst37, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst36))))
	StoreVarInst(struct, fConst38, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst36)))
	StoreVarInst(struct, fConst39, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.270000011f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst40, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst39))))
	StoreVarInst(struct, fConst41, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst39)))
	StoreVarInst(struct, fConst42, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.239999995f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst43, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst42))))
	StoreVarInst(struct, fConst44, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst42)))
	StoreVarInst(struct, fConst45, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.209999993f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst46, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst45))))
	StoreVarInst(struct, fConst47, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst45)))
	StoreVarInst(struct, fConst48, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.180000007f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst49, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst48))))
	StoreVarInst(struct, fConst50, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst48)))
	StoreVarInst(struct, fConst51, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.150000006f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst52, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst51))))
	StoreVarInst(struct, fConst53, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst51)))
	StoreVarInst(struct, fConst54, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.119999997f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst55, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst54))))
	StoreVarInst(struct, fConst56, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst54)))
	StoreVarInst(struct, fConst57, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0900000036f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst58, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst57))))
	StoreVarInst(struct, fConst59, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst57)))
	StoreVarInst(struct, fConst60, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0599999987f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst61, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst60))))
	StoreVarInst(struct, fConst62, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst60)))
	StoreVarInst(struct, fConst63, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0299999993f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst64, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst63))))
	StoreVarInst(struct, fConst65, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst63)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(60.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec3[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(3))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(3))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(3))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(3))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(3))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(3))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(3))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(3))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(3))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(3))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(3))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(3))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(3))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(3))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(3))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("*", Float(15000.0f), LoadVarInst(stack, fSlow1)), Float(500.0f)))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow3), Float(1.41421354f)), LoadVarInst(stack, fSlow2)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", CastInst("float", LoadVarInst(struct, fHslider1)), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("*", Float(500.0f), LoadVarInst(stack, fSlow1)), Float(40.0f)))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow7), Float(1.41421354f)), LoadVarInst(stack, fSlow6)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow7), Float(-1.41421354f)), LoadVarInst(stack, fSlow6)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow2))))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow3), Float(-1.41421354f)), LoadVarInst(stack, fSlow2)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow16, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow17, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("/", LoadVarInst(struct, fConst4), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow21, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("*", LoadVarInst(struct, fConst6), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(stack, fSlow21)))))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("*", LoadVarInst(struct, fConst10), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(200.0f))))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", LoadVarInst(struct, fConst13), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(400.0f))))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("*", LoadVarInst(struct, fConst16), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(600.0f))))))
	DeclareVarInst(stack, "float", fSlow26, BinopInst("*", LoadVarInst(struct, fConst19), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(800.0f))))))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("*", LoadVarInst(struct, fConst22), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1000.0f))))))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("*", LoadVarInst(struct, fConst25), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1200.0f))))))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", LoadVarInst(struct, fConst28), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1400.0f))))))
	DeclareVarInst(stack, "float", fSlow30, BinopInst("*", LoadVarInst(struct, fConst31), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1600.0f))))))
	DeclareVarInst(stack, "float", fSlow31, BinopInst("*", LoadVarInst(struct, fConst34), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(1800.0f))))))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("*", LoadVarInst(struct, fConst37), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2000.0f))))))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("*", LoadVarInst(struct, fConst40), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2200.0f))))))
	DeclareVarInst(stack, "float", fSlow34, BinopInst("*", LoadVarInst(struct, fConst43), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2400.0f))))))
	DeclareVarInst(stack, "float", fSlow35, BinopInst("*", LoadVarInst(struct, fConst46), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2600.0f))))))
	DeclareVarInst(stack, "float", fSlow36, BinopInst("*", LoadVarInst(struct, fConst49), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(2800.0f))))))
	DeclareVarInst(stack, "float", fSlow37, BinopInst("*", LoadVarInst(struct, fConst52), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3000.0f))))))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("*", LoadVarInst(struct, fConst55), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3200.0f))))))
	DeclareVarInst(stack, "float", fSlow39, BinopInst("*", LoadVarInst(struct, fConst58), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3400.0f))))))
	DeclareVarInst(stack, "float", fSlow40, BinopInst("*", LoadVarInst(struct, fConst61), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3600.0f))))))
	DeclareVarInst(stack, "float", fSlow41, BinopInst("*", LoadVarInst(struct, fConst64), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(stack, fSlow21), Float(3800.0f))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec3[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec3[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec3[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec2[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec2[Int32(1)]))))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec2[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec2[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec2[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec1[Int32(2)]))))))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow16))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow17))
			StoreVarInst(struct, fRec4[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow16), LoadVarInst(struct, fVec0[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fSlow18), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("-", LoadVarInst(stack, fSlow17), LoadVarInst(struct, fVec1[Int32(1)])))), Float(1.0f)))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("<", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fSlow19)))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec1[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec1[Int32(1)])))), Select2Inst(LoadVarInst(stack, iTemp0) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec4[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp0) BinopInst("*", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fRec4[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fSlow18)) BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow20), BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fSlow19)))), Float(1.0f)) Float(0.0f))))))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec0[Int32(2)])))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow23), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst11), LoadVarInst(struct, fRec5[Int32(2)])))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst14), LoadVarInst(struct, fRec6[Int32(2)])))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), LoadVarInst(struct, fRec7[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst17), LoadVarInst(struct, fRec7[Int32(2)])))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec8[Int32(2)])))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow27), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst23), LoadVarInst(struct, fRec9[Int32(2)])))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow28), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec10[Int32(2)])))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst29), LoadVarInst(struct, fRec11[Int32(2)])))))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow30), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec12[Int32(2)])))))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow31), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst35), LoadVarInst(struct, fRec13[Int32(2)])))))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow32), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec14[Int32(2)])))))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow33), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst41), LoadVarInst(struct, fRec15[Int32(2)])))))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow34), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec16[Int32(2)])))))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst47), LoadVarInst(struct, fRec17[Int32(2)])))))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow36), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec18[Int32(2)])))))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow37), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst53), LoadVarInst(struct, fRec19[Int32(2)])))))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow38), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec20[Int32(2)])))))
			StoreVarInst(struct, fRec21[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow39), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst59), LoadVarInst(struct, fRec21[Int32(2)])))))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec22[Int32(2)])))))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow41), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(struct, fRec23[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("*", Float(0.25f), BinopInst("-", LoadVarInst(struct, fRec5[Int32(0)]), LoadVarInst(struct, fRec5[Int32(2)])))), BinopInst("*", Float(0.111111112f), BinopInst("-", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(struct, fRec6[Int32(2)])))), BinopInst("*", Float(0.0625f), BinopInst("-", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(struct, fRec7[Int32(2)])))), BinopInst("*", Float(0.0399999991f), BinopInst("-", LoadVarInst(struct, fRec8[Int32(0)]), LoadVarInst(struct, fRec8[Int32(2)])))), BinopInst("*", Float(0.027777778f), BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fRec9[Int32(2)])))), BinopInst("*", Float(0.0204081628f), BinopInst("-", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(struct, fRec10[Int32(2)])))), BinopInst("*", Float(0.015625f), BinopInst("-", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(struct, fRec11[Int32(2)])))), BinopInst("*", Float(0.0123456791f), BinopInst("-", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fRec12[Int32(2)])))), BinopInst("*", Float(0.00999999978f), BinopInst("-", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(struct, fRec13[Int32(2)])))), BinopInst("*", Float(0.00826446246f), BinopInst("-", LoadVarInst(struct, fRec14[Int32(0)]), LoadVarInst(struct, fRec14[Int32(2)])))), BinopInst("*", Float(0.0069444445f), BinopInst("-", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(struct, fRec15[Int32(2)])))), BinopInst("*", Float(0.00591715984f), BinopInst("-", LoadVarInst(struct, fRec16[Int32(0)]), LoadVarInst(struct, fRec16[Int32(2)])))), BinopInst("*", Float(0.00510204071f), BinopInst("-", LoadVarInst(struct, fRec17[Int32(0)]), LoadVarInst(struct, fRec17[Int32(2)])))), BinopInst("*", Float(0.00444444455f), BinopInst("-", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fRec18[Int32(2)])))), BinopInst("*", Float(0.00390625f), BinopInst("-", LoadVarInst(struct, fRec19[Int32(0)]), LoadVarInst(struct, fRec19[Int32(2)])))), BinopInst("*", Float(0.00346020772f), BinopInst("-", LoadVarInst(struct, fRec20[Int32(0)]), LoadVarInst(struct, fRec20[Int32(2)])))), BinopInst("*", Float(0.00308641978f), BinopInst("-", LoadVarInst(struct, fRec21[Int32(0)]), LoadVarInst(struct, fRec21[Int32(2)])))), BinopInst("*", Float(0.00277008303f), BinopInst("-", LoadVarInst(struct, fRec22[Int32(0)]), LoadVarInst(struct, fRec22[Int32(2)])))), BinopInst("*", Float(0.00249999994f), BinopInst("-", LoadVarInst(struct, fRec23[Int32(0)]), LoadVarInst(struct, fRec23[Int32(2)])))), LoadVarInst(struct, fRec0[Int32(2)]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp2)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp2)))
			StoreVarInst(struct, iRec3[Int32(1)], LoadVarInst(struct, iRec3[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(2)], LoadVarInst(struct, fRec10[Int32(1)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(2)], LoadVarInst(struct, fRec11[Int32(1)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(2)], LoadVarInst(struct, fRec13[Int32(1)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(2)], LoadVarInst(struct, fRec15[Int32(1)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(2)], LoadVarInst(struct, fRec16[Int32(1)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(2)], LoadVarInst(struct, fRec17[Int32(1)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(2)], LoadVarInst(struct, fRec18[Int32(1)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(2)], LoadVarInst(struct, fRec19[Int32(1)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(2)], LoadVarInst(struct, fRec20[Int32(1)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(2)], LoadVarInst(struct, fRec21[Int32(1)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(2)], LoadVarInst(struct, fRec22[Int32(1)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(2)], LoadVarInst(struct, fRec23[Int32(1)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 576 bytes
Heap size = 588 bytes
Stack size in compute = 184 bytes

