// McpUI server whose labels need JSON escaping or collapse to the same tool name.
// With an argument, filters stdin through removeControlChars() instead.
#include <iterator>

#include "faust/gui/McpUI.h"

int main(int argc, char**)
{
    if (argc > 1) {
        std::string input((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
        std::cout << removeControlChars(input);
        return 0;
    }
    McpUI ui;
    static FAUSTFLOAT zones[7] = {};
    ui.openVerticalBox("Root \"main\" C:\\dsp\\");
    // A label ending with a backslash, followed by labels with double spaces
    ui.addHorizontalSlider("path\\", &zones[0], 0, 0, 1, 0.01);
    ui.addHorizontalSlider("Gain \"dB\"\tleft  right", &zones[1], 0, 0, 2, 0.01);
    ui.addHorizontalSlider("two  spaces", &zones[2], 0, 0, 3, 0.01);
    // Non-ASCII labels: tool names keep only ASCII letters and digits
    ui.addHorizontalSlider(u8"音量", &zones[3], 0, 0, 4, 0.01);
    ui.addHorizontalSlider(u8"音高", &zones[4], 0, 0, 5, 0.01);
    // Same name once truncated to 50 characters
    ui.addHorizontalSlider("a_very_long_label_that_goes_beyond_the_fifty_characters_limit_1", &zones[5], 0, 0, 6, 0.01);
    ui.addHorizontalSlider("a_very_long_label_that_goes_beyond_the_fifty_characters_limit_2", &zones[6], 0, 0, 7, 0.01);
    ui.closeBox();
    ui.run();
}
