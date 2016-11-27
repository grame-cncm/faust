#include "faust/misc.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"

<<includeIntrinsic>>

<<includeclass>>

#include "faust/dsp/faust-poly-engine.h"
#include "faust/audio/dummy-audio.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char *argv[] )
{
  FaustPolyEngine fPolyEngine(new dummy_audio());

  std::cout << "## Parameters List\n\n";
  
  std::cout << "### Main Parameters\n\n";
  for(int i=0; i<fPolyEngine.getParamsCount(); i++){
    std::cout << "* **" << i << "**: `" << fPolyEngine.getParamAddress(i) << "`" << "\n";
  }
  std::cout << "\n";

  #if POLY2
  // kind of funny, but it's the fastest way
  MapUI *idpVoice = fPolyEngine.keyOn(100,100);

  std::cout << "### Independent Voices" << "\n\n";
  for(int i=0; i<idpVoice->getParamsCount(); i++){
    std::cout << "* **" << i << "**: `" << idpVoice->getParamAdress(i) << "`" << "\n";
  }

  fPolyEngine.keyOff(100); // just to be really clean...
  #endif
  
  return 0;
}
