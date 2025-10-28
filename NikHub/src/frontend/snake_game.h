#pragma once
#include <TFT_eSPI.h>
#include "utils/colors.h"
#include "utils/menu_utils.h"
#include <vector>

class SnakeGame {
public:
    SnakeGame(TFT_eSPI &tftRef) : tft(tftRef), initialized(false) {}

    void init();
    void drawMenu();
    void reset() { initialized = false; }
    String handleTouch(int x, int y, bool swipeLeft, bool swipeRight, bool swipeUp, bool swipeDown, bool mediumPress);

private:
    TFT_eSPI &tft;
    bool initialized;
};
