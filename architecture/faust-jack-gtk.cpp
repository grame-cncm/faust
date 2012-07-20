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
    char    error_msg[256];
	char* 	home = getenv("HOME");

    try {
		if (argc < 2) {
			printf("Usage: faust-jack-gtk args [file.dsp | file.bc]\n");
			exit(1);
		} else {
        
            /*
            int argc1 = 2;
            const char* argv1[argc1];
            argv1[0] = "faust";
            argv1[1] = "-svg";

            compile_faust(argc1, (char**)argv1, false, "in1", "process = +,+;", error_msg);
            compile_faust(argc1, (char**)argv1, false, "in2", "process = _,_;", error_msg);
            */
            
            
            try {
                
                int argc1 = 1;
                char* argv1[argc1];
                argv1[0] = "-svg";
                DSP = new llvmdsp(argc1, argv1, "in1", "process = +,+;", error_msg);
                delete(DSP);
                DSP = new llvmdsp(argc1, argv1, "in2", "process = +,+;", error_msg);
                
                //DSP = new llvmdsp(0, NULL, "in1", "process = +,+;", error_msg);
            }
            catch (...) {
                printf("Mauvais code source : %s", error_msg);
                DSP = new llvmdsp(0, NULL, "in1", "process = +,+;", error_msg);
            }
            
            
            //DSP = new llvmdsp(0, NULL, "in1", "process = +,+;");
            
            //DSP = new llvmdsp(argc, argv, error_msg);
            
            /*
            printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
            DSP = new llvmdsp(1, NULL, "process = +,+;");
            printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
            delete DSP;
            DSP = new llvmdsp(1, NULL, "process = +;");
            printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
            delete DSP;
            DSP = new llvmdsp(1, NULL, "process = +,+,+,+;");
            printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
            */
            
        }
	} catch (...) {
        cerr << error_msg;
		cerr << "Cannot load .dsp or .bc file" << endl;
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
    delete(interface);
    delete(finterface);
    delete(DSP);
  	return 0;
}

