/* link with  */
#include <libgen.h>
#include "faust/gui/FUI.h"
#include "faust/audio/llvm-dsp.h"
#include "faust/gui/faustgtk.h"
#include "faust/audio/jack-dsp.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif


//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

llvmdsp* DSP;

classInitFun llvmdsp::fClassInit;

list<GUI*> GUI::fGuiList;

int main(int argc, char *argv[])
{
	char	appname[256];
    char	filename[256];
	char  	rcfilename[256];
	char* 	home = getenv("HOME");

    try {
		if (argc < 2) {
			printf("Usage: faust-jack-gtk args [file.dsp | file.bc]\n");
			exit(1);
		} else {
			DSP = new llvmdsp(argc, argv);
            /*
            printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
            DSP = new llvmdsp(1, NULL, "process = +,+;");
            printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
            DSP = new llvmdsp(1, NULL, "process = +;");
            printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
            DSP = new llvmdsp(1, NULL, "process = +,+,+,+;");
            printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
            */
            
        }
	} catch (...) {
		printf("Cannot load .dsp or .bc file\n");
		exit(1);
	}

	snprintf(appname, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
	snprintf(rcfilename, 255, "%s/.%s-%src", home, appname, argv[1]);

	GUI* interface 	= new GTKUI(filename, &argc, &argv);
	FUI* finterface	= new FUI();

	DSP->buildUserInterface(interface);
	DSP->buildUserInterface(finterface);

#ifdef HTTPCTRL
	httpdUI* httpdinterface = new httpdUI(appname, argc, argv);
	DSP->buildUserInterface(httpdinterface);
#endif

#ifdef OSCCTRL
	GUI* oscinterface = new OSCUI(filename, argc, argv);
	DSP->buildUserInterface(oscinterface);
#endif

	jackaudio audio;
    if (!audio.init(filename, DSP)) {
        return 0;
    }
	finterface->recallState(rcfilename);
	audio.start();

#ifdef HTTPCTRL
	httpdinterface->run();
#endif

#ifdef OSCCTRL
	oscinterface->run();
#endif
	interface->run();

	audio.stop();
	finterface->saveState(rcfilename);
  	return 0;
}

