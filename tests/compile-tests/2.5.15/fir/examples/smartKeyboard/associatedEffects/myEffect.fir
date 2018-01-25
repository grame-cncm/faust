======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER  ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and  references")
	OpenHorizontalBox("Zita_Rev1")
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("Input")
	AddMetaDeclareInst(fVslider6, "1", "")
	AddMetaDeclareInst(fVslider6, "style", "knob")
	AddMetaDeclareInst(fVslider6, "tooltip", "Delay in ms   before reverberation begins")
	AddMetaDeclareInst(fVslider6, "unit", "ms")
	AddVerticalSlider("In Delay", fVslider6, 60.0f, 20.0f, 100.0f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("Decay Times in Bands (see tooltips)")
	AddMetaDeclareInst(fVslider5, "1", "")
	AddMetaDeclareInst(fVslider5, "scale", "log")
	AddMetaDeclareInst(fVslider5, "style", "knob")
	AddMetaDeclareInst(fVslider5, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies")
	AddMetaDeclareInst(fVslider5, "unit", "Hz")
	AddVerticalSlider("LF X", fVslider5, 200.0f, 50.0f, 1000.0f, 1.0f)
	AddMetaDeclareInst(fVslider4, "2", "")
	AddMetaDeclareInst(fVslider4, "scale", "log")
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddMetaDeclareInst(fVslider4, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band")
	AddMetaDeclareInst(fVslider4, "unit", "s")
	AddVerticalSlider("Low RT60", fVslider4, 3.0f, 1.0f, 8.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider2, "3", "")
	AddMetaDeclareInst(fVslider2, "scale", "log")
	AddMetaDeclareInst(fVslider2, "style", "knob")
	AddMetaDeclareInst(fVslider2, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band")
	AddMetaDeclareInst(fVslider2, "unit", "s")
	AddVerticalSlider("Mid RT60", fVslider2, 2.0f, 1.0f, 8.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider3, "4", "")
	AddMetaDeclareInst(fVslider3, "scale", "log")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60")
	AddMetaDeclareInst(fVslider3, "unit", "Hz")
	AddVerticalSlider("HF Damping", fVslider3, 6000.0f, 1500.0f, 23520.0f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	OpenHorizontalBox("RM Peaking Equalizer 1")
	AddMetaDeclareInst(fVslider7, "1", "")
	AddMetaDeclareInst(fVslider7, "scale", "log")
	AddMetaDeclareInst(fVslider7, "style", "knob")
	AddMetaDeclareInst(fVslider7, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1")
	AddMetaDeclareInst(fVslider7, "unit", "Hz")
	AddVerticalSlider("Eq1 Freq", fVslider7, 315.0f, 40.0f, 2500.0f, 1.0f)
	AddMetaDeclareInst(fVslider8, "2", "")
	AddMetaDeclareInst(fVslider8, "style", "knob")
	AddMetaDeclareInst(fVslider8, "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 1")
	AddMetaDeclareInst(fVslider8, "unit", "dB")
	AddVerticalSlider("Eq1 Level", fVslider8, 0.0f, -15.0f, 15.0f, 0.100000001f)
	CloseboxInst
	AddMetaDeclareInst(0, "4", "")
	OpenHorizontalBox("RM Peaking Equalizer 2")
	AddMetaDeclareInst(fVslider0, "1", "")
	AddMetaDeclareInst(fVslider0, "scale", "log")
	AddMetaDeclareInst(fVslider0, "style", "knob")
	AddMetaDeclareInst(fVslider0, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2")
	AddMetaDeclareInst(fVslider0, "unit", "Hz")
	AddVerticalSlider("Eq2 Freq", fVslider0, 1500.0f, 160.0f, 10000.0f, 1.0f)
	AddMetaDeclareInst(fVslider1, "2", "")
	AddMetaDeclareInst(fVslider1, "style", "knob")
	AddMetaDeclareInst(fVslider1, "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 2")
	AddMetaDeclareInst(fVslider1, "unit", "dB")
	AddVerticalSlider("Eq2 Level", fVslider1, 0.0f, -15.0f, 15.0f, 0.100000001f)
	CloseboxInst
	AddMetaDeclareInst(0, "5", "")
	OpenHorizontalBox("Output")
	AddMetaDeclareInst(fVslider9, "1", "")
	AddMetaDeclareInst(fVslider9, "style", "knob")
	AddMetaDeclareInst(fVslider9, "tooltip", "-1 = dry, 1 = wet")
	AddVerticalSlider("Dry/Wet Mix", fVslider9, 0.0f, -1.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider10, "2", "")
	AddMetaDeclareInst(fVslider10, "style", "knob")
	AddMetaDeclareInst(fVslider10, "tooltip", "Output scale   factor")
	AddMetaDeclareInst(fVslider10, "unit", "dB")
	AddVerticalSlider("Level", fVslider10, -20.0f, -70.0f, 40.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[32768])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fVec1[16384])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fVec2[2048])
	DeclareVarInst(struct, "int", iConst9)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fVec3[16384])
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "int", iConst13)
	DeclareVarInst(struct, float, fVec4[16384])
	DeclareVarInst(struct, float, fVec5[2048])
	DeclareVarInst(struct, "int", iConst14)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fVec6[16384])
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, "int", iConst18)
	DeclareVarInst(struct, float, fVec7[4096])
	DeclareVarInst(struct, "int", iConst19)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fVec8[16384])
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "int", iConst23)
	DeclareVarInst(struct, float, fVec9[4096])
	DeclareVarInst(struct, "int", iConst24)
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fVec10[16384])
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "int", iConst28)
	DeclareVarInst(struct, float, fVec11[2048])
	DeclareVarInst(struct, "int", iConst29)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fVec12[32768])
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, "int", iConst33)
	DeclareVarInst(struct, float, fVec13[4096])
	DeclareVarInst(struct, "int", iConst34)
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, float, fRec35[2])
	DeclareVarInst(struct, float, fVec14[16384])
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "int", iConst38)
	DeclareVarInst(struct, float, fVec15[4096])
	DeclareVarInst(struct, "int", iConst39)
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, float, fRec40[2])
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, float, fVec16[32768])
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, "int", iConst43)
	DeclareVarInst(struct, float, fVec17[4096])
	DeclareVarInst(struct, "int", iConst44)
	DeclareVarInst(struct, float, fRec37[2])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec41[3])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, float, fRec42[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider10)
	DeclareVarInst(struct, float, fRec43[2])
	DeclareVarInst(struct, float, fRec45[3])
	DeclareVarInst(struct, float, fRec44[3])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(2))
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219990999f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst3, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst2))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0191229992f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst7, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst2), LoadVarInst(struct, fConst6))))))
	StoreVarInst(struct, fConst8, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, iConst9, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst6), Float(-1.0f))))))
	StoreVarInst(struct, fConst10, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153128996f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst11, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst10))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst12, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0203460008f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst13, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst10), LoadVarInst(struct, fConst12))))))
	StoreVarInst(struct, iConst14, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst12), Float(-1.0f))))))
	StoreVarInst(struct, fConst15, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713001f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst16, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst15))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst17, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0229039993f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst18, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst15), LoadVarInst(struct, fConst17))))))
	StoreVarInst(struct, iConst19, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst17), Float(-1.0f))))))
	StoreVarInst(struct, fConst20, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst21, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst20))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst22, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0316039994f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst23, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst20), LoadVarInst(struct, fConst22))))))
	StoreVarInst(struct, iConst24, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.0f))))))
	StoreVarInst(struct, fConst25, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst26, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst25))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst27, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0134579996f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst28, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst25), LoadVarInst(struct, fConst27))))))
	StoreVarInst(struct, iConst29, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst27), Float(-1.0f))))))
	StoreVarInst(struct, fConst30, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389003f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst31, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst30))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst32, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0244210009f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst33, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst30), LoadVarInst(struct, fConst32))))))
	StoreVarInst(struct, iConst34, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst32), Float(-1.0f))))))
	StoreVarInst(struct, fConst35, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst36, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst35))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst37, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0292910002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst38, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst35), LoadVarInst(struct, fConst37))))))
	StoreVarInst(struct, iConst39, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst37), Float(-1.0f))))))
	StoreVarInst(struct, fConst40, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891012f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst41, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst40))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst42, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0273330007f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst43, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst40), LoadVarInst(struct, fConst42))))))
	StoreVarInst(struct, iConst44, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst42), Float(-1.0f))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(1500.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(6000.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(3.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(200.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(315.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider10, CastInst("FAUSTFLOAT", Double(-20.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(32768))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(16384))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2048))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(16384))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(16384))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(16384))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(4096))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(16384))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(4096))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(16384))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2048))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(32768))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(4096))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(16384))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(4096))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(32768))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec16[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(4096))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec17[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(3))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(3))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(3))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(3))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(3))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(3))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(3))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(3))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(3))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 182
Store = 0
Binop = 144
Numbers = 73
Declare = 96
Cast = 12
Select = 0
Loop = 0
Funcall = 69

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fVslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider1)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("/", LoadVarInst(stack, fSlow0), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fSlow1))))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)), BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fVslider2)))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst3), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst4), CastInst("float", LoadVarInst(struct, fVslider3)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fSlow7))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("/", LoadVarInst(stack, fSlow8), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow11, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow8)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow9))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fSlow11)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", LoadVarInst(stack, fSlow11), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow10)))))
	DeclareVarInst(stack, "float", fSlow14, CastInst("float", LoadVarInst(struct, fVslider4)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst3), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow5)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst5), CastInst("float", LoadVarInst(struct, fVslider5))))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("+", LoadVarInst(stack, fSlow16), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow16)), LoadVarInst(stack, fSlow17))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "int", iSlow20, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("*", LoadVarInst(struct, fConst8), CastInst("float", LoadVarInst(struct, fVslider6)))))))
	DeclareVarInst(stack, "float", fSlow21, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst11), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow22, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow22))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow22)))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("/", LoadVarInst(stack, fSlow23), LoadVarInst(stack, fSlow24)))
	DeclareVarInst(stack, "float", fSlow26, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow23)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow24))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("-", LoadVarInst(stack, fSlow25), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("*", LoadVarInst(stack, fSlow21), BinopInst("+", LoadVarInst(stack, fSlow26), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow25)))))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst11), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow21)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow30, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst16), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow31, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow30)))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow31))))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow31)))
	DeclareVarInst(stack, "float", fSlow34, BinopInst("/", LoadVarInst(stack, fSlow32), LoadVarInst(stack, fSlow33)))
	DeclareVarInst(stack, "float", fSlow35, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow32)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow33))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow36, BinopInst("-", LoadVarInst(stack, fSlow34), LoadVarInst(stack, fSlow35)))
	DeclareVarInst(stack, "float", fSlow37, BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("+", LoadVarInst(stack, fSlow35), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow34)))))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst16), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow30)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow39, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst21), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow40, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow39)))
	DeclareVarInst(stack, "float", fSlow41, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow40))))
	DeclareVarInst(stack, "float", fSlow42, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow40)))
	DeclareVarInst(stack, "float", fSlow43, BinopInst("/", LoadVarInst(stack, fSlow41), LoadVarInst(stack, fSlow42)))
	DeclareVarInst(stack, "float", fSlow44, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow41)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow42))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow45, BinopInst("-", LoadVarInst(stack, fSlow43), LoadVarInst(stack, fSlow44)))
	DeclareVarInst(stack, "float", fSlow46, BinopInst("*", LoadVarInst(stack, fSlow39), BinopInst("+", LoadVarInst(stack, fSlow44), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow43)))))
	DeclareVarInst(stack, "float", fSlow47, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst21), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow39)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow48, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst26), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow49, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow48)))
	DeclareVarInst(stack, "float", fSlow50, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow49))))
	DeclareVarInst(stack, "float", fSlow51, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow49)))
	DeclareVarInst(stack, "float", fSlow52, BinopInst("/", LoadVarInst(stack, fSlow50), LoadVarInst(stack, fSlow51)))
	DeclareVarInst(stack, "float", fSlow53, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow50)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow51))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow54, BinopInst("-", LoadVarInst(stack, fSlow52), LoadVarInst(stack, fSlow53)))
	DeclareVarInst(stack, "float", fSlow55, BinopInst("*", LoadVarInst(stack, fSlow48), BinopInst("+", LoadVarInst(stack, fSlow53), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow52)))))
	DeclareVarInst(stack, "float", fSlow56, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst26), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow48)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow57, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst31), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow58, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow57)))
	DeclareVarInst(stack, "float", fSlow59, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow58))))
	DeclareVarInst(stack, "float", fSlow60, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow58)))
	DeclareVarInst(stack, "float", fSlow61, BinopInst("/", LoadVarInst(stack, fSlow59), LoadVarInst(stack, fSlow60)))
	DeclareVarInst(stack, "float", fSlow62, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow59)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow60))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow63, BinopInst("-", LoadVarInst(stack, fSlow61), LoadVarInst(stack, fSlow62)))
	DeclareVarInst(stack, "float", fSlow64, BinopInst("*", LoadVarInst(stack, fSlow57), BinopInst("+", LoadVarInst(stack, fSlow62), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow61)))))
	DeclareVarInst(stack, "float", fSlow65, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst31), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow57)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow66, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst36), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow67, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow66)))
	DeclareVarInst(stack, "float", fSlow68, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow67))))
	DeclareVarInst(stack, "float", fSlow69, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow67)))
	DeclareVarInst(stack, "float", fSlow70, BinopInst("/", LoadVarInst(stack, fSlow68), LoadVarInst(stack, fSlow69)))
	DeclareVarInst(stack, "float", fSlow71, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow68)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow69))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow72, BinopInst("-", LoadVarInst(stack, fSlow70), LoadVarInst(stack, fSlow71)))
	DeclareVarInst(stack, "float", fSlow73, BinopInst("*", LoadVarInst(stack, fSlow66), BinopInst("+", LoadVarInst(stack, fSlow71), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow70)))))
	DeclareVarInst(stack, "float", fSlow74, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst36), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow66)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow75, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst41), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow76, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow75)))
	DeclareVarInst(stack, "float", fSlow77, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow76))))
	DeclareVarInst(stack, "float", fSlow78, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow76)))
	DeclareVarInst(stack, "float", fSlow79, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow77)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow78))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow80, BinopInst("/", LoadVarInst(stack, fSlow77), LoadVarInst(stack, fSlow78)))
	DeclareVarInst(stack, "float", fSlow81, BinopInst("*", LoadVarInst(stack, fSlow75), BinopInst("+", LoadVarInst(stack, fSlow79), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow80)))))
	DeclareVarInst(stack, "float", fSlow82, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst41), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow75)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow83, BinopInst("-", LoadVarInst(stack, fSlow80), LoadVarInst(stack, fSlow79)))
	DeclareVarInst(stack, "float", fSlow84, CastInst("float", LoadVarInst(struct, fVslider7)))
	DeclareVarInst(stack, "float", fSlow85, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider8)))))
	DeclareVarInst(stack, "float", fSlow86, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("/", LoadVarInst(stack, fSlow84), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fSlow85))))))
	DeclareVarInst(stack, "float", fSlow87, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow86)), BinopInst("+", LoadVarInst(stack, fSlow86), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow88, BinopInst("*", BinopInst("-", Float(0.0f), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow84)))), BinopInst("+", LoadVarInst(stack, fSlow87), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow89, BinopInst("*", BinopInst("-", Float(0.0f), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow0)))), BinopInst("+", LoadVarInst(stack, fSlow3), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow90, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider9))))
	DeclareVarInst(stack, "float", fSlow91, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider10))))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 432
Store = 110
Binop = 332
Numbers = 158
Declare = 39
Cast = 4
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(struct, fRec8[Int32(2)])))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec12[Int32(0)]))))))
		StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec11[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], LoadVarInst(stack, fTemp0))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(0.300000012f), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow20)), Int32(16383))])))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("-", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec9[Int32(1)])), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(32767))])), LoadVarInst(stack, fTemp1)))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp2))
		StoreVarInst(struct, fRec9[Int32(0)], LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst9)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec10, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp2))))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fRec1[Int32(2)])))))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow27), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow28), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec16[Int32(0)]))))))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec15[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp3, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], LoadVarInst(stack, fTemp3))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", Float(0.300000012f), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow20)), Int32(16383))])))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst13)), Int32(16383))]), LoadVarInst(stack, fTemp4)), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec13[Int32(1)]))))
		StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp5))
		StoreVarInst(struct, fRec13[Int32(0)], LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst14)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec14, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fRec14)))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fRec5[Int32(2)])))))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow36), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow37), BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow38), LoadVarInst(struct, fRec20[Int32(0)]))))))
		StoreVarInst(struct, fVec6[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec19[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp4), LoadVarInst(struct, fVec6[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst18)), Int32(16383))])), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec17[Int32(1)]))))
		StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp7))
		StoreVarInst(struct, fRec17[Int32(0)], LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst19)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec18, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp7)))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fRec18)))
		StoreVarInst(struct, fRec24[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(struct, fRec3[Int32(2)])))))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow45), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow46), BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow47), LoadVarInst(struct, fRec24[Int32(0)]))))))
		StoreVarInst(struct, fVec8[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec23[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("-", LoadVarInst(struct, fVec8[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst23)), Int32(16383))]), BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec21[Int32(1)])))))
		StoreVarInst(struct, fVec9[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp9))
		StoreVarInst(struct, fRec21[Int32(0)], LoadVarInst(struct, fVec9[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst24)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec22, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp9)))
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec28[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fRec7[Int32(2)])))))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow54), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow55), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow56), LoadVarInst(struct, fRec28[Int32(0)]))))))
		StoreVarInst(struct, fVec10[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec27[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("-", LoadVarInst(struct, fVec10[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst28)), Int32(16383))]), BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec25[Int32(1)])))))
		StoreVarInst(struct, fVec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp10))
		StoreVarInst(struct, fRec25[Int32(0)], LoadVarInst(struct, fVec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst29)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec26, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp10)))
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec32[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fRec2[Int32(2)])))))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow63), LoadVarInst(struct, fRec31[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow64), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow65), LoadVarInst(struct, fRec32[Int32(0)]))))))
		StoreVarInst(struct, fVec12[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec31[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fVec12[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst33)), Int32(32767))]))))
		StoreVarInst(struct, fVec13[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp11))
		StoreVarInst(struct, fRec29[Int32(0)], LoadVarInst(struct, fVec13[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst34)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec30, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp11))))
		StoreVarInst(struct, fRec36[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec36[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fRec6[Int32(2)])))))
		StoreVarInst(struct, fRec35[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow72), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow73), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow74), LoadVarInst(struct, fRec36[Int32(0)]))))))
		StoreVarInst(struct, fVec14[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec35[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(struct, fVec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst38)), Int32(16383))]), BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec33[Int32(1)])))))
		StoreVarInst(struct, fVec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp12))
		StoreVarInst(struct, fRec33[Int32(0)], LoadVarInst(struct, fVec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst39)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec34, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp12))))
		StoreVarInst(struct, fRec40[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec40[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fRec4[Int32(2)])))))
		StoreVarInst(struct, fRec39[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow81), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow82), LoadVarInst(struct, fRec40[Int32(0)])), LoadVarInst(struct, fRec4[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow83), LoadVarInst(struct, fRec39[Int32(1)]))))
		StoreVarInst(struct, fVec16[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec39[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec16[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst43)), Int32(32767))]), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec37[Int32(1)]))), LoadVarInst(stack, fTemp1)))
		StoreVarInst(struct, fVec17[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp13))
		StoreVarInst(struct, fRec37[Int32(0)], LoadVarInst(struct, fVec17[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst44)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec38, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp13))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec38)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)])))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fRec14), LoadVarInst(stack, fRec18)))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec25[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec21[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec17[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec13[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec26), BinopInst("+", LoadVarInst(stack, fRec22), LoadVarInst(stack, fTemp14))))))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec38)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)]))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec30), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fRec34)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec38)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)]))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fRec38)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec30), BinopInst("+", LoadVarInst(stack, fRec22), LoadVarInst(stack, fRec26))), LoadVarInst(stack, fRec34)), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fRec18)))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec14), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec38)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp15), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)]))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec18), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec38)), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)]))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec18), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec38)), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)]))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec14), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec38)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp15), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("*", Float(0.370000005f), BinopInst("+", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec3[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("*", LoadVarInst(stack, fSlow88), LoadVarInst(struct, fRec41[Int32(1)])))
		StoreVarInst(struct, fRec41[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp16), BinopInst("+", LoadVarInst(stack, fTemp17), BinopInst("*", LoadVarInst(stack, fSlow87), LoadVarInst(struct, fRec41[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow87), LoadVarInst(struct, fRec41[Int32(0)])), BinopInst("+", LoadVarInst(stack, fTemp17), LoadVarInst(struct, fRec41[Int32(2)]))))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fTemp18)), BinopInst("*", LoadVarInst(stack, fSlow85), BinopInst("-", LoadVarInst(stack, fTemp18), LoadVarInst(stack, fTemp16))))))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("*", LoadVarInst(stack, fSlow89), LoadVarInst(struct, fRec0[Int32(1)])))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp19), BinopInst("+", LoadVarInst(stack, fTemp20), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec0[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec0[Int32(0)])))
		StoreVarInst(struct, fRec42[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow90), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec42[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("+", LoadVarInst(struct, fRec42[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp22))))
		StoreVarInst(struct, fRec43[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow91), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec43[Int32(1)]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp21), BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp20)))), BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp21), BinopInst("+", LoadVarInst(stack, fTemp20), LoadVarInst(struct, fRec0[Int32(2)]))), LoadVarInst(stack, fTemp19)))), LoadVarInst(stack, fTemp23)), BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp22))), LoadVarInst(struct, fRec43[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("*", Float(0.370000005f), BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec3[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(stack, fSlow88), LoadVarInst(struct, fRec45[Int32(1)])))
		StoreVarInst(struct, fRec45[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp24), BinopInst("+", LoadVarInst(stack, fTemp25), BinopInst("*", LoadVarInst(stack, fSlow87), LoadVarInst(struct, fRec45[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow87), LoadVarInst(struct, fRec45[Int32(0)])), BinopInst("+", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fRec45[Int32(2)]))))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp26)), BinopInst("*", LoadVarInst(stack, fSlow85), BinopInst("-", LoadVarInst(stack, fTemp26), LoadVarInst(stack, fTemp24))))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(stack, fSlow89), LoadVarInst(struct, fRec44[Int32(1)])))
		StoreVarInst(struct, fRec44[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp27), BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec44[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec44[Int32(0)])))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp0), LoadVarInst(stack, fTemp22)), BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp29), BinopInst("+", LoadVarInst(struct, fRec44[Int32(2)]), BinopInst("+", LoadVarInst(stack, fTemp27), LoadVarInst(stack, fTemp28)))), BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp29), BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec44[Int32(2)]))), LoadVarInst(stack, fTemp27)))), LoadVarInst(stack, fTemp23))), LoadVarInst(struct, fRec43[Int32(0)])))))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
		StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
		StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
		StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
		StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
		StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
		StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec41[Int32(2)], LoadVarInst(struct, fRec41[Int32(1)]))
		StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
		StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
		StoreVarInst(struct, fRec45[Int32(2)], LoadVarInst(struct, fRec45[Int32(1)]))
		StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
		StoreVarInst(struct, fRec44[Int32(2)], LoadVarInst(struct, fRec44[Int32(1)]))
		StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[32768])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fVec1[16384])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fVec2[2048])
	DeclareVarInst(struct, "int", iConst9)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fVec3[16384])
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "int", iConst13)
	DeclareVarInst(struct, float, fVec4[16384])
	DeclareVarInst(struct, float, fVec5[2048])
	DeclareVarInst(struct, "int", iConst14)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fVec6[16384])
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, "int", iConst18)
	DeclareVarInst(struct, float, fVec7[4096])
	DeclareVarInst(struct, "int", iConst19)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fVec8[16384])
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "int", iConst23)
	DeclareVarInst(struct, float, fVec9[4096])
	DeclareVarInst(struct, "int", iConst24)
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fVec10[16384])
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "int", iConst28)
	DeclareVarInst(struct, float, fVec11[2048])
	DeclareVarInst(struct, "int", iConst29)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fVec12[32768])
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, "int", iConst33)
	DeclareVarInst(struct, float, fVec13[4096])
	DeclareVarInst(struct, "int", iConst34)
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, float, fRec35[2])
	DeclareVarInst(struct, float, fVec14[16384])
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "int", iConst38)
	DeclareVarInst(struct, float, fVec15[4096])
	DeclareVarInst(struct, "int", iConst39)
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, float, fRec40[2])
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, float, fVec16[32768])
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, "int", iConst43)
	DeclareVarInst(struct, float, fVec17[4096])
	DeclareVarInst(struct, "int", iConst44)
	DeclareVarInst(struct, float, fRec37[2])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec41[3])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, float, fRec42[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider10)
	DeclareVarInst(struct, float, fRec43[2])
	DeclareVarInst(struct, float, fRec45[3])
	DeclareVarInst(struct, float, fRec44[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219990999f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst3, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst2))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0191229992f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst7, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst2), LoadVarInst(struct, fConst6))))))
	StoreVarInst(struct, fConst8, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, iConst9, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst6), Float(-1.0f))))))
	StoreVarInst(struct, fConst10, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153128996f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst11, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst10))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst12, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0203460008f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst13, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst10), LoadVarInst(struct, fConst12))))))
	StoreVarInst(struct, iConst14, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst12), Float(-1.0f))))))
	StoreVarInst(struct, fConst15, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713001f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst16, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst15))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst17, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0229039993f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst18, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst15), LoadVarInst(struct, fConst17))))))
	StoreVarInst(struct, iConst19, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst17), Float(-1.0f))))))
	StoreVarInst(struct, fConst20, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst21, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst20))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst22, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0316039994f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst23, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst20), LoadVarInst(struct, fConst22))))))
	StoreVarInst(struct, iConst24, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.0f))))))
	StoreVarInst(struct, fConst25, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst26, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst25))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst27, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0134579996f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst28, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst25), LoadVarInst(struct, fConst27))))))
	StoreVarInst(struct, iConst29, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst27), Float(-1.0f))))))
	StoreVarInst(struct, fConst30, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389003f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst31, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst30))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst32, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0244210009f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst33, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst30), LoadVarInst(struct, fConst32))))))
	StoreVarInst(struct, iConst34, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst32), Float(-1.0f))))))
	StoreVarInst(struct, fConst35, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst36, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst35))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst37, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0292910002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst38, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst35), LoadVarInst(struct, fConst37))))))
	StoreVarInst(struct, iConst39, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst37), Float(-1.0f))))))
	StoreVarInst(struct, fConst40, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891012f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst41, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst40))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst42, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0273330007f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst43, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst40), LoadVarInst(struct, fConst42))))))
	StoreVarInst(struct, iConst44, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst42), Float(-1.0f))))))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(1500.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(6000.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(3.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(200.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(60.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(315.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider10, CastInst("FAUSTFLOAT", Double(-20.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(32768))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(16384))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2048))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(16384))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(16384))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(16384))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(4096))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(16384))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(4096))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(16384))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2048))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(32768))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(4096))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(16384))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(4096))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(32768))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec16[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(4096))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec17[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(3))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(3))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(3))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(3))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(3))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(3))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(3))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(3))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(3))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fVslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider1)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("/", LoadVarInst(stack, fSlow0), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fSlow1))))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)), BinopInst("+", LoadVarInst(stack, fSlow2), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fVslider2)))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst3), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst4), CastInst("float", LoadVarInst(struct, fVslider3)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fSlow7))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("/", LoadVarInst(stack, fSlow8), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow11, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow8)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow9))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fSlow11)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", LoadVarInst(stack, fSlow11), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow10)))))
	DeclareVarInst(stack, "float", fSlow14, CastInst("float", LoadVarInst(struct, fVslider4)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst3), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow5)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst5), CastInst("float", LoadVarInst(struct, fVslider5))))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("+", LoadVarInst(stack, fSlow16), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow16)), LoadVarInst(stack, fSlow17))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "int", iSlow20, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("*", LoadVarInst(struct, fConst8), CastInst("float", LoadVarInst(struct, fVslider6)))))))
	DeclareVarInst(stack, "float", fSlow21, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst11), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow22, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow22))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow22)))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("/", LoadVarInst(stack, fSlow23), LoadVarInst(stack, fSlow24)))
	DeclareVarInst(stack, "float", fSlow26, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow23)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow24))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("-", LoadVarInst(stack, fSlow25), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("*", LoadVarInst(stack, fSlow21), BinopInst("+", LoadVarInst(stack, fSlow26), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow25)))))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst11), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow21)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow30, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst16), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow31, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow30)))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow31))))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow31)))
	DeclareVarInst(stack, "float", fSlow34, BinopInst("/", LoadVarInst(stack, fSlow32), LoadVarInst(stack, fSlow33)))
	DeclareVarInst(stack, "float", fSlow35, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow32)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow33))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow36, BinopInst("-", LoadVarInst(stack, fSlow34), LoadVarInst(stack, fSlow35)))
	DeclareVarInst(stack, "float", fSlow37, BinopInst("*", LoadVarInst(stack, fSlow30), BinopInst("+", LoadVarInst(stack, fSlow35), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow34)))))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst16), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow30)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow39, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst21), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow40, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow39)))
	DeclareVarInst(stack, "float", fSlow41, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow40))))
	DeclareVarInst(stack, "float", fSlow42, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow40)))
	DeclareVarInst(stack, "float", fSlow43, BinopInst("/", LoadVarInst(stack, fSlow41), LoadVarInst(stack, fSlow42)))
	DeclareVarInst(stack, "float", fSlow44, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow41)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow42))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow45, BinopInst("-", LoadVarInst(stack, fSlow43), LoadVarInst(stack, fSlow44)))
	DeclareVarInst(stack, "float", fSlow46, BinopInst("*", LoadVarInst(stack, fSlow39), BinopInst("+", LoadVarInst(stack, fSlow44), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow43)))))
	DeclareVarInst(stack, "float", fSlow47, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst21), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow39)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow48, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst26), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow49, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow48)))
	DeclareVarInst(stack, "float", fSlow50, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow49))))
	DeclareVarInst(stack, "float", fSlow51, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow49)))
	DeclareVarInst(stack, "float", fSlow52, BinopInst("/", LoadVarInst(stack, fSlow50), LoadVarInst(stack, fSlow51)))
	DeclareVarInst(stack, "float", fSlow53, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow50)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow51))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow54, BinopInst("-", LoadVarInst(stack, fSlow52), LoadVarInst(stack, fSlow53)))
	DeclareVarInst(stack, "float", fSlow55, BinopInst("*", LoadVarInst(stack, fSlow48), BinopInst("+", LoadVarInst(stack, fSlow53), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow52)))))
	DeclareVarInst(stack, "float", fSlow56, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst26), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow48)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow57, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst31), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow58, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow57)))
	DeclareVarInst(stack, "float", fSlow59, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow58))))
	DeclareVarInst(stack, "float", fSlow60, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow58)))
	DeclareVarInst(stack, "float", fSlow61, BinopInst("/", LoadVarInst(stack, fSlow59), LoadVarInst(stack, fSlow60)))
	DeclareVarInst(stack, "float", fSlow62, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow59)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow60))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow63, BinopInst("-", LoadVarInst(stack, fSlow61), LoadVarInst(stack, fSlow62)))
	DeclareVarInst(stack, "float", fSlow64, BinopInst("*", LoadVarInst(stack, fSlow57), BinopInst("+", LoadVarInst(stack, fSlow62), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow61)))))
	DeclareVarInst(stack, "float", fSlow65, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst31), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow57)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow66, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst36), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow67, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow66)))
	DeclareVarInst(stack, "float", fSlow68, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow67))))
	DeclareVarInst(stack, "float", fSlow69, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow67)))
	DeclareVarInst(stack, "float", fSlow70, BinopInst("/", LoadVarInst(stack, fSlow68), LoadVarInst(stack, fSlow69)))
	DeclareVarInst(stack, "float", fSlow71, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow68)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow69))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow72, BinopInst("-", LoadVarInst(stack, fSlow70), LoadVarInst(stack, fSlow71)))
	DeclareVarInst(stack, "float", fSlow73, BinopInst("*", LoadVarInst(stack, fSlow66), BinopInst("+", LoadVarInst(stack, fSlow71), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow70)))))
	DeclareVarInst(stack, "float", fSlow74, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst36), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow66)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow75, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst41), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow76, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow75)))
	DeclareVarInst(stack, "float", fSlow77, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fSlow76))))
	DeclareVarInst(stack, "float", fSlow78, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow76)))
	DeclareVarInst(stack, "float", fSlow79, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow77)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow78))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow80, BinopInst("/", LoadVarInst(stack, fSlow77), LoadVarInst(stack, fSlow78)))
	DeclareVarInst(stack, "float", fSlow81, BinopInst("*", LoadVarInst(stack, fSlow75), BinopInst("+", LoadVarInst(stack, fSlow79), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow80)))))
	DeclareVarInst(stack, "float", fSlow82, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst41), LoadVarInst(stack, fSlow14))), LoadVarInst(stack, fSlow75)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow83, BinopInst("-", LoadVarInst(stack, fSlow80), LoadVarInst(stack, fSlow79)))
	DeclareVarInst(stack, "float", fSlow84, CastInst("float", LoadVarInst(struct, fVslider7)))
	DeclareVarInst(stack, "float", fSlow85, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider8)))))
	DeclareVarInst(stack, "float", fSlow86, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("/", LoadVarInst(stack, fSlow84), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fSlow85))))))
	DeclareVarInst(stack, "float", fSlow87, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow86)), BinopInst("+", LoadVarInst(stack, fSlow86), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow88, BinopInst("*", BinopInst("-", Float(0.0f), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow84)))), BinopInst("+", LoadVarInst(stack, fSlow87), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow89, BinopInst("*", BinopInst("-", Float(0.0f), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(stack, fSlow0)))), BinopInst("+", LoadVarInst(stack, fSlow3), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow90, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider9))))
	DeclareVarInst(stack, "float", fSlow91, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider10))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(struct, fRec8[Int32(2)])))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec12[Int32(0)]))))))
			StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec11[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], LoadVarInst(stack, fTemp0))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(0.300000012f), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow20)), Int32(16383))])))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("-", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec9[Int32(1)])), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(32767))])), LoadVarInst(stack, fTemp1)))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp2))
			StoreVarInst(struct, fRec9[Int32(0)], LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst9)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec10, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp2))))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fRec1[Int32(2)])))))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow27), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow28), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec16[Int32(0)]))))))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec15[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp3, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], LoadVarInst(stack, fTemp3))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", Float(0.300000012f), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow20)), Int32(16383))])))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst13)), Int32(16383))]), LoadVarInst(stack, fTemp4)), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec13[Int32(1)]))))
			StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp5))
			StoreVarInst(struct, fRec13[Int32(0)], LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst14)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec14, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fRec14)))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fRec5[Int32(2)])))))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow36), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow37), BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow38), LoadVarInst(struct, fRec20[Int32(0)]))))))
			StoreVarInst(struct, fVec6[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec19[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp4), LoadVarInst(struct, fVec6[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst18)), Int32(16383))])), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec17[Int32(1)]))))
			StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp7))
			StoreVarInst(struct, fRec17[Int32(0)], LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst19)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec18, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp7)))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fRec18)))
			StoreVarInst(struct, fRec24[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(struct, fRec3[Int32(2)])))))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow45), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow46), BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow47), LoadVarInst(struct, fRec24[Int32(0)]))))))
			StoreVarInst(struct, fVec8[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec23[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("-", LoadVarInst(struct, fVec8[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst23)), Int32(16383))]), BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec21[Int32(1)])))))
			StoreVarInst(struct, fVec9[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp9))
			StoreVarInst(struct, fRec21[Int32(0)], LoadVarInst(struct, fVec9[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst24)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec22, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp9)))
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec28[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fRec7[Int32(2)])))))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow54), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow55), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow56), LoadVarInst(struct, fRec28[Int32(0)]))))))
			StoreVarInst(struct, fVec10[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec27[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("-", LoadVarInst(struct, fVec10[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst28)), Int32(16383))]), BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec25[Int32(1)])))))
			StoreVarInst(struct, fVec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp10))
			StoreVarInst(struct, fRec25[Int32(0)], LoadVarInst(struct, fVec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst29)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec26, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp10)))
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec32[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fRec2[Int32(2)])))))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow63), LoadVarInst(struct, fRec31[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow64), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow65), LoadVarInst(struct, fRec32[Int32(0)]))))))
			StoreVarInst(struct, fVec12[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec31[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fVec12[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst33)), Int32(32767))]))))
			StoreVarInst(struct, fVec13[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp11))
			StoreVarInst(struct, fRec29[Int32(0)], LoadVarInst(struct, fVec13[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst34)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec30, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp11))))
			StoreVarInst(struct, fRec36[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec36[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fRec6[Int32(2)])))))
			StoreVarInst(struct, fRec35[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow72), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow73), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow74), LoadVarInst(struct, fRec36[Int32(0)]))))))
			StoreVarInst(struct, fVec14[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec35[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(struct, fVec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst38)), Int32(16383))]), BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec33[Int32(1)])))))
			StoreVarInst(struct, fVec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp12))
			StoreVarInst(struct, fRec33[Int32(0)], LoadVarInst(struct, fVec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst39)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec34, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp12))))
			StoreVarInst(struct, fRec40[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec40[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fRec4[Int32(2)])))))
			StoreVarInst(struct, fRec39[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow81), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow82), LoadVarInst(struct, fRec40[Int32(0)])), LoadVarInst(struct, fRec4[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow83), LoadVarInst(struct, fRec39[Int32(1)]))))
			StoreVarInst(struct, fVec16[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec39[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec16[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst43)), Int32(32767))]), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec37[Int32(1)]))), LoadVarInst(stack, fTemp1)))
			StoreVarInst(struct, fVec17[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp13))
			StoreVarInst(struct, fRec37[Int32(0)], LoadVarInst(struct, fVec17[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst44)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec38, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp13))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec38)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)])))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fRec14), LoadVarInst(stack, fRec18)))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec25[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec21[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec17[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec13[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec26), BinopInst("+", LoadVarInst(stack, fRec22), LoadVarInst(stack, fTemp14))))))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec38)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)]))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec30), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fRec34)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec38)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)]))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fRec38)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec30), BinopInst("+", LoadVarInst(stack, fRec22), LoadVarInst(stack, fRec26))), LoadVarInst(stack, fRec34)), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fRec18)))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec14), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec38)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp15), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)]))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec18), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec38)), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)]))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec18), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec38)), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)]))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec14), LoadVarInst(stack, fRec26)), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec38)), LoadVarInst(struct, fRec13[Int32(1)])), LoadVarInst(struct, fRec25[Int32(1)])), LoadVarInst(struct, fRec33[Int32(1)])), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp15), LoadVarInst(stack, fRec22)), LoadVarInst(stack, fRec30)), LoadVarInst(stack, fRec10)), LoadVarInst(struct, fRec17[Int32(1)])), LoadVarInst(struct, fRec21[Int32(1)])), LoadVarInst(struct, fRec29[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("*", Float(0.370000005f), BinopInst("+", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec3[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("*", LoadVarInst(stack, fSlow88), LoadVarInst(struct, fRec41[Int32(1)])))
			StoreVarInst(struct, fRec41[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp16), BinopInst("+", LoadVarInst(stack, fTemp17), BinopInst("*", LoadVarInst(stack, fSlow87), LoadVarInst(struct, fRec41[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow87), LoadVarInst(struct, fRec41[Int32(0)])), BinopInst("+", LoadVarInst(stack, fTemp17), LoadVarInst(struct, fRec41[Int32(2)]))))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fTemp18)), BinopInst("*", LoadVarInst(stack, fSlow85), BinopInst("-", LoadVarInst(stack, fTemp18), LoadVarInst(stack, fTemp16))))))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("*", LoadVarInst(stack, fSlow89), LoadVarInst(struct, fRec0[Int32(1)])))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp19), BinopInst("+", LoadVarInst(stack, fTemp20), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec0[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec0[Int32(0)])))
			StoreVarInst(struct, fRec42[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow90), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec42[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("+", LoadVarInst(struct, fRec42[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp22))))
			StoreVarInst(struct, fRec43[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow91), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec43[Int32(1)]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp21), BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp20)))), BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp21), BinopInst("+", LoadVarInst(stack, fTemp20), LoadVarInst(struct, fRec0[Int32(2)]))), LoadVarInst(stack, fTemp19)))), LoadVarInst(stack, fTemp23)), BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp22))), LoadVarInst(struct, fRec43[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("*", Float(0.370000005f), BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec3[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(stack, fSlow88), LoadVarInst(struct, fRec45[Int32(1)])))
			StoreVarInst(struct, fRec45[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp24), BinopInst("+", LoadVarInst(stack, fTemp25), BinopInst("*", LoadVarInst(stack, fSlow87), LoadVarInst(struct, fRec45[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow87), LoadVarInst(struct, fRec45[Int32(0)])), BinopInst("+", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fRec45[Int32(2)]))))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp26)), BinopInst("*", LoadVarInst(stack, fSlow85), BinopInst("-", LoadVarInst(stack, fTemp26), LoadVarInst(stack, fTemp24))))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(stack, fSlow89), LoadVarInst(struct, fRec44[Int32(1)])))
			StoreVarInst(struct, fRec44[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp27), BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec44[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec44[Int32(0)])))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp0), LoadVarInst(stack, fTemp22)), BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp29), BinopInst("+", LoadVarInst(struct, fRec44[Int32(2)]), BinopInst("+", LoadVarInst(stack, fTemp27), LoadVarInst(stack, fTemp28)))), BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp29), BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec44[Int32(2)]))), LoadVarInst(stack, fTemp27)))), LoadVarInst(stack, fTemp23))), LoadVarInst(struct, fRec43[Int32(0)])))))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
			StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
			StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
			StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
			StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
			StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec41[Int32(2)], LoadVarInst(struct, fRec41[Int32(1)]))
			StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
			StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
			StoreVarInst(struct, fRec45[Int32(2)], LoadVarInst(struct, fRec45[Int32(1)]))
			StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
			StoreVarInst(struct, fRec44[Int32(2)], LoadVarInst(struct, fRec44[Int32(1)]))
			StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 72 bytes
Heap size int* = 0 bytes
Heap size real = 958976 bytes
Heap size = 959048 bytes
Stack size in compute = 400 bytes

