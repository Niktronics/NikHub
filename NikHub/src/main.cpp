#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>

#include "backend/input.h"
#include "backend/enviroment_service.h"

#include "frontend/menu_manager.h"
#include "frontend/notification_layer.h"
#include "frontend/main_menu.h"
#include "frontend/others_menu.h"
#include "frontend/palette_menu.h"
#include "frontend/games_menu.h"
#include "frontend/snake_game.h"

constexpr int XPT2046_CS = 33;
constexpr int XPT2046_IRQ = 36;
constexpr int XPT2046_MISO = 39;
constexpr int XPT2046_MOSI = 32;
constexpr int XPT2046_CLK = 25;

const char* ssid = "";
const char* password = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "it.pool.ntp.org", 3600);

SPIClass spiTouch(HSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);

TFT_eSPI tft = TFT_eSPI();
Input input(ts);
NotificationLayer notification(tft);
EnviromentService enviromentService(timeClient);

// crea i menu con riferimento al TFT e servizi
MainMenu mainMenu(tft, enviromentService, notification);
OthersMenu othersMenu(tft);
PaletteMenu paletteMenu(tft);
GamesMenu gamesMenu(tft);
SnakeGame snakeGame(tft);

// menu manager prende i riferimenti
MenuManager menuManager(tft, input, notification, mainMenu, othersMenu, paletteMenu, gamesMenu, snakeGame);


void setup() {
    Serial.begin(115200);

    spiTouch.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    ts.begin(spiTouch);
    ts.setRotation(3);

    menuManager.init();
    menuManager.setMenu("main");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connessione WiFi...");
    }
    Serial.print("Connesso! IP: ");
    Serial.println(WiFi.localIP());

    timeClient.begin();

    Serial.println("Setup completato");
}

void loop() {
    menuManager.update();
}