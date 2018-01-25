/* ------------------------------------------------------------
name: "bells"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: c, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


typedef struct Soundfile Soundfile;

#include "gui/CInterface.h"

#ifndef max
// define min and max (the result doesn't matter)
#define max(a,b) (a)
#define min(a,b) (b)
#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdlib.h>

static float fmydspSIG0Wave0[350] = {0.694274008f,0.471697986f,0.172389999f,0.585446f,0.397985995f,0.919579029f,0.531947017f,0.100204997f,0.639469028f,0.672209024f,0.144345f,0.416595012f,0.124108002f,0.380591005f,0.256577998f,0.646031022f,0.852199972f,0.0224376004f,0.382762015f,0.143924996f,0.368690997f,0.430555999f,0.32317999f,0.142956004f,0.274520993f,0.713823974f,0.442793995f,0.352472991f,0.247756004f,0.415152013f,1.0f,0.401868999f,0.197981f,0.279509991f,0.210249007f,0.369740009f,0.369226992f,0.155769005f,0.272368014f,0.335711986f,0.31645f,0.714102983f,0.285780996f,0.220060006f,0.827704012f,0.206341997f,0.180177003f,0.311477989f,0.197606996f,0.575474977f,0.473311007f,0.587231994f,0.502879977f,0.33730799f,0.304513991f,0.429039001f,0.351521999f,0.341372997f,0.175081f,0.561748028f,0.439172f,0.323163986f,0.540517986f,0.536522985f,0.0743864998f,0.213416994f,0.358011991f,0.47449401f,0.310274005f,0.839412987f,0.241372004f,0.202343002f,0.480634004f,0.995684981f,0.373739988f,0.133998007f,0.52067399f,0.207514003f,1.0f,0.101239003f,0.279536009f,0.185984999f,0.436293006f,0.624109983f,0.334518999f,0.283585012f,0.179316998f,0.353846997f,0.449544996f,0.574127972f,0.135171995f,0.538275003f,0.476424009f,0.832903028f,0.164197996f,0.188562006f,0.135977998f,0.390127987f,0.131044999f,0.312065005f,0.142139003f,0.0255900994f,0.266947001f,0.371607006f,0.0168434996f,0.0249467995f,0.508916974f,0.354409993f,0.283347994f,0.628154993f,0.292477995f,0.358350009f,0.342568994f,0.441237003f,0.886699021f,0.0174697991f,0.00641842978f,0.555320024f,0.88012898f,0.0306908991f,0.290080994f,0.248815998f,0.981736004f,0.324624002f,0.213676006f,0.432884991f,0.0981559008f,0.444148988f,0.395554006f,0.525068998f,0.077130802f,0.0488803983f,0.591320992f,0.108043998f,0.443801999f,0.740318f,0.599438012f,0.293092996f,1.0f,0.141662002f,0.910031021f,0.226126f,0.299701989f,0.341472f,0.0568060987f,0.222494006f,0.91871798f,0.199478f,0.216619998f,0.107758999f,0.692323983f,0.556335986f,0.281717986f,0.430831999f,0.341655999f,0.60809499f,0.342128992f,0.31131199f,0.229953006f,0.695087016f,0.0761488974f,0.349817991f,0.361705989f,0.577611029f,0.147797003f,0.327376008f,0.465714991f,0.342902005f,0.521381021f,0.836827993f,0.241111994f,0.284393996f,0.539315999f,0.143408f,0.517019987f,1.0f,0.236335993f,0.480333f,0.676743984f,0.807582021f,0.468620986f,0.236953005f,0.411603987f,0.579250991f,0.425098002f,0.375990003f,0.461176008f,0.276529998f,0.462368011f,0.613004029f,0.666849017f,0.954715014f,0.161506996f,0.170433f,0.290461004f,0.117302999f,0.365132987f,0.233794004f,0.194567993f,0.338874012f,0.523380995f,0.39835f,0.447838992f,0.65289098f,0.157079995f,0.340353996f,0.442169994f,0.338764012f,0.184396997f,0.771606982f,0.160502002f,0.324487001f,0.477499008f,0.831519008f,0.0168763995f,0.154264003f,0.201865003f,0.237785995f,0.390065998f,0.880164027f,0.284233987f,0.162836999f,0.437557012f,0.227845997f,0.399340004f,1.0f,0.158106998f,0.396903008f,0.513028979f,0.676456988f,0.204282001f,0.0895574987f,0.555410028f,0.73248601f,0.125062004f,0.171229005f,0.0816460028f,0.0541394018f,0.396160007f,0.454288006f,0.466863006f,0.928842008f,0.155393004f,0.262849987f,0.113453001f,0.133163005f,0.302020997f,0.612616003f,0.228392005f,0.195617005f,0.287236005f,0.198762f,0.499884009f,0.809139013f,0.00929925032f,0.084029898f,0.286446005f,0.182111993f,0.186043993f,0.754137993f,0.279556006f,0.266948014f,0.494291008f,1.0f,0.321283996f,0.0230981f,0.0375537015f,0.262531012f,0.602204025f,0.489924997f,0.633077025f,0.407409012f,0.422255993f,0.0910641029f,0.357935011f,0.550179005f,0.106192f,0.132366002f,0.376231015f,0.35115099f,0.0420302004f,0.0372182988f,0.696335018f,0.840821028f,0.855234981f,0.249247998f,0.860010982f,0.340481013f,0.285580009f,0.363038987f,0.324122012f,0.515699029f,0.228130996f,0.172591999f,0.0188723002f,0.168243006f,0.995105028f,0.741759002f,0.107092999f,0.0703490004f,0.136636004f,0.0780455023f,0.315748006f,0.502201021f,0.0190421995f,0.0339139998f,0.225723997f,0.160236001f,0.184101f,0.564203024f,0.247317001f,0.284224987f,0.327152997f,0.651443005f,0.593470991f,0.0163899008f,0.0141048003f,0.521130025f,1.0f,0.105108999f,0.530936003f,0.363723993f,0.924808979f,0.250409991f,0.692879975f,0.414121985f,0.0793657973f,0.34781301f,0.441731006f,0.476428002f,0.0808833987f,0.0581637993f,0.557238996f,0.556514978f,0.746083975f,0.582228005f,0.177230999f,0.158425003f,0.850902975f,0.755271018f,0.673614025f,0.317059994f,0.0515386015f,0.201897994f,0.0577937998f,0.232031003f,0.734987974f,0.141593993f,0.267062008f,0.145806998f};

typedef struct {
	
	int fmydspSIG0Wave0_idx;
	
} mydspSIG0;

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)malloc(sizeof(mydspSIG0)); }
static void deletemydspSIG0(mydspSIG0* dsp) { free(dsp); }

int getNumInputsmydspSIG0(mydspSIG0* dsp) {
	return 0;
	
}
int getNumOutputsmydspSIG0(mydspSIG0* dsp) {
	return 1;
	
}
int getInputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

static void instanceInitmydspSIG0(mydspSIG0* dsp, int samplingFreq) {
	dsp->fmydspSIG0Wave0_idx = 0;
	
}

static void fillmydspSIG0(mydspSIG0* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			output[i] = fmydspSIG0Wave0[dsp->fmydspSIG0Wave0_idx];
			dsp->fmydspSIG0Wave0_idx = ((1 + dsp->fmydspSIG0Wave0_idx) % 350);
			
		}
		
	}
	
};

static float fmydspSIG1Wave0[350] = {0.972890019f,0.542393029f,0.495831996f,0.897966027f,0.552366972f,0.557895005f,0.61421299f,0.353693992f,0.436039001f,0.441024005f,0.674912989f,0.566753983f,0.755007982f,0.699029982f,0.164398f,0.910040021f,0.628373027f,0.201718003f,0.429517001f,0.503714979f,0.871173978f,0.106885999f,0.76117301f,0.673601985f,0.291936994f,0.588590026f,0.31527999f,0.41308099f,0.274464011f,0.494062006f,0.696120977f,0.612010002f,0.382757008f,0.995113015f,0.228806004f,0.198449001f,0.595847011f,0.306263f,0.252397001f,0.0883567035f,0.236085996f,1.0f,0.245278001f,0.379388005f,0.198824003f,0.548892021f,0.492763996f,0.42087099f,0.794637024f,0.605633974f,1.0f,0.604158998f,0.399841011f,0.799346983f,0.507187009f,0.509809971f,0.477382988f,0.310225993f,0.426975995f,0.437622994f,0.735711992f,0.630728006f,0.625784993f,0.651167989f,0.277738005f,0.850857973f,0.578078985f,0.645353973f,0.383700013f,0.370597988f,0.78254199f,0.181325004f,0.614391029f,0.740683973f,0.342440993f,0.586185992f,0.286909014f,0.405196995f,0.259214997f,0.566982985f,0.748219013f,0.655897975f,0.368259996f,0.940814018f,0.336156994f,0.413702011f,0.561556995f,0.402175993f,0.117697999f,0.329369009f,0.254570991f,0.870706022f,0.260980994f,0.274122f,0.206247002f,0.645299971f,0.400757998f,0.36362201f,0.636834025f,0.584565997f,0.975602984f,0.616936982f,0.295401007f,0.650447011f,0.464221001f,0.465056986f,0.312467009f,0.238358006f,0.383695006f,0.399673998f,0.753911972f,0.662011981f,0.504267991f,0.599247992f,0.378665f,0.725363016f,0.493214011f,1.0f,0.332836002f,0.265888989f,0.674072981f,0.320401013f,0.440017998f,0.769782007f,0.316419005f,0.529968023f,0.380508989f,0.578675985f,0.249013007f,0.591383994f,0.761717021f,0.687057018f,0.324436992f,0.818863988f,0.505369008f,0.672484994f,0.461782992f,0.426198006f,0.0678874999f,0.43532899f,0.347954988f,0.708393991f,0.293321997f,0.328985989f,0.258253992f,0.893512011f,0.320131004f,0.433553994f,0.459302008f,0.542213023f,0.817241013f,0.516229987f,0.205302f,0.467354f,0.388682991f,0.388215989f,0.171261996f,0.150865003f,0.291720003f,0.311414003f,0.658876002f,0.570647001f,0.38361901f,0.502454996f,0.364113986f,0.532312989f,0.352988988f,1.0f,0.261983991f,0.219591007f,0.544031024f,0.337199003f,0.279172987f,0.668303013f,0.208439007f,0.399230003f,0.418673992f,0.648617983f,0.234133005f,0.504728973f,0.645346999f,0.572851002f,0.232828006f,0.614292026f,0.48527199f,0.666263998f,0.316570014f,0.320354998f,0.191421002f,0.340131015f,0.342069f,0.538371027f,0.281130999f,0.393115014f,0.251394004f,0.890725017f,0.310644001f,0.503700018f,0.299089998f,0.442478001f,0.733128011f,0.455217004f,0.199322f,0.315699011f,0.375856012f,0.376489997f,0.0291450005f,0.0200283006f,0.279578f,0.316799998f,0.655956984f,0.546842992f,0.349665999f,0.470248997f,0.353765011f,0.286794007f,0.180185005f,1.0f,0.210831001f,0.280133009f,0.535853028f,0.376488f,0.153669998f,0.634745002f,0.0510449f,0.485574991f,0.593110979f,0.917883992f,0.380477011f,0.422924995f,0.599372983f,0.311421007f,0.135654002f,0.359954f,0.295747995f,0.474438995f,0.353338987f,0.116742998f,0.45431301f,0.112857997f,0.359310001f,0.483897001f,0.301607996f,0.577341974f,0.262663007f,0.79498601f,0.549579978f,0.808085978f,0.152511001f,0.439590991f,0.535941005f,0.308017999f,0.419836998f,0.579191029f,0.250427991f,0.252119988f,0.102860004f,0.288331985f,0.599678993f,0.665108025f,0.636285007f,0.495234013f,0.251612991f,0.208526999f,0.0939071998f,0.458415002f,0.318951994f,0.235349998f,0.215188995f,0.313412011f,0.0472786985f,0.0386893004f,0.0863358974f,0.222345993f,0.361510992f,0.997036994f,0.238508999f,0.382140011f,1.0f,0.203554004f,0.472086996f,0.509015024f,0.206370994f,0.441013008f,0.794008017f,0.971623003f,0.796383977f,0.55043f,0.687780023f,0.554297984f,0.0436545014f,0.0595576987f,0.214684993f,0.581470013f,0.277319998f,0.36846599f,0.121381998f,0.152739003f,0.0782243982f,0.190496996f,0.31626901f,0.180455998f,0.405196011f,0.518715978f,0.159364998f,0.165808007f,0.194371998f,0.614763975f,0.553415f,0.644793987f,0.441780001f,0.441489995f,0.221588001f,1.0f,0.579370975f,0.606338978f,0.529166996f,0.0214475002f,0.41704601f,0.663151979f,0.894841015f,0.475751996f,0.168289006f,0.468589991f,0.304603994f,0.666369021f,0.308337003f,0.295091003f,0.768944979f,0.350910991f,0.490680009f,0.516583979f,0.40011701f,0.820686996f,0.545485973f,0.709357023f,0.509759009f,0.472005993f,0.152455002f,0.981265008f,0.459134012f,0.698665977f,0.247153997f,0.623252988f,0.255508006f,0.830815017f,0.0887089968f,0.126082003f,0.0770623013f,0.263327986f};

typedef struct {
	
	int fmydspSIG1Wave0_idx;
	
} mydspSIG1;

static mydspSIG1* newmydspSIG1() { return (mydspSIG1*)malloc(sizeof(mydspSIG1)); }
static void deletemydspSIG1(mydspSIG1* dsp) { free(dsp); }

int getNumInputsmydspSIG1(mydspSIG1* dsp) {
	return 0;
	
}
int getNumOutputsmydspSIG1(mydspSIG1* dsp) {
	return 1;
	
}
int getInputRatemydspSIG1(mydspSIG1* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydspSIG1(mydspSIG1* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

static void instanceInitmydspSIG1(mydspSIG1* dsp, int samplingFreq) {
	dsp->fmydspSIG1Wave0_idx = 0;
	
}

static void fillmydspSIG1(mydspSIG1* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			output[i] = fmydspSIG1Wave0[dsp->fmydspSIG1Wave0_idx];
			dsp->fmydspSIG1Wave0_idx = ((1 + dsp->fmydspSIG1Wave0_idx) % 350);
			
		}
		
	}
	
};

static float fmydspSIG2Wave0[350] = {0.761411011f,0.797802985f,0.586057007f,0.225039005f,0.926353991f,0.81387502f,0.529870987f,0.158914998f,0.662515998f,0.308409989f,0.0454785004f,0.55608201f,0.78471297f,0.213035002f,0.956227005f,0.795165002f,0.313508004f,0.158530995f,0.301586002f,0.16832f,0.281266987f,0.154237002f,0.217234999f,0.247238994f,0.522687972f,0.170303002f,0.32061401f,0.154856995f,0.414941013f,0.788363993f,0.713298976f,0.381592005f,0.707010984f,1.0f,0.0106945997f,0.359762996f,0.0746155977f,0.431124002f,0.118052997f,0.527289987f,0.255302995f,0.646854997f,0.201144993f,0.919907987f,0.359389007f,0.253493994f,0.865695f,0.0829263031f,0.222589001f,0.041573599f,0.735773981f,0.769677997f,0.381415993f,0.197542995f,0.682389021f,0.614766002f,0.249524996f,0.289882988f,0.300318986f,0.443690985f,0.275272012f,0.370218009f,0.748790026f,0.161247f,0.634352982f,0.498497993f,0.221988007f,0.350636989f,0.43681699f,0.436462998f,0.525080025f,0.842646003f,0.195324004f,0.224755004f,0.545681f,0.353778005f,0.269044012f,0.327814013f,0.448951989f,0.852304995f,0.380502999f,1.0f,0.458063006f,0.565057993f,0.354635f,0.659528971f,0.449485004f,0.802013993f,0.283446014f,0.521562994f,0.374639004f,0.652112007f,0.181042001f,0.468394011f,0.430115998f,0.157206997f,0.414995015f,0.292737007f,0.487785012f,0.477679998f,0.481445014f,0.556988001f,0.561132014f,0.378264993f,0.291462004f,0.323249996f,0.482602f,0.328247994f,0.196792006f,0.712253988f,0.389806002f,0.307751f,0.792876005f,0.199098006f,0.288837999f,0.146810994f,0.0178443994f,0.394017011f,0.588212013f,0.489226013f,0.701485991f,0.940303028f,0.213191003f,0.0778845027f,0.474462986f,0.609972f,0.163379997f,0.408376008f,0.330864012f,0.889989972f,0.0798100978f,1.0f,0.167172f,0.208727002f,0.227549002f,0.825902998f,0.531897008f,0.580946028f,0.215339005f,0.247318998f,0.268148005f,0.504087985f,0.160954997f,0.170315996f,0.230768993f,0.151190996f,0.0825031027f,0.141328007f,0.288078994f,0.499675989f,0.420354992f,0.487764001f,0.753709972f,0.492247999f,0.181364f,0.205939993f,0.524969995f,0.325641006f,0.236827001f,0.931842029f,0.472981006f,0.312162012f,0.901031971f,0.27047801f,0.167111993f,0.0709697977f,0.166004002f,0.29074499f,0.425893009f,0.403632998f,0.581772029f,0.855693996f,0.0325586982f,0.056835901f,0.241923004f,0.799310029f,0.181961998f,0.530282974f,0.415609986f,1.0f,0.0291501004f,0.831155002f,0.119755f,0.102187999f,0.132036999f,0.766030014f,0.442220986f,0.174899995f,0.142175004f,0.0140794003f,0.4375f,0.851859987f,0.196835995f,0.0907521993f,0.551672995f,0.25652799f,0.0424376987f,0.490363002f,0.108177997f,0.50327599f,0.226584002f,0.312757999f,0.824078977f,0.484120011f,0.0347337984f,0.0619428009f,0.255097002f,0.145273f,0.190358996f,0.995297015f,0.503419995f,0.217574999f,0.793974996f,0.357178986f,0.0409727991f,0.0187931005f,0.414458007f,0.158439994f,0.34623301f,0.0771673024f,0.175110996f,0.380567014f,0.497408986f,0.316163987f,0.488669008f,1.0f,0.420657009f,0.442333013f,0.247060001f,0.796406984f,0.0104146004f,0.227079004f,0.10684f,0.0289872997f,0.767570019f,0.0643121973f,0.0423097983f,0.715521991f,0.472117007f,0.392576993f,0.660432994f,0.803574979f,0.188653007f,0.0191652998f,0.87321198f,0.448718995f,0.0147128003f,0.618966997f,0.307179987f,0.345898986f,0.131393999f,0.193224996f,0.715282977f,0.405620009f,0.0406370014f,0.0503336005f,0.0544330999f,0.0452023f,0.152301997f,0.894549012f,0.443343014f,0.172070995f,0.647666991f,0.328992993f,0.0416014008f,0.0229487997f,0.551070988f,0.42354399f,0.862362027f,0.363525987f,0.769928992f,0.123452f,0.710702002f,0.394894987f,0.556638002f,1.0f,0.450924993f,0.422849f,0.0921870023f,0.413892001f,0.00995371956f,0.321146011f,0.160623997f,0.0300680995f,0.915385008f,0.475499988f,0.506950974f,0.387549013f,0.275590986f,0.468281001f,0.184775993f,0.186837003f,0.188195005f,0.0202785004f,0.697135985f,0.408861995f,0.0116935f,0.349822998f,0.202300996f,0.461378992f,0.0559022985f,0.0582570992f,0.260607988f,0.181875005f,0.0271738991f,0.0249578003f,0.685088992f,0.470384002f,0.283194005f,0.331050009f,0.138348997f,0.338068008f,0.481992006f,0.178241998f,0.0155942002f,0.0110435002f,0.783770978f,0.442707002f,0.616478026f,0.381541997f,0.510891974f,0.0459849983f,0.303119004f,0.0731908977f,0.547715008f,0.348940998f,0.149981007f,0.302157998f,0.284482002f,0.398176998f,0.00413049012f,0.180739f,0.0628390014f,0.0133459f,0.347088009f,0.576370001f,0.240764007f,0.978480995f,0.452755004f,0.529742002f,0.340470999f,0.66228199f,0.444305003f,0.0429900996f,1.0f,0.361939996f,0.0183371995f,0.626892984f,0.552850008f,0.384936005f};

typedef struct {
	
	int fmydspSIG2Wave0_idx;
	
} mydspSIG2;

static mydspSIG2* newmydspSIG2() { return (mydspSIG2*)malloc(sizeof(mydspSIG2)); }
static void deletemydspSIG2(mydspSIG2* dsp) { free(dsp); }

int getNumInputsmydspSIG2(mydspSIG2* dsp) {
	return 0;
	
}
int getNumOutputsmydspSIG2(mydspSIG2* dsp) {
	return 1;
	
}
int getInputRatemydspSIG2(mydspSIG2* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydspSIG2(mydspSIG2* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

static void instanceInitmydspSIG2(mydspSIG2* dsp, int samplingFreq) {
	dsp->fmydspSIG2Wave0_idx = 0;
	
}

static void fillmydspSIG2(mydspSIG2* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			output[i] = fmydspSIG2Wave0[dsp->fmydspSIG2Wave0_idx];
			dsp->fmydspSIG2Wave0_idx = ((1 + dsp->fmydspSIG2Wave0_idx) % 350);
			
		}
		
	}
	
};

static float fmydspSIG3Wave0[350] = {0.925507009f,0.597519994f,0.0965671018f,0.45412001f,0.989772975f,0.593497992f,0.512540996f,0.124241002f,0.705411017f,0.292396009f,0.673398972f,0.302181005f,0.0262340009f,0.286249012f,0.556267023f,1.0f,0.250425994f,0.107711002f,0.427298993f,0.336295009f,0.616257012f,0.214420006f,0.0845293999f,0.231362998f,0.522723973f,0.559113979f,0.348470002f,0.854197025f,0.835575998f,0.735036016f,0.288493991f,0.117122002f,0.409685999f,0.363575011f,0.484943002f,0.170862004f,0.420531005f,0.164793f,0.233847007f,0.861231983f,0.214037001f,0.283461988f,0.173152998f,0.876121998f,0.607809007f,0.294744998f,0.143142f,0.332008988f,0.491878003f,0.626103997f,0.962027013f,0.584298015f,0.213652998f,0.420451999f,0.812328994f,0.545171976f,0.38074401f,0.331535995f,0.386801004f,0.248908997f,0.688755989f,0.313903987f,0.377894014f,0.595845997f,0.412274003f,0.73962599f,0.541148007f,0.393005013f,0.656637013f,0.847671986f,0.930652976f,0.288289011f,0.404938012f,0.657989025f,0.763948977f,0.574084997f,0.282240987f,1.0f,0.429131001f,0.572049022f,0.73486799f,0.577476978f,0.520789027f,0.355592996f,0.890066981f,0.272390991f,0.448222995f,0.423969001f,0.392237008f,0.856091022f,0.0583794005f,0.784967005f,0.359526992f,0.576566994f,0.201513007f,0.642013013f,0.419308007f,0.340667009f,0.423189998f,0.860812008f,0.694019973f,0.42356801f,0.37698701f,0.568453014f,0.502301991f,0.280716002f,0.464040995f,0.395601004f,0.199849993f,0.0950397998f,0.64279002f,0.228325993f,0.484910995f,0.842352986f,0.161403999f,0.403432012f,0.65554899f,0.409097999f,0.699392021f,0.876049995f,1.0f,0.185606003f,0.414254993f,0.695204973f,0.732612014f,0.478298008f,0.249469995f,0.927739024f,0.213135004f,0.227382004f,0.976351976f,0.642745018f,0.376311004f,0.260674f,0.811034024f,0.264631003f,0.239978999f,0.261896998f,0.191642001f,0.781669974f,0.390679002f,0.382436991f,0.206714004f,0.224720001f,0.0676331967f,0.502610981f,0.301454991f,0.241028994f,0.224505007f,0.721193016f,0.436347991f,0.254061997f,0.480495989f,0.772370994f,0.210681006f,0.103414997f,0.485338002f,0.378333986f,0.228484005f,0.114877f,0.686760008f,0.296941996f,0.507420003f,0.997470021f,0.0377103016f,0.132211998f,0.319546998f,0.192031994f,0.520573974f,0.58584398f,0.419362009f,0.084731698f,0.134544f,0.194762006f,0.616689026f,0.397359997f,0.298808992f,0.914745986f,0.0513371006f,0.0543568991f,0.989158988f,0.602891982f,0.145582005f,0.102149002f,0.129022002f,0.116485f,0.279987991f,0.394270003f,0.29013899f,1.0f,0.708655f,0.78055501f,0.387526006f,0.0395217016f,0.00964067038f,0.24368f,0.0740624964f,0.619315028f,0.447394997f,0.292497009f,0.295457989f,0.163747996f,0.521375f,0.864533007f,0.0773407966f,0.0334230997f,0.345120996f,0.278860003f,0.223875999f,0.307756007f,0.763105989f,0.424706995f,0.487201005f,0.968962014f,0.00911747012f,0.0324653015f,0.334275007f,0.166786999f,0.312498003f,0.264261991f,0.354880005f,0.375589997f,0.261094004f,0.565006018f,0.474934995f,0.313520014f,0.251248986f,0.73535198f,0.0189072005f,0.0153633999f,0.786225021f,0.503298998f,0.369037986f,0.250764996f,0.673018992f,0.387573004f,0.742025018f,0.749055982f,0.261714011f,0.75186801f,0.771816015f,1.0f,0.459484011f,0.0124402f,0.0105394004f,0.964109004f,0.457051992f,0.532316029f,0.407128006f,0.697241008f,0.152199998f,0.0895892978f,0.406174988f,0.651040018f,0.0233951006f,0.0101070004f,0.0722346976f,0.0666339993f,0.195489004f,0.41674f,0.654451013f,0.382782012f,0.305395991f,0.631501019f,0.00162801996f,0.0140906004f,0.762915015f,0.410245001f,0.189436004f,0.060446199f,0.624940991f,0.43978101f,0.516273022f,0.896677971f,0.273297995f,0.202868f,0.0996022001f,0.257656991f,0.0174508002f,0.0157859009f,0.429432988f,0.202184007f,0.443111002f,0.343811005f,0.447562009f,0.268694013f,0.753551006f,0.529425979f,0.0772973001f,0.0976959988f,0.446413994f,0.26167801f,0.169035003f,0.0116218999f,0.0207398999f,1.0f,0.488855988f,0.413028985f,0.25266099f,0.148368999f,0.0919644013f,0.0330634005f,0.268763989f,0.441848993f,0.0139873f,0.0108583998f,0.657799006f,0.488247991f,0.375432998f,0.958178997f,0.761492014f,0.409489989f,0.151709005f,0.314931005f,0.00361180003f,0.0133069996f,1.0f,0.605342984f,0.550505996f,0.363516003f,0.255277991f,0.137537003f,0.448881f,0.867614985f,0.483247012f,0.308622003f,0.348444015f,0.534834981f,0.0157715995f,0.0128964996f,0.147607997f,0.0762611032f,0.762224019f,0.511584997f,0.98586297f,0.540226996f,0.691690981f,0.905296028f,0.397520989f,0.697939992f,0.423289001f,0.924612999f,0.491558999f,0.00567911007f,0.0106001999f,0.647916019f,0.324182004f,0.579448998f,0.451936007f,0.877897024f};

typedef struct {
	
	int fmydspSIG3Wave0_idx;
	
} mydspSIG3;

static mydspSIG3* newmydspSIG3() { return (mydspSIG3*)malloc(sizeof(mydspSIG3)); }
static void deletemydspSIG3(mydspSIG3* dsp) { free(dsp); }

int getNumInputsmydspSIG3(mydspSIG3* dsp) {
	return 0;
	
}
int getNumOutputsmydspSIG3(mydspSIG3* dsp) {
	return 1;
	
}
int getInputRatemydspSIG3(mydspSIG3* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydspSIG3(mydspSIG3* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

static void instanceInitmydspSIG3(mydspSIG3* dsp, int samplingFreq) {
	dsp->fmydspSIG3Wave0_idx = 0;
	
}

static void fillmydspSIG3(mydspSIG3* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			output[i] = fmydspSIG3Wave0[dsp->fmydspSIG3Wave0_idx];
			dsp->fmydspSIG3Wave0_idx = ((1 + dsp->fmydspSIG3Wave0_idx) % 350);
			
		}
		
	}
	
};

static float ftbl0mydspSIG0[350];
static float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}
static float ftbl1mydspSIG1[350];
static float ftbl2mydspSIG2[350];
static float ftbl3mydspSIG3[350];

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fVec0[2];
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	int iRec3[2];
	float fConst8;
	float fConst9;
	float fRec2[3];
	float fConst10;
	float fConst11;
	float fConst12;
	float fRec1[3];
	FAUSTFLOAT fHslider2;
	int iVec1[2];
	float fConst13;
	float fRec4[2];
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec0[3];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec5[3];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec6[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec7[3];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec8[3];
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec9[3];
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec10[3];
	float fConst37;
	float fConst38;
	float fConst39;
	float fRec11[3];
	float fConst40;
	float fConst41;
	float fConst42;
	float fRec12[3];
	float fConst43;
	float fConst44;
	float fConst45;
	float fRec13[3];
	FAUSTFLOAT fHslider3;
	int iVec2[2];
	float fRec15[2];
	float fConst46;
	float fConst47;
	float fConst48;
	float fRec14[3];
	float fConst49;
	float fConst50;
	float fConst51;
	float fRec16[3];
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec17[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec18[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec19[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec20[3];
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec21[3];
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec22[3];
	float fConst70;
	float fConst71;
	float fConst72;
	float fRec23[3];
	float fConst73;
	float fConst74;
	float fConst75;
	float fRec24[3];
	FAUSTFLOAT fHslider4;
	int iVec3[2];
	float fRec26[2];
	float fConst76;
	float fConst77;
	float fConst78;
	float fRec25[3];
	float fConst79;
	float fConst80;
	float fConst81;
	float fRec27[3];
	float fConst82;
	float fConst83;
	float fConst84;
	float fRec28[3];
	float fConst85;
	float fConst86;
	float fConst87;
	float fRec29[3];
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec30[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec31[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fRec32[3];
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec33[3];
	float fConst100;
	float fConst101;
	float fConst102;
	float fRec34[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec35[3];
	FAUSTFLOAT fHslider5;
	int iVec4[2];
	float fRec37[2];
	float fConst106;
	float fConst107;
	float fConst108;
	float fRec36[3];
	float fConst109;
	float fConst110;
	float fConst111;
	float fRec38[3];
	float fConst112;
	float fConst113;
	float fConst114;
	float fRec39[3];
	float fConst115;
	float fConst116;
	float fConst117;
	float fRec40[3];
	float fConst118;
	float fConst119;
	float fConst120;
	float fRec41[3];
	float fConst121;
	float fConst122;
	float fConst123;
	float fRec42[3];
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec43[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec44[3];
	float fConst130;
	float fConst131;
	float fConst132;
	float fRec45[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec46[3];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'2',   'Keyboard 1 - Number of Keys':'2',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key Status':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send X':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 0 - Key 0 - Label':'English Bell',  'Keyboard 0 - Key 1 - Label':'French Bell',  'Keyboard 1 - Key 0 - Label':'German Bell',  'Keyboard 1 - Key 1 - Label':'Russian Bell' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "bells");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 1;
			break;
		}
		case 1: {
			rate = 1;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

void classInitmydsp(int samplingFreq) {
	mydspSIG0* sig0 = newmydspSIG0();
	instanceInitmydspSIG0(sig0, samplingFreq);
	fillmydspSIG0(sig0, 350, ftbl0mydspSIG0);
	mydspSIG1* sig1 = newmydspSIG1();
	instanceInitmydspSIG1(sig1, samplingFreq);
	fillmydspSIG1(sig1, 350, ftbl1mydspSIG1);
	mydspSIG2* sig2 = newmydspSIG2();
	instanceInitmydspSIG2(sig2, samplingFreq);
	fillmydspSIG2(sig2, 350, ftbl2mydspSIG2);
	mydspSIG3* sig3 = newmydspSIG3();
	instanceInitmydspSIG3(sig3, samplingFreq);
	fillmydspSIG3(sig3, 350, ftbl3mydspSIG3);
	deletemydspSIG0(sig0);
	deletemydspSIG1(sig1);
	deletemydspSIG2(sig2);
	deletemydspSIG3(sig3);
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)1.0f;
	dsp->fHslider1 = (FAUSTFLOAT)1.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->iRec3[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			dsp->fRec2[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			dsp->fRec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->iVec1[l4] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec4[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec0[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec5[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec6[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			dsp->fRec7[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			dsp->fRec8[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec9[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			dsp->fRec10[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			dsp->fRec11[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			dsp->fRec12[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			dsp->fRec13[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->iVec2[l16] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec15[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			dsp->fRec14[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			dsp->fRec16[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			dsp->fRec17[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			dsp->fRec18[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			dsp->fRec19[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			dsp->fRec20[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			dsp->fRec21[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			dsp->fRec22[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			dsp->fRec23[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			dsp->fRec24[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->iVec3[l28] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec26[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			dsp->fRec25[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			dsp->fRec27[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			dsp->fRec28[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			dsp->fRec29[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			dsp->fRec30[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec31[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			dsp->fRec32[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			dsp->fRec33[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			dsp->fRec34[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			dsp->fRec35[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->iVec4[l40] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec37[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			dsp->fRec36[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			dsp->fRec38[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			dsp->fRec39[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			dsp->fRec40[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			dsp->fRec41[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec42[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec43[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec44[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			dsp->fRec45[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec46[l51] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = tanf((20420.3516f / dsp->fConst0));
	dsp->fConst2 = (1.0f / dsp->fConst1);
	dsp->fConst3 = (1.0f / (((dsp->fConst2 + 1.41421354f) / dsp->fConst1) + 1.0f));
	dsp->fConst4 = tanf((31.415926f / dsp->fConst0));
	dsp->fConst5 = (1.0f / dsp->fConst4);
	dsp->fConst6 = (1.0f / (((dsp->fConst5 + 1.41421354f) / dsp->fConst4) + 1.0f));
	dsp->fConst7 = (1.0f / mydsp_faustpower2_f(dsp->fConst4));
	dsp->fConst8 = (((dsp->fConst5 + -1.41421354f) / dsp->fConst4) + 1.0f);
	dsp->fConst9 = (2.0f * (1.0f - dsp->fConst7));
	dsp->fConst10 = (2.0f * (0.0f - dsp->fConst7));
	dsp->fConst11 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst1))));
	dsp->fConst12 = (((dsp->fConst2 + -1.41421354f) / dsp->fConst1) + 1.0f);
	dsp->fConst13 = (0.00200000009f * dsp->fConst0);
	dsp->fConst14 = (0.00100000005f * dsp->fConst0);
	dsp->fConst15 = (1000.0f / dsp->fConst0);
	dsp->fConst16 = powf(0.00100000005f, (1.0f / (20.3469906f * dsp->fConst0)));
	dsp->fConst17 = ((0.0f - (2.0f * dsp->fConst16)) * cosf((1630.04053f / dsp->fConst0)));
	dsp->fConst18 = mydsp_faustpower2_f(dsp->fConst16);
	dsp->fConst19 = powf(0.00100000005f, (1.0f / (20.2682228f * dsp->fConst0)));
	dsp->fConst20 = ((0.0f - (2.0f * dsp->fConst19)) * cosf((1645.28345f / dsp->fConst0)));
	dsp->fConst21 = mydsp_faustpower2_f(dsp->fConst19);
	dsp->fConst22 = powf(0.00100000005f, (1.0f / (13.6507998f * dsp->fConst0)));
	dsp->fConst23 = ((0.0f - (2.0f * dsp->fConst22)) * cosf((3099.69019f / dsp->fConst0)));
	dsp->fConst24 = mydsp_faustpower2_f(dsp->fConst22);
	dsp->fConst25 = powf(0.00100000005f, (1.0f / (13.6223917f * dsp->fConst0)));
	dsp->fConst26 = ((0.0f - (2.0f * dsp->fConst25)) * cosf((3106.85913f / dsp->fConst0)));
	dsp->fConst27 = mydsp_faustpower2_f(dsp->fConst25);
	dsp->fConst28 = powf(0.00100000005f, (1.0f / (11.0956459f * dsp->fConst0)));
	dsp->fConst29 = ((0.0f - (2.0f * dsp->fConst28)) * cosf((3789.06226f / dsp->fConst0)));
	dsp->fConst30 = mydsp_faustpower2_f(dsp->fConst28);
	dsp->fConst31 = powf(0.00100000005f, (1.0f / (11.0589275f * dsp->fConst0)));
	dsp->fConst32 = ((0.0f - (2.0f * dsp->fConst31)) * cosf((3799.70605f / dsp->fConst0)));
	dsp->fConst33 = mydsp_faustpower2_f(dsp->fConst31);
	dsp->fConst34 = powf(0.00100000005f, (1.0f / (8.6621294f * dsp->fConst0)));
	dsp->fConst35 = ((0.0f - (2.0f * dsp->fConst34)) * cosf((4552.58252f / dsp->fConst0)));
	dsp->fConst36 = mydsp_faustpower2_f(dsp->fConst34);
	dsp->fConst37 = powf(0.00100000005f, (1.0f / (8.6582489f * dsp->fConst0)));
	dsp->fConst38 = ((0.0f - (2.0f * dsp->fConst37)) * cosf((4553.9082f / dsp->fConst0)));
	dsp->fConst39 = mydsp_faustpower2_f(dsp->fConst37);
	dsp->fConst40 = powf(0.00100000005f, (1.0f / (7.56375885f * dsp->fConst0)));
	dsp->fConst41 = ((0.0f - (2.0f * dsp->fConst40)) * cosf((4944.77246f / dsp->fConst0)));
	dsp->fConst42 = mydsp_faustpower2_f(dsp->fConst40);
	dsp->fConst43 = powf(0.00100000005f, (1.0f / (5.38026142f * dsp->fConst0)));
	dsp->fConst44 = ((0.0f - (2.0f * dsp->fConst43)) * cosf((5855.25635f / dsp->fConst0)));
	dsp->fConst45 = mydsp_faustpower2_f(dsp->fConst43);
	dsp->fConst46 = powf(0.00100000005f, (1.0f / (17.0404034f * dsp->fConst0)));
	dsp->fConst47 = ((0.0f - (2.0f * dsp->fConst46)) * cosf((2758.80225f / dsp->fConst0)));
	dsp->fConst48 = mydsp_faustpower2_f(dsp->fConst46);
	dsp->fConst49 = powf(0.00100000005f, (1.0f / (17.0107555f * dsp->fConst0)));
	dsp->fConst50 = ((0.0f - (2.0f * dsp->fConst49)) * cosf((2766.51782f / dsp->fConst0)));
	dsp->fConst51 = mydsp_faustpower2_f(dsp->fConst49);
	dsp->fConst52 = powf(0.00100000005f, (1.0f / (13.3085108f * dsp->fConst0)));
	dsp->fConst53 = ((0.0f - (2.0f * dsp->fConst52)) * cosf((3810.4502f / dsp->fConst0)));
	dsp->fConst54 = mydsp_faustpower2_f(dsp->fConst52);
	dsp->fConst55 = powf(0.00100000005f, (1.0f / (13.1997375f * dsp->fConst0)));
	dsp->fConst56 = ((0.0f - (2.0f * dsp->fConst55)) * cosf((3843.90186f / dsp->fConst0)));
	dsp->fConst57 = mydsp_faustpower2_f(dsp->fConst55);
	dsp->fConst58 = powf(0.00100000005f, (1.0f / (11.3049049f * dsp->fConst0)));
	dsp->fConst59 = ((0.0f - (2.0f * dsp->fConst58)) * cosf((4458.65527f / dsp->fConst0)));
	dsp->fConst60 = mydsp_faustpower2_f(dsp->fConst58);
	dsp->fConst61 = powf(0.00100000005f, (1.0f / (11.300128f * dsp->fConst0)));
	dsp->fConst62 = ((0.0f - (2.0f * dsp->fConst61)) * cosf((4460.28857f / dsp->fConst0)));
	dsp->fConst63 = mydsp_faustpower2_f(dsp->fConst61);
	dsp->fConst64 = powf(0.00100000005f, (1.0f / (8.80774784f * dsp->fConst0)));
	dsp->fConst65 = ((0.0f - (2.0f * dsp->fConst64)) * cosf((5384.47607f / dsp->fConst0)));
	dsp->fConst66 = mydsp_faustpower2_f(dsp->fConst64);
	dsp->fConst67 = powf(0.00100000005f, (1.0f / (8.16906738f * dsp->fConst0)));
	dsp->fConst68 = ((0.0f - (2.0f * dsp->fConst67)) * cosf((5648.90381f / dsp->fConst0)));
	dsp->fConst69 = mydsp_faustpower2_f(dsp->fConst67);
	dsp->fConst70 = powf(0.00100000005f, (1.0f / (5.95891714f * dsp->fConst0)));
	dsp->fConst71 = ((0.0f - (2.0f * dsp->fConst70)) * cosf((6687.63379f / dsp->fConst0)));
	dsp->fConst72 = mydsp_faustpower2_f(dsp->fConst70);
	dsp->fConst73 = powf(0.00100000005f, (1.0f / (5.95436192f * dsp->fConst0)));
	dsp->fConst74 = ((0.0f - (2.0f * dsp->fConst73)) * cosf((6690.02148f / dsp->fConst0)));
	dsp->fConst75 = mydsp_faustpower2_f(dsp->fConst73);
	dsp->fConst76 = powf(0.00100000005f, (1.0f / (21.8895645f * dsp->fConst0)));
	dsp->fConst77 = ((0.0f - (2.0f * dsp->fConst76)) * cosf((1501.1095f / dsp->fConst0)));
	dsp->fConst78 = mydsp_faustpower2_f(dsp->fConst76);
	dsp->fConst79 = powf(0.00100000005f, (1.0f / (21.8487759f * dsp->fConst0)));
	dsp->fConst80 = ((0.0f - (2.0f * dsp->fConst79)) * cosf((1509.44104f / dsp->fConst0)));
	dsp->fConst81 = mydsp_faustpower2_f(dsp->fConst79);
	dsp->fConst82 = powf(0.00100000005f, (1.0f / (17.0969524f * dsp->fConst0)));
	dsp->fConst83 = ((0.0f - (2.0f * dsp->fConst82)) * cosf((2552.54395f / dsp->fConst0)));
	dsp->fConst84 = mydsp_faustpower2_f(dsp->fConst82);
	dsp->fConst85 = powf(0.00100000005f, (1.0f / (17.0448818f * dsp->fConst0)));
	dsp->fConst86 = ((0.0f - (2.0f * dsp->fConst85)) * cosf((2564.88428f / dsp->fConst0)));
	dsp->fConst87 = mydsp_faustpower2_f(dsp->fConst85);
	dsp->fConst88 = powf(0.00100000005f, (1.0f / (13.2791166f * dsp->fConst0)));
	dsp->fConst89 = ((0.0f - (2.0f * dsp->fConst88)) * cosf((3525.52661f / dsp->fConst0)));
	dsp->fConst90 = mydsp_faustpower2_f(dsp->fConst88);
	dsp->fConst91 = powf(0.00100000005f, (1.0f / (13.2376995f * dsp->fConst0)));
	dsp->fConst92 = ((0.0f - (2.0f * dsp->fConst91)) * cosf((3536.94946f / dsp->fConst0)));
	dsp->fConst93 = mydsp_faustpower2_f(dsp->fConst91);
	dsp->fConst94 = powf(0.00100000005f, (1.0f / (9.3884573f * dsp->fConst0)));
	dsp->fConst95 = ((0.0f - (2.0f * dsp->fConst94)) * cosf((4710.07666f / dsp->fConst0)));
	dsp->fConst96 = mydsp_faustpower2_f(dsp->fConst94);
	dsp->fConst97 = powf(0.00100000005f, (1.0f / (9.38386536f * dsp->fConst0)));
	dsp->fConst98 = ((0.0f - (2.0f * dsp->fConst97)) * cosf((4711.63477f / dsp->fConst0)));
	dsp->fConst99 = mydsp_faustpower2_f(dsp->fConst97);
	dsp->fConst100 = powf(0.00100000005f, (1.0f / (8.81131077f * dsp->fConst0)));
	dsp->fConst101 = ((0.0f - (2.0f * dsp->fConst100)) * cosf((4909.61182f / dsp->fConst0)));
	dsp->fConst102 = mydsp_faustpower2_f(dsp->fConst100);
	dsp->fConst103 = powf(0.00100000005f, (1.0f / (8.47139359f * dsp->fConst0)));
	dsp->fConst104 = ((0.0f - (2.0f * dsp->fConst103)) * cosf((5030.8208f / dsp->fConst0)));
	dsp->fConst105 = mydsp_faustpower2_f(dsp->fConst103);
	dsp->fConst106 = powf(0.00100000005f, (1.0f / (20.8901539f * dsp->fConst0)));
	dsp->fConst107 = ((0.0f - (2.0f * dsp->fConst106)) * cosf((857.598267f / dsp->fConst0)));
	dsp->fConst108 = mydsp_faustpower2_f(dsp->fConst106);
	dsp->fConst109 = powf(0.00100000005f, (1.0f / (20.860672f * dsp->fConst0)));
	dsp->fConst110 = ((0.0f - (2.0f * dsp->fConst109)) * cosf((860.746094f / dsp->fConst0)));
	dsp->fConst111 = mydsp_faustpower2_f(dsp->fConst109);
	dsp->fConst112 = powf(0.00100000005f, (1.0f / (14.4779148f * dsp->fConst0)));
	dsp->fConst113 = ((0.0f - (2.0f * dsp->fConst112)) * cosf((1627.08105f / dsp->fConst0)));
	dsp->fConst114 = mydsp_faustpower2_f(dsp->fConst112);
	dsp->fConst115 = powf(0.00100000005f, (1.0f / (14.4106588f * dsp->fConst0)));
	dsp->fConst116 = ((0.0f - (2.0f * dsp->fConst115)) * cosf((1636.26086f / dsp->fConst0)));
	dsp->fConst117 = mydsp_faustpower2_f(dsp->fConst115);
	dsp->fConst118 = powf(0.00100000005f, (1.0f / (11.9841108f * dsp->fConst0)));
	dsp->fConst119 = ((0.0f - (2.0f * dsp->fConst118)) * cosf((1988.55908f / dsp->fConst0)));
	dsp->fConst120 = mydsp_faustpower2_f(dsp->fConst118);
	dsp->fConst121 = powf(0.00100000005f, (1.0f / (11.9061594f * dsp->fConst0)));
	dsp->fConst122 = ((0.0f - (2.0f * dsp->fConst121)) * cosf((2000.63538f / dsp->fConst0)));
	dsp->fConst123 = mydsp_faustpower2_f(dsp->fConst121);
	dsp->fConst124 = powf(0.00100000005f, (1.0f / (9.10661697f * dsp->fConst0)));
	dsp->fConst125 = ((0.0f - (2.0f * dsp->fConst124)) * cosf((2474.64502f / dsp->fConst0)));
	dsp->fConst126 = mydsp_faustpower2_f(dsp->fConst124);
	dsp->fConst127 = powf(0.00100000005f, (1.0f / (9.10333347f * dsp->fConst0)));
	dsp->fConst128 = ((0.0f - (2.0f * dsp->fConst127)) * cosf((2475.25464f / dsp->fConst0)));
	dsp->fConst129 = mydsp_faustpower2_f(dsp->fConst127);
	dsp->fConst130 = powf(0.00100000005f, (1.0f / (7.19911861f * dsp->fConst0)));
	dsp->fConst131 = ((0.0f - (2.0f * dsp->fConst130)) * cosf((2856.81982f / dsp->fConst0)));
	dsp->fConst132 = mydsp_faustpower2_f(dsp->fConst130);
	dsp->fConst133 = powf(0.00100000005f, (1.0f / (6.83458185f * dsp->fConst0)));
	dsp->fConst134 = ((0.0f - (2.0f * dsp->fConst133)) * cosf((2937.34521f / dsp->fConst0)));
	dsp->fConst135 = mydsp_faustpower2_f(dsp->fConst133);
	
}

void instanceInitmydsp(mydsp* dsp, int samplingFreq) {
	instanceConstantsmydsp(dsp, samplingFreq);
	instanceResetUserInterfacemydsp(dsp);
	instanceClearmydsp(dsp);
}

void initmydsp(mydsp* dsp, int samplingFreq) {
	classInitmydsp(samplingFreq);
	instanceInitmydsp(dsp, samplingFreq);
}

void buildUserInterfacemydsp(mydsp* dsp, UIGlue* ui_interface) {
	ui_interface->openVerticalBox(ui_interface->uiInterface, "bells");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k0status", &dsp->fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k1status", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k0status", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k1status", &dsp->fHslider5, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "x", &dsp->fHslider0, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y", &dsp->fHslider1, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	int iSlow0 = (10 * (int)(6.0f * min(fabsf(((2.0f * (float)dsp->fHslider0) + -1.0f)), fabsf(((2.0f * (float)dsp->fHslider1) + -1.0f)))));
	int iSlow1 = (int)min(1.0f, (float)dsp->fHslider2);
	int iSlow2 = (iSlow0 + 1);
	int iSlow3 = (iSlow0 + 2);
	int iSlow4 = (iSlow0 + 3);
	int iSlow5 = (iSlow0 + 4);
	int iSlow6 = (iSlow0 + 5);
	int iSlow7 = (iSlow0 + 6);
	int iSlow8 = (iSlow0 + 7);
	int iSlow9 = (iSlow0 + 8);
	int iSlow10 = (iSlow0 + 9);
	int iSlow11 = (int)min(1.0f, (float)dsp->fHslider3);
	int iSlow12 = (int)min(1.0f, (float)dsp->fHslider4);
	int iSlow13 = (int)min(1.0f, (float)dsp->fHslider5);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fVec0[0] = dsp->fConst0;
			dsp->iRec3[0] = ((1103515245 * dsp->iRec3[1]) + 12345);
			dsp->fRec2[0] = ((4.65661287e-10f * (float)dsp->iRec3[0]) - (dsp->fConst6 * ((dsp->fConst8 * dsp->fRec2[2]) + (dsp->fConst9 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((dsp->fConst6 * (((dsp->fConst7 * dsp->fRec2[0]) + (dsp->fConst10 * dsp->fRec2[1])) + (dsp->fConst7 * dsp->fRec2[2]))) - (dsp->fConst3 * ((dsp->fConst11 * dsp->fRec1[1]) + (dsp->fConst12 * dsp->fRec1[2]))));
			float fTemp0 = (dsp->fRec1[2] + (dsp->fRec1[0] + (2.0f * dsp->fRec1[1])));
			dsp->iVec1[0] = iSlow1;
			float fTemp1 = (0.00200000009f * (dsp->fConst0 - dsp->fVec0[1]));
			dsp->fRec4[0] = ((((iSlow1 - dsp->iVec1[1]) > 0) > 0)?0.0f:min(dsp->fConst13, ((dsp->fRec4[1] + fTemp1) + 1.0f)));
			int iTemp2 = (dsp->fRec4[0] < dsp->fConst14);
			float fTemp3 = (dsp->fConst3 * (fTemp0 * (iTemp2?((dsp->fRec4[0] < 0.0f)?0.0f:(iTemp2?(dsp->fConst15 * dsp->fRec4[0]):1.0f)):((dsp->fRec4[0] < dsp->fConst13)?((dsp->fConst15 * (0.0f - (dsp->fRec4[0] - dsp->fConst14))) + 1.0f):0.0f))));
			dsp->fRec0[0] = (fTemp3 - ((dsp->fConst17 * dsp->fRec0[1]) + (dsp->fConst18 * dsp->fRec0[2])));
			dsp->fRec5[0] = (fTemp3 - ((dsp->fConst20 * dsp->fRec5[1]) + (dsp->fConst21 * dsp->fRec5[2])));
			dsp->fRec6[0] = (fTemp3 - ((dsp->fConst23 * dsp->fRec6[1]) + (dsp->fConst24 * dsp->fRec6[2])));
			dsp->fRec7[0] = (fTemp3 - ((dsp->fConst26 * dsp->fRec7[1]) + (dsp->fConst27 * dsp->fRec7[2])));
			dsp->fRec8[0] = (fTemp3 - ((dsp->fConst29 * dsp->fRec8[1]) + (dsp->fConst30 * dsp->fRec8[2])));
			dsp->fRec9[0] = (fTemp3 - ((dsp->fConst32 * dsp->fRec9[1]) + (dsp->fConst33 * dsp->fRec9[2])));
			dsp->fRec10[0] = (fTemp3 - ((dsp->fConst35 * dsp->fRec10[1]) + (dsp->fConst36 * dsp->fRec10[2])));
			dsp->fRec11[0] = (fTemp3 - ((dsp->fConst38 * dsp->fRec11[1]) + (dsp->fConst39 * dsp->fRec11[2])));
			dsp->fRec12[0] = (fTemp3 - ((dsp->fConst41 * dsp->fRec12[1]) + (dsp->fConst42 * dsp->fRec12[2])));
			dsp->fRec13[0] = (fTemp3 - ((dsp->fConst44 * dsp->fRec13[1]) + (dsp->fConst45 * dsp->fRec13[2])));
			dsp->iVec2[0] = iSlow11;
			dsp->fRec15[0] = ((((iSlow11 - dsp->iVec2[1]) > 0) > 0)?0.0f:min(dsp->fConst13, ((fTemp1 + dsp->fRec15[1]) + 1.0f)));
			int iTemp4 = (dsp->fRec15[0] < dsp->fConst14);
			float fTemp5 = (dsp->fConst3 * (fTemp0 * (iTemp4?((dsp->fRec15[0] < 0.0f)?0.0f:(iTemp4?(dsp->fConst15 * dsp->fRec15[0]):1.0f)):((dsp->fRec15[0] < dsp->fConst13)?((dsp->fConst15 * (0.0f - (dsp->fRec15[0] - dsp->fConst14))) + 1.0f):0.0f))));
			dsp->fRec14[0] = (fTemp5 - ((dsp->fConst47 * dsp->fRec14[1]) + (dsp->fConst48 * dsp->fRec14[2])));
			dsp->fRec16[0] = (fTemp5 - ((dsp->fConst50 * dsp->fRec16[1]) + (dsp->fConst51 * dsp->fRec16[2])));
			dsp->fRec17[0] = (fTemp5 - ((dsp->fConst53 * dsp->fRec17[1]) + (dsp->fConst54 * dsp->fRec17[2])));
			dsp->fRec18[0] = (fTemp5 - ((dsp->fConst56 * dsp->fRec18[1]) + (dsp->fConst57 * dsp->fRec18[2])));
			dsp->fRec19[0] = (fTemp5 - ((dsp->fConst59 * dsp->fRec19[1]) + (dsp->fConst60 * dsp->fRec19[2])));
			dsp->fRec20[0] = (fTemp5 - ((dsp->fConst62 * dsp->fRec20[1]) + (dsp->fConst63 * dsp->fRec20[2])));
			dsp->fRec21[0] = (fTemp5 - ((dsp->fConst65 * dsp->fRec21[1]) + (dsp->fConst66 * dsp->fRec21[2])));
			dsp->fRec22[0] = (fTemp5 - ((dsp->fConst68 * dsp->fRec22[1]) + (dsp->fConst69 * dsp->fRec22[2])));
			dsp->fRec23[0] = (fTemp5 - ((dsp->fConst71 * dsp->fRec23[1]) + (dsp->fConst72 * dsp->fRec23[2])));
			dsp->fRec24[0] = (fTemp5 - ((dsp->fConst74 * dsp->fRec24[1]) + (dsp->fConst75 * dsp->fRec24[2])));
			dsp->iVec3[0] = iSlow12;
			dsp->fRec26[0] = ((((iSlow12 - dsp->iVec3[1]) > 0) > 0)?0.0f:min(dsp->fConst13, ((fTemp1 + dsp->fRec26[1]) + 1.0f)));
			int iTemp6 = (dsp->fRec26[0] < dsp->fConst14);
			float fTemp7 = (dsp->fConst3 * (fTemp0 * (iTemp6?((dsp->fRec26[0] < 0.0f)?0.0f:(iTemp6?(dsp->fConst15 * dsp->fRec26[0]):1.0f)):((dsp->fRec26[0] < dsp->fConst13)?((dsp->fConst15 * (0.0f - (dsp->fRec26[0] - dsp->fConst14))) + 1.0f):0.0f))));
			dsp->fRec25[0] = (fTemp7 - ((dsp->fConst77 * dsp->fRec25[1]) + (dsp->fConst78 * dsp->fRec25[2])));
			dsp->fRec27[0] = (fTemp7 - ((dsp->fConst80 * dsp->fRec27[1]) + (dsp->fConst81 * dsp->fRec27[2])));
			dsp->fRec28[0] = (fTemp7 - ((dsp->fConst83 * dsp->fRec28[1]) + (dsp->fConst84 * dsp->fRec28[2])));
			dsp->fRec29[0] = (fTemp7 - ((dsp->fConst86 * dsp->fRec29[1]) + (dsp->fConst87 * dsp->fRec29[2])));
			dsp->fRec30[0] = (fTemp7 - ((dsp->fConst89 * dsp->fRec30[1]) + (dsp->fConst90 * dsp->fRec30[2])));
			dsp->fRec31[0] = (fTemp7 - ((dsp->fConst92 * dsp->fRec31[1]) + (dsp->fConst93 * dsp->fRec31[2])));
			dsp->fRec32[0] = (fTemp7 - ((dsp->fConst95 * dsp->fRec32[1]) + (dsp->fConst96 * dsp->fRec32[2])));
			dsp->fRec33[0] = (fTemp7 - ((dsp->fConst98 * dsp->fRec33[1]) + (dsp->fConst99 * dsp->fRec33[2])));
			dsp->fRec34[0] = (fTemp7 - ((dsp->fConst101 * dsp->fRec34[1]) + (dsp->fConst102 * dsp->fRec34[2])));
			dsp->fRec35[0] = (fTemp7 - ((dsp->fConst104 * dsp->fRec35[1]) + (dsp->fConst105 * dsp->fRec35[2])));
			dsp->iVec4[0] = iSlow13;
			dsp->fRec37[0] = ((((iSlow13 - dsp->iVec4[1]) > 0) > 0)?0.0f:min(dsp->fConst13, ((fTemp1 + dsp->fRec37[1]) + 1.0f)));
			int iTemp8 = (dsp->fRec37[0] < dsp->fConst14);
			float fTemp9 = (dsp->fConst3 * (fTemp0 * (iTemp8?((dsp->fRec37[0] < 0.0f)?0.0f:(iTemp8?(dsp->fConst15 * dsp->fRec37[0]):1.0f)):((dsp->fRec37[0] < dsp->fConst13)?((dsp->fConst15 * (0.0f - (dsp->fRec37[0] - dsp->fConst14))) + 1.0f):0.0f))));
			dsp->fRec36[0] = (fTemp9 - ((dsp->fConst107 * dsp->fRec36[1]) + (dsp->fConst108 * dsp->fRec36[2])));
			dsp->fRec38[0] = (fTemp9 - ((dsp->fConst110 * dsp->fRec38[1]) + (dsp->fConst111 * dsp->fRec38[2])));
			dsp->fRec39[0] = (fTemp9 - ((dsp->fConst113 * dsp->fRec39[1]) + (dsp->fConst114 * dsp->fRec39[2])));
			dsp->fRec40[0] = (fTemp9 - ((dsp->fConst116 * dsp->fRec40[1]) + (dsp->fConst117 * dsp->fRec40[2])));
			dsp->fRec41[0] = (fTemp9 - ((dsp->fConst119 * dsp->fRec41[1]) + (dsp->fConst120 * dsp->fRec41[2])));
			dsp->fRec42[0] = (fTemp9 - ((dsp->fConst122 * dsp->fRec42[1]) + (dsp->fConst123 * dsp->fRec42[2])));
			dsp->fRec43[0] = (fTemp9 - ((dsp->fConst125 * dsp->fRec43[1]) + (dsp->fConst126 * dsp->fRec43[2])));
			dsp->fRec44[0] = (fTemp9 - ((dsp->fConst128 * dsp->fRec44[1]) + (dsp->fConst129 * dsp->fRec44[2])));
			dsp->fRec45[0] = (fTemp9 - ((dsp->fConst131 * dsp->fRec45[1]) + (dsp->fConst132 * dsp->fRec45[2])));
			dsp->fRec46[0] = (fTemp9 - ((dsp->fConst134 * dsp->fRec46[1]) + (dsp->fConst135 * dsp->fRec46[2])));
			float fTemp10 = (0.0199999996f * (((((((((((((ftbl0mydspSIG0[iSlow0] * (dsp->fRec0[0] - dsp->fRec0[2])) + (ftbl0mydspSIG0[iSlow2] * (dsp->fRec5[0] - dsp->fRec5[2]))) + (ftbl0mydspSIG0[iSlow3] * (dsp->fRec6[0] - dsp->fRec6[2]))) + (ftbl0mydspSIG0[iSlow4] * (dsp->fRec7[0] - dsp->fRec7[2]))) + (ftbl0mydspSIG0[iSlow5] * (dsp->fRec8[0] - dsp->fRec8[2]))) + (ftbl0mydspSIG0[iSlow6] * (dsp->fRec9[0] - dsp->fRec9[2]))) + (ftbl0mydspSIG0[iSlow7] * (dsp->fRec10[0] - dsp->fRec10[2]))) + (ftbl0mydspSIG0[iSlow8] * (dsp->fRec11[0] - dsp->fRec11[2]))) + (ftbl0mydspSIG0[iSlow9] * (dsp->fRec12[0] - dsp->fRec12[2]))) + (ftbl0mydspSIG0[iSlow10] * (dsp->fRec13[0] - dsp->fRec13[2]))) + ((((((((((ftbl1mydspSIG1[iSlow0] * (dsp->fRec14[0] - dsp->fRec14[2])) + (ftbl1mydspSIG1[iSlow2] * (dsp->fRec16[0] - dsp->fRec16[2]))) + (ftbl1mydspSIG1[iSlow3] * (dsp->fRec17[0] - dsp->fRec17[2]))) + (ftbl1mydspSIG1[iSlow4] * (dsp->fRec18[0] - dsp->fRec18[2]))) + (ftbl1mydspSIG1[iSlow5] * (dsp->fRec19[0] - dsp->fRec19[2]))) + (ftbl1mydspSIG1[iSlow6] * (dsp->fRec20[0] - dsp->fRec20[2]))) + (ftbl1mydspSIG1[iSlow7] * (dsp->fRec21[0] - dsp->fRec21[2]))) + (ftbl1mydspSIG1[iSlow8] * (dsp->fRec22[0] - dsp->fRec22[2]))) + (ftbl1mydspSIG1[iSlow9] * (dsp->fRec23[0] - dsp->fRec23[2]))) + (ftbl1mydspSIG1[iSlow10] * (dsp->fRec24[0] - dsp->fRec24[2])))) + ((((((((((ftbl2mydspSIG2[iSlow0] * (dsp->fRec25[0] - dsp->fRec25[2])) + (ftbl2mydspSIG2[iSlow2] * (dsp->fRec27[0] - dsp->fRec27[2]))) + (ftbl2mydspSIG2[iSlow3] * (dsp->fRec28[0] - dsp->fRec28[2]))) + (ftbl2mydspSIG2[iSlow4] * (dsp->fRec29[0] - dsp->fRec29[2]))) + (ftbl2mydspSIG2[iSlow5] * (dsp->fRec30[0] - dsp->fRec30[2]))) + (ftbl2mydspSIG2[iSlow6] * (dsp->fRec31[0] - dsp->fRec31[2]))) + (ftbl2mydspSIG2[iSlow7] * (dsp->fRec32[0] - dsp->fRec32[2]))) + (ftbl2mydspSIG2[iSlow8] * (dsp->fRec33[0] - dsp->fRec33[2]))) + (ftbl2mydspSIG2[iSlow9] * (dsp->fRec34[0] - dsp->fRec34[2]))) + (ftbl2mydspSIG2[iSlow10] * (dsp->fRec35[0] - dsp->fRec35[2])))) + ((((((((((ftbl3mydspSIG3[iSlow0] * (dsp->fRec36[0] - dsp->fRec36[2])) + (ftbl3mydspSIG3[iSlow2] * (dsp->fRec38[0] - dsp->fRec38[2]))) + (ftbl3mydspSIG3[iSlow3] * (dsp->fRec39[0] - dsp->fRec39[2]))) + (ftbl3mydspSIG3[iSlow4] * (dsp->fRec40[0] - dsp->fRec40[2]))) + (ftbl3mydspSIG3[iSlow5] * (dsp->fRec41[0] - dsp->fRec41[2]))) + (ftbl3mydspSIG3[iSlow6] * (dsp->fRec42[0] - dsp->fRec42[2]))) + (ftbl3mydspSIG3[iSlow7] * (dsp->fRec43[0] - dsp->fRec43[2]))) + (ftbl3mydspSIG3[iSlow8] * (dsp->fRec44[0] - dsp->fRec44[2]))) + (ftbl3mydspSIG3[iSlow9] * (dsp->fRec45[0] - dsp->fRec45[2]))) + (ftbl3mydspSIG3[iSlow10] * (dsp->fRec46[0] - dsp->fRec46[2])))));
			output0[i] = (FAUSTFLOAT)fTemp10;
			output1[i] = (FAUSTFLOAT)fTemp10;
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->iRec3[1] = dsp->iRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->iVec1[1] = dsp->iVec1[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec13[2] = dsp->fRec13[1];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->iVec2[1] = dsp->iVec2[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec16[2] = dsp->fRec16[1];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec17[2] = dsp->fRec17[1];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec21[2] = dsp->fRec21[1];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec22[2] = dsp->fRec22[1];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec24[2] = dsp->fRec24[1];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->iVec3[1] = dsp->iVec3[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[2] = dsp->fRec25[1];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec27[2] = dsp->fRec27[1];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec28[2] = dsp->fRec28[1];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec29[2] = dsp->fRec29[1];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec30[2] = dsp->fRec30[1];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec31[2] = dsp->fRec31[1];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec32[2] = dsp->fRec32[1];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec33[2] = dsp->fRec33[1];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec34[2] = dsp->fRec34[1];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec35[2] = dsp->fRec35[1];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->iVec4[1] = dsp->iVec4[0];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[2] = dsp->fRec36[1];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec38[2] = dsp->fRec38[1];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec39[2] = dsp->fRec39[1];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec40[2] = dsp->fRec40[1];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec41[2] = dsp->fRec41[1];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec42[2] = dsp->fRec42[1];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec43[2] = dsp->fRec43[1];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec44[2] = dsp->fRec44[1];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec46[2] = dsp->fRec46[1];
			dsp->fRec46[1] = dsp->fRec46[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
