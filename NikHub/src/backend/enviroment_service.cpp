#include "enviroment_service.h"

void EnviromentService::getJsonFromUrl(const char* url, JsonDocument& doc) {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
        String payload = http.getString();
        deserializeJson(doc, payload);
    }
    http.end();
}

String EnviromentService::getTimeHHMM() {
    timeClient.update();
    return timeClient.getFormattedTime().substring(0, 5).c_str();
}

String EnviromentService::getWeatherDescription() {
    if (millis() - lastWeatherUpdate > 10 * 60 * 1000) return lastWeatherDescription;

    HTTPClient http;
    http.begin(openWeatherAddress);
    int httpCode = http.GET();
    if (httpCode > 0) {
        String payload = http.getString();
        JsonDocument doc;
        deserializeJson(doc, payload);
        float temp = doc["main"]["temp"];
        int umidita = doc["main"]["humidity"];
        const char* descrizione = doc["weather"][0]["description"];
        String tempStr = String(temp, 1) + "C";
        tempStr.replace(".", ",");
        lastWeatherDescription = tempStr + " " + String(descrizione);
        lastWeatherUpdate = millis();
    }
    http.end();
    return lastWeatherDescription;
}