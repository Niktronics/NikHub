#pragma once
#include <TFT_eSPI.h>
#include "backend/enviroment_service.h"
#include "images/greenWallpaper.h"
#include "utils/colors.h"
#include "utils/menu_utils.h"
#include "notification_layer.h"

class MainMenu {
    private:
        TFT_eSPI &tft;
        EnviromentService &enviromentService;
        NotificationLayer &notification;
        TFT_eSprite clockSprite;
        TFT_eSprite weatherSprite;
        bool initialized = false;
        void init();
    public:
        MainMenu(TFT_eSPI &tftRef, EnviromentService &envRef, NotificationLayer &notifRef)
            : tft(tftRef), enviromentService(envRef), notification(notifRef),
              clockSprite(&tftRef), weatherSprite(&tftRef), initialized(false)
        {}
        void drawMenu();
        void reset() { 
            initialized = false;
            clockSprite.deleteSprite();
            weatherSprite.deleteSprite();
         }
        String handleTouch(int x, int y);
};