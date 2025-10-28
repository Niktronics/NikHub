#include "frontend/notification_layer.h"
#include "frontend/menu_manager.h" 

void NotificationLayer::update() {
    if (notifications.empty()) {
        if (nSprite.created()) {
            nSprite.deleteSprite();
        }
        if (tempSprite.created()) {
            tempSprite.deleteSprite();
        }
        int x = (tft.width() - NOTIFICATION_WIDTH) / 2;
        tft.fillRect(x, 10, NOTIFICATION_WIDTH, NOTIFICATION_HEIGHT, TFT_BLACK);
        return;
    }

    Notification &current = notifications.front();
    if (!current.persistent && (millis() - current.startTime) >= NOTIFICATION_TIMEOUT) {
        notifications.erase(notifications.begin());
        int x = (tft.width() - NOTIFICATION_WIDTH) / 2;
        tft.fillRect(x, 10, NOTIFICATION_WIDTH, NOTIFICATION_HEIGHT, TFT_BLACK);
        if (nSprite.created()) nSprite.deleteSprite();
        if (tempSprite.created()) tempSprite.deleteSprite();
        Serial.println("Notification removed due to timeout");
    }

    if (!notifications.empty()) {
        drawNotification(notifications.front());
        Serial.println("Notification drawn");
    }

    Serial.println("Notifications count: " + String(notifications.size()));
}

void NotificationLayer::showNotification(const String &message, bool persistent, bool important) {
    Notification n = { persistent, important, message, millis() };
    notifications.push_back(n);
}

void NotificationLayer::drawNotification(Notification &n) {
    int originX = (tft.width() - NOTIFICATION_WIDTH) / 2;
    int originY = 10;

    // prepara tempSprite con lo sfondo solo se non esiste
    if (!tempSprite.created()) {
        tempSprite.createSprite(NOTIFICATION_WIDTH, NOTIFICATION_HEIGHT);
        // copia pixel dallo schermo nella tempSprite
        for (int yy = 0; yy < NOTIFICATION_HEIGHT; ++yy) {
            for (int xx = 0; xx < NOTIFICATION_WIDTH; ++xx) {
                uint16_t c = tft.readPixel(originX + xx, originY + yy);
                tempSprite.drawPixel(xx, yy, c);
            }
        }
    }

    // prepara nSprite
    if (!nSprite.created()) {
        nSprite.createSprite(NOTIFICATION_WIDTH, NOTIFICATION_HEIGHT);
    }

    // disegna sfondo notifica dentro nSprite
    nSprite.fillRoundRect(0, 0, NOTIFICATION_WIDTH, NOTIFICATION_HEIGHT, 10, TFT_EXTRADARKGREEN);

    nSprite.setTextSize(1);
    nSprite.setTextDatum(MC_DATUM);
    nSprite.setFreeFont(&FreeSansBold9pt7b);
    nSprite.setTextColor(n.important ? TFT_RED : TFT_WHITE);

    // testo centrato
    nSprite.fillRect(0, 0, NOTIFICATION_WIDTH, NOTIFICATION_HEIGHT, TFT_TRANSPARENT); // assicurati trasparente prima del testo
    nSprite.drawString(n.content, NOTIFICATION_WIDTH / 2, NOTIFICATION_HEIGHT / 2);

    // prima disegna lo sfondo salvato, poi la notifica sopra
    tempSprite.pushSprite(originX, originY);
    nSprite.pushSprite(originX, originY);
}

void NotificationLayer::clearNotification() {
    if (!notifications.empty()) {
        notifications.erase(notifications.begin());
    }
    if (nSprite.created()) nSprite.deleteSprite();
    if (tempSprite.created()) tempSprite.deleteSprite();
    int x = (tft.width() - NOTIFICATION_WIDTH) / 2;
    tft.fillRect(x, 10, NOTIFICATION_WIDTH, NOTIFICATION_HEIGHT, TFT_BLACK);
}
