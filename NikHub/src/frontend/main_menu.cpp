#include "frontend/main_menu.h"

unsigned long lastWeatherUpdate = 0;

constexpr int ICON_W = 55;
constexpr int ICON_H = 55;
constexpr int ICON_Y = 162;
constexpr int ICON_RADIUS = 10;
constexpr int ICON_SPACING = 74;

constexpr int ICON_KEYPAD_X   = 21;
constexpr int ICON_GAMES_X    = ICON_KEYPAD_X + ICON_SPACING;
constexpr int ICON_REMINDER_X = ICON_GAMES_X + ICON_SPACING;
constexpr int ICON_OTHERS_X   = ICON_REMINDER_X + ICON_SPACING;

void MainMenu::init() {
    tft.pushImage(0, 0, GREENWALLPAPER_WIDTH, GREENWALLPAPER_HEIGHT, greenWallpaperBitmap);

    // Keypad
    tft.fillRoundRect(ICON_KEYPAD_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS, TFT_DARKGREEN);
    tft.fillRoundRect(ICON_KEYPAD_X + 9, ICON_Y + 9, 14, 14, 3, TFT_GREEN);
    tft.fillRoundRect(ICON_KEYPAD_X + 9 + 14 + 9, ICON_Y + 9, 14, 14, 3, TFT_WHITE);
    tft.fillRoundRect(ICON_KEYPAD_X + 9, ICON_Y + 9 + 14 + 9, 14, 14, 3, TFT_WHITE);
    tft.fillRoundRect(ICON_KEYPAD_X + 9 + 14 + 9, ICON_Y + 9 + 14 + 9, 14, 14, 3, TFT_GREEN);

    // Games
    tft.fillRoundRect(ICON_GAMES_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS, TFT_DARKGREEN);
    tft.fillRoundRect(ICON_GAMES_X + 7, ICON_Y + 15, 40, 25, 6, TFT_WHITE);
    tft.fillRect(ICON_GAMES_X + 12, ICON_Y + 27, 10, 3, TFT_DARKGREEN);
    tft.fillRect(ICON_GAMES_X + 16, ICON_Y + 23, 3, 10, TFT_DARKGREEN);
    tft.fillCircle(ICON_GAMES_X + 32, ICON_Y + 30, 3, TFT_RED);
    tft.fillCircle(ICON_GAMES_X + 40, ICON_Y + 26, 3, TFT_BLUE);

    // Reminder
    tft.fillRoundRect(ICON_REMINDER_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS, TFT_DARKGREEN);
    tft.fillCircle(ICON_REMINDER_X + ICON_W/2, ICON_Y + 25, 12, TFT_YELLOW);
    tft.fillCircle(ICON_REMINDER_X + ICON_W/2 - 4, ICON_Y + 25 - 4, 3, TFT_WHITE);
    tft.fillRect(ICON_REMINDER_X + ICON_W/2 - 6, ICON_Y + 25 + 12, 12, 6, TFT_LIGHTGREY);
    tft.drawLine(ICON_REMINDER_X + ICON_W/2 - 6, ICON_Y + 25 + 14, ICON_REMINDER_X + ICON_W/2 + 6, ICON_Y + 25 + 14, TFT_DARKGREY);
    tft.drawLine(ICON_REMINDER_X + ICON_W/2 - 6, ICON_Y + 25 + 16, ICON_REMINDER_X + ICON_W/2 + 6, ICON_Y + 25 + 16, TFT_DARKGREY);

    // Others
    tft.fillRoundRect(ICON_OTHERS_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS, TFT_DARKGREEN);
    tft.fillCircle(ICON_OTHERS_X + ICON_W/2 - 14, ICON_Y + ICON_H/2, 4, TFT_WHITE);
    tft.fillCircle(ICON_OTHERS_X + ICON_W/2, ICON_Y + ICON_H/2, 4, TFT_WHITE);
    tft.fillCircle(ICON_OTHERS_X + ICON_W/2 + 14, ICON_Y + ICON_H/2, 4, TFT_WHITE);

    if (!clockSprite.created()) clockSprite.createSprite(220, 75);
    if (!weatherSprite.created()) weatherSprite.createSprite(240, 22);

    initialized = true;
}

void MainMenu::drawMenu() {
    if (!initialized) init();

    static const int clockX = (tft.width() - 220) / 2;
    static const int clockY = (tft.height() - 75 - 110) / 2 +2;
    static const int weatherX = (tft.width() - 240) / 2;
    static const int weatherY = (tft.height() - 22) / 2 - 5;

    fillSpriteWithWallpaper(clockSprite, clockX, clockY);
    clockSprite.setTextSize(2);
    clockSprite.setTextColor(TFT_WHITE);
    clockSprite.setTextDatum(MC_DATUM);
    clockSprite.setFreeFont(&FreeSerifBold24pt7b);
    String timeFormatted = enviromentService.getTimeHHMM();
    clockSprite.drawString(timeFormatted, clockSprite.width()/2, clockSprite.height()/2);

    fillSpriteWithWallpaper(weatherSprite, weatherX, weatherY);
    weatherSprite.setTextSize(1);
    weatherSprite.setTextColor(TFT_WHITE);
    weatherSprite.setTextDatum(MC_DATUM);
    weatherSprite.setFreeFont(&FreeMono9pt7b);
    String weatherDesc = enviromentService.getWeatherDescription();
    weatherSprite.drawString(weatherDesc, weatherSprite.width()/2, weatherSprite.height()/2);

    clockSprite.pushSprite(clockX, clockY, TFT_BLACK);
    weatherSprite.pushSprite(weatherX, weatherY, TFT_BLACK);
}

String MainMenu::handleTouch(int x, int y) {
    if (isPointInRoundedRect(x, y, ICON_KEYPAD_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS)) return "keypad";
    if (isPointInRoundedRect(x, y, ICON_GAMES_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS)) return "games";
    if (isPointInRoundedRect(x, y, ICON_REMINDER_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS))  return "reminder";
    if (isPointInRoundedRect(x, y, ICON_OTHERS_X, ICON_Y, ICON_W, ICON_H, ICON_RADIUS)) return "others";
 
    return "";
}