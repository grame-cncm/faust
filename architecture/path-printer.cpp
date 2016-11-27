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

  for(int i=0; i<fPolyEngine.getParamsCount(); i++){
    std::cout << "* **" << i << "**: `" << fPolyEngine.getParamAddress(i) << "`" << "\n";
  }
  
  return 0;
}
