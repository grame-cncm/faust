// @TODO : Improve the way code in the editor is stored/used
#define LASTCODE_FNAME "last_code.dsp"

const char* default_entry_code = R"FAUST(
import("stdfaust.lib");

declare name "myPlugin"; // declare name of your plugin

// you faust dsp code here..
)FAUST";
