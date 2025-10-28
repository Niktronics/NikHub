#include "frontend/games_menu.h"

constexpr int SCREEN_X = 320;
constexpr int SCREEN_Y = 240;

constexpr int GAME_LAYER_Y = 36;
constexpr int GAME_LAYER_H = 180;

constexpr int GAME_LAYER_SIDE_W = 40;

constexpr int GAME_LAYER_LEFT_X   = 0;
constexpr int GAME_LAYER_RIGHT_X  = SCREEN_X - GAME_LAYER_SIDE_W;
constexpr int GAME_LAYER_CENTER_X = GAME_LAYER_LEFT_X + GAME_LAYER_SIDE_W;
constexpr int GAME_LAYER_CENTER_W = SCREEN_X - (2 * GAME_LAYER_SIDE_W);

struct GameItem {
    const char* menuName;
    const char* displayName;
};

constexpr GameItem games[] = {
    {"snake", "Snake"},
    {"pingpong", "Ping Pong"},
    {"tris", "Tris"}
};

int gameIndex = 1; // 0 = snake, 1 = pingpong, 2 = tris

void GamesMenu::init() {

    //tft.pushImage(0, 0, SCREEN_X, SCREEN_Y, &greenWallpaperBitmap);

    //tft.fillScreen(0x11e1);

    tft.setFreeFont(&FreeSerifBold12pt7b);
    tft.setTextSize(1);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Giochi", SCREEN_X/2, 15);

    tft.fillCircle(SCREEN_X-20, 15, 13, TFT_RED);
    tft.setFreeFont(&FreeMonoBold9pt7b);
    tft.drawString("X", SCREEN_X-20, 15);
    
    leftGameLayer.createSprite(GAME_LAYER_SIDE_W, GAME_LAYER_H);
    centerGameLayer.createSprite(GAME_LAYER_CENTER_W, GAME_LAYER_H);
    rightGameLayer.createSprite(GAME_LAYER_SIDE_W, GAME_LAYER_H);

    leftGameLayer.fillSprite(TFT_DARKGREEN);
    centerGameLayer.fillSprite(TFT_GREEN);
    rightGameLayer.fillSprite(TFT_DARKGREEN);

    leftGameLayer.pushSprite(GAME_LAYER_LEFT_X, GAME_LAYER_Y);
    centerGameLayer.pushSprite(GAME_LAYER_CENTER_X, GAME_LAYER_Y);
    rightGameLayer.pushSprite(GAME_LAYER_RIGHT_X, GAME_LAYER_Y);

    initialized = true;
}

void GamesMenu::drawMenu() {
    if (!initialized) init();

    int gameAmount = sizeof(games) / sizeof(games[0]);

    centerGameLayer.fillSprite(TFT_GREEN);
    centerGameLayer.setTextDatum(MC_DATUM);
    centerGameLayer.setFreeFont(&FreeMonoBold12pt7b);
    centerGameLayer.setTextColor(TFT_WHITE, TFT_GREEN);
    centerGameLayer.drawString(games[gameIndex].displayName, GAME_LAYER_CENTER_W / 2, GAME_LAYER_H / 2);

    int prevIndex = (gameIndex - 1 + gameAmount) % gameAmount;
    leftGameLayer.fillSprite(TFT_DARKGREEN);
    leftGameLayer.setTextDatum(MC_DATUM);
    leftGameLayer.setFreeFont(&FreeMonoBold12pt7b);
    leftGameLayer.setTextColor(TFT_WHITE, TFT_DARKGREEN);
    leftGameLayer.drawString(games[prevIndex].displayName, GAME_LAYER_SIDE_W / 2, GAME_LAYER_H / 2);

    int nextIndex = (gameIndex + 1) % gameAmount;
    rightGameLayer.fillSprite(TFT_DARKGREEN);
    rightGameLayer.setTextDatum(MC_DATUM);
    rightGameLayer.setFreeFont(&FreeMonoBold12pt7b);
    rightGameLayer.setTextColor(TFT_WHITE, TFT_DARKGREEN);
    rightGameLayer.drawString(games[nextIndex].displayName, GAME_LAYER_SIDE_W / 2, GAME_LAYER_H / 2);

    leftGameLayer.pushSprite(GAME_LAYER_LEFT_X, GAME_LAYER_Y);
    centerGameLayer.pushSprite(GAME_LAYER_CENTER_X, GAME_LAYER_Y);
    rightGameLayer.pushSprite(GAME_LAYER_RIGHT_X, GAME_LAYER_Y);
}


String GamesMenu::handleTouch(int x, int y, bool swipeLeft, bool swipeRight, bool mediumPress) {
    int gameAmount = sizeof(games) / sizeof(games[0]);

    if (isPointInCircle(x, y, SCREEN_X-20, 15, 70)) {
        return "main";
    }

    else if (isPointInRect(x, y, GAME_LAYER_LEFT_X, GAME_LAYER_Y, GAME_LAYER_SIDE_W, GAME_LAYER_H) || swipeRight) {
        gameIndex = (gameIndex - 1 + gameAmount) % gameAmount;
    }

    else if (isPointInRect(x, y,GAME_LAYER_RIGHT_X, GAME_LAYER_Y, GAME_LAYER_SIDE_W, GAME_LAYER_H) || swipeLeft) {
        gameIndex = (gameIndex + 1) % gameAmount;
    }

    else if (mediumPress == true && isPointInRect(x, y, GAME_LAYER_CENTER_X, GAME_LAYER_Y, GAME_LAYER_CENTER_W, GAME_LAYER_H)) {
        return games[gameIndex].menuName;
    }

    return "";
}