#include "frontend/others_menu.h"

void OthersMenu::init() {

    layerSprite.createSprite(LAYER_W, LAYER_H);

    //tft.fillScreen(TFT_FOREST);
    tft.fillScreen(TFT_WHITE);
    layerSprite.fillRoundRect(LAYER_X, LAYER_Y, LAYER_W, LAYER_H, RADIUS, TFT_EXTRADARKGREEN);

    /* ICONS */

    // palette
    layerSprite.fillRoundRect(ICON_PALETTE_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS, TFT_BLACK);
    layerSprite.fillRoundRect(ICON_PALETTE_X + 9, ICON_Y + 9, 14, 14, 3, TFT_DARKVIOLET);
    layerSprite.fillRoundRect(ICON_PALETTE_X + 9 + 14 + 9, ICON_Y + 9, 14, 14, 3, TFT_MEDIUMVIOLET);
    layerSprite.fillRoundRect(ICON_PALETTE_X + 9, ICON_Y + 9 + 14 + 9, 14, 14, 3, TFT_VIOLET);
    layerSprite.fillRoundRect(ICON_PALETTE_X + 9 + 14 + 9, ICON_Y + 9 + 14 + 9, 14, 14, 3, TFT_ORCHID);

    // home
    layerSprite.fillRoundRect(GO_HOME_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS, TFT_BLACK);
    layerSprite.setTextColor(TFT_WHITE);
    layerSprite.setTextDatum(MC_DATUM);
    layerSprite.setTextSize(1);
    layerSprite.setFreeFont(&FreeMono9pt7b);
    layerSprite.drawString("<", GO_HOME_X + ICON_W/2, ICON_Y + ICON_H/2);

    layerSprite.pushSprite(LAYER_X, LAYER_Y);
    
    initialized = true;
}

void OthersMenu::drawMenu() {
    if (!initialized) init();
}

String OthersMenu::handleTouch(int x, int y) {
    if (isPointInRoundedRect(x, y, ICON_PALETTE_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS)) return "palette";
    if (isPointInRoundedRect(x, y, GO_HOME_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS)) return "main";
    return "";
}