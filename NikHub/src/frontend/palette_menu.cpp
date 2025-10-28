#include "frontend/palette_menu.h"

constexpr int MARGIN = 15;
static int LAYER_H = TFT_HEIGHT - 2 * MARGIN;
static int LAYER_W = TFT_WIDTH - 2 * MARGIN;
constexpr int LAYER_X = MARGIN;
constexpr int LAYER_Y = MARGIN;
constexpr int RADIUS = 15;

constexpr int ICON_W = 20;
constexpr int ICON_H = 20;
constexpr int ICON_Y = 10;
constexpr int ICON_RADIUS = RADIUS / 2;
constexpr int ICON_SPACING_X = 25;
constexpr int ICON_SPACING_Y = 25;

const int GO_HOME_X = LAYER_X + LAYER_W - ICON_W - 10;
const int GO_HOME_Y = LAYER_Y + LAYER_H - ICON_H - 10;

struct ColorItem {
    uint16_t color;
    const char* name;
};

ColorItem colors[] = {
    {TFT_DARKGREY, "DARKGREY"},
    {TFT_LIGHTGREY, "LIGHTGREY"},
    {TFT_SILVER, "SILVER"},
    {TFT_DIMGRAY, "DIMGRAY"},
    {TFT_GAINSBORO, "GAINSBORO"},
    {TFT_NAVY, "NAVY"},
    {TFT_DARKBLUE, "DARKBLUE"},
    {TFT_MEDIUMBLUE, "MEDIUMBLUE"},
    {TFT_SKYBLUE, "SKYBLUE"},
    {TFT_LIGHTBLUE, "LIGHTBLUE"},
    {TFT_DEEPSKYBLUE, "DEEPSKYBLUE"},
    {TFT_STEELBLUE, "STEELBLUE"},
    {TFT_DODGERBLUE, "DODGERBLUE"},
    {TFT_ROYALBLUE, "ROYALBLUE"},
    {TFT_CORNFLOWER, "CORNFLOWER"},
    {TFT_EXTRADARKGREEN, "EXTRADARKGREEN"},
    {TFT_DARKGREEN, "DARKGREEN"},
    {TFT_FOREST, "FOREST"},
    {TFT_SEAGREEN, "SEAGREEN"},
    {TFT_LIME, "LIME"},
    {TFT_LIMEGREEN, "LIMEGREEN"},
    {TFT_SPRINGGREEN, "SPRINGGREEN"},
    {TFT_MEDIUMGREEN, "MEDIUMGREEN"},
    {TFT_LIGHTGREEN, "LIGHTGREEN"},
    {TFT_GREENYELLOW, "GREENYELLOW"},
    {TFT_DARKRED, "DARKRED"},
    {TFT_FIREBRICK, "FIREBRICK"},
    {TFT_CRIMSON, "CRIMSON"},
    {TFT_INDIANRED, "INDIANRED"},
    {TFT_SALMON, "SALMON"},
    {TFT_LIGHTSALMON, "LIGHTSALMON"},
    {TFT_CORAL, "CORAL"},
    {TFT_TOMATO, "TOMATO"},
    {TFT_DARKVIOLET, "DARKVIOLET"},
    {TFT_MEDIUMVIOLET, "MEDIUMVIOLET"},
    {TFT_VIOLET, "VIOLET"},
    {TFT_ORCHID, "ORCHID"},
    {TFT_MEDIUMORCHID, "MEDIUMORCHID"},
    {TFT_PLUM, "PLUM"},
    {TFT_SADDLEBROWN, "SADDLEBROWN"},
    {TFT_SIENNA, "SIENNA"},
    {TFT_CHOCOLATE, "CHOCOLATE"},
    {TFT_PERU, "PERU"},
    {TFT_TAN, "TAN"},
    {TFT_WHEAT, "WHEAT"},
    {TFT_BURLYWOOD, "BURLYWOOD"},
    {TFT_KHAKI, "KHAKI"},
    {TFT_LIGHTKHAKI, "LIGHTKHAKI"},
    {TFT_GOLD, "GOLD"},
    {TFT_LIGHTYELLOW, "LIGHTYELLOW"},
    {TFT_LEMONCHIFFON, "LEMONCHIFFON"},
};

void PaletteMenu::init() {
    tft.fillScreen(TFT_WHITE);

    int x = LAYER_X;
    int y = ICON_Y;
    int count = 0;

    for (auto &c : colors) {
        tft.fillRoundRect(x, y, ICON_W, ICON_H, ICON_RADIUS, c.color);
        x += ICON_SPACING_X;
        count++;
        if (count % 9 == 0) {
            x = LAYER_X;
            y += ICON_SPACING_Y;
        }
    }

    // home
    tft.fillRoundRect(GO_HOME_X, GO_HOME_Y, ICON_W, ICON_H, ICON_RADIUS, TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeMono9pt7b);
    tft.drawString("<", GO_HOME_X + ICON_W / 2, GO_HOME_Y + ICON_H / 2);

    initialized = true;
}

void PaletteMenu::drawMenu() {
    if (!initialized) init();
}

String PaletteMenu::handleTouch(int x, int y) {
    if (isPointInRoundedRect(x, y, GO_HOME_X, GO_HOME_Y, ICON_W, ICON_H, ICON_RADIUS)) return "main";
    return "";
}
