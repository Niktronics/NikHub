#pragma once
#include <TFT_eSPI.h>
#include "frontend/notification_layer.h"
#include "utils/colors.h"
#include "utils/menu_utils.h"
#include "backend/input.h"
#include "frontend/main_menu.h"
#include "frontend/others_menu.h"
#include "frontend/palette_menu.h"
#include "frontend/games_menu.h"
#include "frontend/snake_game.h"

class MenuManager {
public: 
    MenuManager(TFT_eSPI &tftRef, Input &inputRef, NotificationLayer &notifRef, 
                MainMenu &mainRef, OthersMenu &othRef, PaletteMenu &palRef, 
                GamesMenu &gamRef, SnakeGame &snakeRef)
        : tft(tftRef), input(inputRef), notification(notifRef),
          mainMenu(mainRef), othersMenu(othRef), paletteMenu(palRef),
          gamesMenu(gamRef), snakeGame(snakeRef),
          currentMenu("main")
    {}

    void init();
    void update();  
    void setMenu(String menu);
    void handleTouch();
    const String& getMenu() const { return currentMenu; }

private:
    TFT_eSPI &tft;
    Input &input;
    NotificationLayer &notification;
    MainMenu &mainMenu;
    OthersMenu &othersMenu;
    PaletteMenu &paletteMenu;
    GamesMenu &gamesMenu;
    SnakeGame &snakeGame;

    String currentMenu;
    unsigned long lastRender = 0;
    const unsigned long RENDER_INTERVAL = 33; // ~30 FPS
    int DEBOUNCE_MS = 50;
    long lastTouchTime = 0;
    int LONG_PRESS_MS = 800;
    int MEDIUM_PRESS_MS = 400;
    int SWIPE_MIN_DIST = 30;
    unsigned long touchStartTime = 0;
    int lastTouchX, lastTouchY, startX, startY;
    bool isTouching = false;
};
