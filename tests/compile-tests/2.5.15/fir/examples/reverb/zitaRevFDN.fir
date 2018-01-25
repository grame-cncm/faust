======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "tooltip", "~ Zita_Rev's internal   8x8 Feedback Delay Network (FDN) & Schroeder allpass-comb reverberator.  See   Faust's reverbs.lib for documentation and references")
	OpenHorizontalBox("Zita_Rev Internal FDN Reverb")
	AddMetaDeclareInst(fVslider2, "1", "")
	AddMetaDeclareInst(fVslider2, "style", "knob")
	AddMetaDeclareInst(fVslider2, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band")
	AddMetaDeclareInst(fVslider2, "unit", "s")
	AddVerticalSlider("Low RT60", fVslider2, 3.0f, 1.0f, 8.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider3, "2", "")
	AddMetaDeclareInst(fVslider3, "scale", "log")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies")
	AddMetaDeclareInst(fVslider3, "unit", "Hz")
	AddVerticalSlider("LF X", fVslider3, 200.0f, 50.0f, 1000.0f, 1.0f)
	AddMetaDeclareInst(fVslider0, "3", "")
	AddMetaDeclareInst(fVslider0, "scale", "log")
	AddMetaDeclareInst(fVslider0, "style", "knob")
	AddMetaDeclareInst(fVslider0, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band")
	AddMetaDeclareInst(fVslider0, "unit", "s")
	AddVerticalSlider("Mid RT60", fVslider0, 2.0f, 1.0f, 8.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider1, "4", "")
	AddMetaDeclareInst(fVslider1, "scale", "log")
	AddMetaDeclareInst(fVslider1, "style", "knob")
	AddMetaDeclareInst(fVslider1, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60")
	AddMetaDeclareInst(fVslider1, "unit", "Hz")
	AddVerticalSlider("HF Damping", fVslider1, 6000.0f, 1500.0f, 23520.0f, 1.0f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[32768])
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, float, fVec1[2048])
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fVec2[32768])
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "int", iConst11)
	DeclareVarInst(struct, float, fVec3[4096])
	DeclareVarInst(struct, "int", iConst12)
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fVec4[16384])
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "int", iConst16)
	DeclareVarInst(struct, float, fVec5[4096])
	DeclareVarInst(struct, "int", iConst17)
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fVec6[32768])
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, "int", iConst21)
	DeclareVarInst(struct, float, fVec7[4096])
	DeclareVarInst(struct, "int", iConst22)
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fVec8[16384])
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "int", iConst26)
	DeclareVarInst(struct, float, fVec9[2048])
	DeclareVarInst(struct, "int", iConst27)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fVec10[16384])
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "int", iConst31)
	DeclareVarInst(struct, float, fVec11[4096])
	DeclareVarInst(struct, "int", iConst32)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, float, fRec35[2])
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, float, fVec12[16384])
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "int", iConst36)
	DeclareVarInst(struct, float, fVec13[4096])
	DeclareVarInst(struct, "int", iConst37)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, float, fVec14[16384])
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "int", iConst41)
	DeclareVarInst(struct, float, fVec15[2048])
	DeclareVarInst(struct, "int", iConst42)
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, float, fRec7[3])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(8))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(8))
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
	StoreVarInst(struct, fConst1, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219990999f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst2, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst1))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0191229992f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst6, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst1), LoadVarInst(struct, fConst5))))))
	StoreVarInst(struct, iConst7, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst5), Float(-1.0f))))))
	StoreVarInst(struct, fConst8, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891012f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst9, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst8))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst10, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0273330007f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst11, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst8), LoadVarInst(struct, fConst10))))))
	StoreVarInst(struct, iConst12, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst10), Float(-1.0f))))))
	StoreVarInst(struct, fConst13, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst14, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst13))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst15, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0292910002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst16, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst13), LoadVarInst(struct, fConst15))))))
	StoreVarInst(struct, iConst17, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst15), Float(-1.0f))))))
	StoreVarInst(struct, fConst18, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389003f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst19, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst18))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst20, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0244210009f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst21, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst18), LoadVarInst(struct, fConst20))))))
	StoreVarInst(struct, iConst22, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst20), Float(-1.0f))))))
	StoreVarInst(struct, fConst23, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst24, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst23))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst25, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0134579996f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst26, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst23), LoadVarInst(struct, fConst25))))))
	StoreVarInst(struct, iConst27, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst25), Float(-1.0f))))))
	StoreVarInst(struct, fConst28, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst29, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst28))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst30, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0316039994f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst31, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst28), LoadVarInst(struct, fConst30))))))
	StoreVarInst(struct, iConst32, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst30), Float(-1.0f))))))
	StoreVarInst(struct, fConst33, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713001f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst34, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst33))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst35, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0229039993f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst36, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst33), LoadVarInst(struct, fConst35))))))
	StoreVarInst(struct, iConst37, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst35), Float(-1.0f))))))
	StoreVarInst(struct, fConst38, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153128996f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst39, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst38))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst40, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0203460008f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst41, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst38), LoadVarInst(struct, fConst40))))))
	StoreVarInst(struct, iConst42, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst40), Float(-1.0f))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(6000.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(3.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(200.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l1)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l3), Int32(2048))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(32768))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(4096))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(16384))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(4096))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(32768))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(4096))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(16384))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2048))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(16384))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(4096))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(16384))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(4096))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(16384))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2048))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(3))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(3))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(3))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(3))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 170
Store = 0
Binop = 120
Numbers = 53
Declare = 95
Cast = 4
Select = 0
Loop = 0
Funcall = 58

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input6, LoadVarInst(kFunArgs, inputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input7, LoadVarInst(kFunArgs, inputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fVslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst3), CastInst("float", LoadVarInst(struct, fVslider1)))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("/", LoadVarInst(stack, fSlow4), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow4)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow5))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("-", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow6)))))
	DeclareVarInst(stack, "float", fSlow10, CastInst("float", LoadVarInst(struct, fVslider2)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow1)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), CastInst("float", LoadVarInst(struct, fVslider3))))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("+", LoadVarInst(stack, fSlow12), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow12)), LoadVarInst(stack, fSlow13))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow16, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst9), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow17, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow17))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("/", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fSlow19)))
	DeclareVarInst(stack, "float", fSlow21, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow18)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow19))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("-", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow21), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow20))), LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst9), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow16)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow25, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst14), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow26, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow25)))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow26))))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("/", LoadVarInst(stack, fSlow27), LoadVarInst(stack, fSlow28)))
	DeclareVarInst(stack, "float", fSlow30, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow27)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow28))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow31, BinopInst("-", LoadVarInst(stack, fSlow29), LoadVarInst(stack, fSlow30)))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow30), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow29))), LoadVarInst(stack, fSlow25)))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst14), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow25)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow34, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst19), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow35, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow34)))
	DeclareVarInst(stack, "float", fSlow36, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow35))))
	DeclareVarInst(stack, "float", fSlow37, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow35)))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("/", LoadVarInst(stack, fSlow36), LoadVarInst(stack, fSlow37)))
	DeclareVarInst(stack, "float", fSlow39, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow36)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow37))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow40, BinopInst("-", LoadVarInst(stack, fSlow38), LoadVarInst(stack, fSlow39)))
	DeclareVarInst(stack, "float", fSlow41, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow39), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow38))), LoadVarInst(stack, fSlow34)))
	DeclareVarInst(stack, "float", fSlow42, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst19), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow34)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow43, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst24), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow44, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow43)))
	DeclareVarInst(stack, "float", fSlow45, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow44))))
	DeclareVarInst(stack, "float", fSlow46, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow44)))
	DeclareVarInst(stack, "float", fSlow47, BinopInst("/", LoadVarInst(stack, fSlow45), LoadVarInst(stack, fSlow46)))
	DeclareVarInst(stack, "float", fSlow48, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow45)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow46))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow49, BinopInst("-", LoadVarInst(stack, fSlow47), LoadVarInst(stack, fSlow48)))
	DeclareVarInst(stack, "float", fSlow50, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow48), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow47))), LoadVarInst(stack, fSlow43)))
	DeclareVarInst(stack, "float", fSlow51, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst24), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow43)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow52, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst29), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow53, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow52)))
	DeclareVarInst(stack, "float", fSlow54, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow53))))
	DeclareVarInst(stack, "float", fSlow55, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow53)))
	DeclareVarInst(stack, "float", fSlow56, BinopInst("/", LoadVarInst(stack, fSlow54), LoadVarInst(stack, fSlow55)))
	DeclareVarInst(stack, "float", fSlow57, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow54)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow55))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow58, BinopInst("-", LoadVarInst(stack, fSlow56), LoadVarInst(stack, fSlow57)))
	DeclareVarInst(stack, "float", fSlow59, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow57), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow56))), LoadVarInst(stack, fSlow52)))
	DeclareVarInst(stack, "float", fSlow60, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst29), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow52)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow61, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst34), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow62, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow61)))
	DeclareVarInst(stack, "float", fSlow63, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow62))))
	DeclareVarInst(stack, "float", fSlow64, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow62)))
	DeclareVarInst(stack, "float", fSlow65, BinopInst("/", LoadVarInst(stack, fSlow63), LoadVarInst(stack, fSlow64)))
	DeclareVarInst(stack, "float", fSlow66, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow63)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow64))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow67, BinopInst("-", LoadVarInst(stack, fSlow65), LoadVarInst(stack, fSlow66)))
	DeclareVarInst(stack, "float", fSlow68, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow66), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow65))), LoadVarInst(stack, fSlow61)))
	DeclareVarInst(stack, "float", fSlow69, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst34), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow61)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow70, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst39), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow71, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow70)))
	DeclareVarInst(stack, "float", fSlow72, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow71))))
	DeclareVarInst(stack, "float", fSlow73, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow71)))
	DeclareVarInst(stack, "float", fSlow74, BinopInst("/", LoadVarInst(stack, fSlow72), LoadVarInst(stack, fSlow73)))
	DeclareVarInst(stack, "float", fSlow75, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow72)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow73))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow76, BinopInst("-", LoadVarInst(stack, fSlow74), LoadVarInst(stack, fSlow75)))
	DeclareVarInst(stack, "float", fSlow77, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow75), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow74))), LoadVarInst(stack, fSlow70)))
	DeclareVarInst(stack, "float", fSlow78, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst39), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow70)), Float(-1.0f)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 345
Store = 98
Binop = 253
Numbers = 127
Declare = 24
Cast = 16
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fRec7[Int32(2)])))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow9), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec11[Int32(0)]))))))
		StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec10[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("+", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec8[Int32(1)])), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst6)), Int32(32767))])), CastInst("float", LoadVarInst(stack, input7[LoadVarInst(loop, i)]))))
		StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp0))
		StoreVarInst(struct, fRec8[Int32(0)], LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec9, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(struct, fRec3[Int32(2)])))))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec15[Int32(0)]))))))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec14[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec12[Int32(1)])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst11)), Int32(32767))])), CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)]))))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp1))
		StoreVarInst(struct, fRec12[Int32(0)], LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst12)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec13, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp1))))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fRec5[Int32(2)])))))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow31), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow32), BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow33), LoadVarInst(struct, fRec19[Int32(0)]))))))
		StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec18[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec16[Int32(1)])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst16)), Int32(16383))])), CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)]))))
		StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp2))
		StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst17)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec17, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp2))))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fRec1[Int32(2)])))))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow41), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow42), LoadVarInst(struct, fRec23[Int32(0)]))))))
		StoreVarInst(struct, fVec6[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec22[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec20[Int32(1)])), LoadVarInst(struct, fVec6[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst21)), Int32(32767))])), CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)]))))
		StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp3))
		StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst22)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp3))))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fRec6[Int32(2)])))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow49), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow50), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow51), LoadVarInst(struct, fRec27[Int32(0)]))))))
		StoreVarInst(struct, fVec8[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec26[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec8[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst26)), Int32(16383))]), CastInst("float", LoadVarInst(stack, input6[LoadVarInst(loop, i)]))), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec24[Int32(1)]))))
		StoreVarInst(struct, fVec9[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp4))
		StoreVarInst(struct, fRec24[Int32(0)], LoadVarInst(struct, fVec9[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst27)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec25, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp4)))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec31[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fRec2[Int32(2)])))))
		StoreVarInst(struct, fRec30[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow58), LoadVarInst(struct, fRec30[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow59), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow60), LoadVarInst(struct, fRec31[Int32(0)]))))))
		StoreVarInst(struct, fVec10[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec30[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec10[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst31)), Int32(16383))]), CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)]))), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec28[Int32(1)]))))
		StoreVarInst(struct, fVec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp5))
		StoreVarInst(struct, fRec28[Int32(0)], LoadVarInst(struct, fVec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst32)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec29, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp5)))
		StoreVarInst(struct, fRec35[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fRec4[Int32(2)])))))
		StoreVarInst(struct, fRec34[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow67), LoadVarInst(struct, fRec34[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow68), BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow69), LoadVarInst(struct, fRec35[Int32(0)]))))))
		StoreVarInst(struct, fVec12[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec34[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec12[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst36)), Int32(16383))]), CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)]))), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec32[Int32(1)]))))
		StoreVarInst(struct, fVec13[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp6))
		StoreVarInst(struct, fRec32[Int32(0)], LoadVarInst(struct, fVec13[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst37)), Int32(4095))]))
		DeclareVarInst(stack, "float", fRec33, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp6)))
		StoreVarInst(struct, fRec39[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec39[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(struct, fRec0[Int32(2)])))))
		StoreVarInst(struct, fRec38[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow76), LoadVarInst(struct, fRec38[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow77), BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow78), LoadVarInst(struct, fRec39[Int32(0)]))))))
		StoreVarInst(struct, fVec14[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec38[Int32(0)])), Float(9.99999968e-21f)))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst41)), Int32(16383))]), CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)]))), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec36[Int32(1)]))))
		StoreVarInst(struct, fVec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp7))
		StoreVarInst(struct, fRec36[Int32(0)], LoadVarInst(struct, fVec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst42)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec37, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp7)))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fRec37), LoadVarInst(stack, fRec33)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fRec25), BinopInst("+", LoadVarInst(stack, fRec29), LoadVarInst(stack, fTemp8))))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec17), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp9))))))))))))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), LoadVarInst(stack, fTemp9))))), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fRec17))))))))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(stack, fRec29), LoadVarInst(stack, fRec25)))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec17), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp8))))))), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec13), LoadVarInst(stack, fTemp10)))))))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec13), LoadVarInst(stack, fTemp8))))))), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec17), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp10)))))))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fRec37), LoadVarInst(stack, fRec29)))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fRec33), LoadVarInst(stack, fRec25)))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp11))))))), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec17), LoadVarInst(stack, fTemp12)))))))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec17), LoadVarInst(stack, fTemp11))))))), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp12)))))))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(stack, fRec37), LoadVarInst(stack, fRec25)))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fRec33), LoadVarInst(stack, fRec29)))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp13))))))), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec17), LoadVarInst(stack, fTemp14)))))))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec17), LoadVarInst(stack, fTemp13))))))), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp14)))))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[Int32(0)])))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[Int32(0)])))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec2[Int32(0)])))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec3[Int32(0)])))
		StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec4[Int32(0)])))
		StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec5[Int32(0)])))
		StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec6[Int32(0)])))
		StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec7[Int32(0)])))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
		StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
		StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
		StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
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
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[32768])
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, float, fVec1[2048])
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fVec2[32768])
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "int", iConst11)
	DeclareVarInst(struct, float, fVec3[4096])
	DeclareVarInst(struct, "int", iConst12)
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fVec4[16384])
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "int", iConst16)
	DeclareVarInst(struct, float, fVec5[4096])
	DeclareVarInst(struct, "int", iConst17)
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fVec6[32768])
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, "int", iConst21)
	DeclareVarInst(struct, float, fVec7[4096])
	DeclareVarInst(struct, "int", iConst22)
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fVec8[16384])
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "int", iConst26)
	DeclareVarInst(struct, float, fVec9[2048])
	DeclareVarInst(struct, "int", iConst27)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fVec10[16384])
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "int", iConst31)
	DeclareVarInst(struct, float, fVec11[4096])
	DeclareVarInst(struct, "int", iConst32)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, float, fRec35[2])
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, float, fVec12[16384])
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "int", iConst36)
	DeclareVarInst(struct, float, fVec13[4096])
	DeclareVarInst(struct, "int", iConst37)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, float, fVec14[16384])
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "int", iConst41)
	DeclareVarInst(struct, float, fVec15[2048])
	DeclareVarInst(struct, "int", iConst42)
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, float, fRec7[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219990999f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst2, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst1))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0191229992f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst6, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst1), LoadVarInst(struct, fConst5))))))
	StoreVarInst(struct, iConst7, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst5), Float(-1.0f))))))
	StoreVarInst(struct, fConst8, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891012f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst9, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst8))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst10, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0273330007f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst11, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst8), LoadVarInst(struct, fConst10))))))
	StoreVarInst(struct, iConst12, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst10), Float(-1.0f))))))
	StoreVarInst(struct, fConst13, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst14, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst13))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst15, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0292910002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst16, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst13), LoadVarInst(struct, fConst15))))))
	StoreVarInst(struct, iConst17, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst15), Float(-1.0f))))))
	StoreVarInst(struct, fConst18, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389003f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst19, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst18))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst20, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0244210009f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst21, CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst18), LoadVarInst(struct, fConst20))))))
	StoreVarInst(struct, iConst22, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst20), Float(-1.0f))))))
	StoreVarInst(struct, fConst23, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst24, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst23))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst25, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0134579996f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst26, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst23), LoadVarInst(struct, fConst25))))))
	StoreVarInst(struct, iConst27, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst25), Float(-1.0f))))))
	StoreVarInst(struct, fConst28, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837002f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst29, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst28))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst30, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0316039994f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst31, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst28), LoadVarInst(struct, fConst30))))))
	StoreVarInst(struct, iConst32, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst30), Float(-1.0f))))))
	StoreVarInst(struct, fConst33, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713001f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst34, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst33))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst35, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0229039993f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst36, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst33), LoadVarInst(struct, fConst35))))))
	StoreVarInst(struct, iConst37, CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst35), Float(-1.0f))))))
	StoreVarInst(struct, fConst38, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153128996f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, fConst39, BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("*", Float(6.90775537f), LoadVarInst(struct, fConst38))), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst40, FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.0203460008f), LoadVarInst(struct, fConst0)), Float(0.5f))))
	StoreVarInst(struct, iConst41, CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(struct, fConst38), LoadVarInst(struct, fConst40))))))
	StoreVarInst(struct, iConst42, CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(struct, fConst40), Float(-1.0f))))))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(6000.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(3.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(200.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l1)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l3), Int32(2048))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(32768))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(4096))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(16384))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(4096))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(32768))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(4096))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(16384))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2048))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(16384))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(4096))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(16384))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(4096))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(16384))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2048))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(3))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(3))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(3))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(3))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input6, LoadVarInst(kFunArgs, inputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input7, LoadVarInst(kFunArgs, inputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fVslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst3), CastInst("float", LoadVarInst(struct, fVslider1)))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("/", LoadVarInst(stack, fSlow4), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow4)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow5))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("-", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow6)))))
	DeclareVarInst(stack, "float", fSlow10, CastInst("float", LoadVarInst(struct, fVslider2)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow1)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), CastInst("float", LoadVarInst(struct, fVslider3))))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("+", LoadVarInst(stack, fSlow12), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow12)), LoadVarInst(stack, fSlow13))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow16, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst9), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow17, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow17))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("/", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fSlow19)))
	DeclareVarInst(stack, "float", fSlow21, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow18)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow19))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("-", LoadVarInst(stack, fSlow20), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow21), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow20))), LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst9), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow16)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow25, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst14), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow26, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow25)))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow26))))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("/", LoadVarInst(stack, fSlow27), LoadVarInst(stack, fSlow28)))
	DeclareVarInst(stack, "float", fSlow30, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow27)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow28))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow31, BinopInst("-", LoadVarInst(stack, fSlow29), LoadVarInst(stack, fSlow30)))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow30), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow29))), LoadVarInst(stack, fSlow25)))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst14), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow25)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow34, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst19), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow35, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow34)))
	DeclareVarInst(stack, "float", fSlow36, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow35))))
	DeclareVarInst(stack, "float", fSlow37, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow35)))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("/", LoadVarInst(stack, fSlow36), LoadVarInst(stack, fSlow37)))
	DeclareVarInst(stack, "float", fSlow39, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow36)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow37))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow40, BinopInst("-", LoadVarInst(stack, fSlow38), LoadVarInst(stack, fSlow39)))
	DeclareVarInst(stack, "float", fSlow41, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow39), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow38))), LoadVarInst(stack, fSlow34)))
	DeclareVarInst(stack, "float", fSlow42, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst19), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow34)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow43, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst24), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow44, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow43)))
	DeclareVarInst(stack, "float", fSlow45, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow44))))
	DeclareVarInst(stack, "float", fSlow46, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow44)))
	DeclareVarInst(stack, "float", fSlow47, BinopInst("/", LoadVarInst(stack, fSlow45), LoadVarInst(stack, fSlow46)))
	DeclareVarInst(stack, "float", fSlow48, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow45)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow46))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow49, BinopInst("-", LoadVarInst(stack, fSlow47), LoadVarInst(stack, fSlow48)))
	DeclareVarInst(stack, "float", fSlow50, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow48), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow47))), LoadVarInst(stack, fSlow43)))
	DeclareVarInst(stack, "float", fSlow51, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst24), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow43)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow52, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst29), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow53, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow52)))
	DeclareVarInst(stack, "float", fSlow54, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow53))))
	DeclareVarInst(stack, "float", fSlow55, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow53)))
	DeclareVarInst(stack, "float", fSlow56, BinopInst("/", LoadVarInst(stack, fSlow54), LoadVarInst(stack, fSlow55)))
	DeclareVarInst(stack, "float", fSlow57, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow54)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow55))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow58, BinopInst("-", LoadVarInst(stack, fSlow56), LoadVarInst(stack, fSlow57)))
	DeclareVarInst(stack, "float", fSlow59, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow57), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow56))), LoadVarInst(stack, fSlow52)))
	DeclareVarInst(stack, "float", fSlow60, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst29), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow52)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow61, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst34), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow62, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow61)))
	DeclareVarInst(stack, "float", fSlow63, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow62))))
	DeclareVarInst(stack, "float", fSlow64, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow62)))
	DeclareVarInst(stack, "float", fSlow65, BinopInst("/", LoadVarInst(stack, fSlow63), LoadVarInst(stack, fSlow64)))
	DeclareVarInst(stack, "float", fSlow66, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow63)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow64))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow67, BinopInst("-", LoadVarInst(stack, fSlow65), LoadVarInst(stack, fSlow66)))
	DeclareVarInst(stack, "float", fSlow68, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow66), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow65))), LoadVarInst(stack, fSlow61)))
	DeclareVarInst(stack, "float", fSlow69, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst34), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow61)), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow70, FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst39), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow71, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow70)))
	DeclareVarInst(stack, "float", fSlow72, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fSlow71))))
	DeclareVarInst(stack, "float", fSlow73, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow71)))
	DeclareVarInst(stack, "float", fSlow74, BinopInst("/", LoadVarInst(stack, fSlow72), LoadVarInst(stack, fSlow73)))
	DeclareVarInst(stack, "float", fSlow75, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow72)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow73))), Float(-1.0f)))))
	DeclareVarInst(stack, "float", fSlow76, BinopInst("-", LoadVarInst(stack, fSlow74), LoadVarInst(stack, fSlow75)))
	DeclareVarInst(stack, "float", fSlow77, BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow75), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow74))), LoadVarInst(stack, fSlow70)))
	DeclareVarInst(stack, "float", fSlow78, BinopInst("+", BinopInst("/", FunCallInst("expf", BinopInst("/", LoadVarInst(struct, fConst39), LoadVarInst(stack, fSlow10))), LoadVarInst(stack, fSlow70)), Float(-1.0f)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fRec7[Int32(2)])))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow9), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec11[Int32(0)]))))))
			StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec10[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("+", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec8[Int32(1)])), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst6)), Int32(32767))])), CastInst("float", LoadVarInst(stack, input7[LoadVarInst(loop, i)]))))
			StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp0))
			StoreVarInst(struct, fRec8[Int32(0)], LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec9, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(struct, fRec3[Int32(2)])))))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec15[Int32(0)]))))))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec14[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec12[Int32(1)])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst11)), Int32(32767))])), CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)]))))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp1))
			StoreVarInst(struct, fRec12[Int32(0)], LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst12)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec13, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp1))))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fRec5[Int32(2)])))))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow31), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow32), BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow33), LoadVarInst(struct, fRec19[Int32(0)]))))))
			StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec18[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec16[Int32(1)])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst16)), Int32(16383))])), CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)]))))
			StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp2))
			StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst17)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec17, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp2))))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fRec1[Int32(2)])))))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow41), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow42), LoadVarInst(struct, fRec23[Int32(0)]))))))
			StoreVarInst(struct, fVec6[BinopInst("&", LoadVarInst(struct, IOTA), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec22[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec20[Int32(1)])), LoadVarInst(struct, fVec6[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst21)), Int32(32767))])), CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)]))))
			StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp3))
			StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst22)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp3))))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fRec6[Int32(2)])))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow49), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow50), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow51), LoadVarInst(struct, fRec27[Int32(0)]))))))
			StoreVarInst(struct, fVec8[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec26[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec8[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst26)), Int32(16383))]), CastInst("float", LoadVarInst(stack, input6[LoadVarInst(loop, i)]))), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec24[Int32(1)]))))
			StoreVarInst(struct, fVec9[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp4))
			StoreVarInst(struct, fRec24[Int32(0)], LoadVarInst(struct, fVec9[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst27)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec25, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp4)))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec31[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fRec2[Int32(2)])))))
			StoreVarInst(struct, fRec30[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow58), LoadVarInst(struct, fRec30[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow59), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow60), LoadVarInst(struct, fRec31[Int32(0)]))))))
			StoreVarInst(struct, fVec10[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec30[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec10[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst31)), Int32(16383))]), CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)]))), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec28[Int32(1)]))))
			StoreVarInst(struct, fVec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp5))
			StoreVarInst(struct, fRec28[Int32(0)], LoadVarInst(struct, fVec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst32)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec29, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp5)))
			StoreVarInst(struct, fRec35[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fRec4[Int32(2)])))))
			StoreVarInst(struct, fRec34[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow67), LoadVarInst(struct, fRec34[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow68), BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow69), LoadVarInst(struct, fRec35[Int32(0)]))))))
			StoreVarInst(struct, fVec12[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec34[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec12[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst36)), Int32(16383))]), CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)]))), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec32[Int32(1)]))))
			StoreVarInst(struct, fVec13[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp6))
			StoreVarInst(struct, fRec32[Int32(0)], LoadVarInst(struct, fVec13[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst37)), Int32(4095))]))
			DeclareVarInst(stack, "float", fRec33, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp6)))
			StoreVarInst(struct, fRec39[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec39[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(struct, fRec0[Int32(2)])))))
			StoreVarInst(struct, fRec38[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow76), LoadVarInst(struct, fRec38[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow77), BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("*", LoadVarInst(stack, fSlow78), LoadVarInst(struct, fRec39[Int32(0)]))))))
			StoreVarInst(struct, fVec14[BinopInst("&", LoadVarInst(struct, IOTA), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.353553385f), LoadVarInst(struct, fRec38[Int32(0)])), Float(9.99999968e-21f)))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("-", BinopInst("+", LoadVarInst(struct, fVec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst41)), Int32(16383))]), CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)]))), BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec36[Int32(1)]))))
			StoreVarInst(struct, fVec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp7))
			StoreVarInst(struct, fRec36[Int32(0)], LoadVarInst(struct, fVec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst42)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec37, BinopInst("*", Float(0.600000024f), LoadVarInst(stack, fTemp7)))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fRec37), LoadVarInst(stack, fRec33)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fRec25), BinopInst("+", LoadVarInst(stack, fRec29), LoadVarInst(stack, fTemp8))))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec17), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp9))))))))))))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), LoadVarInst(stack, fTemp9))))), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fRec17))))))))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(stack, fRec29), LoadVarInst(stack, fRec25)))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec17), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp8))))))), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec13), LoadVarInst(stack, fTemp10)))))))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec13), LoadVarInst(stack, fTemp8))))))), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec17), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp10)))))))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fRec37), LoadVarInst(stack, fRec29)))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fRec33), LoadVarInst(stack, fRec25)))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp11))))))), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec17), LoadVarInst(stack, fTemp12)))))))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec17), LoadVarInst(stack, fTemp11))))))), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp12)))))))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(stack, fRec37), LoadVarInst(stack, fRec25)))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fRec33), LoadVarInst(stack, fRec29)))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp13))))))), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec17), LoadVarInst(stack, fTemp14)))))))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec13), BinopInst("+", LoadVarInst(stack, fRec17), LoadVarInst(stack, fTemp13))))))), BinopInst("+", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec9), BinopInst("+", LoadVarInst(stack, fRec21), LoadVarInst(stack, fTemp14)))))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[Int32(0)])))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[Int32(0)])))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec2[Int32(0)])))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec3[Int32(0)])))
			StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec4[Int32(0)])))
			StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec5[Int32(0)])))
			StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec6[Int32(0)])))
			StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec7[Int32(0)])))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
			StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
			StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
			StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
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
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 72 bytes
Heap size int* = 0 bytes
Heap size real = 827804 bytes
Heap size = 827876 bytes
Stack size in compute = 444 bytes

