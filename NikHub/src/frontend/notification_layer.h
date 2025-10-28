#pragma once

#include <TFT_eSPI.h>
#include <vector>
#include "utils/colors.h"

class MenuManager;

constexpr int NOTIFICATION_HEIGHT = 23;
constexpr int NOTIFICATION_WIDTH = 250;
constexpr int NOTIFICATION_TIMEOUT = 3000;

struct Notification {
    bool persistent;
    bool important;
    String content;
    unsigned long startTime;
};

class NotificationLayer {
public:
    NotificationLayer(TFT_eSPI &tftRef)
        : tft(tftRef), menuManager(nullptr), nSprite(&tftRef), tempSprite(&tftRef) {}

    void setMenuManager(MenuManager &menuRef) { menuManager = &menuRef; }

    void showNotification(const String &message, bool persistent = false, bool important = false);
    void drawNotification(Notification &n);
    void clearNotification();
    void update();

private:
    TFT_eSPI &tft;
    MenuManager *menuManager;
    TFT_eSprite nSprite;
    TFT_eSprite tempSprite;
    std::vector<Notification> notifications;
};
