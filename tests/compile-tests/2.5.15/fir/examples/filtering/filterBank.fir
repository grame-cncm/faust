======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "tooltip", "See Faust's filters.lib for documentation and references")
	OpenVerticalBox("CONSTANT-Q FILTER BANK (Butterworth dyadic tree)")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the filter-bank has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider9, "1", "")
	AddMetaDeclareInst(fVslider9, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider9, "unit", "dB")
	AddVerticalSlider("0x00", fVslider9, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider8, "2", "")
	AddMetaDeclareInst(fVslider8, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider8, "unit", "dB")
	AddVerticalSlider("0x00", fVslider8, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider7, "3", "")
	AddMetaDeclareInst(fVslider7, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider7, "unit", "dB")
	AddVerticalSlider("0x00", fVslider7, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider6, "4", "")
	AddMetaDeclareInst(fVslider6, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider6, "unit", "dB")
	AddVerticalSlider("0x00", fVslider6, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider5, "5", "")
	AddMetaDeclareInst(fVslider5, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider5, "unit", "dB")
	AddVerticalSlider("0x00", fVslider5, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider4, "6", "")
	AddMetaDeclareInst(fVslider4, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider4, "unit", "dB")
	AddVerticalSlider("0x00", fVslider4, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider3, "7", "")
	AddMetaDeclareInst(fVslider3, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider3, "unit", "dB")
	AddVerticalSlider("0x00", fVslider3, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider2, "8", "")
	AddMetaDeclareInst(fVslider2, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider2, "unit", "dB")
	AddVerticalSlider("0x00", fVslider2, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider1, "9", "")
	AddMetaDeclareInst(fVslider1, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider1, "unit", "dB")
	AddVerticalSlider("0x00", fVslider1, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider0, "10", "")
	AddMetaDeclareInst(fVslider0, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("0x00", fVslider0, -10.0f, -70.0f, 10.0f, 0.100000001f)
	CloseboxInst
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
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, "float", fConst43)
	DeclareVarInst(struct, "float", fConst44)
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, "float", fConst45)
	DeclareVarInst(struct, "float", fConst46)
	DeclareVarInst(struct, "float", fConst47)
	DeclareVarInst(struct, "float", fConst48)
	DeclareVarInst(struct, "float", fConst49)
	DeclareVarInst(struct, "float", fConst50)
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, "float", fConst51)
	DeclareVarInst(struct, "float", fConst52)
	DeclareVarInst(struct, "float", fConst53)
	DeclareVarInst(struct, "float", fConst54)
	DeclareVarInst(struct, "float", fConst55)
	DeclareVarInst(struct, "float", fConst56)
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, "float", fConst57)
	DeclareVarInst(struct, "float", fConst58)
	DeclareVarInst(struct, "float", fConst59)
	DeclareVarInst(struct, "float", fConst60)
	DeclareVarInst(struct, "float", fConst61)
	DeclareVarInst(struct, "float", fConst62)
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "float", fConst63)
	DeclareVarInst(struct, "float", fConst64)
	DeclareVarInst(struct, "float", fConst65)
	DeclareVarInst(struct, "float", fConst66)
	DeclareVarInst(struct, "float", fConst67)
	DeclareVarInst(struct, "float", fConst68)
	DeclareVarInst(struct, "float", fConst69)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec23[3])
	DeclareVarInst(struct, float, fRec22[3])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "float", fConst70)
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, "float", fConst71)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, "float", fConst72)
	DeclareVarInst(struct, float, fRec19[3])
	DeclareVarInst(struct, float, fRec18[3])
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, float, fRec16[3])
	DeclareVarInst(struct, float, fRec15[3])
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, float, fRec13[3])
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "float", fConst73)
	DeclareVarInst(struct, "float", fConst74)
	DeclareVarInst(struct, "float", fConst75)
	DeclareVarInst(struct, "float", fConst76)
	DeclareVarInst(struct, "float", fConst77)
	DeclareVarInst(struct, "float", fConst78)
	DeclareVarInst(struct, "float", fConst79)
	DeclareVarInst(struct, float, fRec37[2])
	DeclareVarInst(struct, float, fRec36[3])
	DeclareVarInst(struct, float, fRec35[3])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "float", fConst80)
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, "float", fConst81)
	DeclareVarInst(struct, float, fRec33[3])
	DeclareVarInst(struct, "float", fConst82)
	DeclareVarInst(struct, float, fRec32[3])
	DeclareVarInst(struct, float, fRec31[3])
	DeclareVarInst(struct, float, fRec30[3])
	DeclareVarInst(struct, float, fRec29[3])
	DeclareVarInst(struct, float, fRec28[3])
	DeclareVarInst(struct, float, fRec27[3])
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, "float", fConst83)
	DeclareVarInst(struct, "float", fConst84)
	DeclareVarInst(struct, "float", fConst85)
	DeclareVarInst(struct, "float", fConst86)
	DeclareVarInst(struct, "float", fConst87)
	DeclareVarInst(struct, "float", fConst88)
	DeclareVarInst(struct, "float", fConst89)
	DeclareVarInst(struct, float, fRec49[2])
	DeclareVarInst(struct, float, fRec48[3])
	DeclareVarInst(struct, float, fRec47[3])
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, "float", fConst90)
	DeclareVarInst(struct, float, fRec46[2])
	DeclareVarInst(struct, "float", fConst91)
	DeclareVarInst(struct, float, fRec45[3])
	DeclareVarInst(struct, "float", fConst92)
	DeclareVarInst(struct, float, fRec44[3])
	DeclareVarInst(struct, float, fRec43[3])
	DeclareVarInst(struct, float, fRec42[3])
	DeclareVarInst(struct, float, fRec41[3])
	DeclareVarInst(struct, float, fRec40[3])
	DeclareVarInst(struct, float, fRec39[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fRec50[2])
	DeclareVarInst(struct, "float", fConst93)
	DeclareVarInst(struct, "float", fConst94)
	DeclareVarInst(struct, "float", fConst95)
	DeclareVarInst(struct, "float", fConst96)
	DeclareVarInst(struct, "float", fConst97)
	DeclareVarInst(struct, "float", fConst98)
	DeclareVarInst(struct, "float", fConst99)
	DeclareVarInst(struct, float, fRec60[2])
	DeclareVarInst(struct, float, fRec59[3])
	DeclareVarInst(struct, float, fRec58[3])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, "float", fConst100)
	DeclareVarInst(struct, float, fRec57[2])
	DeclareVarInst(struct, "float", fConst101)
	DeclareVarInst(struct, float, fRec56[3])
	DeclareVarInst(struct, "float", fConst102)
	DeclareVarInst(struct, float, fRec55[3])
	DeclareVarInst(struct, float, fRec54[3])
	DeclareVarInst(struct, float, fRec53[3])
	DeclareVarInst(struct, float, fRec52[3])
	DeclareVarInst(struct, float, fRec51[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, float, fRec61[2])
	DeclareVarInst(struct, "float", fConst103)
	DeclareVarInst(struct, "float", fConst104)
	DeclareVarInst(struct, "float", fConst105)
	DeclareVarInst(struct, "float", fConst106)
	DeclareVarInst(struct, "float", fConst107)
	DeclareVarInst(struct, "float", fConst108)
	DeclareVarInst(struct, "float", fConst109)
	DeclareVarInst(struct, float, fRec70[2])
	DeclareVarInst(struct, float, fRec69[3])
	DeclareVarInst(struct, float, fRec68[3])
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, "float", fConst110)
	DeclareVarInst(struct, float, fRec67[2])
	DeclareVarInst(struct, "float", fConst111)
	DeclareVarInst(struct, float, fRec66[3])
	DeclareVarInst(struct, "float", fConst112)
	DeclareVarInst(struct, float, fRec65[3])
	DeclareVarInst(struct, float, fRec64[3])
	DeclareVarInst(struct, float, fRec63[3])
	DeclareVarInst(struct, float, fRec62[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fRec71[2])
	DeclareVarInst(struct, "float", fConst113)
	DeclareVarInst(struct, "float", fConst114)
	DeclareVarInst(struct, "float", fConst115)
	DeclareVarInst(struct, "float", fConst116)
	DeclareVarInst(struct, "float", fConst117)
	DeclareVarInst(struct, "float", fConst118)
	DeclareVarInst(struct, "float", fConst119)
	DeclareVarInst(struct, float, fRec79[2])
	DeclareVarInst(struct, float, fRec78[3])
	DeclareVarInst(struct, float, fRec77[3])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, "float", fConst120)
	DeclareVarInst(struct, float, fRec76[2])
	DeclareVarInst(struct, "float", fConst121)
	DeclareVarInst(struct, float, fRec75[3])
	DeclareVarInst(struct, "float", fConst122)
	DeclareVarInst(struct, float, fRec74[3])
	DeclareVarInst(struct, float, fRec73[3])
	DeclareVarInst(struct, float, fRec72[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fRec80[2])
	DeclareVarInst(struct, "float", fConst123)
	DeclareVarInst(struct, "float", fConst124)
	DeclareVarInst(struct, "float", fConst125)
	DeclareVarInst(struct, "float", fConst126)
	DeclareVarInst(struct, "float", fConst127)
	DeclareVarInst(struct, "float", fConst128)
	DeclareVarInst(struct, "float", fConst129)
	DeclareVarInst(struct, float, fRec87[2])
	DeclareVarInst(struct, float, fRec86[3])
	DeclareVarInst(struct, float, fRec85[3])
	DeclareVarInst(struct, float, fVec7[2])
	DeclareVarInst(struct, "float", fConst130)
	DeclareVarInst(struct, float, fRec84[2])
	DeclareVarInst(struct, "float", fConst131)
	DeclareVarInst(struct, float, fRec83[3])
	DeclareVarInst(struct, "float", fConst132)
	DeclareVarInst(struct, float, fRec82[3])
	DeclareVarInst(struct, float, fRec81[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, float, fRec88[2])
	DeclareVarInst(struct, "float", fConst133)
	DeclareVarInst(struct, "float", fConst134)
	DeclareVarInst(struct, "float", fConst135)
	DeclareVarInst(struct, "float", fConst136)
	DeclareVarInst(struct, "float", fConst137)
	DeclareVarInst(struct, "float", fConst138)
	DeclareVarInst(struct, float, fRec94[2])
	DeclareVarInst(struct, float, fRec93[3])
	DeclareVarInst(struct, float, fRec92[3])
	DeclareVarInst(struct, float, fVec8[2])
	DeclareVarInst(struct, "float", fConst139)
	DeclareVarInst(struct, float, fRec91[2])
	DeclareVarInst(struct, "float", fConst140)
	DeclareVarInst(struct, float, fRec90[3])
	DeclareVarInst(struct, "float", fConst141)
	DeclareVarInst(struct, float, fRec89[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec95[2])
	DeclareVarInst(struct, float, fRec98[2])
	DeclareVarInst(struct, float, fRec97[3])
	DeclareVarInst(struct, float, fRec96[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, float, fRec99[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
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
	StoreVarInst(struct, fConst1, FunCallInst("tanf", BinopInst("/", Float(31415.9258f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(0.618034005f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst3)))
	StoreVarInst(struct, fConst5, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst1))))
	StoreVarInst(struct, fConst6, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst5))))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(1.61803401f)), LoadVarInst(struct, fConst1)), Float(1.0f))))
	StoreVarInst(struct, fConst8, BinopInst("+", LoadVarInst(struct, fConst2), Float(1.0f)))
	StoreVarInst(struct, fConst9, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst2)), LoadVarInst(struct, fConst8))))
	StoreVarInst(struct, fConst10, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst8)))
	StoreVarInst(struct, fConst11, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fConst12, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst5))))
	StoreVarInst(struct, fConst13, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-1.61803401f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst14, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-0.618034005f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst15, FunCallInst("tanf", BinopInst("/", Float(122.71846f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst16, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst15)))
	StoreVarInst(struct, fConst17, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(1.61803401f)), LoadVarInst(struct, fConst15)), Float(1.0f))))
	StoreVarInst(struct, fConst18, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(-1.61803401f)), LoadVarInst(struct, fConst15)), Float(1.0f)))
	StoreVarInst(struct, fConst19, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst15))))
	StoreVarInst(struct, fConst20, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst19))))
	StoreVarInst(struct, fConst21, FunCallInst("tanf", BinopInst("/", Float(245.43692f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst22, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst21)))
	StoreVarInst(struct, fConst23, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f))))
	StoreVarInst(struct, fConst24, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst25, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst21))))
	StoreVarInst(struct, fConst26, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst25))))
	StoreVarInst(struct, fConst27, FunCallInst("tanf", BinopInst("/", Float(490.87384f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst28, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst27)))
	StoreVarInst(struct, fConst29, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(1.61803401f)), LoadVarInst(struct, fConst27)), Float(1.0f))))
	StoreVarInst(struct, fConst30, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(-1.61803401f)), LoadVarInst(struct, fConst27)), Float(1.0f)))
	StoreVarInst(struct, fConst31, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst32, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst31))))
	StoreVarInst(struct, fConst33, FunCallInst("tanf", BinopInst("/", Float(981.747681f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst34, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst33)))
	StoreVarInst(struct, fConst35, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(1.61803401f)), LoadVarInst(struct, fConst33)), Float(1.0f))))
	StoreVarInst(struct, fConst36, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(-1.61803401f)), LoadVarInst(struct, fConst33)), Float(1.0f)))
	StoreVarInst(struct, fConst37, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst33))))
	StoreVarInst(struct, fConst38, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst37))))
	StoreVarInst(struct, fConst39, FunCallInst("tanf", BinopInst("/", Float(1963.49536f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst40, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst39)))
	StoreVarInst(struct, fConst41, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(1.61803401f)), LoadVarInst(struct, fConst39)), Float(1.0f))))
	StoreVarInst(struct, fConst42, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(-1.61803401f)), LoadVarInst(struct, fConst39)), Float(1.0f)))
	StoreVarInst(struct, fConst43, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst39))))
	StoreVarInst(struct, fConst44, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst43))))
	StoreVarInst(struct, fConst45, FunCallInst("tanf", BinopInst("/", Float(3926.99072f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst46, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst45)))
	StoreVarInst(struct, fConst47, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(1.61803401f)), LoadVarInst(struct, fConst45)), Float(1.0f))))
	StoreVarInst(struct, fConst48, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(-1.61803401f)), LoadVarInst(struct, fConst45)), Float(1.0f)))
	StoreVarInst(struct, fConst49, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst45))))
	StoreVarInst(struct, fConst50, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst49))))
	StoreVarInst(struct, fConst51, FunCallInst("tanf", BinopInst("/", Float(7853.98145f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst52, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst51)))
	StoreVarInst(struct, fConst53, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(1.61803401f)), LoadVarInst(struct, fConst51)), Float(1.0f))))
	StoreVarInst(struct, fConst54, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(-1.61803401f)), LoadVarInst(struct, fConst51)), Float(1.0f)))
	StoreVarInst(struct, fConst55, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst51))))
	StoreVarInst(struct, fConst56, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst57, FunCallInst("tanf", BinopInst("/", Float(15707.9629f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst58, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst57)))
	StoreVarInst(struct, fConst59, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f))))
	StoreVarInst(struct, fConst60, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst61, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst57))))
	StoreVarInst(struct, fConst62, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst61))))
	StoreVarInst(struct, fConst63, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(0.618034005f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst64, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst63)))
	StoreVarInst(struct, fConst65, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst61))))
	StoreVarInst(struct, fConst66, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f))))
	StoreVarInst(struct, fConst67, BinopInst("+", LoadVarInst(struct, fConst58), Float(1.0f)))
	StoreVarInst(struct, fConst68, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst58)), LoadVarInst(struct, fConst67))))
	StoreVarInst(struct, fConst69, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(struct, fConst67))))
	StoreVarInst(struct, fConst70, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst58)))
	StoreVarInst(struct, fConst71, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst72, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-0.618034005f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst73, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(0.618034005f)), LoadVarInst(struct, fConst51)), Float(1.0f)))
	StoreVarInst(struct, fConst74, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst73)))
	StoreVarInst(struct, fConst75, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst76, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(1.61803401f)), LoadVarInst(struct, fConst51)), Float(1.0f))))
	StoreVarInst(struct, fConst77, BinopInst("+", LoadVarInst(struct, fConst52), Float(1.0f)))
	StoreVarInst(struct, fConst78, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst52)), LoadVarInst(struct, fConst77))))
	StoreVarInst(struct, fConst79, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst63), LoadVarInst(struct, fConst77))))
	StoreVarInst(struct, fConst80, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst52)))
	StoreVarInst(struct, fConst81, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(-1.61803401f)), LoadVarInst(struct, fConst51)), Float(1.0f)))
	StoreVarInst(struct, fConst82, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(-0.618034005f)), LoadVarInst(struct, fConst51)), Float(1.0f)))
	StoreVarInst(struct, fConst83, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(0.618034005f)), LoadVarInst(struct, fConst45)), Float(1.0f)))
	StoreVarInst(struct, fConst84, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst83)))
	StoreVarInst(struct, fConst85, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst49))))
	StoreVarInst(struct, fConst86, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(1.61803401f)), LoadVarInst(struct, fConst45)), Float(1.0f))))
	StoreVarInst(struct, fConst87, BinopInst("+", LoadVarInst(struct, fConst46), Float(1.0f)))
	StoreVarInst(struct, fConst88, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst46)), LoadVarInst(struct, fConst87))))
	StoreVarInst(struct, fConst89, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst73), LoadVarInst(struct, fConst87))))
	StoreVarInst(struct, fConst90, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst46)))
	StoreVarInst(struct, fConst91, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(-1.61803401f)), LoadVarInst(struct, fConst45)), Float(1.0f)))
	StoreVarInst(struct, fConst92, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(-0.618034005f)), LoadVarInst(struct, fConst45)), Float(1.0f)))
	StoreVarInst(struct, fConst93, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(0.618034005f)), LoadVarInst(struct, fConst39)), Float(1.0f)))
	StoreVarInst(struct, fConst94, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst93)))
	StoreVarInst(struct, fConst95, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst43))))
	StoreVarInst(struct, fConst96, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(1.61803401f)), LoadVarInst(struct, fConst39)), Float(1.0f))))
	StoreVarInst(struct, fConst97, BinopInst("+", LoadVarInst(struct, fConst40), Float(1.0f)))
	StoreVarInst(struct, fConst98, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst40)), LoadVarInst(struct, fConst97))))
	StoreVarInst(struct, fConst99, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fConst83))))
	StoreVarInst(struct, fConst100, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst40)))
	StoreVarInst(struct, fConst101, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(-1.61803401f)), LoadVarInst(struct, fConst39)), Float(1.0f)))
	StoreVarInst(struct, fConst102, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(-0.618034005f)), LoadVarInst(struct, fConst39)), Float(1.0f)))
	StoreVarInst(struct, fConst103, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(0.618034005f)), LoadVarInst(struct, fConst33)), Float(1.0f)))
	StoreVarInst(struct, fConst104, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst103)))
	StoreVarInst(struct, fConst105, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst37))))
	StoreVarInst(struct, fConst106, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(1.61803401f)), LoadVarInst(struct, fConst33)), Float(1.0f))))
	StoreVarInst(struct, fConst107, BinopInst("+", LoadVarInst(struct, fConst34), Float(1.0f)))
	StoreVarInst(struct, fConst108, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst34)), LoadVarInst(struct, fConst107))))
	StoreVarInst(struct, fConst109, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst93), LoadVarInst(struct, fConst107))))
	StoreVarInst(struct, fConst110, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst34)))
	StoreVarInst(struct, fConst111, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(-1.61803401f)), LoadVarInst(struct, fConst33)), Float(1.0f)))
	StoreVarInst(struct, fConst112, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(-0.618034005f)), LoadVarInst(struct, fConst33)), Float(1.0f)))
	StoreVarInst(struct, fConst113, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(0.618034005f)), LoadVarInst(struct, fConst27)), Float(1.0f)))
	StoreVarInst(struct, fConst114, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst113)))
	StoreVarInst(struct, fConst115, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst31))))
	StoreVarInst(struct, fConst116, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(1.61803401f)), LoadVarInst(struct, fConst27)), Float(1.0f))))
	StoreVarInst(struct, fConst117, BinopInst("+", LoadVarInst(struct, fConst28), Float(1.0f)))
	StoreVarInst(struct, fConst118, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst28)), LoadVarInst(struct, fConst117))))
	StoreVarInst(struct, fConst119, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst103), LoadVarInst(struct, fConst117))))
	StoreVarInst(struct, fConst120, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst28)))
	StoreVarInst(struct, fConst121, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(-1.61803401f)), LoadVarInst(struct, fConst27)), Float(1.0f)))
	StoreVarInst(struct, fConst122, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(-0.618034005f)), LoadVarInst(struct, fConst27)), Float(1.0f)))
	StoreVarInst(struct, fConst123, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(0.618034005f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst124, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst123)))
	StoreVarInst(struct, fConst125, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst25))))
	StoreVarInst(struct, fConst126, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f))))
	StoreVarInst(struct, fConst127, BinopInst("+", LoadVarInst(struct, fConst22), Float(1.0f)))
	StoreVarInst(struct, fConst128, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst22)), LoadVarInst(struct, fConst127))))
	StoreVarInst(struct, fConst129, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst127), LoadVarInst(struct, fConst113))))
	StoreVarInst(struct, fConst130, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst22)))
	StoreVarInst(struct, fConst131, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst132, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-0.618034005f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst133, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(0.618034005f)), LoadVarInst(struct, fConst15)), Float(1.0f))))
	StoreVarInst(struct, fConst134, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst19))))
	StoreVarInst(struct, fConst135, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(1.61803401f)), LoadVarInst(struct, fConst15)), Float(1.0f))))
	StoreVarInst(struct, fConst136, BinopInst("+", LoadVarInst(struct, fConst16), Float(1.0f)))
	StoreVarInst(struct, fConst137, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst16)), LoadVarInst(struct, fConst136))))
	StoreVarInst(struct, fConst138, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst123), LoadVarInst(struct, fConst136))))
	StoreVarInst(struct, fConst139, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst16)))
	StoreVarInst(struct, fConst140, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(-1.61803401f)), LoadVarInst(struct, fConst15)), Float(1.0f)))
	StoreVarInst(struct, fConst141, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(-0.618034005f)), LoadVarInst(struct, fConst15)), Float(1.0f)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(-10.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
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
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(3))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(3))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(3))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(3))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(3))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l19)], Float(0.0f))
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
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(3))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(3))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(3))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(3))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(3))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(3))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(3))
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
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(3))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(3))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(3))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(3))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(3))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(3))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(3))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(3))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(3))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(3))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(3))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(3))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(3))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(2))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(2))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(3))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(3))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(2))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec57[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(3))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec56[LoadVarInst(loop, l60)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(3))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(3))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(3))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(3))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l64)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l65, Int32(0))
		BinopInst("<", LoadVarInst(loop, l65), Int32(3))
		StoreVarInst(loop, l65, BinopInst("+", LoadVarInst(loop, l65), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l65)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l66, Int32(0))
		BinopInst("<", LoadVarInst(loop, l66), Int32(2))
		StoreVarInst(loop, l66, BinopInst("+", LoadVarInst(loop, l66), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l66)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l67, Int32(0))
		BinopInst("<", LoadVarInst(loop, l67), Int32(2))
		StoreVarInst(loop, l67, BinopInst("+", LoadVarInst(loop, l67), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec70[LoadVarInst(loop, l67)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l68, Int32(0))
		BinopInst("<", LoadVarInst(loop, l68), Int32(3))
		StoreVarInst(loop, l68, BinopInst("+", LoadVarInst(loop, l68), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec69[LoadVarInst(loop, l68)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l69, Int32(0))
		BinopInst("<", LoadVarInst(loop, l69), Int32(3))
		StoreVarInst(loop, l69, BinopInst("+", LoadVarInst(loop, l69), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec68[LoadVarInst(loop, l69)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l70, Int32(0))
		BinopInst("<", LoadVarInst(loop, l70), Int32(2))
		StoreVarInst(loop, l70, BinopInst("+", LoadVarInst(loop, l70), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l70)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l71, Int32(0))
		BinopInst("<", LoadVarInst(loop, l71), Int32(2))
		StoreVarInst(loop, l71, BinopInst("+", LoadVarInst(loop, l71), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec67[LoadVarInst(loop, l71)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l72, Int32(0))
		BinopInst("<", LoadVarInst(loop, l72), Int32(3))
		StoreVarInst(loop, l72, BinopInst("+", LoadVarInst(loop, l72), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec66[LoadVarInst(loop, l72)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l73, Int32(0))
		BinopInst("<", LoadVarInst(loop, l73), Int32(3))
		StoreVarInst(loop, l73, BinopInst("+", LoadVarInst(loop, l73), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec65[LoadVarInst(loop, l73)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l74, Int32(0))
		BinopInst("<", LoadVarInst(loop, l74), Int32(3))
		StoreVarInst(loop, l74, BinopInst("+", LoadVarInst(loop, l74), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l74)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l75, Int32(0))
		BinopInst("<", LoadVarInst(loop, l75), Int32(3))
		StoreVarInst(loop, l75, BinopInst("+", LoadVarInst(loop, l75), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l75)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l76, Int32(0))
		BinopInst("<", LoadVarInst(loop, l76), Int32(3))
		StoreVarInst(loop, l76, BinopInst("+", LoadVarInst(loop, l76), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l76)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l77, Int32(0))
		BinopInst("<", LoadVarInst(loop, l77), Int32(2))
		StoreVarInst(loop, l77, BinopInst("+", LoadVarInst(loop, l77), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec71[LoadVarInst(loop, l77)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l78, Int32(0))
		BinopInst("<", LoadVarInst(loop, l78), Int32(2))
		StoreVarInst(loop, l78, BinopInst("+", LoadVarInst(loop, l78), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec79[LoadVarInst(loop, l78)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l79, Int32(0))
		BinopInst("<", LoadVarInst(loop, l79), Int32(3))
		StoreVarInst(loop, l79, BinopInst("+", LoadVarInst(loop, l79), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec78[LoadVarInst(loop, l79)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l80, Int32(0))
		BinopInst("<", LoadVarInst(loop, l80), Int32(3))
		StoreVarInst(loop, l80, BinopInst("+", LoadVarInst(loop, l80), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec77[LoadVarInst(loop, l80)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l81, Int32(0))
		BinopInst("<", LoadVarInst(loop, l81), Int32(2))
		StoreVarInst(loop, l81, BinopInst("+", LoadVarInst(loop, l81), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l81)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l82, Int32(0))
		BinopInst("<", LoadVarInst(loop, l82), Int32(2))
		StoreVarInst(loop, l82, BinopInst("+", LoadVarInst(loop, l82), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec76[LoadVarInst(loop, l82)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l83, Int32(0))
		BinopInst("<", LoadVarInst(loop, l83), Int32(3))
		StoreVarInst(loop, l83, BinopInst("+", LoadVarInst(loop, l83), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec75[LoadVarInst(loop, l83)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l84, Int32(0))
		BinopInst("<", LoadVarInst(loop, l84), Int32(3))
		StoreVarInst(loop, l84, BinopInst("+", LoadVarInst(loop, l84), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec74[LoadVarInst(loop, l84)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l85, Int32(0))
		BinopInst("<", LoadVarInst(loop, l85), Int32(3))
		StoreVarInst(loop, l85, BinopInst("+", LoadVarInst(loop, l85), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec73[LoadVarInst(loop, l85)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l86, Int32(0))
		BinopInst("<", LoadVarInst(loop, l86), Int32(3))
		StoreVarInst(loop, l86, BinopInst("+", LoadVarInst(loop, l86), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec72[LoadVarInst(loop, l86)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l87, Int32(0))
		BinopInst("<", LoadVarInst(loop, l87), Int32(2))
		StoreVarInst(loop, l87, BinopInst("+", LoadVarInst(loop, l87), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec80[LoadVarInst(loop, l87)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l88, Int32(0))
		BinopInst("<", LoadVarInst(loop, l88), Int32(2))
		StoreVarInst(loop, l88, BinopInst("+", LoadVarInst(loop, l88), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec87[LoadVarInst(loop, l88)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l89, Int32(0))
		BinopInst("<", LoadVarInst(loop, l89), Int32(3))
		StoreVarInst(loop, l89, BinopInst("+", LoadVarInst(loop, l89), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec86[LoadVarInst(loop, l89)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l90, Int32(0))
		BinopInst("<", LoadVarInst(loop, l90), Int32(3))
		StoreVarInst(loop, l90, BinopInst("+", LoadVarInst(loop, l90), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec85[LoadVarInst(loop, l90)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l91, Int32(0))
		BinopInst("<", LoadVarInst(loop, l91), Int32(2))
		StoreVarInst(loop, l91, BinopInst("+", LoadVarInst(loop, l91), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l91)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l92, Int32(0))
		BinopInst("<", LoadVarInst(loop, l92), Int32(2))
		StoreVarInst(loop, l92, BinopInst("+", LoadVarInst(loop, l92), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec84[LoadVarInst(loop, l92)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l93, Int32(0))
		BinopInst("<", LoadVarInst(loop, l93), Int32(3))
		StoreVarInst(loop, l93, BinopInst("+", LoadVarInst(loop, l93), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec83[LoadVarInst(loop, l93)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l94, Int32(0))
		BinopInst("<", LoadVarInst(loop, l94), Int32(3))
		StoreVarInst(loop, l94, BinopInst("+", LoadVarInst(loop, l94), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec82[LoadVarInst(loop, l94)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l95, Int32(0))
		BinopInst("<", LoadVarInst(loop, l95), Int32(3))
		StoreVarInst(loop, l95, BinopInst("+", LoadVarInst(loop, l95), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec81[LoadVarInst(loop, l95)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l96, Int32(0))
		BinopInst("<", LoadVarInst(loop, l96), Int32(2))
		StoreVarInst(loop, l96, BinopInst("+", LoadVarInst(loop, l96), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec88[LoadVarInst(loop, l96)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l97, Int32(0))
		BinopInst("<", LoadVarInst(loop, l97), Int32(2))
		StoreVarInst(loop, l97, BinopInst("+", LoadVarInst(loop, l97), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec94[LoadVarInst(loop, l97)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l98, Int32(0))
		BinopInst("<", LoadVarInst(loop, l98), Int32(3))
		StoreVarInst(loop, l98, BinopInst("+", LoadVarInst(loop, l98), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec93[LoadVarInst(loop, l98)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l99, Int32(0))
		BinopInst("<", LoadVarInst(loop, l99), Int32(3))
		StoreVarInst(loop, l99, BinopInst("+", LoadVarInst(loop, l99), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec92[LoadVarInst(loop, l99)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l100, Int32(0))
		BinopInst("<", LoadVarInst(loop, l100), Int32(2))
		StoreVarInst(loop, l100, BinopInst("+", LoadVarInst(loop, l100), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l100)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l101, Int32(0))
		BinopInst("<", LoadVarInst(loop, l101), Int32(2))
		StoreVarInst(loop, l101, BinopInst("+", LoadVarInst(loop, l101), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec91[LoadVarInst(loop, l101)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l102, Int32(0))
		BinopInst("<", LoadVarInst(loop, l102), Int32(3))
		StoreVarInst(loop, l102, BinopInst("+", LoadVarInst(loop, l102), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l102)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l103, Int32(0))
		BinopInst("<", LoadVarInst(loop, l103), Int32(3))
		StoreVarInst(loop, l103, BinopInst("+", LoadVarInst(loop, l103), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l103)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l104, Int32(0))
		BinopInst("<", LoadVarInst(loop, l104), Int32(2))
		StoreVarInst(loop, l104, BinopInst("+", LoadVarInst(loop, l104), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec95[LoadVarInst(loop, l104)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l105, Int32(0))
		BinopInst("<", LoadVarInst(loop, l105), Int32(2))
		StoreVarInst(loop, l105, BinopInst("+", LoadVarInst(loop, l105), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec98[LoadVarInst(loop, l105)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l106, Int32(0))
		BinopInst("<", LoadVarInst(loop, l106), Int32(3))
		StoreVarInst(loop, l106, BinopInst("+", LoadVarInst(loop, l106), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec97[LoadVarInst(loop, l106)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l107, Int32(0))
		BinopInst("<", LoadVarInst(loop, l107), Int32(3))
		StoreVarInst(loop, l107, BinopInst("+", LoadVarInst(loop, l107), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec96[LoadVarInst(loop, l107)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l108, Int32(0))
		BinopInst("<", LoadVarInst(loop, l108), Int32(2))
		StoreVarInst(loop, l108, BinopInst("+", LoadVarInst(loop, l108), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec99[LoadVarInst(loop, l108)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 13
Store = 0
Binop = 10
Numbers = 10
Declare = 13
Cast = 12
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider0))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider1))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider2))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider3))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider4))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider5))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider6))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider7))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider8))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider9))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 1120
Store = 292
Binop = 816
Numbers = 341
Declare = 47
Cast = 2
Select = 0
Loop = 1
Funcall = 10

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fTemp1))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst10), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(struct, fConst11), LoadVarInst(struct, fVec0[Int32(1)]))))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec10[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst13), LoadVarInst(struct, fRec9[Int32(2)]))))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec9[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(struct, fRec9[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec9[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst14), LoadVarInst(struct, fRec8[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec7[Int32(1)])))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec8[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec8[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec7[Int32(2)])), LoadVarInst(stack, fTemp2)))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec6[Int32(1)])))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec7[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec7[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec6[Int32(2)])), LoadVarInst(stack, fTemp3)))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec5[Int32(1)])))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec6[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec6[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec5[Int32(2)])), LoadVarInst(stack, fTemp4)))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec4[Int32(1)])))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec5[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec5[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec4[Int32(2)])), LoadVarInst(stack, fTemp5)))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec3[Int32(1)])))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec4[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec4[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec3[Int32(2)])), LoadVarInst(stack, fTemp6)))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec2[Int32(1)])))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec3[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp6), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec3[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec2[Int32(2)])), LoadVarInst(stack, fTemp7)))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec1[Int32(1)])))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec2[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp7), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec2[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec1[Int32(2)])), LoadVarInst(stack, fTemp8)))))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec0[Int32(1)])))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec1[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", LoadVarInst(stack, fTemp8), BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec1[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst59), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst60), LoadVarInst(struct, fRec0[Int32(2)])), LoadVarInst(stack, fTemp9)))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec11[Int32(1)]))))
		StoreVarInst(struct, fRec24[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst10), BinopInst("+", LoadVarInst(stack, fTemp1), LoadVarInst(struct, fVec0[Int32(1)])))))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec24[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst13), LoadVarInst(struct, fRec23[Int32(2)]))))))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(struct, fRec23[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec23[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec23[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst14), LoadVarInst(struct, fRec22[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(struct, fRec22[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec22[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec22[Int32(1)])))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp10))
		StoreVarInst(struct, fRec21[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst68), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst69), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst58), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(struct, fConst70), LoadVarInst(struct, fVec1[Int32(1)]))))))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec21[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst66), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst71), LoadVarInst(struct, fRec20[Int32(2)]))))))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst66), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(struct, fRec20[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(struct, fRec20[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(struct, fRec20[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst64), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fRec19[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec18[Int32(1)])))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst64), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(struct, fRec19[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(struct, fRec19[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp11), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec18[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec17[Int32(1)])))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec18[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp11), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec18[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp12), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec17[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec16[Int32(1)])))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec17[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp12), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec17[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp13), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec16[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec15[Int32(1)])))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec16[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp13), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec16[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp14), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec15[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec14[Int32(1)])))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec15[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp14), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec15[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec14[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec13[Int32(1)])))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec14[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec14[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp16), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec13[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec12[Int32(1)])))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec13[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp16), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec13[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", LoadVarInst(stack, fTemp17), BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec12[Int32(2)]))))))
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec25[Int32(1)]))))
		StoreVarInst(struct, fRec37[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst68), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst69), BinopInst("+", LoadVarInst(stack, fTemp10), LoadVarInst(struct, fVec1[Int32(1)])))))
		StoreVarInst(struct, fRec36[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec37[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst66), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec36[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst71), LoadVarInst(struct, fRec36[Int32(2)]))))))
		StoreVarInst(struct, fRec35[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst66), BinopInst("+", LoadVarInst(struct, fRec36[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec36[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst64), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fRec35[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(struct, fRec35[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec35[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec35[Int32(1)])))))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp18))
		StoreVarInst(struct, fRec34[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec34[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst52), LoadVarInst(stack, fTemp18)), BinopInst("*", LoadVarInst(struct, fConst80), LoadVarInst(struct, fVec2[Int32(1)]))))))
		StoreVarInst(struct, fRec33[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec34[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst76), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec33[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec33[Int32(2)]))))))
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst76), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst55), LoadVarInst(struct, fRec33[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst75), LoadVarInst(struct, fRec33[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst55), LoadVarInst(struct, fRec33[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec32[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec32[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec31[Int32(1)])))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst75), LoadVarInst(struct, fRec32[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst55), LoadVarInst(struct, fRec32[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst55), LoadVarInst(struct, fRec32[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp19), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec31[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec30[Int32(1)])))
		StoreVarInst(struct, fRec30[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec31[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp19), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec31[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp20), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec30[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec29[Int32(1)])))
		StoreVarInst(struct, fRec29[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec30[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp20), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec30[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp21), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec29[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec28[Int32(1)])))
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec29[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp21), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec29[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp22), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec28[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec27[Int32(1)])))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec28[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp22), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec28[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp23), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec27[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec26[Int32(1)])))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec27[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp23), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec27[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp24), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec26[Int32(2)]))))))
		StoreVarInst(struct, fRec38[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec38[Int32(1)]))))
		StoreVarInst(struct, fRec49[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec49[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", LoadVarInst(stack, fTemp18), LoadVarInst(struct, fVec2[Int32(1)])))))
		StoreVarInst(struct, fRec48[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec49[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst76), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec48[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec48[Int32(2)]))))))
		StoreVarInst(struct, fRec47[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst76), BinopInst("+", LoadVarInst(struct, fRec48[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec48[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec48[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec47[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec47[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(struct, fRec47[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec47[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec47[Int32(1)])))))
		StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp25))
		StoreVarInst(struct, fRec46[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst88), LoadVarInst(struct, fRec46[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst46), LoadVarInst(stack, fTemp25)), BinopInst("*", LoadVarInst(struct, fConst90), LoadVarInst(struct, fVec3[Int32(1)]))))))
		StoreVarInst(struct, fRec45[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec46[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst86), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec45[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec45[Int32(2)]))))))
		StoreVarInst(struct, fRec44[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst86), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec45[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(struct, fRec45[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec45[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec44[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec44[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec43[Int32(1)])))
		StoreVarInst(struct, fRec43[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(struct, fRec44[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec44[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec44[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp26), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec43[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec42[Int32(1)])))
		StoreVarInst(struct, fRec42[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec43[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp26), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec43[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec42[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec41[Int32(1)])))
		StoreVarInst(struct, fRec41[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec42[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec42[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec41[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec40[Int32(1)])))
		StoreVarInst(struct, fRec40[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec41[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec41[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp29), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec40[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec39[Int32(1)])))
		StoreVarInst(struct, fRec39[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec40[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp29), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec40[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec39[Int32(2)]))))))
		StoreVarInst(struct, fRec50[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec50[Int32(1)]))))
		StoreVarInst(struct, fRec60[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst88), LoadVarInst(struct, fRec60[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fVec3[Int32(1)])))))
		StoreVarInst(struct, fRec59[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec60[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst86), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec59[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec59[Int32(2)]))))))
		StoreVarInst(struct, fRec58[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst86), BinopInst("+", LoadVarInst(struct, fRec59[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec59[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec59[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec58[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec58[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(struct, fRec58[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec58[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec58[Int32(1)])))))
		StoreVarInst(struct, fVec4[Int32(0)], LoadVarInst(stack, fTemp31))
		StoreVarInst(struct, fRec57[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec57[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst40), LoadVarInst(stack, fTemp31)), BinopInst("*", LoadVarInst(struct, fConst100), LoadVarInst(struct, fVec4[Int32(1)]))))))
		StoreVarInst(struct, fRec56[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec57[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst96), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec56[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec56[Int32(2)]))))))
		StoreVarInst(struct, fRec55[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst96), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst43), LoadVarInst(struct, fRec56[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst95), LoadVarInst(struct, fRec56[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst43), LoadVarInst(struct, fRec56[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec55[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec55[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp32, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec54[Int32(1)])))
		StoreVarInst(struct, fRec54[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst95), LoadVarInst(struct, fRec55[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst43), LoadVarInst(struct, fRec55[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst43), LoadVarInst(struct, fRec55[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp32), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec54[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec53[Int32(1)])))
		StoreVarInst(struct, fRec53[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec54[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp32), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec54[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp33), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec53[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp34, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec52[Int32(1)])))
		StoreVarInst(struct, fRec52[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec53[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp33), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec53[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp34), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec52[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec51[Int32(1)])))
		StoreVarInst(struct, fRec51[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec52[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp34), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec52[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp35), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec51[Int32(2)]))))))
		StoreVarInst(struct, fRec61[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec61[Int32(1)]))))
		StoreVarInst(struct, fRec70[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec70[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", LoadVarInst(stack, fTemp31), LoadVarInst(struct, fVec4[Int32(1)])))))
		StoreVarInst(struct, fRec69[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec70[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst96), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec69[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec69[Int32(2)]))))))
		StoreVarInst(struct, fRec68[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst96), BinopInst("+", LoadVarInst(struct, fRec69[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec69[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec69[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec68[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec68[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(struct, fRec68[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec68[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec68[Int32(1)])))))
		StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp36))
		StoreVarInst(struct, fRec67[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst108), LoadVarInst(struct, fRec67[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst34), LoadVarInst(stack, fTemp36)), BinopInst("*", LoadVarInst(struct, fConst110), LoadVarInst(struct, fVec5[Int32(1)]))))))
		StoreVarInst(struct, fRec66[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec67[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst106), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec66[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst111), LoadVarInst(struct, fRec66[Int32(2)]))))))
		StoreVarInst(struct, fRec65[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst106), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(struct, fRec66[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(struct, fRec66[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(struct, fRec66[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec65[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst112), LoadVarInst(struct, fRec65[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec64[Int32(1)])))
		StoreVarInst(struct, fRec64[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(struct, fRec65[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(struct, fRec65[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(struct, fRec65[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp37), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec64[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec63[Int32(1)])))
		StoreVarInst(struct, fRec63[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec64[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp37), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec64[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp38), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec63[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec62[Int32(1)])))
		StoreVarInst(struct, fRec62[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec63[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp38), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec63[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp39), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec62[Int32(2)]))))))
		StoreVarInst(struct, fRec71[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec71[Int32(1)]))))
		StoreVarInst(struct, fRec79[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst108), LoadVarInst(struct, fRec79[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", LoadVarInst(stack, fTemp36), LoadVarInst(struct, fVec5[Int32(1)])))))
		StoreVarInst(struct, fRec78[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec79[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst106), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec78[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst111), LoadVarInst(struct, fRec78[Int32(2)]))))))
		StoreVarInst(struct, fRec77[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst106), BinopInst("+", LoadVarInst(struct, fRec78[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec78[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec78[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec77[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst112), LoadVarInst(struct, fRec77[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("+", LoadVarInst(struct, fRec77[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec77[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec77[Int32(1)])))))
		StoreVarInst(struct, fVec6[Int32(0)], LoadVarInst(stack, fTemp40))
		StoreVarInst(struct, fRec76[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst118), LoadVarInst(struct, fRec76[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst119), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst28), LoadVarInst(stack, fTemp40)), BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fVec6[Int32(1)]))))))
		StoreVarInst(struct, fRec75[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec76[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst116), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec75[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec75[Int32(2)]))))))
		StoreVarInst(struct, fRec74[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst116), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fRec75[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst115), LoadVarInst(struct, fRec75[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fRec75[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst114), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec74[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst122), LoadVarInst(struct, fRec74[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec73[Int32(1)])))
		StoreVarInst(struct, fRec73[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst114), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst115), LoadVarInst(struct, fRec74[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fRec74[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fRec74[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec73[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec72[Int32(1)])))
		StoreVarInst(struct, fRec72[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec73[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec73[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp42), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec72[Int32(2)]))))))
		StoreVarInst(struct, fRec80[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec80[Int32(1)]))))
		StoreVarInst(struct, fRec87[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst118), LoadVarInst(struct, fRec87[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst119), BinopInst("+", LoadVarInst(stack, fTemp40), LoadVarInst(struct, fVec6[Int32(1)])))))
		StoreVarInst(struct, fRec86[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec87[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst116), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec86[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec86[Int32(2)]))))))
		StoreVarInst(struct, fRec85[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst116), BinopInst("+", LoadVarInst(struct, fRec86[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec86[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec86[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst114), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec85[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst122), LoadVarInst(struct, fRec85[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("+", LoadVarInst(struct, fRec85[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec85[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec85[Int32(1)])))))
		StoreVarInst(struct, fVec7[Int32(0)], LoadVarInst(stack, fTemp43))
		StoreVarInst(struct, fRec84[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst128), LoadVarInst(struct, fRec84[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst129), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst22), LoadVarInst(stack, fTemp43)), BinopInst("*", LoadVarInst(struct, fConst130), LoadVarInst(struct, fVec7[Int32(1)]))))))
		StoreVarInst(struct, fRec83[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec84[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst126), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec83[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst131), LoadVarInst(struct, fRec83[Int32(2)]))))))
		StoreVarInst(struct, fRec82[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst126), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(struct, fRec83[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst125), LoadVarInst(struct, fRec83[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(struct, fRec83[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec82[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst132), LoadVarInst(struct, fRec82[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp44, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec81[Int32(1)])))
		StoreVarInst(struct, fRec81[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst125), LoadVarInst(struct, fRec82[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(struct, fRec82[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(struct, fRec82[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp44), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec81[Int32(2)]))))))
		StoreVarInst(struct, fRec88[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec88[Int32(1)]))))
		StoreVarInst(struct, fRec94[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst128), LoadVarInst(struct, fRec94[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst129), BinopInst("+", LoadVarInst(stack, fTemp43), LoadVarInst(struct, fVec7[Int32(1)])))))
		StoreVarInst(struct, fRec93[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec94[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst126), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec93[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst131), LoadVarInst(struct, fRec93[Int32(2)]))))))
		StoreVarInst(struct, fRec92[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst126), BinopInst("+", LoadVarInst(struct, fRec93[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec93[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec93[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec92[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst132), LoadVarInst(struct, fRec92[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("+", LoadVarInst(struct, fRec92[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec92[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec92[Int32(1)])))))
		StoreVarInst(struct, fVec8[Int32(0)], LoadVarInst(stack, fTemp45))
		StoreVarInst(struct, fRec91[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst137), LoadVarInst(struct, fRec91[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst138), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst16), LoadVarInst(stack, fTemp45)), BinopInst("*", LoadVarInst(struct, fConst139), LoadVarInst(struct, fVec8[Int32(1)]))))))
		StoreVarInst(struct, fRec90[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec91[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec90[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec90[Int32(2)]))))))
		StoreVarInst(struct, fRec89[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec90[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec90[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec90[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec89[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst141), LoadVarInst(struct, fRec89[Int32(2)]))))))
		StoreVarInst(struct, fRec95[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow9), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec95[Int32(1)]))))
		StoreVarInst(struct, fRec98[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst137), LoadVarInst(struct, fRec98[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst138), BinopInst("+", LoadVarInst(stack, fTemp45), LoadVarInst(struct, fVec8[Int32(1)])))))
		StoreVarInst(struct, fRec97[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec98[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec97[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec97[Int32(2)]))))))
		StoreVarInst(struct, fRec96[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(struct, fRec97[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec97[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec97[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec96[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst141), LoadVarInst(struct, fRec96[Int32(2)]))))))
		StoreVarInst(struct, fRec99[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec99[Int32(1)]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst59), BinopInst("+", LoadVarInst(stack, fTemp9), BinopInst("*", LoadVarInst(struct, fConst60), LoadVarInst(struct, fRec0[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec11[Int32(0)])))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", LoadVarInst(stack, fTemp17), BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec12[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec25[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec26[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp24), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec26[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec38[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec39[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec39[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec50[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec51[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp35), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec51[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec61[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec62[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp39), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec62[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec71[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec72[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp42), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec72[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec80[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec81[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp44), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec81[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec88[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec89[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec89[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec89[Int32(2)]))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec95[Int32(0)])))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec96[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec96[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec96[Int32(1)])))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec99[Int32(0)]))))))))))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(2)], LoadVarInst(struct, fRec23[Int32(1)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(2)], LoadVarInst(struct, fRec22[Int32(1)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(2)], LoadVarInst(struct, fRec20[Int32(1)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(2)], LoadVarInst(struct, fRec19[Int32(1)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(2)], LoadVarInst(struct, fRec18[Int32(1)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(2)], LoadVarInst(struct, fRec17[Int32(1)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(2)], LoadVarInst(struct, fRec16[Int32(1)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(2)], LoadVarInst(struct, fRec15[Int32(1)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(2)], LoadVarInst(struct, fRec13[Int32(1)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
		StoreVarInst(struct, fRec36[Int32(2)], LoadVarInst(struct, fRec36[Int32(1)]))
		StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
		StoreVarInst(struct, fRec35[Int32(2)], LoadVarInst(struct, fRec35[Int32(1)]))
		StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
		StoreVarInst(struct, fRec33[Int32(2)], LoadVarInst(struct, fRec33[Int32(1)]))
		StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(2)], LoadVarInst(struct, fRec32[Int32(1)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fRec31[Int32(2)], LoadVarInst(struct, fRec31[Int32(1)]))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(2)], LoadVarInst(struct, fRec30[Int32(1)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fRec29[Int32(2)], LoadVarInst(struct, fRec29[Int32(1)]))
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(2)], LoadVarInst(struct, fRec28[Int32(1)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(2)], LoadVarInst(struct, fRec27[Int32(1)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
		StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
		StoreVarInst(struct, fRec48[Int32(2)], LoadVarInst(struct, fRec48[Int32(1)]))
		StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
		StoreVarInst(struct, fRec47[Int32(2)], LoadVarInst(struct, fRec47[Int32(1)]))
		StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
		StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
		StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
		StoreVarInst(struct, fRec45[Int32(2)], LoadVarInst(struct, fRec45[Int32(1)]))
		StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
		StoreVarInst(struct, fRec44[Int32(2)], LoadVarInst(struct, fRec44[Int32(1)]))
		StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
		StoreVarInst(struct, fRec43[Int32(2)], LoadVarInst(struct, fRec43[Int32(1)]))
		StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
		StoreVarInst(struct, fRec42[Int32(2)], LoadVarInst(struct, fRec42[Int32(1)]))
		StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
		StoreVarInst(struct, fRec41[Int32(2)], LoadVarInst(struct, fRec41[Int32(1)]))
		StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
		StoreVarInst(struct, fRec40[Int32(2)], LoadVarInst(struct, fRec40[Int32(1)]))
		StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
		StoreVarInst(struct, fRec39[Int32(2)], LoadVarInst(struct, fRec39[Int32(1)]))
		StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
		StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
		StoreVarInst(struct, fRec60[Int32(1)], LoadVarInst(struct, fRec60[Int32(0)]))
		StoreVarInst(struct, fRec59[Int32(2)], LoadVarInst(struct, fRec59[Int32(1)]))
		StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
		StoreVarInst(struct, fRec58[Int32(2)], LoadVarInst(struct, fRec58[Int32(1)]))
		StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
		StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
		StoreVarInst(struct, fRec57[Int32(1)], LoadVarInst(struct, fRec57[Int32(0)]))
		StoreVarInst(struct, fRec56[Int32(2)], LoadVarInst(struct, fRec56[Int32(1)]))
		StoreVarInst(struct, fRec56[Int32(1)], LoadVarInst(struct, fRec56[Int32(0)]))
		StoreVarInst(struct, fRec55[Int32(2)], LoadVarInst(struct, fRec55[Int32(1)]))
		StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
		StoreVarInst(struct, fRec54[Int32(2)], LoadVarInst(struct, fRec54[Int32(1)]))
		StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
		StoreVarInst(struct, fRec53[Int32(2)], LoadVarInst(struct, fRec53[Int32(1)]))
		StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
		StoreVarInst(struct, fRec52[Int32(2)], LoadVarInst(struct, fRec52[Int32(1)]))
		StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
		StoreVarInst(struct, fRec51[Int32(2)], LoadVarInst(struct, fRec51[Int32(1)]))
		StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
		StoreVarInst(struct, fRec61[Int32(1)], LoadVarInst(struct, fRec61[Int32(0)]))
		StoreVarInst(struct, fRec70[Int32(1)], LoadVarInst(struct, fRec70[Int32(0)]))
		StoreVarInst(struct, fRec69[Int32(2)], LoadVarInst(struct, fRec69[Int32(1)]))
		StoreVarInst(struct, fRec69[Int32(1)], LoadVarInst(struct, fRec69[Int32(0)]))
		StoreVarInst(struct, fRec68[Int32(2)], LoadVarInst(struct, fRec68[Int32(1)]))
		StoreVarInst(struct, fRec68[Int32(1)], LoadVarInst(struct, fRec68[Int32(0)]))
		StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
		StoreVarInst(struct, fRec67[Int32(1)], LoadVarInst(struct, fRec67[Int32(0)]))
		StoreVarInst(struct, fRec66[Int32(2)], LoadVarInst(struct, fRec66[Int32(1)]))
		StoreVarInst(struct, fRec66[Int32(1)], LoadVarInst(struct, fRec66[Int32(0)]))
		StoreVarInst(struct, fRec65[Int32(2)], LoadVarInst(struct, fRec65[Int32(1)]))
		StoreVarInst(struct, fRec65[Int32(1)], LoadVarInst(struct, fRec65[Int32(0)]))
		StoreVarInst(struct, fRec64[Int32(2)], LoadVarInst(struct, fRec64[Int32(1)]))
		StoreVarInst(struct, fRec64[Int32(1)], LoadVarInst(struct, fRec64[Int32(0)]))
		StoreVarInst(struct, fRec63[Int32(2)], LoadVarInst(struct, fRec63[Int32(1)]))
		StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
		StoreVarInst(struct, fRec62[Int32(2)], LoadVarInst(struct, fRec62[Int32(1)]))
		StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
		StoreVarInst(struct, fRec71[Int32(1)], LoadVarInst(struct, fRec71[Int32(0)]))
		StoreVarInst(struct, fRec79[Int32(1)], LoadVarInst(struct, fRec79[Int32(0)]))
		StoreVarInst(struct, fRec78[Int32(2)], LoadVarInst(struct, fRec78[Int32(1)]))
		StoreVarInst(struct, fRec78[Int32(1)], LoadVarInst(struct, fRec78[Int32(0)]))
		StoreVarInst(struct, fRec77[Int32(2)], LoadVarInst(struct, fRec77[Int32(1)]))
		StoreVarInst(struct, fRec77[Int32(1)], LoadVarInst(struct, fRec77[Int32(0)]))
		StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
		StoreVarInst(struct, fRec76[Int32(1)], LoadVarInst(struct, fRec76[Int32(0)]))
		StoreVarInst(struct, fRec75[Int32(2)], LoadVarInst(struct, fRec75[Int32(1)]))
		StoreVarInst(struct, fRec75[Int32(1)], LoadVarInst(struct, fRec75[Int32(0)]))
		StoreVarInst(struct, fRec74[Int32(2)], LoadVarInst(struct, fRec74[Int32(1)]))
		StoreVarInst(struct, fRec74[Int32(1)], LoadVarInst(struct, fRec74[Int32(0)]))
		StoreVarInst(struct, fRec73[Int32(2)], LoadVarInst(struct, fRec73[Int32(1)]))
		StoreVarInst(struct, fRec73[Int32(1)], LoadVarInst(struct, fRec73[Int32(0)]))
		StoreVarInst(struct, fRec72[Int32(2)], LoadVarInst(struct, fRec72[Int32(1)]))
		StoreVarInst(struct, fRec72[Int32(1)], LoadVarInst(struct, fRec72[Int32(0)]))
		StoreVarInst(struct, fRec80[Int32(1)], LoadVarInst(struct, fRec80[Int32(0)]))
		StoreVarInst(struct, fRec87[Int32(1)], LoadVarInst(struct, fRec87[Int32(0)]))
		StoreVarInst(struct, fRec86[Int32(2)], LoadVarInst(struct, fRec86[Int32(1)]))
		StoreVarInst(struct, fRec86[Int32(1)], LoadVarInst(struct, fRec86[Int32(0)]))
		StoreVarInst(struct, fRec85[Int32(2)], LoadVarInst(struct, fRec85[Int32(1)]))
		StoreVarInst(struct, fRec85[Int32(1)], LoadVarInst(struct, fRec85[Int32(0)]))
		StoreVarInst(struct, fVec7[Int32(1)], LoadVarInst(struct, fVec7[Int32(0)]))
		StoreVarInst(struct, fRec84[Int32(1)], LoadVarInst(struct, fRec84[Int32(0)]))
		StoreVarInst(struct, fRec83[Int32(2)], LoadVarInst(struct, fRec83[Int32(1)]))
		StoreVarInst(struct, fRec83[Int32(1)], LoadVarInst(struct, fRec83[Int32(0)]))
		StoreVarInst(struct, fRec82[Int32(2)], LoadVarInst(struct, fRec82[Int32(1)]))
		StoreVarInst(struct, fRec82[Int32(1)], LoadVarInst(struct, fRec82[Int32(0)]))
		StoreVarInst(struct, fRec81[Int32(2)], LoadVarInst(struct, fRec81[Int32(1)]))
		StoreVarInst(struct, fRec81[Int32(1)], LoadVarInst(struct, fRec81[Int32(0)]))
		StoreVarInst(struct, fRec88[Int32(1)], LoadVarInst(struct, fRec88[Int32(0)]))
		StoreVarInst(struct, fRec94[Int32(1)], LoadVarInst(struct, fRec94[Int32(0)]))
		StoreVarInst(struct, fRec93[Int32(2)], LoadVarInst(struct, fRec93[Int32(1)]))
		StoreVarInst(struct, fRec93[Int32(1)], LoadVarInst(struct, fRec93[Int32(0)]))
		StoreVarInst(struct, fRec92[Int32(2)], LoadVarInst(struct, fRec92[Int32(1)]))
		StoreVarInst(struct, fRec92[Int32(1)], LoadVarInst(struct, fRec92[Int32(0)]))
		StoreVarInst(struct, fVec8[Int32(1)], LoadVarInst(struct, fVec8[Int32(0)]))
		StoreVarInst(struct, fRec91[Int32(1)], LoadVarInst(struct, fRec91[Int32(0)]))
		StoreVarInst(struct, fRec90[Int32(2)], LoadVarInst(struct, fRec90[Int32(1)]))
		StoreVarInst(struct, fRec90[Int32(1)], LoadVarInst(struct, fRec90[Int32(0)]))
		StoreVarInst(struct, fRec89[Int32(2)], LoadVarInst(struct, fRec89[Int32(1)]))
		StoreVarInst(struct, fRec89[Int32(1)], LoadVarInst(struct, fRec89[Int32(0)]))
		StoreVarInst(struct, fRec95[Int32(1)], LoadVarInst(struct, fRec95[Int32(0)]))
		StoreVarInst(struct, fRec98[Int32(1)], LoadVarInst(struct, fRec98[Int32(0)]))
		StoreVarInst(struct, fRec97[Int32(2)], LoadVarInst(struct, fRec97[Int32(1)]))
		StoreVarInst(struct, fRec97[Int32(1)], LoadVarInst(struct, fRec97[Int32(0)]))
		StoreVarInst(struct, fRec96[Int32(2)], LoadVarInst(struct, fRec96[Int32(1)]))
		StoreVarInst(struct, fRec96[Int32(1)], LoadVarInst(struct, fRec96[Int32(0)]))
		StoreVarInst(struct, fRec99[Int32(1)], LoadVarInst(struct, fRec99[Int32(0)]))
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
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, "float", fConst43)
	DeclareVarInst(struct, "float", fConst44)
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, "float", fConst45)
	DeclareVarInst(struct, "float", fConst46)
	DeclareVarInst(struct, "float", fConst47)
	DeclareVarInst(struct, "float", fConst48)
	DeclareVarInst(struct, "float", fConst49)
	DeclareVarInst(struct, "float", fConst50)
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, "float", fConst51)
	DeclareVarInst(struct, "float", fConst52)
	DeclareVarInst(struct, "float", fConst53)
	DeclareVarInst(struct, "float", fConst54)
	DeclareVarInst(struct, "float", fConst55)
	DeclareVarInst(struct, "float", fConst56)
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, "float", fConst57)
	DeclareVarInst(struct, "float", fConst58)
	DeclareVarInst(struct, "float", fConst59)
	DeclareVarInst(struct, "float", fConst60)
	DeclareVarInst(struct, "float", fConst61)
	DeclareVarInst(struct, "float", fConst62)
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "float", fConst63)
	DeclareVarInst(struct, "float", fConst64)
	DeclareVarInst(struct, "float", fConst65)
	DeclareVarInst(struct, "float", fConst66)
	DeclareVarInst(struct, "float", fConst67)
	DeclareVarInst(struct, "float", fConst68)
	DeclareVarInst(struct, "float", fConst69)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec23[3])
	DeclareVarInst(struct, float, fRec22[3])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "float", fConst70)
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, "float", fConst71)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, "float", fConst72)
	DeclareVarInst(struct, float, fRec19[3])
	DeclareVarInst(struct, float, fRec18[3])
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, float, fRec16[3])
	DeclareVarInst(struct, float, fRec15[3])
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, float, fRec13[3])
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "float", fConst73)
	DeclareVarInst(struct, "float", fConst74)
	DeclareVarInst(struct, "float", fConst75)
	DeclareVarInst(struct, "float", fConst76)
	DeclareVarInst(struct, "float", fConst77)
	DeclareVarInst(struct, "float", fConst78)
	DeclareVarInst(struct, "float", fConst79)
	DeclareVarInst(struct, float, fRec37[2])
	DeclareVarInst(struct, float, fRec36[3])
	DeclareVarInst(struct, float, fRec35[3])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "float", fConst80)
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, "float", fConst81)
	DeclareVarInst(struct, float, fRec33[3])
	DeclareVarInst(struct, "float", fConst82)
	DeclareVarInst(struct, float, fRec32[3])
	DeclareVarInst(struct, float, fRec31[3])
	DeclareVarInst(struct, float, fRec30[3])
	DeclareVarInst(struct, float, fRec29[3])
	DeclareVarInst(struct, float, fRec28[3])
	DeclareVarInst(struct, float, fRec27[3])
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, "float", fConst83)
	DeclareVarInst(struct, "float", fConst84)
	DeclareVarInst(struct, "float", fConst85)
	DeclareVarInst(struct, "float", fConst86)
	DeclareVarInst(struct, "float", fConst87)
	DeclareVarInst(struct, "float", fConst88)
	DeclareVarInst(struct, "float", fConst89)
	DeclareVarInst(struct, float, fRec49[2])
	DeclareVarInst(struct, float, fRec48[3])
	DeclareVarInst(struct, float, fRec47[3])
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, "float", fConst90)
	DeclareVarInst(struct, float, fRec46[2])
	DeclareVarInst(struct, "float", fConst91)
	DeclareVarInst(struct, float, fRec45[3])
	DeclareVarInst(struct, "float", fConst92)
	DeclareVarInst(struct, float, fRec44[3])
	DeclareVarInst(struct, float, fRec43[3])
	DeclareVarInst(struct, float, fRec42[3])
	DeclareVarInst(struct, float, fRec41[3])
	DeclareVarInst(struct, float, fRec40[3])
	DeclareVarInst(struct, float, fRec39[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fRec50[2])
	DeclareVarInst(struct, "float", fConst93)
	DeclareVarInst(struct, "float", fConst94)
	DeclareVarInst(struct, "float", fConst95)
	DeclareVarInst(struct, "float", fConst96)
	DeclareVarInst(struct, "float", fConst97)
	DeclareVarInst(struct, "float", fConst98)
	DeclareVarInst(struct, "float", fConst99)
	DeclareVarInst(struct, float, fRec60[2])
	DeclareVarInst(struct, float, fRec59[3])
	DeclareVarInst(struct, float, fRec58[3])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, "float", fConst100)
	DeclareVarInst(struct, float, fRec57[2])
	DeclareVarInst(struct, "float", fConst101)
	DeclareVarInst(struct, float, fRec56[3])
	DeclareVarInst(struct, "float", fConst102)
	DeclareVarInst(struct, float, fRec55[3])
	DeclareVarInst(struct, float, fRec54[3])
	DeclareVarInst(struct, float, fRec53[3])
	DeclareVarInst(struct, float, fRec52[3])
	DeclareVarInst(struct, float, fRec51[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, float, fRec61[2])
	DeclareVarInst(struct, "float", fConst103)
	DeclareVarInst(struct, "float", fConst104)
	DeclareVarInst(struct, "float", fConst105)
	DeclareVarInst(struct, "float", fConst106)
	DeclareVarInst(struct, "float", fConst107)
	DeclareVarInst(struct, "float", fConst108)
	DeclareVarInst(struct, "float", fConst109)
	DeclareVarInst(struct, float, fRec70[2])
	DeclareVarInst(struct, float, fRec69[3])
	DeclareVarInst(struct, float, fRec68[3])
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, "float", fConst110)
	DeclareVarInst(struct, float, fRec67[2])
	DeclareVarInst(struct, "float", fConst111)
	DeclareVarInst(struct, float, fRec66[3])
	DeclareVarInst(struct, "float", fConst112)
	DeclareVarInst(struct, float, fRec65[3])
	DeclareVarInst(struct, float, fRec64[3])
	DeclareVarInst(struct, float, fRec63[3])
	DeclareVarInst(struct, float, fRec62[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fRec71[2])
	DeclareVarInst(struct, "float", fConst113)
	DeclareVarInst(struct, "float", fConst114)
	DeclareVarInst(struct, "float", fConst115)
	DeclareVarInst(struct, "float", fConst116)
	DeclareVarInst(struct, "float", fConst117)
	DeclareVarInst(struct, "float", fConst118)
	DeclareVarInst(struct, "float", fConst119)
	DeclareVarInst(struct, float, fRec79[2])
	DeclareVarInst(struct, float, fRec78[3])
	DeclareVarInst(struct, float, fRec77[3])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, "float", fConst120)
	DeclareVarInst(struct, float, fRec76[2])
	DeclareVarInst(struct, "float", fConst121)
	DeclareVarInst(struct, float, fRec75[3])
	DeclareVarInst(struct, "float", fConst122)
	DeclareVarInst(struct, float, fRec74[3])
	DeclareVarInst(struct, float, fRec73[3])
	DeclareVarInst(struct, float, fRec72[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fRec80[2])
	DeclareVarInst(struct, "float", fConst123)
	DeclareVarInst(struct, "float", fConst124)
	DeclareVarInst(struct, "float", fConst125)
	DeclareVarInst(struct, "float", fConst126)
	DeclareVarInst(struct, "float", fConst127)
	DeclareVarInst(struct, "float", fConst128)
	DeclareVarInst(struct, "float", fConst129)
	DeclareVarInst(struct, float, fRec87[2])
	DeclareVarInst(struct, float, fRec86[3])
	DeclareVarInst(struct, float, fRec85[3])
	DeclareVarInst(struct, float, fVec7[2])
	DeclareVarInst(struct, "float", fConst130)
	DeclareVarInst(struct, float, fRec84[2])
	DeclareVarInst(struct, "float", fConst131)
	DeclareVarInst(struct, float, fRec83[3])
	DeclareVarInst(struct, "float", fConst132)
	DeclareVarInst(struct, float, fRec82[3])
	DeclareVarInst(struct, float, fRec81[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, float, fRec88[2])
	DeclareVarInst(struct, "float", fConst133)
	DeclareVarInst(struct, "float", fConst134)
	DeclareVarInst(struct, "float", fConst135)
	DeclareVarInst(struct, "float", fConst136)
	DeclareVarInst(struct, "float", fConst137)
	DeclareVarInst(struct, "float", fConst138)
	DeclareVarInst(struct, float, fRec94[2])
	DeclareVarInst(struct, float, fRec93[3])
	DeclareVarInst(struct, float, fRec92[3])
	DeclareVarInst(struct, float, fVec8[2])
	DeclareVarInst(struct, "float", fConst139)
	DeclareVarInst(struct, float, fRec91[2])
	DeclareVarInst(struct, "float", fConst140)
	DeclareVarInst(struct, float, fRec90[3])
	DeclareVarInst(struct, "float", fConst141)
	DeclareVarInst(struct, float, fRec89[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec95[2])
	DeclareVarInst(struct, float, fRec98[2])
	DeclareVarInst(struct, float, fRec97[3])
	DeclareVarInst(struct, float, fRec96[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, float, fRec99[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, FunCallInst("tanf", BinopInst("/", Float(31415.9258f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(0.618034005f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst3)))
	StoreVarInst(struct, fConst5, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst1))))
	StoreVarInst(struct, fConst6, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst5))))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(1.61803401f)), LoadVarInst(struct, fConst1)), Float(1.0f))))
	StoreVarInst(struct, fConst8, BinopInst("+", LoadVarInst(struct, fConst2), Float(1.0f)))
	StoreVarInst(struct, fConst9, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst2)), LoadVarInst(struct, fConst8))))
	StoreVarInst(struct, fConst10, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst8)))
	StoreVarInst(struct, fConst11, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fConst12, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst5))))
	StoreVarInst(struct, fConst13, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-1.61803401f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst14, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-0.618034005f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst15, FunCallInst("tanf", BinopInst("/", Float(122.71846f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst16, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst15)))
	StoreVarInst(struct, fConst17, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(1.61803401f)), LoadVarInst(struct, fConst15)), Float(1.0f))))
	StoreVarInst(struct, fConst18, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(-1.61803401f)), LoadVarInst(struct, fConst15)), Float(1.0f)))
	StoreVarInst(struct, fConst19, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst15))))
	StoreVarInst(struct, fConst20, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst19))))
	StoreVarInst(struct, fConst21, FunCallInst("tanf", BinopInst("/", Float(245.43692f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst22, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst21)))
	StoreVarInst(struct, fConst23, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f))))
	StoreVarInst(struct, fConst24, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst25, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst21))))
	StoreVarInst(struct, fConst26, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst25))))
	StoreVarInst(struct, fConst27, FunCallInst("tanf", BinopInst("/", Float(490.87384f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst28, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst27)))
	StoreVarInst(struct, fConst29, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(1.61803401f)), LoadVarInst(struct, fConst27)), Float(1.0f))))
	StoreVarInst(struct, fConst30, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(-1.61803401f)), LoadVarInst(struct, fConst27)), Float(1.0f)))
	StoreVarInst(struct, fConst31, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst32, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst31))))
	StoreVarInst(struct, fConst33, FunCallInst("tanf", BinopInst("/", Float(981.747681f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst34, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst33)))
	StoreVarInst(struct, fConst35, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(1.61803401f)), LoadVarInst(struct, fConst33)), Float(1.0f))))
	StoreVarInst(struct, fConst36, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(-1.61803401f)), LoadVarInst(struct, fConst33)), Float(1.0f)))
	StoreVarInst(struct, fConst37, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst33))))
	StoreVarInst(struct, fConst38, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst37))))
	StoreVarInst(struct, fConst39, FunCallInst("tanf", BinopInst("/", Float(1963.49536f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst40, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst39)))
	StoreVarInst(struct, fConst41, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(1.61803401f)), LoadVarInst(struct, fConst39)), Float(1.0f))))
	StoreVarInst(struct, fConst42, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(-1.61803401f)), LoadVarInst(struct, fConst39)), Float(1.0f)))
	StoreVarInst(struct, fConst43, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst39))))
	StoreVarInst(struct, fConst44, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst43))))
	StoreVarInst(struct, fConst45, FunCallInst("tanf", BinopInst("/", Float(3926.99072f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst46, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst45)))
	StoreVarInst(struct, fConst47, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(1.61803401f)), LoadVarInst(struct, fConst45)), Float(1.0f))))
	StoreVarInst(struct, fConst48, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(-1.61803401f)), LoadVarInst(struct, fConst45)), Float(1.0f)))
	StoreVarInst(struct, fConst49, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst45))))
	StoreVarInst(struct, fConst50, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst49))))
	StoreVarInst(struct, fConst51, FunCallInst("tanf", BinopInst("/", Float(7853.98145f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst52, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst51)))
	StoreVarInst(struct, fConst53, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(1.61803401f)), LoadVarInst(struct, fConst51)), Float(1.0f))))
	StoreVarInst(struct, fConst54, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(-1.61803401f)), LoadVarInst(struct, fConst51)), Float(1.0f)))
	StoreVarInst(struct, fConst55, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst51))))
	StoreVarInst(struct, fConst56, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst57, FunCallInst("tanf", BinopInst("/", Float(15707.9629f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst58, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst57)))
	StoreVarInst(struct, fConst59, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f))))
	StoreVarInst(struct, fConst60, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst61, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst57))))
	StoreVarInst(struct, fConst62, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst61))))
	StoreVarInst(struct, fConst63, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(0.618034005f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst64, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst63)))
	StoreVarInst(struct, fConst65, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst61))))
	StoreVarInst(struct, fConst66, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f))))
	StoreVarInst(struct, fConst67, BinopInst("+", LoadVarInst(struct, fConst58), Float(1.0f)))
	StoreVarInst(struct, fConst68, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst58)), LoadVarInst(struct, fConst67))))
	StoreVarInst(struct, fConst69, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(struct, fConst67))))
	StoreVarInst(struct, fConst70, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst58)))
	StoreVarInst(struct, fConst71, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst72, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-0.618034005f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst73, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(0.618034005f)), LoadVarInst(struct, fConst51)), Float(1.0f)))
	StoreVarInst(struct, fConst74, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst73)))
	StoreVarInst(struct, fConst75, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst76, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(1.61803401f)), LoadVarInst(struct, fConst51)), Float(1.0f))))
	StoreVarInst(struct, fConst77, BinopInst("+", LoadVarInst(struct, fConst52), Float(1.0f)))
	StoreVarInst(struct, fConst78, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst52)), LoadVarInst(struct, fConst77))))
	StoreVarInst(struct, fConst79, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst63), LoadVarInst(struct, fConst77))))
	StoreVarInst(struct, fConst80, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst52)))
	StoreVarInst(struct, fConst81, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(-1.61803401f)), LoadVarInst(struct, fConst51)), Float(1.0f)))
	StoreVarInst(struct, fConst82, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst52), Float(-0.618034005f)), LoadVarInst(struct, fConst51)), Float(1.0f)))
	StoreVarInst(struct, fConst83, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(0.618034005f)), LoadVarInst(struct, fConst45)), Float(1.0f)))
	StoreVarInst(struct, fConst84, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst83)))
	StoreVarInst(struct, fConst85, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst49))))
	StoreVarInst(struct, fConst86, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(1.61803401f)), LoadVarInst(struct, fConst45)), Float(1.0f))))
	StoreVarInst(struct, fConst87, BinopInst("+", LoadVarInst(struct, fConst46), Float(1.0f)))
	StoreVarInst(struct, fConst88, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst46)), LoadVarInst(struct, fConst87))))
	StoreVarInst(struct, fConst89, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst73), LoadVarInst(struct, fConst87))))
	StoreVarInst(struct, fConst90, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst46)))
	StoreVarInst(struct, fConst91, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(-1.61803401f)), LoadVarInst(struct, fConst45)), Float(1.0f)))
	StoreVarInst(struct, fConst92, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst46), Float(-0.618034005f)), LoadVarInst(struct, fConst45)), Float(1.0f)))
	StoreVarInst(struct, fConst93, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(0.618034005f)), LoadVarInst(struct, fConst39)), Float(1.0f)))
	StoreVarInst(struct, fConst94, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst93)))
	StoreVarInst(struct, fConst95, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst43))))
	StoreVarInst(struct, fConst96, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(1.61803401f)), LoadVarInst(struct, fConst39)), Float(1.0f))))
	StoreVarInst(struct, fConst97, BinopInst("+", LoadVarInst(struct, fConst40), Float(1.0f)))
	StoreVarInst(struct, fConst98, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst40)), LoadVarInst(struct, fConst97))))
	StoreVarInst(struct, fConst99, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fConst83))))
	StoreVarInst(struct, fConst100, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst40)))
	StoreVarInst(struct, fConst101, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(-1.61803401f)), LoadVarInst(struct, fConst39)), Float(1.0f)))
	StoreVarInst(struct, fConst102, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst40), Float(-0.618034005f)), LoadVarInst(struct, fConst39)), Float(1.0f)))
	StoreVarInst(struct, fConst103, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(0.618034005f)), LoadVarInst(struct, fConst33)), Float(1.0f)))
	StoreVarInst(struct, fConst104, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst103)))
	StoreVarInst(struct, fConst105, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst37))))
	StoreVarInst(struct, fConst106, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(1.61803401f)), LoadVarInst(struct, fConst33)), Float(1.0f))))
	StoreVarInst(struct, fConst107, BinopInst("+", LoadVarInst(struct, fConst34), Float(1.0f)))
	StoreVarInst(struct, fConst108, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst34)), LoadVarInst(struct, fConst107))))
	StoreVarInst(struct, fConst109, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst93), LoadVarInst(struct, fConst107))))
	StoreVarInst(struct, fConst110, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst34)))
	StoreVarInst(struct, fConst111, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(-1.61803401f)), LoadVarInst(struct, fConst33)), Float(1.0f)))
	StoreVarInst(struct, fConst112, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst34), Float(-0.618034005f)), LoadVarInst(struct, fConst33)), Float(1.0f)))
	StoreVarInst(struct, fConst113, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(0.618034005f)), LoadVarInst(struct, fConst27)), Float(1.0f)))
	StoreVarInst(struct, fConst114, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst113)))
	StoreVarInst(struct, fConst115, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst31))))
	StoreVarInst(struct, fConst116, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(1.61803401f)), LoadVarInst(struct, fConst27)), Float(1.0f))))
	StoreVarInst(struct, fConst117, BinopInst("+", LoadVarInst(struct, fConst28), Float(1.0f)))
	StoreVarInst(struct, fConst118, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst28)), LoadVarInst(struct, fConst117))))
	StoreVarInst(struct, fConst119, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst103), LoadVarInst(struct, fConst117))))
	StoreVarInst(struct, fConst120, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst28)))
	StoreVarInst(struct, fConst121, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(-1.61803401f)), LoadVarInst(struct, fConst27)), Float(1.0f)))
	StoreVarInst(struct, fConst122, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst28), Float(-0.618034005f)), LoadVarInst(struct, fConst27)), Float(1.0f)))
	StoreVarInst(struct, fConst123, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(0.618034005f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst124, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst123)))
	StoreVarInst(struct, fConst125, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst25))))
	StoreVarInst(struct, fConst126, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f))))
	StoreVarInst(struct, fConst127, BinopInst("+", LoadVarInst(struct, fConst22), Float(1.0f)))
	StoreVarInst(struct, fConst128, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst22)), LoadVarInst(struct, fConst127))))
	StoreVarInst(struct, fConst129, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst127), LoadVarInst(struct, fConst113))))
	StoreVarInst(struct, fConst130, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst22)))
	StoreVarInst(struct, fConst131, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst132, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-0.618034005f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst133, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(0.618034005f)), LoadVarInst(struct, fConst15)), Float(1.0f))))
	StoreVarInst(struct, fConst134, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst19))))
	StoreVarInst(struct, fConst135, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(1.61803401f)), LoadVarInst(struct, fConst15)), Float(1.0f))))
	StoreVarInst(struct, fConst136, BinopInst("+", LoadVarInst(struct, fConst16), Float(1.0f)))
	StoreVarInst(struct, fConst137, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst16)), LoadVarInst(struct, fConst136))))
	StoreVarInst(struct, fConst138, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst123), LoadVarInst(struct, fConst136))))
	StoreVarInst(struct, fConst139, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst16)))
	StoreVarInst(struct, fConst140, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(-1.61803401f)), LoadVarInst(struct, fConst15)), Float(1.0f)))
	StoreVarInst(struct, fConst141, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst16), Float(-0.618034005f)), LoadVarInst(struct, fConst15)), Float(1.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(-10.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
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
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(3))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(3))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(3))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(3))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(3))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l19)], Float(0.0f))
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
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(3))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(3))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(3))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(3))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(3))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(3))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(3))
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
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(3))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(3))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(3))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(3))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(3))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(3))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(3))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(3))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(3))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(3))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(3))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(3))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(3))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(2))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(2))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(3))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(3))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(2))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec57[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(3))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec56[LoadVarInst(loop, l60)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(3))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(3))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(3))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(3))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l64)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l65, Int32(0))
		BinopInst("<", LoadVarInst(loop, l65), Int32(3))
		StoreVarInst(loop, l65, BinopInst("+", LoadVarInst(loop, l65), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l65)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l66, Int32(0))
		BinopInst("<", LoadVarInst(loop, l66), Int32(2))
		StoreVarInst(loop, l66, BinopInst("+", LoadVarInst(loop, l66), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l66)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l67, Int32(0))
		BinopInst("<", LoadVarInst(loop, l67), Int32(2))
		StoreVarInst(loop, l67, BinopInst("+", LoadVarInst(loop, l67), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec70[LoadVarInst(loop, l67)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l68, Int32(0))
		BinopInst("<", LoadVarInst(loop, l68), Int32(3))
		StoreVarInst(loop, l68, BinopInst("+", LoadVarInst(loop, l68), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec69[LoadVarInst(loop, l68)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l69, Int32(0))
		BinopInst("<", LoadVarInst(loop, l69), Int32(3))
		StoreVarInst(loop, l69, BinopInst("+", LoadVarInst(loop, l69), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec68[LoadVarInst(loop, l69)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l70, Int32(0))
		BinopInst("<", LoadVarInst(loop, l70), Int32(2))
		StoreVarInst(loop, l70, BinopInst("+", LoadVarInst(loop, l70), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l70)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l71, Int32(0))
		BinopInst("<", LoadVarInst(loop, l71), Int32(2))
		StoreVarInst(loop, l71, BinopInst("+", LoadVarInst(loop, l71), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec67[LoadVarInst(loop, l71)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l72, Int32(0))
		BinopInst("<", LoadVarInst(loop, l72), Int32(3))
		StoreVarInst(loop, l72, BinopInst("+", LoadVarInst(loop, l72), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec66[LoadVarInst(loop, l72)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l73, Int32(0))
		BinopInst("<", LoadVarInst(loop, l73), Int32(3))
		StoreVarInst(loop, l73, BinopInst("+", LoadVarInst(loop, l73), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec65[LoadVarInst(loop, l73)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l74, Int32(0))
		BinopInst("<", LoadVarInst(loop, l74), Int32(3))
		StoreVarInst(loop, l74, BinopInst("+", LoadVarInst(loop, l74), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l74)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l75, Int32(0))
		BinopInst("<", LoadVarInst(loop, l75), Int32(3))
		StoreVarInst(loop, l75, BinopInst("+", LoadVarInst(loop, l75), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l75)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l76, Int32(0))
		BinopInst("<", LoadVarInst(loop, l76), Int32(3))
		StoreVarInst(loop, l76, BinopInst("+", LoadVarInst(loop, l76), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l76)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l77, Int32(0))
		BinopInst("<", LoadVarInst(loop, l77), Int32(2))
		StoreVarInst(loop, l77, BinopInst("+", LoadVarInst(loop, l77), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec71[LoadVarInst(loop, l77)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l78, Int32(0))
		BinopInst("<", LoadVarInst(loop, l78), Int32(2))
		StoreVarInst(loop, l78, BinopInst("+", LoadVarInst(loop, l78), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec79[LoadVarInst(loop, l78)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l79, Int32(0))
		BinopInst("<", LoadVarInst(loop, l79), Int32(3))
		StoreVarInst(loop, l79, BinopInst("+", LoadVarInst(loop, l79), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec78[LoadVarInst(loop, l79)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l80, Int32(0))
		BinopInst("<", LoadVarInst(loop, l80), Int32(3))
		StoreVarInst(loop, l80, BinopInst("+", LoadVarInst(loop, l80), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec77[LoadVarInst(loop, l80)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l81, Int32(0))
		BinopInst("<", LoadVarInst(loop, l81), Int32(2))
		StoreVarInst(loop, l81, BinopInst("+", LoadVarInst(loop, l81), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l81)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l82, Int32(0))
		BinopInst("<", LoadVarInst(loop, l82), Int32(2))
		StoreVarInst(loop, l82, BinopInst("+", LoadVarInst(loop, l82), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec76[LoadVarInst(loop, l82)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l83, Int32(0))
		BinopInst("<", LoadVarInst(loop, l83), Int32(3))
		StoreVarInst(loop, l83, BinopInst("+", LoadVarInst(loop, l83), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec75[LoadVarInst(loop, l83)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l84, Int32(0))
		BinopInst("<", LoadVarInst(loop, l84), Int32(3))
		StoreVarInst(loop, l84, BinopInst("+", LoadVarInst(loop, l84), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec74[LoadVarInst(loop, l84)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l85, Int32(0))
		BinopInst("<", LoadVarInst(loop, l85), Int32(3))
		StoreVarInst(loop, l85, BinopInst("+", LoadVarInst(loop, l85), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec73[LoadVarInst(loop, l85)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l86, Int32(0))
		BinopInst("<", LoadVarInst(loop, l86), Int32(3))
		StoreVarInst(loop, l86, BinopInst("+", LoadVarInst(loop, l86), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec72[LoadVarInst(loop, l86)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l87, Int32(0))
		BinopInst("<", LoadVarInst(loop, l87), Int32(2))
		StoreVarInst(loop, l87, BinopInst("+", LoadVarInst(loop, l87), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec80[LoadVarInst(loop, l87)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l88, Int32(0))
		BinopInst("<", LoadVarInst(loop, l88), Int32(2))
		StoreVarInst(loop, l88, BinopInst("+", LoadVarInst(loop, l88), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec87[LoadVarInst(loop, l88)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l89, Int32(0))
		BinopInst("<", LoadVarInst(loop, l89), Int32(3))
		StoreVarInst(loop, l89, BinopInst("+", LoadVarInst(loop, l89), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec86[LoadVarInst(loop, l89)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l90, Int32(0))
		BinopInst("<", LoadVarInst(loop, l90), Int32(3))
		StoreVarInst(loop, l90, BinopInst("+", LoadVarInst(loop, l90), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec85[LoadVarInst(loop, l90)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l91, Int32(0))
		BinopInst("<", LoadVarInst(loop, l91), Int32(2))
		StoreVarInst(loop, l91, BinopInst("+", LoadVarInst(loop, l91), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l91)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l92, Int32(0))
		BinopInst("<", LoadVarInst(loop, l92), Int32(2))
		StoreVarInst(loop, l92, BinopInst("+", LoadVarInst(loop, l92), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec84[LoadVarInst(loop, l92)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l93, Int32(0))
		BinopInst("<", LoadVarInst(loop, l93), Int32(3))
		StoreVarInst(loop, l93, BinopInst("+", LoadVarInst(loop, l93), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec83[LoadVarInst(loop, l93)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l94, Int32(0))
		BinopInst("<", LoadVarInst(loop, l94), Int32(3))
		StoreVarInst(loop, l94, BinopInst("+", LoadVarInst(loop, l94), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec82[LoadVarInst(loop, l94)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l95, Int32(0))
		BinopInst("<", LoadVarInst(loop, l95), Int32(3))
		StoreVarInst(loop, l95, BinopInst("+", LoadVarInst(loop, l95), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec81[LoadVarInst(loop, l95)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l96, Int32(0))
		BinopInst("<", LoadVarInst(loop, l96), Int32(2))
		StoreVarInst(loop, l96, BinopInst("+", LoadVarInst(loop, l96), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec88[LoadVarInst(loop, l96)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l97, Int32(0))
		BinopInst("<", LoadVarInst(loop, l97), Int32(2))
		StoreVarInst(loop, l97, BinopInst("+", LoadVarInst(loop, l97), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec94[LoadVarInst(loop, l97)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l98, Int32(0))
		BinopInst("<", LoadVarInst(loop, l98), Int32(3))
		StoreVarInst(loop, l98, BinopInst("+", LoadVarInst(loop, l98), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec93[LoadVarInst(loop, l98)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l99, Int32(0))
		BinopInst("<", LoadVarInst(loop, l99), Int32(3))
		StoreVarInst(loop, l99, BinopInst("+", LoadVarInst(loop, l99), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec92[LoadVarInst(loop, l99)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l100, Int32(0))
		BinopInst("<", LoadVarInst(loop, l100), Int32(2))
		StoreVarInst(loop, l100, BinopInst("+", LoadVarInst(loop, l100), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l100)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l101, Int32(0))
		BinopInst("<", LoadVarInst(loop, l101), Int32(2))
		StoreVarInst(loop, l101, BinopInst("+", LoadVarInst(loop, l101), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec91[LoadVarInst(loop, l101)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l102, Int32(0))
		BinopInst("<", LoadVarInst(loop, l102), Int32(3))
		StoreVarInst(loop, l102, BinopInst("+", LoadVarInst(loop, l102), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l102)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l103, Int32(0))
		BinopInst("<", LoadVarInst(loop, l103), Int32(3))
		StoreVarInst(loop, l103, BinopInst("+", LoadVarInst(loop, l103), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l103)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l104, Int32(0))
		BinopInst("<", LoadVarInst(loop, l104), Int32(2))
		StoreVarInst(loop, l104, BinopInst("+", LoadVarInst(loop, l104), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec95[LoadVarInst(loop, l104)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l105, Int32(0))
		BinopInst("<", LoadVarInst(loop, l105), Int32(2))
		StoreVarInst(loop, l105, BinopInst("+", LoadVarInst(loop, l105), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec98[LoadVarInst(loop, l105)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l106, Int32(0))
		BinopInst("<", LoadVarInst(loop, l106), Int32(3))
		StoreVarInst(loop, l106, BinopInst("+", LoadVarInst(loop, l106), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec97[LoadVarInst(loop, l106)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l107, Int32(0))
		BinopInst("<", LoadVarInst(loop, l107), Int32(3))
		StoreVarInst(loop, l107, BinopInst("+", LoadVarInst(loop, l107), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec96[LoadVarInst(loop, l107)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l108, Int32(0))
		BinopInst("<", LoadVarInst(loop, l108), Int32(2))
		StoreVarInst(loop, l108, BinopInst("+", LoadVarInst(loop, l108), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec99[LoadVarInst(loop, l108)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider0))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider1))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider2))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider3))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider4))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider5))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider6))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider7))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider8))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider9))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fTemp1))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst10), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(struct, fConst11), LoadVarInst(struct, fVec0[Int32(1)]))))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec10[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst13), LoadVarInst(struct, fRec9[Int32(2)]))))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec9[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(struct, fRec9[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec9[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst14), LoadVarInst(struct, fRec8[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec7[Int32(1)])))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec8[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec8[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec7[Int32(2)])), LoadVarInst(stack, fTemp2)))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec6[Int32(1)])))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec7[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec7[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec6[Int32(2)])), LoadVarInst(stack, fTemp3)))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec5[Int32(1)])))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec6[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec6[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec5[Int32(2)])), LoadVarInst(stack, fTemp4)))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec4[Int32(1)])))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec5[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec5[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec4[Int32(2)])), LoadVarInst(stack, fTemp5)))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec3[Int32(1)])))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec4[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec4[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec3[Int32(2)])), LoadVarInst(stack, fTemp6)))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec2[Int32(1)])))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec3[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp6), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec3[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec2[Int32(2)])), LoadVarInst(stack, fTemp7)))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec1[Int32(1)])))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec2[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp7), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec2[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec1[Int32(2)])), LoadVarInst(stack, fTemp8)))))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec0[Int32(1)])))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec1[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", LoadVarInst(stack, fTemp8), BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec1[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst59), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst60), LoadVarInst(struct, fRec0[Int32(2)])), LoadVarInst(stack, fTemp9)))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec11[Int32(1)]))))
			StoreVarInst(struct, fRec24[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst10), BinopInst("+", LoadVarInst(stack, fTemp1), LoadVarInst(struct, fVec0[Int32(1)])))))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec24[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst13), LoadVarInst(struct, fRec23[Int32(2)]))))))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", LoadVarInst(struct, fRec23[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec23[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec23[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst14), LoadVarInst(struct, fRec22[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(struct, fRec22[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec22[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec22[Int32(1)])))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp10))
			StoreVarInst(struct, fRec21[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst68), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst69), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst58), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(struct, fConst70), LoadVarInst(struct, fVec1[Int32(1)]))))))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec21[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst66), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst71), LoadVarInst(struct, fRec20[Int32(2)]))))))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst66), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(struct, fRec20[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(struct, fRec20[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(struct, fRec20[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst64), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fRec19[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec18[Int32(1)])))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst64), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(struct, fRec19[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(struct, fRec19[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp11), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec18[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec17[Int32(1)])))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec18[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp11), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec18[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp12), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec17[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec16[Int32(1)])))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec17[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp12), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec17[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp13), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec16[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec15[Int32(1)])))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec16[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp13), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec16[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp14), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec15[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec14[Int32(1)])))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec15[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp14), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec15[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec14[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec13[Int32(1)])))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec14[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec14[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp16), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec13[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec12[Int32(1)])))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec13[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp16), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec13[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", LoadVarInst(stack, fTemp17), BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec12[Int32(2)]))))))
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec25[Int32(1)]))))
			StoreVarInst(struct, fRec37[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst68), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst69), BinopInst("+", LoadVarInst(stack, fTemp10), LoadVarInst(struct, fVec1[Int32(1)])))))
			StoreVarInst(struct, fRec36[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec37[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst66), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec36[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst71), LoadVarInst(struct, fRec36[Int32(2)]))))))
			StoreVarInst(struct, fRec35[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst66), BinopInst("+", LoadVarInst(struct, fRec36[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec36[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst64), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fRec35[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(struct, fRec35[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec35[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec35[Int32(1)])))))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp18))
			StoreVarInst(struct, fRec34[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec34[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst52), LoadVarInst(stack, fTemp18)), BinopInst("*", LoadVarInst(struct, fConst80), LoadVarInst(struct, fVec2[Int32(1)]))))))
			StoreVarInst(struct, fRec33[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec34[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst76), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec33[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec33[Int32(2)]))))))
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst76), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst55), LoadVarInst(struct, fRec33[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst75), LoadVarInst(struct, fRec33[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst55), LoadVarInst(struct, fRec33[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec32[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec32[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec31[Int32(1)])))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst75), LoadVarInst(struct, fRec32[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst55), LoadVarInst(struct, fRec32[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst55), LoadVarInst(struct, fRec32[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp19), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec31[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec30[Int32(1)])))
			StoreVarInst(struct, fRec30[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec31[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp19), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec31[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp20), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec30[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec29[Int32(1)])))
			StoreVarInst(struct, fRec29[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec30[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp20), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec30[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp21), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec29[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec28[Int32(1)])))
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec29[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp21), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec29[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp22), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec28[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec27[Int32(1)])))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec28[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp22), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec28[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp23), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec27[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec26[Int32(1)])))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec27[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp23), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec27[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp24), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec26[Int32(2)]))))))
			StoreVarInst(struct, fRec38[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec38[Int32(1)]))))
			StoreVarInst(struct, fRec49[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec49[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", LoadVarInst(stack, fTemp18), LoadVarInst(struct, fVec2[Int32(1)])))))
			StoreVarInst(struct, fRec48[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec49[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst76), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec48[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec48[Int32(2)]))))))
			StoreVarInst(struct, fRec47[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst76), BinopInst("+", LoadVarInst(struct, fRec48[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec48[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec48[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec47[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec47[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(struct, fRec47[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec47[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec47[Int32(1)])))))
			StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp25))
			StoreVarInst(struct, fRec46[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst88), LoadVarInst(struct, fRec46[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst46), LoadVarInst(stack, fTemp25)), BinopInst("*", LoadVarInst(struct, fConst90), LoadVarInst(struct, fVec3[Int32(1)]))))))
			StoreVarInst(struct, fRec45[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec46[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst86), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec45[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec45[Int32(2)]))))))
			StoreVarInst(struct, fRec44[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst86), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec45[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(struct, fRec45[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec45[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec44[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec44[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec43[Int32(1)])))
			StoreVarInst(struct, fRec43[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(struct, fRec44[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec44[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec44[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp26), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec43[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec42[Int32(1)])))
			StoreVarInst(struct, fRec42[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec43[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp26), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec43[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec42[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec41[Int32(1)])))
			StoreVarInst(struct, fRec41[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec42[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec42[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec41[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec40[Int32(1)])))
			StoreVarInst(struct, fRec40[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec41[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec41[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp29), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec40[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec39[Int32(1)])))
			StoreVarInst(struct, fRec39[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec40[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp29), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec40[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec39[Int32(2)]))))))
			StoreVarInst(struct, fRec50[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec50[Int32(1)]))))
			StoreVarInst(struct, fRec60[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst88), LoadVarInst(struct, fRec60[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fVec3[Int32(1)])))))
			StoreVarInst(struct, fRec59[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec60[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst86), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec59[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec59[Int32(2)]))))))
			StoreVarInst(struct, fRec58[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst86), BinopInst("+", LoadVarInst(struct, fRec59[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec59[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec59[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec58[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec58[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(struct, fRec58[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec58[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec58[Int32(1)])))))
			StoreVarInst(struct, fVec4[Int32(0)], LoadVarInst(stack, fTemp31))
			StoreVarInst(struct, fRec57[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec57[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst40), LoadVarInst(stack, fTemp31)), BinopInst("*", LoadVarInst(struct, fConst100), LoadVarInst(struct, fVec4[Int32(1)]))))))
			StoreVarInst(struct, fRec56[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec57[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst96), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec56[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec56[Int32(2)]))))))
			StoreVarInst(struct, fRec55[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst96), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst43), LoadVarInst(struct, fRec56[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst95), LoadVarInst(struct, fRec56[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst43), LoadVarInst(struct, fRec56[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec55[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec55[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp32, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec54[Int32(1)])))
			StoreVarInst(struct, fRec54[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst95), LoadVarInst(struct, fRec55[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst43), LoadVarInst(struct, fRec55[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst43), LoadVarInst(struct, fRec55[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp32), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec54[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec53[Int32(1)])))
			StoreVarInst(struct, fRec53[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec54[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp32), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec54[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp33), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec53[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp34, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec52[Int32(1)])))
			StoreVarInst(struct, fRec52[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec53[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp33), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec53[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp34), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec52[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec51[Int32(1)])))
			StoreVarInst(struct, fRec51[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec52[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp34), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec52[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp35), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec51[Int32(2)]))))))
			StoreVarInst(struct, fRec61[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec61[Int32(1)]))))
			StoreVarInst(struct, fRec70[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec70[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", LoadVarInst(stack, fTemp31), LoadVarInst(struct, fVec4[Int32(1)])))))
			StoreVarInst(struct, fRec69[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec70[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst96), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec69[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec69[Int32(2)]))))))
			StoreVarInst(struct, fRec68[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst96), BinopInst("+", LoadVarInst(struct, fRec69[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec69[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec69[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(struct, fRec68[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec68[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(struct, fRec68[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec68[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec68[Int32(1)])))))
			StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp36))
			StoreVarInst(struct, fRec67[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst108), LoadVarInst(struct, fRec67[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst34), LoadVarInst(stack, fTemp36)), BinopInst("*", LoadVarInst(struct, fConst110), LoadVarInst(struct, fVec5[Int32(1)]))))))
			StoreVarInst(struct, fRec66[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec67[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst106), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec66[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst111), LoadVarInst(struct, fRec66[Int32(2)]))))))
			StoreVarInst(struct, fRec65[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst106), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(struct, fRec66[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(struct, fRec66[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(struct, fRec66[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec65[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst112), LoadVarInst(struct, fRec65[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec64[Int32(1)])))
			StoreVarInst(struct, fRec64[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(struct, fRec65[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(struct, fRec65[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(struct, fRec65[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp37), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec64[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec63[Int32(1)])))
			StoreVarInst(struct, fRec63[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec64[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp37), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec64[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp38), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec63[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec62[Int32(1)])))
			StoreVarInst(struct, fRec62[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec63[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp38), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec63[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp39), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec62[Int32(2)]))))))
			StoreVarInst(struct, fRec71[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec71[Int32(1)]))))
			StoreVarInst(struct, fRec79[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst108), LoadVarInst(struct, fRec79[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", LoadVarInst(stack, fTemp36), LoadVarInst(struct, fVec5[Int32(1)])))))
			StoreVarInst(struct, fRec78[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec79[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst106), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec78[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst111), LoadVarInst(struct, fRec78[Int32(2)]))))))
			StoreVarInst(struct, fRec77[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst106), BinopInst("+", LoadVarInst(struct, fRec78[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec78[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec78[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec77[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst112), LoadVarInst(struct, fRec77[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("+", LoadVarInst(struct, fRec77[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec77[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec77[Int32(1)])))))
			StoreVarInst(struct, fVec6[Int32(0)], LoadVarInst(stack, fTemp40))
			StoreVarInst(struct, fRec76[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst118), LoadVarInst(struct, fRec76[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst119), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst28), LoadVarInst(stack, fTemp40)), BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fVec6[Int32(1)]))))))
			StoreVarInst(struct, fRec75[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec76[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst116), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec75[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec75[Int32(2)]))))))
			StoreVarInst(struct, fRec74[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst116), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fRec75[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst115), LoadVarInst(struct, fRec75[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fRec75[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst114), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec74[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst122), LoadVarInst(struct, fRec74[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec73[Int32(1)])))
			StoreVarInst(struct, fRec73[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst114), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst115), LoadVarInst(struct, fRec74[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fRec74[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fRec74[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec73[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec72[Int32(1)])))
			StoreVarInst(struct, fRec72[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec73[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec73[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp42), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec72[Int32(2)]))))))
			StoreVarInst(struct, fRec80[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec80[Int32(1)]))))
			StoreVarInst(struct, fRec87[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst118), LoadVarInst(struct, fRec87[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst119), BinopInst("+", LoadVarInst(stack, fTemp40), LoadVarInst(struct, fVec6[Int32(1)])))))
			StoreVarInst(struct, fRec86[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec87[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst116), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec86[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec86[Int32(2)]))))))
			StoreVarInst(struct, fRec85[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst116), BinopInst("+", LoadVarInst(struct, fRec86[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec86[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec86[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst114), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst32), LoadVarInst(struct, fRec85[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst122), LoadVarInst(struct, fRec85[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("+", LoadVarInst(struct, fRec85[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec85[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec85[Int32(1)])))))
			StoreVarInst(struct, fVec7[Int32(0)], LoadVarInst(stack, fTemp43))
			StoreVarInst(struct, fRec84[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst128), LoadVarInst(struct, fRec84[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst129), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst22), LoadVarInst(stack, fTemp43)), BinopInst("*", LoadVarInst(struct, fConst130), LoadVarInst(struct, fVec7[Int32(1)]))))))
			StoreVarInst(struct, fRec83[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec84[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst126), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec83[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst131), LoadVarInst(struct, fRec83[Int32(2)]))))))
			StoreVarInst(struct, fRec82[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst126), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(struct, fRec83[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst125), LoadVarInst(struct, fRec83[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(struct, fRec83[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec82[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst132), LoadVarInst(struct, fRec82[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp44, BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec81[Int32(1)])))
			StoreVarInst(struct, fRec81[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst125), LoadVarInst(struct, fRec82[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(struct, fRec82[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(struct, fRec82[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp44), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec81[Int32(2)]))))))
			StoreVarInst(struct, fRec88[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec88[Int32(1)]))))
			StoreVarInst(struct, fRec94[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst128), LoadVarInst(struct, fRec94[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst129), BinopInst("+", LoadVarInst(stack, fTemp43), LoadVarInst(struct, fVec7[Int32(1)])))))
			StoreVarInst(struct, fRec93[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec94[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst126), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec93[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst131), LoadVarInst(struct, fRec93[Int32(2)]))))))
			StoreVarInst(struct, fRec92[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst126), BinopInst("+", LoadVarInst(struct, fRec93[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec93[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec93[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec92[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst132), LoadVarInst(struct, fRec92[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("+", LoadVarInst(struct, fRec92[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec92[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec92[Int32(1)])))))
			StoreVarInst(struct, fVec8[Int32(0)], LoadVarInst(stack, fTemp45))
			StoreVarInst(struct, fRec91[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst137), LoadVarInst(struct, fRec91[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst138), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst16), LoadVarInst(stack, fTemp45)), BinopInst("*", LoadVarInst(struct, fConst139), LoadVarInst(struct, fVec8[Int32(1)]))))))
			StoreVarInst(struct, fRec90[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec91[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec90[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec90[Int32(2)]))))))
			StoreVarInst(struct, fRec89[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec90[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec90[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec90[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec89[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst141), LoadVarInst(struct, fRec89[Int32(2)]))))))
			StoreVarInst(struct, fRec95[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow9), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec95[Int32(1)]))))
			StoreVarInst(struct, fRec98[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst137), LoadVarInst(struct, fRec98[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst138), BinopInst("+", LoadVarInst(stack, fTemp45), LoadVarInst(struct, fVec8[Int32(1)])))))
			StoreVarInst(struct, fRec97[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec98[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec97[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec97[Int32(2)]))))))
			StoreVarInst(struct, fRec96[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(struct, fRec97[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec97[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec97[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst20), LoadVarInst(struct, fRec96[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst141), LoadVarInst(struct, fRec96[Int32(2)]))))))
			StoreVarInst(struct, fRec99[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec99[Int32(1)]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst59), BinopInst("+", LoadVarInst(stack, fTemp9), BinopInst("*", LoadVarInst(struct, fConst60), LoadVarInst(struct, fRec0[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec11[Int32(0)])))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", LoadVarInst(stack, fTemp17), BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec12[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec25[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec26[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(stack, fTemp24), BinopInst("*", LoadVarInst(struct, fConst48), LoadVarInst(struct, fRec26[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec38[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec39[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst41), BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec39[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec50[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec51[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst35), BinopInst("+", LoadVarInst(stack, fTemp35), BinopInst("*", LoadVarInst(struct, fConst36), LoadVarInst(struct, fRec51[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec61[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec62[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst29), BinopInst("+", LoadVarInst(stack, fTemp39), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec62[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec71[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec72[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst23), BinopInst("+", LoadVarInst(stack, fTemp42), BinopInst("*", LoadVarInst(struct, fConst24), LoadVarInst(struct, fRec72[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec80[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec81[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", LoadVarInst(stack, fTemp44), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec81[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec88[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec89[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec89[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec89[Int32(2)]))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec95[Int32(0)])))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec96[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec96[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec96[Int32(1)])))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec99[Int32(0)]))))))))))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(2)], LoadVarInst(struct, fRec23[Int32(1)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(2)], LoadVarInst(struct, fRec22[Int32(1)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(2)], LoadVarInst(struct, fRec20[Int32(1)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(2)], LoadVarInst(struct, fRec19[Int32(1)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(2)], LoadVarInst(struct, fRec18[Int32(1)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(2)], LoadVarInst(struct, fRec17[Int32(1)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(2)], LoadVarInst(struct, fRec16[Int32(1)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(2)], LoadVarInst(struct, fRec15[Int32(1)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(2)], LoadVarInst(struct, fRec13[Int32(1)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
			StoreVarInst(struct, fRec36[Int32(2)], LoadVarInst(struct, fRec36[Int32(1)]))
			StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
			StoreVarInst(struct, fRec35[Int32(2)], LoadVarInst(struct, fRec35[Int32(1)]))
			StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
			StoreVarInst(struct, fRec33[Int32(2)], LoadVarInst(struct, fRec33[Int32(1)]))
			StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(2)], LoadVarInst(struct, fRec32[Int32(1)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fRec31[Int32(2)], LoadVarInst(struct, fRec31[Int32(1)]))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(2)], LoadVarInst(struct, fRec30[Int32(1)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fRec29[Int32(2)], LoadVarInst(struct, fRec29[Int32(1)]))
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(2)], LoadVarInst(struct, fRec28[Int32(1)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(2)], LoadVarInst(struct, fRec27[Int32(1)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
			StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
			StoreVarInst(struct, fRec48[Int32(2)], LoadVarInst(struct, fRec48[Int32(1)]))
			StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
			StoreVarInst(struct, fRec47[Int32(2)], LoadVarInst(struct, fRec47[Int32(1)]))
			StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
			StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
			StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
			StoreVarInst(struct, fRec45[Int32(2)], LoadVarInst(struct, fRec45[Int32(1)]))
			StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
			StoreVarInst(struct, fRec44[Int32(2)], LoadVarInst(struct, fRec44[Int32(1)]))
			StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
			StoreVarInst(struct, fRec43[Int32(2)], LoadVarInst(struct, fRec43[Int32(1)]))
			StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
			StoreVarInst(struct, fRec42[Int32(2)], LoadVarInst(struct, fRec42[Int32(1)]))
			StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
			StoreVarInst(struct, fRec41[Int32(2)], LoadVarInst(struct, fRec41[Int32(1)]))
			StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
			StoreVarInst(struct, fRec40[Int32(2)], LoadVarInst(struct, fRec40[Int32(1)]))
			StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
			StoreVarInst(struct, fRec39[Int32(2)], LoadVarInst(struct, fRec39[Int32(1)]))
			StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
			StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
			StoreVarInst(struct, fRec60[Int32(1)], LoadVarInst(struct, fRec60[Int32(0)]))
			StoreVarInst(struct, fRec59[Int32(2)], LoadVarInst(struct, fRec59[Int32(1)]))
			StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
			StoreVarInst(struct, fRec58[Int32(2)], LoadVarInst(struct, fRec58[Int32(1)]))
			StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
			StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
			StoreVarInst(struct, fRec57[Int32(1)], LoadVarInst(struct, fRec57[Int32(0)]))
			StoreVarInst(struct, fRec56[Int32(2)], LoadVarInst(struct, fRec56[Int32(1)]))
			StoreVarInst(struct, fRec56[Int32(1)], LoadVarInst(struct, fRec56[Int32(0)]))
			StoreVarInst(struct, fRec55[Int32(2)], LoadVarInst(struct, fRec55[Int32(1)]))
			StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
			StoreVarInst(struct, fRec54[Int32(2)], LoadVarInst(struct, fRec54[Int32(1)]))
			StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
			StoreVarInst(struct, fRec53[Int32(2)], LoadVarInst(struct, fRec53[Int32(1)]))
			StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
			StoreVarInst(struct, fRec52[Int32(2)], LoadVarInst(struct, fRec52[Int32(1)]))
			StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
			StoreVarInst(struct, fRec51[Int32(2)], LoadVarInst(struct, fRec51[Int32(1)]))
			StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
			StoreVarInst(struct, fRec61[Int32(1)], LoadVarInst(struct, fRec61[Int32(0)]))
			StoreVarInst(struct, fRec70[Int32(1)], LoadVarInst(struct, fRec70[Int32(0)]))
			StoreVarInst(struct, fRec69[Int32(2)], LoadVarInst(struct, fRec69[Int32(1)]))
			StoreVarInst(struct, fRec69[Int32(1)], LoadVarInst(struct, fRec69[Int32(0)]))
			StoreVarInst(struct, fRec68[Int32(2)], LoadVarInst(struct, fRec68[Int32(1)]))
			StoreVarInst(struct, fRec68[Int32(1)], LoadVarInst(struct, fRec68[Int32(0)]))
			StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
			StoreVarInst(struct, fRec67[Int32(1)], LoadVarInst(struct, fRec67[Int32(0)]))
			StoreVarInst(struct, fRec66[Int32(2)], LoadVarInst(struct, fRec66[Int32(1)]))
			StoreVarInst(struct, fRec66[Int32(1)], LoadVarInst(struct, fRec66[Int32(0)]))
			StoreVarInst(struct, fRec65[Int32(2)], LoadVarInst(struct, fRec65[Int32(1)]))
			StoreVarInst(struct, fRec65[Int32(1)], LoadVarInst(struct, fRec65[Int32(0)]))
			StoreVarInst(struct, fRec64[Int32(2)], LoadVarInst(struct, fRec64[Int32(1)]))
			StoreVarInst(struct, fRec64[Int32(1)], LoadVarInst(struct, fRec64[Int32(0)]))
			StoreVarInst(struct, fRec63[Int32(2)], LoadVarInst(struct, fRec63[Int32(1)]))
			StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
			StoreVarInst(struct, fRec62[Int32(2)], LoadVarInst(struct, fRec62[Int32(1)]))
			StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
			StoreVarInst(struct, fRec71[Int32(1)], LoadVarInst(struct, fRec71[Int32(0)]))
			StoreVarInst(struct, fRec79[Int32(1)], LoadVarInst(struct, fRec79[Int32(0)]))
			StoreVarInst(struct, fRec78[Int32(2)], LoadVarInst(struct, fRec78[Int32(1)]))
			StoreVarInst(struct, fRec78[Int32(1)], LoadVarInst(struct, fRec78[Int32(0)]))
			StoreVarInst(struct, fRec77[Int32(2)], LoadVarInst(struct, fRec77[Int32(1)]))
			StoreVarInst(struct, fRec77[Int32(1)], LoadVarInst(struct, fRec77[Int32(0)]))
			StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
			StoreVarInst(struct, fRec76[Int32(1)], LoadVarInst(struct, fRec76[Int32(0)]))
			StoreVarInst(struct, fRec75[Int32(2)], LoadVarInst(struct, fRec75[Int32(1)]))
			StoreVarInst(struct, fRec75[Int32(1)], LoadVarInst(struct, fRec75[Int32(0)]))
			StoreVarInst(struct, fRec74[Int32(2)], LoadVarInst(struct, fRec74[Int32(1)]))
			StoreVarInst(struct, fRec74[Int32(1)], LoadVarInst(struct, fRec74[Int32(0)]))
			StoreVarInst(struct, fRec73[Int32(2)], LoadVarInst(struct, fRec73[Int32(1)]))
			StoreVarInst(struct, fRec73[Int32(1)], LoadVarInst(struct, fRec73[Int32(0)]))
			StoreVarInst(struct, fRec72[Int32(2)], LoadVarInst(struct, fRec72[Int32(1)]))
			StoreVarInst(struct, fRec72[Int32(1)], LoadVarInst(struct, fRec72[Int32(0)]))
			StoreVarInst(struct, fRec80[Int32(1)], LoadVarInst(struct, fRec80[Int32(0)]))
			StoreVarInst(struct, fRec87[Int32(1)], LoadVarInst(struct, fRec87[Int32(0)]))
			StoreVarInst(struct, fRec86[Int32(2)], LoadVarInst(struct, fRec86[Int32(1)]))
			StoreVarInst(struct, fRec86[Int32(1)], LoadVarInst(struct, fRec86[Int32(0)]))
			StoreVarInst(struct, fRec85[Int32(2)], LoadVarInst(struct, fRec85[Int32(1)]))
			StoreVarInst(struct, fRec85[Int32(1)], LoadVarInst(struct, fRec85[Int32(0)]))
			StoreVarInst(struct, fVec7[Int32(1)], LoadVarInst(struct, fVec7[Int32(0)]))
			StoreVarInst(struct, fRec84[Int32(1)], LoadVarInst(struct, fRec84[Int32(0)]))
			StoreVarInst(struct, fRec83[Int32(2)], LoadVarInst(struct, fRec83[Int32(1)]))
			StoreVarInst(struct, fRec83[Int32(1)], LoadVarInst(struct, fRec83[Int32(0)]))
			StoreVarInst(struct, fRec82[Int32(2)], LoadVarInst(struct, fRec82[Int32(1)]))
			StoreVarInst(struct, fRec82[Int32(1)], LoadVarInst(struct, fRec82[Int32(0)]))
			StoreVarInst(struct, fRec81[Int32(2)], LoadVarInst(struct, fRec81[Int32(1)]))
			StoreVarInst(struct, fRec81[Int32(1)], LoadVarInst(struct, fRec81[Int32(0)]))
			StoreVarInst(struct, fRec88[Int32(1)], LoadVarInst(struct, fRec88[Int32(0)]))
			StoreVarInst(struct, fRec94[Int32(1)], LoadVarInst(struct, fRec94[Int32(0)]))
			StoreVarInst(struct, fRec93[Int32(2)], LoadVarInst(struct, fRec93[Int32(1)]))
			StoreVarInst(struct, fRec93[Int32(1)], LoadVarInst(struct, fRec93[Int32(0)]))
			StoreVarInst(struct, fRec92[Int32(2)], LoadVarInst(struct, fRec92[Int32(1)]))
			StoreVarInst(struct, fRec92[Int32(1)], LoadVarInst(struct, fRec92[Int32(0)]))
			StoreVarInst(struct, fVec8[Int32(1)], LoadVarInst(struct, fVec8[Int32(0)]))
			StoreVarInst(struct, fRec91[Int32(1)], LoadVarInst(struct, fRec91[Int32(0)]))
			StoreVarInst(struct, fRec90[Int32(2)], LoadVarInst(struct, fRec90[Int32(1)]))
			StoreVarInst(struct, fRec90[Int32(1)], LoadVarInst(struct, fRec90[Int32(0)]))
			StoreVarInst(struct, fRec89[Int32(2)], LoadVarInst(struct, fRec89[Int32(1)]))
			StoreVarInst(struct, fRec89[Int32(1)], LoadVarInst(struct, fRec89[Int32(0)]))
			StoreVarInst(struct, fRec95[Int32(1)], LoadVarInst(struct, fRec95[Int32(0)]))
			StoreVarInst(struct, fRec98[Int32(1)], LoadVarInst(struct, fRec98[Int32(0)]))
			StoreVarInst(struct, fRec97[Int32(2)], LoadVarInst(struct, fRec97[Int32(1)]))
			StoreVarInst(struct, fRec97[Int32(1)], LoadVarInst(struct, fRec97[Int32(0)]))
			StoreVarInst(struct, fRec96[Int32(2)], LoadVarInst(struct, fRec96[Int32(1)]))
			StoreVarInst(struct, fRec96[Int32(1)], LoadVarInst(struct, fRec96[Int32(0)]))
			StoreVarInst(struct, fRec99[Int32(1)], LoadVarInst(struct, fRec99[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 1772 bytes
Heap size = 1776 bytes
Stack size in compute = 60 bytes

