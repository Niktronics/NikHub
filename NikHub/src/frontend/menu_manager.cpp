#include "frontend/menu_manager.h"

void MenuManager::init() {
    currentMenu = "main";
    tft.init();
    tft.setRotation(3);
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(0);
    tft.setTextDatum(MC_DATUM);
    tft.setFreeFont(&FreeSansBold18pt7b);
    tft.setTextColor(TFT_RED);
    tft.drawString("NikHub", tft.width()/2, tft.height()/2);
    tft.setTextColor(TFT_WHITE);
    tft.setFreeFont(&FreeMono9pt7b);
    tft.drawString("Caricamento", tft.width()/2, tft.height()/2 + 20);
}

void MenuManager::update() {
    handleTouch();

    if (millis() - lastRender < RENDER_INTERVAL) return;
    lastRender = millis();

    if (currentMenu == "main") {
        mainMenu.drawMenu();
    }

    if (currentMenu == "others") {
        othersMenu.drawMenu();
    }

    if (currentMenu == "palette") {
        paletteMenu.drawMenu();
    }

    if (currentMenu == "games") {
        gamesMenu.drawMenu();
    }

    if (currentMenu == "snake") {
        snakeGame.drawMenu();
    }

    //notification.update();
}

void MenuManager::setMenu(String menu) {
    if (currentMenu == "main") mainMenu.reset();
    if (currentMenu == "others") othersMenu.reset();
    if (currentMenu == "palette") paletteMenu.reset();
    if (currentMenu == "games") gamesMenu.reset();
    if (currentMenu == "snake") snakeGame.reset();
    currentMenu = menu;
}

void MenuManager::handleTouch() {
    int touchX, touchY;
    bool swipeLeft = false;
    bool swipeRight = false;
    bool swipeUp = false;
    bool swipeDown = false;
    bool longPress = false;
    bool mediumPress = false;

    if (!input.isTouched(touchX, touchY)) {
        if (isTouching) {
            unsigned long pressDuration = millis() - touchStartTime;
            int dx = lastTouchX - startX;
            int dy = lastTouchY - startY;

            if (pressDuration >= LONG_PRESS_MS) longPress = true;
            if (pressDuration >= MEDIUM_PRESS_MS) mediumPress = true;

            if (abs(dx) > SWIPE_MIN_DIST || abs(dy) > SWIPE_MIN_DIST) {
                if (abs(dx) > abs(dy)) {
                    if (dx > 0) swipeRight = true;
                    else swipeLeft = true;
                } else {
                    if (dy > 0) swipeDown = true;
                    else swipeUp = true;
                }
            }

            String nextMenu = "";
            if (currentMenu == "games") {
                nextMenu = gamesMenu.handleTouch(lastTouchX, lastTouchY, swipeLeft, swipeRight, mediumPress);
            }

            if (currentMenu == "snake") {
                nextMenu = snakeGame.handleTouch(lastTouchX, lastTouchY, swipeLeft, swipeRight, swipeUp, swipeDown, mediumPress);
            }

            if (nextMenu != "") setMenu(nextMenu);

            isTouching = false;
        }
        return;
    }

    if (!isTouching) {
        touchStartTime = millis();
        startX = touchX;
        startY = touchY;
        isTouching = true;
    }

    lastTouchX = touchX;
    lastTouchY = touchY;

    if (millis() - lastTouchTime < DEBOUNCE_MS) return;
    lastTouchTime = millis();
    
    String nextMenu = "";

    if (currentMenu == "main") nextMenu = mainMenu.handleTouch(touchX, touchY);
    else if (currentMenu == "others") nextMenu = othersMenu.handleTouch(touchX, touchY);
    else if (currentMenu == "palette") nextMenu = paletteMenu.handleTouch(touchX, touchY);

    if (nextMenu != "") setMenu(nextMenu);

    Serial.printf("Touch: %d, %d\n", touchX, touchY);
}