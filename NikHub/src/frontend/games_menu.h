#pragma once
#include <TFT_eSPI.h>
#include "utils/colors.h"
#include "utils/menu_utils.h"
//#include "images/greenWallpaper.h"

class GamesMenu {
    private:
        TFT_eSPI &tft;
        bool initialized = false;
        TFT_eSprite rightGameLayer;
        TFT_eSprite centerGameLayer;
        TFT_eSprite leftGameLayer;
    public:
        GamesMenu(TFT_eSPI &tftRef)
            : tft(tftRef),
              rightGameLayer(&tftRef),
              centerGameLayer(&tftRef),
              leftGameLayer(&tftRef)
        {}
        void init();
        void drawMenu();
        void reset() { 
            initialized = false;
            rightGameLayer.deleteSprite();
            centerGameLayer.deleteSprite();
            leftGameLayer.deleteSprite();
        }
        String handleTouch(int x, int y, bool swipeLeft, bool swipeRight, bool mediumPress);
};