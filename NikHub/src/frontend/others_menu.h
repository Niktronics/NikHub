#pragma once
#include <TFT_eSPI.h>
#include "utils/colors.h"
#include "utils/menu_utils.h"

class OthersMenu {
public:
    OthersMenu(TFT_eSPI &tftRef)
        : tft(tftRef), layerSprite(&tftRef), initialized(false)
    {}

    void init();
    void drawMenu();
    void reset() { 
        initialized = false;
        layerSprite.deleteSprite();
    }
    String handleTouch(int x, int y);

private:
    TFT_eSPI &tft;
    TFT_eSprite layerSprite;
    bool initialized;

    static constexpr int WIDTH = 320;
    static constexpr int HEIGHT = 240;
    static constexpr int AREA = WIDTH * HEIGHT;
    static constexpr int MARGIN = 15;
    static constexpr int LAYER_H = WIDTH - 2 * MARGIN;
    static constexpr int LAYER_W = HEIGHT - 2 * MARGIN;
    static constexpr int LAYER_X = MARGIN;
    static constexpr int LAYER_Y = MARGIN;
    static constexpr int RADIUS = 15;

    static constexpr int ICON_W = 55;
    static constexpr int ICON_H = 55;
    static constexpr int ICON_Y = 163;
    static constexpr int ICON_RADIUS = RADIUS/2;
    static constexpr int ICON_SPACING = 74;

    static constexpr int ICON_PALETTE_X   = 21;
    static constexpr int ICON_1_X    = ICON_PALETTE_X + ICON_SPACING;
    static constexpr int ICON_2_X = ICON_1_X + ICON_SPACING;
    static constexpr int GO_HOME_X   = ICON_2_X + ICON_SPACING;
};
