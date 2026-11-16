#include <iterator>

#include "faust/gui/McpUI.h"

int main(int argc, char**)
{
    if (argc > 1) {
        std::string input((std::istreambuf_iterator<char>(std::cin)),
                          std::istreambuf_iterator<char>());
        std::cout << removeControlChars(input);
    } else {
        McpUI ui;
        FAUSTFLOAT zone = 0;
        ui.openVerticalBox(u8"Synthé 音 🎵");
        ui.addHorizontalSlider(u8"Fréquence", &zone, 0, 0, 1, 0.01);
        ui.closeBox();
        ui.run();
    }
}
