#pragma once
#include <TFT_eSPI.h>
#include "utils/colors.h"
#include "utils/menu_utils.h"

class PaletteMenu {
public:
    PaletteMenu(TFT_eSPI &tftRef) : tft(tftRef), initialized(false) {}

    void init();
    void drawMenu();
    void reset() { initialized = false; }
    String handleTouch(int x, int y);

private:
    TFT_eSPI &tft;
    bool initialized;
};
