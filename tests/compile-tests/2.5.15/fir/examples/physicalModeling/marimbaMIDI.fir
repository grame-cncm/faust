======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations ==========

BlockInst 
	DeclareVarInst(static, float, fmydspSIG0Wave0[250], {1.0f,0.776724994f,0.625723004f,0.855223f,0.760159016f,0.69837302f,0.768010974f,0.64112699f,0.244034007f,0.707754016f,0.634012997f,0.247527003f,0.660848975f,0.450396001f,0.567782998f,0.106361002f,0.716813982f,0.663919985f,0.291207999f,0.310598999f,0.801495016f,0.635291994f,0.307435006f,0.874123991f,0.497667998f,0.487087995f,0.459114999f,0.733455002f,0.541818023f,0.441318005f,0.313919991f,0.40309f,0.685352981f,0.603139997f,0.400552005f,0.453511f,0.634386003f,0.291547f,0.131604999f,0.368506998f,0.839906991f,0.602159977f,0.288296014f,0.579670012f,0.0242493004f,0.262746006f,0.368588001f,0.890284002f,0.408962995f,0.556071997f,0.884427011f,0.832109988f,0.612015009f,0.757175982f,0.919476986f,1.0f,0.827962995f,0.89240998f,0.0357408002f,0.480789006f,0.75287199f,0.0546301007f,0.235936999f,0.362937987f,0.444471985f,0.101751f,0.703418016f,0.453135997f,0.316628993f,0.490393996f,0.982508004f,0.551621974f,0.602008998f,0.666957021f,0.776830018f,0.905662f,0.0987197012f,0.402967989f,0.829451978f,0.307644993f,0.640479982f,0.983971f,0.584204972f,0.650364995f,0.334446996f,0.583570004f,0.540190995f,0.672533989f,0.245711997f,0.687298f,0.883058012f,0.792949975f,0.600619018f,0.572682023f,0.122612f,0.388247997f,0.290657997f,0.380255014f,0.290966988f,0.567818999f,0.0737721026f,0.42098999f,0.0786577985f,0.393994987f,0.268983006f,0.260614008f,0.494085997f,0.238025993f,0.0987823978f,0.277879f,0.440562993f,0.0770211965f,0.450590998f,0.128137007f,0.0368275009f,0.128699005f,0.329605013f,0.374511987f,0.363590002f,0.272594005f,0.379052013f,0.305240989f,0.0741128996f,0.34572801f,0.299349993f,0.221284002f,0.0261390992f,0.293202013f,0.361885011f,0.114330001f,0.239004999f,0.434156001f,0.329582989f,0.219459996f,0.284175009f,0.198554993f,0.431975991f,0.302985013f,1.0f,0.146220997f,0.140700996f,0.264243007f,0.185996994f,0.426322013f,0.304780006f,0.343989998f,0.195429996f,0.386954993f,0.187600002f,0.172812f,0.0434115008f,0.303761005f,0.0694539994f,0.453943014f,0.832450986f,0.317817003f,0.940600991f,1.0f,0.180657998f,0.737921f,0.832297027f,0.402352005f,0.126785994f,0.594398022f,0.485455006f,0.324470013f,0.365101993f,0.777921975f,0.588271976f,0.401353002f,0.610734999f,0.158693001f,0.0746072009f,0.825098991f,0.925459027f,0.65377003f,0.260791987f,0.719384015f,0.559907973f,0.372590005f,0.360035002f,0.622938991f,0.210271001f,0.444595009f,0.311286002f,0.464309007f,0.557231009f,0.524079978f,0.0701055974f,0.320749015f,0.194460005f,0.727608979f,0.522062004f,0.394003987f,0.235035002f,0.395646006f,0.494796008f,0.51731801f,0.109751999f,0.69284898f,0.00632009003f,0.0207582992f,0.00306107011f,0.0637191013f,0.0816610008f,0.0351100005f,0.127813995f,0.202294007f,0.0764145032f,0.263126999f,0.400198996f,0.267277986f,0.633385003f,1.0f,0.73990202f,0.413762987f,0.418110013f,0.612715006f,0.67237401f,0.339673996f,0.211720005f,0.459645003f,0.102499999f,0.325890005f,0.148154005f,0.265442014f,0.0974304974f,0.286437988f,0.275213003f,0.109111004f,0.575088978f,0.370283008f,0.29411f,0.259826005f,0.0648718998f,0.583418012f,0.282662988f,0.182004005f,0.117421001f,0.417726994f,0.169650003f,0.24853f,0.122818999f,0.185486004f,0.0433618017f,0.373849005f,0.25276801f,0.195103005f,0.0927835032f,0.166543007f})
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fmydspSIG0Wave0_idx)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
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
					StoreVarInst(stack, rate, Int32(0))
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
	StoreVarInst(struct, fmydspSIG0Wave0_idx, Int32(0))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 6
Store = 3
Binop = 4
Numbers = 4
Declare = 1
Cast = 0
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], LoadVarInst(static, fmydspSIG0Wave0[LoadVarInst(struct, fmydspSIG0Wave0_idx)]))
		StoreVarInst(struct, fmydspSIG0Wave0_idx, BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(struct, fmydspSIG0Wave0_idx)), Int32(250)))
		EndBlock
	EndForLoop

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("marimba")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("midi")
	AddMetaDeclareInst(fHslider1, "0", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddHorizontalSlider("freq", fHslider1, 440.0f, 50.0f, 1000.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider2, "2", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("gain", fHslider2, 1.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("otherParams")
	AddMetaDeclareInst(fEntry0, "0", "")
	AddMetaDeclareInst(fEntry0, "midi", "ctrl 1")
	AddNumEntry"strikePosition", fEntry0, 0.0f, 0.0f, 4.0f, 1.0f)
	AddMetaDeclareInst(fHslider3, "1", "")
	AddMetaDeclareInst(fHslider3, "midi", "ctrl 1")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("strikeCutOff", fHslider3, 6500.0f, 20.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddHorizontalSlider("outGain", fHslider0, 0.800000012f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider4, "2", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("strikeSharpness", fHslider4, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(fButton0, "3", "")
	AddButtonInst("gate"fButton0)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst(static, float, ftbl0mydspSIG0[250])
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
	DeclareVarInst(struct, int, iRec2[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[2048])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, int, iRec14[2])
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, float, fRec13[3])
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, float, fRec11[3])
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, float, fRec16[3])
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, float, fRec18[3])
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, float, fRec19[3])
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, float, fRec21[3])
	DeclareVarInst(struct, "float", fConst43)
	DeclareVarInst(struct, "float", fConst44)
	DeclareVarInst(struct, "float", fConst45)
	DeclareVarInst(struct, "float", fConst46)
	DeclareVarInst(struct, float, fRec22[3])
	DeclareVarInst(struct, "float", fConst47)
	DeclareVarInst(struct, "float", fConst48)
	DeclareVarInst(struct, "float", fConst49)
	DeclareVarInst(struct, "float", fConst50)
	DeclareVarInst(struct, float, fRec23[3])
	DeclareVarInst(struct, "float", fConst51)
	DeclareVarInst(struct, "float", fConst52)
	DeclareVarInst(struct, "float", fConst53)
	DeclareVarInst(struct, "float", fConst54)
	DeclareVarInst(struct, float, fRec24[3])
	DeclareVarInst(struct, "float", fConst55)
	DeclareVarInst(struct, "float", fConst56)
	DeclareVarInst(struct, "float", fConst57)
	DeclareVarInst(struct, "float", fConst58)
	DeclareVarInst(struct, float, fRec25[3])
	DeclareVarInst(struct, "float", fConst59)
	DeclareVarInst(struct, "float", fConst60)
	DeclareVarInst(struct, "float", fConst61)
	DeclareVarInst(struct, "float", fConst62)
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, "float", fConst63)
	DeclareVarInst(struct, "float", fConst64)
	DeclareVarInst(struct, "float", fConst65)
	DeclareVarInst(struct, "float", fConst66)
	DeclareVarInst(struct, float, fRec27[3])
	DeclareVarInst(struct, "float", fConst67)
	DeclareVarInst(struct, "float", fConst68)
	DeclareVarInst(struct, "float", fConst69)
	DeclareVarInst(struct, "float", fConst70)
	DeclareVarInst(struct, float, fRec28[3])
	DeclareVarInst(struct, "float", fConst71)
	DeclareVarInst(struct, "float", fConst72)
	DeclareVarInst(struct, "float", fConst73)
	DeclareVarInst(struct, "float", fConst74)
	DeclareVarInst(struct, float, fRec29[3])
	DeclareVarInst(struct, "float", fConst75)
	DeclareVarInst(struct, "float", fConst76)
	DeclareVarInst(struct, "float", fConst77)
	DeclareVarInst(struct, "float", fConst78)
	DeclareVarInst(struct, float, fRec30[3])
	DeclareVarInst(struct, "float", fConst79)
	DeclareVarInst(struct, "float", fConst80)
	DeclareVarInst(struct, "float", fConst81)
	DeclareVarInst(struct, "float", fConst82)
	DeclareVarInst(struct, float, fRec31[3])
	DeclareVarInst(struct, "float", fConst83)
	DeclareVarInst(struct, "float", fConst84)
	DeclareVarInst(struct, "float", fConst85)
	DeclareVarInst(struct, "float", fConst86)
	DeclareVarInst(struct, float, fRec32[3])
	DeclareVarInst(struct, "float", fConst87)
	DeclareVarInst(struct, "float", fConst88)
	DeclareVarInst(struct, "float", fConst89)
	DeclareVarInst(struct, "float", fConst90)
	DeclareVarInst(struct, float, fRec33[3])
	DeclareVarInst(struct, "float", fConst91)
	DeclareVarInst(struct, "float", fConst92)
	DeclareVarInst(struct, "float", fConst93)
	DeclareVarInst(struct, "float", fConst94)
	DeclareVarInst(struct, float, fRec34[3])
	DeclareVarInst(struct, "float", fConst95)
	DeclareVarInst(struct, "float", fConst96)
	DeclareVarInst(struct, "float", fConst97)
	DeclareVarInst(struct, "float", fConst98)
	DeclareVarInst(struct, float, fRec35[3])
	DeclareVarInst(struct, "float", fConst99)
	DeclareVarInst(struct, "float", fConst100)
	DeclareVarInst(struct, "float", fConst101)
	DeclareVarInst(struct, "float", fConst102)
	DeclareVarInst(struct, float, fRec36[3])
	DeclareVarInst(struct, "float", fConst103)
	DeclareVarInst(struct, "float", fConst104)
	DeclareVarInst(struct, "float", fConst105)
	DeclareVarInst(struct, "float", fConst106)
	DeclareVarInst(struct, float, fRec37[3])
	DeclareVarInst(struct, "float", fConst107)
	DeclareVarInst(struct, "float", fConst108)
	DeclareVarInst(struct, "float", fConst109)
	DeclareVarInst(struct, "float", fConst110)
	DeclareVarInst(struct, float, fRec38[3])
	DeclareVarInst(struct, "float", fConst111)
	DeclareVarInst(struct, "float", fConst112)
	DeclareVarInst(struct, "float", fConst113)
	DeclareVarInst(struct, "float", fConst114)
	DeclareVarInst(struct, float, fRec39[3])
	DeclareVarInst(struct, "float", fConst115)
	DeclareVarInst(struct, "float", fConst116)
	DeclareVarInst(struct, "float", fConst117)
	DeclareVarInst(struct, "float", fConst118)
	DeclareVarInst(struct, float, fRec40[3])
	DeclareVarInst(struct, "float", fConst119)
	DeclareVarInst(struct, "float", fConst120)
	DeclareVarInst(struct, "float", fConst121)
	DeclareVarInst(struct, "float", fConst122)
	DeclareVarInst(struct, float, fRec41[3])
	DeclareVarInst(struct, "float", fConst123)
	DeclareVarInst(struct, "float", fConst124)
	DeclareVarInst(struct, "float", fConst125)
	DeclareVarInst(struct, "float", fConst126)
	DeclareVarInst(struct, float, fRec42[3])
	DeclareVarInst(struct, "float", fConst127)
	DeclareVarInst(struct, "float", fConst128)
	DeclareVarInst(struct, "float", fConst129)
	DeclareVarInst(struct, "float", fConst130)
	DeclareVarInst(struct, float, fRec43[3])
	DeclareVarInst(struct, "float", fConst131)
	DeclareVarInst(struct, "float", fConst132)
	DeclareVarInst(struct, "float", fConst133)
	DeclareVarInst(struct, "float", fConst134)
	DeclareVarInst(struct, float, fRec44[3])
	DeclareVarInst(struct, "float", fConst135)
	DeclareVarInst(struct, "float", fConst136)
	DeclareVarInst(struct, "float", fConst137)
	DeclareVarInst(struct, "float", fConst138)
	DeclareVarInst(struct, float, fRec45[3])
	DeclareVarInst(struct, "float", fConst139)
	DeclareVarInst(struct, "float", fConst140)
	DeclareVarInst(struct, "float", fConst141)
	DeclareVarInst(struct, "float", fConst142)
	DeclareVarInst(struct, float, fRec46[3])
	DeclareVarInst(struct, "float", fConst143)
	DeclareVarInst(struct, "float", fConst144)
	DeclareVarInst(struct, "float", fConst145)
	DeclareVarInst(struct, "float", fConst146)
	DeclareVarInst(struct, float, fRec47[3])
	DeclareVarInst(struct, "float", fConst147)
	DeclareVarInst(struct, "float", fConst148)
	DeclareVarInst(struct, "float", fConst149)
	DeclareVarInst(struct, "float", fConst150)
	DeclareVarInst(struct, float, fRec48[3])
	DeclareVarInst(struct, "float", fConst151)
	DeclareVarInst(struct, "float", fConst152)
	DeclareVarInst(struct, "float", fConst153)
	DeclareVarInst(struct, "float", fConst154)
	DeclareVarInst(struct, float, fRec49[3])
	DeclareVarInst(struct, "float", fConst155)
	DeclareVarInst(struct, "float", fConst156)
	DeclareVarInst(struct, "float", fConst157)
	DeclareVarInst(struct, "float", fConst158)
	DeclareVarInst(struct, float, fRec50[3])
	DeclareVarInst(struct, "float", fConst159)
	DeclareVarInst(struct, "float", fConst160)
	DeclareVarInst(struct, "float", fConst161)
	DeclareVarInst(struct, "float", fConst162)
	DeclareVarInst(struct, float, fRec51[3])
	DeclareVarInst(struct, "float", fConst163)
	DeclareVarInst(struct, "float", fConst164)
	DeclareVarInst(struct, "float", fConst165)
	DeclareVarInst(struct, "float", fConst166)
	DeclareVarInst(struct, float, fRec52[3])
	DeclareVarInst(struct, "float", fConst167)
	DeclareVarInst(struct, "float", fConst168)
	DeclareVarInst(struct, "float", fConst169)
	DeclareVarInst(struct, "float", fConst170)
	DeclareVarInst(struct, float, fRec53[3])
	DeclareVarInst(struct, "float", fConst171)
	DeclareVarInst(struct, "float", fConst172)
	DeclareVarInst(struct, "float", fConst173)
	DeclareVarInst(struct, "float", fConst174)
	DeclareVarInst(struct, float, fRec54[3])
	DeclareVarInst(struct, "float", fConst175)
	DeclareVarInst(struct, "float", fConst176)
	DeclareVarInst(struct, "float", fConst177)
	DeclareVarInst(struct, "float", fConst178)
	DeclareVarInst(struct, float, fRec55[3])
	DeclareVarInst(struct, "float", fConst179)
	DeclareVarInst(struct, "float", fConst180)
	DeclareVarInst(struct, "float", fConst181)
	DeclareVarInst(struct, "float", fConst182)
	DeclareVarInst(struct, float, fRec56[3])
	DeclareVarInst(struct, "float", fConst183)
	DeclareVarInst(struct, "float", fConst184)
	DeclareVarInst(struct, "float", fConst185)
	DeclareVarInst(struct, "float", fConst186)
	DeclareVarInst(struct, float, fRec57[3])
	DeclareVarInst(struct, "float", fConst187)
	DeclareVarInst(struct, "float", fConst188)
	DeclareVarInst(struct, "float", fConst189)
	DeclareVarInst(struct, "float", fConst190)
	DeclareVarInst(struct, float, fRec58[3])
	DeclareVarInst(struct, "float", fConst191)
	DeclareVarInst(struct, "float", fConst192)
	DeclareVarInst(struct, "float", fConst193)
	DeclareVarInst(struct, "float", fConst194)
	DeclareVarInst(struct, float, fRec59[3])
	DeclareVarInst(struct, "float", fConst195)
	DeclareVarInst(struct, "float", fConst196)
	DeclareVarInst(struct, "float", fConst197)
	DeclareVarInst(struct, "float", fConst198)
	DeclareVarInst(struct, float, fRec60[3])
	DeclareVarInst(struct, "float", fConst199)
	DeclareVarInst(struct, "float", fConst200)
	DeclareVarInst(struct, "float", fConst201)
	DeclareVarInst(struct, "float", fConst202)
	DeclareVarInst(struct, float, fRec61[3])
	DeclareVarInst(struct, "float", fConst203)
	DeclareVarInst(struct, "float", fConst204)
	DeclareVarInst(struct, "float", fConst205)
	DeclareVarInst(struct, "float", fConst206)
	DeclareVarInst(struct, float, fRec62[3])
	DeclareVarInst(struct, "float", fConst207)
	DeclareVarInst(struct, "float", fConst208)
	DeclareVarInst(struct, "float", fConst209)
	DeclareVarInst(struct, "float", fConst210)
	DeclareVarInst(struct, float, fRec63[3])
	DeclareVarInst(struct, "float", fConst211)
	DeclareVarInst(struct, "float", fConst212)
	DeclareVarInst(struct, "float", fConst213)
	DeclareVarInst(struct, "float", fConst214)
	DeclareVarInst(struct, float, fRec64[3])
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, float, fVec4[2048])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec0[2])
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

======= Static Init ==========

BlockInst 
	DeclareVarInst(stack, mydspSIG0, sig0, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(stack, sig0), LoadVarInst(kFunArgs, samplingFreq)))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(250), LoadVarInst(static, ftbl0mydspSIG0)))
	EndBlock
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	EndBlock

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("+", BinopInst("*", Float(0.5f), LoadVarInst(struct, fConst0)), Float(-1.0f)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, FunCallInst("tanf", BinopInst("/", Float(31.415926f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst6, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst6), Float(1.41421354f)), LoadVarInst(struct, fConst5)), Float(1.0f))))
	StoreVarInst(struct, fConst8, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst5))))
	StoreVarInst(struct, fConst9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst6), Float(-1.41421354f)), LoadVarInst(struct, fConst5)), Float(1.0f)))
	StoreVarInst(struct, fConst10, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst8))))
	StoreVarInst(struct, fConst11, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst8))))
	StoreVarInst(struct, fConst12, BinopInst("*", Float(0.00400000019f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst13, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst14, BinopInst("/", Float(500.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst15, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0974743068f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst16, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst15))))
	StoreVarInst(struct, fConst17, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst18, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst15)))
	StoreVarInst(struct, fConst19, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0918262452f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst20, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst19))))
	StoreVarInst(struct, fConst21, BinopInst("/", Float(20.8197117f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst22, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst19)))
	StoreVarInst(struct, fConst23, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0905909166f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst24, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst23))))
	StoreVarInst(struct, fConst25, BinopInst("/", Float(24.0940685f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst26, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst23)))
	StoreVarInst(struct, fConst27, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0810509697f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst28, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst29, BinopInst("/", Float(50.6621399f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst30, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst27)))
	StoreVarInst(struct, fConst31, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0781081766f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst32, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst31))))
	StoreVarInst(struct, fConst33, BinopInst("/", Float(59.3621521f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst34, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst31)))
	StoreVarInst(struct, fConst35, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0688085929f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst36, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst35))))
	StoreVarInst(struct, fConst37, BinopInst("/", Float(88.6990967f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst38, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst35)))
	StoreVarInst(struct, fConst39, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0611052401f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst40, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst39))))
	StoreVarInst(struct, fConst41, BinopInst("/", Float(115.510078f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst42, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst39)))
	StoreVarInst(struct, fConst43, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0567183308f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst44, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst43))))
	StoreVarInst(struct, fConst45, BinopInst("/", Float(132.010986f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst46, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst43)))
	StoreVarInst(struct, fConst47, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0488223769f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst48, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst47))))
	StoreVarInst(struct, fConst49, BinopInst("/", Float(164.478088f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst50, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst47)))
	StoreVarInst(struct, fConst51, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0449043326f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst52, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst51))))
	StoreVarInst(struct, fConst53, BinopInst("/", Float(182.177185f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst54, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst51)))
	StoreVarInst(struct, fConst55, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0350424498f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst56, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst57, BinopInst("/", Float(232.935272f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst58, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst55)))
	StoreVarInst(struct, fConst59, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0341717675f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst60, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst59))))
	StoreVarInst(struct, fConst61, BinopInst("/", Float(237.946106f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst62, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst59)))
	StoreVarInst(struct, fConst63, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.031866312f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst64, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst63))))
	StoreVarInst(struct, fConst65, BinopInst("/", Float(251.725769f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst66, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst63)))
	StoreVarInst(struct, fConst67, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0248362795f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst68, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst67))))
	StoreVarInst(struct, fConst69, BinopInst("/", Float(299.355438f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst70, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst67)))
	StoreVarInst(struct, fConst71, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0221360233f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst72, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst71))))
	StoreVarInst(struct, fConst73, BinopInst("/", Float(320.561829f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst74, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst71)))
	StoreVarInst(struct, fConst75, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0210792925f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst76, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst75))))
	StoreVarInst(struct, fConst77, BinopInst("/", Float(329.427399f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst78, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst75)))
	StoreVarInst(struct, fConst79, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0171158724f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst80, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst79))))
	StoreVarInst(struct, fConst81, BinopInst("/", Float(366.221741f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst82, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst79)))
	StoreVarInst(struct, fConst83, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0140852043f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst84, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst83))))
	StoreVarInst(struct, fConst85, BinopInst("/", Float(399.287628f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst86, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst83)))
	StoreVarInst(struct, fConst87, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000329498813f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst88, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst87))))
	StoreVarInst(struct, fConst89, BinopInst("/", Float(838.660706f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst90, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst87)))
	StoreVarInst(struct, fConst91, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000124247395f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst92, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst91))))
	StoreVarInst(struct, fConst93, BinopInst("/", Float(908.228149f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst94, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst91)))
	StoreVarInst(struct, fConst95, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(7.53835775e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst96, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst95))))
	StoreVarInst(struct, fConst97, BinopInst("/", Float(938.946655f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst98, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst95)))
	StoreVarInst(struct, fConst99, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(5.65755508e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst100, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst99))))
	StoreVarInst(struct, fConst101, BinopInst("/", Float(955.251526f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst102, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst99)))
	StoreVarInst(struct, fConst103, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(4.96453904e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst104, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst103))))
	StoreVarInst(struct, fConst105, BinopInst("/", Float(962.370361f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst106, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst103)))
	StoreVarInst(struct, fConst107, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(3.7056674e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst108, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst107))))
	StoreVarInst(struct, fConst109, BinopInst("/", Float(977.644775f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst110, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst107)))
	StoreVarInst(struct, fConst111, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(2.66114275e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst112, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst111))))
	StoreVarInst(struct, fConst113, BinopInst("/", Float(993.893127f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst114, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst111)))
	StoreVarInst(struct, fConst115, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0131463278f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst116, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst115))))
	StoreVarInst(struct, fConst117, BinopInst("/", Float(410.686584f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst118, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst115)))
	StoreVarInst(struct, fConst119, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0123624494f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst120, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst119))))
	StoreVarInst(struct, fConst121, BinopInst("/", Float(420.713928f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst122, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst119)))
	StoreVarInst(struct, fConst123, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00913601927f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst124, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst123))))
	StoreVarInst(struct, fConst125, BinopInst("/", Float(468.286438f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst126, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst123)))
	StoreVarInst(struct, fConst127, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00767402584f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst128, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst127))))
	StoreVarInst(struct, fConst129, BinopInst("/", Float(494.436432f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst130, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst127)))
	StoreVarInst(struct, fConst131, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00699721137f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst132, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst131))))
	StoreVarInst(struct, fConst133, BinopInst("/", Float(507.916992f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst134, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst131)))
	StoreVarInst(struct, fConst135, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00462675327f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst136, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst135))))
	StoreVarInst(struct, fConst137, BinopInst("/", Float(565.34845f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst138, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst135)))
	StoreVarInst(struct, fConst139, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00401024008f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst140, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst139))))
	StoreVarInst(struct, fConst141, BinopInst("/", Float(584.12323f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst142, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst139)))
	StoreVarInst(struct, fConst143, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00359531236f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst144, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst143))))
	StoreVarInst(struct, fConst145, BinopInst("/", Float(598.105225f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst146, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst143)))
	StoreVarInst(struct, fConst147, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00320503488f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst148, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst147))))
	StoreVarInst(struct, fConst149, BinopInst("/", Float(612.489319f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst150, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst147)))
	StoreVarInst(struct, fConst151, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0015662252f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst152, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst151))))
	StoreVarInst(struct, fConst153, BinopInst("/", Float(695.045959f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst154, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst151)))
	StoreVarInst(struct, fConst155, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00143769139f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst156, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst155))))
	StoreVarInst(struct, fConst157, BinopInst("/", Float(704.150269f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst158, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst155)))
	StoreVarInst(struct, fConst159, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00129330496f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst160, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst159))))
	StoreVarInst(struct, fConst161, BinopInst("/", Float(715.18988f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst162, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst159)))
	StoreVarInst(struct, fConst163, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000912711956f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst164, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst163))))
	StoreVarInst(struct, fConst165, BinopInst("/", Float(749.935852f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst166, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst163)))
	StoreVarInst(struct, fConst167, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000537810789f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst168, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst167))))
	StoreVarInst(struct, fConst169, BinopInst("/", Float(798.247253f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst170, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst167)))
	StoreVarInst(struct, fConst171, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000432563043f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst172, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst171))))
	StoreVarInst(struct, fConst173, BinopInst("/", Float(816.700989f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst174, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst171)))
	StoreVarInst(struct, fConst175, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000362893392f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst176, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst175))))
	StoreVarInst(struct, fConst177, BinopInst("/", Float(831.007812f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst178, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst175)))
	StoreVarInst(struct, fConst179, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(5.79888183e-06f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst180, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst179))))
	StoreVarInst(struct, fConst181, BinopInst("/", Float(1056.23486f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst182, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst179)))
	StoreVarInst(struct, fConst183, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(2.80919903e-06f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst184, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst183))))
	StoreVarInst(struct, fConst185, BinopInst("/", Float(1079.84705f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst186, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst183)))
	StoreVarInst(struct, fConst187, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(1.5867239e-06f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst188, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst187))))
	StoreVarInst(struct, fConst189, BinopInst("/", Float(1096.1897f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst190, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst187)))
	StoreVarInst(struct, fConst191, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(4.94038545e-07f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst192, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst191))))
	StoreVarInst(struct, fConst193, BinopInst("/", Float(1124.29431f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst194, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst191)))
	StoreVarInst(struct, fConst195, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(2.19791588e-07f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst196, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst195))))
	StoreVarInst(struct, fConst197, BinopInst("/", Float(1140.28503f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst198, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst195)))
	StoreVarInst(struct, fConst199, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(4.53858888e-08f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst200, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst199))))
	StoreVarInst(struct, fConst201, BinopInst("/", Float(1164.89001f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst202, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst199)))
	StoreVarInst(struct, fConst203, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(1.88244775e-09f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst204, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst203))))
	StoreVarInst(struct, fConst205, BinopInst("/", Float(1196.12366f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst206, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst203)))
	StoreVarInst(struct, fConst207, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(2.61844324e-10f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst208, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst207))))
	StoreVarInst(struct, fConst209, BinopInst("/", Float(1207.56543f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst210, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst207)))
	StoreVarInst(struct, fConst211, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(6.3867631e-15f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst212, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst211))))
	StoreVarInst(struct, fConst213, BinopInst("/", Float(1228.39417f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst214, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst211)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.80000000000000004f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(6500.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.5f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2048))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec14[LoadVarInst(loop, l5)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(3))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(3))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(3))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(3))
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
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(3))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(3))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(3))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(3))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(3))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(3))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(3))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(3))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(3))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(3))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(3))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(3))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(3))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(3))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(3))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(3))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(3))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(3))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(3))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(3))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(3))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(3))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(3))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(3))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(3))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(3))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(3))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(3))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(3))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(3))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec56[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(3))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec57[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(3))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(3))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(3))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(3))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(3))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(3))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(3))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l60)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(2))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(2048))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(2))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(2))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l64)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 365
Store = 0
Binop = 262
Numbers = 144
Declare = 137
Cast = 19
Select = 0
Loop = 0
Funcall = 63

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("/", Float(340.0f), LoadVarInst(stack, fSlow1)), Float(-0.0399999991f))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("+", LoadVarInst(stack, fSlow2), Float(-1.49999499f)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("floorf", LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow5)), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fSlow6)))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fSlow7)))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fSlow8)))))
	DeclareVarInst(stack, "int", iSlow10, CastInst("int", LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "int", iSlow11, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iSlow10))))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", BinopInst("*", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow6)), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fSlow7)))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fSlow8)))))
	DeclareVarInst(stack, "int", iSlow14, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow10), Int32(1)))))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow7))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fSlow8))))))
	DeclareVarInst(stack, "int", iSlow16, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow10), Int32(2)))))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("*", Float(0.166666672f), BinopInst("*", LoadVarInst(stack, fSlow17), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow8)))))
	DeclareVarInst(stack, "int", iSlow19, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow10), Int32(3)))))))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(stack, fSlow7))))
	DeclareVarInst(stack, "int", iSlow21, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow10), Int32(4)))))))
	DeclareVarInst(stack, "int", iSlow22, BinopInst("*", Int32(50), CastInst("int", CastInst("float", LoadVarInst(struct, fEntry0)))))
	DeclareVarInst(stack, "float", fSlow23, Select2Inst(BinopInst("<", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iSlow22)]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow24, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), CastInst("float", LoadVarInst(struct, fHslider3)))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow24)))
	DeclareVarInst(stack, "float", fSlow26, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow25), Float(1.41421354f)), LoadVarInst(stack, fSlow24)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("/", CastInst("float", LoadVarInst(struct, fHslider2)), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow24))))))
	DeclareVarInst(stack, "float", fSlow30, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow25), Float(-1.41421354f)), LoadVarInst(stack, fSlow24)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow31, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow32, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(stack, fSlow32)))
	DeclareVarInst(stack, "float", fSlow34, BinopInst("*", LoadVarInst(struct, fConst13), LoadVarInst(stack, fSlow32)))
	DeclareVarInst(stack, "float", fSlow35, BinopInst("/", LoadVarInst(struct, fConst14), LoadVarInst(stack, fSlow32)))
	DeclareVarInst(stack, "float", fSlow36, BinopInst("*", LoadVarInst(struct, fConst16), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst17), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow37, Select2Inst(BinopInst("<", BinopInst("*", Float(3.31356001f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(1))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("*", LoadVarInst(struct, fConst20), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst21), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow39, Select2Inst(BinopInst("<", BinopInst("*", Float(3.83469009f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(2))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow40, BinopInst("*", LoadVarInst(struct, fConst24), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow41, Select2Inst(BinopInst("<", BinopInst("*", Float(8.06313038f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(3))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow42, BinopInst("*", LoadVarInst(struct, fConst28), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst29), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow43, Select2Inst(BinopInst("<", BinopInst("*", Float(9.44777966f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(4))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow44, BinopInst("*", LoadVarInst(struct, fConst32), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst33), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow45, Select2Inst(BinopInst("<", BinopInst("*", Float(14.1169004f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(5))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow46, BinopInst("*", LoadVarInst(struct, fConst36), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow47, Select2Inst(BinopInst("<", BinopInst("*", Float(18.3840008f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(6))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow48, BinopInst("*", LoadVarInst(struct, fConst40), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst41), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow49, Select2Inst(BinopInst("<", BinopInst("*", Float(21.0102005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(7))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow50, BinopInst("*", LoadVarInst(struct, fConst44), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst45), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow51, Select2Inst(BinopInst("<", BinopInst("*", Float(26.1774998f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(8))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow52, BinopInst("*", LoadVarInst(struct, fConst48), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow53, Select2Inst(BinopInst("<", BinopInst("*", Float(28.9944f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(9))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow54, BinopInst("*", LoadVarInst(struct, fConst52), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst53), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow55, Select2Inst(BinopInst("<", BinopInst("*", Float(37.0727997f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(10))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow56, BinopInst("*", LoadVarInst(struct, fConst56), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst57), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow57, Select2Inst(BinopInst("<", BinopInst("*", Float(37.8703003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(11))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow58, BinopInst("*", LoadVarInst(struct, fConst60), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow59, Select2Inst(BinopInst("<", BinopInst("*", Float(40.0634003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(12))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow60, BinopInst("*", LoadVarInst(struct, fConst64), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow61, Select2Inst(BinopInst("<", BinopInst("*", Float(47.6439018f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(13))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow62, BinopInst("*", LoadVarInst(struct, fConst68), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst69), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow63, Select2Inst(BinopInst("<", BinopInst("*", Float(51.019001f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(14))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow64, BinopInst("*", LoadVarInst(struct, fConst72), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst73), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow65, Select2Inst(BinopInst("<", BinopInst("*", Float(52.4300003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(15))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow66, BinopInst("*", LoadVarInst(struct, fConst76), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow67, Select2Inst(BinopInst("<", BinopInst("*", Float(58.2859993f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(16))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow68, BinopInst("*", LoadVarInst(struct, fConst80), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow69, Select2Inst(BinopInst("<", BinopInst("*", Float(63.5485992f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(17))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow70, BinopInst("*", LoadVarInst(struct, fConst84), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow71, Select2Inst(BinopInst("<", BinopInst("*", Float(133.477005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(34))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow72, BinopInst("*", LoadVarInst(struct, fConst88), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst89), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow73, Select2Inst(BinopInst("<", BinopInst("*", Float(144.548996f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(35))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow74, BinopInst("*", LoadVarInst(struct, fConst92), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst93), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow75, Select2Inst(BinopInst("<", BinopInst("*", Float(149.438004f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(36))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow76, BinopInst("*", LoadVarInst(struct, fConst96), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow77, Select2Inst(BinopInst("<", BinopInst("*", Float(152.033005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(37))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow78, BinopInst("*", LoadVarInst(struct, fConst100), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow79, Select2Inst(BinopInst("<", BinopInst("*", Float(153.166f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(38))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow80, BinopInst("*", LoadVarInst(struct, fConst104), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow81, Select2Inst(BinopInst("<", BinopInst("*", Float(155.597f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(39))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow82, BinopInst("*", LoadVarInst(struct, fConst108), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst109), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow83, Select2Inst(BinopInst("<", BinopInst("*", Float(158.182999f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(40))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow84, BinopInst("*", LoadVarInst(struct, fConst112), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow85, Select2Inst(BinopInst("<", BinopInst("*", Float(65.3628006f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(18))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow86, BinopInst("*", LoadVarInst(struct, fConst116), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst117), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow87, Select2Inst(BinopInst("<", BinopInst("*", Float(66.9587021f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(19))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow88, BinopInst("*", LoadVarInst(struct, fConst120), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow89, Select2Inst(BinopInst("<", BinopInst("*", Float(74.530098f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(20))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow90, BinopInst("*", LoadVarInst(struct, fConst124), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst125), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow91, Select2Inst(BinopInst("<", BinopInst("*", Float(78.6920013f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(21))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow92, BinopInst("*", LoadVarInst(struct, fConst128), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst129), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow93, Select2Inst(BinopInst("<", BinopInst("*", Float(80.8375015f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(22))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow94, BinopInst("*", LoadVarInst(struct, fConst132), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst133), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow95, Select2Inst(BinopInst("<", BinopInst("*", Float(89.9779968f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(23))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow96, BinopInst("*", LoadVarInst(struct, fConst136), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst137), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow97, Select2Inst(BinopInst("<", BinopInst("*", Float(92.9661026f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(24))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow98, BinopInst("*", LoadVarInst(struct, fConst140), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst141), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow99, Select2Inst(BinopInst("<", BinopInst("*", Float(95.1913986f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(25))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow100, BinopInst("*", LoadVarInst(struct, fConst144), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst145), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow101, Select2Inst(BinopInst("<", BinopInst("*", Float(97.4806976f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(26))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow102, BinopInst("*", LoadVarInst(struct, fConst148), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst149), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow103, Select2Inst(BinopInst("<", BinopInst("*", Float(110.620003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(27))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow104, BinopInst("*", LoadVarInst(struct, fConst152), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst153), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow105, Select2Inst(BinopInst("<", BinopInst("*", Float(112.069f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(28))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow106, BinopInst("*", LoadVarInst(struct, fConst156), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst157), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow107, Select2Inst(BinopInst("<", BinopInst("*", Float(113.825996f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(29))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow108, BinopInst("*", LoadVarInst(struct, fConst160), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst161), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow109, Select2Inst(BinopInst("<", BinopInst("*", Float(119.356003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(30))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow110, BinopInst("*", LoadVarInst(struct, fConst164), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst165), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow111, Select2Inst(BinopInst("<", BinopInst("*", Float(127.044998f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(31))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow112, BinopInst("*", LoadVarInst(struct, fConst168), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst169), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow113, Select2Inst(BinopInst("<", BinopInst("*", Float(129.981995f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(32))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow114, BinopInst("*", LoadVarInst(struct, fConst172), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst173), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow115, Select2Inst(BinopInst("<", BinopInst("*", Float(132.259003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(33))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow116, BinopInst("*", LoadVarInst(struct, fConst176), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst177), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow117, Select2Inst(BinopInst("<", BinopInst("*", Float(168.104996f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(41))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow118, BinopInst("*", LoadVarInst(struct, fConst180), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst181), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow119, Select2Inst(BinopInst("<", BinopInst("*", Float(171.863007f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(42))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow120, BinopInst("*", LoadVarInst(struct, fConst184), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst185), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow121, Select2Inst(BinopInst("<", BinopInst("*", Float(174.464005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(43))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow122, BinopInst("*", LoadVarInst(struct, fConst188), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst189), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow123, Select2Inst(BinopInst("<", BinopInst("*", Float(178.936996f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(44))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow124, BinopInst("*", LoadVarInst(struct, fConst192), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst193), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow125, Select2Inst(BinopInst("<", BinopInst("*", Float(181.481995f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(45))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow126, BinopInst("*", LoadVarInst(struct, fConst196), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst197), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow127, Select2Inst(BinopInst("<", BinopInst("*", Float(185.397995f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(46))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow128, BinopInst("*", LoadVarInst(struct, fConst200), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst201), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow129, Select2Inst(BinopInst("<", BinopInst("*", Float(190.369003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(47))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow130, BinopInst("*", LoadVarInst(struct, fConst204), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst205), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow131, Select2Inst(BinopInst("<", BinopInst("*", Float(192.190002f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(48))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow132, BinopInst("*", LoadVarInst(struct, fConst208), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst209), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow133, Select2Inst(BinopInst("<", BinopInst("*", Float(195.505005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(49))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow134, BinopInst("*", LoadVarInst(struct, fConst212), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst213), LoadVarInst(stack, fSlow1)))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 610
Store = 184
Binop = 426
Numbers = 206
Declare = 12
Cast = 5
Select = 0
Loop = 1
Funcall = 1

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec2[Int32(0)], Int32(0))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec7[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("+", BinopInst("*", Float(0.99000001f), LoadVarInst(struct, fRec9[Int32(0)])), CastInst("float", LoadVarInst(struct, iRec2[Int32(1)]))))
		StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp0))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow11)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow14)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow16)), Int32(2047))]))), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow19)), Int32(2047))]))), BinopInst("*", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow21)), Int32(2047))]))))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec6[Int32(1)]))))
		StoreVarInst(struct, iRec14[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec14[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec14[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec13[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst10), LoadVarInst(struct, fRec13[Int32(1)]))))))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec13[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst11), LoadVarInst(struct, fRec13[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec13[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow28), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow30), LoadVarInst(struct, fRec12[Int32(2)]))))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow31))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fSlow32))
		StoreVarInst(struct, fRec15[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow31), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fSlow33), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec15[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst12), BinopInst("-", LoadVarInst(stack, fSlow32), LoadVarInst(struct, fVec2[Int32(1)])))), Float(1.0f)))))
		DeclareVarInst(stack, "int", iTemp1, BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fSlow34)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow27), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec12[Int32(1)])), LoadVarInst(struct, fRec12[Int32(0)]))), Select2Inst(LoadVarInst(stack, iTemp1) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp1) BinopInst("*", LoadVarInst(stack, fSlow35), LoadVarInst(struct, fRec15[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fSlow33)) BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fSlow34)))), Float(1.0f)) Float(0.0f))))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow36), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec11[Int32(2)])))))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow38), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst22), LoadVarInst(struct, fRec16[Int32(2)])))))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec17[Int32(2)])))))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow42), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec18[Int32(2)])))))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow44), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst34), LoadVarInst(struct, fRec19[Int32(2)])))))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow46), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec20[Int32(2)])))))
		StoreVarInst(struct, fRec21[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow48), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec21[Int32(2)])))))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow50), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst46), LoadVarInst(struct, fRec22[Int32(2)])))))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow52), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec23[Int32(2)])))))
		StoreVarInst(struct, fRec24[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow54), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec24[Int32(2)])))))
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow56), LoadVarInst(struct, fRec25[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst58), LoadVarInst(struct, fRec25[Int32(2)])))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow58), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec26[Int32(2)])))))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow60), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst66), LoadVarInst(struct, fRec27[Int32(2)])))))
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow62), LoadVarInst(struct, fRec28[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst70), LoadVarInst(struct, fRec28[Int32(2)])))))
		StoreVarInst(struct, fRec29[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow64), LoadVarInst(struct, fRec29[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst74), LoadVarInst(struct, fRec29[Int32(2)])))))
		StoreVarInst(struct, fRec30[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow66), LoadVarInst(struct, fRec30[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec30[Int32(2)])))))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow68), LoadVarInst(struct, fRec31[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec31[Int32(2)])))))
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow70), LoadVarInst(struct, fRec32[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec32[Int32(2)])))))
		StoreVarInst(struct, fRec33[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow72), LoadVarInst(struct, fRec33[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst90), LoadVarInst(struct, fRec33[Int32(2)])))))
		StoreVarInst(struct, fRec34[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow74), LoadVarInst(struct, fRec34[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst94), LoadVarInst(struct, fRec34[Int32(2)])))))
		StoreVarInst(struct, fRec35[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow76), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec35[Int32(2)])))))
		StoreVarInst(struct, fRec36[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow78), LoadVarInst(struct, fRec36[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec36[Int32(2)])))))
		StoreVarInst(struct, fRec37[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow80), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec37[Int32(2)])))))
		StoreVarInst(struct, fRec38[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow82), LoadVarInst(struct, fRec38[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst110), LoadVarInst(struct, fRec38[Int32(2)])))))
		StoreVarInst(struct, fRec39[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow84), LoadVarInst(struct, fRec39[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst114), LoadVarInst(struct, fRec39[Int32(2)])))))
		StoreVarInst(struct, fRec40[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow86), LoadVarInst(struct, fRec40[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst118), LoadVarInst(struct, fRec40[Int32(2)])))))
		StoreVarInst(struct, fRec41[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow88), LoadVarInst(struct, fRec41[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst122), LoadVarInst(struct, fRec41[Int32(2)])))))
		StoreVarInst(struct, fRec42[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow90), LoadVarInst(struct, fRec42[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst126), LoadVarInst(struct, fRec42[Int32(2)])))))
		StoreVarInst(struct, fRec43[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow92), LoadVarInst(struct, fRec43[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst130), LoadVarInst(struct, fRec43[Int32(2)])))))
		StoreVarInst(struct, fRec44[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow94), LoadVarInst(struct, fRec44[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec44[Int32(2)])))))
		StoreVarInst(struct, fRec45[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow96), LoadVarInst(struct, fRec45[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec45[Int32(2)])))))
		StoreVarInst(struct, fRec46[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow98), LoadVarInst(struct, fRec46[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec46[Int32(2)])))))
		StoreVarInst(struct, fRec47[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow100), LoadVarInst(struct, fRec47[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst146), LoadVarInst(struct, fRec47[Int32(2)])))))
		StoreVarInst(struct, fRec48[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow102), LoadVarInst(struct, fRec48[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst150), LoadVarInst(struct, fRec48[Int32(2)])))))
		StoreVarInst(struct, fRec49[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow104), LoadVarInst(struct, fRec49[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst154), LoadVarInst(struct, fRec49[Int32(2)])))))
		StoreVarInst(struct, fRec50[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow106), LoadVarInst(struct, fRec50[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst158), LoadVarInst(struct, fRec50[Int32(2)])))))
		StoreVarInst(struct, fRec51[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow108), LoadVarInst(struct, fRec51[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst162), LoadVarInst(struct, fRec51[Int32(2)])))))
		StoreVarInst(struct, fRec52[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow110), LoadVarInst(struct, fRec52[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst166), LoadVarInst(struct, fRec52[Int32(2)])))))
		StoreVarInst(struct, fRec53[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow112), LoadVarInst(struct, fRec53[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst170), LoadVarInst(struct, fRec53[Int32(2)])))))
		StoreVarInst(struct, fRec54[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow114), LoadVarInst(struct, fRec54[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst174), LoadVarInst(struct, fRec54[Int32(2)])))))
		StoreVarInst(struct, fRec55[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow116), LoadVarInst(struct, fRec55[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst178), LoadVarInst(struct, fRec55[Int32(2)])))))
		StoreVarInst(struct, fRec56[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow118), LoadVarInst(struct, fRec56[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst182), LoadVarInst(struct, fRec56[Int32(2)])))))
		StoreVarInst(struct, fRec57[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow120), LoadVarInst(struct, fRec57[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst186), LoadVarInst(struct, fRec57[Int32(2)])))))
		StoreVarInst(struct, fRec58[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow122), LoadVarInst(struct, fRec58[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst190), LoadVarInst(struct, fRec58[Int32(2)])))))
		StoreVarInst(struct, fRec59[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow124), LoadVarInst(struct, fRec59[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst194), LoadVarInst(struct, fRec59[Int32(2)])))))
		StoreVarInst(struct, fRec60[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow126), LoadVarInst(struct, fRec60[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst198), LoadVarInst(struct, fRec60[Int32(2)])))))
		StoreVarInst(struct, fRec61[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow128), LoadVarInst(struct, fRec61[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst202), LoadVarInst(struct, fRec61[Int32(2)])))))
		StoreVarInst(struct, fRec62[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow130), LoadVarInst(struct, fRec62[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst206), LoadVarInst(struct, fRec62[Int32(2)])))))
		StoreVarInst(struct, fRec63[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow132), LoadVarInst(struct, fRec63[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst210), LoadVarInst(struct, fRec63[Int32(2)])))))
		StoreVarInst(struct, fRec64[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow134), LoadVarInst(struct, fRec64[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst214), LoadVarInst(struct, fRec64[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("-", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(struct, fRec11[Int32(2)]))), BinopInst("*", LoadVarInst(stack, fSlow37), BinopInst("-", LoadVarInst(struct, fRec16[Int32(0)]), LoadVarInst(struct, fRec16[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow39), BinopInst("-", LoadVarInst(struct, fRec17[Int32(0)]), LoadVarInst(struct, fRec17[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow41), BinopInst("-", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fRec18[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow43), BinopInst("-", LoadVarInst(struct, fRec19[Int32(0)]), LoadVarInst(struct, fRec19[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("-", LoadVarInst(struct, fRec20[Int32(0)]), LoadVarInst(struct, fRec20[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow47), BinopInst("-", LoadVarInst(struct, fRec21[Int32(0)]), LoadVarInst(struct, fRec21[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow49), BinopInst("-", LoadVarInst(struct, fRec22[Int32(0)]), LoadVarInst(struct, fRec22[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow51), BinopInst("-", LoadVarInst(struct, fRec23[Int32(0)]), LoadVarInst(struct, fRec23[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow53), BinopInst("-", LoadVarInst(struct, fRec24[Int32(0)]), LoadVarInst(struct, fRec24[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow55), BinopInst("-", LoadVarInst(struct, fRec25[Int32(0)]), LoadVarInst(struct, fRec25[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow57), BinopInst("-", LoadVarInst(struct, fRec26[Int32(0)]), LoadVarInst(struct, fRec26[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow59), BinopInst("-", LoadVarInst(struct, fRec27[Int32(0)]), LoadVarInst(struct, fRec27[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow61), BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), LoadVarInst(struct, fRec28[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow63), BinopInst("-", LoadVarInst(struct, fRec29[Int32(0)]), LoadVarInst(struct, fRec29[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow65), BinopInst("-", LoadVarInst(struct, fRec30[Int32(0)]), LoadVarInst(struct, fRec30[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow67), BinopInst("-", LoadVarInst(struct, fRec31[Int32(0)]), LoadVarInst(struct, fRec31[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow69), BinopInst("-", LoadVarInst(struct, fRec32[Int32(0)]), LoadVarInst(struct, fRec32[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow71), BinopInst("-", LoadVarInst(struct, fRec33[Int32(0)]), LoadVarInst(struct, fRec33[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow73), BinopInst("-", LoadVarInst(struct, fRec34[Int32(0)]), LoadVarInst(struct, fRec34[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow75), BinopInst("-", LoadVarInst(struct, fRec35[Int32(0)]), LoadVarInst(struct, fRec35[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow77), BinopInst("-", LoadVarInst(struct, fRec36[Int32(0)]), LoadVarInst(struct, fRec36[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow79), BinopInst("-", LoadVarInst(struct, fRec37[Int32(0)]), LoadVarInst(struct, fRec37[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow81), BinopInst("-", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(struct, fRec38[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow83), BinopInst("-", LoadVarInst(struct, fRec39[Int32(0)]), LoadVarInst(struct, fRec39[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow85), BinopInst("-", LoadVarInst(struct, fRec40[Int32(0)]), LoadVarInst(struct, fRec40[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow87), BinopInst("-", LoadVarInst(struct, fRec41[Int32(0)]), LoadVarInst(struct, fRec41[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow89), BinopInst("-", LoadVarInst(struct, fRec42[Int32(0)]), LoadVarInst(struct, fRec42[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow91), BinopInst("-", LoadVarInst(struct, fRec43[Int32(0)]), LoadVarInst(struct, fRec43[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow93), BinopInst("-", LoadVarInst(struct, fRec44[Int32(0)]), LoadVarInst(struct, fRec44[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow95), BinopInst("-", LoadVarInst(struct, fRec45[Int32(0)]), LoadVarInst(struct, fRec45[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow97), BinopInst("-", LoadVarInst(struct, fRec46[Int32(0)]), LoadVarInst(struct, fRec46[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow99), BinopInst("-", LoadVarInst(struct, fRec47[Int32(0)]), LoadVarInst(struct, fRec47[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow101), BinopInst("-", LoadVarInst(struct, fRec48[Int32(0)]), LoadVarInst(struct, fRec48[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow103), BinopInst("-", LoadVarInst(struct, fRec49[Int32(0)]), LoadVarInst(struct, fRec49[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow105), BinopInst("-", LoadVarInst(struct, fRec50[Int32(0)]), LoadVarInst(struct, fRec50[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow107), BinopInst("-", LoadVarInst(struct, fRec51[Int32(0)]), LoadVarInst(struct, fRec51[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow109), BinopInst("-", LoadVarInst(struct, fRec52[Int32(0)]), LoadVarInst(struct, fRec52[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow111), BinopInst("-", LoadVarInst(struct, fRec53[Int32(0)]), LoadVarInst(struct, fRec53[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow113), BinopInst("-", LoadVarInst(struct, fRec54[Int32(0)]), LoadVarInst(struct, fRec54[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow115), BinopInst("-", LoadVarInst(struct, fRec55[Int32(0)]), LoadVarInst(struct, fRec55[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow117), BinopInst("-", LoadVarInst(struct, fRec56[Int32(0)]), LoadVarInst(struct, fRec56[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow119), BinopInst("-", LoadVarInst(struct, fRec57[Int32(0)]), LoadVarInst(struct, fRec57[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow121), BinopInst("-", LoadVarInst(struct, fRec58[Int32(0)]), LoadVarInst(struct, fRec58[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow123), BinopInst("-", LoadVarInst(struct, fRec59[Int32(0)]), LoadVarInst(struct, fRec59[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow125), BinopInst("-", LoadVarInst(struct, fRec60[Int32(0)]), LoadVarInst(struct, fRec60[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow127), BinopInst("-", LoadVarInst(struct, fRec61[Int32(0)]), LoadVarInst(struct, fRec61[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow129), BinopInst("-", LoadVarInst(struct, fRec62[Int32(0)]), LoadVarInst(struct, fRec62[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow131), BinopInst("-", LoadVarInst(struct, fRec63[Int32(0)]), LoadVarInst(struct, fRec63[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow133), BinopInst("-", LoadVarInst(struct, fRec64[Int32(0)]), LoadVarInst(struct, fRec64[Int32(2)])))))
		StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp3))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("+", BinopInst("*", Float(0.99000001f), LoadVarInst(struct, fRec10[Int32(0)])), BinopInst("*", Float(0.0199999996f), LoadVarInst(struct, fVec3[Int32(1)]))))
		StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp4))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow11)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow14)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow16)), Int32(2047))]))), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow19)), Int32(2047))]))), BinopInst("*", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow21)), Int32(2047))]))))))
		DeclareVarInst(stack, "int", iRec8, Int32(0))
		DeclareVarInst(stack, "float", fRec3, LoadVarInst(struct, fRec6[Int32(0)]))
		DeclareVarInst(stack, "float", fRec4, LoadVarInst(struct, fRec7[Int32(0)]))
		DeclareVarInst(stack, "float", fRec5, BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec8))))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
		DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fRec1)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp5)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp5)))
		StoreVarInst(struct, iRec2[Int32(1)], LoadVarInst(struct, iRec2[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, iRec14[Int32(1)], LoadVarInst(struct, iRec14[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(2)], LoadVarInst(struct, fRec13[Int32(1)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(2)], LoadVarInst(struct, fRec11[Int32(1)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
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
		StoreVarInst(struct, fRec24[Int32(2)], LoadVarInst(struct, fRec24[Int32(1)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(2)], LoadVarInst(struct, fRec25[Int32(1)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(2)], LoadVarInst(struct, fRec27[Int32(1)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(2)], LoadVarInst(struct, fRec28[Int32(1)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec29[Int32(2)], LoadVarInst(struct, fRec29[Int32(1)]))
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(2)], LoadVarInst(struct, fRec30[Int32(1)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fRec31[Int32(2)], LoadVarInst(struct, fRec31[Int32(1)]))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(2)], LoadVarInst(struct, fRec32[Int32(1)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fRec33[Int32(2)], LoadVarInst(struct, fRec33[Int32(1)]))
		StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
		StoreVarInst(struct, fRec34[Int32(2)], LoadVarInst(struct, fRec34[Int32(1)]))
		StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
		StoreVarInst(struct, fRec35[Int32(2)], LoadVarInst(struct, fRec35[Int32(1)]))
		StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
		StoreVarInst(struct, fRec36[Int32(2)], LoadVarInst(struct, fRec36[Int32(1)]))
		StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
		StoreVarInst(struct, fRec37[Int32(2)], LoadVarInst(struct, fRec37[Int32(1)]))
		StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
		StoreVarInst(struct, fRec38[Int32(2)], LoadVarInst(struct, fRec38[Int32(1)]))
		StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
		StoreVarInst(struct, fRec39[Int32(2)], LoadVarInst(struct, fRec39[Int32(1)]))
		StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
		StoreVarInst(struct, fRec40[Int32(2)], LoadVarInst(struct, fRec40[Int32(1)]))
		StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
		StoreVarInst(struct, fRec41[Int32(2)], LoadVarInst(struct, fRec41[Int32(1)]))
		StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
		StoreVarInst(struct, fRec42[Int32(2)], LoadVarInst(struct, fRec42[Int32(1)]))
		StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
		StoreVarInst(struct, fRec43[Int32(2)], LoadVarInst(struct, fRec43[Int32(1)]))
		StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
		StoreVarInst(struct, fRec44[Int32(2)], LoadVarInst(struct, fRec44[Int32(1)]))
		StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
		StoreVarInst(struct, fRec45[Int32(2)], LoadVarInst(struct, fRec45[Int32(1)]))
		StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
		StoreVarInst(struct, fRec46[Int32(2)], LoadVarInst(struct, fRec46[Int32(1)]))
		StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
		StoreVarInst(struct, fRec47[Int32(2)], LoadVarInst(struct, fRec47[Int32(1)]))
		StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
		StoreVarInst(struct, fRec48[Int32(2)], LoadVarInst(struct, fRec48[Int32(1)]))
		StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
		StoreVarInst(struct, fRec49[Int32(2)], LoadVarInst(struct, fRec49[Int32(1)]))
		StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
		StoreVarInst(struct, fRec50[Int32(2)], LoadVarInst(struct, fRec50[Int32(1)]))
		StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
		StoreVarInst(struct, fRec51[Int32(2)], LoadVarInst(struct, fRec51[Int32(1)]))
		StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
		StoreVarInst(struct, fRec52[Int32(2)], LoadVarInst(struct, fRec52[Int32(1)]))
		StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
		StoreVarInst(struct, fRec53[Int32(2)], LoadVarInst(struct, fRec53[Int32(1)]))
		StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
		StoreVarInst(struct, fRec54[Int32(2)], LoadVarInst(struct, fRec54[Int32(1)]))
		StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
		StoreVarInst(struct, fRec55[Int32(2)], LoadVarInst(struct, fRec55[Int32(1)]))
		StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
		StoreVarInst(struct, fRec56[Int32(2)], LoadVarInst(struct, fRec56[Int32(1)]))
		StoreVarInst(struct, fRec56[Int32(1)], LoadVarInst(struct, fRec56[Int32(0)]))
		StoreVarInst(struct, fRec57[Int32(2)], LoadVarInst(struct, fRec57[Int32(1)]))
		StoreVarInst(struct, fRec57[Int32(1)], LoadVarInst(struct, fRec57[Int32(0)]))
		StoreVarInst(struct, fRec58[Int32(2)], LoadVarInst(struct, fRec58[Int32(1)]))
		StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
		StoreVarInst(struct, fRec59[Int32(2)], LoadVarInst(struct, fRec59[Int32(1)]))
		StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
		StoreVarInst(struct, fRec60[Int32(2)], LoadVarInst(struct, fRec60[Int32(1)]))
		StoreVarInst(struct, fRec60[Int32(1)], LoadVarInst(struct, fRec60[Int32(0)]))
		StoreVarInst(struct, fRec61[Int32(2)], LoadVarInst(struct, fRec61[Int32(1)]))
		StoreVarInst(struct, fRec61[Int32(1)], LoadVarInst(struct, fRec61[Int32(0)]))
		StoreVarInst(struct, fRec62[Int32(2)], LoadVarInst(struct, fRec62[Int32(1)]))
		StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
		StoreVarInst(struct, fRec63[Int32(2)], LoadVarInst(struct, fRec63[Int32(1)]))
		StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
		StoreVarInst(struct, fRec64[Int32(2)], LoadVarInst(struct, fRec64[Int32(1)]))
		StoreVarInst(struct, fRec64[Int32(1)], LoadVarInst(struct, fRec64[Int32(0)]))
		StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst(static, float, ftbl0mydspSIG0[250])
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iRec2[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[2048])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, int, iRec14[2])
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, float, fRec13[3])
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, float, fRec11[3])
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, float, fRec16[3])
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, float, fRec18[3])
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, float, fRec19[3])
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, float, fRec21[3])
	DeclareVarInst(struct, "float", fConst43)
	DeclareVarInst(struct, "float", fConst44)
	DeclareVarInst(struct, "float", fConst45)
	DeclareVarInst(struct, "float", fConst46)
	DeclareVarInst(struct, float, fRec22[3])
	DeclareVarInst(struct, "float", fConst47)
	DeclareVarInst(struct, "float", fConst48)
	DeclareVarInst(struct, "float", fConst49)
	DeclareVarInst(struct, "float", fConst50)
	DeclareVarInst(struct, float, fRec23[3])
	DeclareVarInst(struct, "float", fConst51)
	DeclareVarInst(struct, "float", fConst52)
	DeclareVarInst(struct, "float", fConst53)
	DeclareVarInst(struct, "float", fConst54)
	DeclareVarInst(struct, float, fRec24[3])
	DeclareVarInst(struct, "float", fConst55)
	DeclareVarInst(struct, "float", fConst56)
	DeclareVarInst(struct, "float", fConst57)
	DeclareVarInst(struct, "float", fConst58)
	DeclareVarInst(struct, float, fRec25[3])
	DeclareVarInst(struct, "float", fConst59)
	DeclareVarInst(struct, "float", fConst60)
	DeclareVarInst(struct, "float", fConst61)
	DeclareVarInst(struct, "float", fConst62)
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, "float", fConst63)
	DeclareVarInst(struct, "float", fConst64)
	DeclareVarInst(struct, "float", fConst65)
	DeclareVarInst(struct, "float", fConst66)
	DeclareVarInst(struct, float, fRec27[3])
	DeclareVarInst(struct, "float", fConst67)
	DeclareVarInst(struct, "float", fConst68)
	DeclareVarInst(struct, "float", fConst69)
	DeclareVarInst(struct, "float", fConst70)
	DeclareVarInst(struct, float, fRec28[3])
	DeclareVarInst(struct, "float", fConst71)
	DeclareVarInst(struct, "float", fConst72)
	DeclareVarInst(struct, "float", fConst73)
	DeclareVarInst(struct, "float", fConst74)
	DeclareVarInst(struct, float, fRec29[3])
	DeclareVarInst(struct, "float", fConst75)
	DeclareVarInst(struct, "float", fConst76)
	DeclareVarInst(struct, "float", fConst77)
	DeclareVarInst(struct, "float", fConst78)
	DeclareVarInst(struct, float, fRec30[3])
	DeclareVarInst(struct, "float", fConst79)
	DeclareVarInst(struct, "float", fConst80)
	DeclareVarInst(struct, "float", fConst81)
	DeclareVarInst(struct, "float", fConst82)
	DeclareVarInst(struct, float, fRec31[3])
	DeclareVarInst(struct, "float", fConst83)
	DeclareVarInst(struct, "float", fConst84)
	DeclareVarInst(struct, "float", fConst85)
	DeclareVarInst(struct, "float", fConst86)
	DeclareVarInst(struct, float, fRec32[3])
	DeclareVarInst(struct, "float", fConst87)
	DeclareVarInst(struct, "float", fConst88)
	DeclareVarInst(struct, "float", fConst89)
	DeclareVarInst(struct, "float", fConst90)
	DeclareVarInst(struct, float, fRec33[3])
	DeclareVarInst(struct, "float", fConst91)
	DeclareVarInst(struct, "float", fConst92)
	DeclareVarInst(struct, "float", fConst93)
	DeclareVarInst(struct, "float", fConst94)
	DeclareVarInst(struct, float, fRec34[3])
	DeclareVarInst(struct, "float", fConst95)
	DeclareVarInst(struct, "float", fConst96)
	DeclareVarInst(struct, "float", fConst97)
	DeclareVarInst(struct, "float", fConst98)
	DeclareVarInst(struct, float, fRec35[3])
	DeclareVarInst(struct, "float", fConst99)
	DeclareVarInst(struct, "float", fConst100)
	DeclareVarInst(struct, "float", fConst101)
	DeclareVarInst(struct, "float", fConst102)
	DeclareVarInst(struct, float, fRec36[3])
	DeclareVarInst(struct, "float", fConst103)
	DeclareVarInst(struct, "float", fConst104)
	DeclareVarInst(struct, "float", fConst105)
	DeclareVarInst(struct, "float", fConst106)
	DeclareVarInst(struct, float, fRec37[3])
	DeclareVarInst(struct, "float", fConst107)
	DeclareVarInst(struct, "float", fConst108)
	DeclareVarInst(struct, "float", fConst109)
	DeclareVarInst(struct, "float", fConst110)
	DeclareVarInst(struct, float, fRec38[3])
	DeclareVarInst(struct, "float", fConst111)
	DeclareVarInst(struct, "float", fConst112)
	DeclareVarInst(struct, "float", fConst113)
	DeclareVarInst(struct, "float", fConst114)
	DeclareVarInst(struct, float, fRec39[3])
	DeclareVarInst(struct, "float", fConst115)
	DeclareVarInst(struct, "float", fConst116)
	DeclareVarInst(struct, "float", fConst117)
	DeclareVarInst(struct, "float", fConst118)
	DeclareVarInst(struct, float, fRec40[3])
	DeclareVarInst(struct, "float", fConst119)
	DeclareVarInst(struct, "float", fConst120)
	DeclareVarInst(struct, "float", fConst121)
	DeclareVarInst(struct, "float", fConst122)
	DeclareVarInst(struct, float, fRec41[3])
	DeclareVarInst(struct, "float", fConst123)
	DeclareVarInst(struct, "float", fConst124)
	DeclareVarInst(struct, "float", fConst125)
	DeclareVarInst(struct, "float", fConst126)
	DeclareVarInst(struct, float, fRec42[3])
	DeclareVarInst(struct, "float", fConst127)
	DeclareVarInst(struct, "float", fConst128)
	DeclareVarInst(struct, "float", fConst129)
	DeclareVarInst(struct, "float", fConst130)
	DeclareVarInst(struct, float, fRec43[3])
	DeclareVarInst(struct, "float", fConst131)
	DeclareVarInst(struct, "float", fConst132)
	DeclareVarInst(struct, "float", fConst133)
	DeclareVarInst(struct, "float", fConst134)
	DeclareVarInst(struct, float, fRec44[3])
	DeclareVarInst(struct, "float", fConst135)
	DeclareVarInst(struct, "float", fConst136)
	DeclareVarInst(struct, "float", fConst137)
	DeclareVarInst(struct, "float", fConst138)
	DeclareVarInst(struct, float, fRec45[3])
	DeclareVarInst(struct, "float", fConst139)
	DeclareVarInst(struct, "float", fConst140)
	DeclareVarInst(struct, "float", fConst141)
	DeclareVarInst(struct, "float", fConst142)
	DeclareVarInst(struct, float, fRec46[3])
	DeclareVarInst(struct, "float", fConst143)
	DeclareVarInst(struct, "float", fConst144)
	DeclareVarInst(struct, "float", fConst145)
	DeclareVarInst(struct, "float", fConst146)
	DeclareVarInst(struct, float, fRec47[3])
	DeclareVarInst(struct, "float", fConst147)
	DeclareVarInst(struct, "float", fConst148)
	DeclareVarInst(struct, "float", fConst149)
	DeclareVarInst(struct, "float", fConst150)
	DeclareVarInst(struct, float, fRec48[3])
	DeclareVarInst(struct, "float", fConst151)
	DeclareVarInst(struct, "float", fConst152)
	DeclareVarInst(struct, "float", fConst153)
	DeclareVarInst(struct, "float", fConst154)
	DeclareVarInst(struct, float, fRec49[3])
	DeclareVarInst(struct, "float", fConst155)
	DeclareVarInst(struct, "float", fConst156)
	DeclareVarInst(struct, "float", fConst157)
	DeclareVarInst(struct, "float", fConst158)
	DeclareVarInst(struct, float, fRec50[3])
	DeclareVarInst(struct, "float", fConst159)
	DeclareVarInst(struct, "float", fConst160)
	DeclareVarInst(struct, "float", fConst161)
	DeclareVarInst(struct, "float", fConst162)
	DeclareVarInst(struct, float, fRec51[3])
	DeclareVarInst(struct, "float", fConst163)
	DeclareVarInst(struct, "float", fConst164)
	DeclareVarInst(struct, "float", fConst165)
	DeclareVarInst(struct, "float", fConst166)
	DeclareVarInst(struct, float, fRec52[3])
	DeclareVarInst(struct, "float", fConst167)
	DeclareVarInst(struct, "float", fConst168)
	DeclareVarInst(struct, "float", fConst169)
	DeclareVarInst(struct, "float", fConst170)
	DeclareVarInst(struct, float, fRec53[3])
	DeclareVarInst(struct, "float", fConst171)
	DeclareVarInst(struct, "float", fConst172)
	DeclareVarInst(struct, "float", fConst173)
	DeclareVarInst(struct, "float", fConst174)
	DeclareVarInst(struct, float, fRec54[3])
	DeclareVarInst(struct, "float", fConst175)
	DeclareVarInst(struct, "float", fConst176)
	DeclareVarInst(struct, "float", fConst177)
	DeclareVarInst(struct, "float", fConst178)
	DeclareVarInst(struct, float, fRec55[3])
	DeclareVarInst(struct, "float", fConst179)
	DeclareVarInst(struct, "float", fConst180)
	DeclareVarInst(struct, "float", fConst181)
	DeclareVarInst(struct, "float", fConst182)
	DeclareVarInst(struct, float, fRec56[3])
	DeclareVarInst(struct, "float", fConst183)
	DeclareVarInst(struct, "float", fConst184)
	DeclareVarInst(struct, "float", fConst185)
	DeclareVarInst(struct, "float", fConst186)
	DeclareVarInst(struct, float, fRec57[3])
	DeclareVarInst(struct, "float", fConst187)
	DeclareVarInst(struct, "float", fConst188)
	DeclareVarInst(struct, "float", fConst189)
	DeclareVarInst(struct, "float", fConst190)
	DeclareVarInst(struct, float, fRec58[3])
	DeclareVarInst(struct, "float", fConst191)
	DeclareVarInst(struct, "float", fConst192)
	DeclareVarInst(struct, "float", fConst193)
	DeclareVarInst(struct, "float", fConst194)
	DeclareVarInst(struct, float, fRec59[3])
	DeclareVarInst(struct, "float", fConst195)
	DeclareVarInst(struct, "float", fConst196)
	DeclareVarInst(struct, "float", fConst197)
	DeclareVarInst(struct, "float", fConst198)
	DeclareVarInst(struct, float, fRec60[3])
	DeclareVarInst(struct, "float", fConst199)
	DeclareVarInst(struct, "float", fConst200)
	DeclareVarInst(struct, "float", fConst201)
	DeclareVarInst(struct, "float", fConst202)
	DeclareVarInst(struct, float, fRec61[3])
	DeclareVarInst(struct, "float", fConst203)
	DeclareVarInst(struct, "float", fConst204)
	DeclareVarInst(struct, "float", fConst205)
	DeclareVarInst(struct, "float", fConst206)
	DeclareVarInst(struct, float, fRec62[3])
	DeclareVarInst(struct, "float", fConst207)
	DeclareVarInst(struct, "float", fConst208)
	DeclareVarInst(struct, "float", fConst209)
	DeclareVarInst(struct, "float", fConst210)
	DeclareVarInst(struct, float, fRec63[3])
	DeclareVarInst(struct, "float", fConst211)
	DeclareVarInst(struct, "float", fConst212)
	DeclareVarInst(struct, "float", fConst213)
	DeclareVarInst(struct, "float", fConst214)
	DeclareVarInst(struct, float, fRec64[3])
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, float, fVec4[2048])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec0[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("+", BinopInst("*", Float(0.5f), LoadVarInst(struct, fConst0)), Float(-1.0f)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, FunCallInst("tanf", BinopInst("/", Float(31.415926f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst6, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst6), Float(1.41421354f)), LoadVarInst(struct, fConst5)), Float(1.0f))))
	StoreVarInst(struct, fConst8, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst5))))
	StoreVarInst(struct, fConst9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst6), Float(-1.41421354f)), LoadVarInst(struct, fConst5)), Float(1.0f)))
	StoreVarInst(struct, fConst10, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst8))))
	StoreVarInst(struct, fConst11, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst8))))
	StoreVarInst(struct, fConst12, BinopInst("*", Float(0.00400000019f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst13, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst14, BinopInst("/", Float(500.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst15, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0974743068f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst16, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst15))))
	StoreVarInst(struct, fConst17, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst18, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst15)))
	StoreVarInst(struct, fConst19, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0918262452f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst20, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst19))))
	StoreVarInst(struct, fConst21, BinopInst("/", Float(20.8197117f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst22, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst19)))
	StoreVarInst(struct, fConst23, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0905909166f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst24, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst23))))
	StoreVarInst(struct, fConst25, BinopInst("/", Float(24.0940685f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst26, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst23)))
	StoreVarInst(struct, fConst27, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0810509697f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst28, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst29, BinopInst("/", Float(50.6621399f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst30, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst27)))
	StoreVarInst(struct, fConst31, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0781081766f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst32, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst31))))
	StoreVarInst(struct, fConst33, BinopInst("/", Float(59.3621521f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst34, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst31)))
	StoreVarInst(struct, fConst35, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0688085929f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst36, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst35))))
	StoreVarInst(struct, fConst37, BinopInst("/", Float(88.6990967f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst38, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst35)))
	StoreVarInst(struct, fConst39, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0611052401f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst40, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst39))))
	StoreVarInst(struct, fConst41, BinopInst("/", Float(115.510078f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst42, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst39)))
	StoreVarInst(struct, fConst43, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0567183308f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst44, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst43))))
	StoreVarInst(struct, fConst45, BinopInst("/", Float(132.010986f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst46, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst43)))
	StoreVarInst(struct, fConst47, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0488223769f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst48, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst47))))
	StoreVarInst(struct, fConst49, BinopInst("/", Float(164.478088f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst50, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst47)))
	StoreVarInst(struct, fConst51, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0449043326f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst52, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst51))))
	StoreVarInst(struct, fConst53, BinopInst("/", Float(182.177185f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst54, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst51)))
	StoreVarInst(struct, fConst55, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0350424498f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst56, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst57, BinopInst("/", Float(232.935272f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst58, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst55)))
	StoreVarInst(struct, fConst59, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0341717675f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst60, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst59))))
	StoreVarInst(struct, fConst61, BinopInst("/", Float(237.946106f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst62, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst59)))
	StoreVarInst(struct, fConst63, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.031866312f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst64, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst63))))
	StoreVarInst(struct, fConst65, BinopInst("/", Float(251.725769f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst66, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst63)))
	StoreVarInst(struct, fConst67, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0248362795f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst68, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst67))))
	StoreVarInst(struct, fConst69, BinopInst("/", Float(299.355438f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst70, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst67)))
	StoreVarInst(struct, fConst71, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0221360233f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst72, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst71))))
	StoreVarInst(struct, fConst73, BinopInst("/", Float(320.561829f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst74, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst71)))
	StoreVarInst(struct, fConst75, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0210792925f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst76, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst75))))
	StoreVarInst(struct, fConst77, BinopInst("/", Float(329.427399f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst78, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst75)))
	StoreVarInst(struct, fConst79, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0171158724f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst80, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst79))))
	StoreVarInst(struct, fConst81, BinopInst("/", Float(366.221741f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst82, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst79)))
	StoreVarInst(struct, fConst83, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0140852043f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst84, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst83))))
	StoreVarInst(struct, fConst85, BinopInst("/", Float(399.287628f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst86, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst83)))
	StoreVarInst(struct, fConst87, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000329498813f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst88, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst87))))
	StoreVarInst(struct, fConst89, BinopInst("/", Float(838.660706f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst90, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst87)))
	StoreVarInst(struct, fConst91, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000124247395f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst92, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst91))))
	StoreVarInst(struct, fConst93, BinopInst("/", Float(908.228149f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst94, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst91)))
	StoreVarInst(struct, fConst95, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(7.53835775e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst96, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst95))))
	StoreVarInst(struct, fConst97, BinopInst("/", Float(938.946655f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst98, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst95)))
	StoreVarInst(struct, fConst99, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(5.65755508e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst100, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst99))))
	StoreVarInst(struct, fConst101, BinopInst("/", Float(955.251526f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst102, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst99)))
	StoreVarInst(struct, fConst103, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(4.96453904e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst104, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst103))))
	StoreVarInst(struct, fConst105, BinopInst("/", Float(962.370361f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst106, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst103)))
	StoreVarInst(struct, fConst107, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(3.7056674e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst108, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst107))))
	StoreVarInst(struct, fConst109, BinopInst("/", Float(977.644775f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst110, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst107)))
	StoreVarInst(struct, fConst111, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(2.66114275e-05f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst112, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst111))))
	StoreVarInst(struct, fConst113, BinopInst("/", Float(993.893127f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst114, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst111)))
	StoreVarInst(struct, fConst115, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0131463278f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst116, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst115))))
	StoreVarInst(struct, fConst117, BinopInst("/", Float(410.686584f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst118, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst115)))
	StoreVarInst(struct, fConst119, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0123624494f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst120, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst119))))
	StoreVarInst(struct, fConst121, BinopInst("/", Float(420.713928f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst122, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst119)))
	StoreVarInst(struct, fConst123, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00913601927f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst124, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst123))))
	StoreVarInst(struct, fConst125, BinopInst("/", Float(468.286438f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst126, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst123)))
	StoreVarInst(struct, fConst127, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00767402584f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst128, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst127))))
	StoreVarInst(struct, fConst129, BinopInst("/", Float(494.436432f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst130, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst127)))
	StoreVarInst(struct, fConst131, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00699721137f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst132, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst131))))
	StoreVarInst(struct, fConst133, BinopInst("/", Float(507.916992f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst134, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst131)))
	StoreVarInst(struct, fConst135, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00462675327f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst136, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst135))))
	StoreVarInst(struct, fConst137, BinopInst("/", Float(565.34845f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst138, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst135)))
	StoreVarInst(struct, fConst139, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00401024008f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst140, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst139))))
	StoreVarInst(struct, fConst141, BinopInst("/", Float(584.12323f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst142, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst139)))
	StoreVarInst(struct, fConst143, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00359531236f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst144, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst143))))
	StoreVarInst(struct, fConst145, BinopInst("/", Float(598.105225f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst146, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst143)))
	StoreVarInst(struct, fConst147, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00320503488f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst148, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst147))))
	StoreVarInst(struct, fConst149, BinopInst("/", Float(612.489319f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst150, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst147)))
	StoreVarInst(struct, fConst151, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.0015662252f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst152, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst151))))
	StoreVarInst(struct, fConst153, BinopInst("/", Float(695.045959f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst154, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst151)))
	StoreVarInst(struct, fConst155, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00143769139f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst156, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst155))))
	StoreVarInst(struct, fConst157, BinopInst("/", Float(704.150269f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst158, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst155)))
	StoreVarInst(struct, fConst159, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.00129330496f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst160, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst159))))
	StoreVarInst(struct, fConst161, BinopInst("/", Float(715.18988f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst162, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst159)))
	StoreVarInst(struct, fConst163, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000912711956f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst164, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst163))))
	StoreVarInst(struct, fConst165, BinopInst("/", Float(749.935852f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst166, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst163)))
	StoreVarInst(struct, fConst167, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000537810789f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst168, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst167))))
	StoreVarInst(struct, fConst169, BinopInst("/", Float(798.247253f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst170, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst167)))
	StoreVarInst(struct, fConst171, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000432563043f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst172, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst171))))
	StoreVarInst(struct, fConst173, BinopInst("/", Float(816.700989f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst174, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst171)))
	StoreVarInst(struct, fConst175, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(0.000362893392f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst176, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst175))))
	StoreVarInst(struct, fConst177, BinopInst("/", Float(831.007812f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst178, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst175)))
	StoreVarInst(struct, fConst179, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(5.79888183e-06f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst180, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst179))))
	StoreVarInst(struct, fConst181, BinopInst("/", Float(1056.23486f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst182, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst179)))
	StoreVarInst(struct, fConst183, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(2.80919903e-06f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst184, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst183))))
	StoreVarInst(struct, fConst185, BinopInst("/", Float(1079.84705f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst186, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst183)))
	StoreVarInst(struct, fConst187, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(1.5867239e-06f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst188, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst187))))
	StoreVarInst(struct, fConst189, BinopInst("/", Float(1096.1897f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst190, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst187)))
	StoreVarInst(struct, fConst191, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(4.94038545e-07f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst192, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst191))))
	StoreVarInst(struct, fConst193, BinopInst("/", Float(1124.29431f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst194, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst191)))
	StoreVarInst(struct, fConst195, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(2.19791588e-07f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst196, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst195))))
	StoreVarInst(struct, fConst197, BinopInst("/", Float(1140.28503f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst198, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst195)))
	StoreVarInst(struct, fConst199, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(4.53858888e-08f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst200, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst199))))
	StoreVarInst(struct, fConst201, BinopInst("/", Float(1164.89001f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst202, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst199)))
	StoreVarInst(struct, fConst203, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(1.88244775e-09f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst204, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst203))))
	StoreVarInst(struct, fConst205, BinopInst("/", Float(1196.12366f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst206, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst203)))
	StoreVarInst(struct, fConst207, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(2.61844324e-10f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst208, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst207))))
	StoreVarInst(struct, fConst209, BinopInst("/", Float(1207.56543f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst210, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst207)))
	StoreVarInst(struct, fConst211, FunCallInst("powf", Float(0.00100000005f), BinopInst("/", Float(1.0f), BinopInst("*", Float(6.3867631e-15f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst212, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(struct, fConst211))))
	StoreVarInst(struct, fConst213, BinopInst("/", Float(1228.39417f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst214, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst211)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.80000000000000004f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(6500.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.5f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2048))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec14[LoadVarInst(loop, l5)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(3))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(3))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(3))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(3))
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
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(3))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(3))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(3))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(3))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(3))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(3))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(3))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(3))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(3))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(3))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(3))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(3))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(3))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(3))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(3))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(3))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(3))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(3))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(3))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(3))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(3))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(3))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(3))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(3))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(3))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(3))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(3))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(3))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(3))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(3))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec56[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(3))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec57[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(3))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(3))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(3))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(3))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(3))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(3))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(3))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l60)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(2))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(2048))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(2))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(2))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l64)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	DeclareVarInst(stack, mydspSIG0, sig0, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(stack, sig0), LoadVarInst(kFunArgs, samplingFreq)))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(250), LoadVarInst(static, ftbl0mydspSIG0)))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst(static, float, fmydspSIG0Wave0[250], {1.0f,0.776724994f,0.625723004f,0.855223f,0.760159016f,0.69837302f,0.768010974f,0.64112699f,0.244034007f,0.707754016f,0.634012997f,0.247527003f,0.660848975f,0.450396001f,0.567782998f,0.106361002f,0.716813982f,0.663919985f,0.291207999f,0.310598999f,0.801495016f,0.635291994f,0.307435006f,0.874123991f,0.497667998f,0.487087995f,0.459114999f,0.733455002f,0.541818023f,0.441318005f,0.313919991f,0.40309f,0.685352981f,0.603139997f,0.400552005f,0.453511f,0.634386003f,0.291547f,0.131604999f,0.368506998f,0.839906991f,0.602159977f,0.288296014f,0.579670012f,0.0242493004f,0.262746006f,0.368588001f,0.890284002f,0.408962995f,0.556071997f,0.884427011f,0.832109988f,0.612015009f,0.757175982f,0.919476986f,1.0f,0.827962995f,0.89240998f,0.0357408002f,0.480789006f,0.75287199f,0.0546301007f,0.235936999f,0.362937987f,0.444471985f,0.101751f,0.703418016f,0.453135997f,0.316628993f,0.490393996f,0.982508004f,0.551621974f,0.602008998f,0.666957021f,0.776830018f,0.905662f,0.0987197012f,0.402967989f,0.829451978f,0.307644993f,0.640479982f,0.983971f,0.584204972f,0.650364995f,0.334446996f,0.583570004f,0.540190995f,0.672533989f,0.245711997f,0.687298f,0.883058012f,0.792949975f,0.600619018f,0.572682023f,0.122612f,0.388247997f,0.290657997f,0.380255014f,0.290966988f,0.567818999f,0.0737721026f,0.42098999f,0.0786577985f,0.393994987f,0.268983006f,0.260614008f,0.494085997f,0.238025993f,0.0987823978f,0.277879f,0.440562993f,0.0770211965f,0.450590998f,0.128137007f,0.0368275009f,0.128699005f,0.329605013f,0.374511987f,0.363590002f,0.272594005f,0.379052013f,0.305240989f,0.0741128996f,0.34572801f,0.299349993f,0.221284002f,0.0261390992f,0.293202013f,0.361885011f,0.114330001f,0.239004999f,0.434156001f,0.329582989f,0.219459996f,0.284175009f,0.198554993f,0.431975991f,0.302985013f,1.0f,0.146220997f,0.140700996f,0.264243007f,0.185996994f,0.426322013f,0.304780006f,0.343989998f,0.195429996f,0.386954993f,0.187600002f,0.172812f,0.0434115008f,0.303761005f,0.0694539994f,0.453943014f,0.832450986f,0.317817003f,0.940600991f,1.0f,0.180657998f,0.737921f,0.832297027f,0.402352005f,0.126785994f,0.594398022f,0.485455006f,0.324470013f,0.365101993f,0.777921975f,0.588271976f,0.401353002f,0.610734999f,0.158693001f,0.0746072009f,0.825098991f,0.925459027f,0.65377003f,0.260791987f,0.719384015f,0.559907973f,0.372590005f,0.360035002f,0.622938991f,0.210271001f,0.444595009f,0.311286002f,0.464309007f,0.557231009f,0.524079978f,0.0701055974f,0.320749015f,0.194460005f,0.727608979f,0.522062004f,0.394003987f,0.235035002f,0.395646006f,0.494796008f,0.51731801f,0.109751999f,0.69284898f,0.00632009003f,0.0207582992f,0.00306107011f,0.0637191013f,0.0816610008f,0.0351100005f,0.127813995f,0.202294007f,0.0764145032f,0.263126999f,0.400198996f,0.267277986f,0.633385003f,1.0f,0.73990202f,0.413762987f,0.418110013f,0.612715006f,0.67237401f,0.339673996f,0.211720005f,0.459645003f,0.102499999f,0.325890005f,0.148154005f,0.265442014f,0.0974304974f,0.286437988f,0.275213003f,0.109111004f,0.575088978f,0.370283008f,0.29411f,0.259826005f,0.0648718998f,0.583418012f,0.282662988f,0.182004005f,0.117421001f,0.417726994f,0.169650003f,0.24853f,0.122818999f,0.185486004f,0.0433618017f,0.373849005f,0.25276801f,0.195103005f,0.0927835032f,0.166543007f})
	DeclareVarInst(struct, "int", fmydspSIG0Wave0_idx)
	========== Init method ==========
	StoreVarInst(struct, fmydspSIG0Wave0_idx, Int32(0))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], LoadVarInst(static, fmydspSIG0Wave0[LoadVarInst(struct, fmydspSIG0Wave0_idx)]))
			StoreVarInst(struct, fmydspSIG0Wave0_idx, BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(struct, fmydspSIG0Wave0_idx)), Int32(250)))
			EndBlock
		EndForLoop
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("/", Float(340.0f), LoadVarInst(stack, fSlow1)), Float(-0.0399999991f))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("+", LoadVarInst(stack, fSlow2), Float(-1.49999499f)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("floorf", LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow5)), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fSlow6)))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fSlow7)))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fSlow8)))))
	DeclareVarInst(stack, "int", iSlow10, CastInst("int", LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "int", iSlow11, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iSlow10))))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", BinopInst("*", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow6)), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fSlow7)))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fSlow8)))))
	DeclareVarInst(stack, "int", iSlow14, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow10), Int32(1)))))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow7))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fSlow8))))))
	DeclareVarInst(stack, "int", iSlow16, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow10), Int32(2)))))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("*", Float(0.166666672f), BinopInst("*", LoadVarInst(stack, fSlow17), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow8)))))
	DeclareVarInst(stack, "int", iSlow19, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow10), Int32(3)))))))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(stack, fSlow7))))
	DeclareVarInst(stack, "int", iSlow21, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst2), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow10), Int32(4)))))))
	DeclareVarInst(stack, "int", iSlow22, BinopInst("*", Int32(50), CastInst("int", CastInst("float", LoadVarInst(struct, fEntry0)))))
	DeclareVarInst(stack, "float", fSlow23, Select2Inst(BinopInst("<", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iSlow22)]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow24, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), CastInst("float", LoadVarInst(struct, fHslider3)))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow24)))
	DeclareVarInst(stack, "float", fSlow26, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow25), Float(1.41421354f)), LoadVarInst(stack, fSlow24)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("/", CastInst("float", LoadVarInst(struct, fHslider2)), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow26)))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow24))))))
	DeclareVarInst(stack, "float", fSlow30, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow25), Float(-1.41421354f)), LoadVarInst(stack, fSlow24)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow31, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow32, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "float", fSlow33, BinopInst("*", LoadVarInst(struct, fConst12), LoadVarInst(stack, fSlow32)))
	DeclareVarInst(stack, "float", fSlow34, BinopInst("*", LoadVarInst(struct, fConst13), LoadVarInst(stack, fSlow32)))
	DeclareVarInst(stack, "float", fSlow35, BinopInst("/", LoadVarInst(struct, fConst14), LoadVarInst(stack, fSlow32)))
	DeclareVarInst(stack, "float", fSlow36, BinopInst("*", LoadVarInst(struct, fConst16), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst17), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow37, Select2Inst(BinopInst("<", BinopInst("*", Float(3.31356001f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(1))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow38, BinopInst("*", LoadVarInst(struct, fConst20), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst21), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow39, Select2Inst(BinopInst("<", BinopInst("*", Float(3.83469009f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(2))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow40, BinopInst("*", LoadVarInst(struct, fConst24), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst25), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow41, Select2Inst(BinopInst("<", BinopInst("*", Float(8.06313038f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(3))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow42, BinopInst("*", LoadVarInst(struct, fConst28), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst29), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow43, Select2Inst(BinopInst("<", BinopInst("*", Float(9.44777966f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(4))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow44, BinopInst("*", LoadVarInst(struct, fConst32), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst33), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow45, Select2Inst(BinopInst("<", BinopInst("*", Float(14.1169004f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(5))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow46, BinopInst("*", LoadVarInst(struct, fConst36), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow47, Select2Inst(BinopInst("<", BinopInst("*", Float(18.3840008f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(6))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow48, BinopInst("*", LoadVarInst(struct, fConst40), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst41), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow49, Select2Inst(BinopInst("<", BinopInst("*", Float(21.0102005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(7))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow50, BinopInst("*", LoadVarInst(struct, fConst44), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst45), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow51, Select2Inst(BinopInst("<", BinopInst("*", Float(26.1774998f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(8))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow52, BinopInst("*", LoadVarInst(struct, fConst48), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow53, Select2Inst(BinopInst("<", BinopInst("*", Float(28.9944f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(9))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow54, BinopInst("*", LoadVarInst(struct, fConst52), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst53), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow55, Select2Inst(BinopInst("<", BinopInst("*", Float(37.0727997f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(10))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow56, BinopInst("*", LoadVarInst(struct, fConst56), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst57), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow57, Select2Inst(BinopInst("<", BinopInst("*", Float(37.8703003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(11))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow58, BinopInst("*", LoadVarInst(struct, fConst60), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst61), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow59, Select2Inst(BinopInst("<", BinopInst("*", Float(40.0634003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(12))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow60, BinopInst("*", LoadVarInst(struct, fConst64), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow61, Select2Inst(BinopInst("<", BinopInst("*", Float(47.6439018f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(13))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow62, BinopInst("*", LoadVarInst(struct, fConst68), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst69), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow63, Select2Inst(BinopInst("<", BinopInst("*", Float(51.019001f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(14))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow64, BinopInst("*", LoadVarInst(struct, fConst72), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst73), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow65, Select2Inst(BinopInst("<", BinopInst("*", Float(52.4300003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(15))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow66, BinopInst("*", LoadVarInst(struct, fConst76), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow67, Select2Inst(BinopInst("<", BinopInst("*", Float(58.2859993f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(16))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow68, BinopInst("*", LoadVarInst(struct, fConst80), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow69, Select2Inst(BinopInst("<", BinopInst("*", Float(63.5485992f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(17))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow70, BinopInst("*", LoadVarInst(struct, fConst84), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow71, Select2Inst(BinopInst("<", BinopInst("*", Float(133.477005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(34))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow72, BinopInst("*", LoadVarInst(struct, fConst88), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst89), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow73, Select2Inst(BinopInst("<", BinopInst("*", Float(144.548996f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(35))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow74, BinopInst("*", LoadVarInst(struct, fConst92), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst93), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow75, Select2Inst(BinopInst("<", BinopInst("*", Float(149.438004f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(36))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow76, BinopInst("*", LoadVarInst(struct, fConst96), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow77, Select2Inst(BinopInst("<", BinopInst("*", Float(152.033005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(37))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow78, BinopInst("*", LoadVarInst(struct, fConst100), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow79, Select2Inst(BinopInst("<", BinopInst("*", Float(153.166f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(38))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow80, BinopInst("*", LoadVarInst(struct, fConst104), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow81, Select2Inst(BinopInst("<", BinopInst("*", Float(155.597f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(39))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow82, BinopInst("*", LoadVarInst(struct, fConst108), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst109), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow83, Select2Inst(BinopInst("<", BinopInst("*", Float(158.182999f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(40))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow84, BinopInst("*", LoadVarInst(struct, fConst112), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow85, Select2Inst(BinopInst("<", BinopInst("*", Float(65.3628006f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(18))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow86, BinopInst("*", LoadVarInst(struct, fConst116), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst117), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow87, Select2Inst(BinopInst("<", BinopInst("*", Float(66.9587021f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(19))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow88, BinopInst("*", LoadVarInst(struct, fConst120), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow89, Select2Inst(BinopInst("<", BinopInst("*", Float(74.530098f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(20))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow90, BinopInst("*", LoadVarInst(struct, fConst124), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst125), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow91, Select2Inst(BinopInst("<", BinopInst("*", Float(78.6920013f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(21))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow92, BinopInst("*", LoadVarInst(struct, fConst128), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst129), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow93, Select2Inst(BinopInst("<", BinopInst("*", Float(80.8375015f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(22))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow94, BinopInst("*", LoadVarInst(struct, fConst132), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst133), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow95, Select2Inst(BinopInst("<", BinopInst("*", Float(89.9779968f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(23))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow96, BinopInst("*", LoadVarInst(struct, fConst136), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst137), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow97, Select2Inst(BinopInst("<", BinopInst("*", Float(92.9661026f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(24))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow98, BinopInst("*", LoadVarInst(struct, fConst140), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst141), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow99, Select2Inst(BinopInst("<", BinopInst("*", Float(95.1913986f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(25))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow100, BinopInst("*", LoadVarInst(struct, fConst144), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst145), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow101, Select2Inst(BinopInst("<", BinopInst("*", Float(97.4806976f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(26))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow102, BinopInst("*", LoadVarInst(struct, fConst148), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst149), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow103, Select2Inst(BinopInst("<", BinopInst("*", Float(110.620003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(27))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow104, BinopInst("*", LoadVarInst(struct, fConst152), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst153), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow105, Select2Inst(BinopInst("<", BinopInst("*", Float(112.069f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(28))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow106, BinopInst("*", LoadVarInst(struct, fConst156), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst157), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow107, Select2Inst(BinopInst("<", BinopInst("*", Float(113.825996f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(29))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow108, BinopInst("*", LoadVarInst(struct, fConst160), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst161), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow109, Select2Inst(BinopInst("<", BinopInst("*", Float(119.356003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(30))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow110, BinopInst("*", LoadVarInst(struct, fConst164), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst165), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow111, Select2Inst(BinopInst("<", BinopInst("*", Float(127.044998f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(31))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow112, BinopInst("*", LoadVarInst(struct, fConst168), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst169), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow113, Select2Inst(BinopInst("<", BinopInst("*", Float(129.981995f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(32))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow114, BinopInst("*", LoadVarInst(struct, fConst172), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst173), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow115, Select2Inst(BinopInst("<", BinopInst("*", Float(132.259003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(33))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow116, BinopInst("*", LoadVarInst(struct, fConst176), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst177), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow117, Select2Inst(BinopInst("<", BinopInst("*", Float(168.104996f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(41))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow118, BinopInst("*", LoadVarInst(struct, fConst180), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst181), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow119, Select2Inst(BinopInst("<", BinopInst("*", Float(171.863007f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(42))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow120, BinopInst("*", LoadVarInst(struct, fConst184), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst185), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow121, Select2Inst(BinopInst("<", BinopInst("*", Float(174.464005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(43))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow122, BinopInst("*", LoadVarInst(struct, fConst188), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst189), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow123, Select2Inst(BinopInst("<", BinopInst("*", Float(178.936996f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(44))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow124, BinopInst("*", LoadVarInst(struct, fConst192), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst193), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow125, Select2Inst(BinopInst("<", BinopInst("*", Float(181.481995f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(45))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow126, BinopInst("*", LoadVarInst(struct, fConst196), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst197), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow127, Select2Inst(BinopInst("<", BinopInst("*", Float(185.397995f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(46))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow128, BinopInst("*", LoadVarInst(struct, fConst200), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst201), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow129, Select2Inst(BinopInst("<", BinopInst("*", Float(190.369003f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(47))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow130, BinopInst("*", LoadVarInst(struct, fConst204), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst205), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow131, Select2Inst(BinopInst("<", BinopInst("*", Float(192.190002f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(48))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow132, BinopInst("*", LoadVarInst(struct, fConst208), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst209), LoadVarInst(stack, fSlow1)))))
	DeclareVarInst(stack, "float", fSlow133, Select2Inst(BinopInst("<", BinopInst("*", Float(195.505005f), LoadVarInst(stack, fSlow1)), LoadVarInst(struct, fConst3)) LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iSlow22), Int32(49))]) Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow134, BinopInst("*", LoadVarInst(struct, fConst212), FunCallInst("cosf", BinopInst("*", LoadVarInst(struct, fConst213), LoadVarInst(stack, fSlow1)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[Int32(0)], Int32(0))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec7[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("+", BinopInst("*", Float(0.99000001f), LoadVarInst(struct, fRec9[Int32(0)])), CastInst("float", LoadVarInst(struct, iRec2[Int32(1)]))))
			StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp0))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow11)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow14)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow16)), Int32(2047))]))), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow19)), Int32(2047))]))), BinopInst("*", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow21)), Int32(2047))]))))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec6[Int32(1)]))))
			StoreVarInst(struct, iRec14[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec14[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec14[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec13[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst10), LoadVarInst(struct, fRec13[Int32(1)]))))))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec13[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst11), LoadVarInst(struct, fRec13[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec13[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow28), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow30), LoadVarInst(struct, fRec12[Int32(2)]))))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow31))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fSlow32))
			StoreVarInst(struct, fRec15[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow31), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fSlow33), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec15[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst12), BinopInst("-", LoadVarInst(stack, fSlow32), LoadVarInst(struct, fVec2[Int32(1)])))), Float(1.0f)))))
			DeclareVarInst(stack, "int", iTemp1, BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fSlow34)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow27), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec12[Int32(1)])), LoadVarInst(struct, fRec12[Int32(0)]))), Select2Inst(LoadVarInst(stack, iTemp1) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp1) BinopInst("*", LoadVarInst(stack, fSlow35), LoadVarInst(struct, fRec15[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fSlow33)) BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow35), BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fSlow34)))), Float(1.0f)) Float(0.0f))))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow36), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec11[Int32(2)])))))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow38), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst22), LoadVarInst(struct, fRec16[Int32(2)])))))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow40), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst26), LoadVarInst(struct, fRec17[Int32(2)])))))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow42), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(struct, fRec18[Int32(2)])))))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow44), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst34), LoadVarInst(struct, fRec19[Int32(2)])))))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow46), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fRec20[Int32(2)])))))
			StoreVarInst(struct, fRec21[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow48), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec21[Int32(2)])))))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow50), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst46), LoadVarInst(struct, fRec22[Int32(2)])))))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow52), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst50), LoadVarInst(struct, fRec23[Int32(2)])))))
			StoreVarInst(struct, fRec24[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow54), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst54), LoadVarInst(struct, fRec24[Int32(2)])))))
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow56), LoadVarInst(struct, fRec25[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst58), LoadVarInst(struct, fRec25[Int32(2)])))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow58), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst62), LoadVarInst(struct, fRec26[Int32(2)])))))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow60), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst66), LoadVarInst(struct, fRec27[Int32(2)])))))
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow62), LoadVarInst(struct, fRec28[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst70), LoadVarInst(struct, fRec28[Int32(2)])))))
			StoreVarInst(struct, fRec29[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow64), LoadVarInst(struct, fRec29[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst74), LoadVarInst(struct, fRec29[Int32(2)])))))
			StoreVarInst(struct, fRec30[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow66), LoadVarInst(struct, fRec30[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec30[Int32(2)])))))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow68), LoadVarInst(struct, fRec31[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec31[Int32(2)])))))
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow70), LoadVarInst(struct, fRec32[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec32[Int32(2)])))))
			StoreVarInst(struct, fRec33[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow72), LoadVarInst(struct, fRec33[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst90), LoadVarInst(struct, fRec33[Int32(2)])))))
			StoreVarInst(struct, fRec34[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow74), LoadVarInst(struct, fRec34[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst94), LoadVarInst(struct, fRec34[Int32(2)])))))
			StoreVarInst(struct, fRec35[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow76), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec35[Int32(2)])))))
			StoreVarInst(struct, fRec36[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow78), LoadVarInst(struct, fRec36[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec36[Int32(2)])))))
			StoreVarInst(struct, fRec37[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow80), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec37[Int32(2)])))))
			StoreVarInst(struct, fRec38[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow82), LoadVarInst(struct, fRec38[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst110), LoadVarInst(struct, fRec38[Int32(2)])))))
			StoreVarInst(struct, fRec39[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow84), LoadVarInst(struct, fRec39[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst114), LoadVarInst(struct, fRec39[Int32(2)])))))
			StoreVarInst(struct, fRec40[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow86), LoadVarInst(struct, fRec40[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst118), LoadVarInst(struct, fRec40[Int32(2)])))))
			StoreVarInst(struct, fRec41[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow88), LoadVarInst(struct, fRec41[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst122), LoadVarInst(struct, fRec41[Int32(2)])))))
			StoreVarInst(struct, fRec42[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow90), LoadVarInst(struct, fRec42[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst126), LoadVarInst(struct, fRec42[Int32(2)])))))
			StoreVarInst(struct, fRec43[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow92), LoadVarInst(struct, fRec43[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst130), LoadVarInst(struct, fRec43[Int32(2)])))))
			StoreVarInst(struct, fRec44[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow94), LoadVarInst(struct, fRec44[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec44[Int32(2)])))))
			StoreVarInst(struct, fRec45[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow96), LoadVarInst(struct, fRec45[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec45[Int32(2)])))))
			StoreVarInst(struct, fRec46[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow98), LoadVarInst(struct, fRec46[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec46[Int32(2)])))))
			StoreVarInst(struct, fRec47[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow100), LoadVarInst(struct, fRec47[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst146), LoadVarInst(struct, fRec47[Int32(2)])))))
			StoreVarInst(struct, fRec48[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow102), LoadVarInst(struct, fRec48[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst150), LoadVarInst(struct, fRec48[Int32(2)])))))
			StoreVarInst(struct, fRec49[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow104), LoadVarInst(struct, fRec49[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst154), LoadVarInst(struct, fRec49[Int32(2)])))))
			StoreVarInst(struct, fRec50[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow106), LoadVarInst(struct, fRec50[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst158), LoadVarInst(struct, fRec50[Int32(2)])))))
			StoreVarInst(struct, fRec51[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow108), LoadVarInst(struct, fRec51[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst162), LoadVarInst(struct, fRec51[Int32(2)])))))
			StoreVarInst(struct, fRec52[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow110), LoadVarInst(struct, fRec52[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst166), LoadVarInst(struct, fRec52[Int32(2)])))))
			StoreVarInst(struct, fRec53[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow112), LoadVarInst(struct, fRec53[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst170), LoadVarInst(struct, fRec53[Int32(2)])))))
			StoreVarInst(struct, fRec54[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow114), LoadVarInst(struct, fRec54[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst174), LoadVarInst(struct, fRec54[Int32(2)])))))
			StoreVarInst(struct, fRec55[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow116), LoadVarInst(struct, fRec55[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst178), LoadVarInst(struct, fRec55[Int32(2)])))))
			StoreVarInst(struct, fRec56[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow118), LoadVarInst(struct, fRec56[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst182), LoadVarInst(struct, fRec56[Int32(2)])))))
			StoreVarInst(struct, fRec57[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow120), LoadVarInst(struct, fRec57[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst186), LoadVarInst(struct, fRec57[Int32(2)])))))
			StoreVarInst(struct, fRec58[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow122), LoadVarInst(struct, fRec58[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst190), LoadVarInst(struct, fRec58[Int32(2)])))))
			StoreVarInst(struct, fRec59[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow124), LoadVarInst(struct, fRec59[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst194), LoadVarInst(struct, fRec59[Int32(2)])))))
			StoreVarInst(struct, fRec60[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow126), LoadVarInst(struct, fRec60[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst198), LoadVarInst(struct, fRec60[Int32(2)])))))
			StoreVarInst(struct, fRec61[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow128), LoadVarInst(struct, fRec61[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst202), LoadVarInst(struct, fRec61[Int32(2)])))))
			StoreVarInst(struct, fRec62[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow130), LoadVarInst(struct, fRec62[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst206), LoadVarInst(struct, fRec62[Int32(2)])))))
			StoreVarInst(struct, fRec63[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow132), LoadVarInst(struct, fRec63[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst210), LoadVarInst(struct, fRec63[Int32(2)])))))
			StoreVarInst(struct, fRec64[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow134), LoadVarInst(struct, fRec64[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst214), LoadVarInst(struct, fRec64[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("-", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(struct, fRec11[Int32(2)]))), BinopInst("*", LoadVarInst(stack, fSlow37), BinopInst("-", LoadVarInst(struct, fRec16[Int32(0)]), LoadVarInst(struct, fRec16[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow39), BinopInst("-", LoadVarInst(struct, fRec17[Int32(0)]), LoadVarInst(struct, fRec17[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow41), BinopInst("-", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fRec18[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow43), BinopInst("-", LoadVarInst(struct, fRec19[Int32(0)]), LoadVarInst(struct, fRec19[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow45), BinopInst("-", LoadVarInst(struct, fRec20[Int32(0)]), LoadVarInst(struct, fRec20[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow47), BinopInst("-", LoadVarInst(struct, fRec21[Int32(0)]), LoadVarInst(struct, fRec21[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow49), BinopInst("-", LoadVarInst(struct, fRec22[Int32(0)]), LoadVarInst(struct, fRec22[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow51), BinopInst("-", LoadVarInst(struct, fRec23[Int32(0)]), LoadVarInst(struct, fRec23[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow53), BinopInst("-", LoadVarInst(struct, fRec24[Int32(0)]), LoadVarInst(struct, fRec24[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow55), BinopInst("-", LoadVarInst(struct, fRec25[Int32(0)]), LoadVarInst(struct, fRec25[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow57), BinopInst("-", LoadVarInst(struct, fRec26[Int32(0)]), LoadVarInst(struct, fRec26[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow59), BinopInst("-", LoadVarInst(struct, fRec27[Int32(0)]), LoadVarInst(struct, fRec27[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow61), BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), LoadVarInst(struct, fRec28[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow63), BinopInst("-", LoadVarInst(struct, fRec29[Int32(0)]), LoadVarInst(struct, fRec29[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow65), BinopInst("-", LoadVarInst(struct, fRec30[Int32(0)]), LoadVarInst(struct, fRec30[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow67), BinopInst("-", LoadVarInst(struct, fRec31[Int32(0)]), LoadVarInst(struct, fRec31[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow69), BinopInst("-", LoadVarInst(struct, fRec32[Int32(0)]), LoadVarInst(struct, fRec32[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow71), BinopInst("-", LoadVarInst(struct, fRec33[Int32(0)]), LoadVarInst(struct, fRec33[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow73), BinopInst("-", LoadVarInst(struct, fRec34[Int32(0)]), LoadVarInst(struct, fRec34[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow75), BinopInst("-", LoadVarInst(struct, fRec35[Int32(0)]), LoadVarInst(struct, fRec35[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow77), BinopInst("-", LoadVarInst(struct, fRec36[Int32(0)]), LoadVarInst(struct, fRec36[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow79), BinopInst("-", LoadVarInst(struct, fRec37[Int32(0)]), LoadVarInst(struct, fRec37[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow81), BinopInst("-", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(struct, fRec38[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow83), BinopInst("-", LoadVarInst(struct, fRec39[Int32(0)]), LoadVarInst(struct, fRec39[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow85), BinopInst("-", LoadVarInst(struct, fRec40[Int32(0)]), LoadVarInst(struct, fRec40[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow87), BinopInst("-", LoadVarInst(struct, fRec41[Int32(0)]), LoadVarInst(struct, fRec41[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow89), BinopInst("-", LoadVarInst(struct, fRec42[Int32(0)]), LoadVarInst(struct, fRec42[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow91), BinopInst("-", LoadVarInst(struct, fRec43[Int32(0)]), LoadVarInst(struct, fRec43[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow93), BinopInst("-", LoadVarInst(struct, fRec44[Int32(0)]), LoadVarInst(struct, fRec44[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow95), BinopInst("-", LoadVarInst(struct, fRec45[Int32(0)]), LoadVarInst(struct, fRec45[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow97), BinopInst("-", LoadVarInst(struct, fRec46[Int32(0)]), LoadVarInst(struct, fRec46[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow99), BinopInst("-", LoadVarInst(struct, fRec47[Int32(0)]), LoadVarInst(struct, fRec47[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow101), BinopInst("-", LoadVarInst(struct, fRec48[Int32(0)]), LoadVarInst(struct, fRec48[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow103), BinopInst("-", LoadVarInst(struct, fRec49[Int32(0)]), LoadVarInst(struct, fRec49[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow105), BinopInst("-", LoadVarInst(struct, fRec50[Int32(0)]), LoadVarInst(struct, fRec50[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow107), BinopInst("-", LoadVarInst(struct, fRec51[Int32(0)]), LoadVarInst(struct, fRec51[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow109), BinopInst("-", LoadVarInst(struct, fRec52[Int32(0)]), LoadVarInst(struct, fRec52[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow111), BinopInst("-", LoadVarInst(struct, fRec53[Int32(0)]), LoadVarInst(struct, fRec53[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow113), BinopInst("-", LoadVarInst(struct, fRec54[Int32(0)]), LoadVarInst(struct, fRec54[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow115), BinopInst("-", LoadVarInst(struct, fRec55[Int32(0)]), LoadVarInst(struct, fRec55[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow117), BinopInst("-", LoadVarInst(struct, fRec56[Int32(0)]), LoadVarInst(struct, fRec56[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow119), BinopInst("-", LoadVarInst(struct, fRec57[Int32(0)]), LoadVarInst(struct, fRec57[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow121), BinopInst("-", LoadVarInst(struct, fRec58[Int32(0)]), LoadVarInst(struct, fRec58[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow123), BinopInst("-", LoadVarInst(struct, fRec59[Int32(0)]), LoadVarInst(struct, fRec59[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow125), BinopInst("-", LoadVarInst(struct, fRec60[Int32(0)]), LoadVarInst(struct, fRec60[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow127), BinopInst("-", LoadVarInst(struct, fRec61[Int32(0)]), LoadVarInst(struct, fRec61[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow129), BinopInst("-", LoadVarInst(struct, fRec62[Int32(0)]), LoadVarInst(struct, fRec62[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow131), BinopInst("-", LoadVarInst(struct, fRec63[Int32(0)]), LoadVarInst(struct, fRec63[Int32(2)])))), BinopInst("*", LoadVarInst(stack, fSlow133), BinopInst("-", LoadVarInst(struct, fRec64[Int32(0)]), LoadVarInst(struct, fRec64[Int32(2)])))))
			StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp3))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("+", BinopInst("*", Float(0.99000001f), LoadVarInst(struct, fRec10[Int32(0)])), BinopInst("*", Float(0.0199999996f), LoadVarInst(struct, fVec3[Int32(1)]))))
			StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp4))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow11)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow14)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow16)), Int32(2047))]))), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow19)), Int32(2047))]))), BinopInst("*", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow21)), Int32(2047))]))))))
			DeclareVarInst(stack, "int", iRec8, Int32(0))
			DeclareVarInst(stack, "float", fRec3, LoadVarInst(struct, fRec6[Int32(0)]))
			DeclareVarInst(stack, "float", fRec4, LoadVarInst(struct, fRec7[Int32(0)]))
			DeclareVarInst(stack, "float", fRec5, BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec8))))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
			DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fRec1)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp5)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp5)))
			StoreVarInst(struct, iRec2[Int32(1)], LoadVarInst(struct, iRec2[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, iRec14[Int32(1)], LoadVarInst(struct, iRec14[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(2)], LoadVarInst(struct, fRec13[Int32(1)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(2)], LoadVarInst(struct, fRec11[Int32(1)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
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
			StoreVarInst(struct, fRec24[Int32(2)], LoadVarInst(struct, fRec24[Int32(1)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(2)], LoadVarInst(struct, fRec25[Int32(1)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(2)], LoadVarInst(struct, fRec27[Int32(1)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(2)], LoadVarInst(struct, fRec28[Int32(1)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec29[Int32(2)], LoadVarInst(struct, fRec29[Int32(1)]))
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(2)], LoadVarInst(struct, fRec30[Int32(1)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fRec31[Int32(2)], LoadVarInst(struct, fRec31[Int32(1)]))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(2)], LoadVarInst(struct, fRec32[Int32(1)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fRec33[Int32(2)], LoadVarInst(struct, fRec33[Int32(1)]))
			StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
			StoreVarInst(struct, fRec34[Int32(2)], LoadVarInst(struct, fRec34[Int32(1)]))
			StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
			StoreVarInst(struct, fRec35[Int32(2)], LoadVarInst(struct, fRec35[Int32(1)]))
			StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
			StoreVarInst(struct, fRec36[Int32(2)], LoadVarInst(struct, fRec36[Int32(1)]))
			StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
			StoreVarInst(struct, fRec37[Int32(2)], LoadVarInst(struct, fRec37[Int32(1)]))
			StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
			StoreVarInst(struct, fRec38[Int32(2)], LoadVarInst(struct, fRec38[Int32(1)]))
			StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
			StoreVarInst(struct, fRec39[Int32(2)], LoadVarInst(struct, fRec39[Int32(1)]))
			StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
			StoreVarInst(struct, fRec40[Int32(2)], LoadVarInst(struct, fRec40[Int32(1)]))
			StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
			StoreVarInst(struct, fRec41[Int32(2)], LoadVarInst(struct, fRec41[Int32(1)]))
			StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
			StoreVarInst(struct, fRec42[Int32(2)], LoadVarInst(struct, fRec42[Int32(1)]))
			StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
			StoreVarInst(struct, fRec43[Int32(2)], LoadVarInst(struct, fRec43[Int32(1)]))
			StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
			StoreVarInst(struct, fRec44[Int32(2)], LoadVarInst(struct, fRec44[Int32(1)]))
			StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
			StoreVarInst(struct, fRec45[Int32(2)], LoadVarInst(struct, fRec45[Int32(1)]))
			StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
			StoreVarInst(struct, fRec46[Int32(2)], LoadVarInst(struct, fRec46[Int32(1)]))
			StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
			StoreVarInst(struct, fRec47[Int32(2)], LoadVarInst(struct, fRec47[Int32(1)]))
			StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
			StoreVarInst(struct, fRec48[Int32(2)], LoadVarInst(struct, fRec48[Int32(1)]))
			StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
			StoreVarInst(struct, fRec49[Int32(2)], LoadVarInst(struct, fRec49[Int32(1)]))
			StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
			StoreVarInst(struct, fRec50[Int32(2)], LoadVarInst(struct, fRec50[Int32(1)]))
			StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
			StoreVarInst(struct, fRec51[Int32(2)], LoadVarInst(struct, fRec51[Int32(1)]))
			StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
			StoreVarInst(struct, fRec52[Int32(2)], LoadVarInst(struct, fRec52[Int32(1)]))
			StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
			StoreVarInst(struct, fRec53[Int32(2)], LoadVarInst(struct, fRec53[Int32(1)]))
			StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
			StoreVarInst(struct, fRec54[Int32(2)], LoadVarInst(struct, fRec54[Int32(1)]))
			StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
			StoreVarInst(struct, fRec55[Int32(2)], LoadVarInst(struct, fRec55[Int32(1)]))
			StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
			StoreVarInst(struct, fRec56[Int32(2)], LoadVarInst(struct, fRec56[Int32(1)]))
			StoreVarInst(struct, fRec56[Int32(1)], LoadVarInst(struct, fRec56[Int32(0)]))
			StoreVarInst(struct, fRec57[Int32(2)], LoadVarInst(struct, fRec57[Int32(1)]))
			StoreVarInst(struct, fRec57[Int32(1)], LoadVarInst(struct, fRec57[Int32(0)]))
			StoreVarInst(struct, fRec58[Int32(2)], LoadVarInst(struct, fRec58[Int32(1)]))
			StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
			StoreVarInst(struct, fRec59[Int32(2)], LoadVarInst(struct, fRec59[Int32(1)]))
			StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
			StoreVarInst(struct, fRec60[Int32(2)], LoadVarInst(struct, fRec60[Int32(1)]))
			StoreVarInst(struct, fRec60[Int32(1)], LoadVarInst(struct, fRec60[Int32(0)]))
			StoreVarInst(struct, fRec61[Int32(2)], LoadVarInst(struct, fRec61[Int32(1)]))
			StoreVarInst(struct, fRec61[Int32(1)], LoadVarInst(struct, fRec61[Int32(0)]))
			StoreVarInst(struct, fRec62[Int32(2)], LoadVarInst(struct, fRec62[Int32(1)]))
			StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
			StoreVarInst(struct, fRec63[Int32(2)], LoadVarInst(struct, fRec63[Int32(1)]))
			StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
			StoreVarInst(struct, fRec64[Int32(2)], LoadVarInst(struct, fRec64[Int32(1)]))
			StoreVarInst(struct, fRec64[Int32(1)], LoadVarInst(struct, fRec64[Int32(0)]))
			StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 16 bytes
Heap size real = 17968 bytes
Heap size = 17996 bytes
Stack size in compute = 556 bytes

